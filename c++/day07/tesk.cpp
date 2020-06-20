#include <iostream>
#include <cstring>

using namespace std;

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
		T & operator[](int i)
		{
			return ptr[i];
		}

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
	for (int i = 0; i < 10; i++)
		cout << arr[i] << ",";
	cout << endl;

	return 0;
}

