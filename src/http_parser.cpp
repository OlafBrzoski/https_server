#include "http_parser.h"
#include <string> 
#include <map>

HttpParser::parse(const std::string& raw_request){
    HttpRequest request;

    size_t start = 0;
    size_t end = raw_request.find(" ");
    request.method = raw_request.substr(start,end-start);

    start = end + 1;
    end = raw_request.find(" ",start);
    request.path = raw_request.substr(start,end-start);

    start = end + 1;
    end = raw_request.find("\r\n");
    request.version = raw_request.substr(start,end-start);
    
    //work in progress...

}

HttpParser::headers(const std::string& raw_request, HttpRequest& ans){
    
}
