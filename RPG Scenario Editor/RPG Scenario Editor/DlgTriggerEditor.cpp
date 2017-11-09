// DlgTriggerEditor.cpp : 实现文件
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "DlgTriggerEditor.h"
#include "afxdialogex.h"


// DlgTriggerEditor 对话框

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


// DlgTriggerEditor 消息处理程序

//当主窗口选择元素改变
afx_msg LRESULT DlgTriggerEditor::OnMyChooesChange(WPARAM wParam, LPARAM lParam)
{
	//判断是否初始化
	if (hasInit == false)
	{
		KillTimer(0);
		TriggerInit();
	}

	//清除数据
	SetDlgItemText(IDC_STATIC_TRIGGER_NAME, L"---");		//触发器名
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, L"---");		//动作数
	SetDlgItemText(IDC_STATIC_ACTION_NAME, L"---");			//动作名
	SetDlgItemText(IDC_STATIC_ACTIONO_PARAM_COUNT, L"---");	//参数个数
	SetDlgItemText(IDC_EDIT_ACTION_PARAMS, L"");			//动作脚本
	m_checkBoxTriggerExecute.SetCheck(BST_UNCHECKED);		//设置复选框（触发器启用）为取消选中

	//当前没有选中元素
	if (gv->nowIsChooesElement==false)
	{
		return 0;
	}


	//显示当前编辑的元素
	SetDlgItemText(IDC_STATIC_NOW_EDIT_ELEMENT, gv->nowChooesElementInfo);

	//加载触发器脚本
	triggerAnalyzer.LoadScript(gv->nowChooesElementTriggerScript);

	//自动补齐所有触发器（！！！！！！！该功能可以后续优化）
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		if (triggerAnalyzer.IsTriggerExist(gv->triggerLoader.triggerInfos[i].name) == false)
		{
			triggerAnalyzer.AddTrigger(gv->triggerLoader.triggerInfos[i].name);
			triggerAnalyzer.SetTriggerExecute(gv->triggerLoader.triggerInfos[i].name, false);
		}
	}

	TriggerScript tempTrigger;

	//置触发器列表第三列信息（是否执行）
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

	//置触发器默认选中
	EasyListCtrl elc;
	if (triggerAnalyzer.GetTriggerCount() > 0)
	{
		elc.SelectRow(m_listTriggerList, 0);
		nowTriggerSelect = 0;
		TriggerSelectChange(0);
	}
	return 0;
}

//窗口创建
int DlgTriggerEditor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(0, 100, NULL);
	return 0;
}

//计时器
void DlgTriggerEditor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(0);
	TriggerInit();
	CDialogEx::OnTimer(nIDEvent);
}

//初始化
void DlgTriggerEditor::TriggerInit()
{
	gv = GV::GetInstance();

	EasyListCtrl elc;

#pragma region 可用触发ListCtrl初始化
	m_listTriggerList.InsertColumn(0, L"#");
	m_listTriggerList.InsertColumn(1, L"名称");
	m_listTriggerList.InsertColumn(2, L"开启");

	//设置风格
	DWORD dwStyle = m_listTriggerList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listTriggerList.SetExtendedStyle(dwStyle); //设置扩展风格

	CString temp;
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		m_listTriggerList.InsertItem(i, NULL);

		temp.Format(L"%d", i + 1);
		m_listTriggerList.SetItemText(i, 0, temp);//序号
		m_listTriggerList.SetItemText(i, 1, gv->triggerLoader.triggerInfos[i].name);//触发器名
		m_listTriggerList.SetItemText(i, 2, L"");//是否启动
	}

	//调整列宽
	elc.AdjustColumnWidth(m_listTriggerList);

	//置默认选中
	nowTriggerSelect = -1;
#pragma endregion


#pragma region 动作列表ListCtrl初始化
	m_listActionList.InsertColumn(0, L"#");
	m_listActionList.InsertColumn(1, L"名称");
	m_listActionList.InsertColumn(2, L"开启");

	dwStyle = m_listActionList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listActionList.SetExtendedStyle(dwStyle); //设置扩展风格

	//调整列宽
	elc.AdjustColumnWidth(m_listActionList);

	//置默认选中
	nowActionSelect = -1;
