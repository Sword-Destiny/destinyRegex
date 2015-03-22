/*******************************************************
 *	regex.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):正则表达式
 ******************************************************/
#pragma once
#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H
#include "string.h"
#include "regex_defination.h"

namespace RegularExpression {

	class list_char {
	public:
		char value;
		list_char *next;
		inline list_char(const char& c) {
			this->value = c;
			this->next = NULL;
		}
		virtual ~list_char() {
			if (this->next) {
				delete this->next;
			}
		}
	};

	class single_condition {
	public:
		list_char* match_letters;
		single_condition* next;
		unsigned int least_match_time;//最少匹配次数
		unsigned int max_match_time;//最多匹配次数
		inline single_condition(list_char* match_ls, unsigned int l_m_time, unsigned m_m_time) {
			this->least_match_time = l_m_time;
			this->max_match_time = m_m_time;
			this->match_letters = match_ls;
			this->next = NULL;
		}
		virtual ~single_condition() {
			if (this->match_letters) {
				delete this->match_letters;
			}
			if (this->next) {
				delete this->next;
			}
		}
	};

	class condition {
	public:
		single_condition* single_conditions;
		condition* next;
		inline condition(single_condition* s_con) {
			this->single_conditions = s_con;
			this->next = NULL;
		}
		virtual ~condition() {
			if (this->single_conditions) {
				delete this->single_conditions;
			}
			if (this->next) {
				delete this->next;
			}
		}
	};

	static condition* current_condition;
	static condition* temp_condition;

	static single_condition* current_s_condition;
	static single_condition* temp_s_condition;

	static list_char* current_char_list;
	static list_char* temp_list_char;

	static int temp_index = 0;
	static bool is_mid_bracket_close = true;

	static int temp_least_num = 0;
	static int temp_max_num = 0;

	const char* error_str = "";

	/*添加list_char*/
	void char_list_add_char(char c) {
		if (!current_char_list) {
			current_char_list = new list_char(c);
			temp_list_char = current_char_list;
		}
		else {
			temp_list_char->next = new list_char(c);
			temp_list_char = temp_list_char->next;
		}
	}

	/*添加Single_condition*/
	void s_condition_add_s_condition(list_char* list) {
		if (!current_s_condition) {
			current_s_condition = new single_condition(list, temp_least_num, temp_max_num);
			temp_s_condition = current_s_condition;
		}
		else {
			temp_s_condition->next = new single_condition(list, temp_least_num, temp_max_num);
			temp_s_condition = temp_s_condition->next;
		}
	}

	/*添加condition*/
	void condition_add_condition(single_condition* s_con) {
		if (!current_condition) {
			current_condition = new condition(s_con);
			temp_condition = current_condition;
		}
		else {
			temp_condition->next = new condition(s_con);
			temp_condition = temp_condition->next;
		}
	}

	/*list_char添加连续字符*/
	void char_list_add_many_char(char start, char end) {
		if (!current_char_list) {
			current_char_list = new list_char(start);
			temp_list_char = current_char_list;
		}
		else {
			temp_list_char->next = new list_char(start);
			temp_list_char = temp_list_char->next;
		}
		if (end >= 127) {
			end = 126;
		}
		for (char t = start + 1; t <= end; t++) {
			temp_list_char->next = new list_char(t);
			temp_list_char = temp_list_char->next;
		}
	}

	/*释放空间*/
	void free_current() {
		if (current_char_list) {
			delete current_char_list;
		}
		if (current_s_condition) {
			delete current_s_condition;
		}
		if (current_condition) {
			delete current_condition;
		}
	}

	/*正则表达式类*/
	class regex {
	public:
		string reg_str;
		condition* conditions;

