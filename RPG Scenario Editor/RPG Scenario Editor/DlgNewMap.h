#pragma once


// DlgNewMap 对话框

class DlgNewMap : public CDialogEx
{
	DECLARE_DYNAMIC(DlgNewMap)

public:
	DlgNewMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgNewMap();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEW_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
