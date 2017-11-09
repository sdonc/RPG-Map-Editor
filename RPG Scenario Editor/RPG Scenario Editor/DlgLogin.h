#pragma once
#include "EncodeMD5.h"
#include "afxwin.h"
#include "DlgRegister.h"
// DlgLogin �Ի���

class DlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLogin)

public:
	DlgLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgLogin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	EncodeMD5 md5;
public:
	afx_msg void OnBnClickedButton2();
	GV *gv;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//������֤��
	void UpDateVerificationCode();

	CString m_userID;//�û���
	CString m_password;//����
	CString m_verificationCodeInput;//��֤��
	CButton m_verificationCode;
	afx_msg void OnBnClickedButton3();

	int verificationCode;

	DlgRegister dlgRegister;//ע�ᴰ��
	afx_msg void OnEnSetfocusEdit3();
	afx_msg void OnEnSetfocusEdit2();

	afx_msg void OnClose();
	virtual void OnOK();
};
