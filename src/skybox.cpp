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
	/** 删除纹理对象及其占用的内存 */
	for (int i = 0; i< 6; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1, &m_texture[i].ID);
	}

}

/** 天空盒初始化 */
bool CSkyBox::Init()
{
	//char filename[128];                                         /**< 用来保存文件名 */
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
		if (!m_texture[i].LoadBitmap(filename))                     /**< 载入位图文件 */
		{
			//MessageBox(NULL,(LPCWSTR)"装载位图文件失败！", (LPCWSTR)"错误", MB_OK);    /**< 如果载入失败则弹出对话框 */
			printf("\nreading image failed");
			int tmp;
			std::cin >> tmp;
			exit(0);
		}
		glGenTextures(1, &m_texture[i].ID);                        /**< 生成一个纹理对象名称 */

		glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);             /**< 创建纹理对象 */
																   /** 控制滤波: */
																   /*
																   其中GL_TEXTURE_WRAP_S，GL_TEXTURE_WRAP_T通常可设置为GL_REPEAT或GL_CLAMP两种方式。
																   当待填充的多边形大于纹理的时候，GL_REPEAT表示多余的部分用重复的方式填充；GL_CLAMP表示多余的部分用相连边缘的相邻像素填充。
																   在实际绘制中，我们一般采用GL_CLAMP_EDGE来处理，这就消除了接缝处的细线，增强了天空盒的真实感。
																   */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		/** 创建纹理 */
		printf("%s", m_texture[i].image);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
			m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_texture[i].image);
	}
	return true;

}

/** 构造天空盒 */
void  CSkyBox::CreateSkyBox(float x, float y, float z,
	float box_width, float box_height,
	float box_length)
{
	/** 获得场景中光照状态 */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);

	/** 计算天空盒长 宽 高 */
	float width = MAP * box_width / 8;
	float height = MAP * box_height / 8;
	float length = MAP * box_length / 8;

	/** 计算天空盒中心位置 */
	x = x + MAP / 8 - width / 2;
	y = y + MAP / 24 - height / 2;
	z = z + MAP / 8 - length / 2;

	glDisable(GL_LIGHTING);            /**< 关闭光照 */

									   /** 开始绘制 */
	glPushMatrix();
	glTranslatef(-x, -y, -z);

	/** 绘制背面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** 绘制前面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);

	glEnd();

	/** 绘制底面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[2].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);

	glEnd();

	/** 绘制顶面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);

	glEnd();

	/** 绘制左面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** 绘制右面 */
	glBindTexture(GL_TEXTURE_2D, m_texture[5].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();                 /** 绘制结束 */

	if (lp)                         /** 恢复光照状态 */
		glEnable(GL_LIGHTING);

}
