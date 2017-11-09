#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ActionAnalyzer.h"
#include "TriggerAnalyzer.h"

// DlgTriggerEditor �Ի���

class DlgTriggerEditor : public CDialogEx
{
	DECLARE_DYNAMIC(DlgTriggerEditor)

public:
	DlgTriggerEditor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgTriggerEditor();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TRIGGER_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMyChooesChange(WPARAM wParam, LPARAM lParam);
public:
	CListCtrl m_listTriggerList;
	CListCtrl m_listActionList;
	CComboBox m_comboBoxCanUseAction;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	void TriggerInit();

	GV* gv;

	bool hasInit;//�Ƿ��ʼ��

	TriggerAnalyzer triggerAnalyzer;
	ActionAnalyzer actionAnalyzer;
	
	int nowTriggerSelect;
	int nowActionSelect;

	afx_msg void OnBnClickedButton6();
	CButton m_checkBoxTriggerExecute;

	//������ѡ��ı�
	void TriggerSelectChange(int index);

	//����ѡ��ı�
	void ActionSelectChange(int index);

	afx_msg void OnClose();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckTriggerExecute();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButtonEnable();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton19();
};
