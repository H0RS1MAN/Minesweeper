#include<iostream>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include "Game.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;


int main() {
	Game myGame;
	myGame.setGame();
	myGame.loadImage();
	myGame.setField();
	myGame.playGame();
}