#pragma once
#include <vector>
#include "Music.h"
#include"Window.h"
#include"Timer.h"
#include "LeaderBoard.h"


class Game :public Window, protected Music, public Timer//继承关系
{
private: 
    int row;            // 雷区的行数，x轴方向
    int col;            // 雷区的列数，y轴方向
    int size;           // 方格的边长，单位是像素
    int icon;           // 图标大小，用于显示图标（如旗帜、问号等）
    int mineCount;     // 雷的总数
    int openCells;     // 已翻开的方格数
    int theme;         // 当前主题，用于改变游戏界面的视觉效果
    IMAGE img[20];     // 用于存储游戏中使用到的图像资源
    std::vector<std::vector<int>> mineArea; // 存储雷区信息的二维数组，记录每个方格的状态
    int setFlag;       // 设置标志，可能用于标记特定状态
    int difficulty;    // 游戏难度级别
    bool gameWon;      // 游戏是否胜利的标志
    bool gameLost;     // 游戏是否失败的标志
    LeaderBoard leaderboard; // 排行榜，用于记录玩家分数和排名

private: 
    void selectDifficulty(); // 选择游戏难度
    void selectTheme();      // 选择游戏主题
    void initMinefield();    // 初始化雷区，随机放置雷
    void drawMinefield();    // 绘制雷区界面

    int uncoverCell(int x, int y);          // 翻开指定位置的方格
    int markCell(int x, int y);             // 在指定位置标记雷（插旗）
    void uncoverSafeCell(int x, int y);     // 翻开安全区域的方格
    void checkSurroundingMines(int x, int y); // 检查周围是否有雷
    void updateGameState(int total, int openCells, bool& gameWon, bool& gameLost, int x, int y); // 更新游戏状态
    void handlePostGameLogic(bool gameWon, bool gameLost); // 处理游戏结束后的逻辑

public:
    Game() : row(0), col(0), size(0), icon(0), mineCount(0), openCells(0),
        theme(0), setFlag(0), difficulty(1), gameWon(false), gameLost(false) {
        leaderboard.loadScores("leaderboard.txt"); // 构造函数中加载排行榜数据
    }

    ~Game() { // 析构函数，确保游戏结束时保存排行榜数据
        leaderboard.saveScores("leaderboard.txt");
    }

    void setValue(int _row, int _col, int _mineCount, int _size, int _icon); // 设置游戏参数，如行数、列数、雷的总数等

    void setGame() { // 初始化游戏设置，包括难度和主题选择

        selectDifficulty();
        selectTheme();
    }

    void loadImage(); // 加载游戏所需的图像资源

    void setField() { // 设置游戏场地，包括初始化和绘制雷区
        initMinefield();
        drawMinefield();
    }

    void playGame(); // 开始游戏的主循环
    bool gameLose();  // 判断游戏是否失败
    bool gameWin();   // 判断游戏是否胜利
};