		inline regex() :reg_str("") {}
		inline regex(const char* str):reg_str(str) {
			if (!this->compile()) {
				throw exception(error_str);
			}
		}
		inline regex(const string& str) : reg_str(str) {
			if (!this->compile()) {
				throw exception(error_str);
			}
		}
		inline regex(const std::string& str) : reg_str(str) {
			if (!this->compile()) {
				throw exception(error_str);
			}
		}
		inline virtual ~regex() {
			if (this->conditions) {
				delete this->conditions;
			}
		}
	private:
		regex(const regex& r){}
		regex& operator=(const regex& r) {
			return *this;
		}
	public:
		/*编译*/
		bool compile() {
			this->conditions = NULL;
			return init(0, this->reg_str.size() - 1);
		}

		/*得到匹配数量*/
		bool get_match_num(int begin, int end) {
			if (begin > end || reg_str[begin] != LEFT_LARGE_BRACE) {
				if (reg_str[begin] == PLUS) {
					temp_index = begin;
					temp_least_num = 1;
					temp_max_num = MAX_INT_VAL;
					return true;
				}
				if (reg_str[begin] == MULTI_MATCH_LETTER) {
					temp_index = begin;
					temp_least_num = 0;
					temp_max_num = MAX_INT_VAL;
					return true;
				}
				temp_least_num = 1;
				temp_max_num = 1;
				temp_index = begin - 1;
				return true;
			}
			char* buffer = new char[11];
			int temp_num = 0;
			int comma_num = 0;
			for (int i = begin + 1; i <= end; i++) {
				if (reg_str[i] == BLANK || reg_str[i] >= '0'&&reg_str[i] <= '9') {
					if (temp_num > 9) {
						error_str = "匹配次数的数字太大!";
						delete[] buffer;
						return false;
					}
					buffer[temp_num] = reg_str[i];
					temp_num++;
				}
				else if (reg_str[i] == COMMA) {
					if (comma_num > 0) {
						error_str = "匹配次数语法错误!";
						delete[] buffer;
						return false;
					}
					buffer[temp_num] = '\0';
					comma_num++;
					if (is_num(buffer)) {
						temp_least_num = atoi(buffer);
						temp_num = 0;
					}
					else {
						error_str = "匹配次数语法错误!";
						delete[] buffer;
						return false;
					}
				}
				else if (reg_str[i] == RIGHT_LARGE_BRACE) {
					if (comma_num > 0) {
						buffer[temp_num] = '\0';
						if (is_num(buffer)) {
							temp_max_num = atoi(buffer);
							if (temp_least_num > temp_max_num) {
								error_str = "最小匹配次数不能大于最大匹配次数!";
								delete[] buffer;
								return false;
							}
						}
						else {
							if (has_num(buffer)) {
								error_str = "匹配次数语法错误!";
								delete[] buffer;
								return false;
							}
							else {
								temp_max_num = MAX_INT_VAL;
							}
						}
					}
					else {
						buffer[temp_num] = '\0';
						if (is_num(buffer)) {
							temp_least_num = atoi(buffer);
							temp_max_num = temp_least_num;
						}
						else {
							error_str = "匹配次数语法错误!";
							delete[] buffer;
							return false;
						}
					}
					temp_index = i;
					delete[] buffer;
					return true;
				}
				else {
					error_str = "计算匹配次数时出现了意外的字符";
					delete[] buffer;
					return false;
				}
			}
			error_str = "左大括号{和右大括号}不匹配!";
			delete[] buffer;
			return false;
		}

