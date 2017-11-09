// DlgTriggerEditor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgTriggerEditor.h"
#include "afxdialogex.h"


// DlgTriggerEditor �Ի���

IMPLEMENT_DYNAMIC(DlgTriggerEditor, CDialogEx)

DlgTriggerEditor::DlgTriggerEditor(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TRIGGER_EDIT, pParent)
{

}

DlgTriggerEditor::~DlgTriggerEditor()
{
}

void DlgTriggerEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listTriggerList);
	DDX_Control(pDX, IDC_LIST5, m_listActionList);
	DDX_Control(pDX, IDC_COMBO1, m_comboBoxCanUseAction);
	DDX_Control(pDX, IDC_CHECK_TRIGGER_EXECUTE, m_checkBoxTriggerExecute);
}


BEGIN_MESSAGE_MAP(DlgTriggerEditor, CDialogEx)
	ON_MESSAGE(MY_CHOOES_CHANGE, &DlgTriggerEditor::OnMyChooesChange)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON6, &DlgTriggerEditor::OnBnClickedButton6)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &DlgTriggerEditor::OnNMClickList1)
	ON_BN_CLICKED(IDC_CHECK_TRIGGER_EXECUTE, &DlgTriggerEditor::OnBnClickedCheckTriggerExecute)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgTriggerEditor::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, &DlgTriggerEditor::OnNMClickList5)
	ON_BN_CLICKED(IDC_BUTTON8, &DlgTriggerEditor::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_ENABLE, &DlgTriggerEditor::OnBnClickedButtonEnable)
	ON_BN_CLICKED(IDC_BUTTON16, &DlgTriggerEditor::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON21, &DlgTriggerEditor::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON10, &DlgTriggerEditor::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON18, &DlgTriggerEditor::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON20, &DlgTriggerEditor::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON17, &DlgTriggerEditor::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON7, &DlgTriggerEditor::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON19, &DlgTriggerEditor::OnBnClickedButton19)
END_MESSAGE_MAP()


// DlgTriggerEditor ��Ϣ�������

//��������ѡ��Ԫ�ظı�
afx_msg LRESULT DlgTriggerEditor::OnMyChooesChange(WPARAM wParam, LPARAM lParam)
{
	//�ж��Ƿ��ʼ��
	if (hasInit == false)
	{
		KillTimer(0);
		TriggerInit();
	}

	//�������
	SetDlgItemText(IDC_STATIC_TRIGGER_NAME, L"---");		//��������
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, L"---");		//������
	SetDlgItemText(IDC_STATIC_ACTION_NAME, L"---");			//������
	SetDlgItemText(IDC_STATIC_ACTIONO_PARAM_COUNT, L"---");	//��������
	SetDlgItemText(IDC_EDIT_ACTION_PARAMS, L"");			//�����ű�
	m_checkBoxTriggerExecute.SetCheck(BST_UNCHECKED);		//���ø�ѡ�򣨴��������ã�Ϊȡ��ѡ��

	//��ǰû��ѡ��Ԫ��
	if (gv->nowIsChooesElement==false)
	{
		return 0;
	}


	//��ʾ��ǰ�༭��Ԫ��
	SetDlgItemText(IDC_STATIC_NOW_EDIT_ELEMENT, gv->nowChooesElementInfo);

	//���ش������ű�
	triggerAnalyzer.LoadScript(gv->nowChooesElementTriggerScript);

	//�Զ��������д����������������������ù��ܿ��Ժ����Ż���
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		if (triggerAnalyzer.IsTriggerExist(gv->triggerLoader.triggerInfos[i].name) == false)
		{
			triggerAnalyzer.AddTrigger(gv->triggerLoader.triggerInfos[i].name);
			triggerAnalyzer.SetTriggerExecute(gv->triggerLoader.triggerInfos[i].name, false);
		}
	}

	TriggerScript tempTrigger;

	//�ô������б��������Ϣ���Ƿ�ִ�У�
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		if (triggerAnalyzer.IsTriggerExist(gv->triggerLoader.triggerInfos[i].name))
		{
			triggerAnalyzer.GetTriggerInfo(gv->triggerLoader.triggerInfos[i].name, tempTrigger);
			m_listTriggerList.SetItemText(i, 2, tempTrigger.execute ? L"true" : L"false");
		}
		else
		{
			m_listTriggerList.SetItemText(i, 2, L"false");
		}
	}

	//�ô�����Ĭ��ѡ��
	EasyListCtrl elc;
	if (triggerAnalyzer.GetTriggerCount() > 0)
	{
		elc.SelectRow(m_listTriggerList, 0);
		nowTriggerSelect = 0;
		TriggerSelectChange(0);
	}
	return 0;
}

