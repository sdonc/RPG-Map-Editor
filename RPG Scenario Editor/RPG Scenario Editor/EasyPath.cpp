#include "stdafx.h"
#include "EasyPath.h"


EasyPath::EasyPath()
{
}


EasyPath::~EasyPath()
{
}

CString EasyPath::GetProgramDir()
{
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);
	(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串  

	return CString(_szPath);
}

CString EasyPath::GetProgramName(bool suffix)
{
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);

	CString name(_szPath);

	if (suffix)
	{
		return name.Right(name.GetLength() - name.ReverseFind('\\') - 1);
	}
	else
	{
		int p1,p2;
		p1 = name.ReverseFind('\\');

		p2 = name.Find('.', p1+1);

		if (p2==-1)//该文件无后缀
		{
			return name.Right(name.GetLength() - p1 - 1);
		}
		else
		{
			return name.Mid(p1+1, p2-p1-1);
		}
	}

	
}
