#include "stdafx.h"
#include "User.h"
#include "EncodeMD5.h"

User::User()
{
	//��ȥ��������·��
	basePath = ep.GetProgramDir();
}


User::~User()
{
}

bool User::LoadUserData()
{
	if (ef.IsFileExist(basePath + L"UserConfig.sdonc") == false)
	{
		ef.CreatFile(basePath + L"UserConfig.sdonc");
	}
	//��ȡ����
	CString src = ef.ReadCString(basePath + L"UserConfig.sdonc");

#pragma region ������������ַ���
	CStringArray rows;
	CString temp;

	et.DivideText(src, L"\r\n", rows);//�Ի��з����ָ��ַ���

	//���ע�ͣ���ĩβ��ʼ��ͷ������
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//ȡ // ����߲���ɾ���ַ�����β�Ŀո�
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


	//�������һ�¶�ȡ�����ı�
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"�����û����ݹ���" + str + L"����\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

	userData.Copy(rows);
	return true;
}

bool User::SaveUserData()
{
	CString str = L"//�벻Ҫ�����޸ı��ļ������ݣ����򽫻ᵼ�¶�ȡ�����쳣��";
	for (int i = 0; i < userData.GetCount(); i++)
	{
		str = str + L"\r\n" + userData.GetAt(i);
	}
	return ef.WriteCString(basePath + L"UserConfig.sdonc", str, true);
}

bool User::Login(CString userID, CString password)
{
	bool isOK = false;
	CString hash = GetHash(userID, password);
	EasyText et;
	for (int i = 0; i < userData.GetCount(); i++)
	{
		if (hash == et.Right(userData.GetAt(i), L","))
		{
			isOK = true;
			break;
		}
	}
	return isOK;
}

bool User::Register(CString userID, CString password)
{

	bool isUserIDExist = false;//�û����Ƿ����
	CString hash = GetHash(userID, userID);
	EasyText et;

	//����û����Ƿ�����ظ�
	for (int i = 0; i < userData.GetCount(); i++)
	{
		if (hash == et.Left(userData.GetAt(i), L","))
		{
			isUserIDExist = true;//�û����Ѵ���
			break;
		}
	}
	if (isUserIDExist == false)
	{
		//д������
		userData.Add(hash + L"," + GetHash(userID, password));
		SaveUserData();
		return true;
	}
	return false;
}

CString User::GetHash(CString userID, CString password)
{
	EncodeMD5 md5;

	//�����㷨����
	// md5 ( md5(userID+salt) + md5(password+salt1) + md5(userID + password) + "RPG��Ϸ����༭�������ߣ�sdonc")

	CString temp1, temp2, temp3, temp4;

	temp1 = userID + salt;
	temp2 = password + salt1;
	temp3 = userID + password;
	string text1(CW2A(temp1.GetBuffer()));
	string text2(CW2A(temp2.GetBuffer()));
	string text3(CW2A(temp3.GetBuffer()));

	md5.update(text1);
	temp1.ReleaseBuffer();
	temp1 = md5.toString().c_str();

	md5.update(text1);
	temp2.ReleaseBuffer();
	temp2 = md5.toString().c_str();

	md5.update(text1);
	temp3.ReleaseBuffer();
	temp3 = md5.toString().c_str();


	temp4 = temp1 + temp2 + temp3 + L"RPG��Ϸ����༭�������ߣ�sdonc";

	string text4(CW2A(temp4.GetBuffer()));
	md5.update(text4);
	temp4.ReleaseBuffer();
	temp4 = md5.toString().c_str();

	return temp4;
}
