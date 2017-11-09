#pragma once


// DlgNewMap �Ի���

class DlgNewMap : public CDialogEx
{
	DECLARE_DYNAMIC(DlgNewMap)

public:
	DlgNewMap(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgNewMap();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEW_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_mapName;
	CString m_mapWidth;
	CString m_mapHeigth;

	afx_msg void OnBnClickedButtonNewMap();
	afx_msg void OnBnClickedButtonCancelNewMap();
	GV* gv;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
