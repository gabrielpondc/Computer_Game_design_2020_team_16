#pragma once
#include "stdafx.h"
//ÏîÄ¿
class Item
{

};

class Core
{
	int x;
	int y;
	int z;
public :
	UINT texture_1;
	UINT tree;
	Core(int x,int y,int z):x(x),y(y),z(z) {}
	Core();
	void Init();
	void Draw();
	//»­µÆ
	void DrawLamp();
	//»­Ïä×Ó
	void DrawBox();
};
