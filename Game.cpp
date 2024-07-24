#include "Game.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include <thread>
#include <chrono>
#include <windows.h>
#include<numeric>

double const ADDITION = 320;

void Game::setValue(int _row, int _col, int _mineCount, int _size, int _icon) {
	row = _row;
	col = _col;
	size = _size;
	mineCount = _mineCount;
	mineArea.resize(row * 2, std::vector<int>(col * 2, 0));//初始化mineArea[][]
	openCells = 0;
	icon = _icon;
}

void drawDifficultySelectionScreen() {
	setbkcolor(LIGHTGRAY);
	cleardevice();
	settextcolor(BLACK);
	AddFontResourceEx("res/DingTalk-JinBuTi.ttf", FR_PRIVATE, NULL);
	settextstyle(30, 0, _T("钉钉进步体"));
	// 绘制三个难度按钮
	outtextxy(280, 100, _T("请选择游戏难度："));
	setfillcolor(LIGHTGRAY);
	setlinecolor(BLACK);
	fillrectangle(350, 200, 450, 250);
	settextstyle(20, 0, _T("钉钉进步体"));
	outtextxy(380, 215, _T("初级"));
	fillrectangle(350, 300, 450, 350);
	outtextxy(380, 315, _T("中级"));
	fillrectangle(350, 400, 450, 450);
	outtextxy(380, 415, _T("高级"));
	RemoveFontResourceEx("res/DingTalk-JinBuTi.ttf", FR_PRIVATE, NULL);
}


void Game::selectDifficulty()
{
	initgraph(800, 600);
	windowLocation(800, 600);
	cleardevice();
	drawDifficultySelectionScreen();
	MOUSEMSG msg;
	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x > 350 && msg.x < 450) {
				if (msg.y > 200 && msg.y < 250) {
					difficulty = 1; // 简单
					break;
				}
				else if (msg.y > 300 && msg.y < 350) {
					difficulty = 2; // 普通
					break;
				}
				else if (msg.y > 400 && msg.y < 450) {
					difficulty = 3; // 困难
					break;
				}
			}
		}
	}
	// 根据选择设置游戏参数
	switch (difficulty) {
	case 1:
		setValue(9, 9, 80, 35, 54);
		break;
	case 2:
		setValue(16, 16, 40, 35, 54);
		break;
	case 3:
		setValue(30, 16, 99, 35, 54);
		break;
	}
	closegraph();
}

void Game::selectTheme()
{
	initgraph(800, 600);
	windowLocation(800, 600);
	setbkcolor(LIGHTGRAY);
	cleardevice();

	settextcolor(BLACK);
	AddFontResourceEx("res/ttf/DingTalk-JinBuTi.ttf", FR_PRIVATE, NULL);// 临时加载字体资源
	settextstyle(30, 0, _T("钉钉进步体"));// 设置字体样式
	// 计算文本宽度
	int textWidth = textwidth(_T("请选择游戏主题"));
	// 计算文本起始位置
	int textX = (800 - textWidth) / 2;
	// 绘制文本
	outtextxy(textX, 50, _T("请选择游戏主题"));
	RemoveFontResourceEx("res/ttf/DingTalk-JinBuTi.ttf", FR_PRIVATE, NULL);

	const int buttonWidth = 200;
	const int buttonHeight = 50;
	const int startX = 300; // 将按钮左侧起始位置调整为窗口中心
	const int startY = 120;
	const TCHAR* buttonText[6] = { _T("现代-暗色"), _T("现代-浅色"), _T("经典-暗色"), _T("经典-浅色"), _T("花园"), _T("未知") };
	RECT buttons[6];
	//绘制6个矩形按钮
	for (int i = 0; i < 6; ++i) {
		buttons[i].left = startX;
		buttons[i].top = startY + i * 70;
		buttons[i].right = startX + buttonWidth;
		buttons[i].bottom = startY + i * 70 + buttonHeight;

		setlinecolor(BLACK);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		roundrect(buttons[i].left, buttons[i].top, buttons[i].right, buttons[i].bottom, 10, 10);

		settextcolor(BLACK);
		centerText(buttons[i], buttonText[i]);

	}
	//通过循环判断所点击的按钮，因为6个按钮之间距离和分布满足一定数学关系
	bool chosen = false;
	while (!chosen) {
		MOUSEMSG msgSelectTheme = GetMouseMsg();
		if (msgSelectTheme.uMsg == WM_LBUTTONDOWN) {
			for (int i = 0; i < 6; ++i) {
				if (msgSelectTheme.x >= startX && msgSelectTheme.x <= startX + buttonWidth &&
					msgSelectTheme.y >= startY + i * 70 && msgSelectTheme.y <= startY + i * 70 + buttonHeight) {
					theme = i + 1;
					chosen = true;
					break;
				}
			}
		}
	}
	closegraph();
}

