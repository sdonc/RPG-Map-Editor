
// RPG Scenario Editor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRPGScenarioEditorApp: 
// �йش����ʵ�֣������ RPG Scenario Editor.cpp
//

class CRPGScenarioEditorApp : public CWinApp
{
public:
	CRPGScenarioEditorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRPGScenarioEditorApp theApp;
