#include "stdafx.h"
#include "TriggerLoader.h"


TriggerLoader::TriggerLoader()
{
}

TriggerLoader::~TriggerLoader()
{
}

void TriggerLoader::LoadTriggerConfig()
{
	Check();			//检查配置文件
	LoadTriggerInfo();	//加载触发器信息
	LoadActionInfo();	//加载动作信息
	LoadVariableInfo();	//加载全局变量
}

bool TriggerLoader::GetParamInfo(CString actionName, CArray<ParamInfo> & paramInfos)
{
	//清除数据
	paramInfos.RemoveAll();

	//查找对应的参数信息
	bool exist;
	int index;
	for (int i = 0; i < actionInfos.GetCount(); i++)
	{
		if (actionInfos[i].name == actionName)
		{
			exist = true;
			index = i;
			break;
		}
	}
	if (exist==false)
	{
		return false;
	}

	CString params = actionInfos[index].params;//参数脚本
	params = NormalizeText(params);//规范化参数脚本

	CString temp;//临时存放某个参数的脚本
	CString temp1;//存放序号
	EasyText et;
	for (int i = 0; i < actionInfos[index].paramCount; i++)
	{
		temp1.Format(L"%d", i + 1);
		temp = et.Middle(params, L"<Param" + temp1 + L">", L"</Param" + temp1 + L">");

		paramInfos.Add(ParamInfo{
			et.Middle(temp,L"<ParamName>",L"</ParamName>"),
			et.Middle(temp,L"<Necessary>",L"</Necessary>") == L"true"?true:false,
			et.Middle(temp, L"<Type>", L"</Type>"),
			et.Middle(temp, L"<Tip>", L"</Tip>")
		});
	}
	return true;
}

void TriggerLoader::ReleaseData()
{
	triggerInfos.RemoveAll();
	actionInfos.RemoveAll();
	variableInfos.RemoveAll();
}

void TriggerLoader::Check()
{
	EasyPath ep;
	EasyFile ef;
	if (ef.IsFileExist(ep.GetProgramDir() + L"triggers\\TriggerConfig.sdonc") == false)
	{
		AfxMessageBox(L"触发器配置文件丢失。");
		exit(-1);
	}
	if (ef.IsFileExist(ep.GetProgramDir() + L"triggers\\ActionConfig.sdonc") == false)
	{
		AfxMessageBox(L"动作配置文件丢失。");
		exit(-1);
	}
	if (ef.IsFileExist(ep.GetProgramDir() + L"triggers\\VariableConfig.sdonc") == false)
	{
		AfxMessageBox(L"变量配置文件丢失。");
		exit(-1);
	}
}

void TriggerLoader::LoadTriggerInfo()
{
	//读入文件
	EasyPath ep;
	EasyFile ef;
	EasyText et;
	CString str = ef.ReadCString(ep.GetProgramDir() + L"triggers\\TriggerConfig.sdonc");
	str = NormalizeText(str);

	//读取触发器名
	CString triggerStr = et.Middle(str, L"<Trigger>", L"</Trigger>");

	//分割触发器名
	CStringArray triggerNames;
	et.DivideText(triggerStr, L",", triggerNames);
	for (int i = triggerNames.GetCount() - 1; i >= 0; i--)
	{
		triggerNames[i].Trim();
		if (triggerNames[i] == L"")
		{
			triggerNames.RemoveAt(i);
		}
	}


	//添加触发器
	CString temp;
	for (int i = 0; i < triggerNames.GetCount(); i++)
	{
		//读取某个触发器的配置信息
		temp = et.Middle(str, L"<" + triggerNames.GetAt(i) + L">", L"</" + triggerNames.GetAt(i) + L">");

		//读取提示信息
		temp = et.Middle(temp, L"<Tip>", L"</Tip>");
		temp.Trim();

		triggerInfos.Add(TriggerInfo{
			triggerNames.GetAt(i),
			temp
		});
	}

}

