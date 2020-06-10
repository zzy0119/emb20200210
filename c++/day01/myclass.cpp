#include <stdio.h>
/*
 iostream.h cin cout
 fstream.h
 complex.h

 std--->standard 标准命名空间
 新版本库 iostream cstdio
 */

// 命名空间
namespace A{
	FILE *fp = NULL;
}

namespace B {
	FILE *fp = NULL;
}

// 定义学生类
class Student {
public:
	// 类包含的变量
	char *name;
	int age;
	float score;
	// 函数
	void say() {
		printf("%s的年龄是%d,成绩是%f\n", name, age, score);
	}
};

int main(int argc, char *argv[])
{
	Student stu1; // stu1称为对象

	stu1.name = "小白";
	stu1.age = 10;
	stu1.score = 90.99;

	stu1.say();

	// ::域解析操作符
	A::fp = fopen("/etc/passwd", "r");
	B::fp = fopen("./myclass.cpp", "r");

	using namespace A;
	fp = fopen("./myclass.cpp", "r"); // fp就是A

	return 0;
}
