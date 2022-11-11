#include "head.h"
//定义全局变量
char strFileName[MAX_PATH] = "";	//用于接收文件名
char expression[MaxSize] = "";//用于储存算数表达式
//定义栈对象
Expression_Stack es;//表达式栈
Operation_Stack os;//操作符栈
Number_Stack ns;//数字栈
Expression_Stack es1;//表达式栈1,用于中缀表达式求值
Operation_Stack os1;//操作符栈,用于中缀表达式求值
Number_Stack ns1;//数字栈1，用于中缀表达式求值

//main函数
int main() {
	menu_init();//初始化界面
	ExMessage msg;//获取消息对象
	while (true) {
		msg = getmessage(EX_MOUSE | EX_KEY);//获取鼠标和键盘消息
		switch (msg.message) {
			case WM_LBUTTONDOWN://鼠标左键点击
				if (msg.x >= 250 && msg.x <= 250 + 200 && msg.y >= 250 && msg.y <= 250 + 100) {
					initgraph(400, 650);//初始化界面
					HWND hwnd = GetHWnd();//获取窗口句柄函数；
					SetWindowText(hwnd, "计算器");//修改窗口名字函数
					setbkcolor(0xFAFFF0);//设置背景颜色
					cleardevice();//用背景颜色刷新
					calcul_memu();//计算器界面
					mouse_info();//读取鼠标消息
				}
				if (msg.x >= 530 && msg.x <= 530 + 200 && msg.y >= 250 && msg.y <= 250 + 100) {
					HWND hn = GetHWnd();//获取窗口句柄函数；
					char* path = get_file_path();//获得文件路径
					char suf[MaxSize] = "";//定义后缀表达式字符串
					//如果文件路径存在
					if (path) {
						strcpy_s(expression, read(path).c_str());//将文件第一行的表达式字符串保存到数组中
						//判断表达式是否为空
						if (strcmp(expression, "") == 0) {
							MessageBox(hn, "表达式为空！", NULL, MB_OK | MB_ICONERROR);
							break;
						}
						//判断表达式是否非法
						if (judge_infix(expression) == 0) {
							MessageBox(hn, "表达式非法！", NULL, MB_OK | MB_ICONERROR);
						}
						else {
							MessageBox(hn, expression, "表达式", MB_OK | MB_ICONASTERISK);//输出表达式到窗口
							getInput();//将表达式字符串转化为后缀表达式栈
							//将后缀表达式栈的内容拷贝到后缀表达式字符串
							for (int i = 0; i <= es.top; i++) {
								strcat_s(suf, es.stack[i]);
								strcat_s(suf, " ");
							}
							MessageBoxA(hn, suf, "中缀表达式化为后缀表达式为：", MB_OK | MB_ICONASTERISK);//输出后缀表达式字符串到窗口
							char out[MaxSize] = "";//定义运算结果字符串
							string s = to_string(suf_getOutput());//获取运算结果字符串
							strcpy_s(out, s.c_str());//拷贝字符串
							MessageBox(hn, out, "运算结果为", MB_OK | MB_ICONASTERISK);//输出结果字符串到窗口
							strcpy_s(expression, "");//表达式清空
						}
					}
				}
				break;
			default:
				break;
		}
	}
	return 0;
}

