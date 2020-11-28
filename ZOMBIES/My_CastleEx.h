#pragma once
#include "stdafx.h"
//�Ǳ�

class Bullet
{
public:
	//λ������
	float x, y, z;
	//��������
	float gx, gy, gz;
	//��һ�����ֵ�λ��
	float nx, ny, nz;
	float speed = 10;
	Bullet()
	{

	}
	Bullet(float x, float y, float z, float gx, float gy, float gz):x(x),y(y),z(z),gx(gx-x),gy(gy-y),gz(gz-z)
	{

	}
	//����ÿ���ӵ�
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
	//���������˵�����,�ж����ӵ��Ƿ���ײ
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

//�ؿ�������
class CastleEx
{
public:
	GLuint Interface[3];
	int Pattern;//��ǰģʽ
	float time,endTime;//��ʼ��ʱ��
	Scene scene;
	SkyBox skyBox;
	Player player;
	//С��ʬ
	vector<Robot> robots;
	int robotNum=0;
	int killRobotNum = 0;
	//�����е��ӵ�
	vector<Bullet> bullet;
	CastleEx();
	void Init();
	//�ж�ǹе�Ի������ܵ����˺�
	void GunDamage();
	//�жϽ�ս�����Ի����˵��˺�
	void AxeDamage(float x,float y,float z);
	//����ʬ
	void DrawRobot(float x, float y, float z);
	//���ɽ�ʬ
	void generateRobot();
	//һ������
	void Processing();
	//�ı�ؿ�ģʽ
	void ChangePattern(int p);
	//��ʾ��ǰ��Ϣ
	void ShowMess();
	//��ʾ��ʼ����
	void ShowBeging();
	//��ʾ����
	void ShowHelp();
	//��ʾ����
	void ShowEnd();
	//�жϻ������Ƿ����
	void judgeAlive(Robot *r);
};

