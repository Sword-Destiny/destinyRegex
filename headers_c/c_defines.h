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

#ifndef _Bool
#define true 1
#define false 0
#define bool int
#endif

#define OR_CHAR '|'

#include <stdlib.h>
#include <stdio.h>

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

enum auto_machine_ident {
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
};

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

#endif