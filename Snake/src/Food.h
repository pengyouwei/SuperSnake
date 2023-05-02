#pragma once
#include "Snake.h"

class Food {
public:
	int x; // ×ø±ê
	int y;
	int size;
	bool isEaten; // ÊÇ·ñ±»³Ô

	void Init(int width, int height, int blockSize, int wallSize);
	void Create(int width, int height, int blockSize, int wallSize, const Snake* snake);
	void Draw(int camera_x, int camera_y);
};