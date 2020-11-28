#pragma once
#include "stdafx.h"
//����
typedef struct
{
	GLubyte *imageData;//ͼ������
	GLuint bpp;//�������
	GLuint width;//ͼ����
	GLuint height;//ͼ��߶�
	GLuint texID;//��Ӧ������ID
}TextureImage;


#define TEXTURE_LAKE 3

class Texture
{
public:
	//tga��ʽ
	static bool LoadTGA(TextureImage *texture, char *filename);
	//bmp��ʽ
	static bool LoadT8(GLuint &texture, LPCWSTR filename);


#define GL_CLAMP_TO_EDGE	0x812F
	/***********************************************/
	// ����һ��.TGA �ļ����ڴ�
	static bool BuildTexture(char *filename, GLuint &texid);
	static int LoadGLTextures(char *Filename, GLuint *ttexture);
};

