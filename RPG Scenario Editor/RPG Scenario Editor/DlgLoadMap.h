#pragma once
#include "afxcmn.h"


// DlgLoadMap �Ի���

class DlgLoadMap : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLoadMap)

public:
	DlgLoadMap(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgLoadMap();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOAD_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	CListCtrl m_list;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();

	//ListCtrlѡ����Ŀ���ı�
	void OnListCtrlItemChange(int index);
	int nowListCtrlChoose;//��ǰListCtrlѮ���û��ѡ��������-1��
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton2();
private:
	GV* gv;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
