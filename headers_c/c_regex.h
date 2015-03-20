/*******************************************************
 *	c_regex.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):字符串
 ******************************************************/
#pragma once
 /*C正则表达式*/
#ifndef DESTINY_REGEX
#define DESTINY_REGEX

#include "c_regex_engine.h"

static struct regex_match_iterator* current_match_iterator;
static struct regex_match_iterator* temp_match_iterator;

static struct regex_token_iterator* current_token_iterator;
static struct regex_token_iterator* temp_token_iterator;

/*添加regex_match_iterator*/
void match_it_add_match(char* value) {
	if (current_match_iterator) {
		temp_match_iterator->next = construct_match_iterator(value);
		temp_match_iterator = temp_match_iterator->next;
	}
	else {
		current_match_iterator = construct_match_iterator(value);
		temp_match_iterator = current_match_iterator;
	}
}

/*添加regex_token_iterator*/
void token_it_add_token(char* value) {
	if (current_token_iterator) {
		temp_token_iterator->next = construct_token_iterator(value);
		temp_token_iterator = temp_token_iterator->next;
	}
	else {
		current_token_iterator = construct_token_iterator(value);
		temp_token_iterator = current_token_iterator;
	}
}

//编译正则表达式
bool compile(struct regex *reg) {
	int len = 0;
	while (reg->reg_str[len] != '\0') {
		len++;
	}
	reg->str_len = len;
	reg->match_strs = NULL;
	reg->token_strs = NULL;
	reg->conditions = NULL;
	return init(reg, 0, len - 1, -1);
}

//正则表达式匹配list_char
bool char_list_match(const char* str, int start_index, int end_index, struct list_char* list) {
	for (int i = start_index; i <= end_index; i++) {
		struct list_char* li = list;
		bool b = false;
		while (li) {
			if (li->value == str[i]) {
				b = true;
				break;
			}
			li = li->next;
		}
		if (!b) {
			return false;
		}
	}
	return true;
}

/*正则表达式匹配single_condition*/
bool s_condition_match(const char* str, int start_index, int end_index, struct single_condition* s_con) {
	for (int i = s_con->least_match_time; i <= (int)s_con->max_match_time; i++) {
		if (start_index + i - 1 > end_index) {
			return false;
		}
		if (char_list_match(str, start_index, start_index + i - 1, s_con->match_letters)) {
			if (s_con->next == NULL) {
				if (start_index + i - 1 == end_index) {
					return true;
				}
				continue;
			}
			if (s_condition_match(str, start_index + i, end_index, s_con->next)) {
				return true;
			}
		}
	}
	return false;
}

//正则表达式匹配condition
inline bool condition_match(const char* str, int start_index, int end_index, struct condition* con) {
	return s_condition_match(str, start_index, end_index, con->single_conditions);
}

/*正则表达式分割辅助函数*/
int regex_splite_s(const char* str, struct regex* reg, int start, int end, int max, int least) {
	for (int start_index = start; start_index <= end; start_index++) {
		int least_index = start_index + least - 1;
		int max_index = start_index + max;
		int tail_index = ((end < max_index - 1) ? end : (max_index - 1));
		for (int end_index = tail_index; end_index >= least_index; end_index--) {
			struct condition* con = reg->conditions;
			while (con) {
				if (condition_match(str, start_index, end_index, con)) {
					if (start_index > 0) {
						char* token_str = generate_str(str, start, start_index - 1);
						token_it_add_token(token_str);
					}
					char* match_str = generate_str(str, start_index, end_index);
					match_it_add_match(match_str);
					return regex_splite_s(str, reg, end_index + 1, end, max, least);
				}
				con = con->next;
			}
		}
	}
	return start - 1;
}

//正则表达式切割字符串
bool regex_splite(const char* str, struct regex* reg) {
	if (!reg || strlen(reg->reg_str) < 1) {
		error_str = "正则表达式不能为空!";
		return false;
	}
	if (!compile(reg)) {
		return false;
	}
	current_token_iterator = NULL;
	current_match_iterator = NULL;
	temp_match_iterator = NULL;
	temp_token_iterator = NULL;
	int len = strlen(str);
	int least = get_regex_least_length(reg);
	int max = get_regex_max_length(reg);
	int tail_index = regex_splite_s(str, reg, 0, len - 1, max, least);
	if (tail_index < len - 1) {
		char* s = generate_str(str, tail_index + 1, len - 1);
		token_it_add_token(s);
	}
	reg->match_strs = current_match_iterator;
	reg->token_strs = current_token_iterator;
	return true;
}

//正则表达式匹配
bool regex_match(const char* str, struct regex* reg) {
	if (!reg || strlen(reg->reg_str) < 1) {
		error_str = "正则表达式不能为空!";
		return false;
	}
	if (!compile(reg)) {
		return false;
	}
	struct condition* con = reg->conditions;
	while (con) {
		if (condition_match(str, 0, strlen(str) - 1, con)) {
			return true;
		}
		con = con->next;
	}
	return false;
}

//正则表达式搜寻
bool regex_search(const char* str, struct regex *reg) {
	if (!reg || strlen(reg->reg_str) < 1) {
		error_str = "正则表达式不能为空!";
		return false;
	}
	if (!compile(reg)) {
		return false;
	}
	int len = strlen(str);
	int least = get_regex_least_length(reg);
	//int max = get_regex_max_length(reg);
	for (int start_index = 0; start_index < len; start_index++) {
		int least_index = start_index + least - 1;
		//int max_index = start_index + max;
		for (int end_index = least_index; end_index < len /*&& end_index < max_index*/; end_index++) {
			struct condition* con = reg->conditions;
			while (con) {
				if (condition_match(str, start_index, end_index, con)) {
					char* s = generate_str(str, start_index, end_index);
					reg->match_strs = construct_match_iterator(s);
					return true;
				}
				con = con->next;
			}
		}
	}
	return false;
}

#endif