#ifdef __cplusplus
#	include "headers_cpp/regex.h"
#	include "headers_cpp/string.h"
#	include "headers_cpp/single_list.h"
using RegularExpression::regex;
using RegularExpression::regex_token;
using RegularExpression::regex_token_iterator;
using RegularExpression::sregex_token_iterator;
#else
#	include "headers_c/c_regex.h"
#endif

int main() {
#ifdef __cplusplus
	string str = "abcd";
	cout << str << endl;
	cout << str.c_str() << endl;
	cout << str.begin() << endl;
	cout << str.end() << endl;
	system("pause");
#else
	//for (int i = 0; i < 10000000; i++) {
	struct regex* reg = construct_regex("[\\?\\.\\(\\{\\t]{1,2}[\\t]{2}");
	if (regex_search("aaa.\t\tbbb", reg)) {
		printf("true!\n");
	}
	else {
		printf("%s\n", error_str);
		error_str = "";
	}
	if (regex_search(".", reg)) {
		printf("true!\n");
	}
	else {
		printf("%s\n", error_str);
		error_str = "";
	}
	//}
	system("pause");
	return 0;
#endif
}