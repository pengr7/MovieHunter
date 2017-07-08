#include "skybox.h"
#include <iostream>
#include "CBMPLoader.cpp"
#include <stdio.h>
#include "Dependencies\freeglut\freeglut.h"

const unsigned int MAP_WIDTH = 1024;
const unsigned int CELL_WIDTH = 16;
const unsigned int MAP = MAP_WIDTH * CELL_WIDTH / 2;

CSkyBox::CSkyBox()
{
	;
}

CSkyBox::~CSkyBox()
{
	/** ɾ�����������ռ�õ��ڴ� */
	for (int i = 0; i< 6; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1, &m_texture[i].ID);
	}

}

/** ��պг�ʼ�� */
bool CSkyBox::Init()
{
	//char filename[128];                                         /**< ���������ļ��� */
	//for (int i = 0; i < 128; i++)
	//	filename[i] = '0';
	//char *bmpName[] = { "back","front","bottom","top","left","right" };
	char *bmpName[] = { "t_bk.bmp\0","t_ft.bmp\0","t_dn.bmp\0","t_up.bmp\0","t_l.bmpf\0","t_rt.bmp\0" };

	for (int i = 0; i< 6; i++)
	{
		char filename[128];
		//memset(filename, 128, 0);
		printf("data/%s", bmpName[i]);
		printf("\n");
		//strcat(filename, bmpName[i]);
		int j = 0;
		for (j = 0; bmpName[j]; j++) {
			filename[j] = bmpName[i][j];
		}
		filename[j] = '\0';
		printf("%s\n", filename);
		if (!m_texture[i].LoadBitmap(filename))                     /**< ����λͼ�ļ� */
		{
			//MessageBox(NULL,(LPCWSTR)"װ��λͼ�ļ�ʧ�ܣ�", (LPCWSTR)"����", MB_OK);    /**< �������ʧ���򵯳��Ի��� */
			printf("\nreading image failed");
			int tmp;
			std::cin >> tmp;
			exit(0);
		}
		glGenTextures(1, &m_texture[i].ID);                        /**< ����һ������������� */

		glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);             /**< ����������� */
																   /** �����˲�: */
																   /*
																   ����GL_TEXTURE_WRAP_S��GL_TEXTURE_WRAP_Tͨ��������ΪGL_REPEAT��GL_CLAMP���ַ�ʽ��
																   �������Ķ���δ��������ʱ��GL_REPEAT��ʾ����Ĳ������ظ��ķ�ʽ��䣻GL_CLAMP��ʾ����Ĳ�����������Ե������������䡣
																   ��ʵ�ʻ����У�����һ�����GL_CLAMP_EDGE��������������˽ӷ촦��ϸ�ߣ���ǿ����պе���ʵ�С�
																   */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		/** �������� */
		printf("%s", m_texture[i].image);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
			m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_texture[i].image);
	}
	return true;

}

/** ������պ� */
void  CSkyBox::CreateSkyBox(float x, float y, float z,
	float box_width, float box_height,
	float box_length)
{
	/** ��ó����й���״̬ */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);

	/** ������պг� �� �� */
	float width = MAP * box_width / 8;
	float height = MAP * box_height / 8;
	float length = MAP * box_length / 8;

	/** ������պ�����λ�� */
	x = x + MAP / 8 - width / 2;
	y = y + MAP / 24 - height / 2;
	z = z + MAP / 8 - length / 2;

	glDisable(GL_LIGHTING);            /**< �رչ��� */

									   /** ��ʼ���� */
	glPushMatrix();
	glTranslatef(-x, -y, -z);

	/** ���Ʊ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** ����ǰ�� */
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);

	glEnd();

	/** ���Ƶ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[2].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);

	glEnd();

	/** ���ƶ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[5].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();                 /** ���ƽ��� */

	if (lp)                         /** �ָ�����״̬ */
		glEnable(GL_LIGHTING);

}