		/*转义字符处理*/
		bool change_letter(int begin, int end) {
			if (begin > end) {
				return false;
			}
			switch (reg_str[begin]) {
				case CHANGE_LETTER:
					char_list_add_char(CHANGE_LETTER);
					return true;
				case TAB:
					char_list_add_char('\t');
					return true;
				case RETURN_:
					char_list_add_char('\r');
					return true;
				case NEW_LINE:
					char_list_add_char('\n');
					return true;
				case TAB_V:
					char_list_add_char('\v');
					return true;
				case NEW_PAGE:
					char_list_add_char('\f');
					return true;
				case LEFT_BRACKET:
					char_list_add_char(LEFT_BRACKET);
					return true;
				case RIGHT_BRACKET:
					char_list_add_char(RIGHT_BRACKET);
					return true;
				case LEFT_LARGE_BRACE:
					char_list_add_char(LEFT_LARGE_BRACE);
					return true;
				case RIGHT_LARGE_BRACE:
					char_list_add_char(RIGHT_LARGE_BRACE);
					return true;
				case LEFT_MID_BRACKET:
					char_list_add_char(LEFT_MID_BRACKET);
					return true;
				case RIGHT_MID_BRACKET:
					char_list_add_char(RIGHT_MID_BRACKET);
					return true;
				case BLANK:
					char_list_add_char(BLANK);
					return true;
				case COMMA:
					char_list_add_char(COMMA);
					return true;
				case DOT:
					char_list_add_char(DOT);
					return true;
				case MULTI_MATCH_LETTER:
					char_list_add_char(MULTI_MATCH_LETTER);
					return true;
				case QUES:
					char_list_add_char(QUES);
					return true;
				case PLUS:
					char_list_add_char(PLUS);
					return true;
				case DECIMAL:
					char_list_add_many_char('0', '9');
					return true;
				case LOWER_LETTER:
					char_list_add_many_char('a', 'z');
					return true;
				case SPACE:
					char_list_add_char(BLANK);
					char_list_add_char('\t');
					char_list_add_char('\r');
					char_list_add_char('\n');
					char_list_add_char('\v');
					char_list_add_char('\f');
					return true;
				case UPER_LETTER:
					char_list_add_many_char('A', 'Z');
					return true;
				case SIMPLE_LETTER:
					char_list_add_many_char('0', '9');
					char_list_add_many_char('a', 'z');
					char_list_add_many_char('A', 'Z');
					char_list_add_char('_');
					return true;
				case NOT_DECIMAL:
					char_list_add_many_char(-128, '0' - 1);
					char_list_add_many_char('9' + 1, 126);
					char_list_add_char(127);
					return true;
				case NOT_LOWER_LETTER:
					char_list_add_many_char(-128, 'a' - 1);
					char_list_add_many_char('z' + 1, 126);
					char_list_add_char(127);
					return true;
				case NOT_SPACE:
					char_list_add_many_char(-128, 8);
					char_list_add_many_char(14, 31);
					char_list_add_many_char(33, 126);
					char_list_add_char(127);
					return true;
				case NOT_UPER_LETTER:
					char_list_add_many_char(-128, 'A' - 1);
					char_list_add_many_char('Z' + 1, 126);
					char_list_add_char(127);
					return true;
				case NOT_SIMPLE_LETTER:
					char_list_add_many_char(-128, '0' - 1);
					char_list_add_many_char('9' + 1, 'A' - 1);
					char_list_add_many_char('Z' + 1, '_' - 1);
					char_list_add_char(96);
					char_list_add_many_char('z' + 1, 126);
					char_list_add_char(127);
					return true;
				case RANGE_LETTER:
					char_list_add_char(RANGE_LETTER);
					return true;
				default:
					error_str = "错误的转义字符!";
					return false;
			}
		}

		/*字符范围符-的处理*/
		bool range(int begin, int end) {
			if (begin > end) {
				return false;
			}
			char end_char = reg_str[begin];
			if (current_char_list) {
				if (temp_list_char->value < end_char) {
					if (end_char == 127) {
						char_list_add_many_char(temp_list_char->value + 1, 126);
						char_list_add_char(127);
					}
					else {
						char_list_add_many_char(temp_list_char->value + 1, end_char);
					}
				}
				else {
					error_str = "非法的范围(-左部字符必须小于-右部字符)!";
					return false;
				}
			}
			else {
				char_list_add_char(RANGE_LETTER);
			}
			return true;
		}

