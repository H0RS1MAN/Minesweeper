#pragma once
#include <chrono>
#include<iostream>
#include<graphics.h>
#include<string>
#include<conio.h>
#include <atomic>
#include <thread>

class Game;

class Timer {
public:
    Timer() : running(false), elapsedTimeSeconds(0) {
        // ���캯���г�ʼ��
    }

    ~Timer() {
        // ����������ȷ���̰߳�ȫ��ֹͣ��ʱ��
        stop();
    }

    std::atomic<int> elapsedTimeSeconds;// ������������ʹ��ԭ�����ͱ�֤���̻߳����µ��̰߳�ȫ

    void start() {
        if (!running) {
            running = true;
            timerThread = std::thread(&Timer::timerFunction, this);// �����̣߳�����timerFunction
        }
    }

    void stop() {
        if (running) {
            running = false;
            if (timerThread.joinable()) {
                timerThread.join();// ����߳̿�join����ȴ��߳̽���
            }
        }
    }

    void showTime(int ROW, int COL, int SIZE, int icon);
    //int getElapsedTimeSeconds() const {
    //    return elapsedTimeSeconds.load();
    //}
    void timerFunction();
private:
    std::atomic<bool> running;
    std::thread timerThread;
};
