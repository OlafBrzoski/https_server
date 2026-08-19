#pragma once
#include <string>
#include "http_parser.h"


std::string build_response(const HttpRequest& request);
