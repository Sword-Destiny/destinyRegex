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

#include "c_regex_auto_machine.h"

/*释放空间*/
void free_char_list(struct list_char* list) {
	struct list_char* next;
	while (list) {
		next = list->next;
		free(list);
		list = next;
	}
}

/*释放空间*/
inline void free_single_conditions(struct single_condition* s_con) {
	struct single_condition* next;
	while (s_con) {
		next = s_con->next;
		free_char_list(s_con->match_letters);
		free(s_con);
		s_con = next;
	}
}

/*释放空间*/
void free_conditions(struct condition *con) {
	struct condition* next;
	while (con) {
		next = con->next;
		free_single_conditions(con->single_conditions);
		free(con);
		con = next;
	}
}

/*释放空间*/
void free_match_iterator(struct match_iterator* it) {
	struct match_iterator* next;
	while (it) {
		next = it->next;
		free(it);
		it = next;
	}
}

/*释放空间*/
void free_regex_token_iterator(struct regex_token_iterator* it) {
	struct regex_token_iterator* next;
	while (it) {
		next = it->next;
		free(it);
		it = next;
	}
}

/*释放空间*/
inline void free_regex(struct regex* reg) {
	free_conditions(reg->conditions);
	free_match_iterator(reg->match_strs);
	free_regex_token_iterator(reg->token_strs);
	free(reg);
}

//编译正则表达式
bool compile(struct regex *reg) {
	int len = 0;
	while (reg->str[len] != '\0') {
		len++;
	}
	reg->str_len = len;
	return init(reg, 0, len - 1, -1);
}

//TODO
bool regex_match(const char* str, struct regex *reg);

//TODO
bool regex_search(const char* str, struct regex *reg);

#endif