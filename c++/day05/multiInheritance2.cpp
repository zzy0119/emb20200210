#include <iostream>

using namespace std;

// 多继承很容易出现命名冲突问题
class A{
	protected:
		int m_a;
	public:
		A(int a);
};

A::A(int a)
{
	m_a = a;
}

class B:virtual public A {
	protected:
		int m_b;	
	public:
		B(int a, int b);
		void show();
};

B::B(int a, int b):A(a), m_b(b) {}

void B::show()
{
	cout << m_a << "," << m_b << endl;
}

class C:virtual public A {
	protected:
		int m_c;
	public:
		C(int a, int c);
		void show();
};
C::C(int a, int c) : A(a), m_c(c) {}
void C::show()
{
	cout << m_a << "," << m_c << endl;
}

class D:public B, public C {
	protected:
		int m_d;
	public:
		D(int a, int b, int c, int d);
		void show();
};
D::D(int a, int b, int c, int d):A(a), B(10, b), C(100, c), m_d(d) {}
void D::show()
{
	cout << m_a << "," << m_b << "," << m_c << "," << m_d << endl;
}

int main(void)
{
	B b(1, 2);
	b.show();

	C c(3, 4);
	c.show();

	D d(5,6,7,8);
	d.show();


	return 0;
}

