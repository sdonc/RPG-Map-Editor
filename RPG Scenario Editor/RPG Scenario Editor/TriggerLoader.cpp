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
	Check();			//��������ļ�
	LoadTriggerInfo();	//���ش�������Ϣ
	LoadActionInfo();	//���ض�����Ϣ
	LoadVariableInfo();	//����ȫ�ֱ���
}

bool TriggerLoader::GetParamInfo(CString actionName, CArray<ParamInfo> & paramInfos)
{
	//�������
	paramInfos.RemoveAll();

	//���Ҷ�Ӧ�Ĳ�����Ϣ
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

	CString params = actionInfos[index].params;//�����ű�
	params = NormalizeText(params);//�淶�������ű�

	CString temp;//��ʱ���ĳ�������Ľű�
	CString temp1;//������
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
		AfxMessageBox(L"�����������ļ���ʧ��");
		exit(-1);
	}
	if (ef.IsFileExist(ep.GetProgramDir() + L"triggers\\ActionConfig.sdonc") == false)
	{
		AfxMessageBox(L"���������ļ���ʧ��");
		exit(-1);
	}
	if (ef.IsFileExist(ep.GetProgramDir() + L"triggers\\VariableConfig.sdonc") == false)
	{
		AfxMessageBox(L"���������ļ���ʧ��");
		exit(-1);
	}
}

void TriggerLoader::LoadTriggerInfo()
{
	//�����ļ�
	EasyPath ep;
	EasyFile ef;
	EasyText et;
	CString str = ef.ReadCString(ep.GetProgramDir() + L"triggers\\TriggerConfig.sdonc");
	str = NormalizeText(str);

	//��ȡ��������
	CString triggerStr = et.Middle(str, L"<Trigger>", L"</Trigger>");

	//�ָ������
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


	//��Ӵ�����
	CString temp;
	for (int i = 0; i < triggerNames.GetCount(); i++)
	{
		//��ȡĳ����������������Ϣ
		temp = et.Middle(str, L"<" + triggerNames.GetAt(i) + L">", L"</" + triggerNames.GetAt(i) + L">");

		//��ȡ��ʾ��Ϣ
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
	//�����ļ�
	EasyPath ep;
	EasyFile ef;
	EasyText et;
	CString str = ef.ReadCString(ep.GetProgramDir() + L"triggers\\ActionConfig.sdonc");
	str = NormalizeText(str);

	//��ȡ������
	CString actionStr = et.Middle(str, L"<Action>", L"</Action>");

	//�ָ����
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

	//��Ӷ���
	CString temp;		//�����Ķ���������Ϣ
	CString actionTip;	//������ʾ
	CString infoStr;	//������Ϣ��<Info>��ʶ�������
	CString paramList;	//�����б�
	int paramCount;		//��������

	for (int i = 0; i < actionNames.GetCount(); i++)
	{
		temp = et.Middle(str, L"<" + actionNames.GetAt(i) + L">", L"</" + actionNames.GetAt(i) + L">");

		//��ȡInfo��ʶ�����Ϣ
		infoStr = et.Middle(temp, L"<Info>", L"/Info");

		//��ȡ��������
		paramCount = _ttoi(et.Middle(infoStr, L"<ParamCount>", L"</ParamCount>").Trim());

		//��ȡ���������ı�
		actionTip = et.Middle(infoStr, L"<Tip>", L"</Tip>");
		actionTip.Trim();

		//��ȡ����������Ϣ
		if (paramCount == 0)
		{
			paramList = L"";
		}
		else
		{
			paramList = et.Middle(temp, L"<ParamList>", L"</ParamList>");
		}

		//��Ӷ���
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
	//�����ļ�
	EasyPath ep;
	EasyFile ef;
	EasyText et;
	CString str = ef.ReadCString(ep.GetProgramDir() + L"triggers\\VariableConfig.sdonc");
	str = NormalizeText(str);

	//�ָ��ı�
	CStringArray rows;
	et.DivideText(str, L"\r\n", rows);


	CString type, name, value;
	CString errorText;
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		rows[i].Trim();

		//��ȡ����
		type = et.Left(rows.GetAt(i), L" ");

		//��ȡ������
		name = et.Middle(rows.GetAt(i), type,L";");
		name.Trim();

		//����������Ϊ��
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
				L"ȫ�ֱ��������ļ�����" + temp + "��\"" + rows.GetAt(i) + L"\"������\"" + type + L"\"���Ǳ�������֧�ֵ����͡�"
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

	isOK = et.DivideText(text, L"\r\n", rows);//�Ի��з����ָ��ַ���
	if (isOK == false)
	{
		return text.Trim();//���������ǿ��ı�����ֻ��һ�С�
	}

	//���ע�ͣ���ĩβ��ʼ��ͷ������
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//ȡ "//" �����
		}
	}


	//������У�ע�⣺���ܷ��ڡ����ע�͡���ǰ�棬��Ϊ�п������ע�ͺ����б�ɿյģ�
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}

	//���ɹ淶�����ı�
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
