#include "stdafx.h"
#include "User.h"
#include "EncodeMD5.h"

User::User()
{
	//后去程序运行路径
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
	//读取数据
	CString src = ef.ReadCString(basePath + L"UserConfig.sdonc");

#pragma region 处理读进来的字符串
	CStringArray rows;
	CString temp;

	et.DivideText(src, L"\r\n", rows);//以换行符来分割字符串

	//清除注释（从末尾开始往头遍历）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//取 // 的左边并且删除字符串首尾的空格。
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


	//调试输出一下读取到的文本
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"读入用户数据共：" + str + L"条。\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

	userData.Copy(rows);
	return true;
}

bool User::SaveUserData()
{
	CString str = L"//请不要擅自修改本文件的内容，否则将会导致读取数据异常！";
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

	bool isUserIDExist = false;//用户名是否存在
	CString hash = GetHash(userID, userID);
	EasyText et;

	//检查用户名是否存在重复
	for (int i = 0; i < userData.GetCount(); i++)
	{
		if (hash == et.Left(userData.GetAt(i), L","))
		{
			isUserIDExist = true;//用户名已存在
			break;
		}
	}
	if (isUserIDExist == false)
	{
		//写入数据
		userData.Add(hash + L"," + GetHash(userID, password));
		SaveUserData();
		return true;
	}
	return false;
}

CString User::GetHash(CString userID, CString password)
{
	EncodeMD5 md5;

	//加密算法如下
	// md5 ( md5(userID+salt) + md5(password+salt1) + md5(userID + password) + "RPG游戏剧情编辑器，作者：sdonc")

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


	temp4 = temp1 + temp2 + temp3 + L"RPG游戏剧情编辑器，作者：sdonc";

	string text4(CW2A(temp4.GetBuffer()));
	md5.update(text4);
	temp4.ReleaseBuffer();
	temp4 = md5.toString().c_str();

	return temp4;
}
