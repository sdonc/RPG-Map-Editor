#include "stdafx.h"
#include "GV.h"

GV* GV::gv = NULL;//��ʼ����̬����
GV::GV()
{
	//��ʼ��ImageLoader
	imageLoader = new ImageLoader();
	
}


GV::~GV()
{
}

void GV::LoadImageSrc()
{
	imageLoader->BeginLoad();
}

void GV::LoadUserData()
{
	if (user.LoadUserData() == false)
	{
		AfxMessageBox(L"�����û������쳣��");
		exit(-1);
	}
}

void GV::LoadAllMap()
{
	EasyFile ef;
	EasyPath ep;

	ef.EnumFile(ep.GetProgramDir() + L"maps", mapFiles, L"map");
}
