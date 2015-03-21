#pragma once
#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
#	include "headers_cpp/regex.h"
#	include "headers_cpp/string.h"
using RegularExpression::error_str;
using RegularExpression::regex;
using RegularExpression::regex_token_iterator;
using RegularExpression::sregex_token_iterator;
//using RegularExpression::string;
using RegularExpression::regex_match;
using RegularExpression::regex_search;
#else
#	include "headers_c\c_regex.h"
#endif

#endif