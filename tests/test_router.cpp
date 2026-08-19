#include <gtest/gtest.h>
#include "router.h"
#include "http_parser.h"

TEST(RouterTest, Returns400ForEmptyMethod) {
    HttpRequest empty_req = {"", "", "", {}, ""};
    
    std::string response = build_response(empty_req);
    
    EXPECT_NE(response.find("400 Bad Request"), std::string::npos);
}

TEST(RouterTest, Returns404ForMissingFile) {
    HttpRequest missing_req = {"GET", "/plik_ktory_nie_istnieje_12345.html", "HTTP/1.1", {}, ""};
    
    std::string response = build_response(missing_req);
    
    EXPECT_NE(response.find("404 Not Found"), std::string::npos);
}
