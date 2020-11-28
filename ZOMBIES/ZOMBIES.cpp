// ZOMBIES.cpp : Defines the entry point for the application.
//
#pragma once
#include "stdafx.h"
#include "ZOMBIES.h"
#include "My_snowman.h"
#include"My_Item.h"
#include"My_CastleEx.h"
float ratio_;
GLuint texture_2;
SnowMan snowman;
CastleEx castle;
/*****************自定函数**************/
void inputKey(int key, int x, int y);
void mykeyboard(unsigned char key, int x, int y); 
void reshapeSize(int w, int h);
void renderScene(void);//每局的重画
void myMotion(int x, int y);
void MouseClick(int button, int state, int x, int y);
void Init();

int soundn = 0;
FSOUND_STREAM *sound[11][20];

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{

	//glMatrixMode(GL_PROJECTION || GL_MODELVIEW);
	char *argv[] = { "hello ", " " };
	int argc = 2;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	int cx = glutGet(GLUT_SCREEN_WIDTH);
	int cy = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((cx - WINDOW_WIDTH) / 2, (cy - WINDOW_HEIGHT) / 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("ZOMBIES");

	Init();

	glutDisplayFunc(renderScene);

	glutSpecialFunc(inputKey);
	//glutKeyboardFunc(mykeyboard);
	//glutKeyboardUpFunc(releaseKey);
	
	glutIdleFunc(renderScene);		//开始空闲回调
	glutReshapeFunc(reshapeSize);

	glutMainLoop();
	return(0);
}
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	//FSOUND_Stream_Play(FSOUND_FREE, mp3back[(i11++) % 10]);
	return 0L;
}

void Init()
{
	glEnable(GL_DEPTH_TEST);		//启用深度测试。根据坐标的远近自动隐藏被遮住的图形（材料）
	snowman.initScene();
	castle.Init();
	Texture::LoadGLTextures(".\\img\\handGun.bmp", &texture_2);
	if (FSOUND_Init(44100, 32, 0))			// 把声音初始化为44khz
	{
		for (int i = 0; i < 20; i++)
		{
			sound[0][i] = FSOUND_Stream_OpenFile(".\\Music\\ak47.wav", FSOUND_LOOP_OFF, 0);
			sound[1][i] = FSOUND_Stream_OpenFile(".\\Music\\pistol.wav", FSOUND_LOOP_OFF, 0);
			sound[2][i] = FSOUND_Stream_OpenFile(".\\Music\\hitting.wav", FSOUND_LOOP_OFF, 0);
			sound[3][i] = FSOUND_Stream_OpenFile(".\\Music\\stick.wav", FSOUND_LOOP_OFF, 0);
			sound[4][i] = FSOUND_Stream_OpenFile(".\\Music\\hited.wav", FSOUND_LOOP_OFF, 0); 
			sound[5][i] = FSOUND_Stream_OpenFile(".\\Music\\run.wav", FSOUND_LOOP_OFF, 0); 
			sound[6][i] = FSOUND_Stream_OpenFile(".\\Music\\ak47loading.wav", FSOUND_LOOP_OFF, 0);
			sound[7][i] = FSOUND_Stream_OpenFile(".\\Music\\pistolloading.wav", FSOUND_LOOP_OFF, 0);
			sound[8][i] = FSOUND_Stream_OpenFile(".\\Music\\atked.mp3", FSOUND_LOOP_OFF, 0);
			sound[9][i] = FSOUND_Stream_OpenFile(".\\Music\\backmusic.mp3", FSOUND_LOOP_OFF, 0);
			sound[10][i] = FSOUND_Stream_OpenFile(".\\Music\\scream.wav", FSOUND_LOOP_OFF, 0);
		}
	}
	FSOUND_Stream_Play(FSOUND_FREE, sound[9][0]);
	//雾气
	GLfloat fogColor[] = { 0.8,0.8,0.8,0.1 };

	glFogfv(GL_FOG_COLOR, fogColor);   //颜色
	glFogf(GL_FOG_START, 100.0f);	  //开始
	glFogf(GL_FOG_END, 1200.0f);		//结束
	glFogi(GL_FOG_MODE, GL_LINEAR);  //模式
	glFogf(GL_FOG_DENSITY, 0.1f);	//密度
	glEnable(GL_FOG);

	ShowCursor(FALSE);

}


void reshapeSize(int w, int h)
{
	// 防止被0除.
	if (h == 0)
		h = 1;
	ratio_ = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//设置视口为整个窗口大小
	glViewport(0, 0, w, h);

	//设置可视空间
	gluPerspective(40, ratio_, 0.5, 1200);
	//gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	castle.player.camera.ChangeCamera();
}

//每局的重画
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//判断游戏流程
	castle.Processing();
	glEnable(GL_TEXTURE_2D);		//启用二维文理
	glBindTexture(GL_TEXTURE_2D, texture_2);
	glColor4f(1, 1, 1, 1);

	//FSOUND_Stream_Play(FSOUND_FREE, mp3back);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10, -10, 10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10, -10, 10);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10, 10, 10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10, 10, 10);
	glEnd();

	//glScaled(2, 2, 2);
	//glutSolidCube(1);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);		//关闭二维文理

	glutSwapBuffers();
}
//记录状态，防止键盘疯狂阻塞输入
int key_state[4] = { 0 };
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':// 矩形对角坐标变量修改使得矩形上移
		if (key_state[0] == 1)
			return;
		else
		{
			castle.player.camera.ChangeMoveDirectFB(1);
			key_state[0] = 1;
		}
		break;
	case 'S':
	case 's'://矩形对角坐标变量修改使得矩形下移
		if (key_state[1] == 1)
			return;
		else
		{
			castle.player.camera.ChangeMoveDirectFB(-1);
			key_state[1] = 1;
		}
		break;
	case 'A':
	case 'a'://矩形对角坐标变量修改使得矩形左移
		if (key_state[2] == 1)
			return;
		else
		{
			castle.player.camera.ChangeMoveDirectLR(1);
			key_state[2] = 1;
		}
		break;
	case 'D':
	case 'd'://矩形对角坐标变量修改使得矩形右移
		if (key_state[3] == 1)
			return;
		else
		{
			castle.player.camera.ChangeMoveDirectLR(-1);
			key_state[3] = 1;
		}
		break;
	}
}

