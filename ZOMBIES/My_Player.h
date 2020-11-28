#pragma once
#include "stdafx.h"
#include"My_Camera.h"
//大棒 玩家
class Sword
{
public:
	float r ;
	float step;//挥击速度
	int hitting=0;
	int damage = 80;
	//画一个圆柱
	void cyLinder(float x0, float y0, float z0, float x1, float y1, float z1);
	void DrawSword(float x, float y, float z, float len);
	//画出来
	void Draw();
	void BeginHit();
};

//手枪
class Pistol
{
public:
	float r;
	float step;//挥击速度
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
	float step;//挥击速度
	int damage = 34;
	//是否在连射
	int shotting = 0;
	//连射间隔 
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
//玩家
class Player
{
public:
	//控制视角
	Camera camera;
	//血条
	float blood;
	//武器 1斧头2手枪3机关枪
	int weapon;
	Sword sword;
	Pistol pistol;
	AK47 ak47;
	Player();
	void Init();
	//攻击武器显示
	void ShowAttRange();
	float attackedcolor, attackedcolorstep;
	int attackedcolorI;
	void BeginAttacked();
	void ShowBlood();
};

