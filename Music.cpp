#include "Music.h"
#include<iostream>
#include<Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void Music::loadMusic() const
{
	mciSendString("open ./res/sound_effects/release_cell.mp3", NULL, 0, NULL);
	mciSendString("open ./res/sound_effects/flag_cell.mp3", NULL, 0, NULL);
	mciSendString("open ./res/sound_effects/move.mp3", NULL, 0, NULL);
	mciSendString("open ./res/sound_effects/game_lost.mp3", NULL, 0, NULL);
	mciSendString("open ./res/sound_effects/game_won.mp3", NULL, 0, NULL);
}

void Music::playReleaseCellMusic() const
{
	mciSendString("play ./res/sound_effects/release_cell.mp3 wait", NULL, 0, NULL);
}

void Music::closeReleaseCellMusic() const
{
	mciSendString("close ./res/sound_effects/release_cell.mp3", NULL, 0, NULL);
}



void Music::playFlagCellMusic() const
{
	mciSendString("play ./res/sound_effects/flag_cell.mp3 wait", NULL, 0, NULL);
}

void Music::closeFlagCellMusic() const
{
	mciSendString("close ./res/sound_effects/flag_cell.mp3", NULL, 0, NULL);
}

void Music::playMoveMusic() const
{
	mciSendString("play ./res/sound_effects/move.mp3 wait", NULL, 0, NULL);
}

void Music::closeMoveMusic() const
{
	mciSendString("close ./res/sound_effects/move.mp3", NULL, 0, NULL);
}

void Music::playGameLostMusic() const
{
	mciSendString("play ./res/sound_effects/game_lost.mp3 wait", NULL, 0, NULL);
}

void Music::closeGameLostMusic() const
{
	mciSendString("close ./res/sound_effects/game_lost.mp3", NULL, 0, NULL);
}

void Music::playGameWinMusic() const
{
	mciSendString("play ./res/sound_effects/game_won.mp3 wait", NULL, 0, NULL);
}

void Music::closeGameWinMusic() const
{
	mciSendString("close ./res/sound_effects/game_won.mp3", NULL, 0, NULL);
}


