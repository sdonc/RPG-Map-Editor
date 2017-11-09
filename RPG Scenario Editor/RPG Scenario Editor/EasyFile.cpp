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
	if (path == "")//目录不能为空
		return false;
	if (mandatory == false)
	{
		if (IsFileExist(path))
			return false;
	}

	if (file.Open(path, CFile::modeCreate))
	{
		file.Close();//解除文件占用
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
	if (path == "")//目录不能为空
		return false;

	if (mandatory)
	{
		if (IsFileExist(path) == false)
		{
			CreatFile(path, true);
		}
	}


	if (!IsFileExist(path))//文件不存在
	{
		if (file.Open(path, CFile::modeCreate) == false)
			return false;
		file.Close();
	}

	file.Open(path, CFile::modeWrite);


	file.Write(content, content.GetLength() * 2);//宽字符，每个文字占用两个字节

	file.Close();//解除文件占用

	return true;
}

bool EasyFile::IsFileExist(CString path)
{
	//参考自：http://www.cnblogs.com/lujin49/p/5034797.html
	//文件和目录都能判断
	if (-1 != GetFileAttributes(path)) //如果文件夹存在， 最后的\\号有无都没关系
	{
		return true;
	}
	else
	{

		return false;
	}


	//仅判断文件不能判断目录
	//if (file.Open(path, CFile::modeRead))
	//{
	//	file.Close();//解除文件占用
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}


CString EasyFile::ReadCString(CString path, CString defaultContent)
{
	if (IsFileExist(path) == false)//文件不存在返回默认文本
		return defaultContent;

	file.Open(path, CFile::modeRead);
	
	wchar_t *buf = new wchar_t[(unsigned int)file.GetLength() / 2 + 1];
	buf[file.GetLength() / 2] = 0;//0终止字符串，用于输出。

	file.Read(buf, (unsigned int)file.GetLength());
	CString str(buf);
	file.Close();
	return str;

}

bool EasyFile::Select(CString path)
{
	//运行 (“explorer /n,/select,” ＋ #引号 ＋ 子文本替换 (文件路径, “\\”, “\”, , , 真) ＋ #引号, 假, )

	if (IsFileExist(path) == false)
	{
		return false;
	}

	CString str1, str2;
	str1 = L"explorer /n,/select,";
	str2 = L"\"";
	path.Replace(L"//", L"\\");//格式化文本
	path.Replace(L"/", L"\\");
	str1 = str1 + str2 + path + str2;

	ShellExecute(NULL, L"open", L"explorer", (LPCWSTR)str1, NULL, SW_SHOW);
	return true;
}


int EasyFile::EnumFile(CString path, CStringArray & files, CString type, bool fullPath)
{
	//清除files
	files.RemoveAll();

	//检查目录是否存在
	if (path.GetLength() == 0)
		return 0;

	if (path.GetAt(path.GetLength() - 1) == '\\' && path.GetAt(path.GetLength() - 2) != ':')
	{
		//如果传入的末尾带有“\“，则把那个线去掉
		path = path.Left(path.GetLength() - 1);
	}


	//补齐过滤器
	type = L"*." + type;

	CFileFind finder;

	BOOL bWorking = finder.FindFile(path + L"\\" + type);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		files.Add(finder.GetFileName());
	}

	//移除两个特殊的目录
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
