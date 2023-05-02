#pragma once

constexpr int MAX_NUM = 35;

struct Dot {
	double x, y; // ����
	double dx, dy; // x���y��������������ٶȣ�
	double theta; // ����Ƕ�
	double w; // �������ٶ�

	void Draw(int camera_x, int camera_y, int r, int g, int b);
};

class Particle {
public:
	int num; // ���Ӹ���
	Dot dot[MAX_NUM];
	double speed; // �����ٶ�

	int r, g, b;

	void Init(int food_x, int food_y, int blockSize);
	void Draw(int camera_x, int camera_y, int r, int g, int b);
};