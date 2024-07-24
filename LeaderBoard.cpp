#include "LeaderBoard.h"

void LeaderBoard::addScore(const std::string& name, std::string& difficulty, int time)
{
    PlayerScore score = { name, difficulty, time };
    scores.push_back(score);
    // �������а�����
    std::sort(scores.begin(), scores.end());
    int rank = 1;
    for (const auto& score : scores) {
        if (score.difficulty == difficulty) {
            if (score.timeTaken != time)
                rank++;
            else
                break;
        }
    }
    std::cout << "��������λ��" << difficulty << "��" << rank << "λ��" << "��ʱ" << time << "��" << std::endl;

}

void LeaderBoard::loadScores(const std::string& filename)
{
    std::ifstream infile(filename);
    std::string name;
    std::string difficulty;
    int timeTaken;
    while (infile >> name >> difficulty >> timeTaken) {
        PlayerScore score = { name, difficulty, timeTaken };
        scores.push_back(score);
    }
    infile.close();
    // ���غ������Ҫ����
    std::sort(scores.begin(), scores.end());
}

void LeaderBoard::saveScores(const std::string& filename)
{
    std::ofstream outfile(filename);
    for (const auto& score : scores) {
        outfile << score.playerName << " " << score.difficulty << " " << score.timeTaken << std::endl;
    }
    outfile.close();
}


void LeaderBoard::displayScoresByDifficulty(std::vector<PlayerScore> scores, const std::string& difficulty) {
    std::cout << "���а�-" << difficulty << ":\n";
    //������������
    for (const auto& score : scores) {
        if (score.difficulty == difficulty) {
            std::cout << score.playerName << "\t" << score.difficulty << "\t" << score.timeTaken << "\n";
        }
    }
}

void LeaderBoard::displayLeaderboard()
{
    displayScoresByDifficulty(scores, "����");
    std::cout << "--------------------------------------" << std::endl;
    displayScoresByDifficulty(scores, "�м�");
    std::cout << "--------------------------------------" << std::endl;
    displayScoresByDifficulty(scores, "�߼�");
    std::cout << "--------------------------------------" << std::endl;
}
