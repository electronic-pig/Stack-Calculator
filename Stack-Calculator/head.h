/* 对外提供的接口 */
#include<easyx.h>/* 图形库头文件 */
#include<iostream>
#include<string>
#include<fstream>
#define MaxSize 100
using namespace std;
//声明全局变量
extern char strFileName[MAX_PATH];
extern char expression[MaxSize];
//表达式栈
class Expression_Stack {
public:
	int top;//栈顶下标
	int index;//数据下标
	char stack[MaxSize][MaxSize];//用于存储表达式的二维数组
	//构造方法
	Expression_Stack() {
		top = -1;
		index = -1;
		for (int i = 0; i < MaxSize; i++) {
			for (int j = 0; j < MaxSize; j++) {
				stack[i][j] = '\0';
			}
		}
	}
	//栈清空
	void clear() {
		top = -1;
		index = -1;
		for (int i = 0; i < MaxSize; i++) {
			for (int j = 0; j < MaxSize; j++) {
				stack[i][j] = '\0';
			}
		}
	}
};
//运算符栈
class Operation_Stack {
public:
	int top;//栈顶下标
	char stack[MaxSize];//用于存储操作符的一维数组
	//构造方法
	Operation_Stack() {
		top = -1;
		for (int i = 0; i < MaxSize; i++) {
			stack[i] = '\0';
		}
	}
};
//数据栈
class Number_Stack {
public:
	int top;//栈顶下标
	double stack[MaxSize];//用于存储数据的一维数组
	//构造方法
	Number_Stack() {
		top = -1;
		for (int i = 0; i < MaxSize; i++) {
			stack[i] = 0.0;
		}
	}
};
//栈的声明
extern Expression_Stack es;//表达式栈,用于后缀表达式求值
extern Operation_Stack os;//操作符栈,用于后缀表达式求值
extern Number_Stack ns;//数字栈,用于后缀表达式求值
extern Expression_Stack es1;//表达式栈1,用于中缀表达式求值
extern Operation_Stack os1;//操作符栈1,用于中缀表达式求值
extern Number_Stack ns1;//数字栈1，用于中缀表达式求值
//main.cpp
int main();
//GUI.cpp
void button(int x, int y, int w, int h, int textSize, TCHAR* text);
void menu_init();
void calcul_memu();
void mouse_info();
//file.cpp
char* get_file_path();
string read(char path[]);
//judge_infix.cpp
int judge_infix(char* str);
//suf_oparate.cpp
void getInput();
void IntoSuf(char ch);
double suf_getOutput();
//in_oparate.cpp
void transfer();
double in_getOutput();
double Cal(char a, double b, double c);