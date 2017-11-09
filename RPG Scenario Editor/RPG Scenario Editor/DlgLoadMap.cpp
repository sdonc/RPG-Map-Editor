// DlgLoadMap.cpp : 实现文件
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgLoadMap.h"
#include "afxdialogex.h"


// DlgLoadMap 对话框

IMPLEMENT_DYNAMIC(DlgLoadMap, CDialogEx)

DlgLoadMap::DlgLoadMap(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOAD_MAP, pParent)
{

}

DlgLoadMap::~DlgLoadMap()
{
}

void DlgLoadMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(DlgLoadMap, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgLoadMap::OnBnClickedButton3)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &DlgLoadMap::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &DlgLoadMap::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON9, &DlgLoadMap::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgLoadMap::OnBnClickedButton2)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DlgLoadMap 消息处理程序


void DlgLoadMap::OnBnClickedButton3()
{
	EasyFile ef;
	EasyPath ep;
	CStringArray files;
	ef.EnumFile(ep.GetProgramDir() + L"maps", files,L"map");
	
	CString temp;

	m_list.DeleteAllItems();
	for (int i = 0; i < files.GetCount(); i++)
	{
		m_list.InsertItem(i, NULL);
		temp.Format(L"%d", i + 1);
		m_list.SetItemText(i, 0, temp);
		m_list.SetItemText(i, 1, files.GetAt(i));
	}

	//自动调整列宽
	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_list);
}


int DlgLoadMap::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	//初始化共享函数
	gv = GV::GetInstance();

	SetTimer(1, 200, NULL);

	return 0;
}

//在资源管理器中打开
void DlgLoadMap::OnBnClickedButton1()
{
	if (nowListCtrlChoose == -1 || m_list.GetItemCount() == 0)
	{
		return;
	}
	EasyFile ef;
	EasyPath ep;
	ef.Select(ep.GetProgramDir() + L"maps\\" + m_list.GetItemText(nowListCtrlChoose, 1));

}


void DlgLoadMap::OnListCtrlItemChange(int index)
{
	if (index==-1 || m_list.GetItemCount() == 0)
	{
		return;
	}
	nowListCtrlChoose = index;
	EasyPath ep;
	CFile file;
	CFileStatus status;
	file.Open(ep.GetProgramDir()+ L"maps\\" + m_list.GetItemText(nowListCtrlChoose, 1),CFile::modeRead);
	file.GetStatus(status);
	file.Close();

	/*
	printf("创建时间：%s\r\n", status.m_ctime.Format("%Y-%m-%d%H:%M:%S"));
	printf("修改时间：%s\r\n", status.m_mtime.Format("%Y-%m-%d%H:%M-%S"));
	*/

	CString temp;
	temp = status.m_ctime.Format(L"%Y年%m月%d日 %H:%M:%S");
	SetDlgItemText(IDC_STATIC_CREAT_TIME, temp);
	temp = status.m_mtime.Format(L"%Y年%m月%d日 %H:%M:%S");
	SetDlgItemText(IDC_STATIC_CHANGE_TIME, temp);

	EasyFile ef;
	temp = ef.ReadCString(ep.GetProgramDir() + L"maps\\" + m_list.GetItemText(nowListCtrlChoose, 1));

	EasyText et;
	SetDlgItemText(IDC_STATIC_MAP_WIDTH, et.Middle(temp, L"<Width>", L"</Width>"));
	SetDlgItemText(IDC_STATIC_MAP_HEIGTH, et.Middle(temp,L"<Heigth>",L"</Heigth>"));

}


void DlgLoadMap::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	OnListCtrlItemChange(pLVCD->iItem);

	*pResult = 0;
}

//取消打开地图
void DlgLoadMap::OnBnClickedButton9()
{
	PostMessage(WM_CLOSE);
}

//打开地图
void DlgLoadMap::OnBnClickedButton2()
{
	if (nowListCtrlChoose == -1)
	{
		AfxMessageBox(L"请先选择一个地图文件。");
		return;
	}
	EasyPath ep;
	gv->gameMap.SetPath(ep.GetProgramDir() + L"maps\\" + m_list.GetItemText(nowListCtrlChoose,1));
	GetParent()->SendMessage(MY_LOADMAP, 0, 0);
	PostMessage(WM_CLOSE);

	//模态与非模态创建与销毁
	//http://blog.csdn.net/liuyi1207164339/article/details/46682063

	/*
	备忘
	1、先去gameMap里面设置路径
	3、发送消息给主窗口
	2、然后调用gameMap的读取地图
	4、本窗口销毁

	5、主窗口ListCtrl刷新
	6、主窗口重绘

	主窗口略过选中的绘图
	1、在PaintMap函数里增加现行鼠标略过的判断
	
	主窗口点击拖拽的功能
	1、点击的时候获取选中对象的index
	2、然后在start里面计算出各种索引
	3、仿照添加元素的绘图方法来绘制
	*/
}


void DlgLoadMap::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//初始化ListCtrl
	m_list.InsertColumn(0, L"#");
	m_list.InsertColumn(1, L"地图名");
	nowListCtrlChoose = -1;

	//设置风格
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格

	//枚举地图目录
	OnBnClickedButton3();

	//清楚时钟
	KillTimer(nIDEvent);

	CDialogEx::OnTimer(nIDEvent);
}
