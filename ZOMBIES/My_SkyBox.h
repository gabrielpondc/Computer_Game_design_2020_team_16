#pragma once
#include "stdafx.h"


//´´½¨Ìì¿ÕºÐ
class SkyBox
{
	
public :
	TextureImage texture[6];
	SkyBox();
	void LoadTexture();
	void drawSkyBox(float x, float y, float z);
};

