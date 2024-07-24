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
        // 构造函数中初始化
    }

    ~Timer() {
        // 析构函数中确保线程安全地停止计时器
        stop();
    }

    std::atomic<int> elapsedTimeSeconds;// 经过的秒数，使用原子类型保证多线程环境下的线程安全

    void start() {
        if (!running) {
            running = true;
            timerThread = std::thread(&Timer::timerFunction, this);// 创建线程，运行timerFunction
        }
    }

    void stop() {
        if (running) {
            running = false;
            if (timerThread.joinable()) {
                timerThread.join();// 如果线程可join，则等待线程结束
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
