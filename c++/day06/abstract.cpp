#include <iostream>

using namespace std;

// 线
class Line {
	public:
		Line(float len);
		virtual float area() = 0; //纯虚函数
		virtual float volumn() = 0;
	protected:
		float m_len;
};
Line::Line(float len) : m_len(len) {}

// 矩形类
class Rec:public Line {
	public:
		Rec(float len, float width);
		float area();
	protected:
		float m_width;
};

Rec::Rec(float len, float width):Line(len), m_width(width) {}
float Rec::area()
{
	return m_len * m_width;
}

// 长方体
class Cubo:public Rec {
	public:
		Cubo(float len, float width, float height);
		float area(); 
		float volumn();
	private:
		float m_height;
};

Cubo::Cubo(float len, float width, float height):Rec(len, width), m_height(height) {}

float Cubo::area()
{
	return 2*(m_len*m_width + m_len*m_height + m_width*m_height); 
}
float Cubo::volumn()
{
	return m_len * m_width * m_height;
}

int main(void)
{
	Line *p = new Cubo(10, 20, 30);
	cout << "面积:" <<  p->area() << endl;
	cout << "体积:" << p->volumn() << endl;

	return 0;
}
