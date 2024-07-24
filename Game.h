#pragma once
#include <vector>
#include "Music.h"
#include"Window.h"
#include"Timer.h"
#include "LeaderBoard.h"


class Game :public Window, protected Music, public Timer//�̳й�ϵ
{
private: 
    int row;            // ������������x�᷽��
    int col;            // ������������y�᷽��
    int size;           // ����ı߳�����λ������
    int icon;           // ͼ���С��������ʾͼ�꣨�����ġ��ʺŵȣ�
    int mineCount;     // �׵�����
    int openCells;     // �ѷ����ķ�����
    int theme;         // ��ǰ���⣬���ڸı���Ϸ������Ӿ�Ч��
    IMAGE img[20];     // ���ڴ洢��Ϸ��ʹ�õ���ͼ����Դ
    std::vector<std::vector<int>> mineArea; // �洢������Ϣ�Ķ�ά���飬��¼ÿ�������״̬
    int setFlag;       // ���ñ�־���������ڱ���ض�״̬
    int difficulty;    // ��Ϸ�Ѷȼ���
    bool gameWon;      // ��Ϸ�Ƿ�ʤ���ı�־
    bool gameLost;     // ��Ϸ�Ƿ�ʧ�ܵı�־
    LeaderBoard leaderboard; // ���а����ڼ�¼��ҷ���������

private: 
    void selectDifficulty(); // ѡ����Ϸ�Ѷ�
    void selectTheme();      // ѡ����Ϸ����
    void initMinefield();    // ��ʼ�����������������
    void drawMinefield();    // ������������

    int uncoverCell(int x, int y);          // ����ָ��λ�õķ���
    int markCell(int x, int y);             // ��ָ��λ�ñ���ף����죩
    void uncoverSafeCell(int x, int y);     // ������ȫ����ķ���
    void checkSurroundingMines(int x, int y); // �����Χ�Ƿ�����
    void updateGameState(int total, int openCells, bool& gameWon, bool& gameLost, int x, int y); // ������Ϸ״̬
    void handlePostGameLogic(bool gameWon, bool gameLost); // ������Ϸ��������߼�

public:
    Game() : row(0), col(0), size(0), icon(0), mineCount(0), openCells(0),
        theme(0), setFlag(0), difficulty(1), gameWon(false), gameLost(false) {
        leaderboard.loadScores("leaderboard.txt"); // ���캯���м������а�����
    }

    ~Game() { // ����������ȷ����Ϸ����ʱ�������а�����
        leaderboard.saveScores("leaderboard.txt");
    }

    void setValue(int _row, int _col, int _mineCount, int _size, int _icon); // ������Ϸ���������������������׵�������

    void setGame() { // ��ʼ����Ϸ���ã������ѶȺ�����ѡ��

        selectDifficulty();
        selectTheme();
    }

    void loadImage(); // ������Ϸ�����ͼ����Դ

    void setField() { // ������Ϸ���أ�������ʼ���ͻ�������
        initMinefield();
        drawMinefield();
    }

    void playGame(); // ��ʼ��Ϸ����ѭ��
    bool gameLose();  // �ж���Ϸ�Ƿ�ʧ��
    bool gameWin();   // �ж���Ϸ�Ƿ�ʤ��
};
