#pragma once
#include "stdafx.h"
#include"My_Camera.h"
//��� ���
class Sword
{
public:
	float r ;
	float step;//�ӻ��ٶ�
	int hitting=0;
	int damage = 80;
	//��һ��Բ��
	void cyLinder(float x0, float y0, float z0, float x1, float y1, float z1);
	void DrawSword(float x, float y, float z, float len);
	//������
	void Draw();
	void BeginHit();
};

//��ǹ
class Pistol
{
public:
	float r;
	float step;//�ӻ��ٶ�
	int shotting = 0;
	int damage = 50;
	int bullet=7,bulletNum=0;
	float Bomb_changing, Bomb_chang=2.5, changflag=0;
	GLuint textureid;
	void Init();
	void Draw();
	void BeginShot();

};

//ak47
class AK47
{
public:
	float r;
	float step;//�ӻ��ٶ�
	int damage = 34;
	//�Ƿ�������
	int shotting = 0;
	//������ 
	float shot_interval = 0.1;
	float shot_before;
	int bullet = 30, bulletNum = 0;
	float Bomb_changing, Bomb_chang = 2.5, changflag = 0;
	int shott = 0;
	GLuint textureid;
	void Init();
	void Draw();
	void BeginShot();
};
//���
class Player
{
public:
	//�����ӽ�
	Camera camera;
	//Ѫ��
	float blood;
	//���� 1��ͷ2��ǹ3����ǹ
	int weapon;
	Sword sword;
	Pistol pistol;
	AK47 ak47;
	Player();
	void Init();
	//����������ʾ
	void ShowAttRange();
	float attackedcolor, attackedcolorstep;
	int attackedcolorI;
	void BeginAttacked();
	void ShowBlood();
};

