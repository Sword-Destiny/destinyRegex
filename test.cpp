/*******************************************************
 *	test.cpp
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请查看LICENSE文件
 *	Description(描述):测试
 ******************************************************/
#include "header.h"
using std::string;

//测试正则表达式分割字符串
void test_token_cpp() {
	RegularExpression::string str = "abcdabcdacbd";
	try {
		regex reg("[ab]{1,2}");
		sregex_token_iterator it(str.begin(), str.end(), reg, -1);
		sregex_token_iterator end;
		while (it != end) {
			cout << *it << endl;
			it++;
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}

//测试正则表达式匹配
void test_match_cpp() {
	string str = "abcdabcdacbd";
	try {
		regex reg("abcd");
		if (regex_match(str, reg)) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}

//测试正则表达式搜索
void test_search_cpp() {
	string str = "abcdabcdacbd";
	try {
		regex reg("abcd");
		if (regex_search(str, reg)) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}

int main() {
	test_token_cpp();
	test_match_cpp();
	test_search_cpp();
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