//���ڴ���
int DlgTriggerEditor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(0, 100, NULL);
	return 0;
}

//��ʱ��
void DlgTriggerEditor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(0);
	TriggerInit();
	CDialogEx::OnTimer(nIDEvent);
}

//��ʼ��
void DlgTriggerEditor::TriggerInit()
{
	gv = GV::GetInstance();

	EasyListCtrl elc;

#pragma region ���ô���ListCtrl��ʼ��
	m_listTriggerList.InsertColumn(0, L"#");
	m_listTriggerList.InsertColumn(1, L"����");
	m_listTriggerList.InsertColumn(2, L"����");

	//���÷��
	DWORD dwStyle = m_listTriggerList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listTriggerList.SetExtendedStyle(dwStyle); //������չ���

	CString temp;
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		m_listTriggerList.InsertItem(i, NULL);

		temp.Format(L"%d", i + 1);
		m_listTriggerList.SetItemText(i, 0, temp);//���
		m_listTriggerList.SetItemText(i, 1, gv->triggerLoader.triggerInfos[i].name);//��������
		m_listTriggerList.SetItemText(i, 2, L"");//�Ƿ�����
	}

	//�����п�
	elc.AdjustColumnWidth(m_listTriggerList);

	//��Ĭ��ѡ��
	nowTriggerSelect = -1;
#pragma endregion


#pragma region �����б�ListCtrl��ʼ��
	m_listActionList.InsertColumn(0, L"#");
	m_listActionList.InsertColumn(1, L"����");
	m_listActionList.InsertColumn(2, L"����");

	dwStyle = m_listActionList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listActionList.SetExtendedStyle(dwStyle); //������չ���

	//�����п�
	elc.AdjustColumnWidth(m_listActionList);

	//��Ĭ��ѡ��
	nowActionSelect = -1;
#pragma endregion


	//���ö���ComboBox��ʼ��
	for (int i = 0; i < gv->triggerLoader.actionInfos.GetCount(); i++)
	{
		m_comboBoxCanUseAction.InsertString(i, gv->triggerLoader.actionInfos[i].name);
	}


	//���ø�ѡ�򣨴��������ã�Ϊȡ��ѡ��
	m_checkBoxTriggerExecute.SetCheck(BST_UNCHECKED);

	hasInit = true;
}

//�رհ�ť
void DlgTriggerEditor::OnBnClickedButton6()
{
	this->DestroyWindow();//�رմ���
}

//������ListCtelѡ��ı�
void DlgTriggerEditor::TriggerSelectChange(int index)
{
	if (index == -1)
	{
		SetDlgItemText(IDC_EDIT_TRIGGER_TIP, L"");
		SetDlgItemText(IDC_STATIC_ACTION_COUNT, L"---");
		SetDlgItemText(IDC_STATIC_TRIGGER_NAME, L"---");
		m_checkBoxTriggerExecute.SetCheck(BST_UNCHECKED);
		return;
	}

#pragma region ��ʾ��������Ϣ���

	TriggerScript tempTrigger;
	m_listActionList.DeleteAllItems();					//��������б�
	bool haveAction;

	//���ض���
	haveAction = triggerAnalyzer.GetTriggerInfo(m_listTriggerList.GetItemText(index, 1), tempTrigger);

	//��ʾ�ô������İ�����Ϣ
	SetDlgItemText(IDC_EDIT_TRIGGER_TIP, gv->triggerLoader.triggerInfos[index].tip);

	//��ʾ��ǰ��������
	SetDlgItemText(IDC_STATIC_TRIGGER_NAME, m_listTriggerList.GetItemText(index, 1));

	//��ʾ��ǰ�������Ƿ�ִ��
	if (m_listTriggerList.GetItemText(index, 2) == L"true")
		m_checkBoxTriggerExecute.SetCheck(BST_CHECKED);
	else
		m_checkBoxTriggerExecute.SetCheck(BST_UNCHECKED);

#pragma endregion


#pragma region ��ʾ������Ϣ���

	//�ж��Ƿ��ж���
	if (haveAction == false)
	{
		//��ʾ�ô������Ķ�����
		SetDlgItemText(IDC_STATIC_ACTION_COUNT, L"0");
		return;
	}
	//���ض�������
	actionAnalyzer.LoadActions(tempTrigger.actions, tempTrigger.actionCount);

	CString temp;
	CArray<Action> tempActions;
	actionAnalyzer.GetActionInfos(tempTrigger.name, tempActions);

	//���붯���б�
	for (int i = 0; i < tempActions.GetCount(); i++)
	{
		temp.Format(L"%d", i + 1);
		m_listActionList.InsertItem(i, NULL);
		m_listActionList.SetItemText(i, 0, temp);//���
		m_listActionList.SetItemText(i, 1, tempActions[i].name);//����
		m_listActionList.SetItemText(i, 2, tempActions[i].execute ? L"true" : L"false");//�Ƿ�����
	}

	//��ʾ��ǰ�������Ķ�����
	temp.Format(L"%d", tempTrigger.actionCount);
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, temp);

