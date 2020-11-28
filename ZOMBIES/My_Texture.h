#pragma once
#include "stdafx.h"
//纹理
typedef struct
{
	GLubyte *imageData;//图像数据
	GLuint bpp;//像素深度
	GLuint width;//图像宽度
	GLuint height;//图像高度
	GLuint texID;//对应的纹理ID
}TextureImage;


#define TEXTURE_LAKE 3

class Texture
{
public:
	//tga格式
	static bool LoadTGA(TextureImage *texture, char *filename);
	//bmp格式
	static bool LoadT8(GLuint &texture, LPCWSTR filename);


#define GL_CLAMP_TO_EDGE	0x812F
	/***********************************************/
	// 载入一个.TGA 文件到内存
	static bool BuildTexture(char *filename, GLuint &texid);
	static int LoadGLTextures(char *Filename, GLuint *ttexture);
};

