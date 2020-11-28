#include "stdafx.h"
#include"My_Player.h"

//��Բ��
void Sword::cyLinder(float x0, float y0, float z0, float x1, float y1, float z1) {
	//���Ҫ��AB����仭һ��Բ���壬���������y���ϻ�һ��ͬ���ȵ�Բ����Ȼ�������ת���󣬽�������AB
	GLdouble dir_x = x1 - x0,
		dir_y = y1 - y0,
		dir_z = z1 - z0;
	GLdouble cy_length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);    //���Բ���ĳ���
	static GLUquadricObj* quad_obj = NULL;
	if (quad_obj == NULL)
		quad_obj = gluNewQuadric();
	gluQuadricDrawStyle(quad_obj, GLU_FILL);
	gluQuadricNormals(quad_obj, GLU_SMOOTH);
	glPushMatrix();//����ǰ����ѹ������ջ
	glTranslated(x0, y0, z0);//ƽ�Ƶ���㣬��A��
	double length;
	length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);
	dir_x /= length; dir_y /= length; dir_z /= length;
	GLdouble up_x = 0.0,
		up_y = 1.0,
		up_z = 0.0;
	GLdouble side_x, side_y, side_z;
	//ʵ�������Ĳ��
	side_x = up_y*dir_z - up_z*dir_y;
	side_y = up_z*dir_x - up_x*dir_z;
	side_z = up_x*dir_y - up_y*dir_x;
	length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);
	side_x /= length; side_y /= length; side_z /= length;
	up_x = dir_y*side_z - dir_z*side_y;
	up_y = dir_z*side_x - dir_x*side_z;
	up_z = dir_x*side_y - dir_y*side_x;
	//�õ��任����
	GLdouble m[] = { side_x,side_y,side_z,0.0,
		up_x,up_y,up_z,0.0,
		dir_x,dir_y,dir_z,0.0,
		0.0,0.0,0.0,1.0 };
	glMultMatrixd(m);                //��m������Ե�ǰ����
	GLdouble radius = 0.5;      //��Щ���������Լ�����
	GLdouble slices = 8.0;
	GLdouble stack = 3.0;
	gluCylinder(quad_obj, radius, radius, cy_length, slices, stack);
	glPopMatrix();
}

void Sword::DrawSword(float x, float y, float z, float len)
{
	len = len / 2;
	glColor3f(0.6, 0.6, 0.6);
	cyLinder(x, y - len, z, x - 1, y + len, z - 1);

}
//������
void Sword::Draw()
{

	glPushMatrix();
	glTranslatef(-0.5, -2, -1);
	if (hitting == 1)
	{
		if ((r + step) < -90)
			step = -step;
		if ((r + step) > 0)
			hitting = 0;
		r += step;
		glRotatef(r, -2, 0, 1);
	}
	glTranslated(0, 2, 2);
	DrawSword(0, 0, 0, 4);
	glPopMatrix();
}
void Sword::BeginHit()
{
	r = 0;
	step = -10;
	hitting = 1;
}


void Pistol::Init()
{
	Texture::BuildTexture(".\\img\\handGun.tga", textureid);
}
void Pistol::Draw()
{
	if (bulletNum == 0 && changflag != 1)
	{
		FSOUND_Stream_Play(FSOUND_FREE, sound[7][(soundn++) % 20]);
		Bomb_changing = clock() / 1000;
		changflag = 1;
	}
	if (changflag == 1)
	{
		if (((float)clock() / 1000 - Bomb_changing) > Bomb_chang)
		{
			bulletNum = bullet;
			changflag = 0;
		}
	}
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.9);
	glEnable(GL_TEXTURE_2D);		//���ö�ά����
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textureid);

	glPushMatrix();
	glTranslatef(-0.7, -0.4, 0);
	if (shotting == 1)
	{
		if ((r + step) < -30)
			step = -step;
		if ((r + step) > 0)
			shotting = 0;
		r += step;
		glRotatef(r, 1, 0, 0);

	}
	glRotatef(20, 0, 1, 0);
	//glRotatef(r, 1, 0, 0);
	//glRotatef(20, 0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.37);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.3, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0.3, 0.37);
	glEnd();
	glDisable(GL_TEXTURE_2D);   //ʹ�ú�ر�����
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
void Pistol::BeginShot()
{
	r = 0;
	step = -8;
	shotting = 1;
}


