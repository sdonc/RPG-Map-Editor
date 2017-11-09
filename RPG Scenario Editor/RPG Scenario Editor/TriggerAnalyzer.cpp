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
	//����ɽű�
	triggers.RemoveAll();

	//����Ƿ�Ϊ��
	if (script == L"")
	{
		return;
	}

	//����﷨����
	if (script.Find(L"\r\n")!=-1 || script.Find(L"\t") != -1)
	{
		return;
	}

	//ȥ�����л��к������Ʊ��
	script.Replace(L"#r#n", L"");
	script.Replace(L"#t", L"");

	EasyText et;
	CString src;//�ű��ַ����е�����
	src = et.Middle(script, L"<Script>", L"</Script>");
	
	//���ű��Ƿ�Ϊ��
	if (src == L"")
	{
		return;
	}

	//<Triggers>OnEnterStart,OnLeaveEnd</Triggers>
	//��ȡ<Triggers>��־������

	//��鴥�����Ƿ�Ϊ��
	CString temp;
	temp = et.Middle(src, L"<Triggers>", L"</Triggers>");
	if (temp == L"")
	{
		return;
	}

	//����������
	CStringArray triggerNames;
	if (et.DivideText(temp, L",", triggerNames)==false)
	{
		//����ָ��ı�ʧ�ܵĻ���˵��ֻ��һ��������
		triggerNames.Add(temp);
	}

	//���봥�� 
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

	//���ɴ�������
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


	//���ɴ������ű�
	for (int i = 0; i < triggers.GetCount(); i++)
	{
		//������������ʼ��
		temp = L"#t<" + triggers[i].name + L">";

		//�Ƿ�ִ��
		temp = temp + L"#r#n#t#t<Execute>" + (triggers[i].execute ? L"true" : L"false") + L"</Execute>";

		//��������
		temp1.Format(L"%d", triggers[i].actionCount);
		temp = temp + L"#r#n#t#t<ActionCount>" + temp1 + L"</ActionCount>";

		//���д�����
		temp = temp + L"#r#n#t#t<ActionList>#r#n" + triggers[i].actions + L"#r#n#t#t</ActionList>";

		//������������ʼ��
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

	//�ϲ����ܵĴ������ű�
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
	//������������Ϊ��
	if (triggerName == L"")
	{
		return false;
	}

	//�������Ѵ���
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
