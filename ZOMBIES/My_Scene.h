#pragma once
#include "stdafx.h"
#include "My_Item.h"


class Tree //树
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


/*********所有场景在此绘制********/
class Scene
{
public:
	Core core;
	Terrain terrain;
	GLuint my_texture[2];
	Scene::Scene();
	Trees trees;
	void Scene::Init();
	//画一个平板地面
	void Scene::drawdiban();
	//画网格线的地面
	void Scene::DrawGround(float MAP);
	//画坐标系
	void Scene::DrawXYZ();
	//画地图边界
	void Scene::DrawBorder();
	//画湖
	void Scene::DrawLake();
	//画出所有场景
	void Scene::DrawScene();
	//画2D场景
	void Scene::Draw2D();

};

