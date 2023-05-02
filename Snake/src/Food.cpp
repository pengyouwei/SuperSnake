#include "Food.h"
#include <cstdlib>
#include <ctime>
#include <graphics.h>


void Food::Init(int width, int height, int blockSize, int wallSize)
{
	srand(unsigned(time(0)));

	size = blockSize;
	// ʳ���ʼ����
	x = wallSize + blockSize * (rand() % ((width - blockSize) / blockSize));
	y = wallSize + blockSize * (rand() % ((height - blockSize) / blockSize));
}

void Food::Create(int width, int height, int blockSize, int wallSize, const Snake* snake)
{
	x = wallSize + blockSize * (rand() % ((width - blockSize) / blockSize));
	y = wallSize + blockSize * (rand() % ((height - blockSize) / blockSize));

	// ���ʳ�������Ƿ��������غ�
	for (int i = 0; i < snake->len; i++) {
		if (x == snake->node[i].x && y == snake->node[i].y) {
			Create(width, height, blockSize, wallSize, snake);
		}
	}

	isEaten = false;
}

void Food::Draw(int camera_x, int camera_y)
{
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	setfillcolor(RGB(r, g, b)), setlinecolor(RGB(r, g, b)); // ��ɫ
	// setfillcolor(WHITE), setlinecolor(WHITE); // ��ɫ

	fillrectangle(x + camera_x, y + camera_y, x + size - 1 + camera_x, y + size - 1 + camera_y);
}


