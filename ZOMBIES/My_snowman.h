#pragma once
#include "stdafx.h"
//雪人类
class SnowMan
{
	GLint snowman_display_list;
public:
	SnowMan()
	{
		//initScene();
	}
	void drawSnowMan() {
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0.0f ,0.75f, 0.0f);
		glutSolidSphere(0.75f,20,20);
		glTranslatef(0.0f, 1.0f, 0.0f);
		glutSolidSphere(0.25f,20,20);
		glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glTranslatef(0.05f, 0.10f, 0.18f);
		glutSolidSphere(0.05f,10,10);
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glutSolidSphere(0.05f,10,10);
		glPopMatrix();
		glColor3f(1.0f, 0.5f , 0.5f);
		glRotatef(0.0f,1.0f, 0.0f, 0.0f);
		glutSolidCone(0.08f,0.5f,10,2);
	}

	GLuint createDL() {
		GLuint snowManDL;
		//生成一个显示列表号
		snowManDL = glGenLists(1);
		// 开始显示列表
		glNewList(snowManDL,GL_COMPILE);
		drawSnowMan();
		glEndList();
		return(snowManDL);
	}

	void initScene() {

		glEnable(GL_DEPTH_TEST);
		snowman_display_list = createDL();
	}

	void drawIt()
	{

		//画了36个雪人
		for(int i = -3; i < 3; i++)
			for(int j=-3; j < 3; j++) {
				glPushMatrix();
				glTranslatef(i*10.0,0,j * 10.0);
				glCallList(snowman_display_list);;
				glPopMatrix();
			}
	}
};