#pragma endregion

	//ѡ���һ����������ʾ
	if (tempActions.GetCount()>0)
	{
		ActionSelectChange(0);
	}
}

//����ListCtrlѡ��ı�
void DlgTriggerEditor::ActionSelectChange(int index)
{
	if (index == -1)
	{
		//��ʾ������
		SetDlgItemText(IDC_STATIC_ACTION_NAME, L"---");

		//��ʾ��������
		SetDlgItemText(IDC_STATIC_ACTIONO_PARAM_COUNT, L"---");

		//��ʾ��������
		SetDlgItemText(IDC_EDIT_ACTION_PARAMS, L"---");

		return;
	}

	Action action;
	actionAnalyzer.GetActionInfo(index, action);

	//��ʾ������
	SetDlgItemText(IDC_STATIC_ACTION_NAME, action.name);

	//���Ҳ�������
	CString temp = L"---";
	for (int i = 0; i < gv->triggerLoader.actionInfos.GetCount(); i++)
	{
		if (action.name == gv->triggerLoader.actionInfos[i].name)
		{
			temp.Format(L"%d", gv->triggerLoader.actionInfos[i].paramCount);
			break;
		}
	}
	if (temp == L"---")
	{
		AfxMessageBox(L"���Ҷ���������Ϣ����");
	}
	//��ʾ��������
	SetDlgItemText(IDC_STATIC_ACTIONO_PARAM_COUNT, temp);

	//��ʾ��������
	SetDlgItemText(IDC_EDIT_ACTION_PARAMS, action.params);

	//����/���� ��ť���ñ���
	if (action.execute)
	{
		SetDlgItemText(IDC_BUTTON_ENABLE, L"����");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON_ENABLE, L"����");
	}

}

//���򼴽����ر�
void DlgTriggerEditor::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	gv->isTriggerEditorShow = false;
	CDialogEx::OnClose();
}

//��ߴ������б����
void DlgTriggerEditor::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	nowTriggerSelect = pLVCD->iItem;

	TriggerSelectChange(nowTriggerSelect);



	*pResult = 0;
}

//������ִ��������޸�
void DlgTriggerEditor::OnBnClickedCheckTriggerExecute()
{
	if (nowTriggerSelect == -1)
	{
		return;
	}

	//��ȡListCtrlѡ�еĴ�����������
	CString temp = m_listTriggerList.GetItemText(nowTriggerSelect, 1);

	//�жϴ������Ƿ���ڣ������������һ��������
	if (triggerAnalyzer.IsTriggerExist(temp) == false)
	{
		triggerAnalyzer.AddTrigger(temp);
	}

	//���ô������Ƿ�ִ��
	if (m_checkBoxTriggerExecute.GetCheck() == BST_CHECKED)
	{
		m_listTriggerList.SetItemText(nowTriggerSelect, 2, L"true");
		triggerAnalyzer.SetTriggerExecute(temp, true);
	}
	else
	{
		m_listTriggerList.SetItemText(nowTriggerSelect, 2, L"false");
		triggerAnalyzer.SetTriggerExecute(temp, false);
	}
}

