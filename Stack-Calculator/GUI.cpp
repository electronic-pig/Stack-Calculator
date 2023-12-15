#include "head.h"
#include "resource.h"
//界面按钮
void button(int x, int y, int w, int h, int textSize, TCHAR* text, int roundRect) {
	setbkmode(TRANSPARENT);//设置文字的背景透明
	setfillcolor(0xAAAAAA);
	fillroundrect(x, y, x + w, y + h, roundRect, roundRect);//画出圆角矩形
	settextstyle(textSize, 0, "黑体");//设置字体格式
	//使文本居中对齐
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	settextcolor(0x333333);
	outtextxy(tx, ty, text);//输出字符串
}
//初始化界面
void menu_init() {
	initgraph(1000, 563);//初始化界面
	HWND hwnd = GetHWnd();//获取窗口句柄函数；
	SetWindowText(hwnd, "数学表达式求值");//修改窗口名字函数
	/* 加载背景图片 */
	IMAGE background;
	loadimage(&background, _T("IMAGE"), _T("background"), 1000, 563);
	putimage(0, 0, &background);
	TCHAR s1[20] = "从键盘输入";
	TCHAR s2[20] = "从文件输入";
	TCHAR s3[110] = "注：从键盘输入采用中缀表达式直接求值,从文件输入采用中缀转后缀表达式求值";
	//画包含文本的按钮
	button(250, 250, 200, 100, 30, s1, 24);
	button(530, 250, 200, 100, 30, s2, 24);
	button(150, 0, 700, 25, 17, s3, 6);
}
//计算器界面
void calcul_memu() {
	setfillcolor(0xFFFFFF);
	solidrectangle(0, 100, 400, 600);
	setlinestyle(PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1);
	setlinecolor(BLACK);
	line(0, 100, 400, 100);
	line(0, 200, 400, 200);
	line(0, 300, 400, 300);
	line(0, 400, 400, 400);
	line(0, 500, 400, 500);
	line(0, 599, 400, 599);
	line(100, 100, 100, 600);
	line(200, 100, 200, 600);
	line(300, 100, 300, 600);
	setbkmode(TRANSPARENT);//设置文字的背景透明
	settextstyle(50, 30, "幼圆", 0, 0, 750, false, false, false);
	settextcolor(0x333333);
	outtextxy(35, 120, "C");
	outtextxy(125, 120, "(");
	outtextxy(240, 120, ")");
	outtextxy(315, 120, "<-");
	outtextxy(35, 220, "7");
	outtextxy(135, 220, "8");
	outtextxy(235, 220, "9");
	outtextxy(335, 220, "+");
	outtextxy(35, 320, "4");
	outtextxy(135, 320, "5");
	outtextxy(235, 320, "6");
	outtextxy(335, 320, "-");
	outtextxy(35, 420, "1");
	outtextxy(135, 420, "2");
	outtextxy(235, 420, "3");
	outtextxy(335, 420, "*");
	outtextxy(40, 510, ".");
	outtextxy(135, 520, "0");
	outtextxy(235, 520, "=");
	outtextxy(335, 520, "/");
	setfillcolor(0xBBBBBB);
	solidrectangle(0, 600, 400, 650);
	settextstyle(0, 0, "幼圆", 0, 0, 1000, false, false, false);
	outtextxy(140, 610, "返回主界面");
}
//处理鼠标消息
void mouse_info() {
	int i = 0;//字符串数组下标
	char str[MaxSize] = "";//用于保存表达式的字符串
	int count = 0;//统计字符数
	char out[MaxSize] = "";//运算结果字符串
	char suf[MaxSize] = "";//后缀表达式字符串
	bool output = false;
	ExMessage m;
	while (true) {
		setbkmode(OPAQUE);//用背景色充当文字填充背景
		settextstyle(60, 20, "幼圆", 0, 0, 0, false, false, false);
		settextcolor(0x333333);
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message) {
			//鼠标左键按下
		case WM_LBUTTONDOWN:
			if (str[0] == '\0') {
				cleardevice();
				calcul_memu();
			}
			if (m.x > 100 && m.x < 200 && m.y > 100 && m.y < 200) {
				str[i] = '(';
				++i; count++;
			}
			if (m.x > 200 && m.x < 300 && m.y > 100 && m.y < 200) {
				str[i] = ')';
				++i; count++;
			}
			if (m.x > 300 && m.x < 400 && m.y > 200 && m.y < 300) {

				str[i] = '+';
				++i; count++;
			}
			if (m.x > 0 && m.x < 100 && m.y > 200 && m.y < 300) {

				str[i] = '7';
				++i; count++;
			}
			if (m.x > 100 && m.x < 200 && m.y > 200 && m.y < 300) {
				str[i] = '8';
				++i; count++;
			}
			if (m.x > 200 && m.x < 300 && m.y > 200 && m.y < 300) {
				str[i] = '9';
				++i; count++;
			}
			if (m.x > 300 && m.x < 400 && m.y > 300 && m.y < 400) {
				str[i] = '-';
				++i; count++;
			}
			if (m.x > 0 && m.x < 100 && m.y > 300 && m.y < 400) {
				str[i] = '4';
				++i; count++;
			}
			if (m.x > 100 && m.x < 200 && m.y > 300 && m.y < 400) {
				str[i] = '5';
				++i; count++;
			}
			if (m.x > 200 && m.x < 300 && m.y > 300 && m.y < 400) {
				str[i] = '6';
				++i; count++;
			}
			if (m.x > 300 && m.x < 400 && m.y > 400 && m.y < 500) {
				str[i] = '*';
				++i; count++;
			}
			if (m.x > 0 && m.x < 100 && m.y > 400 && m.y < 500) {
				str[i] = '1';
				++i; count++;
			}
			if (m.x > 100 && m.x < 200 && m.y > 400 && m.y < 500) {
				str[i] = '2';
				++i; count++;
			}
			if (m.x > 200 && m.x < 300 && m.y > 400 && m.y < 500) {
				str[i] = '3';
				++i; count++;
			}
			if (m.x > 300 && m.x < 400 && m.y > 500 && m.y < 600) {
				str[i] = '/';
				++i; count++;
			}
			if (m.x > 0 && m.x < 120 && m.y>500 && m.y < 600) {
				str[i] = '.';
				++i; count++;
			}
			if (m.x > 100 && m.x < 200 && m.y > 500 && m.y < 600) {
				str[i] = '0';
				++i; count++;
			}
			//按'<-'键清除后一个，往后退
			if (m.x > 300 && m.x < 400 && m.y > 100 && m.y < 200) {
				//前面还有字符
				if (i != 0) {
					i--;
					str[i] = '\0';
					count--;
					outtextxy(400 - count * 20 - 20, 20, " ");//把前一位打印的字符清空
				}
			}
			//按C键清除所有字符
			if (m.x > 0 && m.x < 100 && m.y > 100 && m.y < 200) {
				i = 0;
				count = 0;
				memset(str, '\0', sizeof(str));//字符串清空
				cleardevice();
				calcul_memu();
			}
			//按“=”结束输入
			if (m.x > 200 && m.x < 300 && m.y > 500 && m.y < 600) {
				str[i] = '=';
				str[i + 1] = '\0';
				cleardevice();//界面清空
				calcul_memu();
				//判断表达式是否为空
				if (strcmp(str, "=") == 0) {
					settextstyle(60, 20, "幼圆", 0, 0, 0, false, false, false);
					outtextxy(180, 20, "表达式为空！");
					es.clear();//表达式栈清空
					memset(str, '\0', sizeof(str));//字符串清空
					i = 0;
					count = 0;
					output = true;
					break;
				}
				//如果表达式非法
				if (judge_infix(str) == 0) {
					settextstyle(60, 20, "幼圆", 0, 0, 0, false, false, false);
					outtextxy(180, 20, "表达式非法！");
					es.clear();//表达式栈清空
					memset(str, '\0', sizeof(str));//字符串清空
					i = 0;
					count = 0;
					output = true;
					break;
				}
				strcpy_s(expression, str);//拷贝字符串到表达式
				transfer();
				//获得运算结果字符串
				string s = to_string(in_getOutput());
				strcpy_s(out, s.c_str());
				settextstyle(60, 20, "幼圆", 0, 0, 0, false, false, false);
				int length = static_cast<int>(s.length());
				outtextxy(400 -  length * 20, 20, out);
				es1.clear();//表达式栈清空
				memset(str, '\0', sizeof(str));//字符串清空
				memset(expression, '\0', sizeof(expression));//表达式清空
				memset(out, '\0', sizeof(out));//运算结果清空
				memset(suf, '\0', sizeof(suf));//后缀表达式清空
				i = 0;
				count = 0;
				output = true;
				break;
			}
			if (m.x > 0 && m.x < 400 && m.y > 600 && m.y < 650) {
				main();
			}
			break;
			//鼠标左键弹起
		case WM_LBUTTONUP:
			outtextxy(400 - count * 20, 20, str);
			break;
			//键盘按下
		case WM_KEYDOWN:
			if (m.vkcode == 0x30) {
				str[i] = '0';
				++i; count++;
			}
			if (m.vkcode == 0x31) {
				str[i] = '1';
				++i; count++;
			}
			if (m.vkcode == 0x32) {
				str[i] = '2';
				++i; count++;
			}
			if (m.vkcode == 0x33) {
				str[i] = '3';
				++i; count++;
			}
			if (m.vkcode == 0x34) {
				str[i] = '4';
				++i; count++;
			}
			if (m.vkcode == 0x35) {
				str[i] = '5';
				++i; count++;
			}
			if (m.vkcode == 0x36) {
				str[i] = '6';
				++i; count++;
			}
			if (m.vkcode == 0x37) {
				str[i] = '7';
				++i; count++;
			}
			if (m.vkcode == 0x38) {
				str[i] = '8';
				++i; count++;
			}
			if (m.vkcode == 0x39) {
				str[i] = '9';
				++i; count++;
			}
			//回退键
			if (m.vkcode == VK_BACK) {
				//前面还有字符
				if (i != 0) {
					i--;
					str[i] = '\0';
					count--;
					outtextxy(400 - count * 20 - 20, 20, " ");//把前一位打印的字符清空
				}
			}
			break;
			//键盘弹起
		case WM_KEYUP:
			outtextxy(400 - count * 20, 20, str);
			break;
		}
	}
}