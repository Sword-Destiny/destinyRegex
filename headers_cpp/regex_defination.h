/*******************************************************
 *	regex_defination.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):正则表达式定义
 ******************************************************/
#ifndef REGEX_ENGINE_H
#define REGEX_ENGINE_H

#define MAX_INT_VAL 0x3FFFFFFF

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
