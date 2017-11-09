#pragma once

struct Action
{
	CString name;	//动作名
	bool execute;	//动作是否执行（true = 执行）
	CString params;	//动作参数
};
class ActionAnalyzer
{
public:
	ActionAnalyzer();
	~ActionAnalyzer();

	//加载动作脚本
	//函数会自动处理#r#n和#t
	void LoadActions(CString actionScript,int actionCount);

	//取动作脚本
	//参数format（可空）：是否格式化输出。（true = 自动把#r#n转换成换行符，#t转换成制表符）
	//参数formatParam（可空）：是否格式化参数输出。（true = 自动把$r$n转换成换行符，$t转换成制表符）
	CString GetActions(bool format=false,bool formatParam=false);

	//取动作数
	//返回 actions 的数量
	int GetActionsCount();

	//取动作信息
	bool GetActionInfo(CString actionName, Action& action);
	bool GetActionInfo(int index, Action& action);


	//取动作信息列表
	int GetActionInfos(CString actionName,CArray<Action> &actions);

	//添加动作
	bool AddAction(CString actionName,CString params = L"");

	//删除动作
	bool DeleteAction(CString actionName);
	bool DeleteAction(int index);

	//动作是否存在
	bool IsActionExist(CString actionName);
	bool IsActionExist(int index);

	//设置动作是否可执行
	bool SetActionExecute(CString actionName, bool execute);
	bool SetActionExecute(int index,bool execute);

	//设置动作参数
	bool SetActionParams(CString actionName, CString params);
	bool SetActionParams(int index,CString params);

private:
	CArray<Action> actions;
};


