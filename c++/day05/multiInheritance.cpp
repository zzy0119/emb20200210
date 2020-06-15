#include <iostream>

using namespace std;

class A{
	protected:
		int m_a;
		int m_b;
	public:
		A(int a, int b);
		~A();
		void show();
};
A::A(int a, int b) : m_a(a), m_b(b) 
{
	cout << "A constructor" << endl;
}

A::~A()
{
	cout << "A destructor" << endl;
}

void A::show()
{
	cout << "m_a:" << m_a << endl;
	cout << "m_b:" << m_b << endl;
}

class B {
	protected:
		int m_c;
		int m_d;
	public:
		B(int c, int d);
		~B();
		void show();
};
B::B(int c, int d):m_c(c), m_d(d)
{
	cout << "B constructor" << endl;
}
B::~B()
{
	cout << "B destructor" << endl;
}

void B::show()
{
	cout << "m_c:" << m_c << endl;
	cout << "m_d:" << m_d << endl;
}
// 多继承
class C : public B, public A {
	private:
		int m_e;
	public:
		C(int a, int b, int c, int d, int e);
		~C();
		void show();
};
C::C(int a, int b, int c, int d, int e):B(c, d), A(a, b), m_e(e)
{
	cout << "C constructor" << endl;
}
C::~C()
{
	cout << "C destructor" << endl;
}

void C::show()
{
	// 父类的方法
	A::show();
	B::show();
	cout << "m_e" << m_e << endl;
}

int main(void)
{
	C obj(1,2,3,4,5);
	obj.show();

	return 0;
}

