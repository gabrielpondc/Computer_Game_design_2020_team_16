#include "stdafx.h"
#include"My_Camera.h"

//��������ƶ�
void Camera::changeState(int state)
{
	moveState = state;
}

void Camera::Walking()
{
	if (clock() / 1000-soundbefo > soundstep)
	{
		FSOUND_Stream_Play(FSOUND_FREE, sound[5][(soundn++) % 20]);
		soundbefo = clock() / 1000;
	}

	if (abs(shock + shock_step) > 0.2)
		shock_step = -shock_step;
	shock += shock_step;

	angleXupdown += TheAngleUPDown;
	angleX += TheAngle;
	lx = sin(angleX)*cos(angleY);
	ly = sin(angleY);
	lz = cos(angleX)*cos(angleY);
	//�߽�����
	float x1 = x + TheMove*lx + TheMoveAround*cos(angleX);
	float z1 = z + TheMove*lz - TheMoveAround*sin(angleX);
	if (x1 < 600 && x1 > 100)
		x = x1;
	if (z1 < 600 && z1 > 100)
		z = z1;

	y = terrain->GetHeight(x, z) + height;
	glLoadIdentity();
	X = x; Y = y + shock; Z = z; LX = x + lx; LY = y + ly + shock; LZ = z + lz;
	gluLookAt(X, Y, Z,
		LX, LY ,LZ,
		0.0f, 1.0f, 0.0f);
}
//û��������ƶ�
void Camera::Stoping()
{

	angleXupdown += TheAngleUPDown;
	angleX += TheAngle;
	lx = sin(angleX)*cos(angleY);
	ly = sin(angleY);
	lz = cos(angleX)*cos(angleY);

	//�߽�����
	float x1 = x + TheMove*lx + TheMoveAround*cos(angleX);
	float z1 = z + TheMove*lz - TheMoveAround*sin(angleX);
	if (x1 < 600 && x1 > 100)
		x = x1;
	if (z1 < 600 && z1 > 100)
		z = z1;

	y = terrain->GetHeight(x, z) + height;
	glLoadIdentity();
	X = x; Y = y ; Z = z; LX = x + lx; LY = y + ly ; LZ = z + lz;
	gluLookAt(X, Y, Z,
		LX, LY, LZ,
		0.0f, 1.0f, 0.0f);
}
//��������
void Camera::Jumping()
{
	angleXupdown += TheAngleUPDown;
	angleX += TheAngle;
	lx = sin(angleX)*cos(angleY);
	ly = sin(angleY);
	lz = cos(angleX)*cos(angleY);

	//�߽�����
	float x1 = x + TheMove*lx + TheMoveAround*cos(angleX);
	float z1 = z + TheMove*lz - TheMoveAround*sin(angleX);
	if (x1 < 600 && x1 > 100)
		x = x1;
	if (z1 < 600 && z1 > 100)
		z = z1;

	jump_v -= jump_a;
	//if (jump + jump_step > 2)
	//jump_step = -jump_step;
	jump += jump_v;

	if (y + jump < terrain->GetHeight(x, z) + height)
		jumping = 0;

	glLoadIdentity();
	X = x; Y = y+ jump; Z = z; LX = x + lx; LY = y + ly+ jump; LZ = z + lz;
	gluLookAt(X, Y, Z,
		LX, LY, LZ,
		0.0f, 1.0f, 0.0f);
}

//�ϵ��ӽǷ���
void Camera::Flying()
{
	angleXupdown += TheAngleUPDown;
	angleX += TheAngle;
	lx = sin(angleX)*cos(angleY);
	ly = sin(angleY);
	lz = cos(angleX)*cos(angleY);

	//û�б߽������������
	float x1 = x + TheMove*lx + TheMoveAround*cos(angleX);
	float z1 = z + TheMove*lz - TheMoveAround*sin(angleX);
		x = x1;
		z = z1;

	y = height;
	glLoadIdentity();
	X = x; Y = y; Z = z; LX = x + lx; LY = y + ly; LZ = z + lz;
	gluLookAt(X, Y, Z,
		LX, LY, LZ,
		0.0f, 1.0f, 0.0f);
}
//ÿ�̸ı��ӽǵ����
void Camera::ChangeCamera()
{
	if (jumping == 1)
		Jumping();
	else if (moveState == 0)
		Stoping();
	else if (moveState == 1)
		Walking();
}

//�����ƶ��ķ���ǰ��
void Camera::ChangeMoveDirectFB(float frontBack)
{

	//�޸�״̬(����Ǿ�ֹ��ֵ����������������ƶ���Ϊ0)
	if (frontBack == 0&& TheMoveAround<0.001)
	{
		moveState = 0;
	}
	else
	{
		shock = 0;
		shock_step = 0.04;
		moveState = 1;
	}
	TheMove = frontBack / (1 / speed);
}
//�����ƶ��ķ�������
void Camera::ChangeMoveDirectLR(float LeftRight)
{

	//�޸�״̬(����Ǿ�ֹ��ֵ����������������ƶ���Ϊ0)
	if (LeftRight == 0 && TheMove<0.001)
	{
		moveState = 0;
	}
	else
	{
		shock = 0;
		shock_step = 0.04;
		moveState = 1;
	}
	TheMoveAround = LeftRight / (1 / speed);
}
//��ʼ��
void Camera::BeginJump()
{
	if (jumping == 1)
		return;
	jump = 0;
	jump_v = 0.6;
	jump_a = 0.02;
	jumping = 1;
}

//����ĵط����ٶ�
void Camera::ChangeSideRate(int x, int y)
{
	//������
	float sensitivity = 5000;
	//���λ�ñ��ڶ� �ƶ�ʱ�ڶ�λ�ü�ȥ�ƶ����λ��
	// 300 �����ƫ����
	//����
	angleX += (float)(WINDOW_WIDTH / 2 - x) / sensitivity;
	AddangleY((float)(WINDOW_HEIGHT / 2 - y) / sensitivity);


	//���²��޶���Χ
	//if (angleXupdown + (float)(WINDOW_HEIGHT / 2 - y) / sensitivity<0.1&& angleXupdown + (float)(WINDOW_HEIGHT / 2 - y) / sensitivity>-0.1)
	//	angleXupdown += (float)(WINDOW_HEIGHT / 2 - y) / (sensitivity * 6);
	int cx = glutGet(GLUT_SCREEN_WIDTH);
	int cy = glutGet(GLUT_SCREEN_HEIGHT);
	SetCursorPos((cx - WINDOW_WIDTH) / 2 + WINDOW_WIDTH / 2, (cy - WINDOW_HEIGHT) / 2 + WINDOW_HEIGHT / 2);
}

void Camera::AddangleY(float they)
{
	if (angleY + they<1.2 && angleY + they>-1.2)
	{
		angleY += they;
	}
}
