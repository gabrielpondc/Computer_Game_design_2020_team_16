#pragma once
#include "stdafx.h"

//地形
class Terrain
{
public:
	//山势的构造
	//山的点的密集程度
#define MAP_SCALE 7
#define MAP_W  101

	float		g_terrain[MAP_W*MAP_W][3];
	float		g_texcoord[MAP_W*MAP_W][2];
	GLuint		g_index[MAP_W*MAP_W * 2];

	UINT texture_1;
#define THEHEIGHT 0
	void InitTerrain();
	//读取三个字符并转成数字
	int readNum(int *cursor, char str[MAP_W * 3 + 10]);
	//修改三个字符的数字
	void changeNum(int cursor, char str[], int num);
	//读取已有的文件
	void InitTerrain_Read();
	//修改现有地图的某些地形
	//x1 左上角左边 x2右下角坐标
	void InitTerrain_Change(int x1, int z1, int x2, int z2);
	//画山
	void DrawSand();
	//获取某点高度
	float GetHeight(float x, float z);
};
