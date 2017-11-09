#pragma once

struct Action
{
	CString name;	//������
	bool execute;	//�����Ƿ�ִ�У�true = ִ�У�
	CString params;	//��������
};
class ActionAnalyzer
{
public:
	ActionAnalyzer();
	~ActionAnalyzer();

	//���ض����ű�
	//�������Զ�����#r#n��#t
	void LoadActions(CString actionScript,int actionCount);

	//ȡ�����ű�
	//����format���ɿգ����Ƿ��ʽ���������true = �Զ���#r#nת���ɻ��з���#tת�����Ʊ����
	//����formatParam���ɿգ����Ƿ��ʽ�������������true = �Զ���$r$nת���ɻ��з���$tת�����Ʊ����
	CString GetActions(bool format=false,bool formatParam=false);

	//ȡ������
	//���� actions ������
	int GetActionsCount();

	//ȡ������Ϣ
	bool GetActionInfo(CString actionName, Action& action);
	bool GetActionInfo(int index, Action& action);


	//ȡ������Ϣ�б�
	int GetActionInfos(CString actionName,CArray<Action> &actions);

	//��Ӷ���
	bool AddAction(CString actionName,CString params = L"");

	//ɾ������
	bool DeleteAction(CString actionName);
	bool DeleteAction(int index);

	//�����Ƿ����
	bool IsActionExist(CString actionName);
	bool IsActionExist(int index);

	//���ö����Ƿ��ִ��
	bool SetActionExecute(CString actionName, bool execute);
	bool SetActionExecute(int index,bool execute);

	//���ö�������
	bool SetActionParams(CString actionName, CString params);
	bool SetActionParams(int index,CString params);

private:
	CArray<Action> actions;
};


