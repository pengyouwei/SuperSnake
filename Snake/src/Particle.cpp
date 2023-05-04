#include "Particle.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <graphics.h>

#define PI acos(-1)
constexpr double G = 0.001; // 类似重力加速度,使粒子有向下掉的趋势

void Dot::Draw(int camera_x, int camera_y, int r, int g, int b)
{
	setfillcolor(RGB(r, g, b)), setlinecolor(RGB(r, g, b));
	// setfillcolor(RGB(180, 180, 180)), setlinecolor(RGB(180, 180, 180)); // 白色
	fillrectangle(x + camera_x, y + camera_y, x + size + camera_x, y + size + camera_y);
}

void Particle::Init(int food_x, int food_y, int blockSize)
{
	srand(unsigned(time(0)));

	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

	num = 30;
	for (int i = 0; i < num; i++) {

		speed = rand() % 10 / 10.0; // 速度随机

		dot[i].x = rand() % blockSize + food_x;
		dot[i].y = rand() % blockSize + food_y;

		dot[i].theta = rand() % 360 / 180.0 * PI; // 发射角随机
		// 根据发射速度计算 x 轴和 y 轴的分速度
		dot[i].dx = speed * cos(dot[i].theta);
		dot[i].dy = speed * -sin(dot[i].theta);
		
		// dot[i].size = 10;
		dot[i].size = rand() % 10 + 5; // 粒子大小随机

	}
}

void Particle::Draw(int camera_x, int camera_y, int r, int g, int b)
{
	for (int i = 0; i < num; i++) {
		// 坐标持续变化
		dot[i].x += dot[i].dx;
		dot[i].y += dot[i].dy;

		// 向下的速度越来越快
		dot[i].dy += G;

		dot[i].Draw(camera_x, camera_y, r, g, b);
	}
}

