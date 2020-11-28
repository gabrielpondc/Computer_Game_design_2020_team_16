#pragma once
#include "stdafx.h"
//城堡

class Bullet
{
public:
	//位置向量
	float x, y, z;
	//方向向量
	float gx, gy, gz;
	//下一个出现的位置
	float nx, ny, nz;
	float speed = 10;
	Bullet()
	{

	}
	Bullet(float x, float y, float z, float gx, float gy, float gz):x(x),y(y),z(z),gx(gx-x),gy(gy-y),gz(gz-z)
	{

	}
	//画出每个子弹
	void DrawBullet()
	{
		float len = 5;
		glBegin(GL_LINES);
		glColor3f(1, 1, 0);
		glVertex3i(x,y,z); 
		glVertex3i(x+gx*len,y+gy*len,z+gz*len);
		nx = x + gx*speed;
		ny = y + gy*speed;
		nz = z + gz*speed;
		x = nx; y = ny; z = nz;
		glEnd();
	}
	//传来机器人的坐标,判断与子弹是否相撞
	bool JudgeHit(float x, float y, float z, float v)
	{
		float X = this->x, Y = this->y, Z = this->z;
		for (int i = 0; i < speed; i++)
		{
			if (sqrt(pow(x - X, 2) + pow((y + 0.3) - Y, 2) + pow(z - Z, 2)) < v)
			{
				return true;
			}
			X += gx; Y += gy; Z += gz;
		}
		return false;
	}
};

//关卡控制类
class CastleEx
{
public:
	GLuint Interface[3];
	int Pattern;//当前模式
	float time,endTime;//开始的时间
	Scene scene;
	SkyBox skyBox;
	Player player;
	//小僵尸
	vector<Robot> robots;
	int robotNum=0;
	int killRobotNum = 0;
	//飞行中的子弹
	vector<Bullet> bullet;
	CastleEx();
	void Init();
	//判断枪械对机器人受到的伤害
	void GunDamage();
	//判断近战武器对机器人的伤害
	void AxeDamage(float x,float y,float z);
	//画僵尸
	void DrawRobot(float x, float y, float z);
	//生成僵尸
	void generateRobot();
	//一个流程
	void Processing();
	//改变关卡模式
	void ChangePattern(int p);
	//显示当前信息
	void ShowMess();
	//显示开始界面
	void ShowBeging();
	//显示帮助
	void ShowHelp();
	//显示结束
	void ShowEnd();
	//判断机器人是否活着
	void judgeAlive(Robot *r);
};

