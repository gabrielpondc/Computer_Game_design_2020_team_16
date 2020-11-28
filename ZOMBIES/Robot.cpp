#pragma once

#include "stdafx.h"
#include"Robot.h"

//��ʬ��
#define PI 3.14159

//Robot * robot = new Robot(0, -outer - 4 * inner, -30, 10);

//�������߶�ʱ�ڶ����ֺͽŵĽǶ�
void Robot::peopleRun()
{

	/*if (peopleTheta >= 30 || peopleTheta <= -30)
	pace = -pace;
	peopleTheta += pace;*/


	if (rtheta >= 30 || rtheta <= -30)
		pace = -pace;
	rtheta += pace;

}

//��������
void Robot::drawRobot()
{
	double size = this->size;
	double x = this->x;
	double y = this->y;
	double z = this->z;
	//double colorChangeStep = 0.2;
	//double 
	//����������ͷ  
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//glTranslatef(x, y, z);
	//glTranslatef(robot->x + sin(xangle / 360 * 2 * PI) * 1, robot->y, robot->z - cos(xangle / 360 * 2 * PI) * 1);
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->angle, 0, 1, 0);//����y����ת
	glTranslatef(-(this->x), -(this->y), -(this->z));

	this->robotFall();

	glPushMatrix();
	if (this->retrogressionTime > 0)
	{
		glColor4f(1, 0, 0, 0.1);
	}
	else
	{
		glColor4f(0.41, 0.41, 0.41, 0.2);
	}
	glTranslatef(x + 0 * size, y + 2.5*size, z + 0 * size);
	glScaled(3 * size, 3 * size, 1.35 * size);//--����� //����
	glutSolidCube(1);  //����������ͷ                
	glPopMatrix();

	//if ((this->angle <= 90 && this->angle >= -90) || (this->angle >= 270) || (this->angle <= -270)) //����z����
	//{
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(x + 0.75 * size, y + 3.7*size, z + 0.7 * size);
		glScaled(0.4 * size, 0.4 * size, 0.4 * size);//--����� //����
		glutSolidCube(1);  //�����������۾�              
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(x - 0.75 * size, y + 3.7*size, z + 0.7 * size);
		glScaled(0.4 * size, 0.4 * size, 0.4 * size);//--����� //����
		glutSolidCube(1);  //�������۾�              
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(x - 0 * size, y + 2.9*size, z + 0.7 * size);
		glScaled(1.5 * size, 0.1 * size, 0.1 * size);//--����� //����
		glutSolidCube(1);  //��������             
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(x - 0.75 * size, y + 3.1*size, z + 0.7 * size);
		glScaled(0.15 * size, 0.15 * size, 0.4 * size);//--����� //����
		glutSolidCube(1);  //����������            
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(x + 0.75 * size, y + 3.1*size, z + 0.7 * size);
		glScaled(0.15 * size, 0.15 * size, 0.4 * size);//--����� //����
		glutSolidCube(1);  //����������            
		glPopMatrix();
	//}


	glPushMatrix();
	if (this->retrogressionTime > 0)
	{
		glColor4f(1, 0, 0, 0.1);
	}
	else
	{
		glColor3f(0.51, 0.51, 0.51);
	}
	glTranslatef(x + 0 * size, y - 2 * size, z + 0 * size);
	glRotatef(rtheta, 1, 0, 0);//����x����ת
	glTranslatef(-(x + 0 * size), -(y - 2 * size), -(z + 0 * size));
	glTranslatef(x + 1 * size, y - 3.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--�����
	glutSolidCube(1);  //������������   

					   //����С��


	glPopMatrix();


	glPushMatrix();
	if (this->retrogressionTime > 0)
	{
		glColor4f(1, 0, 0, 0.1);
	}
	else
	{
		glColor3f(0.51, 0.51, 0.51);
	}
	glTranslatef(x + 0 * size, y - 2 * size, z + 0 * size);
	glRotatef(-rtheta, 1, 0, 0);//����x����ת
	glTranslatef(-(x + 0 * size), -(y - 2 * size), -(z + 0 * size));
	glTranslatef(x - 1 * size, y - 3.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--�����
	glutSolidCube(1);  //������������                
	glPopMatrix();

	glPushMatrix();
	if (this->retrogressionTime > 0)
	{
		glColor4f(0.8, 0, 0, 0.6);
	}
	else
	{
		glColor3f(0.31, 0.31, 0.31);
	}
	glTranslatef(x, y, z);
	glScaled(4 * size, 4 * size, 1.4 * size);//--�����
	glutSolidCube(1);  //������������                
	glPopMatrix();

	glPushMatrix();
	if (this->retrogressionTime > 0)
	{
		glColor4f(1, 0, 0, 0.1);
	}
	else
	{
		glColor3f(0.51, 0.51, 0.51);
	}
	glTranslatef(x + 0 * size, y + 2 * size, z + 0 * size);

	if (this->attackFlag == false) //��ʬ������ʱ���������ڶ�
	{
		this->leftAttackHandAngle = rtheta; //�ȳ�ʼ����������ʱ�ĽǶ�
		glRotatef(rtheta, 1, 0, 0);//����x����ת
	}
	else //�ֹ���ʱ����ʬ��������180�Ⱥ��ַ��µ�0��
	{
		this->robotAttack(this->leftAttackHandAngle);
	}
	glTranslatef(-(x + 0 * size), -(y + 2 * size), -(z + 0 * size));
	glTranslatef(x - 2.5*size, y + 0.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--�����
	glutSolidCube(1);  //��������������
	glPopMatrix();


	glPushMatrix();
	if (this->retrogressionTime > 0)
	{
		glColor4f(1, 0, 0, 0.1);
	}
	else
	{
		glColor3f(0.51, 0.51, 0.51);
	}
	glTranslatef(x + 0 * size, y + 2 * size, z + 0 * size);

	if (this->attackFlag == false) //��ʬ������ʱ���������ڶ�
	{
		this->rightAttackHandAngle = -rtheta; //�ȳ�ʼ����������ʱ�ĽǶ�
		glRotatef(-rtheta, 1, 0, 0);//����x����ת
	}
	else //�ֹ���ʱ����ʬ��������180�Ⱥ��ַ��µ�0��
	{
		this->robotAttack(this->rightAttackHandAngle);
	}
	glTranslatef(-(x + 0 * size), -(y + 2 * size), -(z + 0 * size));
	glTranslatef(x + 2.5*size, y + 0.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--�����
	glutSolidCube(1);  //�������������� 

	glPopMatrix();
	glPopMatrix();





}


//���Գ���1
//��ʬ�򶨵��ƶ��㷨            p - people�����ǣ�   Robot - ��ʬ
//void Robot::moveToPeople(double px, double py, double pz)
//{
//	double accuracy = 18; //�����ľ���(18 - �ο���������ʱ�Ϻõ���)��Խ�� - ��Ŀ���ĽǶ�Խ׼ȷ ���Ǿ��Ȳ��ܹ��ͣ�Ҫ���ն�
//	double range = 2; //�ӽ���Χ Խ�� - Խ�ӽ�
//	if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy)) //׷�ٵ�Ŀ�����ӵ��Ŀ�����м�
//	{
//		if (abs(pz - this->z) < range && abs(px - this->x) < range)
//		{
//			//��ʬ�����Ѿ��ӽ���
//			return;
//		}
//	}
//
//	while (true) //��תֱ���ҵ�����
//	{
//		
//		if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy))//����һ��
//		{
//			if (((robotAtX - px)*(px - this->x) >= 0) && ((robotAtZ - pz)*(pz - this->z) >= 0))//׷�ٵ�Ŀ�����ӵ��Ŀ�����м�
//			{
//				break;
//			}
//		}
//		
//		this->angle -= 1;
//		if (this->angle <= -360)
//		{
//			this->angle += 360;
//		}
//		robotAtZ = this->z + cos(this->angle / 360 * 2 * PI)*ss;
//		robotAtX = this->x - sin(this->angle / 360 * 2 * PI)*ss;
//	}
//	//��ʬֱ��
//	double zs = (this->zstep);
//
//	this->z = this->z + cos(angle / 360 * 2 * PI)*zs;
//	this->x = this->x - sin(angle / 360 * 2 * PI)*zs;
//	peopleRun();
//}

//���Գ���2
////��ʬ�򶨵��ƶ��㷨            p - people�����ǣ�   Robot - ��ʬ
//void Robot::moveToPeople(double px, double py, double pz)
//{
//	while (true) //��תֱ���ҵ�����
//	{
//		double accuracy = 18; //�����ľ���(18 - �ο���������ʱ�Ϻõ���)��Խ�� - ��Ŀ���Խ׼ȷ ���Ǿ��Ȳ��ܹ��ͣ�Ҫ���ն�
//		if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy))//����һ��
//		{
//			if (((robotAtX - px)*(px - this->x) >= 0) && ((robotAtZ - pz)*(pz - this->z) >= 0)) //׷�ٵ�Ŀ�����ӵ��Ŀ�����м�
//			{
//				//��ʬ�����Ѿ��ӽ���
//
//				break;
//			}
//		}
//		
//		this->angle -= 1;
//		if (this->angle <= -360)
//		{
//			this->angle += 360;
//		}
//		robotAtZ = this->z + cos(this->angle / 360 * 2 * PI)*ss;
//		robotAtX = this->x - sin(this->angle / 360 * 2 * PI)*ss;
//	}
//	//��ʬֱ��
//	double zs = (this->zstep);
//
//	this->z = this->z + cos(angle / 360 * 2 * PI)*zs;
//	this->x = this->x - sin(angle / 360 * 2 * PI)*zs;
//	peopleRun();
//}
//
//���Գ���3
//��ʬ�򶨵��ƶ��㷨            p - people�����ǣ�   Robot - ��ʬ
//void Robot::moveToPeople(double px, double py, double pz)
//{
//	double accuracy = 48; //�����ľ���(18 - �ο���������ʱ�Ϻõ���)��Խ�� - ��Ŀ���ĽǶ�Խ׼ȷ ���Ǿ��Ȳ��ܹ��ͣ�Ҫ���ն�
//	double range = 2; //�ӽ���Χ Խ�� - Խ�ӽ�
//	if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy)) //׷�ٵ�Ŀ�����ӵ��Ŀ�����м�
//	{
//		if (abs(pz - this->z) < range && abs(px - this->x) < range)
//		{
//			//��ʬ�����Ѿ��ӽ���
//			return;
//		}
//	}
//
//	if ( (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy) && ((robotAtX - px)*(px - this->x) >= 0) && ((robotAtZ - pz)*(pz - this->z) >= 0))//׷�ٵ�Ŀ�����ӵ��Ŀ�����м�
//	{
//		if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy))//����һ�� 
//		{
//			//��ʬ�����Ѿ���������
//			return;
//		}
//
//		//��ʬֱ��
//		double zs = (this->zstep);
//
//		this->z = this->z + cos(angle / 360 * 2 * PI)*zs;
//		this->x = this->x - sin(angle / 360 * 2 * PI)*zs;
//		peopleRun();	
//	}
//	else
//	{
//		this->angle -= 1;
//		if (this->angle <= -360)
//		{
//			this->angle += 360;
//		}
//		robotAtZ = this->z + cos(this->angle / 360 * 2 * PI)*ss;
//		robotAtX = this->x - sin(this->angle / 360 * 2 * PI)*ss;
//	}
//	
//}

void Robot::moveToPeople(double px, double py, double pz)
{
	//this->robotToGoal = (atan(0.5) / 3.14) * 180;



	double xDifferenceValue = abs(px - this->x);
	double zDifferenceValue = abs(pz - this->z);

	//�Ի�����Ϊ���ĵ� z��Ϊ0�ȣ���ʱ�� ��������ϵ
	if (pz > this->z && px >= this->x)//��һ����
	{
		this->robotToGoalAngle = (atan(xDifferenceValue / zDifferenceValue) / PI) * 180;//��н�
		this->robotToGoalAngle += 0;//�������޽�
	}
	else if (pz < this->z && px > this->x) //�ڶ�����
	{
		this->robotToGoalAngle = (atan(zDifferenceValue / xDifferenceValue) / PI) * 180; //��н�
		this->robotToGoalAngle += 90;//�������޽�
	}
	else if (pz < this->z && px <= this->x)//��������
	{
		this->robotToGoalAngle = (atan(xDifferenceValue / zDifferenceValue) / PI) * 180;//��н�
		this->robotToGoalAngle += 180; //�������޽�
	}
	else if (pz >= this->z && px < this->x)//��������
	{
		this->robotToGoalAngle = (atan(zDifferenceValue / xDifferenceValue) / PI) * 180; //��н�
		this->robotToGoalAngle += 270; //�������޽�
	}



	if (this->robotToGoalAngle >= 360)
	{
		this->robotToGoalAngle -= 360;
	}
	this->angle = this->robotToGoalAngle; //�ѻ�������z��ļн�ת�� - �Ի�����Ϊ���ĵ� z��Ϊ0�ȣ���ʱ��Ŀ���ļн�

	double zs = (this->zstep);
	this->z = this->z + cos(this->angle / 360 * 2 * PI)*zs*rate;
	this->x = this->x + sin(this->angle / 360 * 2 * PI)*zs*rate;
	peopleRun();
}

//�����˵����㷨  n - �����˵��˵Ĳ��������ڿ��е�ʱ����n ,Robot - ������
void Robot::RobotRetrogression(int n)
{
	//��������˲���ʵ��
	if (this == NULL)
	{
		return;
	}

	//�ж�n�Ƿ�Ϊ����
	if (n % 2 == 1)
	{
		n += 1;//��Ϊż��
	}

	//��ʼ��this��retrogression��ر���
	if (this->retrogressionTime == 0 && this->retrogressionFlag == 1)
	{
		this->retrogressionTime = n;
	}

	float g = 1.0; //�������ٶȣ�����ͨ���޸��������Ƹ߶�

	if (this->retrogressionTime > n / 2) //������ʱ��
	{
		if (true) //����д�޽纯��
		{
			//�������ٶȹ�ʽ������
			this->y = this->y + 0.5 * g * (n - this->retrogressionTime);
			//�Ի�����ת�Ƕ�ȷ�ϻ����˵ķ���
			//���
			float zs = zstep + 0.5; //��󵹵ĵ�λ����/////////////////////////////////////
			this->z = this->z + cos(this->angle / 360 * 2 * PI)*(-zs);
			this->x = this->x + sin(this->angle / 360 * 2 * PI)*(-zs);
		}
		else
		{
			this->retrogressionFlag = 0;
			this->retrogressionTime = 0;
		}
	}
	else //���˵�ʱ��
	{
		if (true) //����д�޽纯��
		{
			//�������ٶȹ�ʽ,�½�
			this->y = this->y - 0.5 * g * ((n - this->retrogressionTime) - n / 2);
			//�Ի�����ת�Ƕ�ȷ�ϻ����˵ķ���
			//���
			float zs = zstep + 1; //��λ����
			this->z = this->z + cos(this->angle / 360 * 2 * PI)*(-zs);
			this->x = this->x + sin(this->angle / 360 * 2 * PI)*(-zs);
		}
		else
		{
			this->retrogressionFlag = 0;
			this->retrogressionTime = 0;
		}
	}

	this->retrogressionTime--;


}

//��ʬ���غ���
void Robot::robotFall()
{
	glTranslatef(this->x, this->y - 5 * this->size, this->z);
	glRotatef(this->fallangle, -1, 0, 0);//����y����ת
	glTranslatef(-(this->x), -(this->y - 5 * this->size), -(this->z));
}

//��ʬ��������
void Robot::robotAttack(float theta)
{
	if (this->attackFlag == true) //��ʬ���й���
	{
		glRotatef(-theta, 1, 0, 0);//����x����ת
	}
}

//��ʼ����
void Robot::robotStartAttack()
{
	this->attackFlag = true;
	this->leftAttackFinishFlag = false;
	this->rightAttackFinishFlag = false;
	this->leftAttackHandFlag = false;
	this->rightAttackHandFlag = false;
}

//�ж��˺�
void  Robot::judgeDamage(int damage)
{
	blood -= damage;
}