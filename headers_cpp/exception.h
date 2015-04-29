/*******************************************************
 *	exception.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):字符串
 ******************************************************/
#pragma once
#ifndef DESTINY_EXCEPTION_H
#define DESTINY_EXCEPTION_H

namespace RegularExpression {
	class exception {
	private:
		const char* str;
	public:
		explicit exception(const char* s) :str(s) {}
		virtual ~exception(){}
		inline const char* what() {
			return this->str;
		}
	};
}

#endif