void Game::loadImage()
{
	const std::string themes[] = { "alternative_dark", "alternative_light", "classic_dark", "classic_light", "flowerfield", "twemoji" };
	const std::string icons[] = { "back_to_menu.png", "exit.png", "restart.png" };

	int themeIndex = theme - 1; 

	for (int i = 0; i <= 13; i++) {
		std::string file = "res/minefield_themes/" + themes[themeIndex] + "/" + std::to_string(i) + ".png";
		loadimage(&img[i], file.c_str(), size, size);
	}
	for (int i = 14; i <= 16; i++) {
		std::string file = "res/minefield_themes/" + themes[themeIndex] + "/" + std::to_string(i) + ".png";
		loadimage(&img[i], file.c_str(), 2 * size, 2 * size);
	}
	loadimage(&img[17], "res/icon/back_to_menu.png", icon, icon);
	loadimage(&img[18], "res/icon/exit.png", icon, icon);
	loadimage(&img[19], "res/icon/restart.png", icon, icon);
}

void Game::initMinefield()
{
	//初始化，先将盘面每一个区域设置为0
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mineArea[i][j] = 0;
		}
	}
	srand((unsigned)time(NULL));//初始化随机数种子

	std::vector<int>mine(row * col);
	std::iota(mine.begin(), mine.end(), 0); // 从0开始，依次给向量中的每个元素赋值0, 1, 2, ..., (row*col-1)
	std::random_shuffle(mine.begin(), mine.end()); // 随机打乱向量mine中的元素顺序，以随机确定雷的位置
	for (int cnt = 0; cnt < mineCount; cnt++) {
		int x = mine[cnt] / col;
		int y = mine[cnt] % col;
		mineArea[x][y] = -1;//非安全格为-1
		int minX = max(0, x - 1);
		int maxX = min(row - 1, x + 1);
		int minY = max(0, y - 1);
		int maxY = min(col - 1, y + 1);
		for (int i = minX; i <= maxX; ++i) {
			for (int j = minY; j <= maxY; j++) {
				if (mineArea[i][j] != -1)
					mineArea[i][j]++;
			}
		}
	}
}
/*
mineArea[][]
	-1                   雷
	0-8         安全格，显示出周围雷数
   19-28             覆盖所有方格
	>=29              被标记方格
*/

void Game::drawMinefield()
{
	initgraph(size * row + ADDITION, size * col);
	windowLocation(size * row + ADDITION, size * col);
	windowLocation(size * row, size * col);
	setbkcolor(WHITE); // 假设背景色为白色
	cleardevice();    // 清除窗口，填充背景色
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(size * row, 0, size * row + ADDITION, size * col);
	//根据玩家所选难度，绘制窗口
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mineArea[i][j] += 20;
		}
	}
	loadImage();
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (mineArea[i][j] == -1) {
				putimage(i * size, j * size, &img[11]); // Mine
			}
			else if (mineArea[i][j] > -1 && mineArea[i][j] < 9) {
				putimage(i * size, j * size, &img[mineArea[i][j]]); // mineCount
			}
			else if (mineArea[i][j] > 18 && mineArea[i][j] < 29) {
				putimage(i * size, j * size, &img[12]); // Not Open
			}
			else {
				putimage(i * size, j * size, &img[10]); // Flag
			}
		}
	}
	int change = 0;
	putimage(row * size + int(0.5 * ADDITION) - size, 0, &img[16]);
	putimage(row * size + change, col * size - icon, &img[17]);//back_to_menu
	putimage(row * size + int(0.5 * (ADDITION - icon)) + change, col * size - icon, &img[19]);//restart
	putimage(row * size + ADDITION - icon + change, col * size - icon, &img[18]);//exit
	
}

int change = 0;

