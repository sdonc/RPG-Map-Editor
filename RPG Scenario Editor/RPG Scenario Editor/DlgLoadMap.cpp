// DlgLoadMap.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgLoadMap.h"
#include "afxdialogex.h"


// DlgLoadMap �Ի���

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


// DlgLoadMap ��Ϣ�������


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

	//�Զ������п�
	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_list);
}


int DlgLoadMap::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	//��ʼ��������
	gv = GV::GetInstance();

	SetTimer(1, 200, NULL);

	return 0;
}

//����Դ�������д�
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
	printf("����ʱ�䣺%s\r\n", status.m_ctime.Format("%Y-%m-%d%H:%M:%S"));
	printf("�޸�ʱ�䣺%s\r\n", status.m_mtime.Format("%Y-%m-%d%H:%M-%S"));
	*/

	CString temp;
	temp = status.m_ctime.Format(L"%Y��%m��%d�� %H:%M:%S");
	SetDlgItemText(IDC_STATIC_CREAT_TIME, temp);
	temp = status.m_mtime.Format(L"%Y��%m��%d�� %H:%M:%S");
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

//ȡ���򿪵�ͼ
void DlgLoadMap::OnBnClickedButton9()
{
	PostMessage(WM_CLOSE);
}

//�򿪵�ͼ
void DlgLoadMap::OnBnClickedButton2()
{
	if (nowListCtrlChoose == -1)
	{
		AfxMessageBox(L"����ѡ��һ����ͼ�ļ���");
		return;
	}
	EasyPath ep;
	gv->gameMap.SetPath(ep.GetProgramDir() + L"maps\\" + m_list.GetItemText(nowListCtrlChoose,1));
	GetParent()->SendMessage(MY_LOADMAP, 0, 0);
	PostMessage(WM_CLOSE);

	//ģ̬���ģ̬����������
	//http://blog.csdn.net/liuyi1207164339/article/details/46682063

	/*
	����
	1����ȥgameMap��������·��
	3��������Ϣ��������
	2��Ȼ�����gameMap�Ķ�ȡ��ͼ
	4������������

	5��������ListCtrlˢ��
	6���������ػ�

	�������Թ�ѡ�еĻ�ͼ
	1����PaintMap������������������Թ����ж�
	
	�����ڵ����ק�Ĺ���
	1�������ʱ���ȡѡ�ж����index
	2��Ȼ����start����������������
	3���������Ԫ�صĻ�ͼ����������
	*/
}


void DlgLoadMap::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//��ʼ��ListCtrl
	m_list.InsertColumn(0, L"#");
	m_list.InsertColumn(1, L"��ͼ��");
	nowListCtrlChoose = -1;

	//���÷��
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_list.SetExtendedStyle(dwStyle); //������չ���

	//ö�ٵ�ͼĿ¼
	OnBnClickedButton3();

	//���ʱ��
	KillTimer(nIDEvent);

	CDialogEx::OnTimer(nIDEvent);
}
