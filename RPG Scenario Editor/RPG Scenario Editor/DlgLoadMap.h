#pragma once
#include "afxcmn.h"


// DlgLoadMap 对话框

class DlgLoadMap : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLoadMap)

public:
	DlgLoadMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgLoadMap();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOAD_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	CListCtrl m_list;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();

	//ListCtrl选中项目被改变
	void OnListCtrlItemChange(int index);
	int nowListCtrlChoose;//当前ListCtrl旬中项（没有选中项则是-1）
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton2();
private:
	GV* gv;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
