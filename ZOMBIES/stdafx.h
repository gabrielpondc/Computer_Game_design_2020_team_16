// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 

// C ����ʱͷ�ļ�
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <olectl.h>		
#include <math.h>
#include <stdlib.h>
#include <glew.h>
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include "stdafx.h"

#include <glut.h>
#include <glaux.h>
#pragma comment ( lib, "glaux.lib" )
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include <vector> 

#include "My_Texture.h"
#include "My_Terrain.h"
#include "Robot.h"
#include "My_Scene.h"
#include "My_Player.h"
#include "Font.h"
#include "My_SkyBox.h"
#include "My_Item.h"
#include "fmod.h"  //// ��Ƶ���ͷ�ļ�
#pragma comment(lib, "fmodvc.lib")	          // ����Ƶ����뵽��������

//��������
using namespace std;


/*************���ڱ���****************/
//��Ļ�ֱ��ʣ���֤���������м�
#define SCREEN_WIDTH  2560
#define SCREEN_HEIGHT 1440
//���ڴ�С
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800

#define MAP_SIZE 600

extern int soundn;
extern FSOUND_STREAM *sound[11][20];