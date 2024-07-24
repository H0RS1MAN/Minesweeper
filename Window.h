#pragma once
#include<graphics.h>
#include<conio.h>
#include <windows.h>
class Window
{
public:
	void centerText(RECT rect, const TCHAR* text) const;
	void windowLocation(int windowWidth, int windowHeight) const;
};