#pragma endregion


	//可用动作ComboBox初始化
	for (int i = 0; i < gv->triggerLoader.actionInfos.GetCount(); i++)
	{
		m_comboBoxCanUseAction.InsertString(i, gv->triggerLoader.actionInfos[i].name);
	}


	//设置复选框（触发器启用）为取消选中
	m_checkBoxTriggerExecute.SetCheck(BST_UNCHECKED);

	hasInit = true;
}

//关闭按钮
void DlgTriggerEditor::OnBnClickedButton6()
{
	this->DestroyWindow();//关闭窗口
}

//触发器ListCtel选项被改变
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

#pragma region 显示触发器信息相关

	TriggerScript tempTrigger;
	m_listActionList.DeleteAllItems();					//清除动作列表
	bool haveAction;

	//加载动作
	haveAction = triggerAnalyzer.GetTriggerInfo(m_listTriggerList.GetItemText(index, 1), tempTrigger);

	//显示该触发器的帮助信息
	SetDlgItemText(IDC_EDIT_TRIGGER_TIP, gv->triggerLoader.triggerInfos[index].tip);

	//显示当前触发器名
	SetDlgItemText(IDC_STATIC_TRIGGER_NAME, m_listTriggerList.GetItemText(index, 1));

	//显示当前触发器是否执行
	if (m_listTriggerList.GetItemText(index, 2) == L"true")
		m_checkBoxTriggerExecute.SetCheck(BST_CHECKED);
	else
		m_checkBoxTriggerExecute.SetCheck(BST_UNCHECKED);

#pragma endregion


#pragma region 显示动作信息相关

	//判断是否有动作
	if (haveAction == false)
	{
		//显示该触发器的动作数
		SetDlgItemText(IDC_STATIC_ACTION_COUNT, L"0");
		return;
	}
	//加载动作数据
	actionAnalyzer.LoadActions(tempTrigger.actions, tempTrigger.actionCount);

	CString temp;
	CArray<Action> tempActions;
	actionAnalyzer.GetActionInfos(tempTrigger.name, tempActions);

	//加入动作列表
	for (int i = 0; i < tempActions.GetCount(); i++)
	{
		temp.Format(L"%d", i + 1);
		m_listActionList.InsertItem(i, NULL);
		m_listActionList.SetItemText(i, 0, temp);//序号
		m_listActionList.SetItemText(i, 1, tempActions[i].name);//名称
		m_listActionList.SetItemText(i, 2, tempActions[i].execute ? L"true" : L"false");//是否启动
	}

	//显示当前触发器的动作数
	temp.Format(L"%d", tempTrigger.actionCount);
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, temp);

#pragma endregion

	//选择第一个动作来显示
	if (tempActions.GetCount()>0)
	{
		ActionSelectChange(0);
	}
}

//动作ListCtrl选项被改变
void DlgTriggerEditor::ActionSelectChange(int index)
{
	if (index == -1)
	{
		//显示动作名
		SetDlgItemText(IDC_STATIC_ACTION_NAME, L"---");

		//显示参数个数
		SetDlgItemText(IDC_STATIC_ACTIONO_PARAM_COUNT, L"---");

		//显示参数内容
		SetDlgItemText(IDC_EDIT_ACTION_PARAMS, L"---");

		return;
	}

	Action action;
	actionAnalyzer.GetActionInfo(index, action);

	//显示动作名
	SetDlgItemText(IDC_STATIC_ACTION_NAME, action.name);

	//查找参数个数
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
		AfxMessageBox(L"查找动作参数信息出错。");
	}
	//显示参数个数
	SetDlgItemText(IDC_STATIC_ACTIONO_PARAM_COUNT, temp);

	//显示参数内容
	SetDlgItemText(IDC_EDIT_ACTION_PARAMS, action.params);

	//禁用/启动 按钮设置标题
	if (action.execute)
	{
		SetDlgItemText(IDC_BUTTON_ENABLE, L"禁用");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON_ENABLE, L"开启");
	}

}

