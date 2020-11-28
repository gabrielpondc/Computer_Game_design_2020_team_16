#include "stdafx.h"
#include"My_CastleEx.h"

CastleEx::CastleEx()
{
	Pattern = 0;
}
void CastleEx::Init()
{
	Texture::BuildTexture(".\\img\\cover.jpg", Interface[0]);
	Texture::BuildTexture(".\\img\\help.jpg", Interface[1]);
	scene.Init();
	skyBox.LoadTexture();
	player.Init();
	player.camera.terrain = &(scene.terrain);
	//robots.push_back(Robot(rand() % 700, 0, rand() % 700, 0.6, 10000,1));

}


//�ж�ǹе�Ի������ܵ����˺�
void CastleEx::GunDamage()
{
	float f1 = (clock() / 1000.0 - player.ak47.shot_before);
	//�ж��Ƿ�������ǹ
	if (player.weapon == 3 && player.ak47.shotting == 1 && f1 > player.ak47.shot_interval)
	{
		if (player.ak47.bulletNum == 0 && player.ak47.changflag == 0)
		{
			FSOUND_Stream_Play(FSOUND_FREE, sound[6][(soundn++) % 20]);
			player.ak47.Bomb_changing = clock() / 1000;
			player.ak47.changflag = 1;
		}
		else
		{
			if (player.ak47.changflag == 1)
				return;
			FSOUND_Stream_Play(FSOUND_FREE, sound[0][(soundn++) % 20]);
			//��װ��ǹ
			player.ak47.BeginShot();
			player.ak47.shot_before = clock() / 1000.0;
			player.ak47.BeginShot();
			player.camera.AddangleY(0.02);
			bullet.push_back(Bullet(player.camera.X, player.camera.Y, player.camera.Z, player.camera.LX, player.camera.LY, player.camera.LZ));
			player.ak47.bulletNum -= 1;
		}

	}
	if (bullet.size() == 0)
		return;
	//����ÿһ���ӵ���ѭ��
	std::vector<Bullet>::iterator it;
	for (it = bullet.begin(); it != bullet.end();)
	{
		
		//��ȥ�ӵ��ж�
		if ((*it).x<0 || (*it).x>700 || (*it).z<0 || (*it).z>700 || (*it).y<0 || (*it).y>400)
			it = bullet.erase(it);
		else
		{
			//���н�ʬ��ײ�ж�
			bool judge = false;
			std::vector<Robot>::iterator it2;
			for (it2 = robots.begin(); it2 != robots.end();)
			{
				if ((*it2).live == false)
				{
					it2++;
					continue;
				}
				//��ײ���
				judge = (*it).JudgeHit((*it2).x, (*it2).y, (*it2).z,3.5*(*it2).size);
				if (judge)
				{
					(*it2).retrogressionFlag = 1;
					(*it2).blood -= player.weapon == 2 ? player.pistol.damage : player.ak47.damage;
					it = bullet.erase(it);
					break;
				}
				it2++;
			}
			if (!judge)
			{
				(*it).DrawBullet();
				it++;
			}
		}
	}
}


//�жϽ�ս�����Ի����˵��˺�
void CastleEx::AxeDamage(float x, float y, float z)
{
	std::vector<Robot>::iterator it;
	for (it = robots.begin(); it != robots.end();)
	{
		if ((*it).live == false)
		{
			it++;
			continue;
		}
		float x1 = (*it).x, y1 = (*it).y, z1 = (*it).z;
		//��ײ���
		//ֱ���ж�����֮��ľ��룬��ײ��Χ��Բ��
		if (sqrt(pow(x - x1, 2) + pow(y - y1, 2) + pow(z - z1, 2)) < 10* (*it).size)
		{
			FSOUND_Stream_Play(FSOUND_FREE, sound[2][(soundn++) % 20]);
			(*it).judgeDamage(player.sword.damage);
			(*it).retrogressionFlag = 1;
		}
		it++;
	}
}

