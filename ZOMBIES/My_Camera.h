#pragma once
#include "stdafx.h"
//摄像头头文件
class Camera
{
public:
	//方位角
	float angleX = 0.0, angleXupdown = 0.0;
	//俯仰角
	float angleY = 0.0, angleYupdown = 0.0;
	//相当于人的高度
	float height;
	float x = 350.0f, y = 5, z = 350.0f;
	float lx = 0.0f, ly = 0.0f, lz = -1.0f;
	//进行攻击方向判断的重要参数
	float X ,Y , Z ;
	float LX , LY , LZ ;

	float TheAngle = 0.0;
	float TheMove = 0.0;
	float TheMoveAround = 0.0;
	float TheAngleUPDown = 0.0;
	Terrain *terrain;

	float soundbefo=0,soundstep=0.1;
	
	/************移动相关***********/
	//震动系数
	float shock = 0, shock_step=0.01;
	//跳跃系数
	float jumping=0,jump = 0, jump_v = 0,jump_a= 0.01;
	//移动状态 0静静地动 1动动地动
	int moveState=0;
	//移动速度
	float speed ;
	//改变状态
	void changeState(int state);
	//有起伏地移动
	void Walking();
	//没有起伏的移动
	void Stoping();
	//跳起来了的移动
	void Jumping();
	//上帝视角飞行
	void Flying();
	//每盘改变视角的入口
	void ChangeCamera();
	//个人移动的方向前后
	void ChangeMoveDirectFB(float frontBack);
	//个人移动的方向左右
	void ChangeMoveDirectLR(float LeftRight);
	//开始跳初始化
	void BeginJump();
	//鼠标控制看别的地方的速度
	void ChangeSideRate(int x, int y);
	void AddangleY(float they);
};