#include <iostream>

using namespace std;

// 轮胎类
class Tyre {
private:
	int m_radius;
	int m_width;
public:
	Tyre(int radius, int width);
	~Tyre();
	void show();
};

Tyre::Tyre(int radius, int width):m_radius(radius), m_width(width){}
Tyre::~Tyre()
{
	cout << "Tyre constructor is called" << endl;
}
void Tyre::show()
{
	cout << "轮胎半径：" << m_radius << "寸" << endl;
	cout << "轮胎宽度：" << m_radius << "mm" << endl;
}

// 引擎类
class Engine {
private:
	float m_output;
public:
	Engine(float output=2.0);
	~Engine();
	void show();
};

Engine::Engine(float output):m_output(output) {}
Engine::~Engine()
{
	cout << "Engin constructor is called" << endl; 
}

void Engine::show() 
{
	cout << "排量" << m_output << "L" << endl;
}

// 车类
class Car {
	private:
		int m_price;
		Tyre m_tyre; // 成员对象
		Engine m_engine;
	public:
		Car(int price, int radius, int width);
		~Car();
		void show();
};

// 通过初始化列表为成员变量初始化
Car::Car(int price, int radius, int width) : m_price(price), m_tyre(radius, width){
}

void Car::show()
{
	cout << "价格是" << m_price << "￥" << endl;
	m_tyre.show();
	m_engine.show();
}

Car::~Car()
{
	cout << "Car constructor is called" << endl;
}

int main(void)
{
	Car car(200000, 20, 300);	
	car.show();

	return 0;
}