		/*分析中括号中的内容*/
		bool left_mid_bracket(int begin, int end) {
			for (int i = begin; i <= end; i++) {
				switch (reg_str[i]) {
					case LEFT_BRACKET:
					case RIGHT_BRACKET:
						error_str = "中括号[]中不允许嵌套小括号()!";
						return false;
					case LEFT_LARGE_BRACE:
					case RIGHT_LARGE_BRACE:
						error_str = "中括号[]中不允许嵌套大括号{}!";
						return false;
					case LEFT_MID_BRACKET:
						error_str = "中括号[]不允许嵌套!";
						return false;
					case RIGHT_MID_BRACKET:
						if (current_char_list) {
							is_mid_bracket_close = true;
							temp_index = i;
							return true;
						}
						else {
							error_str = "中括号[]中不能为空!";
							return false;
						}
						break;
					case CHANGE_LETTER:
						if (!change_letter(i + 1, end)) {
							return false;
						}
						else {
							i++;
						}
						break;
					case RANGE_LETTER:
						if (!range(i + 1, end)) {
							return false;
						}
						break;
					default:
						char_list_add_char(reg_str[i]);
						break;
				}
			}
			error_str = "左中括号[未找到匹配的右中括号]!";
			return false;
		}

		/*初始状态*/
		/*NOTICE:不使用type参数*/
		bool init(int begin, int end) {
			current_condition = NULL;
			temp_condition = NULL;
			current_s_condition = NULL;
			temp_s_condition = NULL;
			current_char_list = NULL;
			temp_list_char = NULL;
			for (int i = begin; i <= end; i++) {
				switch (reg_str[i]) {
					case LEFT_LARGE_BRACE:
						error_str = "左大括号{不能直接出现!";
						free_current();
						return false;
					case RIGHT_LARGE_BRACE:
						error_str = "右大括号}找不到匹配的左大括号!";
						free_current();
						return false;
					case LEFT_BRACKET:
					case RIGHT_BRACKET:
						//NOTICE
						error_str = "暂时不支持使用小括号()分段匹配";
						free_current();
						return false;
					case OR_CHAR:
						if (!current_s_condition) {
							error_str = "|的使用不正确!";
							free_current();
							return false;
						}
						condition_add_condition(current_s_condition);
						current_s_condition = NULL;
						temp_s_condition = NULL;
						break;
					case PLUS:
						error_str = "加号+不能单独出现!";
						free_current();
						return false;
					case MULTI_MATCH_LETTER:
						error_str = "星号*不能单独出现!";
						free_current();
						return false;
					case LEFT_MID_BRACKET:
						if (is_mid_bracket_close) {
							if (!left_mid_bracket(i + 1, end)) {
								free_current();
								return false;
							}
							else {
								i = temp_index;
								if (get_match_num(i + 1, end)) {
									s_condition_add_s_condition(current_char_list);
									i = temp_index;
									current_char_list = NULL;
									temp_list_char = NULL;
								}
								else {
									free_current();
									return false;
								}
							}
						}
						else {
							error_str = "中括号[]不允许嵌套!";
							free_current();
							return false;
						}
						break;
					case RIGHT_MID_BRACKET:
						error_str = "右中括号找不到匹配的左中括号!";
						free_current();
						return false;
					case CHANGE_LETTER:
						if (!change_letter(i + 1, end)) {
							free_current();
							return false;
						}
						else {
							i++;
							if (get_match_num(i + 1, end)) {
								s_condition_add_s_condition(current_char_list);
								i = temp_index;
								current_char_list = NULL;
								temp_list_char = NULL;
							}
							else {
								free_current();
								return false;
							}
						}
						break;
					case QUES:
						char_list_add_many_char(-128, 126);
						char_list_add_char(127);
						temp_least_num = 1;
						temp_max_num = 1;
						s_condition_add_s_condition(current_char_list);
						current_char_list = NULL;
						temp_list_char = NULL;
						break;
					case DOT:
						char_list_add_many_char(-128, 126);
						char_list_add_char(127);
						if (get_match_num(i + 1, end)) {
							s_condition_add_s_condition(current_char_list);
							i = temp_index;
							current_char_list = NULL;
							temp_list_char = NULL;
						}
						else {
							free_current();
							return false;
						}
						break;
					default:
						char_list_add_char(reg_str[i]);
						if (get_match_num(i + 1, end)) {
							s_condition_add_s_condition(current_char_list);
							i = temp_index;
							current_char_list = NULL;
							temp_list_char = NULL;
						}
						else {
							free_current();
							return false;
						}
						break;
				}
			}
			if (current_s_condition) {
				condition_add_condition(current_s_condition);
				current_s_condition = NULL;
				temp_s_condition = NULL;
			}
			if (!current_condition) {
				error_str = "正则表达式不能为空!";
				free_current();
				return false;
			}
			conditions = current_condition;
			current_condition = NULL;
			return true;
		}

