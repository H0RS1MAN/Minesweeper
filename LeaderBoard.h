#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>

class LeaderBoard
{
private:
    struct PlayerScore {
        std::string playerName;
        std::string difficulty;
        int timeTaken;
        bool operator < (const PlayerScore& other) const {//���������
            return timeTaken < other.timeTaken; // ��ʱԽ�٣�����Խǰ
        }
    };

    std::vector<PlayerScore> scores;

public:
    void addScore(const std::string& name, std::string& difficulty, int time);
    void loadScores(const std::string& filename);
    void saveScores(const std::string& filename);
    void displayScoresByDifficulty(std::vector<PlayerScore> scores, const std::string& difficulty);
    void displayLeaderboard();
};

