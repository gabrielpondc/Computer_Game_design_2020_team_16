

#include "stdafx.h"
#include"My_Texture.h"
//����
//tga��ʽ
bool Texture::LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{
	GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type = GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)
	FILE *file;
	fopen_s(&file, filename, "rb");						// Open The TGA File
	if (file == NULL ||										// Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}
	texture->width = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

															//OpenGL������ֻ��ʹ��24λ����32λ��TGAͼ��
	if (texture->width <= 0 ||								// Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||								// Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}
	texture->bpp = header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData = (GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if (texture->imageData == NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if (texture->imageData != NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}
	//RGB���ݸ�ʽת����������OpenGL��ʹ��
	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp = texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose(file);											// Close The File
															// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs
	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	if (texture[0].bpp == 24)									// Was The TGA 24 Bits
	{
		type = GL_RGB;										// If So Set The 'type' To GL_RGB
	}
	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
	return true;											// Texture Building Went Ok, Return True
}
//bmp��ʽ
bool Texture::LoadT8(GLuint &texture, LPCWSTR filename)
{
	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);
	if (pImage == NULL)		return false;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, pImage->sizeX,
		pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	free(pImage->data);
	free(pImage);
	return true;
}

#define GL_CLAMP_TO_EDGE	0x812F
/***********************************************/
bool Texture::BuildTexture(char *filename, GLuint &texid)					// ����һ��.TGA �ļ����ڴ�
{

	GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };				// û��ѹ����TGA Header
	GLubyte		TGAcompare[12];											// �����Ƚ� TGA Header
	GLubyte		header[6];												// Header�ͷ���������ֽ�
	GLuint		bytesPerPixel;											// ����TGA�ļ���ÿ�������õ����ֽ���
	GLuint		imageSize;												// �����������������ͼ��Ĵ�С
	GLuint		temp;													// ��ʱ����
	GLuint		type = GL_RGBA;											// ��Ĭ�ϵ�GLģʽ����ΪRBGA (32 BPP)
	GLubyte	*imageData;											// ͼ������ (���32bit)
	GLuint	bpp;												// ÿһ���ص�ͼ����ɫ���
	GLuint	width;												// ͼ����
	GLuint	height;												// ͼ��߶�


	HDC			hdcTemp=0;												// DC��������λͼ
	HBITMAP		hbmpTemp=0;												// ������ʱλͼ
	IPicture	*pPicture;												// ����IPicture Interface
	OLECHAR		wszPath[MAX_PATH + 1];									// ͼƬ����ȫ·��
	char		szPath[MAX_PATH + 1];										// ͼƬ����ȫ·��
	long		lWidth;													// ͼ����
	long		lHeight;												// ͼ��߶�
	long		lWidthPixels;											// ͼ��Ŀ��(������Ϊ��λ)
	long		lHeightPixels;											// ͼ��ĸߴ�(������Ϊ��λ)
	GLint		glMaxTexDim;											// ������������ߴ�



	if (strstr(filename, "JPG") || strstr(filename, "bmp") || strstr(filename, "jpg") || strstr(filename, "BMP"))
	{


		if (strstr(filename, "http://"))									// ���·������ http:// ��...
		{
			strcpy(szPath, filename);										// ��·�������� szPath
		}
		else																// ������ļ�����ͼƬ
		{
			GetCurrentDirectoryA(MAX_PATH, szPath);							// ȡ�õ�ǰ·��
			strcat(szPath, "\\");											// ����ַ�"\"
			strcat(szPath, filename);										// ���ͼƬ�����·��
		}

		MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);		// ��ASCII��ת��ΪUnicode��׼��
		HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);

		if (FAILED(hr))														// �������ʧ��
		{
			// ͼƬ����ʧ�ܳ�����Ϣ
			MessageBoxA(HWND_DESKTOP, "TextureLoad Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;													// ���� FALSE
		}

		hdcTemp = CreateCompatibleDC(GetDC(0));								// ���������豸������
		if (!hdcTemp)														// ����ʧ��?
		{
			pPicture->Release();											// �ͷ�IPicture
																			// ͼƬ����ʧ�ܳ�����Ϣ
			MessageBoxA(HWND_DESKTOP, "TextureLoad Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;													// ���� FALSE
		}

		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);					// ȡ��֧�ֵ��������ߴ�

		pPicture->get_Width(&lWidth);										// ȡ��IPicture ��� (ת��ΪPixels��ʽ)
		lWidthPixels = MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
		pPicture->get_Height(&lHeight);										// ȡ��IPicture �߶� (ת��ΪPixels��ʽ)
		lHeightPixels = MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

		// ����ͼƬ����õ�Ч��
		if (lWidthPixels <= glMaxTexDim)									// ͼƬ����Ƿ񳬹��Կ����֧�ֳߴ�
			lWidthPixels = 1 << (int)floor((log((double)lWidthPixels) / log(2.0f)) + 0.5f);
		else																// ����,��ͼƬ�����Ϊ�Կ����֧�ֳߴ�
			lWidthPixels = glMaxTexDim;

		if (lHeightPixels <= glMaxTexDim)									// ͼƬ�߶��Ƿ񳬹��Կ����֧�ֳߴ�
			lHeightPixels = 1 << (int)floor((log((double)lHeightPixels) / log(2.0f)) + 0.5f);
		else																// ����,��ͼƬ�߶���Ϊ�Կ����֧�ֳߴ�
			lHeightPixels = glMaxTexDim;

		// ����һ����ʱλͼ
		BITMAPINFO	bi = { 0 };												// λͼ������
		DWORD		*pBits = 0;												// ָ��λͼBits��ָ��

		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);				// ���ýṹ��С
		bi.bmiHeader.biBitCount = 32;									// 32 λ
		bi.bmiHeader.biWidth = lWidthPixels;							// �������ֵ
		bi.bmiHeader.biHeight = lHeightPixels;						// �߶�����ֵ
		bi.bmiHeader.biCompression = BI_RGB;								// RGB ��ʽ
		bi.bmiHeader.biPlanes = 1;									// һ��λƽ��

																	// ����һ��λͼ�������ǿ���ָ����ɫ����� ������ÿλ��ֵ
		hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);

		if (!hbmpTemp)														// ����ʧ��?
		{
			DeleteDC(hdcTemp);												// ɾ���豸������
			pPicture->Release();											// �ͷ�IPicture
																			// ͼƬ����ʧ�ܳ�����Ϣ
			MessageBoxA(HWND_DESKTOP, "TextureLoad Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;													// ���� FALSE
		}

		SelectObject(hdcTemp, hbmpTemp);									// ѡ����ʱDC�������ʱλͼ����

																			// ��λͼ�ϻ���IPicture
		pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);

		// ��BGRת��ΪRGB����ALPHAֵ��Ϊ255
		for (long i = 0; i < lWidthPixels * lHeightPixels; i++)				// ѭ���������е�����
		{
			BYTE* pPixel = (BYTE*)(&pBits[i]);							// ��ȡ��ǰ����
			BYTE  temp = pPixel[0];									// ��ʱ�洢��һ����ɫ����(��ɫ)
			pPixel[0] = pPixel[2];									// ����ɫֵ�浽��һλ
			pPixel[2] = temp;											// ����ɫֵ�浽����λ
			pPixel[3] = 255;											// ALPHAֵ��Ϊ255
		}
		glGenTextures(1, &texid);											// ��������
																			// ʹ������λͼ�������� �ĵ�������
		glBindTexture(GL_TEXTURE_2D, texid);		// ������
													//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// �����˲�
													//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // �����˲�
													/*
													glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
													glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
													*/
													//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
													//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //��С�����������˲�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//�Ŵ���������˲�
																		 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 


																		 // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
																		 // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
																		 //  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
																		 // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);



																		 // ��������
																		 //glTexImage2D(GL_TEXTURE_2D, 0, 3, lWidthPixels, lHeightPixels, 0, GL_RGB, GL_UNSIGNED_BYTE, pBits);
																		 //	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,lWidthPixels, lHeightPixels,0,GL_RGB,GL_UNSIGNED_BYTE,pBits);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, lWidthPixels, lHeightPixels, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

		DeleteObject(hbmpTemp);												// ɾ������
		DeleteDC(hdcTemp);													// ɾ���豸������

		pPicture->Release();												// �ͷ� IPicture


	}



	else if (strstr(filename, "TGA") || strstr(filename, "tga"))									// ���·������ http:// ��...
	{

		//	GLuint	texID;												// ����ID
		FILE *file = fopen(filename, "rb");									// �� TGA �ļ�

		if (file == NULL)													// �ļ��Ƿ��Ѵ���?
		{
			// ͼƬ����ʧ�ܳ�����Ϣ
			MessageBoxA(HWND_DESKTOP, "TextureLoad Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;													// ����FALSE
		}

		if (fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare)// �Ƿ���ʮ�����ֽڿɶ�?
			|| memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0			// header��������Ҫ���Ƿ����?
			|| fread(header, 1, sizeof(header), file) != sizeof(header))		// ����Ƕ��������ֽ�
		{
			fclose(file);													// ���ʧ��,�ر��ļ�
																			// ͼƬ����ʧ�ܳ�����Ϣ
			MessageBoxA(HWND_DESKTOP, "TextureLoad Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;													// ����FALSE
		}

		width = header[1] * 256 + header[0];						// ȷ����TGA ��� (���ֽ�*256+���ֽ�)
		height = header[3] * 256 + header[2];						// ȷ����TGA �߶� (���ֽ�*256+���ֽ�)

		if (width <= 0											// ����Ƿ�С�ڵ���0
			|| height <= 0										// �߶��Ƿ�С�ڵ���0
			|| (header[4] != 24 && header[4] != 32))							// TGA ��24λ��32λ?
		{
			fclose(file);													// �κ�һ��������, ��ر��ļ�
																			// ͼƬ����ʧ�ܳ�����Ϣ
			MessageBoxA(HWND_DESKTOP, "TextureLoad Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;													// ����FALSE
		}

		bpp = header[4];										// ��ȡTGAÿ�����ص�λ(24 or 32)
		bytesPerPixel = bpp / 8;									// ����8��ȡ�� ÿ�����ص��ֽ�
		imageSize = width*height*bytesPerPixel;		// ����TAG��������Ҫ���ڴ�

		imageData = (GLubyte *)malloc(imageSize);					// ����һ���ڴ�ռ������洢TGA����

		if (imageData == NULL 										// �����洢���ڴ��Ƿ����?
			|| fread(imageData, 1, imageSize, file) != imageSize)	// ͼ���С�Ƿ���ڴ�ռ��С�����
		{
			if (imageData != NULL)									// ͼ�������Ƿ�����
			{
				free(imageData);									// ����� �ͷ�ͼ������
			}
			fclose(file);													// �ر��ļ�
			MessageBoxA(HWND_DESKTOP, "TextureLoad Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;													// ����FALSE
		}

		for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)				// ѭ������ͼ������
		{																	// ������һ�͵����ֽ�(�� �� ��)
			temp = imageData[i];										// ��ͼ�����ݡ�i����ֵ������ʱ������
			imageData[i] = imageData[i + 2];				// ���������ֽڵ�ֵ�浽��һ���ֽ���
			imageData[i + 2] = temp;								// ����ʱ������ֵ��������ֽ�(��һ�ֽڵ�ֵ)
		}

		fclose(file);														// �ر��ļ�

																			//����һ������
		glGenTextures(1, &texid);									// ����OpenGL����ID

		glBindTexture(GL_TEXTURE_2D, texid);						// ������
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// �����˲�
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// �����˲�


		if (bpp == 24)												// TGAͼƬ�ǲ��� 24 λ��
		{
			type = GL_RGB;													// ����ǽ�'type'����Ϊ GL_RGB
		}

		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);

		free(imageData);
	}


	DeleteObject(hbmpTemp);												// ɾ������
	DeleteDC(hdcTemp);													// ɾ���豸������
	return TRUE;														// �������ɹ���������ȷ
}


