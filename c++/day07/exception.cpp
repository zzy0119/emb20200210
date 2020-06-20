#include <iostream>
#include <exception>

using namespace std;

int main(void)
{
	string s = "hello world";

	try { // 明确抛出异常 try才能检测到
		char ch = s[40];
		cout << ch << endl;
	} catch(exception e) {
		cout << "out of range" << endl;	
	}
	
	try {
		char ch2 = s.at(40);
		cout << ch2 << endl;
	} catch(exception e) {
		cout << "out of range[2]" << endl;	
	}

	// Throw(抛出异常) --->try(检测异常)--->Catch(捕获异常)

	return 0;
}