void AK47::Init()
{
	Texture::BuildTexture(".\\img\\ak47.tga", textureid);
}
void AK47::Draw()
{
	if (changflag == 1)
	{
		if (((float)clock() / 1000 - Bomb_changing) > Bomb_chang)
		{
			bulletNum = bullet;
			changflag = 0;
		}
	}
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.9);
	glEnable(GL_TEXTURE_2D);		//���ö�ά����
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textureid);

	glPushMatrix();
	glTranslatef(-1, -0.6, 0);
	if (shott == 1)
	{
		if ((r + step) < -8)
			step = -step;
		if ((r + step) > 0)
			shott = 0;
		r += step;
		glRotatef(r, 1, 0, 0);

	}
	glRotatef(20, 0, 1, 0);
	//glRotatef(r, 1, 0, 0);
	//glRotatef(20, 0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 1.1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.5, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0.5, 1.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);   //ʹ�ú�ر�����
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
void AK47::BeginShot()
{
	r = 0;
	step = -3;
	shott = 1;
}

Player::Player()
{
	blood = 100;
	weapon = 1;
	camera.height = 5;
	camera.speed = 0.3;
	camera.jumping = 1;
	camera.x = 350;
	camera.jump = 20;
	camera.z = 340;
}
void Player::Init()
{
	pistol.Init();
	ak47.Init();
}
//����������ʾ
void Player::ShowAttRange()
{
	glPushMatrix();
	if (weapon == 1)
	{
		glTranslatef(camera.LX, camera.LY, camera.LZ);
		glColor3f(1, 1, 1);
		//ˮƽ��ʼ�ն����Լ�
		glRotatef((camera.angleX / 3.141592) * 180, 0, 1, 0);
		sword.Draw();
	}
	//��ǹ
	else if (weapon == 2)
	{
		glTranslatef(camera.LX, camera.LY, camera.LZ);
		glColor3f(1, 1, 1);
		//ˮƽ��ʼ�ն����Լ�
		glRotatef((camera.angleX / 3.141592) * 180, 0, 1, 0);
		pistol.Draw();
	}
	//��ǹ
	else if (weapon == 3)
	{
		glTranslatef(camera.LX, camera.LY, camera.LZ);
		glColor3f(1, 1, 1);
		//ˮƽ��ʼ�ն����Լ�
		glRotatef((camera.angleX / 3.141592) * 180, 0, 1, 0);
		ak47.Draw();

	}
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ָ����Ϻ���
	//glEnable(GL_BLEND);        //���û��״̬
	//glColor4f(1, 1, 1,0.1);
	//��ֱ����Ƕ�
	//float d = (sqrt(pow(camera.LX - camera.X, 2) + pow(camera.LZ - camera.Z, 2)));
	//float r2= atan(  (d/(camera.LY - camera.Y)) / 3.1415) * 180;
	//ˮƽ����



	//�����幥����Χ
	//glScaled(0.5, 0.5, 0.5);
	//glutSolidSphere(1, 40, 40);
	//glutSolidCube(1);
	glPopMatrix();
	//glDisable(GL_BLEND);  

}
void Player::BeginAttacked()
{
	attackedcolor = 0.3;
	attackedcolorstep = 0.01;
	attackedcolorI = 1;
}

void Player::ShowBlood()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ָ����Ϻ���
	glEnable(GL_BLEND);        //���û��״̬
							   //��Ѫ��
	glColor4f(1, 0, 0, 0.5);
	glRectf(200, 10, blood * 10 + 200, 50);
	glDisable(GL_BLEND);

	//������
	if (attackedcolorI != 1)
		return;
	attackedcolor -= attackedcolorstep;
	if (attackedcolor < 0)
		attackedcolorI = 0;
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ָ����Ϻ���
	glEnable(GL_BLEND);        //���û��״̬
	glColor4f(1, 0.1, 0.1, attackedcolor);
	glTranslatef(1400 / 2, 800, 0);
	const int n = 200;
	const GLfloat a = 0.7f, b = 0.2f;
	int size = 1000;
	const GLfloat P = 3.1415926536f;
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 1; i <= n; i++)
	{
		glVertex2f(size*a*cos(2 * P / i*n), size*b*sin(2 * P / i*n));
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

