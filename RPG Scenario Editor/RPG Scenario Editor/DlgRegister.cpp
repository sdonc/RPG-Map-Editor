// DlgRegister.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgRegister.h"
#include "afxdialogex.h"


// DlgRegister �Ի���

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


// DlgRegister ��Ϣ�������





void DlgRegister::OnBnClickedButton3()
{
	this->DestroyWindow();
}


void DlgRegister::OnBnClickedButton2()
{
	UpdateData(TRUE);

	//��������Ƿ�Ϸ�
	if (m_userID.GetLength()<6 || m_userID.GetLength()>128)
	{
		AfxMessageBox(L"�û��������û������ȱ����Ǵ��ڵ���6λ��С�ڵ���128λ��");
		return;
	}

	//��������Ƿ�Ϸ�
	if (m_password.GetLength()<6 || m_password.GetLength()>128)
	{
		AfxMessageBox(L"����������볤�ȱ����Ǵ��ڵ���6λ��С�ڵ���128λ��");
		return;
	}

	if (m_password!= m_password1)
	{
		AfxMessageBox(L"������������벻һ�������顣");
		return;
	}

	//�����֤���Ƿ���ȷ
	if (_ttoi(m_verificationCode) != verificationCode)
	{
		AfxMessageBox(L"��֤��������������롣");
		return;
	}


	//ע��
	if (gv->user.Register(m_userID, m_password) == false)
	{
		AfxMessageBox(L"ע��ʧ�ܣ��˺��Ѵ��ڡ�");
		return;
	}
	AfxMessageBox(L"ע��ɹ���");
	this->DestroyWindow();
}


void DlgRegister::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//void DlgRegister::OnBnClickedButtonVcode()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void DlgRegister::UpDateVerificationCode()
{

	//��ȡ[1000,9999]�������
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
	//���û���һ���л������������ʱ���Զ���ȡ��֤��
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int userChoose = MessageBox(L"��Ҫȡ��ע���˺���", L"ѯ��", MB_ICONQUESTION | MB_YESNO);
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
	// TODO: �ڴ����ר�ô����/����û���
	OnBnClickedButton2();
	//CDialogEx::OnOK();
}


void DlgRegister::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	int userChoose = MessageBox(L"��Ҫȡ��ע���˺���", L"ѯ��", MB_ICONQUESTION | MB_YESNO);
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