//���������
void DlgTriggerEditor::OnBnClickedButton3()
{
	if (nowTriggerSelect == -1)
	{
		return;
	}
	//��ȡListCtrlѡ�еĴ�����������
	CString temp = m_listTriggerList.GetItemText(nowTriggerSelect, 1);

	//ɾ��������
	triggerAnalyzer.DeleteTrigger(temp);

	//ListCtel���ô���������Ϊfalse
	m_listTriggerList.SetItemText(nowTriggerSelect, 2, L"false");

	//ˢ����ʾ��������Ϣ
	TriggerSelectChange(nowTriggerSelect);
}

//�����б�ListCtrl�������¼�
void DlgTriggerEditor::OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	nowActionSelect = pLVCD->iItem;

	ActionSelectChange(nowActionSelect);

	*pResult = 0;
}

//���붯����ť����¼�
void DlgTriggerEditor::OnBnClickedButton8()
{
	//��ȡѡ��Ķ�����
	int nIndex = m_comboBoxCanUseAction.GetCurSel();
	CString selectText;
	m_comboBoxCanUseAction.GetLBText(nIndex, selectText);

	if (selectText == L"")
	{
		return;
	}

	//���Ҹö�������Ϣ
	bool exist;
	ActionInfo actioninfo;
	for (int i = 0; i < gv->triggerLoader.actionInfos.GetCount(); i++)
	{
		if (gv->triggerLoader.actionInfos[i].name == selectText)
		{
			exist = true;
			actioninfo.name = gv->triggerLoader.actionInfos[i].name;
			actioninfo.paramCount = gv->triggerLoader.actionInfos[i].paramCount;
			actioninfo.params = gv->triggerLoader.actionInfos[i].params;
			actioninfo.tip = gv->triggerLoader.actionInfos[i].tip;
			break;
		}
	}
	if (exist == false)
	{
		AfxMessageBox(L"���Ҷ�����Ϣʧ�ܡ�");
		return;
	}

	//�ж����޲�����Ȼ������Ӷ���
	CString temp;
	if (actioninfo.paramCount !=0)
	{
		//���Ҹ÷����Ĳ���
		CArray<ParamInfo> paramInfos;
		if (gv->triggerLoader.GetParamInfo(selectText, paramInfos) == false)
		{
			AfxMessageBox(L"���Ҳ�����Ϣʧ�ܡ�");
			return;
		}

		//����Ĭ�ϲ����б�
		for (int i = 0; i < paramInfos.GetCount(); i++)
		{
			if (i!=0)
			{
				temp = temp + L"\r\n";
			}
			temp = temp + L"<" + paramInfos[i].name + L">" + L"</" + paramInfos[i].name + L">";
		}

		actionAnalyzer.AddAction(selectText, temp);
	}
	else
	{
		actionAnalyzer.AddAction(selectText, L"");
	}
	
	//����ListCtrl
	temp.Format(L"%d", m_listActionList.GetItemCount() + 1);
	m_listActionList.InsertItem(m_listActionList.GetItemCount(), temp);					//���
	m_listActionList.SetItemText(m_listActionList.GetItemCount() - 1, 1, selectText);	//������
	m_listActionList.SetItemText(m_listActionList.GetItemCount() - 1, 2, L"true");		//�Ƿ�ִ��

	//�����п�
	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listActionList);

	//����ѡ����
	nowActionSelect = m_listActionList.GetItemCount() - 1;
	ActionSelectChange(nowActionSelect);

	//���津�����б�
	if (triggerAnalyzer.SetTriggerActions(m_listTriggerList.GetItemText(nowTriggerSelect,1),actionAnalyzer.GetActions(),actionAnalyzer.GetActionsCount())==false)
	{
		AfxMessageBox(L"���涯���ű�ʧ�ܡ�");
	}

	//��ʾ������
	temp.Format(L"%d", triggerAnalyzer.GetTriggerCount());
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, temp);

}

