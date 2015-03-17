/*******************************************************
 *	regex.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: All rifgts reserved! 保留所有权利！
 *	Description(描述):正则表达式定义
 ******************************************************/
#pragma once
#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H
#include "string.h"

namespace RegularExpression {

	/*正则表达式类*/
	class regex {
	public:
		String pattern;
		inline regex(const String& str) :pattern(str) {}
		inline regex(const string& str) : pattern(str) {}
		inline virtual ~regex() {}
	};

	template<class T>
	/*正则表达式包装类*/
	class regex_token {
	public:
		T match_str;
		regex_token<T>* next;
		inline regex_token() :next(NULL) {}
		inline regex_token(const String& str) : match_str(str), next(NULL) {}
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

		//TODO
		regex_token_iterator(const int& begin, const int& end, const regex &r, const int& type = -1) {

		}

		regex_token_iterator& operator==(const regex_token_iterator<T> &it) {
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

	typedef regex_token_iterator<String> sregex_token_iterator;


	//TODO
	bool regex_match(const String& str, regex reg);
	//TODO
	bool regex_search(const String& str, regex reg);

}

#endif