//程序即将被关闭
void DlgTriggerEditor::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	gv->isTriggerEditorShow = false;
	CDialogEx::OnClose();
}

//左边触发器列表被点击
void DlgTriggerEditor::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	nowTriggerSelect = pLVCD->iItem;

	TriggerSelectChange(nowTriggerSelect);



	*pResult = 0;
}

//触发器执行情况被修改
void DlgTriggerEditor::OnBnClickedCheckTriggerExecute()
{
	if (nowTriggerSelect == -1)
	{
		return;
	}

	//获取ListCtrl选中的触发器的名称
	CString temp = m_listTriggerList.GetItemText(nowTriggerSelect, 1);

	//判断触发器是否存在，不存在则添加一个触发器
	if (triggerAnalyzer.IsTriggerExist(temp) == false)
	{
		triggerAnalyzer.AddTrigger(temp);
	}

	//设置触发器是否执行
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

//清除触发器
void DlgTriggerEditor::OnBnClickedButton3()
{
	if (nowTriggerSelect == -1)
	{
		return;
	}
	//获取ListCtrl选中的触发器的名称
	CString temp = m_listTriggerList.GetItemText(nowTriggerSelect, 1);

	//删除触发器
	triggerAnalyzer.DeleteTrigger(temp);

	//ListCtel上置触发器启动为false
	m_listTriggerList.SetItemText(nowTriggerSelect, 2, L"false");

	//刷新显示触发器信息
	TriggerSelectChange(nowTriggerSelect);
}

//动作列表ListCtrl被单击事件
void DlgTriggerEditor::OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	nowActionSelect = pLVCD->iItem;

	ActionSelectChange(nowActionSelect);

	*pResult = 0;
}

//加入动作按钮点击事件
void DlgTriggerEditor::OnBnClickedButton8()
{
	//获取选择的动作名
	int nIndex = m_comboBoxCanUseAction.GetCurSel();
	CString selectText;
	m_comboBoxCanUseAction.GetLBText(nIndex, selectText);

	if (selectText == L"")
	{
		return;
	}

	//查找该动作的信息
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
		AfxMessageBox(L"查找动作信息失败。");
		return;
	}

	//判断有无参数，然后再添加动作
	CString temp;
	if (actioninfo.paramCount !=0)
	{
		//查找该方法的参数
		CArray<ParamInfo> paramInfos;
		if (gv->triggerLoader.GetParamInfo(selectText, paramInfos) == false)
		{
			AfxMessageBox(L"查找参数信息失败。");
			return;
		}

		//生成默认参数列表
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
	
	//加入ListCtrl
	temp.Format(L"%d", m_listActionList.GetItemCount() + 1);
	m_listActionList.InsertItem(m_listActionList.GetItemCount(), temp);					//序号
	m_listActionList.SetItemText(m_listActionList.GetItemCount() - 1, 1, selectText);	//动作名
	m_listActionList.SetItemText(m_listActionList.GetItemCount() - 1, 2, L"true");		//是否执行

	//调整列宽
	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listActionList);

	//设置选中项
	nowActionSelect = m_listActionList.GetItemCount() - 1;
	ActionSelectChange(nowActionSelect);

	//保存触发器列表
	if (triggerAnalyzer.SetTriggerActions(m_listTriggerList.GetItemText(nowTriggerSelect,1),actionAnalyzer.GetActions(),actionAnalyzer.GetActionsCount())==false)
	{
		AfxMessageBox(L"保存动作脚本失败。");
	}

	//显示动作数
	temp.Format(L"%d", triggerAnalyzer.GetTriggerCount());
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, temp);

}

