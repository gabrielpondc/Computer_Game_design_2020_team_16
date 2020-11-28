#pragma once
#include "stdafx.h"
//机器人
class Robot
{
public:
	double x;
	double y;
	double z;
	double size;
	double angle; //僵尸与z轴的夹角
	int retrogressionFlag; //倒退标识变量 0 - 不后退，1 - 后退
	int retrogressionTime; //倒飞在空中的时间 
	int tryGoToGoalFlag; //是否启动僵尸到达目标点的逼近跟着算法，0 - 不出发，1 - 出发
	bool live; //生命 true - 生存 ，false - 死亡
	double fallangle; //倒地旋转角度
	bool attackFlag; //是否攻击 true - 攻击 ， false - 不攻击
	double leftAttackHandAngle; //攻击时左手抬起的角度
	bool leftAttackHandFlag; //攻击时左手抬起的标记量 true - 在使用 ， false - 不在使用
	double rightAttackHandAngle; //攻击时右手抬起的角度
	bool rightAttackHandFlag; //攻击时右手抬起的标记量
	double attackUpMaxAngle; //攻击时手抬起的最高高度 true - 在使用 ， false - 不在使用
	bool leftAttackFinishFlag; //左手攻击时是否完成 true - 这时攻击完成
	bool rightAttackFinishFlag; //右手攻击时是否完成 true - 这时攻击完成

	double ss = 1000; //设置僵尸视线长度
	double robotAtX;
	double robotAtY;
	double robotAtZ;
	double rtheta;
	double pace;
	double zstep;
	float rate ;
	double robotToGoalAngle; //僵尸与目标点的夹角

	int blood;//血量
	int atk = 2;
	Robot()
	{
		x = 0;
		y = 1;
		z = 1;
		size = 1;
		angle = 0;
		retrogressionFlag = 0;
		retrogressionTime = 0;
		tryGoToGoalFlag = 1;
		live = true;
		fallangle = 0;
		attackFlag = false;
		leftAttackHandAngle = 0;
		rightAttackHandAngle = 0;
		attackUpMaxAngle = 180;
		leftAttackHandFlag = false;
		rightAttackHandFlag = false;
		leftAttackFinishFlag = false;
		rightAttackFinishFlag = false;
		float ss = 1000; //设置僵尸视线长度
		float robotAtX = x;
		float robotAtY = y;
		float robotAtZ = z + ss;
		pace = 4;
		rtheta = 0;
		zstep = 0.1;
		robotToGoalAngle = 0;
		blood = 100;
		rate = 1;
	}
	//初始位置，大小，血量
	Robot(double x, double y, double z, double size,int blood,float rate)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->size = size;
		this->blood = blood;
		this->rate = rate;
		angle = 0;
		retrogressionFlag = 0;
		retrogressionTime = 0;
		tryGoToGoalFlag = 1;
		live = true;
		fallangle = 0;
		attackFlag = false;
		leftAttackHandAngle = 0;
		rightAttackHandAngle = 0;
		attackUpMaxAngle = 180;
		leftAttackHandFlag = false;
		rightAttackHandFlag = false;
		leftAttackFinishFlag = false;
		rightAttackFinishFlag = false;
		ss = 1000; //设置僵尸视线长度
		robotAtX = x;
		robotAtY = y;
		robotAtZ = z + ss;
		pace = 4;
		rtheta = 0;
		zstep = 0.1;
		robotToGoalAngle = 0;
	}
	//画
	void drawRobot();
	//跟踪移动
	void moveToPeople(double px, double py, double pz);
	//后退
	void RobotRetrogression(int n);
	//倒下函数
	void robotFall();
	//攻击
	void robotAttack(float theta);
	//开始攻击
	void robotStartAttack();
	//走路摆动
	void peopleRun();
	//void drawRobot();
	void judgeDamage(int damage);
};
