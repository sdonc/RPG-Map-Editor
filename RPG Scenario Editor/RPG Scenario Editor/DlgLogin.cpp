// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// DlgLogin �Ի���

IMPLEMENT_DYNAMIC(DlgLogin, CDialogEx)

DlgLogin::DlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_userID(_T(""))
	, m_password(_T(""))
	, m_verificationCodeInput(_T(""))
{
	
	
}

DlgLogin::~DlgLogin()
{
}

void DlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userID);
	DDX_Text(pDX, IDC_EDIT3, m_password);
	DDX_Text(pDX, IDC_EDIT2, m_verificationCodeInput);
	DDX_Control(pDX, IDC_BUTTON1, m_verificationCode);
}


BEGIN_MESSAGE_MAP(DlgLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgLogin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgLogin::OnBnClickedButton2)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON3, &DlgLogin::OnBnClickedButton3)
	ON_EN_SETFOCUS(IDC_EDIT3, &DlgLogin::OnEnSetfocusEdit3)
	ON_EN_SETFOCUS(IDC_EDIT2, &DlgLogin::OnEnSetfocusEdit2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// DlgLogin ��Ϣ�������


void DlgLogin::OnBnClickedButton1()
{
	UpDateVerificationCode();
	
}


void DlgLogin::OnBnClickedButton2()
{
	

	UpdateData(TRUE);

	//��������Ƿ�Ϸ�
	if (m_userID.GetLength()<6 || m_userID.GetLength()>128)
	{
		gv->isLogin = false;
		AfxMessageBox(L"��¼ʧ�ܣ��û������������û������ȱ����Ǵ���6λ��С��128Ϊ��");
		return;
	}

	//��������Ƿ�Ϸ�
	if (m_password.GetLength()<6 || m_password.GetLength()>128)
	{
		gv->isLogin = false;
		AfxMessageBox(L"��¼ʧ�ܣ����볤���������볤�ȱ����Ǵ���6λ��С��128λ��");
		return;
	}

	//�����֤���Ƿ���ȷ
	if (_ttoi(m_verificationCodeInput)!=verificationCode)
	{
		gv->isLogin = false;
		AfxMessageBox(L"��¼ʧ�ܣ���֤��������������롣");
		return;
	}

	if (gv->user.Login(m_userID, m_password)==false)
	{
		gv->isLogin = false;
		AfxMessageBox(L"��¼ʧ�ܣ�����ԭ��\r\n\t1���û������������\r\n\t2���û�������");
		return;
	}
	AfxMessageBox(L"��¼�ɹ���");
	gv->isLogin = true;
	this->DestroyWindow();
}


int DlgLogin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	verificationCode = -1;
	gv = GV::GetInstance();

	return 0;
}

void DlgLogin::UpDateVerificationCode()
{
	//��ȡ[1000,9999]�������
	int vCode = (rand() % (9999 - 1000 + 1)) + 1000;
	verificationCode = vCode;
	CString str;
	str.Format(L"%d", vCode);
	SetDlgItemText(IDC_BUTTON1, str);
	verificationCode = vCode;
}


void DlgLogin::OnBnClickedButton3()
{
	int iWidth = GetSystemMetrics(SM_CXSCREEN);//��Ļ���
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//��Ļ�߶�
	CRect rect;

	//����δ����
	if (dlgRegister.GetSafeHwnd() == 0)
		dlgRegister.Create(IDD_DIALOG_REGISTER);


	dlgRegister.GetWindowRect(rect);

	//������ʾ
	dlgRegister.MoveWindow(
		(iWidth - rect.Width()) / 2,
		(iHeight - rect.Height()) / 2,
		rect.Width(),
		rect.Height()
	);

	dlgRegister.ShowWindow(SW_SHOW);
	//dlgRegister.DoModal();
}


void DlgLogin::OnEnSetfocusEdit3()
{
	//���û���һ���л������������ʱ���Զ���ȡ��֤��
	static bool isFirst = true;
	if (isFirst)
	{
		UpDateVerificationCode();
		isFirst = false;
	}

}


void DlgLogin::OnEnSetfocusEdit2()
{
	if (verificationCode == -1)
	{
		UpDateVerificationCode();
	}
}


void DlgLogin::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	//���ûس����ر�
	CDialogEx::OnCancel();
}

//���û����»س���ִ��
void DlgLogin::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	OnBnClickedButton2();
	//CDialogEx::OnOK();
}
