#include "stdafx.h"
#include "TriggerAnalyzer.h"


TriggerAnalyzer::TriggerAnalyzer()
{
}


TriggerAnalyzer::~TriggerAnalyzer()
{
	triggers.RemoveAll();
}

void TriggerAnalyzer::LoadScript(CString script)
{
	//清除旧脚本
	triggers.RemoveAll();

	//检查是否为空
	if (script == L"")
	{
		return;
	}

	//检查语法错误
	if (script.Find(L"\r\n")!=-1 || script.Find(L"\t") != -1)
	{
		return;
	}

	//去除所有换行和所有制表符
	script.Replace(L"#r#n", L"");
	script.Replace(L"#t", L"");

	EasyText et;
	CString src;//脚本字符串中的内容
	src = et.Middle(script, L"<Script>", L"</Script>");
	
	//检查脚本是否为空
	if (src == L"")
	{
		return;
	}

	//<Triggers>OnEnterStart,OnLeaveEnd</Triggers>
	//读取<Triggers>标志的内容

	//检查触发器是否为空
	CString temp;
	temp = et.Middle(src, L"<Triggers>", L"</Triggers>");
	if (temp == L"")
	{
		return;
	}

	//处理触发器名
	CStringArray triggerNames;
	if (et.DivideText(temp, L",", triggerNames)==false)
	{
		//如果分割文本失败的话，说明只有一个触发器
		triggerNames.Add(temp);
	}

	//加入触发 
	for (int i = 0; i < triggerNames.GetCount(); i++)
	{
		temp = et.Middle(src, L"<" + triggerNames.GetAt(i) + L">", L"</" + triggerNames.GetAt(i) + L">");
		triggers.Add(TriggerScript{
			triggerNames.GetAt(i),
			et.Middle(temp,L"<Execute>",L"</Execute>") == L"true" ? true : false,
			_ttoi(et.Middle(temp, L"<ActionCount>", L"</ActionCount>")),
			et.Middle(temp,L"<ActionList>",L"</ActionList>")
		});
	}
}

CString TriggerAnalyzer::GetScript(bool format)
{
	CString script;
	CString triggerName;
	CString triggerScripts;
	CString temp;
	CString temp1;

	//生成触发器名
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		if (i==0)
		{
			triggerName = triggers[i].name;
		}
		else
		{
			triggerName = triggerName + L"," + triggers[i].name;
		}
	}
	triggerName = L"#t<Triggers>" + triggerName + L"</Triggers>";


	//生成触发器脚本
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		//触发器名（起始）
		temp = L"#t<" + triggers[i].name + L">";

		//是否执行
		temp = temp + L"#r#n#t#t<Execute>" + (triggers[i].execute ? L"true" : L"false") + L"</Execute>";

		//触发器数
		temp1.Format(L"%d", triggers[i].actionCount);
		temp = temp + L"#r#n#t#t<ActionCount>" + temp1 + L"</ActionCount>";

		//所有触发器
		temp = temp + L"#r#n#t#t<ActionList>#r#n" + triggers[i].actions + L"#r#n#t#t</ActionList>";

		//触发器名（起始）
		temp = temp + L"#r#n#t</" + triggers[i].name + L">";

		if (i==0)
		{
			triggerScripts = temp;
		}
		else
		{
			triggerScripts = triggerScripts + L"#r#n#r#n" + temp;
		}
	}

	//合并成总的触发器脚本
	script = L"<Script>";
	script = script + L"#r#n" + triggerName;
	script = script + L"#r#n" + triggerScripts;
	script = script + L"#r#n" + L"</Script>";

	if (format)
	{
		script.Replace(L"#r#n", L"\r\n");
		script.Replace(L"#t", L"\t");
	}
	return script;
}

int TriggerAnalyzer::GetTriggerCount()
{
	return triggers.GetCount();
}

bool TriggerAnalyzer::GetTriggerInfo(CString triggerName, TriggerScript& triggerInfo)
{
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		if (triggers[i].name == triggerName)
		{
			triggerInfo.actionCount = triggers[i].actionCount;
			triggerInfo.actions = triggers[i].actions;
			triggerInfo.execute = triggers[i].execute;
			triggerInfo.name = triggers[i].name;
			return true;
		}
	}

	return false;
}

int TriggerAnalyzer::GetTriggerInfos(CString triggerName, CArray<TriggerScript>& triggerScriptArray)
{
	triggerScriptArray.Copy(triggers);
	return triggers.GetCount();
}

bool TriggerAnalyzer::AddTrigger(CString triggerName)
{
	//触发器名不能为空
	if (triggerName == L"")
	{
		return false;
	}

	//触发器已存在
	if (IsTriggerExist(triggerName))
	{
		return false;
	}

	triggers.Add(TriggerScript{ triggerName ,true,0,L""});


	return true;
}

bool TriggerAnalyzer::DeleteTrigger(CString triggerName)
{
	if (triggerName==L"")
	{
		return false;
	}
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		if (triggers[i].name == triggerName)
		{
			triggers.RemoveAt(i);
			return true;
		}
	}
	return false;
}

bool TriggerAnalyzer::IsTriggerExist(CString triggerName)
{
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		if (triggers[i].name == triggerName)
		{
			return true;
		}
	}
	return false;
}

bool TriggerAnalyzer::SetTriggerExecute(CString triggerName, bool execute)
{
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		if (triggers[i].name == triggerName)
		{
			triggers[i].execute = execute;
			return true;
		}
	}
	return false;
}

bool TriggerAnalyzer::SetTriggerActions(CString triggerName, CString actions,int actionCount)
{
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		if (triggers[i].name == triggerName)
		{
			triggers[i].actions = actions;
			triggers[i].actionCount = actionCount;

#if _DEBUG
			EasyFile ef;
			EasyPath ep;
			ef.WriteCString(ep.GetProgramDir() + L"test\\nowTriggerScript.txt", GetScript(true), true);
#endif // _DEBUG


			return true;
		}
	}
	return false;
}
