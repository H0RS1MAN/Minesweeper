#include "Window.h"

void Window::centerText(RECT rect, const TCHAR* text) const{
	int textWidth = textwidth(text);
	int textHeight = textheight(text);
	int centerX = rect.left + (rect.right - rect.left - textWidth) / 2;
	int centerY = rect.top + (rect.bottom - rect.top - textHeight) / 2;
	outtextxy(centerX, centerY, text);
}

void Window::windowLocation(int windowWidth, int windowHeight) const{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // ��ȡ��Ļ���
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);  // ��ȡ��Ļ�߶�
	int x = (screenWidth - windowWidth) / 2;  // ���㴰�����Ͻǵ� x ����
	int y = (screenHeight - windowHeight) / 2 + 5;  // ���㴰�����Ͻǵ� y ����
	HWND hwnd = GetHWnd();//���ڵľ��
	SetWindowPos(hwnd, NULL, x - 100, y - 20, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	/*��һ�������Ǵ��ھ��hwnd����ʾҪ�����Ĵ���
	�ڶ��������Ƿ���Ŀ�괰�ڵľ����NULL��ʾ���ı�Z��
	����������x - 100�Ǵ�����λ�õ�x���꣬�������Ļԭ���ˮƽƫ����
	���ĸ�����y - 20�Ǵ�����λ�õ�y���꣬�������Ļԭ��Ĵ�ֱƫ����
	������͵���������0, 0��ʾ���ı䴰�ڵĿ�Ⱥ͸߶�
	���һ��������SWP_NOSIZE | SWP_NOZORDER��ָ���˸ı䴰��λ��ʱ���ı䴰�ڵĴ�С��Z��*/ 
}



