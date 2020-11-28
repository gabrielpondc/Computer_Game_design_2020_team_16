#pragma once
#include "stdafx.h"

//����
class Terrain
{
public:
	//ɽ�ƵĹ���
	//ɽ�ĵ���ܼ��̶�
#define MAP_SCALE 7
#define MAP_W  101

	float		g_terrain[MAP_W*MAP_W][3];
	float		g_texcoord[MAP_W*MAP_W][2];
	GLuint		g_index[MAP_W*MAP_W * 2];

	UINT texture_1;
#define THEHEIGHT 0
	void InitTerrain();
	//��ȡ�����ַ���ת������
	int readNum(int *cursor, char str[MAP_W * 3 + 10]);
	//�޸������ַ�������
	void changeNum(int cursor, char str[], int num);
	//��ȡ���е��ļ�
	void InitTerrain_Read();
	//�޸����е�ͼ��ĳЩ����
	//x1 ���Ͻ���� x2���½�����
	void InitTerrain_Change(int x1, int z1, int x2, int z2);
	//��ɽ
	void DrawSand();
	//��ȡĳ��߶�
	float GetHeight(float x, float z);
};
