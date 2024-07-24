#include "Window.h"

void Window::centerText(RECT rect, const TCHAR* text) const{
	int textWidth = textwidth(text);
	int textHeight = textheight(text);
	int centerX = rect.left + (rect.right - rect.left - textWidth) / 2;
	int centerY = rect.top + (rect.bottom - rect.top - textHeight) / 2;
	outtextxy(centerX, centerY, text);
}

void Window::windowLocation(int windowWidth, int windowHeight) const{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // 获取屏幕宽度
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);  // 获取屏幕高度
	int x = (screenWidth - windowWidth) / 2;  // 计算窗口左上角的 x 坐标
	int y = (screenHeight - windowHeight) / 2 + 5;  // 计算窗口左上角的 y 坐标
	HWND hwnd = GetHWnd();//窗口的句柄
	SetWindowPos(hwnd, NULL, x - 100, y - 20, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	/*第一个参数是窗口句柄hwnd，表示要操作的窗口
	第二个参数是放置目标窗口的句柄，NULL表示不改变Z序
	第三个参数x - 100是窗口新位置的x坐标，相对于屏幕原点的水平偏移量
	第四个参数y - 20是窗口新位置的y坐标，相对于屏幕原点的垂直偏移量
	第五个和第六个参数0, 0表示不改变窗口的宽度和高度
	最后一个参数是SWP_NOSIZE | SWP_NOZORDER，指定了改变窗口位置时不改变窗口的大小和Z序*/ 
}



