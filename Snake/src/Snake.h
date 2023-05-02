#pragma once
#include <graphics.h>

constexpr int MAX_LEN = 800;

// ����
enum Dir {
	UP, DOWN, LEFT, RIGHT, STOP
};
// �߽ڵ�
struct Node {
	int x; // ����
	int y;
	int size; // ��С
	COLORREF color; // ��ɫ
	
	void Draw(int x, int y, int size, COLORREF color, int camera_x, int camera_y, int headSize);
};
// ��
class Snake {
private:
	int headSize; // ��ͷ��С
	int tailSize; // ��β��С
	COLORREF headColor; // ��ͷ��ɫ
	COLORREF tailColor; // ��β��ɫ
	Dir dir; // ����
	

public:
	int len; // ����
	Node node[MAX_LEN];

	void Init(int blockSize, int wallSize);
	void Draw(int camera_x, int camera_y);
	void Move(int blockSize, int wallSize, int width, int height, bool& isShake, int& shakeCnt, bool& isOver, int food_x, int food_y, bool& isEaten, DWORD& delay);
	void Turn();
	void Stop();
};