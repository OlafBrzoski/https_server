#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <cerrno>

#define BACKLOG 10

int main(){
    struct sockaddr_storage client_addr;
    struct addrinfo hints, *res;
    int sock_fd, client_fd;
    socklen_t addr_size;

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL,"8080",&hints,&res);

    sock_fd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if ( sock_fd < 0 ){
        std::cout << "Socket error: "<< strerror(errno) << std::endl;
        return -1;
    }

    if( bind(sock_fd,res->ai_addr,res->ai_addrlen) < 0){
        std::cout << "Binding error: " << strerror(errno) << std::endl;
        return -1;
    }

    if( listen(sock_fd,BACKLOG) < 0 ){
        std::cout << "Listening error: " << strerror(errno) << std::endl;
        return -1;
    }
    
    addr_size = sizeof(client_addr);
    client_fd = accept(sock_fd,(struct sockaddr *)&client_addr,&addr_size);
    if( client_fd < 0 ){
        std::cout << "Couldn't accept: " << strerror(errno) << std::endl;
    }
    
    char buff[1000];
    if( recv(client_fd,buff,1000,0) < 0 ){
        std::cout << "Couldn't recive the data: " << strerror(errno) << std::endl;
    }
    std::cout << buff << std::endl;

    return 0;
}
