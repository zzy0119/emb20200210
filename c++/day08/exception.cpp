#include <iostream>

using namespace std;

/*
 try {
 	// 可能抛出异常
 } catch (exception var) {
 	// 异常处理
 }
 */

class Base {};
class Drived:public Base {};

int main(void)
{
	try {
		throw Drived();// Drived类型的对象
		cout << "this statement will not be excuted" << endl;
	} catch(int) {
		cout << "Exception type: int" << endl;
	} catch(char *) {
		cout << "Excption type: char *" << endl;
	} catch(Base) {
		cout << "Exception type: Base" << endl;
	} catch(Drived) {
		cout << "Exception type: Drived" << endl;
	}

	return 0;
}
