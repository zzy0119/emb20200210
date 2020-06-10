#include <iostream>

using namespace std;

class Student {
	public:
		Student(char *name, int age);
	public:
		// 将show方法作为当前类的友元函数
		friend void show(Student *stu);
	private:
		char *m_name;
		int m_age;
};

Student::Student(char *name, int age) : m_name(name), m_age(age) {}

// 非成员函数 
void show(Student *stu) 
{
	cout << stu->m_name << stu->m_age << endl;
}

int main(void)
{
	Student s("c++", 20);
	
	show(&s);

	return 0;
}
