#include "Timer.h"

const int ADDITION = 320;

void Timer::showTime(int ROW, int COL, int SIZE, int icon) {
	settextcolor(RED);
	AddFontResourceEx("res/ttf/digital-7-4.ttf", FR_PRIVATE, NULL);// ��ʱ����������Դ
	const int height = SIZE;
	settextstyle(height, 0, _T("Digital-7"));// ����������ʽ
	std::string numberStr = std::to_string(elapsedTimeSeconds); // ������ת��Ϊ�ַ���
	numberStr = " " + numberStr + " ";
	int textWidth = textwidth(numberStr.c_str()); // ��ȡ�ַ������ı����
	outtextxy(ROW * SIZE + 0.5 * (ADDITION - textWidth), COL * SIZE - (icon + height), numberStr.c_str());
	RemoveFontResourceEx("res/ttf/DingTalk-JinBuTi.ttf", FR_PRIVATE, NULL);
}

void Timer::timerFunction()
{
    // ��ȡ��ǰʱ����Ϊ��ʱ����ʼ��
    auto lastTime = std::chrono::steady_clock::now();
    // ѭ������Ƿ���Ҫ���¾���������
    while (running) {
        // ��ȡ��ǰʱ��
        auto currentTime = std::chrono::steady_clock::now();
        // ���㵱ǰʱ�����ϴμ�¼ʱ��Ĳ�ֵ����ת������
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count() >= 1) {
            // �����ֵ���ڻ����1�룬������elapsedTimeSeconds����
            elapsedTimeSeconds++;
            // ����lastTimeΪ��ǰʱ�䣬׼����һ�ּ�ʱ
            lastTime = currentTime;
        }
    }
}

