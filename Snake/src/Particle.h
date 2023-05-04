#pragma once

constexpr int MAX_NUM = 35;

struct Dot {
	double x, y; // 坐标
	double dx, dy; // x轴和y轴的增量（代替速度）
	double theta; // 发射角度
	double w; // 自旋角速度
	int size; // 粒子大小
	
	void Draw(int camera_x, int camera_y, int r, int g, int b);
};

class Particle {
public:
	int num; // 粒子个数
	Dot dot[MAX_NUM];
	double speed; // 发射速度

	int r, g, b;

	void Init(int food_x, int food_y, int blockSize);
	void Draw(int camera_x, int camera_y, int r, int g, int b);
};
