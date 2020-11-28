#pragma once

#include "stdafx.h"
#include"Robot.h"

//僵尸类
#define PI 3.14159

//Robot * robot = new Robot(0, -outer - 4 * inner, -30, 10);

//机器人走动时摆动的手和脚的角度
void Robot::peopleRun()
{

	/*if (peopleTheta >= 30 || peopleTheta <= -30)
	pace = -pace;
	peopleTheta += pace;*/


	if (rtheta >= 30 || rtheta <= -30)
		pace = -pace;
	rtheta += pace;

}

//画机器人
void Robot::drawRobot()
{
	double size = this->size;
	double x = this->x;
	double y = this->y;
	double z = this->z;
	//double colorChangeStep = 0.2;
	//double 
	//绘制立方体头  
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//glTranslatef(x, y, z);
	//glTranslatef(robot->x + sin(xangle / 360 * 2 * PI) * 1, robot->y, robot->z - cos(xangle / 360 * 2 * PI) * 1);
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->angle, 0, 1, 0);//绕着y轴旋转
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
	glScaled(3 * size, 3 * size, 1.35 * size);//--搞清楚 //缩放
	glutSolidCube(1);  //绘制立方体头                
	glPopMatrix();

	//if ((this->angle <= 90 && this->angle >= -90) || (this->angle >= 270) || (this->angle <= -270)) //脸朝z方向
	//{
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(x + 0.75 * size, y + 3.7*size, z + 0.7 * size);
		glScaled(0.4 * size, 0.4 * size, 0.4 * size);//--搞清楚 //缩放
		glutSolidCube(1);  //绘制立方体眼睛              
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(x - 0.75 * size, y + 3.7*size, z + 0.7 * size);
		glScaled(0.4 * size, 0.4 * size, 0.4 * size);//--搞清楚 //缩放
		glutSolidCube(1);  //绘制立眼睛              
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(x - 0 * size, y + 2.9*size, z + 0.7 * size);
		glScaled(1.5 * size, 0.1 * size, 0.1 * size);//--搞清楚 //缩放
		glutSolidCube(1);  //绘制立嘴             
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(x - 0.75 * size, y + 3.1*size, z + 0.7 * size);
		glScaled(0.15 * size, 0.15 * size, 0.4 * size);//--搞清楚 //缩放
		glutSolidCube(1);  //绘制立牙齿            
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(x + 0.75 * size, y + 3.1*size, z + 0.7 * size);
		glScaled(0.15 * size, 0.15 * size, 0.4 * size);//--搞清楚 //缩放
		glutSolidCube(1);  //绘制立牙齿            
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
	glRotatef(rtheta, 1, 0, 0);//绕着x轴旋转
	glTranslatef(-(x + 0 * size), -(y - 2 * size), -(z + 0 * size));
	glTranslatef(x + 1 * size, y - 3.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--搞清楚
	glutSolidCube(1);  //绘制立方体腿   

					   //绘制小腿


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
	glRotatef(-rtheta, 1, 0, 0);//绕着x轴旋转
	glTranslatef(-(x + 0 * size), -(y - 2 * size), -(z + 0 * size));
	glTranslatef(x - 1 * size, y - 3.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--搞清楚
	glutSolidCube(1);  //绘制立方体腿                
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
	glScaled(4 * size, 4 * size, 1.4 * size);//--搞清楚
	glutSolidCube(1);  //绘制立方体身                
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

	if (this->attackFlag == false) //僵尸不攻击时，手正常摆动
	{
		this->leftAttackHandAngle = rtheta; //先初始化攻击左手时的角度
		glRotatef(rtheta, 1, 0, 0);//绕着x轴旋转
	}
	else //手攻击时，僵尸手上升到180度后又放下到0度
	{
		this->robotAttack(this->leftAttackHandAngle);
	}
	glTranslatef(-(x + 0 * size), -(y + 2 * size), -(z + 0 * size));
	glTranslatef(x - 2.5*size, y + 0.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--搞清楚
	glutSolidCube(1);  //绘制立方体左手
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

	if (this->attackFlag == false) //僵尸不攻击时，手正常摆动
	{
		this->rightAttackHandAngle = -rtheta; //先初始化攻击右手时的角度
		glRotatef(-rtheta, 1, 0, 0);//绕着x轴旋转
	}
	else //手攻击时，僵尸手上升到180度后又放下到0度
	{
		this->robotAttack(this->rightAttackHandAngle);
	}
	glTranslatef(-(x + 0 * size), -(y + 2 * size), -(z + 0 * size));
	glTranslatef(x + 2.5*size, y + 0.5*size, z + 0 * size);
	glScaled(1 * size, 3 * size, 1.4 * size);//--搞清楚
	glutSolidCube(1);  //绘制立方体右手 

	glPopMatrix();
	glPopMatrix();





}


//测试程序1
//僵尸向定点移动算法            p - people（主角）   Robot - 僵尸
//void Robot::moveToPeople(double px, double py, double pz)
//{
//	double accuracy = 18; //搜索的精度(18 - 参考量，测试时较好的量)，越低 - 离目标点的角度越准确 但是精度不能过低，要把握度
//	double range = 2; //接近范围 越低 - 越接近
//	if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy)) //追踪的目标在视点和目标点的中间
//	{
//		if (abs(pz - this->z) < range && abs(px - this->x) < range)
//		{
//			//僵尸方向已经接近人
//			return;
//		}
//	}
//
//	while (true) //旋转直到找到对象
//	{
//		
//		if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy))//三点一线
//		{
//			if (((robotAtX - px)*(px - this->x) >= 0) && ((robotAtZ - pz)*(pz - this->z) >= 0))//追踪的目标在视点和目标点的中间
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
//	//僵尸直走
//	double zs = (this->zstep);
//
//	this->z = this->z + cos(angle / 360 * 2 * PI)*zs;
//	this->x = this->x - sin(angle / 360 * 2 * PI)*zs;
//	peopleRun();
//}

//测试程序2
////僵尸向定点移动算法            p - people（主角）   Robot - 僵尸
//void Robot::moveToPeople(double px, double py, double pz)
//{
//	while (true) //旋转直到找到对象
//	{
//		double accuracy = 18; //搜索的精度(18 - 参考量，测试时较好的量)，越低 - 离目标点越准确 但是精度不能过低，要把握度
//		if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy))//三点一线
//		{
//			if (((robotAtX - px)*(px - this->x) >= 0) && ((robotAtZ - pz)*(pz - this->z) >= 0)) //追踪的目标在视点和目标点的中间
//			{
//				//僵尸方向已经接近人
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
//	//僵尸直走
//	double zs = (this->zstep);
//
//	this->z = this->z + cos(angle / 360 * 2 * PI)*zs;
//	this->x = this->x - sin(angle / 360 * 2 * PI)*zs;
//	peopleRun();
//}
//
//测试程序3
//僵尸向定点移动算法            p - people（主角）   Robot - 僵尸
//void Robot::moveToPeople(double px, double py, double pz)
//{
//	double accuracy = 48; //搜索的精度(18 - 参考量，测试时较好的量)，越低 - 离目标点的角度越准确 但是精度不能过低，要把握度
//	double range = 2; //接近范围 越低 - 越接近
//	if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy) && (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy)) //追踪的目标在视点和目标点的中间
//	{
//		if (abs(pz - this->z) < range && abs(px - this->x) < range)
//		{
//			//僵尸方向已经接近人
//			return;
//		}
//	}
//
//	if ( (((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) > -accuracy) && ((robotAtX - px)*(px - this->x) >= 0) && ((robotAtZ - pz)*(pz - this->z) >= 0))//追踪的目标在视点和目标点的中间
//	{
//		if ((((robotAtZ - pz) * (px - this->x)) - ((pz - this->z) * (robotAtX - px)) < accuracy))//三点一线 
//		{
//			//僵尸方向已经靠近人了
//			return;
//		}
//
//		//僵尸直走
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

	//以机器人为中心点 z轴为0度，逆时针 建立坐标系
	if (pz > this->z && px >= this->x)//第一象限
	{
		this->robotToGoalAngle = (atan(xDifferenceValue / zDifferenceValue) / PI) * 180;//求夹角
		this->robotToGoalAngle += 0;//加上象限角
	}
	else if (pz < this->z && px > this->x) //第二象限
	{
		this->robotToGoalAngle = (atan(zDifferenceValue / xDifferenceValue) / PI) * 180; //求夹角
		this->robotToGoalAngle += 90;//加上象限角
	}
	else if (pz < this->z && px <= this->x)//第三象限
	{
		this->robotToGoalAngle = (atan(xDifferenceValue / zDifferenceValue) / PI) * 180;//求夹角
		this->robotToGoalAngle += 180; //加上象限角
	}
	else if (pz >= this->z && px < this->x)//第四象限
	{
		this->robotToGoalAngle = (atan(zDifferenceValue / xDifferenceValue) / PI) * 180; //求夹角
		this->robotToGoalAngle += 270; //加上象限角
	}



	if (this->robotToGoalAngle >= 360)
	{
		this->robotToGoalAngle -= 360;
	}
	this->angle = this->robotToGoalAngle; //把机器人与z轴的夹角转到 - 以机器人为中心点 z轴为0度，逆时针目标点的夹角

	double zs = (this->zstep);
	this->z = this->z + cos(this->angle / 360 * 2 * PI)*zs*rate;
	this->x = this->x + sin(this->angle / 360 * 2 * PI)*zs*rate;
	peopleRun();
}

//机器人倒退算法  n - 机器人倒退的步伐数，在空中的时间是n ,Robot - 机器人
void Robot::RobotRetrogression(int n)
{
	//如果机器人不是实例
	if (this == NULL)
	{
		return;
	}

	//判断n是否为奇数
	if (n % 2 == 1)
	{
		n += 1;//设为偶数
	}

	//初始化this的retrogression相关变量
	if (this->retrogressionTime == 0 && this->retrogressionFlag == 1)
	{
		this->retrogressionTime = n;
	}

	float g = 1.0; //重力加速度，可以通过修改它来控制高度

	if (this->retrogressionTime > n / 2) //上升的时间
	{
		if (true) //这里写限界函数
		{
			//重力加速度公式，上升
			this->y = this->y + 0.5 * g * (n - this->retrogressionTime);
			//以机器旋转角度确认机器人的方向
			//向后倒
			float zs = zstep + 0.5; //向后倒的单位步长/////////////////////////////////////
			this->z = this->z + cos(this->angle / 360 * 2 * PI)*(-zs);
			this->x = this->x + sin(this->angle / 360 * 2 * PI)*(-zs);
		}
		else
		{
			this->retrogressionFlag = 0;
			this->retrogressionTime = 0;
		}
	}
	else //后退的时间
	{
		if (true) //这里写限界函数
		{
			//重力加速度公式,下降
			this->y = this->y - 0.5 * g * ((n - this->retrogressionTime) - n / 2);
			//以机器旋转角度确认机器人的方向
			//向后倒
			float zs = zstep + 1; //单位步长
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

//僵尸倒地函数
void Robot::robotFall()
{
	glTranslatef(this->x, this->y - 5 * this->size, this->z);
	glRotatef(this->fallangle, -1, 0, 0);//绕着y轴旋转
	glTranslatef(-(this->x), -(this->y - 5 * this->size), -(this->z));
}

//僵尸攻击函数
void Robot::robotAttack(float theta)
{
	if (this->attackFlag == true) //僵尸进行攻击
	{
		glRotatef(-theta, 1, 0, 0);//绕着x轴旋转
	}
}

//开始攻击
void Robot::robotStartAttack()
{
	this->attackFlag = true;
	this->leftAttackFinishFlag = false;
	this->rightAttackFinishFlag = false;
	this->leftAttackHandFlag = false;
	this->rightAttackHandFlag = false;
}

//判断伤害
void  Robot::judgeDamage(int damage)
{
	blood -= damage;
}