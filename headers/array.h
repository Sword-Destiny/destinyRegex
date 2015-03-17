/*******************************************************
 *	array.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: All rifgts reserved! 保留所有权利！
 *	Description(描述):Array数组类定义
 ******************************************************/
#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include "includes.h"

template<class T>
/*数组*/
class Array {
protected:
	T* a;
public:
	const int length;
	Array() :length(0) {
		this->a = NULL;
	}
	Array(const int &len) :length(len) {
		this->a = new T[len];
	}
	~Array() {
		delete[] this->a;
	}
	Array(const Array<T>& arr) :length(arr.length) {
		this->a = new T[arr.length];
		for (int i = 0; i < arr.length; i++) {
			this->a[i] = arr.a[i];
		}
	}
	Array(const T* arr, int dataSize) :length(dataSize) {
		this->a = new T[dataSize];
		for (int i = 0; i < dataSize; i++) {
			this->a[i] = arr[i];
		}
	}
	/*赋值*/
	Array<T>& operator=(const Array<T>& arr) {
		if (this == &arr) {
			return *this;
		}
		delete[] this->a;
		this->a = new T[arr.length];
		*(const_cast<int*>(&this->length)) = arr.length;
		for (int i = 0; i < arr.length; i++) {
			this->a[i] = arr.a[i];
		}
		return *this;
	}
	inline T& operator[](int index) {
		return this->a[index];
	}
	inline T operator[](int index)const {
		return this->a[index];
	}
	bool set(int index, const T& data) {
		if (index >= 0 && index < length) {
			a[index = data];
			return true;
		}
		return false;
	}
	bool get(int index, T& result)const {
		if (index < 0 || index >= length) {
			return false;
		}
		result = a[index];
		return true;
	}
	/*返回数据data的索引位置*/
	/*有序时有用*/
	int index_of(const T& data) {
		int low = 0;
		int high = this->length;
		int mid = -1;
		while (high >= low) {
			mid = (low + high) / 2;
			if (a[mid] == data) {
				break;
			}
			if (a[mid] < data) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}
		return low <= high ? mid : -1;
	}
	/*返回数据data的索引位置*/
	/*有序时有用*/
	int index_of(const T& data, int low, int high) {
		int mid = -1;
		while (high >= low) {
			mid = (low + high) / 2;
			if (a[mid] == data) {
				break;
			}
			if (a[mid] < data) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}
		return low <= high ? mid : -1;
	}
	/*相等性判断*/
	bool operator==(const Array<T>& arr) const {
		if (this->length != arr.length) {
			return false;
		}
		for (int i = 0; i < this->length; i++) {
			if (this->a[i] != arr.a[i]) {
				return false;
			}
		}
		return true;
	}
	/*不等性判断*/
	inline bool operator!=(const Array<T>& arr) const {
		return !this->operator==(arr);
	}
};
#endif