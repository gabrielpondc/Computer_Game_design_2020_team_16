// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 

// C 运行时头文件
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <olectl.h>		
#include <math.h>
#include <stdlib.h>
#include <glew.h>
// TODO:  在此处引用程序需要的其他头文件

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
#include "fmod.h"  //// 音频库的头文件
#pragma comment(lib, "fmodvc.lib")	          // 把音频库加入到链接器中

//基础变量
using namespace std;


/*************窗口变量****************/
//屏幕分辨率，保证窗口在正中间
#define SCREEN_WIDTH  2560
#define SCREEN_HEIGHT 1440
//窗口大小
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800

#define MAP_SIZE 600

extern int soundn;
extern FSOUND_STREAM *sound[11][20];