//���õ�ǰѡ�еĴ���
void DlgTriggerEditor::OnBnClickedButtonEnable()
{
	//�ж��������Ƿ�ѡ����Ԫ��
	if (gv->nowIsChooesElement == false)
	{
		AfxMessageBox(L"�����ڵ�ͼ�༭����ѡ��һ��Ԫ�ء�");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˶���
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"δѡ������");
		return;
	}

	//��ȡ������
	CString temp = m_listActionList.GetItemText(nowActionSelect, 1);

	//�ж��Ƿ�ִ��
	if (m_listActionList.GetItemText(nowActionSelect, 2)==L"true")
	{
		//����
		actionAnalyzer.SetActionExecute(temp, false);

		//���ñ���
		SetDlgItemText(IDC_BUTTON_ENABLE, L"����");
		m_listActionList.SetItemText(nowActionSelect, 2, L"false");
	}
	else
	{
		//����
		actionAnalyzer.SetActionExecute(temp, true);

		//���ñ���
		SetDlgItemText(IDC_BUTTON_ENABLE, L"����");
		m_listActionList.SetItemText(nowActionSelect, 2, L"true");
	}
}

//�������ж���
void DlgTriggerEditor::OnBnClickedButton16()
{
	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}


	//�������еĶ���
	CString temp;
	for (int i = 0; i < m_listActionList.GetItemCount(); i++)
	{
		//��ȡ������
		temp = m_listActionList.GetItemText(i, 1);

		//���ö���Ϊ����
		actionAnalyzer.SetActionExecute(temp, false);

		//����ListCtrl����
		m_listActionList.SetItemText(i, 2, L"false");
	}

	//���ð�ť����
	SetDlgItemText(IDC_BUTTON_ENABLE, L"����");
}

//�������ж���
void DlgTriggerEditor::OnBnClickedButton21()
{
	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}


	//�������еĶ���
	CString temp;
	for (int i = 0; i < m_listActionList.GetItemCount(); i++)
	{
		//��ȡ������
		temp = m_listActionList.GetItemText(i, 1);

		//���ö���Ϊ����
		actionAnalyzer.SetActionExecute(temp, true);

		//����ListCtrl����
		m_listActionList.SetItemText(i, 2, L"true");
	}

	//���ð�ť����
	SetDlgItemText(IDC_BUTTON_ENABLE, L"����");

}

//ɾ������
void DlgTriggerEditor::OnBnClickedButton10()
{	
	//�ж��������Ƿ�ѡ����Ԫ��
	if (gv->nowIsChooesElement == false)
	{
		AfxMessageBox(L"�����ڵ�ͼ�༭����ѡ��һ��Ԫ�ء�");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˶���
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"δѡ������");
		return;
	}
	
	//ɾ������
	actionAnalyzer.DeleteAction(nowActionSelect);

	//ɾ������
	m_listActionList.DeleteItem(nowActionSelect);

	//ѡ����һ��
	nowActionSelect--;
	if (nowActionSelect>=0)
	{
		EasyListCtrl elc;
		elc.SelectRow(m_listActionList, nowActionSelect);
	}

	//��ʾ������
	CString temp;
	temp.Format(L"%d", triggerAnalyzer.GetTriggerCount());
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, temp);
}

//���涯���ű�
void DlgTriggerEditor::OnBnClickedButton18()
{
	//�ж��������Ƿ�ѡ����Ԫ��
	if (gv->nowIsChooesElement == false)
	{
		AfxMessageBox(L"�����ڵ�ͼ�༭����ѡ��һ��Ԫ�ء�");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˶���
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"δѡ������");
		return;
	}

	//��ȡ�������ű�
	CString temp;
	GetDlgItemText(IDC_EDIT_ACTION_PARAMS, temp);

	//���ö����ű�
	actionAnalyzer.SetActionParams(nowActionSelect, temp);

	//���津�����б�
	if (triggerAnalyzer.SetTriggerActions(m_listTriggerList.GetItemText(nowTriggerSelect, 1), actionAnalyzer.GetActions(), actionAnalyzer.GetActionsCount()) == false)
	{
		AfxMessageBox(L"���涯���ű�ʧ�ܡ�");
	}
}


