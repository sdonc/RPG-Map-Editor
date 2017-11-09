#include "stdafx.h"
#include "ActionAnalyzer.h"


ActionAnalyzer::ActionAnalyzer()
{
}


ActionAnalyzer::~ActionAnalyzer()
{
}

void ActionAnalyzer::LoadActions(CString actionScript, int actionCount)
{
	//���������
	actions.RemoveAll();

	//����������Ϊ0
	if (actionCount == 0)
	{
		return;
	}

	//����Ƿ�Ϊ��
	if (actionScript == L"")
	{
		return;
	}

	//����﷨����
	if (actionScript.Find(L"\r\n") != -1 || actionScript.Find(L"\t") != -1)
	{
		return;
	}

	//������л��к��Ʊ��
	actionScript.Replace(L"#r#n", L"");
	actionScript.Replace(L"#t", L"");

	CString temp, temp1;
	EasyText et;

	//���붯��
	for (int i = 0; i < actionCount; i++)
	{
		//��ȡ�����ű�
		temp1.Format(L"%d", i + 1);
		temp = et.Middle(actionScript, L"<Action" + temp1 + L">", L"</Action" + temp1 + L">");

		//��ʽ�������ı�����ѹ��
		temp1 = et.Middle(temp, L"<Params>", L"</Params>");
		temp1.Replace(L"$r$n", L"\r\n");
		temp1.Replace(L"$t", L"\t");

		//��Ӷ���
		actions.Add(Action{
			et.Middle(temp,L"<Name>",L"</Name>"),
			et.Middle(temp,L"<Execute>",L"</Execute>") == L"true" ? true : false,
			temp1
		});
	}
}

CString ActionAnalyzer::GetActions(bool format, bool formatParam)
{
	CString actionScript;//���صĶ����ű�

	CString temp,param, count;
	for (int i = 0; i < actions.GetCount(); i++)
	{
		count.Format(L"%d", i + 1);
		temp = L"#t#t#t<Action" + count + L">";
		temp = temp + L"#r#n#t#t#t#t<Name>" + actions[i].name + L"</Name>";
		temp = temp + L"#r#n#t#t#t#t<Execute>" + (actions[i].execute ? L"true" : L"false") + L"</Execute>";
		
		//��ʽ��������ѹ����
		param = actions[i].params;
		param.Replace(L"\r\n", L"$r$n");
		param.Replace(L"\t",L"$t");

		temp = temp + L"#r#n#t#t#t#t<Params>" + param + L"</Params>";
		temp = temp + L"#r#n#t#t#t</Action" + count + L">";

		if (i==0)
		{
			actionScript = temp;
		}
		else
		{
			actionScript = actionScript + L"#r#n" + temp;
		}
	}

	if (format)
	{
		actionScript.Replace(L"#r#n", L"\r\n");
		actionScript.Replace(L"#t", L"\t");
	}

	if (formatParam)
	{
		actionScript.Replace(L"$r$n", L"\r\n");
		actionScript.Replace(L"$t", L"\t");
	}

	return actionScript;
}

int ActionAnalyzer::GetActionsCount()
{
	return actions.GetCount();
}

bool ActionAnalyzer::GetActionInfo(CString actionName, Action& action)
{
	for (int i = 0; i < actions.GetCount(); i++)
	{
		if (actions[i].name == actionName)
		{
			action.name = actions[i].name;
			action.execute = actions[i].execute;
			action.params = actions[i].params;
			return true;
		}
	}
	return false;
}

bool ActionAnalyzer::GetActionInfo(int index, Action & action)
{
	if (index<0 || index>actions.GetCount()-1)
	{
		return false;
	}
	action = actions[index];
	return true;
}

int ActionAnalyzer::GetActionInfos(CString actionName, CArray<Action>& actions)
{
	actions.Copy(this->actions);
	return actions.GetCount();
}

bool ActionAnalyzer::AddAction(CString actionName, CString params)
{
	if (actionName==L"")
	{
		return false;
	}
	actions.Add(Action{ actionName ,true,params });
	return true;
}

bool ActionAnalyzer::DeleteAction(CString actionName)
{
	for (int i = 0; i < actions.GetCount(); i++)
	{
		if (actions[i].name == actionName)
		{
			actions.RemoveAt(i);
			return true;
		}
	}
	return false;
}

bool ActionAnalyzer::DeleteAction(int index)
{
	if (IsActionExist(index))
	{
		actions.RemoveAt(index);
		return true;
	}
	return false;
}

bool ActionAnalyzer::IsActionExist(CString actionName)
{
	for (int i = 0; i < actions.GetCount(); i++)
	{
		if (actions[i].name == actionName)
		{
			return true;
		}
	}
	return false;
}

bool ActionAnalyzer::IsActionExist(int index)
{
	if (index <0 || index>actions.GetCount() - 1)
	{
		return false;
	}
	return true;
}

bool ActionAnalyzer::SetActionExecute(CString actionName, bool execute)
{
	for (int i = 0; i < actions.GetCount(); i++)
	{
		if (actions[i].name == actionName)
		{
			actions[i].execute = execute;
			return true;
		}
	}
	return false;
}

bool ActionAnalyzer::SetActionExecute(int index, bool execute)
{
	if (index <0 || index>actions.GetCount() - 1)
	{
		return false;
	}
	actions[index].execute = execute;
	return true;
}

bool ActionAnalyzer::SetActionParams(CString actionName, CString params)
{
	for (int i = 0; i < actions.GetCount(); i++)
	{
		if (actions[i].name == actionName)
		{
			actions[i].params = params;
			return true;
		}
	}
	return false;
}

bool ActionAnalyzer::SetActionParams(int index, CString params)
{
	if (index <0 || index>actions.GetCount()-1)
	{
		return false;
	}
	actions[index].params = params;
	return true;
}
