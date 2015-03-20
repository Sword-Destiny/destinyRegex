#pragma once
#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
#	include "headers_cpp/regex.h"
#	include "headers_cpp/string.h"
#	include "headers_cpp/single_list.h"
using RegularExpression::regex;
using RegularExpression::regex_token;
using RegularExpression::regex_token_iterator;
using RegularExpression::sregex_token_iterator;
#else
#	include "headers_c\c_regex.h"
#endif

#endif