#pragma once

///  类名：EasyText（方便的文本操作）
///  描述：本类主要是一些便捷处理文本的方法集合，例如获取文本的左边内容、删除文本前后的空格等。

class EasyText
{
public:
	EasyText();
	~EasyText();

	/*
	函数名：取文本左边
	功能：从源文本(sourceText)中将目标文本(targetText)左边的文本取出来并返回该文本。如果目标文本找不到则返回空字符串。
	参数：
	sourceText						源文本
	targetText						欲寻找文本
	beginIndex	可空(默认 = 0)		起始寻找位置，位置从0开始。如果该参数留空则从0开始。
	ignoreCase	可空(默认 = false)	忽略大小写。true = 忽略大小写。
	示例：Left("123456789abcdefg","56") 返回 1234
	*/
	CString Left(CString sourceText, CString targetText,int beginIndex = 0, bool ignoreCase = false);
	
	/*
	函数名：取文本右边
	功能：从源文本(sourceText)中将目标文本(targetText)右边的文本取出来并返回该文本。如果目标文本找不到则返回空字符串。
	参数：
	sourceText						源文本
	targetText						欲寻找文本
	beginIndex	可空(默认 = 0)		起始寻找位置，位置从0开始。如果该参数留空则从0开始。
	ignoreCase	可空(默认 = false)	忽略大小写。true = 忽略大小写。
	示例：Right("123456789abcdefg","789") 返回 abcdefg
	*/
	CString Right(CString sourceText, CString targetText, int beginIndex = 0, bool ignoreCase = false);
	
	
	/*
	函数名：取文本中间
	功能：从源文本(sourceText)中将左边文本(leftText)和右边文本(rightText)之间的文本取出来并返回该文本。如左边文本和右边文本有一个找不到则返回空字符串。
	参数：
	sourceText						源文本
	leftText						左边文本
	rightText						右边文本
	beginIndex	可空(默认 = 0)		起始寻找位置，位置从0开始。如果该参数留空则从0开始。
	ignoreCase	可空(默认 = false)	忽略大小写。true = 忽略大小写。
	示例：Mid("123456789abcdefg","4","c")  返回 56789ab
	*/
	CString Middle(CString sourceText,CString leftText, CString rightText, int beginIndex = 0,bool ignoreCase=false);


	/*
	函数名：分割文本
	功能：以divedeText来分割sourceText
	参数：
	sourceText						源文本
	divedeText						用来分割的文本
	CStringArray（指针输出）		输出到字符串队列
	ignoreCase	可空(默认 = false)	忽略大小写。true = 忽略大小写。
	返回：分割成功返回真，失败返回假。
	*/
	bool DivideText(CString sourceText, CString divedeText, _Out_ CStringArray & cStringArray, bool ignoreCase = false);
};

