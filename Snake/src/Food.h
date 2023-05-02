#pragma once
#include "Snake.h"

class Food {
public:
	int x; // ����
	int y;
	int size;
	bool isEaten; // �Ƿ񱻳�

	void Init(int width, int height, int blockSize, int wallSize);
	void Create(int width, int height, int blockSize, int wallSize, const Snake* snake);
	void Draw(int camera_x, int camera_y);
};