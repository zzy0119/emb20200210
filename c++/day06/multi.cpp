#include <iostream>

using namespace std;
// 基类
class People {
	protected:
		char *m_name;
		int m_age;
	public:
		People(char *name, int age);
		virtual void display(); // 虚函数
};
People::People(char *name, int age) : m_name(name), m_age(age) {}
void People::display()
{
	cout << m_name << "今年" << m_age << "岁了，目前还是一个无业游民" << endl;
}

class Teacher:public People {
	private:
		int m_salary;
	public:
		Teacher(char *name, int age, int salary);
		virtual void display();
};
Teacher::Teacher(char *name, int age, int salary) : People(name, age), m_salary(salary) {}
void Teacher::display()
{
	cout << m_name << "今年" << m_age << "了， 他的职业是一名老师" << endl;
}

int main(void)
{
	People *p = new People("小白", 20);
	p->display();

	p = new Teacher("王美丽", 30, 10000);
	p->display();

	return 0;
}