void TriggerLoader::LoadActionInfo()
{
	//读入文件
	EasyPath ep;
	EasyFile ef;
	EasyText et;
	CString str = ef.ReadCString(ep.GetProgramDir() + L"triggers\\ActionConfig.sdonc");
	str = NormalizeText(str);

	//读取动作名
	CString actionStr = et.Middle(str, L"<Action>", L"</Action>");

	//分割动作名
	CStringArray actionNames;
	et.DivideText(actionStr, L",", actionNames);
	for (int i = actionNames.GetCount() - 1; i >= 0; i--)
	{
		actionNames[i].Trim();
		if (actionNames[i] == L"")
		{
			actionNames.RemoveAt(i);
		}
	}

	//添加动作
	CString temp;		//完整的动作配置信息
	CString actionTip;	//动作提示
	CString infoStr;	//配置信息中<Info>标识间的内容
	CString paramList;	//参数列表
	int paramCount;		//参数个数

	for (int i = 0; i < actionNames.GetCount(); i++)
	{
		temp = et.Middle(str, L"<" + actionNames.GetAt(i) + L">", L"</" + actionNames.GetAt(i) + L">");

		//读取Info标识间的信息
		infoStr = et.Middle(temp, L"<Info>", L"/Info");

		//读取参数个数
		paramCount = _ttoi(et.Middle(infoStr, L"<ParamCount>", L"</ParamCount>").Trim());

		//读取动作帮助文本
		actionTip = et.Middle(infoStr, L"<Tip>", L"</Tip>");
		actionTip.Trim();

		//读取参数配置信息
		if (paramCount == 0)
		{
			paramList = L"";
		}
		else
		{
			paramList = et.Middle(temp, L"<ParamList>", L"</ParamList>");
		}

		//添加动作
		actionInfos.Add(ActionInfo{
			actionNames.GetAt(i),
			paramCount,
			actionTip,
			paramList
		});
	}



}

void TriggerLoader::LoadVariableInfo()
{
	//读入文件
	EasyPath ep;
	EasyFile ef;
	EasyText et;
	CString str = ef.ReadCString(ep.GetProgramDir() + L"triggers\\VariableConfig.sdonc");
	str = NormalizeText(str);

	//分割文本
	CStringArray rows;
	et.DivideText(str, L"\r\n", rows);


	CString type, name, value;
	CString errorText;
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		rows[i].Trim();

		//读取类型
		type = et.Left(rows.GetAt(i), L" ");

		//读取变量名
		name = et.Middle(rows.GetAt(i), type,L";");
		name.Trim();

		//变量名不能为空
		if (name == L"")
		{
			rows.RemoveAt(i);
			continue;
		}

		
		if (type == L"string")
		{
			variableInfos.Add(VariableInfo{
				name,
				type,
				L""
			});
		}
		else if (type ==  L"int")
		{
			variableInfos.Add(VariableInfo{
				name,
				type,
				L"0"
			});
		}
		else if(type == L"bool")
		{
			variableInfos.Add(VariableInfo{
				name,
				type,
				L"false"
			});
		}
		else
		{
			CString temp;
			temp.Format(L"%d", i + 1);
			AddErrorText(
				errorText,
				L"全局变量配置文件，第" + temp + "行\"" + rows.GetAt(i) + L"\"的类型\"" + type + L"\"不是本程序所支持的类型。"
			);
		}
	}

	if (errorText!=L"")
	{
		AfxMessageBox(errorText);
	}

}

CString TriggerLoader::NormalizeText(CString text)
{
	bool isOK;
	EasyText et;
	CStringArray rows;
	CString temp;

	isOK = et.DivideText(text, L"\r\n", rows);//以换行符来分割字符串
	if (isOK == false)
	{
		return text.Trim();//传进来的是空文本或者只有一行。
	}

	//清除注释（从末尾开始往头遍历）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//取 "//" 的左边
		}
	}


	//清除空行（注意：不能放在“清除注释”的前面，因为有可能清除注释后那行变成空的）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}

	//生成规范化的文本
	for (int i = 0; i < rows.GetCount(); i++)
	{
		if (i == 0)
		{
			text = rows.GetAt(i);
		}
		else
		{
			text = text + L"\r\n" + rows.GetAt(i);
		}
	}
	return text;
}

void TriggerLoader::AddErrorText(CString & src, CString willAddText)
{
	if (src == L"")
	{
		src = willAddText;
	}
	else
	{
		src = src + L"\r\n" + willAddText;
	}
}
