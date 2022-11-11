#include "head.h"
//判断中缀表达式合法性,不考虑数据大小，参数为中缀表达式字符串
int judge_infix(char* str) {
	int temp = 0;//用于字符串遍历和括号匹配
	char allchar[] = "0123456789.+-*/()=";//所有可能字符
	bool has_operatechar = false;//判断字符串里是否有操作符
	int n = 1;//循环变量
	//尾字符不为"="时非法
	if (str[strlen(str) - 1] != '=')
		return 0;
	//尾字符前一个只能是数字或者“)”，否则非法
	if (str[strlen(str) - 2] != ')' && !(str[strlen(str) - 2] >= '0' && str[strlen(str) - 2] <= '9')) {
		return 0;
	}
	//第一个字符为乘除或小数点或")"时非法
	if (str[0] == '/' || str[0] == '*' || str[0] == '.' || str[0] == ')')
		return 0;
	//第一个字符为'('
	if (str[0] == '(') temp++;
	//字符串中不含操作符时非法
	while (n < strlen(str) - 1) {
		if (str[n] == '+' || str[n] == '-' || str[n] == '*' || str[n] == '/') {
			has_operatechar = true;
			break;
		}
		n++;
	}
	if (!has_operatechar) return 0;
	//遍历字符串，范围是（1， n-2）
	for (int i = 1; i < strlen(str) - 1; i++) {
		//字符串中出现不允许的字符时非法
		char* p = strchr(allchar, str[i]);
		if (p == NULL) return 0;
		//操作符并排时非法
		if (str[i] == '+' || str[i] == '*' || str[i] == '-' || str[i] == '/')
			if (str[i + 1] == '+' || str[i + 1] == '*' || str[i + 1] == '-' || str[i + 1] == '/')
				return 0;
		//等号提前出现非法
		if (str[i] == '=')
			return 0;
		//字符为"("
		if (str[i] == '(') {
			//其后的字符为乘除时非法
			if ((str[i + 1] == '*' || str[i + 1] == '/'))
				return 0;
			//"("前为数字时非法
			else if (str[i - 1] >= '0' && str[i - 1] <= '9')
				return 0;
			//检查括号匹配
			temp++;
		}
		//字符为")"
		else if (str[i] == ')') {
			//")"前为操作符时非法
			if (str[i - 1] == '+' || str[i - 1] == '*' || str[i - 1] == '-' || str[i - 1] == '/')
				return 0;
			//")"后为数字时非法
			else if (str[i + 1] >= '0' && str[i + 1] <= '9')
				return 0;
			//检查括号匹配
			temp--;
			//")"出现在"("前面时非法
			if (temp < 0)
				return 0;
		}
		//字符为"."
		if (str[i] == '.') {
			//小数点前后不为数字时非法
			if (str[i - 1] < '0' || str[i - 1] > '9') return 0;
			if (str[i + 1] < '0' || str[i + 1] > '9') return 0;
		}
		//字符为"/",除以0时非法(0.0,0.00,0.000等)
		if (str[i] == '/' && str[i + 1] == '0') {
			//保证数组不越界
			if (size_t(i) + 2 <= strlen(str) - 1) {
				if (str[i + 2] == '.') {
					while (size_t(i) + 2 <= strlen(str) - 1) {
						i++;
						if (str[i + 2] >= '1' && str[i + 2] <= '9') return 1;
						if (str[i + 2] != '0') return 0;
					}
				}
				else return 0;
			}
			return 0;
		}
	}
	//括号不匹配时非法
	if (temp != 0)
		return 0;
	return 1;
}