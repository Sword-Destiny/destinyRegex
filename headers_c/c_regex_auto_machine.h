/*******************************************************
 *	c_regex_auto_machine.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):字符串
 ******************************************************/
#pragma once
/*自动机*/
#ifndef C_REGEX_AUTO_MACHINE
#define C_REGEX_AUTO_MACHINE
#include "c_defines.h"

/*自动机初始状态*/
/*NOTICE:不使用type参数*/
bool init(struct regex* reg, int begin, int end, int type/*不使用此参数*/) {
	for (int i = begin; i <= end; i++) {
		//TODO
		switch (reg->str[i]) {
			case '\0':
				return true;
			default:
				break;
		}
	}
	return true;
}

#endif