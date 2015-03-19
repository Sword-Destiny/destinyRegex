/*******************************************************
 *	c_defines.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):字符串
 ******************************************************/
#pragma once
 /*数据结构定义*/
#ifndef C_DESTINY_REGEX
#define C_DESTINY_REGEX

#define NULL 0
#define MAX_INT_VAL 0x7FFFFFFF

#define true 1
#define false 0
#define bool char

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*enum auto_machine_ident {
	left_large_brace = '{',
	right_large_brace = '}',
	left_mid_bracket = '[',
	right_mid_bracket = ']',
	left_bracket = '(',
	right_bracket = ')',
	change_letter = '\\', //双斜线转义
	tab = 't',//需要转义
	return_ = 'r',//需要转义
	new_line = 'n', //需要转义
	blank = ' ',//空格
	comma = ',', //逗号
	dot = '.',//通配符
	multi_match_letter = '*', //多次匹配符
	ques = '?',//0或1个
	plus = '+',//一个或多个
	decimal = 'd',//一个十进制数字,需要转义
	lower_letter = 'l', //一个小写字母,需要转义
	space = 's',//一个空白符（空格符，制表符等）,需要转义
	uper_letter = 'u',//一个大写字母,需要转义
	simple_letter = 'w', //一个字母（a～z或A～Z）或数字（0～9）或下划线（_）,需要转义
	not_decimal = 'D',//除了\d之外的字符,需要转义
	not_lower_letter = 'L', //除了\l之外的字符,需要转义
	not_space = 'S',//除了\s之外的字符,需要转义
	not_uper_letter = 'U',//除了\u之外的字符,需要转义
	not_simple_letter = 'W', //除了\w之外的字符,需要转义
	range_letter = '-' //范围表示符
};*/

/*list for chars*/
struct list_char {
	char value;
	struct list_char *next;
};

/*构造list_char*/
inline struct list_char* construct_char(char c) {
	struct list_char* list = (struct list_char*)malloc(sizeof(struct list_char));
	list->value = c;
	list->next = NULL;
	return list;
}

/*正则表达式单一匹配单元*/
struct single_condition {
	struct list_char* match_letters;
	struct single_condition* next;
	unsigned int least_match_time;//最少匹配次数
	unsigned int max_match_time;//最多匹配次数
};

/*构造single_condition*/
inline struct single_condition* construct_s_condition(struct list_char* list, int l_m_time, int m_m_time) {
	struct single_condition* con = (struct single_condition*)malloc(sizeof(struct single_condition));
	con->match_letters = list;
	con->least_match_time = l_m_time;
	con->max_match_time = m_m_time;
	con->next = NULL;
	return con;
}

/*正则表达式匹配单元*/
struct condition {
	struct single_condition* single_conditions;
	struct condition* next;
};

/*构造condition*/
inline struct condition* construct_condition(struct single_condition* s_con) {
	struct condition* con = (struct condition*)malloc(sizeof(struct condition));
	con->single_conditions = s_con;
	con->next = NULL;
	return con;
}

/*匹配字符串*/
struct match_iterator {
	struct match_iterator* next;
	char* value;
};

/*未匹配字符串，拆分字符串*/
struct regex_token_iterator {
	struct regex_token_iterator* next;
	char* value;
};

/*正则表达式*/
/*匹配之前必须compiler*/
struct regex {
	const char* str;
	int str_len;
	struct condition* conditions;
	struct match_iterator* match_strs;
	struct regex_token_iterator* token_strs;
};

/*构造regex*/
inline struct regex* construct_regex(const char* str) {
	struct regex* reg = (struct regex*)malloc(sizeof(struct regex));
	reg->conditions = NULL;
	reg->str = str;
	reg->str_len = 0;
	reg->match_strs = NULL;
	reg->token_strs = NULL;
	return reg;
}


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
	//free(reg);
}

/*是否包含数字字符*/
bool has_num(const char* str) {
	int index = 0;
	while (str[index] != '\0') {
		if (str[index] >= '0'&&str[index] <= '9') {
			return true;
		}
		index++;
	}
	return false;
}

/*是否是一个数字*/
bool is_num(const char* str) {
	bool has_num_char = false;
	bool has_num = false;
	int index = 0;
	while (str[index] != '\0') {
		if (str[index] >= '0'&&str[index] <= '9') {
			if (has_num) {
				return false;
			}
			has_num_char = true;
		}
		else if (str[index] == ' ') {
			if (has_num_char) {
				has_num = true;
			}
		}
		else {
			return false;
		}
		index++;
	}
	return has_num_char;
}

#endif