void Game::playGame()
{
	loadMusic();
	int total = row * col - mineCount;
	openCells = 0;
	gameWon = false;
	gameLost = false;
	start();//计时开始
	while (!gameWon && !gameLost) {
		MOUSEMSG msg = GetMouseMsg();
		int x = msg.x / size;
		int y = msg.y / size;
		if (x < row && y < col) {
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (mineArea[x][y] >= 1 && mineArea[x][y] <= 8) {
					checkSurroundingMines(x, y);
					break;
				}
				else {
					uncoverCell(x, y);
				}
				break;
			case WM_RBUTTONDOWN:
				markCell(x, y);
				break;
			default:
				break;
			}
		}

		showTime(row, col, size, icon);

		updateGameState(total, openCells, gameWon, gameLost, x, y);
	}
	handlePostGameLogic(gameWon, gameLost);
}

void drawRemainingMinesCount(int mineCount, int setFlag, int SIZE, int ROW, int COL, int icon) {
	// 保存当前背景颜色
	int currentBkColor = getbkcolor();
	setbkcolor(BLACK);
	setlinecolor(BLACK);
	// 加载字体资源
	AddFontResourceEx("res/ttf/digital-7-4.ttf", FR_PRIVATE, NULL);
	const int height = SIZE;
	// 设置字体样式
	settextstyle(height, 0, _T("Digital-7"));
	// 将剩余雷数转换为字符串
	std::string numberStr = std::to_string(mineCount - setFlag);
	numberStr = " 剩余雷数：" + numberStr + " ";
	// 获取字符串的文本宽度
	int textWidth = textwidth(numberStr.c_str());
	// 计算文本的坐标
	int textX = ROW * SIZE + 0.5 * (ADDITION - textWidth);
	int textY = icon + height + 20;
	// 绘制透明矩形，覆盖上一次的文字
	fillrectangle(textX, textY, textX + textWidth, textY + height);
	// 设置文本颜色为橙色
	settextcolor(RGB(255, 165, 0));
	// 绘制文字
	outtextxy(textX, textY, numberStr.c_str());
	// 恢复背景颜色
	setbkcolor(currentBkColor);
	// 移除字体资源
	RemoveFontResourceEx("res/ttf/digital-7-4.ttf", FR_PRIVATE, NULL);
}

void Game::updateGameState(int total, int openCells, bool& gameWon, bool& gameLost, int x, int y) {
	drawRemainingMinesCount(mineCount, setFlag, size, row, col, icon);
	if (!gameWon && total == openCells) {
		gameWin();
		playGameWinMusic();
		closeGameWinMusic();
		gameWon = true;
		
	}
	if (!gameLost && mineArea[x][y] == -1) {
		gameLose();
		playGameLostMusic();
		closeGameLostMusic();
		gameLost = true;
		
	}
}

void Game::handlePostGameLogic(bool gameWon, bool gameLost) {
	elapsedTimeSeconds = 0;
	setFlag = 0;
	while (gameWon || gameLost) {
		MOUSEMSG msg = GetMouseMsg();
		int exit = false;
		int x = msg.x;
		int y = msg.y;
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (y >= col * size - icon && y <= col * size) {
				if (x >= row * size + 0.5 * (ADDITION - icon) + change && x <= row * size + 0.5 * (ADDITION - icon) + change + icon) {
					closegraph();
					setField();
					playGame();
				}
				else if (x >= row * size + ADDITION - icon + change && x <= row * size + ADDITION - icon + change + icon) {
					closegraph();
					exit = true;
					break;
				}
				else if (x >= row * size + change && x <= row * size + change + icon) {
					closegraph();
					setGame();
					setField();
					playGame();
				}
			}
		}
		if (exit)
			break;
	}
}

int Game::uncoverCell(int x, int y)//打开方格
{
	if (mineArea[x][y] <= 28 && mineArea[x][y] >= 19) {//打开方格，而且代表它们的数组介于19~28之间
		mineArea[x][y] -= 20;//介于-1~8之间
		if (mineArea[x][y] >= 1 && mineArea[x][y] <= 8) {
			putimage(x * size, y * size, &img[mineArea[x][y]]); // mineCount
			openCells++;
			playReleaseCellMusic();
			closeReleaseCellMusic();
		}
		else if (mineArea[x][y] == 0) {
			openCells++;
			uncoverSafeCell(x, y);
			playMoveMusic();
			closeMoveMusic();
		}
		else {
			putimage(x * size, y * size, &img[9]);
			gameLose();
		}
	}
	return mineArea[x][y];
}

