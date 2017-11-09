// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// DlgLogin 对话框

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


// DlgLogin 消息处理程序


void DlgLogin::OnBnClickedButton1()
{
	UpDateVerificationCode();
	
}


void DlgLogin::OnBnClickedButton2()
{
	

	UpdateData(TRUE);

	//检查输入是否合法
	if (m_userID.GetLength()<6 || m_userID.GetLength()>128)
	{
		gv->isLogin = false;
		AfxMessageBox(L"登录失败：用户名长度有误。用户名长度必须是大于6位且小于128为。");
		return;
	}

	//检查输入是否合法
	if (m_password.GetLength()<6 || m_password.GetLength()>128)
	{
		gv->isLogin = false;
		AfxMessageBox(L"登录失败：密码长度有误。密码长度必须是大于6位且小于128位。");
		return;
	}

	//检查验证码是否正确
	if (_ttoi(m_verificationCodeInput)!=verificationCode)
	{
		gv->isLogin = false;
		AfxMessageBox(L"登录失败：验证码错误，请重新输入。");
		return;
	}

	if (gv->user.Login(m_userID, m_password)==false)
	{
		gv->isLogin = false;
		AfxMessageBox(L"登录失败：可能原因\r\n\t1、用户名或密码错误；\r\n\t2、用户不存在");
		return;
	}
	AfxMessageBox(L"登录成功！");
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
	//获取[1000,9999]的随机数
	int vCode = (rand() % (9999 - 1000 + 1)) + 1000;
	verificationCode = vCode;
	CString str;
	str.Format(L"%d", vCode);
	SetDlgItemText(IDC_BUTTON1, str);
	verificationCode = vCode;
}


void DlgLogin::OnBnClickedButton3()
{
	int iWidth = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
	CRect rect;

	//窗口未创建
	if (dlgRegister.GetSafeHwnd() == 0)
		dlgRegister.Create(IDD_DIALOG_REGISTER);


	dlgRegister.GetWindowRect(rect);

	//居中显示
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
	//当用户第一次切换到密码输入的时候自动获取验证码
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	//禁用回车键关闭
	CDialogEx::OnCancel();
}

//当用户按下回车键执行
void DlgLogin::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBnClickedButton2();
	//CDialogEx::OnOK();
}
