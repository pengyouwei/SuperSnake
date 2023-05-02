#include "Particle.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <graphics.h>

#define PI acos(-1)
constexpr double G = 0.001; // �����������ٶ�,ʹ���������µ�������

void Dot::Draw(int camera_x, int camera_y, int r, int g, int b)
{
	setfillcolor(RGB(r, g, b)), setlinecolor(RGB(r, g, b));
	// setfillcolor(RGB(180, 180, 180)), setlinecolor(RGB(180, 180, 180)); // ��ɫ
	fillrectangle(x + camera_x, y + camera_y, x + 10 + camera_x, y + 10 + camera_y);
}

void Particle::Init(int food_x, int food_y, int blockSize)
{
	srand(unsigned(time(0)));

	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

	num = 30;
	for (int i = 0; i < num; i++) {

		speed = rand() % 10 / 10.0; // �ٶ����

		dot[i].x = rand() % blockSize + food_x;
		dot[i].y = rand() % blockSize + food_y;

		dot[i].theta = rand() % 360 / 180.0 * PI; // ��������
		// ���ݷ����ٶȼ��� x ��� y ��ķ��ٶ�
		dot[i].dx = speed * cos(dot[i].theta);
		dot[i].dy = speed * -sin(dot[i].theta);

	}
}

void Particle::Draw(int camera_x, int camera_y, int r, int g, int b)
{
	for (int i = 0; i < num; i++) {
		// ��������仯
		dot[i].x += dot[i].dx;
		dot[i].y += dot[i].dy;

		// ���µ��ٶ�Խ��Խ��
		dot[i].dy += G;

		dot[i].Draw(camera_x, camera_y, r, g, b);
	}
}

