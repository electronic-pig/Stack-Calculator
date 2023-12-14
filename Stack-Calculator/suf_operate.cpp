#include "head.h"
//由表达式字符串转化为后缀表达式栈
void getInput() {
	int flag = 0;
	char ch = expression[0];
	int i = 0;
	while (ch != '=') {
		// 如果输入字符是数字或小数点，直接存入
		if (ch >= '0' && ch <= '9' || ch == '.') {
			// 初始字符
			if (flag == 0) {
				es.stack[++es.top][++es.index] = ch;
				flag = 1;
			}
			// 前一个输入为数字或负号，继续向后排
			else if (flag == 1) {
				es.stack[es.top][++es.index] = ch;
			}
			// flag == 2  // 前一个输入为操作符，换一行排
			else {
				es.index = -1;
				es.stack[++es.top][++es.index] = ch;
				flag = 1;
			}
		}
		// 如果接受字符是除开'-'的其他符号，执行中缀转后缀算法
		else if (ch == '+' || ch == '*' || ch == '/' || ch == '(' || ch == ')') {
			IntoSuf(ch);
			flag = 2;
		}
		//检查'-'是减号还是负号
		else if (ch == '-') {
			//如果“-”出现在表达式首位并且后面紧跟数字，那么此时为负号
			if (i == 0 && expression[1] >= '0' && expression[1] <= '9') {
				es.stack[++es.top][++es.index] = ch;
				flag = 1;
			}
			//如果“-”出现在表达式首位并且后面紧跟左括号，那么此时为负号，在整个字符串数组首位插个0处理成 “ 0 - （xxx）”的形式
			if (i == 0 && expression[1] == '(') {
				char temp[MaxSize] = "";
				strcat_s(temp, expression);
				memset(expression, '\0', sizeof(expression));
				expression[0] = '0';
				strcat_s(expression, temp);
				i = -1;
				flag = 0;
			}
			//如果“ - ”出现在左括号后面，那么此时为负号，合并到后面的数字字符串中
			if (i > 0 && expression[i - 1] == '(') {
				es.index = -1;
				es.stack[++es.top][++es.index] = ch;
				flag = 1;
			}
			else if (i > 0) {
				//执行中缀转后缀算法
				IntoSuf(ch);
				flag = 2;
			}
		}
		i++;
		ch = expression[i];
	}
	// 输入‘=’后，将操作符栈中的字符全部取出来
	while (os.top >= 0) {
		es.index = -1;
		es.stack[++es.top][++es.index] = os.stack[os.top--];
	}
}
//中缀表达式转后缀表达式
void IntoSuf(char ch) {
	// 如果栈空
	if (os.top == -1) {
		os.stack[++os.top] = ch;//直接入栈
	}
	else
	{
		// 如果接受字符为*或/，则将栈顶的*或/全部排出再存入
		if (ch == '*' || ch == '/') {
			while (os.stack[os.top] == '*' || os.stack[os.top] == '/') {
				es.index = -1;
				es.stack[++es.top][++es.index] = os.stack[os.top--];
			}
			os.stack[++os.top] = ch;
		}
		// 如果接受字符为+或-
		else if (ch == '+' || ch == '-') {
			if (os.stack[os.top] == '(')    // 栈顶是（，则直接存入
				os.stack[++os.top] = ch;
			// 栈顶为其他，则取出至栈顶为（或栈空，再存入
			else {
				while (os.top >= 0 && os.stack[os.top] != '(') {
					es.index = -1;
					es.stack[++es.top][++es.index] = os.stack[os.top];//将操作符放入表达式栈
					os.stack[os.top] = '\0';
					os.top--;//操作符退栈
				}
				os.stack[++os.top] = ch;
			}
		}
		// 接受字符为（，则直接存入
		else if (ch == '(') {
			os.stack[++os.top] = ch;
		}
		// 接受字符为）,则将栈内（前字符全部排出,并舍弃（
		else if (ch == ')') {
			while (os.stack[os.top] != '(') {
				es.index = -1;
				es.stack[++es.top][++es.index] = os.stack[os.top];//将操作符放入表达式栈
				os.stack[os.top] = '\0';
				os.top--;//操作符退栈
			}
			os.stack[os.top] = '\0';
			os.top--;//‘(’退栈
		}
	}
}
//返回由后缀表达式计算的结果
double suf_getOutput() {
	int i;
	double Pre, Later;// Pre为前数，Later为后数，out为结果值
	double out = 0;//结果
	char Operation;// 符号
	for (i = 0; i <= es.top; i++) {
		//栈的元素第一位为数字或者为负数，即第二位元素不为空
		if (es.stack[i][0] >= '0' || es.stack[i][1] != '\0') {
			double d = atof(es.stack[i]);  // atof()将字符类型转化为double类型
			ns.top++;
			ns.stack[ns.top] = d;
		}
		else {
			Operation = es.stack[i][0];//操作符
			Later = ns.stack[ns.top--];
			Pre = ns.stack[ns.top--];
			switch (Operation) {
			case '+': out = Pre + Later; break;// 加
			case '-': out = Pre - Later; break;// 减
			case '*': out = Pre * Later; break;// 乘
			case '/': out = Pre / Later; break;// 除
			}
			ns.stack[++ns.top] = out;
		}
	}
	es.clear();//操作符栈清空
	return out;
}