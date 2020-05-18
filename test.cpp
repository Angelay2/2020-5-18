#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
/*
1. ȫ�ֱ����;�̬���ݶ������ݶ�
	sizeof�ǻ�ȡ���͵Ĵ�С�Ĳ�����   strlen�ǻ�ȡ��Ч�ַ������ĺ���
	malloc�����µ����οռ�
	realloc������ȥ����ռ� ������ԭ������, Ҳ����ԭ������ ��ַ��ͬ
	������Ŀռ䲻����ʱ��, �ͻ��ɷ�ԭ������ �����ͷ�ԭ�пռ� 
	realloc(NULL, sizeof(int)), ����൱��malloc
	
2. malloc/free
	�Զ���/��������:
		malloc:ֻ����ռ�
		free: �ͷſռ�
*/

void test(){

	int* pi = (int*)malloc(sizeof(int));
	int* pi2 = (int*)realloc(pi, sizeof(int)* 4);// ԭ������
	int* pi3 = (int*)realloc(pi2, sizeof(int)* 1000); // ��ԭ������,��Ϊ����Ŀռ䲻������, ֻ�����¿��ٿռ�,  ���Ұ�ǰ���ԭ��ָ������пռ䶼�ͷŵ��� (pi��pi2ָ��Ŀռ�)
	int* pi4 = (int*)realloc(pi3, sizeof(int)); // ����
	// int* pi5 = (int*)realloc(NULL, sizeof(int));// �൱��malloc

	// realloc ����Ҫ��ʾ�ͷŴ���realloc��ָ�������ָ��Ŀռ�
	// free(pi); // ��� ��Ϊpi��pi2ָ��Ŀռ��ѱ��ͷŵ�
	// free(pi2);// ���
	// free(pi3);// ����� 
	// ֻ���ͷ����һ��realloc���ص�ָ����ָ��Ŀռ伴��, 
	free(pi4);// ����� ����ͬʱ���� ���߱���, ��Ϊָ�����ͬһƬ�ռ� 
	// free(pi5);// ���
	int* pi6 = (int*)calloc(4, sizeof(int)); // ����ռ� + ���ռ�0��ʼ��
	free(pi6);
}

/* 3. new/delete   new []/delete[]

��������:
	new: ����ռ� , Ҳ���Գ�ʼ��(new ����(��ʼֵ))
	delete: �ռ��ͷ�
	new[] : ���������ռ�, �����Գ�ʼ��
	delete[]: �ͷ������ռ�
�Զ�������:
	new: ����ռ� + ���ù��캯��(������Ĭ�Ϲ���, Ҳ�����Ǵ��ι���, �û�ָ��)
	delete: �������� + �ռ��ͷ�
	new[] : ���������ռ� + ����Ĭ�Ϲ���
	delete[] : �������� + �ͷ������ռ�
new/delete,  new []/ delete [] ����ʹ��
�ײ��߼�:
	new: operator new����ռ� + ���ù���
	delete: �������� + operator delete�ͷſռ�
	operator new: malloc + ���쳣
	operator delete: ����free
	new[] : ������������� operator new[] --> operator new + ����
	delete[] : ������������� ����+operator delete[] --> operatoe delete

*/
class A{
public:
	// �޲ι����ȫȱʡ�Ĺ��춼��Ĭ�Ϲ���
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
	// malloc �����ǿ��ռ� ��û�г�ʼ�� ���ù��캯������  �Ҳ��ܳ�ʼ�� ��Ϊ��Ա����Ϊprivate 
	A* pa = (A*)malloc(sizeof(A));// ���� ֵ��Ϊ���ֵ 
	A obj(1, 2, 3);// ջ�� �����˹��캯��

	// C++������µ��ڶ��������ڴ�ķ�ʽ --> new + ��������(��ʼֵ)
	//                                    new + ��������[Ԫ�ظ���]
	int* p = new int; // ���������οռ�
	int* p2 = new int(2); // ������1�����οռ�, ��ֵΪ2
	int* p3 = new int[10]; // ������10�����������οռ�

	// �Զ�������: new --> ����ռ� + ���ù��캯����ʼ��
	A* pa2 = new A(4, 5, 6); // �����ֵ�Ѿ�������, Ҳ���Զ����õĹ��캯��

	// ��new����Ŀռ� ��delete�ͷ�  new [] --> delete[]+ָ��
	delete p;
	delete p2;
	delete[] p3;

	// �����Զ�������: delete��������Դ(������������) + �ͷſռ�
	// ֻ���ͷŶ��Ͽռ�
	delete pa2;
}

void test3(){
	//A array[10];

	cout << "heap creat: " << endl;
	//�����Զ������͵������ռ䣬��Ҫ��Ĭ�Ϲ��캯��(�����޲ι����ȫȱʡ����)
	A* array2 = new A[10];

	//delete array2;
	delete[] array2;

	A* pa = new A(10, 9, 8);// �����ι���
	A* pa1 = new A; // ��Ĭ�Ϲ���

	A* pcopy = new A(*pa);// Ҳ���Ե���������
}


/* 
void* operator new(size_t n);   ��һ��ȫ�ֺ���, �������� malloc
������ռ�ʧ��ʱ ��malloc����һ������
 ����������غ��������ж��ֱ����ʽ:
	operator++(A a);  
	operator++(a); 
	++a;
*/
void test4(){
	void* ptr1 = operator new(10); 
	// void* ptr2 = new 10; // ˵��new������������غ���
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = (int*)operator new(sizeof(int));
	// ����ʧ�ܵ�����:
	// malloc����ʧ�� ����NULLָ��
	// operator newʧ�� ���쳣
	char* p3 = (char*)malloc(sizeof(int)* (0x7fffffff)); // ����2G�Ŀռ� malloc�᷵��NULL
	char* p4 = (char*)operator new(sizeof(char)* (0x7fffffff));// �ᱨ�쳣 
}

// operator delete: ��װfree
void test5(){
	int* pi = (int*)operator new(sizeof(int));
	operator delete(pi);
}

using std::allocator;
struct ListNode
{
	int _data;
	ListNode* _next;

	//operator new����
	void* operator new(size_t n)
	{
		void* ptr = allocator<ListNode>().allocate(1);
		cout << "memory poll allocate" << endl;
		return ptr;
	}
	//operator delete����
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

	//��ʽ���ù��캯��: new��λ���ʽ�� ���Ѿ�����õĿռ��Ͻ��г�ʼ��
	// new (�ռ�ָ��) ���ͣ������б�
	new (pa)A(1, 2, 3); //���ι���

	A* pa2 = (A*)malloc(sizeof(A));
	new (pa2)A; //�޲ι���


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