//禁用当前选中的触发
void DlgTriggerEditor::OnBnClickedButtonEnable()
{
	//判断主窗口是否选中了元素
	if (gv->nowIsChooesElement == false)
	{
		AfxMessageBox(L"请先在地图编辑器中选择一个元素。");
		return;
	}

	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}

	//判断当前是否选择了动作
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"未选择动作。");
		return;
	}

	//获取动作名
	CString temp = m_listActionList.GetItemText(nowActionSelect, 1);

	//判断是否执行
	if (m_listActionList.GetItemText(nowActionSelect, 2)==L"true")
	{
		//禁用
		actionAnalyzer.SetActionExecute(temp, false);

		//设置标题
		SetDlgItemText(IDC_BUTTON_ENABLE, L"开启");
		m_listActionList.SetItemText(nowActionSelect, 2, L"false");
	}
	else
	{
		//开启
		actionAnalyzer.SetActionExecute(temp, true);

		//设置标题
		SetDlgItemText(IDC_BUTTON_ENABLE, L"禁用");
		m_listActionList.SetItemText(nowActionSelect, 2, L"true");
	}
}

//禁用所有动作
void DlgTriggerEditor::OnBnClickedButton16()
{
	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}


	//禁用所有的动作
	CString temp;
	for (int i = 0; i < m_listActionList.GetItemCount(); i++)
	{
		//获取动作名
		temp = m_listActionList.GetItemText(i, 1);

		//设置动作为禁用
		actionAnalyzer.SetActionExecute(temp, false);

		//设置ListCtrl标题
		m_listActionList.SetItemText(i, 2, L"false");
	}

	//设置按钮标题
	SetDlgItemText(IDC_BUTTON_ENABLE, L"开启");
}

//开启所有动作
void DlgTriggerEditor::OnBnClickedButton21()
{
	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}


	//开启所有的动作
	CString temp;
	for (int i = 0; i < m_listActionList.GetItemCount(); i++)
	{
		//获取动作名
		temp = m_listActionList.GetItemText(i, 1);

		//设置动作为禁用
		actionAnalyzer.SetActionExecute(temp, true);

		//设置ListCtrl标题
		m_listActionList.SetItemText(i, 2, L"true");
	}

	//设置按钮标题
	SetDlgItemText(IDC_BUTTON_ENABLE, L"禁用");

}

//删除动作
void DlgTriggerEditor::OnBnClickedButton10()
{	
	//判断主窗口是否选中了元素
	if (gv->nowIsChooesElement == false)
	{
		AfxMessageBox(L"请先在地图编辑器中选择一个元素。");
		return;
	}

	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}

	//判断当前是否选择了动作
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"未选择动作。");
		return;
	}
	
	//删除动作
	actionAnalyzer.DeleteAction(nowActionSelect);

	//删除表项
	m_listActionList.DeleteItem(nowActionSelect);

	//选择上一项
	nowActionSelect--;
	if (nowActionSelect>=0)
	{
		EasyListCtrl elc;
		elc.SelectRow(m_listActionList, nowActionSelect);
	}

	//显示动作数
	CString temp;
	temp.Format(L"%d", triggerAnalyzer.GetTriggerCount());
	SetDlgItemText(IDC_STATIC_ACTION_COUNT, temp);
}

//保存动作脚本
void DlgTriggerEditor::OnBnClickedButton18()
{
	//判断主窗口是否选中了元素
	if (gv->nowIsChooesElement == false)
	{
		AfxMessageBox(L"请先在地图编辑器中选择一个元素。");
		return;
	}

	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}

	//判断当前是否选择了动作
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"未选择动作。");
		return;
	}

	//获取触发器脚本
	CString temp;
	GetDlgItemText(IDC_EDIT_ACTION_PARAMS, temp);

	//设置动作脚本
	actionAnalyzer.SetActionParams(nowActionSelect, temp);

	//保存触发器列表
	if (triggerAnalyzer.SetTriggerActions(m_listTriggerList.GetItemText(nowTriggerSelect, 1), actionAnalyzer.GetActions(), actionAnalyzer.GetActionsCount()) == false)
	{
		AfxMessageBox(L"保存动作脚本失败。");
	}
}


