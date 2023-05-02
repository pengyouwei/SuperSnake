#pragma once
#include "Snake.h"
#include "Food.h"
#include "Particle.h"

constexpr int WIDTH = 1080; // 窗口宽度
constexpr int HEIGHT = 720; // 窗口高度
constexpr int BLOCK_SIZE = 30; // 定义方块大小

constexpr int MAX_DELAY = 100; // 延时最大值，速度最慢的时候
constexpr int MIN_DELAY = 1;  // 延时最小值，速度最快的时候

class Game {
private:
	int width;		// 窗口宽度
	int height;		// 窗口高度
	DWORD delay;		// 延时控制蛇的速度
	int camera_x;   // 相机横坐标，为 0 时在窗口中央 
	int camera_y;   // 相机纵坐标，为 0 时在窗口中央 
	bool isShake;    // 窗口抖动的开关
	int shakeTimes; // 抖动帧数
	int shakeCnt;   // 记录抖动次数
	int blockSize;  // 蛇头大小
	int wallSize;   // 墙的厚度
	bool isUpdate;  // 更新数据的开关
	bool isOver;    // 游戏是否结束的开关

	Snake* snake;
	Food* food;
	Particle* particle;

	void DrawWall();
	void WindowShake(); // 窗口抖动
	void GameOver(); 

public:
	Game(int width = WIDTH, int height = HEIGHT, int blockSize = BLOCK_SIZE);
	void Init();
	void Play();
	void ShowStartPage();
};