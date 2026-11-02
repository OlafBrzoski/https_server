#pragma once
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
        HttpConnection(int fd, EpollReactor* reactor);
        ~HttpConnection(); 

        HttpConnection(const HttpConnection&) = delete;
        HttpConnection& operator=(const HttpConnection&) = delete;

        void handle_read();  
        void handle_write(); 

        bool is_timed_out(int timeout_seconds) const;
};
