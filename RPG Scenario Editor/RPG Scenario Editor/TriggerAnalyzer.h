#pragma once
struct TriggerScript
{
	CString name;			//触发器名
	bool execute;			//是否执行（true = 执行）
	int actionCount;		//动作数
	CString actions;		//动作脚本
};

//触发器脚本分析器
class TriggerAnalyzer
{
public:
	TriggerAnalyzer();
	~TriggerAnalyzer();

	
	//加载触发器脚本
	//函数会自动处理#r#n和#t
	void LoadScript(CString script);

	//取触发器脚本（返回触发器所有文本）
	//参数format（可空）：是否格式化输出。（true = 自动把#r#n转换成换行符，#t转换成制表符）
	CString GetScript(bool format=false);

	//取触发器数
	int GetTriggerCount();

	//取触发器信息
	bool GetTriggerInfo(CString triggerName, TriggerScript& triggerInfo);

	//取触发器信息列表
	int GetTriggerInfos(CString triggerName,CArray<TriggerScript> &triggerScriptArray);

	//添加触发器
	bool AddTrigger(CString triggerName);

	//删除触发器
	bool DeleteTrigger(CString triggerName);

	//触发器是否存在
	bool IsTriggerExist(CString triggerName);

	//设置触发器是否可执行
	bool SetTriggerExecute(CString triggerName,bool execute);

	//设置触发器动作脚本
	bool SetTriggerActions(CString triggerName,CString actions, int actionCount);
	



private:
	CArray<TriggerScript> triggers;
};

/*
触发器脚本存储格式

<Script>
	<Triggers>OnEnterStart,OnLeaveEnd</Triggers>  存储所有的触发器标志，用逗号隔开

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