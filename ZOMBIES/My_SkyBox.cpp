#include "stdafx.h"
#include"My_SkyBox.h"

//天空盒

//顺序 前后左右上下

SkyBox::SkyBox()
{
	//LoadTGA(&texture[0], "img\\SkyBox\\amh_baxk.tga");

}
void SkyBox::LoadTexture()
{
	Texture::LoadTGA(&(texture[0]), ".\\img\\SkyBox\\front.tga");
	Texture::LoadTGA(&(texture[1]), ".\\img\\SkyBox\\back.tga");
	Texture::LoadTGA(&(texture[2]), ".\\img\\SkyBox\\left.tga");
	Texture::LoadTGA(&(texture[3]), ".\\img\\SkyBox\\right.tga");
	Texture::LoadTGA(&(texture[4]), ".\\img\\SkyBox\\up.tga");
	Texture::LoadTGA(&(texture[5]), ".\\img\\SkyBox\\down.tga");
}
void SkyBox::drawSkyBox(float x, float y, float z)
{
	//glDisable(GL_FOG);
	glPushMatrix();
	float map_w = MAP_SIZE;
	glTranslatef(x, map_w - 450 + y, z);
	glEnable(GL_TEXTURE_2D);		//启用二维文理
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[0].texID);

	glBegin(GL_QUADS);
	//以z轴为正前方的话
	// Front Face 正前方
	// Bottom Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-map_w, -map_w, map_w);
	// Bottom Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(map_w, -map_w, map_w);
	// Top Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(map_w, map_w, map_w);
	// Top Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-map_w, map_w, map_w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1].texID);
	glBegin(GL_QUADS);
	// Back Face 
	// Bottom Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-map_w, -map_w, -map_w);
	// Top Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-map_w, map_w, -map_w);
	// Top Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(map_w, map_w, -map_w);
	// Bottom Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(map_w, -map_w, -map_w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4].texID);
	glBegin(GL_QUADS);
	// Top Face 
	// Top Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-map_w, map_w, -map_w);
	// Bottom Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-map_w, map_w, map_w);
	// Bottom Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(map_w, map_w, map_w);
	// Top Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(map_w, map_w, -map_w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5].texID);
	glBegin(GL_QUADS);
	// Bottom Face 
	// Top Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-map_w, -map_w, -map_w);
	// Top Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(map_w, -map_w, -map_w);
	// Bottom Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(map_w, -map_w, map_w);
	// Bottom Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-map_w, -map_w, map_w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[3].texID);
	glBegin(GL_QUADS);
	// Right face 
	// Bottom Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(map_w, -map_w, -map_w);
	// Top Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(map_w, map_w, -map_w);
	// Top Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(map_w, map_w, map_w);
	// Bottom Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(map_w, -map_w, map_w);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2].texID);
	glBegin(GL_QUADS);
	// Left Face 
	// Bottom Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-map_w, -map_w, -map_w);
	// Bottom Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-map_w, -map_w, map_w);
	// Top Right Of The Texture and Quad 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-map_w, map_w, map_w);
	// Top Left Of The Texture and Quad 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-map_w, map_w, -map_w);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);		//关闭二维文理
	//glEnable(GL_FOG);

}

