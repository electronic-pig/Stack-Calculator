#include "head.h"
//运算函数，a为运算符,b、c分别为两数
double Cal(char a, double b, double c) {
	switch (a) {
	case '+':
		return (b + c);
		break;
	case '-':
		return (b - c);
		break;
	case '*':
		return (b * c);
		break;
	case '/':
		return (1.0 * b / c);
		break;
	default:
		return 0;
	}
}
//将字符串字符转化为中缀表达式,存储在中缀表达式栈中
void transfer() {
	int flag = 0;
	char ch = expression[0];
	int i = 0;
	while (ch != '=') {
		// 如果输入字符是数字或小数点，直接存入
		if (ch >= '0' && ch <= '9' || ch == '.') {
			// 初始字符
			if (flag == 0) {
				es1.stack[++es1.top][++es1.index] = ch;
				flag = 1;
			}
			// 前一个输入为数字或负号，继续向后排
			else if (flag == 1) {
				es1.stack[es1.top][++es1.index] = ch;
				flag = 1;
			}
			// flag == 2  // 前一个输入为操作符，换一行排
			else {
				es1.index = -1;
				es1.stack[++es1.top][++es1.index] = ch;
				flag = 1;
			}
		}
		// 如果接受字符是除开'-'的其他符号，换一行排
		else if (ch == '+' || ch == '*' || ch == '/' || ch == '(' || ch == ')') {
			es1.index = -1;
			es1.stack[++es1.top][++es1.index] = ch;
			flag = 2;
		}
		//检查'-'是减号还是负号
		else if (ch == '-') {
			//如果“-”出现在表达式首位并且后面紧跟数字，那么此时为负号
			if (i == 0 && expression[1] >= '0' && expression[1] <= '9') {
				es1.stack[++es1.top][++es1.index] = ch;
				flag = 1;
			}
			//如果“-”出现在表达式首位并且后面紧跟左括号，那么此时为负号，在整个字符串数组首位插个0处理成 “ 0 - （xxx）”的形式
			if (i == 0 && expression[1] == '(') {
				es1.stack[++es1.top][++es1.index] = '0';
				es1.index = -1;
				es1.stack[++es1.top][++es1.index] = ch;
				flag = 2;
			}
			//如果“ - ”出现在左括号后面，那么此时为负号，合并到后面的数字字符串中
			if (i > 0 && expression[i - 1] == '(') {
				es1.index = -1;
				es1.stack[++es1.top][++es1.index] = ch;
				flag = 1;
			}
			else if (i > 0) {
				//换一行排
				es1.index = -1;
				es1.stack[++es1.top][++es1.index] = ch;
				flag = 2;
			}
		}
		i++;
		ch = expression[i];
	}
}
//中缀表达式求值
double in_getOutput() {
	char a;
	double b;
	double c;
	int temp = 0;//用于括号匹配
	//遍历中缀表达式二维数组
	for (int i = 0; i <= es1.top; i++) {
		//如果是加号或减号，那么栈顶运算符可以拿出来运算了
		if ((es1.stack[i][0] == '+' || es1.stack[i][0] == '-') && es1.stack[i][1] == '\0') {
			//若操作符栈为空，故须运算符入操作符栈
			if (os1.top == -1) {
				os1.stack[++os1.top] = es1.stack[i][0];
			}
			else {
				while (os1.stack[os1.top] == '+' || os1.stack[os1.top] == '-' || os1.stack[os1.top] == '*' || os1.stack[os1.top] == '/') {
					b = ns1.stack[ns1.top--];//取出一个数字
					c = ns1.stack[ns1.top--];//再取出一个数字
					a = os1.stack[os1.top--];//操作符栈顶元素拿出
					ns1.stack[++ns1.top] = Cal(a, b, c);//运算结果要入数字栈
				}
				os1.stack[++os1.top] = es1.stack[i][0];//运算完了之后该运算符要入栈
			}
		}
		//如果是乘号或除号，则只有栈顶也是乘除号时才需要计算
		else if (es1.stack[i][0] == '*' || es1.stack[i][0] == '/') {
			//同上
			if (os1.top == -1) {
				os1.top++;
				os1.stack[os1.top] = es1.stack[i][0];
			}
			else {
				while (os1.stack[os1.top] == '*' || os1.stack[os1.top] == '/') {
					a = os1.stack[os1.top--];//同上
					c = ns1.stack[ns1.top--];//同上
					b = ns1.stack[ns1.top--];//同上
					ns1.stack[++ns1.top] = Cal(a, b, c);//同上
					ns1.stack[ns1.top + 1] = 0;//栈顶后一个元素清空
					os1.stack[os1.top + 1] = '\0';//栈顶后一个元素清空
				}
				os1.stack[++os1.top] = es1.stack[i][0];//同上
			}
		}
		//如果是左括号则直接压入栈2
		else if (es1.stack[i][0] == '(') {
			os1.top++;
			os1.stack[os1.top] = es1.stack[i][0];
			temp++;
		}
		//如果是右括号，则计算第一个左括号前的所有操作符，最后将此左括号直接弹出
		else if (es1.stack[i][0] == ')') {
			if (temp > 0) {
				while (os1.stack[os1.top] != '(') {
					a = os1.stack[os1.top--];
					c = ns1.stack[ns1.top--];
					b = ns1.stack[ns1.top--];
					ns1.stack[++ns1.top] = Cal(a, b, c);
					ns1.stack[ns1.top + 1] = 0;//栈顶后一个元素清空
					os1.stack[os1.top + 1] = '\0';//栈顶后一个元素清空
				}
				os1.top--;//此左括号直接弹出
				os1.stack[os1.top + 1] = '\0';//栈顶后一个元素清空
				temp--;
			}
		}
		//如果不是操作符则直接进去
		else {
			ns1.stack[++ns1.top] = atof(es1.stack[i]);//数字，转为整数
		}
	}
	//遍历后如果栈不为空，计算剩下操作符
	while (os1.top != -1) {
		a = os1.stack[os1.top--];
		c = ns1.stack[ns1.top--];
		b = ns1.stack[ns1.top--];
		ns1.stack[++ns1.top] = Cal(a, b, c);
		ns1.stack[ns1.top + 1] = 0;//栈顶后一个元素清空
	}
	return ns1.stack[ns1.top];
}