void CastleEx::DrawRobot(float x, float y, float z)
{
	std::vector<Robot>::iterator it;
	glPushMatrix();
	for (it = robots.begin(); it != robots.end();)
	{
		if ((*it).retrogressionFlag == 1)
		{
			(*it).RobotRetrogression(20);
		}
		/****************************************************/
		//�ӽ�Ŀ���ʱ�Զ�����
		double range = 5; //***************�ӽ���Χ Խ�� - Խ�ӽ�
		
		if (abs(x - (*it).x) < range && abs(z - (*it).z) < range)
		{
			if ((*it).attackFlag == false)
			{
				(*it).robotStartAttack();
			}
		}
		(*it).y = scene.terrain.GetHeight((*it).x, (*it).z) + 5 * (*it).size;////////////////////////////////
		//��ʬ����Ŀ������
		if ((*it).tryGoToGoalFlag == 1) //�Ƿ�����
		{
			double toX = x;
			double toZ = z;
			//*************��ʬ�߽���Ҷ����ֹͣ
			if (!(abs(toX - (*it).x) < 3 && abs(toZ - (*it).z) < 3))
			{
				(*it).moveToPeople(toX, 0, toZ);
			}
		}
		(*it).drawRobot();
		judgeAlive(&(*it));

		//�����˵�����ת�Ƕ�
		if ((*it).live == false)
		{
			if ((*it).fallangle <= 90)
			{/******************�����ٶ�*****************/
				(*it).fallangle+=4;
			}
		}
		if ((*it).live == true)
		{
			/****************************************************/
			int attackStepAngle = 5; //�����˹���ʱ��ÿˢ��һ���ǵĵ�λ�Ƕ�

									 //��ʬ����ʱ����ת�ĽǶ�
			if ((*it).attackFlag == true) //��ʬ����ʱ
			{
				//����
				if ((*it).leftAttackFinishFlag == false)//��������Ƿ���ɹ���
				{
					if ((*it).leftAttackHandFlag == false) //�������Ͼ�
					{
						((*it).leftAttackHandAngle) += attackStepAngle; //�Ƕ�++
						if ((*it).leftAttackHandAngle >= (*it).attackUpMaxAngle) //���ֵ���180��ʱ
						{
							(*it).leftAttackHandFlag = true; //ת��
						}
					}
					else //��������̧
					{
						((*it).leftAttackHandAngle) -= attackStepAngle; //�Ƕ�--
						if ((*it).leftAttackHandAngle <= 0) //���ֵ���0��
						{
							(*it).leftAttackHandFlag = false;//ת��
							(*it).rtheta = 0;
							(*it).leftAttackFinishFlag = true; //���ֹ��������
						}
					}
				}
				//����
				if ((*it).rightAttackFinishFlag == false)//��������Ƿ���ɹ���
				{
					if ((*it).rightAttackHandFlag == false) //������for���Ͼ�
					{
						((*it).rightAttackHandAngle) += attackStepAngle;//�Ƕ�++

						if ((*it).rightAttackHandAngle >= (*it).attackUpMaxAngle) //���ֵ���180��
						{
							(*it).rightAttackHandFlag = true;//ת��
						}
					}
					else
					{
						((*it).rightAttackHandAngle) -= attackStepAngle; //�Ƕ�--
						if ((*it).rightAttackHandAngle <= 0) //���ֵ���0��
						{
							(*it).rightAttackHandFlag = false;//ת��
							(*it).rtheta = 0;
							(*it).rightAttackFinishFlag = true; //���ֹ��������
						}
					}
				}
				/***************��ʬ��������******************/
				if ((*it).leftAttackFinishFlag == true && (*it).rightAttackFinishFlag == true)
				{
					//��ʬ������Χ
					if (sqrt(pow((*it).x - player.camera.X, 2) + pow((*it).y - player.camera.Y, 2) + pow((*it).z - player.camera.Z, 2)) < 16 * (*it).size)
					{
						player.BeginAttacked();
						player.blood -= (*it).atk;
						FSOUND_Stream_Play(FSOUND_FREE, sound[8][(soundn++) % 20]);
					}
					(*it).attackFlag = false;
				}
			}
		}
		//(*it).drawRobot();
		glPopMatrix();
		it++;
	}
}

void CastleEx::judgeAlive(Robot *r)
{
	if (r->retrogressionTime <= 0)
	{
		r->retrogressionFlag = 0; //�ı�����
		if (r->blood <= 0&& r->live)
		{
			r->live = false;
			r->tryGoToGoalFlag = 0;
			robotNum -= 1; killRobotNum += 1;
		}
	}
}

void CastleEx::generateRobot()
{
	//�齱�ͽ�ʬ�����ֵ�����ֵ
	int rt = (100 - (clock() / 1000) / 5);
	if (rand() % (rt < 10 ? 10 : rt) == 1)
	{
		robots.push_back(Robot(rand() % 700, 0, rand() % 700, 0.6, 100, 1 + (clock() / 1000) / 100 > 3 ? 3 : 1 + (clock() / 1000) / 100));
		robotNum += 1;
	}
	if (player.blood <= 0)
	{
		endTime = (clock() / 1000) - time;
		ChangePattern(3);
		Sleep(1000);
		FSOUND_Stream_Play(FSOUND_FREE, sound[10][0]);
	}
}

