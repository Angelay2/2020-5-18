#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
/*
1. 全局变量和静态数据都在数据段
	sizeof是获取类型的大小的操作符   strlen是获取有效字符个数的函数
	malloc开辟新的整形空间
	realloc是重新去分配空间 可用来原地扩容, 也可以原地缩容 地址相同
	当后面的空间不够的时候, 就会变成非原地扩容 并且释放原有空间 
	realloc(NULL, sizeof(int)), 这就相当于malloc
	
2. malloc/free
	自定义/内置类型:
		malloc:只申请空间
		free: 释放空间
*/

void test(){

	int* pi = (int*)malloc(sizeof(int));
	int* pi2 = (int*)realloc(pi, sizeof(int)* 4);// 原地扩容
	int* pi3 = (int*)realloc(pi2, sizeof(int)* 1000); // 非原地扩容,因为后面的空间不够用了, 只能重新开辟空间,  而且把前面的原有指向的所有空间都释放掉了 (pi和pi2指向的空间)
	int* pi4 = (int*)realloc(pi3, sizeof(int)); // 缩容
	// int* pi5 = (int*)realloc(NULL, sizeof(int));// 相当于malloc

	// realloc 不需要显示释放传入realloc的指针参数所指向的空间
	// free(pi); // 会崩 因为pi和pi2指向的空间已被释放掉
	// free(pi2);// 会崩
	// free(pi3);// 不会崩 
	// 只需释放最后一次realloc返回的指针所指向的空间即可, 
	free(pi4);// 不会崩 两个同时出现 后者崩了, 因为指向的是同一片空间 
	// free(pi5);// 会崩
	int* pi6 = (int*)calloc(4, sizeof(int)); // 申请空间 + 做空间0初始化
	free(pi6);
}

/* 3. new/delete   new []/delete[]

内置类型:
	new: 申请空间 , 也可以初始化(new 类型(初始值))
	delete: 空间释放
	new[] : 申请连续空间, 不可以初始化
	delete[]: 释放连续空间
自定义类型:
	new: 申请空间 + 调用构造函数(可以是默认构造, 也可以是带参构造, 用户指定)
	delete: 调用析构 + 空间释放
	new[] : 申请连续空间 + 调用默认构造
	delete[] : 调用析构 + 释放连续空间
new/delete,  new []/ delete [] 配套使用
底层逻辑:
	new: operator new申请空间 + 调用构造
	delete: 调用析构 + operator delete释放空间
	operator new: malloc + 报异常
	operator delete: 就是free
	new[] : 函数里面调的是 operator new[] --> operator new + 构造
	delete[] : 函数里面调的是 析构+operator delete[] --> operatoe delete

*/
class A{
public:
	// 无参构造和全缺省的构造都是默认构造
	A(int a = 1, int b = 2, int c = 3)
	//A(int a, int b, int c)
		: _a(a)
		, _b(b)
		, _c(c){
		cout << "A(int, int, int)" << endl;
		}

	A(const A& A)
	{
		cout << "A(const A&)" << endl;
	}

	~A(){
		cout << "~A()" << endl;
	}
private:
	int _a;
	int _b;
	int _c;
};
void test2(){
	// malloc 仅仅是开空间 并没有初始化 调用构造函数功能  且不能初始化 因为成员变量为private 
	A* pa = (A*)malloc(sizeof(A));// 堆上 值都为随机值 
	A obj(1, 2, 3);// 栈上 掉用了构造函数

	// C++添加了新的在堆上申请内存的方式 --> new + 数据类型(初始值)
	//                                    new + 数据类型[元素个数]
	int* p = new int; // 创建了整形空间
	int* p2 = new int(2); // 创建了1个整形空间, 且值为2
	int* p3 = new int[10]; // 创建了10个连续的整形空间

	// 自定义类型: new --> 申请空间 + 调用构造函数初始化
	A* pa2 = new A(4, 5, 6); // 这里的值已经赋好了, 也是自动调用的构造函数

	// 用new申请的空间 用delete释放  new [] --> delete[]+指针
	delete p;
	delete p2;
	delete[] p3;

	// 对于自定义类型: delete会清理资源(调用析构函数) + 释放空间
	// 只能释放堆上空间
	delete pa2;
}

void test3(){
	//A array[10];

	cout << "heap creat: " << endl;
	//申请自定义类型的连续空间，需要有默认构造函数(包括无参构造和全缺省构造)
	A* array2 = new A[10];

	//delete array2;
	delete[] array2;

	A* pa = new A(10, 9, 8);// 调带参构造
	A* pa1 = new A; // 调默认构造

	A* pcopy = new A(*pa);// 也可以调拷贝构造
}


/* 
void* operator new(size_t n);   是一个全局函数, 功能类似 malloc
但申请空间失败时 比malloc多了一个报错
 而运算符重载函数可以有多种表达形式:
	operator++(A a);  
	operator++(a); 
	++a;
*/
void test4(){
	void* ptr1 = operator new(10); 
	// void* ptr2 = new 10; // 说明new不是运算符重载函数
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = (int*)operator new(sizeof(int));
	// 申请失败的区别:
	// malloc申请失败 返回NULL指针
	// operator new失败 报异常
	char* p3 = (char*)malloc(sizeof(int)* (0x7fffffff)); // 申请2G的空间 malloc会返回NULL
	char* p4 = (char*)operator new(sizeof(char)* (0x7fffffff));// 会报异常 
}

// operator delete: 封装free
void test5(){
	int* pi = (int*)operator new(sizeof(int));
	operator delete(pi);
}

using std::allocator;
struct ListNode
{
	int _data;
	ListNode* _next;

	//operator new定制
	void* operator new(size_t n)
	{
		void* ptr = allocator<ListNode>().allocate(1);
		cout << "memory poll allocate" << endl;
		return ptr;
	}
	//operator delete定制
	void operator delete(void* ptr)
	{
		allocator<ListNode>().deallocate((ListNode*)ptr, 1);
		cout << "memory poll deallocate" << endl;
	}
};

struct ListNode2
{
	int _data;
	ListNode* _next;
};

void test6()
{
	ListNode* lst = new ListNode;

	ListNode2* lst2 = new ListNode2;

	delete lst;
	delete lst2;
}

void test7()
{
	A* pa = (A*)malloc(sizeof(A));

	//显式调用构造函数: new定位表达式： 在已经申请好的空间上进行初始化
	// new (空间指针) 类型（参数列表）
	new (pa)A(1, 2, 3); //带参构造

	A* pa2 = (A*)malloc(sizeof(A));
	new (pa2)A; //无参构造


}

int main(){
	//test2();
	test();
	/*
	char* pChar3 = "abcd";
	cout << sizeof(pChar3) << endl;
	cout << strlen(pChar3) << endl;
*/
	system("pause");
	return 0;
}