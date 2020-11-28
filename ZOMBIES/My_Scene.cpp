#pragma once
#include "stdafx.h"
#include"My_Scene.h"


void Trees::Init()
{
	Texture::BuildTexture(".\\img\\Tree\\tree1.tga", textureid[0]);
	Texture::BuildTexture(".\\img\\Tree\\tree2.tga", textureid[1]);
	Texture::BuildTexture(".\\img\\Tree\\tree3.tga", textureid[2]);
	Texture::BuildTexture(".\\img\\Tree\\tree4.tga", textureid[3]);
	int heightList[] = { 15,18 ,18,18};
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (i>50 && i<100 && j>0 && j<50)
			{
				if (rand() % 20 == 1)
				{
					//�����������
					int n = rand() % 4;
					int x = i*MAP_SCALE;
					int z = j*MAP_SCALE;
					if (terrain->g_terrain[j*MAP_W + i][1] < 0)
						continue;
					theTrees.push_back(Tree(x, 0, z, 3, terrain->GetHeight(x, z) + heightList[n], rand() % 360, n));
				}
			}
			else if ((i < 15 || i>85 || j<15 || j>85))
			{
				if (rand() % 20 == 1)
				{
					int n = rand() % 4;
					int x = i*MAP_SCALE;
					int z = j*MAP_SCALE;
					if (terrain->g_terrain[j*MAP_W + i][1] < 0)
						continue;
					theTrees.push_back(Tree(x, 0, z, 3, terrain->GetHeight(x, z) + heightList[n], rand() % 360, n));
				}
			}
			else
			{
				if (rand() % 50 == 1)
				{
					int n = rand() % 4;
					int x = i*MAP_SCALE;
					int z = j*MAP_SCALE;
					if (terrain->g_terrain[j*MAP_W + i][1] < 0)
						continue;
					theTrees.push_back(Tree(x, 0, z, 3, terrain->GetHeight(x, z) + heightList[n], rand() % 360, n));
				}
			}
		}
	}
}
void Trees::drawTree()
{
	std::vector<Tree>::iterator it;
	for (it = theTrees.begin(); it != theTrees.end();)
	{
		drawOneTree((*it).x,(*it).height, (*it).z, (*it).size, (*it).angle, (*it).texid);
		it++;
	}
}

