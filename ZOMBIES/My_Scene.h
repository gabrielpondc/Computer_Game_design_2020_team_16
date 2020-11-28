#pragma once
#include "stdafx.h"
#include "My_Item.h"


class Tree //��
{
public:
	float x, y, z, size, height;
	int angle;
	int texid;
	Tree()
	{
		x = 350;
		y = 30;
		z = 350;
		size = 3;
	}
	Tree(float x, float y, float z, float size, float height, int angle,int texid)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->height = height;
		this->texid = texid;
		this->size = size;
		this->angle = angle;
	}

};

class Trees
{
public:
	GLuint textureid[10];
	std::vector <Tree> theTrees;
	Terrain *terrain;
	
	void Init();
	void drawTree();
	void drawOneTree(float x, float y, float z, float size, int angle, int n);


};


/*********���г����ڴ˻���********/
class Scene
{
public:
	Core core;
	Terrain terrain;
	GLuint my_texture[2];
	Scene::Scene();
	Trees trees;
	void Scene::Init();
	//��һ��ƽ�����
	void Scene::drawdiban();
	//�������ߵĵ���
	void Scene::DrawGround(float MAP);
	//������ϵ
	void Scene::DrawXYZ();
	//����ͼ�߽�
	void Scene::DrawBorder();
	//����
	void Scene::DrawLake();
	//�������г���
	void Scene::DrawScene();
	//��2D����
	void Scene::Draw2D();

};

