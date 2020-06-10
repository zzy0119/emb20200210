#include <stdio.h>

using namespace std;

// 修饰成员变量和成员函数：public private protected--->成员访问限定符

// 定义学生类
class Student {
public:
	// 类包含的变量
	char *name;
	// 函数
	void say();
	int age;
private:
	float score;
};

void Student::say() 
{
	printf("%s的年龄是%d,成绩是%f\n", name, age, score);
}

int main(int argc, char *argv[])
{
	Student stu1; // stu1称为对象

	stu1.name = "小白";
	stu1.age = 10;
	stu1.score = 90.99;

	stu1.say();

	return 0;
}
