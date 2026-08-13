#include "http_parser.h"
#include <string> 
#include <map>

HttpRequest HttpParser::parse(const std::string& raw_request){
    HttpRequest request;

    size_t start = 0;
    size_t end = raw_request.find(" ");
    request.method = raw_request.substr(start,end-start);

    start = end + 1;
    end = raw_request.find(" ",start);
    request.path = raw_request.substr(start,end-start);

    start = end + 1;
    end = raw_request.find("\r\n",start);
    request.version = raw_request.substr(start,end-start);
    
    start = end + 2;
    headers(raw_request, request, start, end);
    body(raw_request, request, start, end);

    return request;
}

void HttpParser::headers(const std::string& raw_request, HttpRequest& ans, size_t& start, size_t& end){
    while( true ){
        size_t line_end = raw_request.find("\r\n",start);
        if ( start == line_end ){
                start = line_end + 2;
                break;
            }
            else{
                std::string key;
                std::string value; 
                end = raw_request.find(":",start);
                if (end == std::string::npos || end > line_end) {
                    start = line_end + 2;
                    continue; 
                }
                key = raw_request.substr(start,end-start);
                start = end + 1;
                if (start < raw_request.size() && raw_request[start] == ' ') {
                    start++;
                }
                end = line_end;
                value = raw_request.substr(start,end-start);
                start = end + 2;
                ans.headers[key] = value;

            }
    }   
}

void HttpParser::body(const std::string& raw_request, HttpRequest& ans, size_t& start, size_t& end){
    if( start < raw_request.size() ){
        ans.body = raw_request.substr(start);
    }
}
