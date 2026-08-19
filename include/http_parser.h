#pragma once
#include <string>
#include <map>

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};

class HttpParser{
    public:
        HttpRequest parse(const std::string& raw_request);
    private:
        void headers (const std::string& raw_request, HttpRequest& ans, size_t& start, size_t& end, bool& fault);
        void body (const std::string& raw_request, HttpRequest& ans, size_t& start);
};
