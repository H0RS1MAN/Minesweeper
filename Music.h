#pragma once


class Music
{
public:
    void loadMusic() const;

    void playReleaseCellMusic() const; // �򿪷���
    void closeReleaseCellMusic() const;

    void playFlagCellMusic() const; // ����
    void closeFlagCellMusic() const;

    void playMoveMusic() const; // �հ׸�ݹ�
    void closeMoveMusic() const;

    void playGameLostMusic() const; // ����
    void closeGameLostMusic() const; 

    void playGameWinMusic() const; // ʤ��
    void closeGameWinMusic() const;
};

