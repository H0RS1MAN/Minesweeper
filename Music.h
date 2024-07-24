#pragma once


class Music
{
public:
    void loadMusic() const;

    void playReleaseCellMusic() const; // 打开方格
    void closeReleaseCellMusic() const;

    void playFlagCellMusic() const; // 插旗
    void closeFlagCellMusic() const;

    void playMoveMusic() const; // 空白格递归
    void closeMoveMusic() const;

    void playGameLostMusic() const; // 踩雷
    void closeGameLostMusic() const; 

    void playGameWinMusic() const; // 胜利
    void closeGameWinMusic() const;
};

