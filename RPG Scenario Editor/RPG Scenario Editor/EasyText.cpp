#include "stdafx.h"
#include "EasyText.h"


EasyText::EasyText()
{
}


EasyText::~EasyText()
{
}

CString EasyText::Left(CString sourceText, CString targetText, int beginIndex, bool ignoreCase)
{
	//异常检查
	if (
		sourceText.IsEmpty() ||								/*源文本不能为空*/
		targetText.IsEmpty() ||								/*欲搜索文本不能为空*/
		sourceText.GetLength() < targetText.GetLength()	||	/*欲搜索文本的长度不能大于源文本*/
		beginIndex < 0 ||									/*起始寻找位置不嫩小于0*/
		beginIndex > (sourceText.GetLength() - targetText.GetLength())/*当起始寻找位置大于 源文本-欲寻找文本 时，不符合逻辑，此时也不可能寻找到该文本*/
		)
		return L"";


	CString temp_sourceText = sourceText;//备份sourceText。使用这个备份的原因：当ignoreCase = true 时会让 sourceText 所有的字符都变成小写的，所以到最后就没法正确输出文本了。

	//处理大小写，如果忽略大小写则转成小写
	if (ignoreCase)
	{
		sourceText.MakeLower();
		targetText.MakeLower();
	}

	//寻找指定文本
	int p = sourceText.Find(targetText, beginIndex);
	if (p == -1)//寻找不到指定文本
		return L"";

	return temp_sourceText.Left(p);
}

CString EasyText::Right(CString sourceText, CString targetText, int beginIndex, bool ignoreCase)
{
	//异常检查
	if (
		sourceText.IsEmpty() ||									/*源文本不能为空*/
		targetText.IsEmpty() ||									/*欲搜索文本不能为空*/
		sourceText.GetLength() < targetText.GetLength() ||		/*欲搜索文本的长度不能大于源文本*/
		beginIndex < 0 ||										/*起始寻找位置不嫩小于0*/
		beginIndex > (sourceText.GetLength() - targetText.GetLength())	/*当起始寻找位置大于 源文本-欲寻找文本 时，不符合逻辑，此时也不可能寻找到该文本*/
		)
		return L"";

	CString temp_sourceText = sourceText;//备份sourceText。使用这个备份的原因：当ignoreCase = true 时会让 sourceText 所有的字符都变成小写的，所以到最后就没法正确输出文本了。

	//处理大小写，如果忽略大小写则转成小写
	if (ignoreCase)
	{
		sourceText.MakeLower();
		targetText.MakeLower();
	}

	//寻找指定文本
	int p = sourceText.Find(targetText, beginIndex);
	if (p == -1)//寻找不到指定文本
		return L"";

	return temp_sourceText.Right(temp_sourceText.GetLength() - p - targetText.GetLength());
}

CString EasyText::Middle(CString sourceText, CString leftText, CString rightText, int beginIndex, bool ignoreCase)
{
	//异常检查
	if (
		sourceText.IsEmpty() ||								/*源文本不能为空*/
		leftText.IsEmpty() ||								/*左边文本不能为空*/
		rightText.IsEmpty() ||								/*右边文本不能为空*/
		sourceText.GetLength() < leftText.GetLength() ||	/*欲搜索文本的长度不能大于左边文本*/
		sourceText.GetLength() < rightText.GetLength() ||	/*欲搜索文本的长度不能大于右边文本*/
		beginIndex < 0 ||									/*起始寻找位置不嫩小于0*/
		beginIndex > (sourceText.GetLength() - leftText.GetLength() - rightText.GetLength())/*不符合逻辑，此时不可能同时寻找到左右两边的文本*/
		)
		return L"";

	CString temp_sourceText = sourceText;//备份sourceText。使用这个备份的原因：当ignoreCase = true 时会让 sourceText 所有的字符都变成小写的，所以到最后就没法正确输出文本了。

	//处理大小写，如果忽略大小写则转成小写
	if (ignoreCase)
	{
		sourceText.MakeLower();
		leftText.MakeLower(); 
		rightText.MakeLower();
	}

	int a;	//记录 左边文本(leftText) 出现的位置
	int b;	//记录 右边文本(rightText) 出现的位置

	//寻找 左边文本
	a = sourceText.Find(leftText, beginIndex);
	if (a == -1)//找不到 左边文本
		return L"";

	//寻找 右边文本
	b = sourceText.Find(rightText, a + leftText.GetLength());
	if (b == -1)//找不到 右边文本
		return L"";

	return temp_sourceText.Mid(a + leftText.GetLength(), b - a - leftText.GetLength());
}


bool EasyText::DivideText(CString sourceText, CString divedeText, CStringArray & cStringArray, bool ignoreCase)
{
	//异常检测
	if (sourceText.IsEmpty() || divedeText.IsEmpty())
	{
		return false;
	}

	//非空的话清除所有的成员
	if (cStringArray.IsEmpty() == false)
	{
		cStringArray.RemoveAll();
	}

	CString temp_sourceText = sourceText;//备份源文本
	if (ignoreCase)
	{
		sourceText.MakeLower();
		divedeText.MakeLower();
	}

	int left = 0;//左边
	int right = 0;//右边
	int count = 0;//字符串数

	while (left<sourceText.GetLength())
	{
		left = right;
		right = sourceText.Find(divedeText, right + divedeText.GetLength());

		if (right == -1)
			break;
		else
		{
			count++;
			if (left == 0)//第一个
				cStringArray.Add(temp_sourceText.Mid(0, right));
			else
				cStringArray.Add(temp_sourceText.Mid(left + divedeText.GetLength(), right - left - divedeText.GetLength()));
		}
	}

	if (count == 0)//分割失败
		return false;
	else//把最后一串文本加进来
		cStringArray.Add(temp_sourceText.Right(temp_sourceText.GetLength() - left - divedeText.GetLength()));

	return true;

}