int Game::markCell(int x, int y)//插旗
{
	//取消插旗
	if (mineArea[x][y] >= 39) {
		mineArea[x][y] -= 20;
		putimage(x * size, y * size, &img[12]);
		playFlagCellMusic();
		closeFlagCellMusic();
		setFlag--;
	}
	//插旗
	else if (mineArea[x][y] >= 19 && mineArea[x][y] <= 28) {//未插旗
		mineArea[x][y] += 20;
		putimage(x * size, y * size, &img[10]);
		playFlagCellMusic();
		closeFlagCellMusic();
		setFlag++;
	}
	return mineArea[x][y];
}

void Game::uncoverSafeCell(int x, int y)//展开安全格
{
	std::vector<std::pair<int, int>> cellsToOpen;//pair将x和y捆绑在一起
	cellsToOpen.push_back({ x, y });
	mineArea[x][y] = 0;
	putimage(x * size, y * size, &img[0]);

	while (!cellsToOpen.empty()) {
		int x = cellsToOpen.back().first;
		int y = cellsToOpen.back().second;
		cellsToOpen.pop_back();//去掉已经处理的（x, y）
		//防止越界
		int minX = max(x - 1, 0);
		int maxX = min(x + 1, row - 1);
		int minY = max(y - 1, 0);
		int maxY = min(y + 1, col - 1);

		for (int i = minX; i <= maxX; ++i) {
			for (int j = minY; j <= maxY; ++j) {
				if (mineArea[i][j] == 20) {
					mineArea[i][j] = 0;
					putimage(i * size, j * size, &img[0]);
					cellsToOpen.push_back({ i, j });//把（i, j）放在容器末
					openCells++;
				}
				else if (mineArea[i][j] >= 21 && mineArea[i][j] <= 28) {
					mineArea[i][j] -= 20;
					putimage(i * size, j * size, &img[mineArea[i][j]]);
					openCells++;
				}
			}
		}
	}
}

void Game::checkSurroundingMines(int x, int y) {
	int cnt = 0;
	//防止越界
	int minX = max(x - 1, 0);
	int maxX = min(row - 1, x + 1);
	int minY = max(y - 1, 0);
	int maxY = min(col - 1, y + 1);
	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			if (mineArea[i][j] >= 29) {
				cnt++;
			}
		}
	}
	if (cnt == mineArea[x][y]) {
		playMoveMusic();
		closeMoveMusic();
		for (int i = minX; i <= maxX; i++) {
			for (int j = minY; j <= maxY; j++) {
				if (mineArea[i][j] >= 40 || mineArea[i][j] == 19) {
					gameLose();
					playGameLostMusic();
					closeGameLostMusic();
					gameLost = true;
				}
				else if (mineArea[i][j] >= 20 && mineArea[i][j] <= 28) {
					mineArea[i][j] -= 20;
					putimage(i * size, j * size, &img[mineArea[i][j]]);
					openCells++;
					if (mineArea[i][j] == 0) {
						uncoverSafeCell(i, j);
					}
				}
			}
		}
	}
}

bool Game::gameLose()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (mineArea[i][j] == 19) {
				mineArea[i][j] -= 20;
				putimage(i * size, j * size, &img[11]);
			}
			else if (mineArea[i][j] >= 40 && mineArea[i][j] <= 48) {
				mineArea[i][j] -= 40;
				putimage(i * size, j * size, &img[13]);
			}
		}
	}
	putimage(row * size + 0.5 * ADDITION - size, 0, &img[14]);
	stop();//停止计时器
	return 0;
}

bool Game::gameWin()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (mineArea[i][j] == 39 || mineArea[i][j] == 19) {
				putimage(i * size, j * size, &img[11]); // Mine
			}
		}
	}
	putimage(row * size + 0.5 * ADDITION - size, 0, &img[15]);
	stop();//停止计时器
	std::string difficultyLevel[] = { "初级", "中级", "高级" };
	leaderboard.addScore("playerName", difficultyLevel[difficulty - 1], elapsedTimeSeconds);
	leaderboard.saveScores("leaderboard.txt"); // 保存分数到文件
	leaderboard.displayLeaderboard(); // 显示排行榜
	return 0;
}
