#pragma once
#include "Snake.h"
#include "Food.h"
#include "Particle.h"

constexpr int WIDTH = 1080; // ���ڿ��
constexpr int HEIGHT = 720; // ���ڸ߶�
constexpr int BLOCK_SIZE = 30; // ���巽���С

constexpr int MAX_DELAY = 100; // ��ʱ���ֵ���ٶ�������ʱ��
constexpr int MIN_DELAY = 1;  // ��ʱ��Сֵ���ٶ�����ʱ��

class Game {
private:
	int width;		// ���ڿ��
	int height;		// ���ڸ߶�
	DWORD delay;		// ��ʱ�����ߵ��ٶ�
	int camera_x;   // ��������꣬Ϊ 0 ʱ�ڴ������� 
	int camera_y;   // ��������꣬Ϊ 0 ʱ�ڴ������� 
	bool isShake;    // ���ڶ����Ŀ���
	int shakeTimes; // ����֡��
	int shakeCnt;   // ��¼��������
	int blockSize;  // ��ͷ��С
	int wallSize;   // ǽ�ĺ��
	bool isUpdate;  // �������ݵĿ���
	bool isOver;    // ��Ϸ�Ƿ�����Ŀ���

	Snake* snake;
	Food* food;
	Particle* particle;

	void DrawWall();
	void WindowShake(); // ���ڶ���
	void GameOver(); 

public:
	Game(int width = WIDTH, int height = HEIGHT, int blockSize = BLOCK_SIZE);
	void Init();
	void Play();
	void ShowStartPage();
};