int Texture::LoadGLTextures(char *Filename, GLuint *ttexture)//ttexture[i]Ϊ�������������ݵ�����,�ɸ���
{
	FILE *File;
	BITMAPINFOHEADER header;
	BYTE *texture;//texture���������RGBA texture[width][height][4]
	int width, height, m, j;
	unsigned char *image;
	File = fopen(Filename, "rb");
	//��ȡBMP��Ϣͷ������14�ֽ��ļ�ͷ
	if (File) {
		fseek(File, 14, SEEK_SET);
		fread(&header, sizeof(BITMAPINFOHEADER), 1, File);
	}
	else return FALSE;
	//��ȡ����
	width = header.biWidth;
	height = header.biHeight;
	//Ϊimage�������ؿռ䣬��ȡͼƬ���ݣ�Ϊtexture����width*height*4����λ�ռ�������������
	image = (unsigned char *)malloc(width*height * 3);
	fread(image, sizeof(unsigned char), width*height * 3, File);//Ψһ�Ĳ���֮�����ڽ�3�ֽ����ض�Ϊһά�ַ���
	texture = (BYTE *)malloc(width*height * 4);// Ψһ�Ĳ���֮�����ڽ�4�ֽ����ض�Ϊһά�ַ���
											   //���´��뽫��texture�����У�һ����˵ΪBlue Green Red Alpha��ʽ(24λͼ��ʽ),��������ʹ��BGRAģʽ
											   /****************************************�޸�ģ��,ͨ�����������޸�ͼƬ��ʾ��:*************************************************************/
											   //���δ��뽫����ɫ���ص�͸����(Alpha)��Ϊ100%,������ɫ��Ϊ0%
	for (m = 0; m < width; m++)
	{
		for (j = 0; j < height; j++)
		{
			//����ɫֵд�� 
			texture[m*width * 4 + j * 4] = image[m*width * 3 + j * 3];
			texture[m*width * 4 + j * 4 + 1] = image[m*width * 3 + j * 3 + 1];
			texture[m*width * 4 + j * 4 + 2] = image[m*width * 3 + j * 3 + 2];
			//����alphaֵ,�����ɫΪ͸��ɫ 
			if (texture[m*width * 4 + j * 4] == 0 && texture[m*width * 4 + j * 4 + 1] == 0 && texture[m*width * 4 + j * 4 + 2] == 0)
				texture[m*width * 4 + j * 4 + 3] = 0;                 //͸����alpha=0 
			else
				texture[m*width * 4 + j * 4 + 3] = 255;           //��͸����alpha=255
		}
	}
	//ttexture[i]Ϊ�����������
	//�������������Լ�������
	glGenTextures(1, ttexture);
	glBindTexture(GL_TEXTURE_2D, *ttexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_BGRA, GL_UNSIGNED_BYTE, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glAlphaFunc(GL_GREATER, 0.5);//ʹAlphaֵ��Ч
								 //�����������,�����ͷſռ�
	free(texture);
	free(image);						// �ͷ�ͼ������
	return TRUE;
}