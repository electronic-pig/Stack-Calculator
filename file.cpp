#include "head.h"
//获得选择的文件路径
char* get_file_path() {
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小
	ofn.hwndOwner = NULL;//拥有着窗口句柄
	ofn.lpstrFile = strFileName;//接收返回的文件路径
	ofn.nMaxFile = sizeof(strFileName);	//缓冲区长度
	ofn.lpstrInitialDir = ".\\";//初始目录为项目目录
	ofn.lpstrTitle = TEXT("请选择一个文件"); //窗口标题
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //文件、目录必须存在，隐藏只读选项
	//打开文件对话框
	if (GetOpenFileName(&ofn)) {
		return strFileName;
	}
	//如果没有选择文件，则返回错误消息窗口
	else {
		MessageBox(NULL, TEXT("请选择一文件"), NULL, MB_ICONERROR);
		return NULL;
	}
}
//读文件操作，返回第一行的字符串
string read(char path[]) {
	ifstream file;
	file.open(path, ios::in);//从文件路径打开文件
	string s;
	getline(file, s);//读取文件第一行到字符串
	file.close();//文件关闭
	return s;
}