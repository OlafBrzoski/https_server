#include "router.h"
#include <string>
#include <fstream>
#include <sstream>


std::string build_response(const HttpRequest& request){
    std::string response = "HTTP/1.1";
    std::string path = "../public";
    std::string error_body = "<html><body><h1>404 - This page does not exist</h1></body></html>";

    if ( request.method == "GET" ){

        if ( request.path == "/" ){
            path += "/index.html";
        }

        else {
            path += request.path;
        }
        std::ifstream file(path);
        if ( !file.is_open() ){
            response += " 404 Not Found\r\n";
            response += "Content-Type: text/html\r\n";
            response += "Content-Length: " + std::to_string(error_body.length()) + "\r\n";
            response += "Connection: close\r\n";
            response += "\r\n";
            response += error_body;
            return response;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string file_content = buffer.str();
        file.close();

        response += " 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Content-Length: " + std::to_string(file_content.length()) + "\r\n";
        response += "Connection: close\r\n";
        response += "\r\n";
        response += file_content;
        return response;

    }
    return "";
}
