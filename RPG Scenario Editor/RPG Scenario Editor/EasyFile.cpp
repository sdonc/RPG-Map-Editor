#include "stdafx.h"
#include "EasyFile.h"


EasyFile::EasyFile()
{

}


EasyFile::~EasyFile()
{
}

bool EasyFile::CreatFile(CString path, bool mandatory)
{
	if (path == "")//Ŀ¼����Ϊ��
		return false;
	if (mandatory == false)
	{
		if (IsFileExist(path))
			return false;
	}

	if (file.Open(path, CFile::modeCreate))
	{
		file.Close();//����ļ�ռ��
		return true;
	}
	else
	{
		return false;
	}
}

bool EasyFile::RemoveFile(CString path)
{
	if (IsFileExist(path) == false)
		return false;

	file.Remove(path);

	return false;
}

bool EasyFile::WriteCString(CString path, CString content, bool mandatory)
{
	if (path == "")//Ŀ¼����Ϊ��
		return false;

	if (mandatory)
	{
		if (IsFileExist(path) == false)
		{
			CreatFile(path, true);
		}
	}


	if (!IsFileExist(path))//�ļ�������
	{
		if (file.Open(path, CFile::modeCreate) == false)
			return false;
		file.Close();
	}

	file.Open(path, CFile::modeWrite);


	file.Write(content, content.GetLength() * 2);//���ַ���ÿ������ռ�������ֽ�

	file.Close();//����ļ�ռ��

	return true;
}

bool EasyFile::IsFileExist(CString path)
{
	//�ο��ԣ�http://www.cnblogs.com/lujin49/p/5034797.html
	//�ļ���Ŀ¼�����ж�
	if (-1 != GetFileAttributes(path)) //����ļ��д��ڣ� ����\\�����޶�û��ϵ
	{
		return true;
	}
	else
	{

		return false;
	}


	//���ж��ļ������ж�Ŀ¼
	//if (file.Open(path, CFile::modeRead))
	//{
	//	file.Close();//����ļ�ռ��
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}


CString EasyFile::ReadCString(CString path, CString defaultContent)
{
	if (IsFileExist(path) == false)//�ļ������ڷ���Ĭ���ı�
		return defaultContent;

	file.Open(path, CFile::modeRead);
	
	wchar_t *buf = new wchar_t[(unsigned int)file.GetLength() / 2 + 1];
	buf[file.GetLength() / 2] = 0;//0��ֹ�ַ��������������

	file.Read(buf, (unsigned int)file.GetLength());
	CString str(buf);
	file.Close();
	return str;

}

bool EasyFile::Select(CString path)
{
	//���� (��explorer /n,/select,�� �� #���� �� ���ı��滻 (�ļ�·��, ��\\��, ��\��, , , ��) �� #����, ��, )

	if (IsFileExist(path) == false)
	{
		return false;
	}

	CString str1, str2;
	str1 = L"explorer /n,/select,";
	str2 = L"\"";
	path.Replace(L"//", L"\\");//��ʽ���ı�
	path.Replace(L"/", L"\\");
	str1 = str1 + str2 + path + str2;

	ShellExecute(NULL, L"open", L"explorer", (LPCWSTR)str1, NULL, SW_SHOW);
	return true;
}


int EasyFile::EnumFile(CString path, CStringArray & files, CString type, bool fullPath)
{
	//���files
	files.RemoveAll();

	//���Ŀ¼�Ƿ����
	if (path.GetLength() == 0)
		return 0;

	if (path.GetAt(path.GetLength() - 1) == '\\' && path.GetAt(path.GetLength() - 2) != ':')
	{
		//��������ĩβ���С�\��������Ǹ���ȥ��
		path = path.Left(path.GetLength() - 1);
	}


	//���������
	type = L"*." + type;

	CFileFind finder;

	BOOL bWorking = finder.FindFile(path + L"\\" + type);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		files.Add(finder.GetFileName());
	}

	//�Ƴ����������Ŀ¼
	for (int i = files.GetCount() - 1; i >= 0; i--)
	{
		if (files.GetAt(i) == L"." || files.GetAt(i) == L"..")
			files.RemoveAt(i);
	}

	if (fullPath)
	{
		for (int i = 0; i < files.GetCount(); i++)
		{
			files.SetAt(i, path + L"\\" + files.GetAt(i));
		}
	}

	finder.Close();
	return files.GetCount();
}