void DlgTriggerEditor::OnBnClickedButton20()
{
	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˶���
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"δѡ������");
		return;
	}

	//ѯ���û��Ƿ����ýű�
	if (MessageBox(L"ȷ��Ҫ���ò�����\r\nע�����ò����������Զ����棬�����Ҫ�ָ�����ǰ�����ݣ�\r\n������ѡ����һ��������Ȼ�����л�������", L"ѯ��",
		MB_ICONQUESTION | MB_YESNO)== IDNO)
	{
		return;
	}

	//��ȡ������
	CString actionName = m_listActionList.GetItemText(nowActionSelect,1);
	if (actionName == L"")
	{
		AfxMessageBox(L"��ȡ��������������");
		return;
	}

	//���Ҹö����Ĳ���
	CArray<ParamInfo> paramInfos;
	if (gv->triggerLoader.GetParamInfo(actionName, paramInfos) == false)
	{
		AfxMessageBox(L"���Ҳ�����Ϣʧ�ܡ�");
		return;
	}

	//����Ĭ�ϲ����б�
	CString param;
	for (int i = 0; i < paramInfos.GetCount(); i++)
	{
		if (i != 0)
		{
			param = param + L"\r\n";
		}
		param = param + L"<" + paramInfos[i].name + L">" + L"</" + paramInfos[i].name + L">";
	}

	//��ʾĬ�ϲ���
	SetDlgItemText(IDC_EDIT_ACTION_PARAMS, param);
}

//������ť
void DlgTriggerEditor::OnBnClickedButton17()
{
	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}

	//�жϵ�ǰ�Ƿ�ѡ���˶���
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"δѡ������");
		return;
	}

	//��ȡ������
	CString actionName = m_listActionList.GetItemText(nowActionSelect, 1);
	if (actionName == L"")
	{
		AfxMessageBox(L"��ȡ��������������");
		return;
	}

	//���Ҹö����Ĳ���
	CArray<ParamInfo> paramInfos;
	if (gv->triggerLoader.GetParamInfo(actionName, paramInfos) == false)
	{
		AfxMessageBox(L"���Ҳ�����Ϣʧ�ܡ�");
		return;
	}

	//���ɰ�����Ϣ
	CString helpInfo,temp;

	//������������
	helpInfo = L"��������" + actionName;

	//��������������
	temp.Format(L"%d", paramInfos.GetCount());
	helpInfo = helpInfo + L"\r\n  ������" + temp + L"��";

	//������������ʾ
	for (int i = 0; i < gv->triggerLoader.actionInfos.GetCount(); i++)
	{
		if (gv->triggerLoader.actionInfos[i].name == actionName)
		{
			temp = gv->triggerLoader.actionInfos[i].tip;
			break;
		}
	}
	if (temp!=L"")
	{
		helpInfo = helpInfo + L"\r\n  ��ʾ��" + temp;
	}
	
	//�ж��Ƿ��в���
	CString paramHelp =L"";
	if (paramInfos.GetCount() != 0)
	{
		//���ɲ���������Ϣ
		for (int i = 0; i < paramInfos.GetCount(); i++)
		{
			temp.Format(L"%d", i + 1);
			if (i != 0)
			{
				paramHelp = paramHelp + L"\r\n";
			}
			paramHelp = paramHelp + L"����" + temp + L"��" + paramInfos[i].name + L"��";
			paramHelp = paramHelp + (paramInfos[i].necessary ? L"����" : L"�ɿ�") + L"����";
			paramHelp = paramHelp + paramInfos[i].tip;
		}

		//���������Ϣ
		AfxMessageBox(helpInfo + L"\r\n\r\n" + paramHelp);

		return;
	}

	AfxMessageBox(helpInfo);
}


void DlgTriggerEditor::OnBnClickedButton7()
{
	//�ж��������Ƿ�ѡ����Ԫ��
	if (gv->nowIsChooesElement==false)
	{
		AfxMessageBox(L"�����ڵ�ͼ�༭����ѡ��һ��Ԫ�ء�");
		return;
	}
	gv->nowChooesElementTriggerScript = triggerAnalyzer.GetScript();
	GetParent()->SendMessage(MY_TRIGGER_CHANGE,0,0);
}


void DlgTriggerEditor::OnBnClickedButton19()
{
	//�жϵ�ǰ�Ƿ�ѡ���˴�����
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"����ѡ��һ����������");
		return;
	}



	EasyFile ef;
	EasyPath ep;

	ef.WriteCString(ep.GetProgramDir() + L"temp_trigger.txt", triggerAnalyzer.GetScript(true),true);
	ef.Select(ep.GetProgramDir() + L"temp_trigger.txt");
}
