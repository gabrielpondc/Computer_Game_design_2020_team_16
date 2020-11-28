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
/*****************�Զ�����**************/
void inputKey(int key, int x, int y);
void mykeyboard(unsigned char key, int x, int y); 
void reshapeSize(int w, int h);
void renderScene(void);//ÿ�ֵ��ػ�
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
	
	glutIdleFunc(renderScene);		//��ʼ���лص�
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
	glEnable(GL_DEPTH_TEST);		//������Ȳ��ԡ����������Զ���Զ����ر���ס��ͼ�Σ����ϣ�
	snowman.initScene();
	castle.Init();
	Texture::LoadGLTextures(".\\img\\handGun.bmp", &texture_2);
	if (FSOUND_Init(44100, 32, 0))			// ��������ʼ��Ϊ44khz
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
	//����
	GLfloat fogColor[] = { 0.8,0.8,0.8,0.1 };

	glFogfv(GL_FOG_COLOR, fogColor);   //��ɫ
	glFogf(GL_FOG_START, 100.0f);	  //��ʼ
	glFogf(GL_FOG_END, 1200.0f);		//����
	glFogi(GL_FOG_MODE, GL_LINEAR);  //ģʽ
	glFogf(GL_FOG_DENSITY, 0.1f);	//�ܶ�
	glEnable(GL_FOG);

	ShowCursor(FALSE);

}


void reshapeSize(int w, int h)
{
	// ��ֹ��0��.
	if (h == 0)
		h = 1;
	ratio_ = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//�����ӿ�Ϊ�������ڴ�С
	glViewport(0, 0, w, h);

	//���ÿ��ӿռ�
	gluPerspective(40, ratio_, 0.5, 1200);
	//gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	castle.player.camera.ChangeCamera();
}

//ÿ�ֵ��ػ�
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//�ж���Ϸ����
	castle.Processing();
	glEnable(GL_TEXTURE_2D);		//���ö�ά����
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
	glDisable(GL_TEXTURE_2D);		//�رն�ά����

	glutSwapBuffers();
}
//��¼״̬����ֹ���̷����������
int key_state[4] = { 0 };
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':// ���ζԽ���������޸�ʹ�þ�������
		if (key_state[0] == 1)
			return;
		else
		{
			castle.player.camera.ChangeMoveDirectFB(1);
			key_state[0] = 1;
		}
		break;
	case 'S':
	case 's'://���ζԽ���������޸�ʹ�þ�������
		if (key_state[1] == 1)
			return;
		else
		{
			castle.player.camera.ChangeMoveDirectFB(-1);
			key_state[1] = 1;
		}
		break;
	case 'A':
	case 'a'://���ζԽ���������޸�ʹ�þ�������
		if (key_state[2] == 1)
			return;
		else
		{
			castle.player.camera.ChangeMoveDirectLR(1);
			key_state[2] = 1;
		}
		break;
	case 'D':
	case 'd'://���ζԽ���������޸�ʹ�þ�������
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

//�ͷŰ���
void GamingKey(unsigned char key, int x, int y) {

	switch (key) {
	case 'W':
	case 'w':// ���ζԽ���������޸�ʹ�þ�������
		key_state[0] = 0;
		castle.player.camera.ChangeMoveDirectFB(0);
		break;
	case 'S':
	case 's'://���ζԽ���������޸�ʹ�þ�������
		key_state[1] = 0;
		castle.player.camera.ChangeMoveDirectFB(0);
		break;
	case 'A':
	case 'a'://���ζԽ���������޸�ʹ�þ�������
		key_state[2] = 0;
		castle.player.camera.ChangeMoveDirectLR(0);
		break;
	case 'D':
	case 'd'://���ζԽ���������޸�ʹ�þ�������
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
		glutPassiveMotionFunc(myMotion);//ע������ƶ��ص�����
		glutMotionFunc(myMotion);		//ע��������ƶ��ص�����
		glutMouseFunc(MouseClick);		//ע����갴ť�ص�����
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
//����ƶ�ʱ�������ƶ��е�����
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
			//��װ��ǹ
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


