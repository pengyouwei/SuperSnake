#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include <conio.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

COLORREF WALL_COLOR = COLORREF RGB(100, 100, 100); // 墙壁颜色

void Game::DrawWall()
{
	setfillcolor(WALL_COLOR);
	setlinecolor(WALL_COLOR);
	fillrectangle(0 + camera_x, 0 + camera_y, width - 1 + camera_x, wallSize - 1 + camera_y);
	fillrectangle(0 + camera_x, height - 1 - wallSize + camera_y, width - 1 + camera_x, height - 1 + camera_y);
	fillrectangle(0 + camera_x, 0 + camera_y, wallSize - 1 + camera_x, height - 1 + camera_y);
	fillrectangle(width - 1 - wallSize + camera_x, 0 + camera_y, width - 1 + camera_x, height - 1 + camera_y);
}

void Game::WindowShake()
{
	if (isShake == false) return;
	if (shakeCnt < shakeTimes) {
		camera_x = rand() % 30 - wallSize;
		camera_y = rand() % 30 - wallSize;
		shakeCnt++;
	}
	else {
		camera_x = 0;
		camera_y = 0;
	}
}

void Game::GameOver()
{
	isShake = true;

	settextcolor(WHITE);
	settextstyle(90, 50, "Consolas");
	RECT r = { 0, 0, WIDTH, HEIGHT };
	

	while (1) {
		if (_kbhit()) {
			char k = _getch();
			if (k == 13) {
				delete snake;
				delete food;
				delete particle;
				Init();
				break;
			}
		}

		if (isShake) {
			shakeCnt = 0;
			WindowShake();
		}

		BeginBatchDraw();

		cleardevice();
		snake->Draw(camera_x, camera_y);
		food->Draw(camera_x, camera_y);
		DrawWall();
		drawtext("GAME OVER", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		EndBatchDraw();
	}
}

Game::Game(int width, int height, int blockSize)
{
	this->width = width;
	this->height = height;
	this->delay = MAX_DELAY;
	this->blockSize = blockSize;
	this->shakeTimes = 150;
	this->shakeCnt = 0;
	this->isShake = false;
	this->wallSize = blockSize / 2;
	this->camera_x = 0;
	this->camera_y = 0;
	this->snake = nullptr;
	this->food = nullptr;
	this->particle = nullptr;
	this->isUpdate = false;
	this->isOver = false;
}

void Game::Init()
{
	delay = MAX_DELAY;
	camera_x = 0;
	camera_y = 0;
	shakeTimes = 150;
	shakeCnt = 0;
	isShake = false;
	isUpdate = false;
	isOver = false;

	srand(unsigned(time(0)));

	snake = new Snake;
	snake->Init(blockSize, wallSize);

	food = new Food;
	food->Init(width, height, blockSize, wallSize);

	particle = new Particle;
	particle->Init(food->x, food->y, blockSize);

	// 初始化一个窗口
	initgraph(width, height);
	cleardevice();
	// 画墙壁
	DrawWall();
	// 背景音乐
	mciSendString("play assets/bk.mp3 repeat", 0, 0, 0);
}

void Game::Play()
{
	// 开始界面
	ShowStartPage();

	// 游戏初始化
	Init();
	
	DWORD t1, t2;
	t1 = t2 = GetTickCount();

	while (1) {
		
		snake->Turn();

		t2 = GetTickCount();
		if (t2 - t1 > delay) { //使游戏非堵塞延时
			t1 = t2;
			snake->Move(blockSize, wallSize, width, height, isShake, shakeCnt, isOver, food->x, food->y, food->isEaten, delay);
		}

		if (food->isEaten) {
			particle->Init(food->x, food->y, blockSize);
			food->Create(width, height, blockSize, wallSize, snake);
		}

		if (isShake) {
			WindowShake();
		}
		
		if (isOver) {
			GameOver();
		}


		BeginBatchDraw();

		cleardevice();
		snake->Draw(camera_x, camera_y); // 画蛇
		food->Draw(camera_x, camera_y);  // 画食物
		if (snake->len > 3) {            // 画粒子
			particle->Draw(camera_x, camera_y, particle->r, particle->g, particle->b);
		}
		DrawWall();
		
		EndBatchDraw();

	}
}

void Game::ShowStartPage()
{
	initgraph(1080, 608);

	IMAGE imshow;
	loadimage(&imshow, "assets/cover.png");
	putimage(0, 0, &imshow);

	// mciSendString("open assets/start.mp3", 0, 0, 0);
	// mciSendString("play assets/start.mp3 repeat", 0, 0, 0);

	settextcolor(RGB(120, 109, 105));
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfItalic = true;
	f.lfQuality = ANTIALIASED_QUALITY; // 字体抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Arial Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT); // 字体背景透明
	outtextxy(580, 540, "按任意键继续...");

	char k;
	while (!_kbhit()) {}
	k = _getch();

	// mciSendString("close assets/start.mp3", 0, 0, 0);

	closegraph();

}
