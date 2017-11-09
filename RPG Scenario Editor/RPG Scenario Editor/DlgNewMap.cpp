// DlgNewMap.cpp : 实现文件
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgNewMap.h"
#include "afxdialogex.h"

// DlgNewMap 对话框

IMPLEMENT_DYNAMIC(DlgNewMap, CDialogEx)

DlgNewMap::DlgNewMap(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_NEW_MAP, pParent)
	, m_mapName(_T(""))
	, m_mapWidth(_T(""))
	, m_mapHeigth(_T(""))
{

}

DlgNewMap::~DlgNewMap()
{
}

void DlgNewMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_mapName);
	DDX_Text(pDX, IDC_EDIT2, m_mapWidth);
	DDX_Text(pDX, IDC_EDIT3, m_mapHeigth);

}


BEGIN_MESSAGE_MAP(DlgNewMap, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_NEW_MAP, &DlgNewMap::OnBnClickedButtonNewMap)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_NEW_MAP, &DlgNewMap::OnBnClickedButtonCancelNewMap)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// DlgNewMap 消息处理程序

void DlgNewMap::OnBnClickedButtonNewMap()
{
	UpdateData(true);
	EasyFile ef;
	EasyPath ep;
	
	
	if (m_mapName.GetLength()==0)
	{
		AfxMessageBox(L"请输入地图名。");
		return;
	}
	else if (m_mapName.Find(L"\\")!=-1 || 
			m_mapName.Find(L"/")!= -1 ||
		m_mapName.Find(L":") != -1 ||
		m_mapName.Find(L"*") != -1 ||
		m_mapName.Find(L"?") != -1 ||
		m_mapName.Find(L"<") != -1 ||
		m_mapName.Find(L">") != -1 ||
		m_mapName.Find(L"\"") != -1
		)
	{
		//检查字符集
		AfxMessageBox(L"地图名包含不合法字符【\\ / : * ? < > : \"】，请检查。");
		return;
	}
	else
	{
		//检查文件是否重复
		gv->LoadAllMap();
		bool isExist = false;
		for (int i = 0; i < gv->mapFiles.GetCount(); i++)
		{
			if (gv->mapFiles.GetAt(i) == m_mapName + L".map")
			{
				isExist = true;
				break;
			}
		}
		if (isExist)
		{
			int mesBoxRef = MessageBox(L"该文件已存在，是否覆盖？", L"询问", MB_ICONQUESTION | MB_YESNO);
			if (mesBoxRef == IDNO)
			{
				return;
			}
		}
	

	}

	int mapWidth = _ttoi(m_mapWidth);
	int mapHeigth = _ttoi(m_mapHeigth);

	//检查地图参数配置
	if (mapWidth<600 || mapWidth>10000)
	{
		AfxMessageBox(L"地图宽度不合法，地图宽度取值：[600,10000]");
		return;
	}	
	if (mapHeigth<600 || mapHeigth>10000)
	{
		AfxMessageBox(L"地图高度不合法，地图高度取值：[600,10000]");
		return;
	}

	//如果新建成功就将新地图的信息传到GV里
	gv->gameMap.SetMapHeigth(mapHeigth);
	gv->gameMap.SetMapWidth(mapWidth);
	gv->gameMap.SetMapName(m_mapName);

	//通过发送消息通知主窗口新建地图
	SendMessageA(GetParent()->GetSafeHwnd(), MY_NEWMAP, 0, 0);
	this->DestroyWindow();
}


void DlgNewMap::OnBnClickedButtonCancelNewMap()
{
	this->DestroyWindow();
}


int DlgNewMap::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	gv = GV::GetInstance();

	m_mapName = L"tttt";
	m_mapHeigth = L"2000";
	m_mapWidth = L"2000";


	return 0;
}
