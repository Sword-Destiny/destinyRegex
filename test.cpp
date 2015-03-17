#include "headers\regex.h"
#include "headers\string.h"
#include "headers\single_list.h"

using RegularExpression::regex;
using RegularExpression::regex_token;
using RegularExpression::regex_token_iterator;
using RegularExpression::sregex_token_iterator;

void run() {
	regex_token<String> *token = new regex_token<String>("a");
	token->next = new regex_token<String>("b");
	token->next->next = new regex_token<String>("c");
	sregex_token_iterator it;
	it.first = it.current = token;
	sregex_token_iterator end;
	while (it != end) {
		String str = *it++;
		//cout << str << endl;
	}
	//cout << endl;
	sregex_token_iterator temp = it;
	temp.current = temp.first;
	while (temp != end) {
		String str = *temp++;
		//cout << str << endl;
	}
}

void list_run() {
	SingleList<int> list;
	cout << list.insert(-1, 1) << endl;
	for (int i = 0; i < 10; i++) {
		list.insert(i, i);
		list.print();
	}
	list.insert(9, -1);
	list.insert(-1, 100);
	list.insert(1000, 1000);
	list.print();
}

int main() {
	list_run();
	system("pause");
	return 0;
}