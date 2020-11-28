#pragma once
#include "stdafx.h"
//����ͷͷ�ļ�
class Camera
{
public:
	//��λ��
	float angleX = 0.0, angleXupdown = 0.0;
	//������
	float angleY = 0.0, angleYupdown = 0.0;
	//�൱���˵ĸ߶�
	float height;
	float x = 350.0f, y = 5, z = 350.0f;
	float lx = 0.0f, ly = 0.0f, lz = -1.0f;
	//���й��������жϵ���Ҫ����
	float X ,Y , Z ;
	float LX , LY , LZ ;

	float TheAngle = 0.0;
	float TheMove = 0.0;
	float TheMoveAround = 0.0;
	float TheAngleUPDown = 0.0;
	Terrain *terrain;

	float soundbefo=0,soundstep=0.1;
	
	/************�ƶ����***********/
	//��ϵ��
	float shock = 0, shock_step=0.01;
	//��Ծϵ��
	float jumping=0,jump = 0, jump_v = 0,jump_a= 0.01;
	//�ƶ�״̬ 0�����ض� 1�����ض�
	int moveState=0;
	//�ƶ��ٶ�
	float speed ;
	//�ı�״̬
	void changeState(int state);
	//��������ƶ�
	void Walking();
	//û��������ƶ�
	void Stoping();
	//�������˵��ƶ�
	void Jumping();
	//�ϵ��ӽǷ���
	void Flying();
	//ÿ�̸ı��ӽǵ����
	void ChangeCamera();
	//�����ƶ��ķ���ǰ��
	void ChangeMoveDirectFB(float frontBack);
	//�����ƶ��ķ�������
	void ChangeMoveDirectLR(float LeftRight);
	//��ʼ����ʼ��
	void BeginJump();
	//�����ƿ���ĵط����ٶ�
	void ChangeSideRate(int x, int y);
	void AddangleY(float they);
};