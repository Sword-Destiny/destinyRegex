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
#define MAX_INT_VAL 0x3FFFFFFF

#define true 1
#define false 0
#define bool char

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OR_CHAR '|'
#define LEFT_LARGE_BRACE '{'
#define RIGHT_LARGE_BRACE '}'
#define LEFT_MID_BRACKET '['
#define RIGHT_MID_BRACKET ']'
#define LEFT_BRACKET '('
#define RIGHT_BRACKET ')'
#define CHANGE_LETTER '\\' //双斜线转义
#define TAB 't' //需要转义
#define RETURN_ 'r' //需要转义
#define NEW_LINE 'n' //需要转义
#define NEW_PAGE 'f' //需要转义
#define TAB_V 'v' //需要转义
#define BLANK ' ' //空格
#define COMMA ',' //逗号
#define DOT '.' //通配符
#define MULTI_MATCH_LETTER '*' //多次匹配符
#define QUES '?' //0或1个
#define PLUS '+' //一个或多个
#define DECIMAL 'd' //一个十进制数字,需要转义
#define LOWER_LETTER 'l' //一个小写字母,需要转义
#define SPACE 's' //一个空白符（空格符，制表符等）,需要转义
#define UPER_LETTER 'u'//一个大写字母,需要转义
#define SIMPLE_LETTER 'w' //一个字母（a～z或A～Z）或数字（0～9）或下划线（_）,需要转义
#define NOT_DECIMAL 'D' //除了\d之外的字符,需要转义
#define NOT_LOWER_LETTER 'L' //除了\l之外的字符,需要转义
#define NOT_SPACE 'S' //除了\s之外的字符,需要转义
#define NOT_UPER_LETTER 'U' //除了\u之外的字符,需要转义
#define NOT_SIMPLE_LETTER 'W' //除了\w之外的字符,需要转义
#define RANGE_LETTER '-' //范围表示符

char* error_str = "";//错误信息

/*匹配字符可选列表*/
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
struct regex_match_iterator {
	struct regex_match_iterator* next;
	char* value;
};

/*构造regex_match_iterator*/
inline struct regex_match_iterator* construct_match_iterator(char* val) {
	struct regex_match_iterator* it = (struct regex_match_iterator*)malloc(sizeof(struct regex_match_iterator));
	it->next = NULL;
	it->value = val;
	return it;
}

/*未匹配字符串，拆分字符串*/
struct regex_token_iterator {
	struct regex_token_iterator* next;
	char* value;
};

/*构造regex_token_iterator*/
inline struct regex_token_iterator* construct_token_iterator(char* val) {
	struct regex_token_iterator* it = (struct regex_token_iterator*)malloc(sizeof(struct regex_token_iterator));
	it->next = NULL;
	it->value = val;
	return it;
}

/*正则表达式*/
/*匹配之前必须compiler*/
struct regex {
	const char* reg_str;
	int str_len;
	struct condition* conditions;
	struct regex_match_iterator* match_strs;
	struct regex_token_iterator* token_strs;
};

/*构造regex*/
inline struct regex* construct_regex(const char* str) {
	struct regex* reg = (struct regex*)malloc(sizeof(struct regex));
	reg->conditions = NULL;
	reg->reg_str = str;
	reg->str_len = 0;
	reg->match_strs = NULL;
	reg->token_strs = NULL;
	return reg;
}


/*释放list_char空间*/
void free_char_list(struct list_char* list) {
	struct list_char* next;
	while (list) {
		next = list->next;
		free(list);
		list = next;
	}
}

/*释放single_condition空间*/
inline void free_single_conditions(struct single_condition* s_con) {
	struct single_condition* next;
	while (s_con) {
		next = s_con->next;
		free_char_list(s_con->match_letters);
		free(s_con);
		s_con = next;
	}
}

/*释放condition空间*/
void free_conditions(struct condition *con) {
	struct condition* next;
	while (con) {
		next = con->next;
		free_single_conditions(con->single_conditions);
		free(con);
		con = next;
	}
}

/*释放regex_match_iterator空间*/
void free_match_iterator(struct regex_match_iterator* it) {
	struct regex_match_iterator* next;
	while (it) {
		next = it->next;
		free(it->value);
		free(it);
		it = next;
	}
}

/*释放regex_token_iterator空间*/
void free_regex_token_iterator(struct regex_token_iterator* it) {
	struct regex_token_iterator* next;
	while (it) {
		next = it->next;
		free(it->value);
		free(it);
		it = next;
	}
}

/*释放regex空间*/
inline void free_regex(struct regex* reg) {
	free_conditions(reg->conditions);
	free_match_iterator(reg->match_strs);
	free_regex_token_iterator(reg->token_strs);
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


/*得到正则表达式最短匹配长度*/
int get_regex_least_length(struct regex* reg) {
	int least_len = MAX_INT_VAL;
	int len;
	struct condition* con = reg->conditions;
	while (con) {
		len = 0;
		struct single_condition* s_con = con->single_conditions;
		while (s_con) {
			len += s_con->least_match_time;
			s_con = s_con->next;
		}
		if (len < least_len) {
			least_len = len;
		}
		con = con->next;
	}
	return least_len;
}

/*得到正则表达式最长匹配长度*/
int get_regex_max_length(struct regex* reg) {
	int max_len = 0;
	int len;
	struct condition* con = reg->conditions;
	while (con) {
		len = 0;
		struct single_condition* s_con = con->single_conditions;
		while (s_con) {
			if (len < MAX_INT_VAL) {
				len += s_con->max_match_time;
			}
			s_con = s_con->next;
		}
		if (len > max_len) {
			max_len = len;
		}
		con = con->next;
	}
	return max_len;
}

/*构造字符串*/
char* generate_str(const char* str, int start, int end) {
	char* s = (char*)malloc((end - start + 2)*sizeof(char));
	int j = 0;
	for (int i = start; i <= end; i++) {
		s[j] = str[i];
		j++;
	}
	s[j] = '\0';
	return s;
}
#endif