#include <iostream>
#include <cstring>

using namespace std;

// 自定义异常类
class OutOfRange {
	public:
		OutOfRange():m_flag(1) {}
		OutOfRange(int len , int index):m_len(len), m_index(index), m_flag(2) {}

	public:
		void exceptionInfo();// 异常信息
	private:
		int m_flag;// 不同的值不同的错误 m_flag = 1 空数组 m_flag=2 越界
		int m_len;
		int m_index;
};

void OutOfRange::exceptionInfo()
{
	switch (m_flag) {
		case 1:
			cout << "Error msg: empty array, no elements" << endl;
			break;
		case 2:
			cout << "Error msg: out of range" << m_len << "," << m_index << endl;
			break;
		default:
			cout << "Unkown exception" << endl;
			break;
	} 
}

// 模板头
template<typename T>
class Array {
	public:
		Array(int n=0);
		~Array();
		void add_tail(const T &elm);
		int length() {return size;}
		// = [] -> ()
		Array & operator=(const Array & a);
		T & operator[](int i);
		T pop_tail();// 返回数组的最后一个元素

	private:
		int size;
		T *ptr;
};

template<typename T>
Array<T>::Array(int n):size(n)
{
	if (n == 0)
		ptr = NULL;
	else {
		ptr = new T[size];
	}
}

template<typename T>
Array<T>::~Array()
{
	if (ptr)
		delete []ptr;
}


template<typename T>
Array<T> & Array<T>::operator=(const Array & a)
{
	if (this==&a)
		return *this;
	if (a.ptr == NULL) // 空数组
		if (ptr)
			delete [] ptr;
		ptr = NULL;
		size = 0;
		return *this;

	if (a.size > size) {
		if (ptr)
			delete [] ptr;
		ptr = new T[a.size];
	}
	memcpy(ptr, a.ptr, sizeof(T)*a.size);
	size = a.size;

	return *this;
}

template<typename T>
T & Array<T>::operator[](int i)
{
	if (i < 0 || i >= size) {
		// 越界
		throw OutOfRange(size, i); // 抛出异常
	}
	return ptr[i];
}

template<typename T>
T Array<T>::pop_tail()
{
	if (size == 0)
		throw OutOfRange();
	return ptr[size-1];
}

template<typename T>
void Array<T>::add_tail(const T &elm)
{
	if (ptr) {
		T *tmp = new T[size+1];	
		memcpy(tmp, ptr, sizeof(T)*size);
		delete [] ptr;
		ptr = tmp;
	} else {
		ptr = new T[1];
	}
	ptr[size++] = elm;
}

int main(void)
{
	Array<int> arr;

	for (int i = 1; i <= 10; i++)
		arr.add_tail(i);
	for (int i = 0; i < 10; i++) {
		cout << arr[i] << ",";
	}
	cout << endl;

	try {
		cout << arr[20] << endl;	
	} catch (OutOfRange e) {
		e.exceptionInfo();
	}


	return 0;
}

