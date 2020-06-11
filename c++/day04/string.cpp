#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main(void)
{
	string s1; // s1空字符串
	string s2 = "c++"; // 没有'\0'
	string s3 = s2;
	string s4(10, 'h');
	int len = s4.length();

	cout << s1 << "," << s2 << "," << s3 << endl;	
	cout << s4 << endl;
	cout << len << endl;

	// string --->char *
	string path = "/etc/passwd";
	fopen(path.c_str(), "r");

#if 0
	// 读入字符串
	cin >> s1;
	cout << s1 << endl;

	// 访问字符串中的每一个字符
	for (int i = 0; i < s1.length(); i++)
		cout << s1[i];
	cout << endl;
	s1[2] = 'v';
	cout << s1 << endl;
#endif

	// 字符串拼接
	string s5 = s2 + s4;
	cout << s5 << endl;
	string s6 = "s6";
	s6 += s5;
	cout << s6 << endl;
	char *s7 = "seven";

	s5 = s6 + s7;
	cout << s5 << endl;

	// 插入
	s1 = "123456789";
	s2 = s1;
	s3 = "hello";
	s1.insert(2, s3);
	cout << s1 << endl;

	//删除
	s1.erase(5, 3); // pos, len
	cout << s1 << endl;
	
	// 提取子串
	s2 = s1.substr(3, 3);
	cout << s2 << endl;

	// 查找
	int index = s1.find(s2, 3); // substr, pos rfind()
	cout << s1 << endl;
	cout << s2 << endl;
	cout << index << endl;

	// 找到两个字符串中共同拥有的字符位置
	s1 = "pppptwo three four";
	s2 = "hellotwoworld";
	index = s1.find_first_of(s2);
	cout << index << endl;

	return 0;
}

