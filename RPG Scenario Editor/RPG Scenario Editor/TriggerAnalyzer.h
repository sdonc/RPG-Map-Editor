#pragma once
struct TriggerScript
{
	CString name;			//��������
	bool execute;			//�Ƿ�ִ�У�true = ִ�У�
	int actionCount;		//������
	CString actions;		//�����ű�
};

//�������ű�������
class TriggerAnalyzer
{
public:
	TriggerAnalyzer();
	~TriggerAnalyzer();

	
	//���ش������ű�
	//�������Զ�����#r#n��#t
	void LoadScript(CString script);

	//ȡ�������ű������ش����������ı���
	//����format���ɿգ����Ƿ��ʽ���������true = �Զ���#r#nת���ɻ��з���#tת�����Ʊ����
	CString GetScript(bool format=false);

	//ȡ��������
	int GetTriggerCount();

	//ȡ��������Ϣ
	bool GetTriggerInfo(CString triggerName, TriggerScript& triggerInfo);

	//ȡ��������Ϣ�б�
	int GetTriggerInfos(CString triggerName,CArray<TriggerScript> &triggerScriptArray);

	//��Ӵ�����
	bool AddTrigger(CString triggerName);

	//ɾ��������
	bool DeleteTrigger(CString triggerName);

	//�������Ƿ����
	bool IsTriggerExist(CString triggerName);

	//���ô������Ƿ��ִ��
	bool SetTriggerExecute(CString triggerName,bool execute);

	//���ô����������ű�
	bool SetTriggerActions(CString triggerName,CString actions, int actionCount);
	



private:
	CArray<TriggerScript> triggers;
};

/*
�������ű��洢��ʽ

<Script>
	<Triggers>OnEnterStart,OnLeaveEnd</Triggers>  �洢���еĴ�������־���ö��Ÿ���

	<OnEnterStart>
		<Execute>true</Execute>
		<ActionCount>3</AvtionCount>
		<ActionList>
			<Action1>
				<Execute>true</Execute>
				<Name></Name>
				<Params><Params>
			</Action1>
			<Action2>
				<Execute>true</Execute>
				<Name></Name>
				<Params><Params>
			</Action2>
			<Action3>
				<Execute>true</Execute>
				<Name></Name>
				<Params></Params>
			</Action3>
		</ActionList>
	</OnEnterStart>

	<OnLeaveEnd>
		<Execute>true</Execute>
		<ActionCount>1</AvtionCount>
		<Action1>
			<Execute>true</Execute>
			<Name></Name>
			<Params><Params>
		</Action1>
	</OnLeaveEnd>
</Script>

*/