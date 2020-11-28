#include "stdafx.h"
#include"My_Terrain.h"

//地形
void Terrain::InitTerrain()
{
	float h = 10;
	int n = 1;//缩放倍率
	ofstream OutFile("Test.txt");

	Texture::LoadT8((texture_1), L".\\img\\Terrain.BMP");
	//unsigned char    *g_imageData;//
	int index = 0;
	int Vertex;
	for (int i = 0; i <= MAP_W; i++)
	{
		OutFile << (i % 10);
	}
	for (int z = 0; z < MAP_W; z++)
	{
		OutFile << '\n' << (z % 10);
		for (int x = 0; x < MAP_W; x++)
		{
			Vertex = z * MAP_W + x;
			g_terrain[Vertex][0] = float(x)*MAP_SCALE;		//x
															//g_terrain[Vertex][1] = (float)(g_imageData[(z*MAP_W + x) * 3] / 3); //y
			g_terrain[Vertex][1] = ((rand() % (int)h) + 2)*n; //y
			OutFile << (g_terrain[Vertex][1] < 10 ? "  " : " ") << (g_terrain[Vertex][1]);

			g_terrain[Vertex][2] = float(z)*MAP_SCALE;			//z
			g_texcoord[Vertex][0] = (float)x;
			g_texcoord[Vertex][1] = (float)z;
			g_index[index++] = Vertex;
			g_index[index++] = Vertex + MAP_W;
		}
	}
	OutFile << '\n';
	OutFile.close();
}
//读取三个字符并转成数字
int Terrain::readNum(int *cursor, char str[MAP_W * 3 + 10])
{
	char c[4];
	for (int i = 0; i < 3; i++)
	{
		c[i] = str[(*cursor)++];
	}
	c[3] = '\0';
	return atoi(c);
}
//修改三个字符的数字
void Terrain::changeNum(int cursor, char str[], int num)
{
	str[cursor - 1] = num - (num / 10) * 10 + 48;
	if (num >= 10)
	{
		str[cursor - 2] = ((num / 10)) + 48;
	}
	else
	{
		str[cursor - 2] = ' ';
	}
	str[cursor - 3] = ' ';
}
//读取已有的文件
void Terrain::InitTerrain_Read()
{
	ifstream readFile("Test.txt");
	char head[MAP_W + 10];

	char ch; int i = 0;
	for (i = 0; i < MAP_W * 3 + 10; i++)
	{
		if ((ch = readFile.get()) != '\n')
			head[i] = ch;
		else
			break;
	}
	head[i] = '\0';
	//readFile >> head;

	Texture::LoadT8((texture_1), L".\\img\\Terrain.BMP");
	//unsigned char    *g_imageData;//不知道啥
	int index = 0;
	int Vertex;
	int cursor;
	for (int z = 0; z < MAP_W; z++)
	{
		char temp[MAP_W * 3 + 10];

		//读取有空格的一行
		int ch, i;
		while ((ch = readFile.get()) == ' ');
		for (i = 0; i < MAP_W * 3 + 10; i++)
		{
			if ((ch = readFile.get()) != '\n')
				temp[i] = ch;
			else
				break;
		}
		temp[i] = '\0';
		//readFile >> temp;

		cursor = 1;

		for (int x = 0; x < MAP_W; x++)
		{
			int h;// = temp[x + 1] - 48;
			h = readNum(&cursor, temp);
			Vertex = z * MAP_W + x;
			g_terrain[Vertex][0] = float(x)*MAP_SCALE;		//x
															//g_terrain[Vertex][1] = (float)(g_imageData[(z*MAP_W + x) * 3] / 3); //y
			g_terrain[Vertex][1] = h; //y

			g_terrain[Vertex][2] = float(z)*MAP_SCALE;		//z
			g_texcoord[Vertex][0] = (float)x;
			g_texcoord[Vertex][1] = (float)z;
			g_index[index++] = Vertex;
			g_index[index++] = Vertex + MAP_W;

		}
	}
	readFile.close();
}

