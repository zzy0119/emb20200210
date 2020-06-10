#include <iostream>

using namespace std;

// 类的声明
class Person {
private:// 私有的
	char *m_name;
	// const int m_age;
	int m_age;
	float m_score;
public:
	Person();
	Person(char *name, int age, float score); // 构造函数 无返回值
	~Person(); // 析构函数
	void show();
};

Person::Person()
{
	cout << "Person is called" << endl;
	m_name = NULL;
	m_age = 0;
	m_score = 0.0;
}

#if 0
Person::Person(char *name, int age, float score)
{
	m_name = name;
	m_age = age;
	m_score = score;
}
#endif

// 成员变量是const类型，初始化此变量唯一方法就是通过初始化列表
Person::Person(char *name, int age, float score):m_name(name), m_age(age)
{
	m_score = score;	
}

void Person::show()
{
	cout << m_name << "的年龄是" << m_age << "成绩是" \
		<< m_score << endl;
}

Person::~Person()
{
	cout << "the destructor is called" << endl;
}

int main(void)
{
	Person per; // Person per Person *a = new Person
	Person p("小李", 20, 88.88);// 栈
	Person *pp = new Person("小王", 22, 90.1);

	p.show();

	pp->show();
	
	delete pp;

	return 0;
}

