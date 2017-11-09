#pragma once

//��������Ϣ
struct TriggerInfo
{
	CString name;	//��������
	CString tip;	//��������ʾ
};

//������Ϣ
struct ActionInfo
{
	CString name;	//������
	int paramCount;	//��������
	CString tip;	//������ʾ
	CString params;	//������Ϣ
};

//������Ϣ
struct ParamInfo
{
	CString name;	//������
	bool necessary;	//�Ƿ����
	CString type;	//��������
	CString tip;	//������ʾ
};

//ȫ�ֱ�����Ϣ
struct VariableInfo
{
	CString name;	//������
	CString type;	//����
	CString value;	//ֵ
};
class TriggerLoader
{
public:
	TriggerLoader();
	~TriggerLoader();

	//���ش�������Ϣ
	void LoadTriggerConfig();

	CArray<TriggerInfo> triggerInfos;	//���п��õĴ�����
	
	CArray<ActionInfo> actionInfos;	//���п��õĶ���

	CArray<VariableInfo> variableInfos;	//���п��õı���

	bool GetParamInfo(CString actionName, CArray<ParamInfo> & paramInfos);

private:
	//�������
	void ReleaseData();

	//��������ļ�
	void Check();

	//���ش�������Ϣ
	void LoadTriggerInfo();

	//���ض�����Ϣ
	void LoadActionInfo();

	//����ȫ�ֱ���
	void LoadVariableInfo();

	//�����ı�
	CString NormalizeText(CString text);

	//��Ӵ����ı�
	void AddErrorText(CString &src, CString willAddText);
};

