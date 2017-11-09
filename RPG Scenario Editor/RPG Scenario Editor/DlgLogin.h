#pragma once
#include "EncodeMD5.h"
#include "afxwin.h"
#include "DlgRegister.h"
// DlgLogin 对话框

class DlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLogin)

public:
	DlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	EncodeMD5 md5;
public:
	afx_msg void OnBnClickedButton2();
	GV *gv;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//更新验证码
	void UpDateVerificationCode();

	CString m_userID;//用户名
	CString m_password;//密码
	CString m_verificationCodeInput;//验证码
	CButton m_verificationCode;
	afx_msg void OnBnClickedButton3();

	int verificationCode;

	DlgRegister dlgRegister;//注册窗口
	afx_msg void OnEnSetfocusEdit3();
	afx_msg void OnEnSetfocusEdit2();

	afx_msg void OnClose();
	virtual void OnOK();
};
