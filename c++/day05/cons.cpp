#include <iostream>

using namespace std;

// 基类
class Person {
	protected:
		const char *m_name;
		int m_age;
	public:
		Person();// 默认的构造方法
		Person(const char *, int );
};

Person::Person():m_name("默认"), m_age(0) {}

Person::Person(const char *name, int age) : m_name(name), m_age(age) {}

// 派生类
class Student:public Person{
	private:
		float m_score;
	public:
		Student();
		Student(const char *name, int age, float score);
		void show();
};

Student::Student():m_score(0.0){}

// 派生类的构造函数中调用基类的构造函数
// Student::Student(const char *name, int age, float score) : Person(name, age), m_score(score){}

Student::Student(const char *name, int age, float score) : m_score(score){}
void Student::show()
{
	cout << m_name << endl;
	cout << m_age << endl;
	cout << m_score << endl;
}


int main(void)
{
	Student stu("c++", 20, 100);	
	stu.show();

	Student stu2;// 默认构造方法
	stu2.show();

	return 0;
}

