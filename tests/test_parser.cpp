#include <gtest/gtest.h>
#include <string>
#include "http_parser.h"

TEST(HttpParserTest, ParsesBasicGetRequest) {
    HttpParser parser;
    std::string raw_request = "GET /test.html HTTP/1.1\r\nHost: localhost\r\n\r\n";

    HttpRequest request = parser.parse(raw_request);

    EXPECT_EQ(request.method, "GET");
    EXPECT_EQ(request.path, "/test.html");
}

TEST(HttpParserTest, HandlesMalformedRequest) {
    HttpParser parser;
    std::string bad_request = "GETHTTP/1.1\r\nHost: localhost\r\n\r\n";

    HttpRequest request = parser.parse(bad_request);

    EXPECT_EQ(request.method, "");
}

TEST(HttpParserTest, IncompleteHeaders) {
    HttpParser parser;
    std::string incomplete_request = "GET /index.html HTTP/1.1\r\nHost: loc";

    HttpRequest request = parser.parse(incomplete_request);

    EXPECT_EQ(request.method, "");
}

TEST(HttpParserTest, ParsesPostMethod) {
    HttpParser parser;
    std::string post_request = "POST /login HTTP/1.1\r\n\r\n";

    HttpRequest request = parser.parse(post_request);

    EXPECT_EQ(request.method, "POST");
    EXPECT_EQ(request.path, "/login");
}
