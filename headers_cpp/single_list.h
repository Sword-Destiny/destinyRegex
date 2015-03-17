/*******************************************************
 *	single_list.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):单链表定义
 ******************************************************/
#pragma once
#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include "includes.h"

/*超前声明*/
template<class T> class SingleList;

template<class T>
/*节点类*/
class SingleNode {
public:
	T element;
	SingleNode<T>* next;
	friend class SingleList<T>;
	SingleNode(const SingleNode<T>& s) {}
	SingleNode& operator=(const SingleNode<T>& s) {
		return *this;
	}
public:
	inline SingleNode() :next(NULL) {}
	explicit SingleNode(const T&elem) :element(elem), next(NULL) {}
	~SingleNode() {

	}
};

template<class T>
/*带表尾指针的循环单链表*/
class SingleList {
public:
	int length;
	SingleNode<T> *tail;//尾指针
	SingleList() :length(0), tail(NULL) {}
	~SingleList() {
		if (tail) {
			SingleNode<T> *head_node = tail->next, *p = NULL;
			tail->next = NULL;
			while (head_node != NULL) {
				p = head_node->next;
				delete head_node;
				head_node = p;
			}
		}
	}
	SingleList(const SingleList<T>& s) :length(s.length) {
		if (s.length == 0) {
			this->tail = NULL;
			return;
		}
		SingleNode<T> *head_node = new SingleNode<T>(s.tail->next->element);
		this->tail = head_node;
		SingleNode<T>* p = s.tail->next->next;
		while (p != s.tail->next) {
			this->tail->next = new SingleNode<T>(p->element);
			p = p->next;
			this->tail = this->tail->next;
		}
		this->tail->next = head_node;
	}
	SingleList& operator=(const SingleList<T>& s) {
		if (this == &s) {
			return *this;
		}
		if (tail) {
			SingleNode<T> *head_node = tail->next, *p = NULL;
			tail->next = NULL;
			while (head_node != NULL) {
				p = head_node->next;
				delete head_node;
				head_node = p;
			}
		}
		this->length = s.length;
		if (s.length == 0) {
			this->tail = NULL;
			return *this;
		}
		SingleNode<T> *head_node = new SingleNode<T>(s.tail->next->element);
		this->tail = head_node;
		SingleNode<T>* p = s.tail->next->next;
		while (p != s.tail->next) {
			this->tail->next = new SingleNode<T>(p->element);
			p = p->next;
			this->tail = this->tail->next;
		}
		this->tail->next = head_node;
		return *this;
	}
	/*返回表的长度*/
	inline int get_length()const {
		return this->length;
	}
	/*表是否为空*/
	inline bool is_empty()const {
		return this->tail == NULL;
	}
	/*返回数据在链表中的索引*/
	virtual int index_of(const T& data)const {
		if (!this->tail) {
			return -1;
		}
		SingleNode<T> *p = this->tail->next;
		int i = 0;
		for (;; i++) {
			if (p != this->tail->next&&p->element != data || p == this->tail->next&&i == 0 && p->element != data) {
				p = p->next;
			}
			else {
				break;
			}
		}
		if (p == this->tail->next&&p->element != data) {
			return -1;
		}
		return i;
	}
	/*得到索引index处的数据*/
	T operator[](int index) const {
		SingleNode<T>* p = this->tail;
		for (int j = 0; j <= index; j++) {
			p = p->next;
		}
		return p->element;
	}
	/*得到索引index处的数据*/
	T& operator[](int index) {
		SingleNode<T>* p = this->tail;
		for (int j = 0; j <= index; j++) {
			p = p->next;
		}
		return p->element;
	}
	/*在末尾添加数据*/
	void add_tail(const T &data) {
		this->length++;
		if (this->tail == NULL) {
			this->tail = new SingleNode<T>(data);
			this->tail->next = this->tail;
			return;
		}
		SingleNode<T> *head_node = this->tail->next;
		this->tail->next = new SingleNode<T>(data);
		this->tail = this->tail->next;
		this->tail->next = head_node;
	}
	/*插入数据*/
	bool insert(const int& index, const T& data) {
		if (index < 0) {
			return false;
		}
		if (!this->tail) {
			if (index != 0) {
				return false;
			}
			this->tail = new SingleNode<T>(data);
			this->tail->next = this->tail;
			this->length++;
			return true;
		}
		SingleNode<T> *p = this->tail;
		for (int i = 0; i < index; i++) {
			if (p->next == this->tail) {
				if (index - i == 1) {
					SingleNode<T> *head = this->tail->next;
					this->tail->next = new SingleNode<T>(data);
					this->tail = this->tail->next;
					this->tail->next = head;
					this->length++;
					return true;
				}
				else {
					return false;
				}
			}
			p = p->next;
		}
		SingleNode<T> *q = p->next;
		p->next = new SingleNode<T>(data);
		p->next->next = q;
		this->length++;
		return true;
	}
	/*移除指定元素*/
	bool remove(const T& data) {
		if (!this->tail) {
			return false;
		}
		SingleNode<T> *head_node = this->tail->next;
		SingleNode<T> *head_head_node = this->tail;
		while (head_node != this->tail) {
			if (head_node->element == data) {
				head_head_node->next = head_node->next;
				delete head_node;
				this->length--;
				return true;
			}
			head_head_node = head_node;
			head_node = head_node->next;
		}
		if (head_node->element == data) {
			head_head_node->next = head_node->next;
			delete head_node;
			this->tail = head_head_node;
			this->length--;
			return true;
		}
		return false;
	}
	/*移除所有指定元素*/
	int remove_all(const T& data) {
		int num = 0;
		if (!this->tail) {
			return num;
		}
		SingleNode<T> *head_node = this->tail->next;
		SingleNode<T> *head_head_node = this->tail;
		while (head_node != this->tail) {
			if (head_node->element == data) {
				head_head_node->next = head_node->next;
				delete head_node;
				this->length--;
				num++;
				head_node = head_head_node->next;
			}
			else {
				head_head_node = head_node;
				head_node = head_node->next;
			}
		}
		if (head_node->element == data) {
			head_head_node->next = head_node->next;
			delete head_node;
			this->tail = head_head_node;
			this->length--;
			num++;
		}
		return num;
	}
	/*输出单链表*/
	friend ostream& operator<<(ostream& os, SingleList<T> &list) {
		return list.print(os);
	}
	/*输出单链表*/
	ostream& print(const int& w = 8, const string& sep = " | ", ostream& os = cout)const {
		os << "| ";
		if (!this->tail) {
			os << " |" << endl;
			return os;
		}
		SingleNode<T> *p = this->tail->next;
		for (int i = 0; i < this->length; i++) {
			os << setw(8) << p->element << sep;
			p = p->next;
		}
		os << endl;
		return os;
	}
	/*移除所有元素*/
	void clear() {
		if (this->tail) {
			SingleNode<T> *head_node = this->tail->next, *p = NULL;
			this->tail->next = NULL;
			while (head_node != NULL) {
				p = head_node->next;
				delete head_node;
				head_node = p;
			}
		}
		this->tail = NULL;
		this->length = 0;
	}
};

#endif