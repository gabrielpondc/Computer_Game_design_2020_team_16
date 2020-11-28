#pragma once
#include "stdafx.h"
//������
class Robot
{
public:
	double x;
	double y;
	double z;
	double size;
	double angle; //��ʬ��z��ļн�
	int retrogressionFlag; //���˱�ʶ���� 0 - �����ˣ�1 - ����
	int retrogressionTime; //�����ڿ��е�ʱ�� 
	int tryGoToGoalFlag; //�Ƿ�������ʬ����Ŀ���ıƽ������㷨��0 - ��������1 - ����
	bool live; //���� true - ���� ��false - ����
	double fallangle; //������ת�Ƕ�
	bool attackFlag; //�Ƿ񹥻� true - ���� �� false - ������
	double leftAttackHandAngle; //����ʱ����̧��ĽǶ�
	bool leftAttackHandFlag; //����ʱ����̧��ı���� true - ��ʹ�� �� false - ����ʹ��
	double rightAttackHandAngle; //����ʱ����̧��ĽǶ�
	bool rightAttackHandFlag; //����ʱ����̧��ı����
	double attackUpMaxAngle; //����ʱ��̧�����߸߶� true - ��ʹ�� �� false - ����ʹ��
	bool leftAttackFinishFlag; //���ֹ���ʱ�Ƿ���� true - ��ʱ�������
	bool rightAttackFinishFlag; //���ֹ���ʱ�Ƿ���� true - ��ʱ�������

	double ss = 1000; //���ý�ʬ���߳���
	double robotAtX;
	double robotAtY;
	double robotAtZ;
	double rtheta;
	double pace;
	double zstep;
	float rate ;
	double robotToGoalAngle; //��ʬ��Ŀ���ļн�

	int blood;//Ѫ��
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
		float ss = 1000; //���ý�ʬ���߳���
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
	//��ʼλ�ã���С��Ѫ��
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
		ss = 1000; //���ý�ʬ���߳���
		robotAtX = x;
		robotAtY = y;
		robotAtZ = z + ss;
		pace = 4;
		rtheta = 0;
		zstep = 0.1;
		robotToGoalAngle = 0;
	}
	//��
	void drawRobot();
	//�����ƶ�
	void moveToPeople(double px, double py, double pz);
	//����
	void RobotRetrogression(int n);
	//���º���
	void robotFall();
	//����
	void robotAttack(float theta);
	//��ʼ����
	void robotStartAttack();
	//��·�ڶ�
	void peopleRun();
	//void drawRobot();
	void judgeDamage(int damage);
};