string tostr(int num)
{
	char c[10];
	_itoa(num, c, 10);
	return c;
}
//��ʾ��ǰ��Ϣ
void CastleEx::ShowMess()
{
	Font::selectFont(30, ANSI_CHARSET, "PixelGameFont");
	glColor3f(1, 1, 1);
	glRasterPos2f(50, WINDOW_HEIGHT-50);
	const string s = "	ZOMBIES:" + tostr(robotNum) + "	KILLED:" + tostr(killRobotNum);
	Font::drawCNString(s.c_str());

	glRasterPos2f(WINDOW_WIDTH/2, WINDOW_HEIGHT - 50);
	const string s1 = tostr(clock() / 1000 - time);
	Font::drawCNString(s1.c_str());

	if (player.weapon == 2)
	{
		Font::selectFont(60, ANSI_CHARSET, "PixelGameFont");
		glColor3f(1, 1, 1);
		glRasterPos2f(WINDOW_WIDTH - 300, 100);
		const string s = tostr(player.pistol.bulletNum);
		Font::drawCNString(s.c_str());
	}
	else if (player.weapon == 3)
	{
		Font::selectFont(60, ANSI_CHARSET, "PixelGameFont");
		glColor3f(1, 1, 1);
		glRasterPos2f(WINDOW_WIDTH - 300, 100);
		const string s = tostr(player.ak47.bulletNum);
		Font::drawCNString(s.c_str());
	}

}

//�ı�ؿ�ģʽ
void CastleEx::ChangePattern(int p)
{
	Pattern = p;
}

//��ʼ����
void CastleEx::ShowBeging()
{
	//2dģʽ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);		//���ö�ά����
	glBindTexture(GL_TEXTURE_2D, Interface[0]);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(WINDOW_WIDTH, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);		//�رն�ά����
}

//��������
void CastleEx::ShowHelp()
{
	glEnable(GL_TEXTURE_2D);		//���ö�ά����
	glBindTexture(GL_TEXTURE_2D, Interface[1]);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(WINDOW_WIDTH, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);		//�رն�ά����
}

//��������
void CastleEx::ShowEnd()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Font::selectFont(150, ANSI_CHARSET, "blood");
	glColor3f(128, 0, 0);
	glRasterPos2f(WINDOW_WIDTH / 2 - 450, WINDOW_HEIGHT / 2 + 100);
	const string s = "  Game Over";
	Font::drawCNString(s.c_str());

	Font::selectFont(40, ANSI_CHARSET, "PixelGameFont");
	glColor3f(1, 1, 1);
	glRasterPos2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 100);
	const string s1 = "  Final Killed: " + tostr(killRobotNum);
	Font::drawCNString(s1.c_str());

	Font::selectFont(40, ANSI_CHARSET, "PixelGameFont");
	glColor3f(1, 1, 1);
	glRasterPos2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 250);
	const string s2 = "  Survival Time:" + tostr(endTime) + "s";
	Font::drawCNString(s2.c_str());

	Font::selectFont(20, ANSI_CHARSET, "PixelGameFont");
	glColor3f(1, 1, 1);
	glRasterPos2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 350);
	const string s3 = "Press (F9) Quit the Game";
	Font::drawCNString(s3.c_str());
}


//һ������
void CastleEx::Processing()
{
	if (Pattern == 0)
	{
		ShowBeging();
	}
	else if (Pattern == 1)//����
	{
		ShowHelp();
	}
	else if (Pattern == 2)//����ģʽ
	{
		//3dģʽ
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40, 1.0f*SCREEN_WIDTH / SCREEN_HEIGHT, 0.5, 1200);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//�ı��ӽ�
		player.camera.ChangeCamera();
		//���������պ�
		skyBox.drawSkyBox(player.camera.x, player.camera.y, player.camera.z);
		GunDamage();
		DrawRobot(player.camera.x, player.camera.y, player.camera.z);
		//����Ҫ����
		scene.DrawScene();
		player.ShowAttRange();

		//2dģʽ
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		scene.Draw2D();
		ShowMess();
		player.ShowBlood();

		//��ʬ����
		generateRobot();
	}
	else if (Pattern == 3)//��Ϸ����
	{
		ShowEnd();
	}
	else if (Pattern == 4)//����
	{
		ShowHelp();
	}

}





