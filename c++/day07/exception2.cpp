#include <iostream>
#include <exception>

using namespace std;

void func()
{
	throw "unkown Exception";
	cout << "this is a test" << endl;
}

int main(void)
{
	try {
		func();
	} catch (const char *e) {
		cout << e << endl;
	}

	return 0;
}

