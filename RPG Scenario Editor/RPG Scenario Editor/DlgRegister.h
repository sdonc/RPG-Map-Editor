#pragma once


// DlgRegister 对话框

class DlgRegister : public CDialogEx
{
	DECLARE_DYNAMIC(DlgRegister)

public:
	DlgRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgRegister();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CString m_userID;
	CString m_password;
	CString m_password1;
	CString m_verificationCode;

	void UpDateVerificationCode();

	//		afx_msg void OnBnClickedButtonVcode();
	afx_msg void OnBnClickedButtonVcode();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	GV* gv;
	afx_msg void OnEnSetfocusEdit4();
	afx_msg void OnEnSetfocusEdit2();
	int verificationCode;
	virtual void OnOK();
	virtual void OnCancel();
};
