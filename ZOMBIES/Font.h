#pragma once
#include "stdafx.h"
#include <glut.h>
//字体

class Font
{
public:

	//* 选择字体函数                                                                    
	static void selectFont(int size, int charset, const char* face)
	{
		HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
			charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
		HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
		DeleteObject(hOldFont);
	}

	//* 生成中文字体函数                                                                  
	static void drawCNString(const char* str)
	{
		int len, i;
		wchar_t* wstring;
		HDC hDC = wglGetCurrentDC();
		GLuint list = glGenLists(1);

		// 计算字符的个数
		// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
		// 否则一个字节算一个字符
		len = 0;
		for (i = 0; str[i] != '\0'; ++i)
		{
			if (IsDBCSLeadByte(str[i]))
				++i;
			++len;
		}

		// 将混合字符转化为宽字符
		wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
		wstring[len] = L'\0';

		// 逐个输出字符
		for (i = 0; i<len; ++i)
		{
			wglUseFontBitmapsW(hDC, wstring[i], 1, list);
			glCallList(list);
		}

		// 回收所有临时资源
		free(wstring);
		glDeleteLists(list, 1);
	}

};