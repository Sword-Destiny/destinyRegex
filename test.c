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
	struct regex reg;
	reg.str = "[a-zA-Z]{2,3}";
	compile(&reg);
	free_regex(&reg);
	system("pause");
	return 0;
#endif
}