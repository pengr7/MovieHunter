#pragma once

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "CBMPLoader.h"
#include "Vector.h"
//#include "Camera.h"

#define GL_CLAMP_TO_EDGE    0x812F

/** ��պ��� */
class CSkyBox
{
public:
	/** ���캯�� */
	CSkyBox();
	~CSkyBox();

	/** ��ʼ�� */
	bool Init();

	/** ��Ⱦ��� */
	void  CreateSkyBox(float x, float y, float z,
		float width, float height,
		float length);

private:

	CBMPLoader  m_texture[6];   /**< ��պ����� */

};


#endif ///__SKYBOX_H__