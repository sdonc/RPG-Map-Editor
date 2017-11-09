#pragma once

//触发器信息
struct TriggerInfo
{
	CString name;	//触发器名
	CString tip;	//触发器提示
};

//动作信息
struct ActionInfo
{
	CString name;	//动作名
	int paramCount;	//参数个数
	CString tip;	//动作提示
	CString params;	//参数信息
};

//参数信息
struct ParamInfo
{
	CString name;	//参数名
	bool necessary;	//是否必须
	CString type;	//参数类型
	CString tip;	//参数提示
};

//全局变量信息
struct VariableInfo
{
	CString name;	//变量名
	CString type;	//类型
	CString value;	//值
};
class TriggerLoader
{
public:
	TriggerLoader();
	~TriggerLoader();

	//加载触发器信息
	void LoadTriggerConfig();

	CArray<TriggerInfo> triggerInfos;	//所有可用的触发器
	
	CArray<ActionInfo> actionInfos;	//所有可用的动作

	CArray<VariableInfo> variableInfos;	//所有可用的变量

	bool GetParamInfo(CString actionName, CArray<ParamInfo> & paramInfos);

private:
	//清除数据
	void ReleaseData();

	//检查配置文件
	void Check();

	//加载触发器信息
	void LoadTriggerInfo();

	//加载动作信息
	void LoadActionInfo();

	//加载全局变量
	void LoadVariableInfo();

	//处理文本
	CString NormalizeText(CString text);

	//添加错误文本
	void AddErrorText(CString &src, CString willAddText);
};

