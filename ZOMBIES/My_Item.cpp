#include "stdafx.h"
#include"My_Item.h"


Core::Core()
{
	x = 0; y = 0; z = 0;
}
void Core::Init()
{
	Texture::BuildTexture(".\\img\\Box.jpg", texture_1);
	//Texture::LoadT16((tree), ".\\img\\t1.bmp");
}
void Core::Draw()
{
	glPushMatrix();
	glTranslatef(350, 11.1, 350);
	glScaled(2, 2, 2);
	DrawLamp();
	glPopMatrix();

}
void Core::DrawLamp()
{
	
	float r = 3;
	//光照范围
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数
	glEnable(GL_BLEND);        //启用混合状态
							   //箱子
	DrawBox();
	//整体转移
	glTranslatef(0, 3, 0);

	//灯身
	glColor4f(0, 0, 0, 1);
	glPushMatrix();

	glScaled(0.5, 6, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	//灯头
	glPushMatrix();
	glTranslatef(0, 3, 0.5);
	//灯
	glColor4f(1, 1, 0, 1);
	glPushMatrix();
	glTranslatef(0, -0.2, 0.1);
	glScaled(0.25, 0.25, 0.25);
	glutSolidSphere(1, 40, 40);
	glPopMatrix();

	//头
	glColor4f(0, 0, 0, 1);
	glPushMatrix();
	glScaled(0.8, 0.5, 1.3);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	//----灯头

	//亮光
	glPushMatrix();
	glColor4f(1, 1, 0, 0.1);
	glTranslatef(0, -3, 0.6);
	glRotatef(-90, 1, 0, 0);

	glutSolidCone(r, 6, 40, 40);//实心圆锥体
	glPopMatrix();

	glDisable(GL_BLEND);

	glTranslatef(0, -3, 0);
	//----整体
}

//画箱子
void Core::DrawBox()
{
	glPushMatrix();

	glTranslatef(0, 1, 1.3);

	//阴影
	glPushMatrix();
	glTranslatef(0, -1, 0);
	glColor4f(0, 0, 0, 0.4);
	glBegin(GL_QUADS);
	glVertex3d(-1.2, 0, -1);
	glVertex3d(1.2, 0, -1);
	glVertex3d(1.7, 0, 1.7);
	glVertex3d(-1.7, 0, 1.7);
	glEnd();
	glPopMatrix();


	glEnable(GL_TEXTURE_2D);		//启用二维文理
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glColor4f(1, 1, 1, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, 1);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, -1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, -1);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, -1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, 1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 1, 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, -1, -1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, -1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 1);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, 1);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, -1);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);		//关闭二维文理

}