void DlgTriggerEditor::OnBnClickedButton20()
{
	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}

	//判断当前是否选择了动作
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"未选择动作。");
		return;
	}

	//询问用户是否重置脚本
	if (MessageBox(L"确定要重置参数吗？\r\n注：重置参数并不会自动保存，如果需要恢复重置前的内容，\r\n可以先选择另一个动作，然后再切换回来。", L"询问",
		MB_ICONQUESTION | MB_YESNO)== IDNO)
	{
		return;
	}

	//获取动作名
	CString actionName = m_listActionList.GetItemText(nowActionSelect,1);
	if (actionName == L"")
	{
		AfxMessageBox(L"读取动作名发生错误。");
		return;
	}

	//查找该动作的参数
	CArray<ParamInfo> paramInfos;
	if (gv->triggerLoader.GetParamInfo(actionName, paramInfos) == false)
	{
		AfxMessageBox(L"查找参数信息失败。");
		return;
	}

	//生成默认参数列表
	CString param;
	for (int i = 0; i < paramInfos.GetCount(); i++)
	{
		if (i != 0)
		{
			param = param + L"\r\n";
		}
		param = param + L"<" + paramInfos[i].name + L">" + L"</" + paramInfos[i].name + L">";
	}

	//显示默认参数
	SetDlgItemText(IDC_EDIT_ACTION_PARAMS, param);
}

//帮助按钮
void DlgTriggerEditor::OnBnClickedButton17()
{
	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}

	//判断当前是否选择了动作
	if (nowActionSelect == -1)
	{
		AfxMessageBox(L"未选择动作。");
		return;
	}

	//获取动作名
	CString actionName = m_listActionList.GetItemText(nowActionSelect, 1);
	if (actionName == L"")
	{
		AfxMessageBox(L"读取动作名发生错误。");
		return;
	}

	//查找该动作的参数
	CArray<ParamInfo> paramInfos;
	if (gv->triggerLoader.GetParamInfo(actionName, paramInfos) == false)
	{
		AfxMessageBox(L"查找参数信息失败。");
		return;
	}

	//生成帮助信息
	CString helpInfo,temp;

	//帮助：动作名
	helpInfo = L"动作名：" + actionName;

	//帮助：参数个数
	temp.Format(L"%d", paramInfos.GetCount());
	helpInfo = helpInfo + L"\r\n  参数：" + temp + L"个";

	//帮助：动作提示
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
		helpInfo = helpInfo + L"\r\n  提示：" + temp;
	}
	
	//判断是否有参数
	CString paramHelp =L"";
	if (paramInfos.GetCount() != 0)
	{
		//生成参数帮助信息
		for (int i = 0; i < paramInfos.GetCount(); i++)
		{
			temp.Format(L"%d", i + 1);
			if (i != 0)
			{
				paramHelp = paramHelp + L"\r\n";
			}
			paramHelp = paramHelp + L"参数" + temp + L"：" + paramInfos[i].name + L"（";
			paramHelp = paramHelp + (paramInfos[i].necessary ? L"必须" : L"可空") + L"），";
			paramHelp = paramHelp + paramInfos[i].tip;
		}

		//输出帮助信息
		AfxMessageBox(helpInfo + L"\r\n\r\n" + paramHelp);

		return;
	}

	AfxMessageBox(helpInfo);
}


void DlgTriggerEditor::OnBnClickedButton7()
{
	//判断主窗口是否选中了元素
	if (gv->nowIsChooesElement==false)
	{
		AfxMessageBox(L"请先在地图编辑器中选择一个元素。");
		return;
	}
	gv->nowChooesElementTriggerScript = triggerAnalyzer.GetScript();
	GetParent()->SendMessage(MY_TRIGGER_CHANGE,0,0);
}


void DlgTriggerEditor::OnBnClickedButton19()
{
	//判断当前是否选择了触发器
	if (nowTriggerSelect == -1)
	{
		AfxMessageBox(L"请先选择一个触发器。");
		return;
	}



	EasyFile ef;
	EasyPath ep;

	ef.WriteCString(ep.GetProgramDir() + L"temp_trigger.txt", triggerAnalyzer.GetScript(true),true);
	ef.Select(ep.GetProgramDir() + L"temp_trigger.txt");
}
