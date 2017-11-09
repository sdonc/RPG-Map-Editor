// DlgRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgRegister.h"
#include "afxdialogex.h"


// DlgRegister 对话框

IMPLEMENT_DYNAMIC(DlgRegister, CDialogEx)

DlgRegister::DlgRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_REGISTER, pParent)
	, m_userID(_T(""))
	, m_password(_T(""))
	, m_password1(_T(""))
	, m_verificationCode(_T(""))
{

}

DlgRegister::~DlgRegister()
{
}

void DlgRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userID);
	DDX_Text(pDX, IDC_EDIT3, m_password);
	DDX_Text(pDX, IDC_EDIT4, m_password1);
	DDX_Text(pDX, IDC_EDIT2, m_verificationCode);
}


BEGIN_MESSAGE_MAP(DlgRegister, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, &DlgRegister::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgRegister::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgRegister::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON_VCODE, &DlgRegister::OnBnClickedButtonVcode)
ON_BN_CLICKED(IDC_BUTTON_VCODE, &DlgRegister::OnBnClickedButtonVcode)
ON_WM_CREATE()
ON_EN_SETFOCUS(IDC_EDIT4, &DlgRegister::OnEnSetfocusEdit4)
ON_EN_SETFOCUS(IDC_EDIT2, &DlgRegister::OnEnSetfocusEdit2)
END_MESSAGE_MAP()


// DlgRegister 消息处理程序





void DlgRegister::OnBnClickedButton3()
{
	this->DestroyWindow();
}


void DlgRegister::OnBnClickedButton2()
{
	UpdateData(TRUE);

	//检查输入是否合法
	if (m_userID.GetLength()<6 || m_userID.GetLength()>128)
	{
		AfxMessageBox(L"用户名有误：用户名长度必须是大于等于6位且小于等于128位。");
		return;
	}

	//检查输入是否合法
	if (m_password.GetLength()<6 || m_password.GetLength()>128)
	{
		AfxMessageBox(L"密码错误：密码长度必须是大于等于6位且小于等于128位。");
		return;
	}

	if (m_password!= m_password1)
	{
		AfxMessageBox(L"两次输入的密码不一样，请检查。");
		return;
	}

	//检查验证码是否正确
	if (_ttoi(m_verificationCode) != verificationCode)
	{
		AfxMessageBox(L"验证码错误，请重新输入。");
		return;
	}


	//注册
	if (gv->user.Register(m_userID, m_password) == false)
	{
		AfxMessageBox(L"注册失败：账号已存在。");
		return;
	}
	AfxMessageBox(L"注册成功！");
	this->DestroyWindow();
}


void DlgRegister::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


//void DlgRegister::OnBnClickedButtonVcode()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void DlgRegister::UpDateVerificationCode()
{

	//获取[1000,9999]的随机数
	int vCode = (rand() % (9999 - 1000 + 1)) + 1000;
	verificationCode = vCode;
	CString str;
	str.Format(L"%d", vCode);
	SetDlgItemText(IDC_BUTTON_VCODE, str);


}

void DlgRegister::OnBnClickedButtonVcode()
{
	UpDateVerificationCode();
}


int DlgRegister::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	verificationCode = -1;
	gv = GV::GetInstance();

	return 0;
}


void DlgRegister::OnEnSetfocusEdit4()
{
	//当用户第一次切换到密码输入的时候自动获取验证码
	if (verificationCode == -1)
	{
		UpDateVerificationCode();
	}
}


void DlgRegister::OnEnSetfocusEdit2()
{
	if (verificationCode==-1)
	{
		UpDateVerificationCode();
	}
}

void DlgRegister::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int userChoose = MessageBox(L"您要取消注册账号吗？", L"询问", MB_ICONQUESTION | MB_YESNO);
	switch (userChoose)
	{
	case IDYES:
		CDialogEx::OnCancel();
		break;
	case IDNO:
		return;
	}
}
void DlgRegister::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBnClickedButton2();
	//CDialogEx::OnOK();
}


void DlgRegister::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	int userChoose = MessageBox(L"您要取消注册账号吗？", L"询问", MB_ICONQUESTION | MB_YESNO);
	switch (userChoose)
	{
	case IDYES:
		CDialogEx::OnCancel();
		break;
	case IDNO:
		return;
	}

	CDialogEx::OnCancel();
}