		/*得到正则表达式最短匹配长度*/
		int get_regex_least_length()const {
			int least_len = MAX_INT_VAL;
			int len;
			condition* con = this->conditions;
			while (con) {
				len = 0;
				single_condition* s_con = con->single_conditions;
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
		int get_regex_max_length()const {
			int max_len = 0;
			int len;
			condition* con = this->conditions;
			while (con) {
				len = 0;
				single_condition* s_con = con->single_conditions;
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

	};

	template<class T>
	/*正则表达式包装类*/
	class regex_token {
	public:
		T match_str;
		regex_token<T>* next;
		inline regex_token() :next(NULL) {}
		inline regex_token(const string& str) : match_str(str), next(NULL) {}
		inline virtual ~regex_token() {}
	public:
		inline T operator*()const {
			return this->match_str;
		}
	};

	template<class T>
	/*正则表达式迭代类*/
	class regex_token_iterator {
	public:

		regex_token<T> *first;
		regex_token<T> *current;

		regex_token_iterator() :first(NULL), current(NULL) {}

		regex_token_iterator(const regex_token_iterator<T> &it) {
			if (!it.first) {
				this->first = NULL;
				this->current = NULL;
				return;
			}
			regex_token<T> *head_node = new regex_token<T>(it.first->match_str);
			this->first = head_node;
			if (it.current == NULL) {
				this->current = NULL;
			}
			if (it.current == it.first) {
				this->current = this->first;
			}
			regex_token<T> *p = it.first->next;
			while (p != NULL) {
				head_node->next = new regex_token<T>(p->match_str);
				if (it.current == p) {
					this->current = head_node->next;
				}
				p = p->next;
				head_node = head_node->next;
			}
		}

		regex_token_iterator(const char* begin, const char* end, const regex &r, const int& type = -1) {
			this->first = NULL;
			this->current = NULL;
			if (begin > end) {
				if (!regex_splite("", r)) {
					throw exception(error_str);
				}
				return;
			}
			const char* start = begin;
			int size = 0;
			while (start != end) {
				size++;
				start++;
			}
			size++;
			string str(begin, size);
			if (!regex_splite(str, r)) {
				throw exception(error_str);
			}
		}
	private:
		/*添加字符串*/
		void token_it_add_token(const string& s) {
			if (!this->first) {
				this->first = new regex_token<T>(s);
				this->current = this->first;
			}
			else {
				this->current->next = new regex_token<T>(s);
				this->current = this->current->next;
			}
		}
	public:
		/*正则表达式分割*/
		bool regex_splite(const string& str, const regex& reg);
	private:
		/*正则表达式分割辅助函数*/
		int regex_splite_s(const string& str, const regex& reg, int start, int end, int max, int least);
	public:
		regex_token_iterator& operator=(const regex_token_iterator<T> &it) {
			if (this == &it) {
				return *this;
			}
			if (this->first) {
				regex_token<T> *head_node = this->first, *p = NULL;
				while (head_node != NULL) {
					p = head_node->next;
					delete head_node;
					head_node = p;
				}
			}
			if (!it.first) {
				this->first = NULL;
				this->current = NULL;
				return *this;
			}
			regex_token<T> *head_node = new regex_token<T>(it.first->match_str);
			this->first = head_node;
			if (it.current == NULL) {
				this->current = NULL;
			}
			if (it.current == it.first) {
				this->current = this->first;
			}
			regex_token<T> *p = it.first->next;
			while (p != NULL) {
				head_node->next = new regex_token<T>(p->match_str);
				if (it.current == p) {
					this->current = head_node->next;
				}
				p = p->next;
				head_node = head_node->next;
			}
			return *this;
		}

	public:
		inline regex_token_iterator<T> operator++(int) {
			regex_token_iterator<T> temp(*this);
			this->current = this->current->next;
			return temp;
		}
		inline regex_token_iterator<T>& operator++() {
			this->current = this->current->next;
			return *this;
		}
		inline T operator*()const {
			return **this->current;
		}
		inline bool operator==(const regex_token_iterator<T>& it)const {
			return it.current == this->current;
		}
		inline bool operator!=(const regex_token_iterator<T>& it)const {
			return it.current != this->current;
		}
	public:

		virtual ~regex_token_iterator() {
			if (this->first) {
				regex_token<T> *head_node = this->first, *p = NULL;
				while (head_node != NULL) {
					p = head_node->next;
					delete head_node;
					head_node = p;
				}
				this->first = NULL;
			}
		}
	};

	typedef regex_token_iterator<string> sregex_token_iterator;

	//正则表达式匹配list_char
	bool char_list_match(const string& str, int start_index, int end_index, list_char* list) {
		for (int i = start_index; i <= end_index; i++) {
			list_char* li = list;
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
	bool s_condition_match(const string& str, int start_index, int end_index, single_condition* s_con) {
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
	inline bool condition_match(const string& str, int start_index, int end_index, condition* con) {
		return s_condition_match(str, start_index, end_index, con->single_conditions);
	}

	//正则表达式匹配
	bool regex_match(const string& str, regex &reg) {
		if (reg.reg_str.size() < 1) {
			error_str = "正则表达式不能为空!";
			return false;
		}
		condition* con = reg.conditions;
		while (con) {
			if (condition_match(str, 0, str.size() - 1, con)) {
				return true;
			}
			con = con->next;
		}
		return false;
	}

	//正则表达式搜寻
	bool regex_search(const string& str, regex &reg) {
		if (reg.reg_str.size() < 1) {
			error_str = "正则表达式不能为空!";
			return false;
		}
		int len = str.size();
		int least = reg.get_regex_least_length();
		for (int start_index = 0; start_index < len; start_index++) {
			int least_index = start_index + least - 1;
			for (int end_index = least_index; end_index < len; end_index++) {
				condition* con = reg.conditions;
				while (con) {
					if (condition_match(str, start_index, end_index, con)) {
						//string s = str.sub_str(start_index, end_index - start_index + 1);
						return true;
					}
					con = con->next;
				}
			}
		}
		return false;
	}

	template<class T>
	//正则表达式切割字符串
	bool regex_token_iterator<T>::regex_splite(const string& str, const regex &reg) {
		if (reg.reg_str.size() < 1) {
			error_str = "正则表达式不能为空!";
			return false;
		}
		int len = str.size();
		int least = reg.get_regex_least_length();
		int max = reg.get_regex_max_length();
		int tail_index = regex_splite_s(str, reg, 0, len - 1, max, least);
		if (tail_index < len - 1) {
			string s = str.sub_str(tail_index + 1, len - tail_index - 1);
			token_it_add_token(s);
		}
		this->current = this->first;
		return true;
	}

	template<class T>
	/*正则表达式分割辅助函数*/
	int regex_token_iterator<T>::regex_splite_s(const string& str, const regex& reg, int start, int end, int max, int least) {
		for (int start_index = start; start_index <= end; start_index++) {
			int least_index = start_index + least - 1;
			int max_index = start_index + max;
			int tail_index = ((end < max_index - 1) ? end : (max_index - 1));
			for (int end_index = tail_index; end_index >= least_index; end_index--) {
				condition* con = reg.conditions;
				while (con) {
					if (condition_match(str, start_index, end_index, con)) {
						if (start_index > 0) {
							string token_str = str.sub_str(start, start_index - start);
							token_it_add_token(token_str);
						}
						//string match_str = str.sub_str(start_index, end_index - start_index + 1);
						//match_it_add_match(match_str);
						return regex_splite_s(str, reg, end_index + 1, end, max, least);
					}
					con = con->next;
				}
			}
		}
		return start - 1;
	}
}

#endif
