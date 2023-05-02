#pragma once
#include <graphics.h>

constexpr int MAX_LEN = 800;

// 方向
enum Dir {
	UP, DOWN, LEFT, RIGHT, STOP
};
// 蛇节点
struct Node {
	int x; // 坐标
	int y;
	int size; // 大小
	COLORREF color; // 颜色
	
	void Draw(int x, int y, int size, COLORREF color, int camera_x, int camera_y, int headSize);
};
// 蛇
class Snake {
private:
	int headSize; // 蛇头大小
	int tailSize; // 蛇尾大小
	COLORREF headColor; // 蛇头颜色
	COLORREF tailColor; // 蛇尾颜色
	Dir dir; // 方向
	

public:
	int len; // 长度
	Node node[MAX_LEN];

	void Init(int blockSize, int wallSize);
	void Draw(int camera_x, int camera_y);
	void Move(int blockSize, int wallSize, int width, int height, bool& isShake, int& shakeCnt, bool& isOver, int food_x, int food_y, bool& isEaten, DWORD& delay);
	void Turn();
	void Stop();
};