void Trees::drawOneTree(float x, float y, float z, float size, int angle, int n)
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);	// ��XYZ����ת������
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.9);
	glEnable(GL_TEXTURE_2D);//��������
	glBindTexture(GL_TEXTURE_2D, textureid[n]);  //��ָ������
	glBegin(GL_QUADS);

	//����ͼ�ĸ�������������
	//����ȷ���������꣬���±�0,0 ���½�1,0 ���Ͻ� 1,1 ���Ͻ�0,1 ���м����0.5,0.5����s,t��s-ˮƽ���꣬t-��ֱ���꣬ȡֵֻ����0-1
	glTexCoord2f(0.0f, 1.0f); //���������꣬����ͼ������	 
	glVertex3d(-4 * size, +6 * size, 0); //��λ�õ���������
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(+4 * size, +6 * size, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(+4 * size, -6 * size, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(-4 * size, -6 * size, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D); //�ر�����ע�����������������Ĺ��ջ�������

	glEnable(GL_TEXTURE_2D);//��������
	glBindTexture(GL_TEXTURE_2D, textureid[n]);  //��ָ������
	glBegin(GL_QUADS);

	//����ͼ�ĸ�������������

	//����ȷ���������꣬���±�0,0 ���½�1,0 ���Ͻ� 1,1 ���Ͻ�0,1 ���м����0.5,0.5����s,t��s-ˮƽ���꣬t-��ֱ���꣬ȡֵֻ����0-1
	glTexCoord2f(0.0f, 1.0f); //���������꣬����ͼ������	 
	glVertex3d(0, +6 * size, -4 * size); //��λ�õ���������
	glTexCoord2f(1.0f, 1.0f);
	glVertex3d(0, +6 * size, +4 * size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3d(0, -6 * size, +4 * size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3d(0, -6 * size, -4 * size);
	glEnd();
	glDisable(GL_TEXTURE_2D); //�ر�����ע�����������������Ĺ��ջ�������
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	glPopMatrix();
}

Scene::Scene()
{
	//InitTerrain(5);
}

void Scene::Init()
{
	//terrain.InitTerrain();
	terrain.InitTerrain_Read();
	//terrain.InitTerrain_Change(58, 15, 85, 45);
	core.Init();
	trees.terrain = &terrain;
	trees.Init();
	Texture::BuildTexture(".\\img\\lake1.jpg", my_texture[0]);
	Texture::BuildTexture(".\\img\\lake2.jpg", my_texture[1]);
	int i = 0;
}
//��һ��ƽ�����
void Scene::drawdiban()
{
	//����һ������
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
}

//�������ߵĵ���
void Scene::DrawGround(float MAP)
{
	//��ͼ��С x*x������
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f);
	glTranslatef(0, 0, 0);

	int size0 = (int)(MAP * 2);
	glBegin(GL_LINES);
	for (int x = -size0; x < size0; x += 4)
	{
		glVertex3i(x, 0, -size0); glVertex3i(x, 0, size0);
	}
	for (int z = -size0; z < size0; z += 4)
	{
		glVertex3i(-size0, 0, z); glVertex3i(size0, 0, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();
}

//������ϵ
void Scene::DrawXYZ()
{
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3i(0, 0, 0); glVertex3i(50, 0, 0);
	glVertex3i(0, 0, 0); glVertex3i(0, 50, 0);
	glVertex3i(0, 0, 0); glVertex3i(0, 0, 50);
	glEnd();
	glDisable(GL_BLEND);

	//�����ĵ�
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3i(350, 10, 0); glVertex3i(350, 10, 700);
	glVertex3i(0, 10, 350); glVertex3i(700, 10, 350);
	glEnd();
	glDisable(GL_BLEND);
}

//����ͼ�߽�
void Scene::DrawBorder()
{
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3i(100, 6, 100); glVertex3i(600, 6, 100);
	glVertex3i(600, 6, 100); glVertex3i(600, 6, 600);
	glVertex3i(600, 6, 600); glVertex3i(100, 6, 600);
	glVertex3i(100, 6, 600); glVertex3i(100, 6, 100);
	glEnd();
	glDisable(GL_BLEND);
}

//����
void Scene::DrawLake()
{
	int x1 = 23, x2 = 41, z1 = 60, z2 = 75;
	int height = 1;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, my_texture[(clock()/500)%2]);
	int scale = 20;
	//��z��Ϊ��ǰ���Ļ�
	for (int x = x1*MAP_SCALE; x <= x2*MAP_SCALE; x += scale)
	{
		for (int z = z1*MAP_SCALE; z <= z2*MAP_SCALE; z += scale)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x, height, z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + scale, height, z);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + scale, height, z + scale);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x, height, z + scale);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void Scene::DrawScene()
{

	//��������˳���н���
	//DrawXYZ();
	//DrawBorder();
	//��
	DrawLake();
	//��
	terrain.DrawSand();
	//��
	trees.drawTree();
	//��
	core.Draw();

}

void Scene::Draw2D()
{
	float x = WINDOW_WIDTH / 2;
	float y = WINDOW_HEIGHT / 2;
	glColor3f(1, 1, 1);
	int len = 20;
	int  d = 7;
	glBegin(GL_LINES);
	glVertex2i(x, y+ d);
	glVertex2i(x, y+ len);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(x+ d, y);
	glVertex2i(x+ len, y);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(x, y- d);
	glVertex2i(x, y - len);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(x- d, y);
	glVertex2i(x- len, y);
	glEnd();

}


