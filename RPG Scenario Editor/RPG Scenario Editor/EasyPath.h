#pragma once

///  类名：EasyPth（方便的路径路径操作）
///  作者：sdonc
///  日期：2017-10-18
///  版本：1.0
///  网址：www.sdonc.com
///  版权：版权归原作者所有，此源码仅供学习与参考，使用本源码时请保留本版权声明和作者信息。

class EasyPath
{
public:
	EasyPath();
	~EasyPath();

	/*
	函数名：取运行目录
	返回：返回当前程序运行时所在的目录
	示例：返回值：F:\VS_Project\MFC\Model\ModelForPRG\Debug\
	*/
	CString GetProgramDir();


	/*
	函数名：取运行程序名
	返回：返回当前程序的名称
	参数1 suffix（可空）：包含后缀名。默认为true。
	示例：返回值（suffix = true）：test.exe
		  返回值（suffix = false）：test
	*/
	CString GetProgramName(bool suffix=true);

};

