#include "stdafx.h"
#include "GV.h"

GV* GV::gv = NULL;//初始化静态变量
GV::GV()
{
	//初始化ImageLoader
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
		AfxMessageBox(L"加载用户数据异常！");
		exit(-1);
	}
}

void GV::LoadAllMap()
{
	EasyFile ef;
	EasyPath ep;

	ef.EnumFile(ep.GetProgramDir() + L"maps", mapFiles, L"map");
}