//释放按键
void GamingKey(unsigned char key, int x, int y) {

	switch (key) {
	case 'W':
	case 'w':// 矩形对角坐标变量修改使得矩形上移
		key_state[0] = 0;
		castle.player.camera.ChangeMoveDirectFB(0);
		break;
	case 'S':
	case 's'://矩形对角坐标变量修改使得矩形下移
		key_state[1] = 0;
		castle.player.camera.ChangeMoveDirectFB(0);
		break;
	case 'A':
	case 'a'://矩形对角坐标变量修改使得矩形左移
		key_state[2] = 0;
		castle.player.camera.ChangeMoveDirectLR(0);
		break;
	case 'D':
	case 'd'://矩形对角坐标变量修改使得矩形右移
		key_state[3] = 0;
		castle.player.camera.ChangeMoveDirectLR(0);
		break;
	case 'R':
	case 'r':
		if (castle.player.weapon == 2)
		{
			if (castle.player.pistol.changflag == 1)
				return;
			FSOUND_Stream_Play(FSOUND_FREE, sound[7][(soundn++) % 20]);
			castle.player.pistol.Bomb_changing = clock() / 1000;
			castle.player.pistol.changflag = 1;
		}
		else if (castle.player.weapon == 3)
		{
			if (castle.player.ak47.changflag == 1)
				return;
			FSOUND_Stream_Play(FSOUND_FREE, sound[6][(soundn++) % 20]);
			castle.player.ak47.Bomb_changing = clock() / 1000;
			castle.player.ak47.changflag = 1;
		}
		break;
	case ' ':
		castle.player.camera.BeginJump();
		break;
	case'1':
		castle.player.weapon = 1;
		break;
	case'2':
		castle.player.weapon = 2;
		break;
	case'3':
		castle.player.weapon = 3;
		break;
	default:
		break;
	}
}

void inputKey(int key, int x, int y) {

	switch (key) {

	case GLUT_KEY_F1:

		break;
	case GLUT_KEY_F2:
		if (castle.Pattern != 0)
			return;
		glutKeyboardFunc(mykeyboard);
		glutKeyboardUpFunc(GamingKey);
		glutPassiveMotionFunc(myMotion);//注册鼠标移动回调函数
		glutMotionFunc(myMotion);		//注册点击鼠标移动回调函数
		glutMouseFunc(MouseClick);		//注册鼠标按钮回调函数
		FSOUND_Stream_Stop(sound[9][0]);
		castle.ChangePattern(2);
		castle.time = clock() / 1000;
		break;

		break;
	case GLUT_KEY_F3:
		if (castle.Pattern != 0)
			return;
		castle.ChangePattern(4);
		break;
	case GLUT_KEY_F9:
		if(castle.Pattern == 4)
			castle.ChangePattern(0);
		else
			exit(0);
		break;


	}
}
int i = 0;
//鼠标移动时获得鼠标移动中的坐标
void myMotion(int x, int y)
{
	castle.player.camera.ChangeSideRate(x, y);
	if (castle.player.ak47.shotting == 1)
	{
		int i = 0;
	}
}

void MouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		if (castle.player.weapon == 1)
		{
			FSOUND_Stream_Play(FSOUND_FREE, sound[3][(soundn++) % 20]);
			castle.player.sword.BeginHit();
			castle.AxeDamage(castle.player.camera.LX, castle.player.camera.LY, castle.player.camera.LZ);
		}
		else if (castle.player.weapon == 2)
		{
			//假装开枪
			if (castle.player.pistol.bulletNum == 0&& castle.player.pistol.changflag==0)
			{
				FSOUND_Stream_Play(FSOUND_FREE, sound[7][(soundn++) % 20]);
				castle.player.pistol.Bomb_changing = clock() / 1000;
				castle.player.pistol.changflag = 1;
			}
			else
			{
				if (castle.player.pistol.changflag == 1)
					return;
				FSOUND_Stream_Play(FSOUND_FREE, sound[1][(soundn++) % 20]);
				castle.player.pistol.BeginShot();
				castle.player.camera.AddangleY(0.02);
				castle.bullet.push_back(Bullet(castle.player.camera.X, castle.player.camera.Y, castle.player.camera.Z, castle.player.camera.LX, castle.player.camera.LY, castle.player.camera.LZ));
				castle.player.pistol.bulletNum -= 1;
			}
		}
		else if (castle.player.weapon == 3)
		{
			castle.player.ak47.shot_before = clock() / 1000;
			castle.player.ak47.shotting = 1;
		}
		//castle.robots.front().retrogressionFlag = 1;
	}
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP)
	{
		if (castle.player.weapon == 3)
		{
			castle.player.ak47.shotting = 0;
		}
	}
	return;
}


