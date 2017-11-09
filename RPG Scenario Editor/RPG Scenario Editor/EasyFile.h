#pragma once


///  类名：EasyFile（方便的文件操作）


class EasyFile
{
public:
	EasyFile();
	~EasyFile();

	/*
	函数名：新建文件
	参数1 path(必须)：欲创建的文件的完整路径
	参数1 mandatory(可空)：默认为假。强制创建：如果欲创建的文件已经存在，则删除文件然后新建一个空的文件。
	返回：创建成功返回真，失败返回假
	*/
	bool CreatFile(CString path, bool mandatory = false);


	/*
	函数名：删除文件
	参数1 path(必须)：欲创建的文件的完整路径
	返回：删除成功返回真，失败返回假
	*/
	bool RemoveFile(CString path);


	/*
	函数名：写入文件字符串
	参数1 path(必须)：欲写入文件的完整路径
	参数2 content(可空)：欲写入文件的内容
	参数2 mandatory(可空)：默认为假。强制写入
	返回：成功写入返回真，失败返回假
	*/
	bool WriteCString(CString path, CString content , bool mandatory=false);


	/*
	函数名：文件是否存在
	参数 path(不可空)：欲判断的文件路径
	返回：文件存在返回真，不存在返回假
	*/
	bool IsFileExist(CString path);

	/*
	函数名：写入文件字符串
	参数1 path(必须)：欲读取文件的路径
	参数2 defaultContent(可空)：默认文本。如果指定文件不存在，返回默认的文本。留空默认返回空字符串。
	返回：读取成功返回指定文件的字符串，失败返回空字符串
	备注：本函数将所有内容以宽字符(wchar_t)来读取。
	*/
	CString ReadCString(CString path, CString defaultContent=NULL);


	/*
	函数名：文件定位
	参数1 path(必须)：欲定位的文件
	返回：成功返回真，失败返回假。
	功能：打开资源管理器并选中那个文件
	*/
	bool Select(CString path);


	/*
	函数名：枚举文件（不进行所有子目录遍历）
	参数1 path(必须)：欲枚举的文件夹
	参数2 files(必须)：将枚举到的文件路径返回
	参数3 type(可空)：枚举的文件类型，默认为枚举所有文件。示例：L"jpg"，L"map"
	参数4 fullPath(可空)：是否返回全路径，当为true时候，
	返回：返回枚举到文件的个数。
	*/
	int EnumFile(CString path, CStringArray & files, CString type = L"*", bool fullPath = false);


private:
	CFile file;
};

