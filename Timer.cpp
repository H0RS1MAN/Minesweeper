#include "Timer.h"

const int ADDITION = 320;

void Timer::showTime(int ROW, int COL, int SIZE, int icon) {
	settextcolor(RED);
	AddFontResourceEx("res/ttf/digital-7-4.ttf", FR_PRIVATE, NULL);// 临时加载字体资源
	const int height = SIZE;
	settextstyle(height, 0, _T("Digital-7"));// 设置字体样式
	std::string numberStr = std::to_string(elapsedTimeSeconds); // 将整数转换为字符串
	numberStr = " " + numberStr + " ";
	int textWidth = textwidth(numberStr.c_str()); // 获取字符串的文本宽度
	outtextxy(ROW * SIZE + 0.5 * (ADDITION - textWidth), COL * SIZE - (icon + height), numberStr.c_str());
	RemoveFontResourceEx("res/ttf/DingTalk-JinBuTi.ttf", FR_PRIVATE, NULL);
}

void Timer::timerFunction()
{
    // 获取当前时间作为计时的起始点
    auto lastTime = std::chrono::steady_clock::now();
    // 循环检查是否需要更新经过的秒数
    while (running) {
        // 获取当前时间
        auto currentTime = std::chrono::steady_clock::now();
        // 计算当前时间与上次记录时间的差值，并转换成秒
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count() >= 1) {
            // 如果差值大于或等于1秒，则增加elapsedTimeSeconds计数
            elapsedTimeSeconds++;
            // 更新lastTime为当前时间，准备下一轮计时
            lastTime = currentTime;
        }
    }
}