//修改现有地图的某些地形
//x1 左上角左边 x2右下角坐标
void Terrain::InitTerrain_Change(int x1, int z1, int x2, int z2)
{
	fstream readFile("Test.txt");
	char head[MAP_W + 10];

	char ch; int i = 0;
	for (i = 0; i < MAP_W * 3 + 10; i++)
	{
		if ((ch = readFile.get()) != '\n')
			head[i] = ch;
		else
			break;
	}
	head[i] = '\0';

	string ss = head;
	string s = ss + "\n";

	Texture::LoadT8((texture_1), L".\\img\\Terrain.BMP");
	int index = 0;
	int Vertex;
	int cursor;
	for (int z = 0; z < MAP_W; z++)
	{
		char temp[MAP_W * 3 + 10];

		int ch, i;
		for (i = 0; i < MAP_W * 3 + 10; i++)
		{
			if ((ch = readFile.get()) != '\n')
				temp[i] = ch;
			else
				break;
		}
		temp[i] = '\0';
		//readFile >> temp;
		//s += temp[0];
		cursor = 1;
		for (int x = 0; x < MAP_W; x++)
		{
			int h;// = temp[x + 1] - 48;
			h = readNum(&cursor, temp);

			Vertex = z * MAP_W + x;
			g_terrain[Vertex][0] = float(x)*MAP_SCALE;		//x

															//在该范围内
			if (z >= z1&&z <= z2&&x >= x1&&x <= x2)
			{
				/*************************************************************************/
				//h = THEHEIGHT;

				//最高最低差值
				float maxh = 30.0; float minh = 1;

				//中心点
				float X = (float)(x2 - x1) / 2 + x1;
				float Z = (float)(z2 - z1) / 2 + z1;
				//总距离
				float Distance = sqrt((x1 - X)*(x1 - X) + (z1 - Z)*(z1 - Z));
				//现距离
				float distance = sqrt((x - X)*(x - X) + (z - Z)*(z - Z));
				//比率
				float p = 1 - distance / Distance;

				h = (maxh - minh)*p + minh + rand() % 2;
				changeNum(cursor, temp, h);
			}

			g_terrain[Vertex][1] = h; //y

			g_terrain[Vertex][2] = float(z)*MAP_SCALE;		//z
			g_texcoord[Vertex][0] = (float)x;
			g_texcoord[Vertex][1] = (float)z;
			g_index[index++] = Vertex;
			g_index[index++] = Vertex + MAP_W;
		}
		ss = temp;
		s += ss + "\n";

	}
	readFile.close();
	ofstream OutFile("Test2.txt");
	OutFile.write(s.c_str(), s.length());
	OutFile.close();
	int y = 0;
}
//画山
void Terrain::DrawSand()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, g_terrain);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, g_texcoord);

	glEnable(GL_TEXTURE_2D);		//启用二维文理

	glBindTexture(GL_TEXTURE_2D, texture_1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//纹理过滤函数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glColor3f(1, 1, 1);
	for (int z = 0; z < MAP_W - 1; z++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, MAP_W * 2, GL_UNSIGNED_INT, &g_index[z*MAP_W * 2]);
		glDrawElements(GL_LINE_STRIP, MAP_W * 2, GL_UNSIGNED_INT, &g_index[z*MAP_W * 2]);

	}
	glDisable(GL_TEXTURE_2D);
}

//获取某点高度
float Terrain::GetHeight(float x, float z)
{
	float CameraX = x / MAP_SCALE;
	float CameraZ = z / MAP_SCALE;
	int Col0 = int(CameraX);
	int Row0 = int(CameraZ);
	int Col1 = Col0 + 1;
	int Row1 = Row0 + 1;
	if (Col1 > MAP_W)	Col1 = 0;
	if (Row1 > MAP_W)	Row1 = 0;
	float h00 = g_terrain[Col0 + Row0*MAP_W][1];
	float h01 = g_terrain[Col1 + Row0*MAP_W][1];
	float h11 = g_terrain[Col1 + Row1*MAP_W][1];
	float h10 = g_terrain[Col0 + Row1*MAP_W][1];
	float tx = CameraX - int(CameraX);
	float ty = CameraZ - int(CameraZ);
	float txty = tx * ty;
	return h00*(1.0f - ty - tx + txty)
		+ h01*(tx - txty)
		+ h11*txty
		+ h10*(ty - txty);
}
