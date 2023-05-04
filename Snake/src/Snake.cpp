#include "Snake.h"
#include <conio.h>
#include "Game.h"
#include "Food.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int rush_distance = 10;

void Snake::Init(int blockSize, int wallSize)
{
	len = 3;
	dir = RIGHT; // 初始方向
	headSize = blockSize;
	tailSize = headSize / 3 * 2;
	headColor = COLORREF RGB(255, 0, 0);
	tailColor = COLORREF RGB(50, 50, 200);

	// 蛇头单独初始化
	node[0].x = wallSize + blockSize * (len - 1);
	node[0].y = wallSize;
	node[0].size = blockSize;
	node[0].color = headColor;
	node[len - 1].color = tailColor; // 蛇尾颜色提前设置好
	node[len - 1].size = tailSize;   // 蛇尾大小提前设置好
	// 蛇的身体初始化
	for (int i = 1; i < len; i++) {
		node[i].x = node[i - 1].x - blockSize;
		node[i].y = wallSize;
		// 计算颜色和大小
		if (i < len - 1) {
			int rp = (GetRValue(headColor) - GetRValue(tailColor)) / (len - 1);
			int gp = (GetGValue(headColor) - GetGValue(tailColor)) / (len - 1);
			int bp = (GetBValue(headColor) - GetBValue(tailColor)) / (len - 1);
			
			int r = GetRValue(headColor) - i * rp;
			int g = GetGValue(headColor) - i * gp;
			int b = GetBValue(headColor) - i * bp;

			node[i].color = COLORREF RGB(r, g, b);

			node[i].size = headSize - i * (headSize - tailSize) / (len - 1);
		}
	}
}

void Node::Draw(int x, int y, int size, COLORREF color, int camera_x, int camera_y, int headSize)
{
	int d = (headSize - size) / 2; // 偏移量，方便把方块放在正中间
	setfillcolor(color), setlinecolor(color);
	fillrectangle(x + camera_x + d, y + camera_y + d, x + size - 1 + camera_x + d, y + size - 1 + camera_y + d);
}

void Snake::Draw(int camera_x, int camera_y)
{
	for (int i = 0; i < len; i++) {
		int x = node[i].x;
		int y = node[i].y;
		int size = node[i].size;
		COLORREF color = node[i].color;
		node[i].Draw(x, y, size, color, camera_x, camera_y, headSize);
	}
}
// 蛇蛇动起来
void Snake::Move(int blockSize, int wallSize, int width, int height, bool& isShake, int& shakeCnt, bool& isOver, int food_x, int food_y, bool& isEaten, DWORD& delay)
{
	// 更新蛇身体坐标
	for (int i = len - 1; i > 0; i--) {
		node[i].x = node[i - 1].x;
		node[i].y = node[i - 1].y;
	}
	

	// 判断蛇头方向, 并且接近食物时冲过去
	switch (dir) {
	case UP:
		node[0].y -= blockSize;
		if (node[0].y < wallSize) node[0].y = height - wallSize - blockSize;
		if ((node[0].x == food_x) && (node[0].y - food_y > 0) && (node[0].y - food_y < blockSize * rush_distance)) delay = MIN_DELAY;
		break;
	case DOWN:
		node[0].y += blockSize;
		if (node[0].y >= height - wallSize) node[0].y = wallSize;
		if ((node[0].x == food_x) && (food_y - node[0].y > 0) && (food_y - node[0].y < blockSize * rush_distance)) delay = MIN_DELAY;
		break;
	case LEFT:
		node[0].x -= blockSize;
		if (node[0].x < wallSize) node[0].x = width - wallSize - blockSize;
		if ((node[0].y == food_y) && (node[0].x - food_x > 0) && (node[0].x - food_x < blockSize * rush_distance)) delay = MIN_DELAY;
		break;
	case RIGHT:
		node[0].x += blockSize;
		if (node[0].x >= width - wallSize) node[0].x = wallSize;
		if ((node[0].y == food_y) && (food_x - node[0].x > 0) && (food_x - node[0].x < blockSize * rush_distance)) delay = MIN_DELAY;
		break;
	case STOP: break;
	}

	// 检测是否咬到自己
	for (int i = 4; i < len; i++) {
		if (node[0].x == node[i].x && node[0].y == node[i].y) {
			isShake = true;
			isOver = true;
		}
	}

	// 检测是否吃到食物
	if (node[0].x == food_x && node[0].y == food_y) {
		shakeCnt = 0;
		isShake = true; // 打开抖动开关
		isEaten = true;
		delay = MAX_DELAY; // 恢复速度

		if (len < MAX_LEN) len++;

		mciSendString("play assets/eat.wav", 0, 0, 0);

		// 蛇变长后需要重新计算每节的大小和颜色
		node[len - 1].color = tailColor; 
		node[len - 1].size = tailSize;   
		for (int i = 1; i < len; i++) {
			if (i < len - 1) {
				int rp = (GetRValue(headColor) - GetRValue(tailColor)) / (len - 1);
				int gp = (GetGValue(headColor) - GetGValue(tailColor)) / (len - 1);
				int bp = (GetBValue(headColor) - GetBValue(tailColor)) / (len - 1);

				int r = GetRValue(headColor) - i * rp;
				int g = GetGValue(headColor) - i * gp;
				int b = GetBValue(headColor) - i * bp;

				node[i].color = COLORREF RGB(r, g, b);

				node[i].size = headSize - i * (headSize - tailSize) / (len - 1);
			}
		}
	}
}
// 蛇蛇转向
void Snake::Turn()
{
	char k;
	if (_kbhit()) {
		k = _getch();
		switch (k)
		{
		case 'w': if (dir != DOWN) dir = UP; break;
		case 's': if (dir != UP) dir = DOWN; break;
		case 'a': if (dir != RIGHT) dir = LEFT; break;
		case 'd': if (dir != LEFT) dir = RIGHT; break;
		case ' ': Stop();
		}
	}
}
// 空格暂停
void Snake::Stop()
{
	settextcolor(WHITE);
	settextstyle(90, 50, "Consolas");
	RECT r = { 0, 0, WIDTH, HEIGHT };
	drawtext("GAME PAUSE", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	mciSendString("stop bkmusic", 0, 0, 0);

	while (1) {
		if (_kbhit()) {
			char k = _getch();
			if (k == ' ') {
				mciSendString("play bkmusic", 0, 0, 0);
				break;
			}
		}
	}
}


