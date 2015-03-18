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
	struct list_char* l_c = construct_char('a');
	l_c->next = construct_char('b');
	struct single_condition* s_con = construct_s_condition(l_c, 1, 3);

	struct list_char* l_c1 = construct_char('c');
	l_c1->next = construct_char('d');
	s_con->next = construct_s_condition(l_c1, 2, 4);

	struct condition* con = construct_condition(s_con);

	struct list_char* l_c2 = construct_char('e');
	l_c2->next = construct_char('f');
	struct single_condition* s_con1 = construct_s_condition(l_c2, 3, 6);

	struct list_char* l_c3 = construct_char('g');
	l_c3->next = construct_char('h');
	s_con1->next = construct_s_condition(l_c3, 4, 8);

	con->next = construct_condition(s_con1);

	struct regex* reg = construct_regex("[ab]{1,3}[cd]{2,4}");
	compile(reg);
	reg->conditions = con;
	free_regex(reg);
	//}
	system("pause");
	return 0;
#endif
}