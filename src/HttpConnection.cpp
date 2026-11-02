#include <string>
#include <chrono>
#include "EpollReactor.h"
#include "http_parser.h" 
#include "router.h"
#include <unistd.h>

class HttpConnection {
private:
    int fd_;
    EpollReactor* reactor_; 
    
    std::string raw_request_data_; 
    std::string write_buffer_;     
    
    std::chrono::steady_clock::time_point last_activity_;

public:
    HttpConnection(int fd, EpollReactor* reactor){
        fd_ = fd;
        reactor_ = reactor;
        reactor_->add(fd_, EPOLLIN | EPOLLET);
        last_activity_ = std::chrono::steady_clock::now();
    }
    ~HttpConnection(){
        close(fd_);
     }

    HttpConnection(const HttpConnection&) = delete;
    HttpConnection& operator=(const HttpConnection&) = delete;

    void handle_read(){
        while (true) {
            char buff [4096];
            int bytes_read = recv(fd_,buff,sizeof(buff),0);

            if ( bytes_read > 0 ){
                raw_request_data_.append(buff,bytes_read);
                last_activity_ = std::chrono::steady_clock::now();
            }

            else if ( bytes_read == 0 ){
                return;
            }

            else{

                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    break; 
                } 
                else {
                    std::cout<<"Something went wrong: " << strerror(errno) << std::endl;
                    return; 
                }
            }
        }
        size_t end_of_request_; 
        while((end_of_request_ = raw_request_data_.find("\r\n\r\n")) != std::string::npos){
            std::string complete_request = raw_request_data_.substr(0, end_of_request_ + 4);
            raw_request_data_.erase(0, end_of_request_ + 4);

            HttpParser parser;
            HttpRequest request = parser.parse(complete_request);
            write_buffer_.append( build_response(request));

        }
        if ( !write_buffer_.empty() ){
            handle_write();
        }
    }

    void handle_write(){
        while (!write_buffer_.empty()){
            int bytes_send = send(fd_, write_buffer_.c_str(), write_buffer_.length(), 0);
            if ( bytes_send > 0 ){
                write_buffer_.erase(0,bytes_send);
                last_activity_ = std::chrono::steady_clock::now();
            }
            else if ( bytes_send < 0 ){
                if( errno == EAGAIN ){
                    reactor_->modify(fd_,EPOLLIN | EPOLLOUT | EPOLLET);
                    return;
                }
                else{
                    std::cout<< "Something went wrong: " << strerror(errno) << std::endl;
                    return;
                }
            }
            else{
                reactor_->modify(fd_,EPOLLIN | EPOLLET);
                return;
            }
        }

        reactor_->modify(fd_,EPOLLIN | EPOLLET);

    } 

    bool is_timed_out(int timeout_seconds) const{
        if(timeout_seconds <= std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - last_activity_).count()){
            return true;
        }
        else{
            return false;
        }
    }
};
