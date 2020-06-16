#include <iostream>

using namespace std;

// 复数类
class Complex {
	public:
		Complex();
		Complex(double real, double imag);
		// 声明运算符重载 // - == !=
		Complex operator+(const Complex &A) const;
		void display() const;
	private:
		double m_real;
		double m_imag;
};

Complex::Complex() : m_real(0.0), m_imag(0.0) {}
Complex::Complex(double real, double imag) : m_real(real), m_imag(imag) {}
Complex Complex::operator+(const Complex &A) const 
{
	Complex B;
	B.m_real = this->m_real + A.m_real;
	B.m_imag = this->m_imag + A.m_imag;

	return B;
}

void Complex::display() const
{
	cout << m_real << "+" << m_imag << "i" << endl;
}

int main(void)
{
	Complex obj1(2.3, 5.2);
	Complex obj2(3.9, 5.5);

	Complex obj3 = obj1 + obj2;// obj1.operator+(obj2)
	obj3.display();

	return 0;
}

