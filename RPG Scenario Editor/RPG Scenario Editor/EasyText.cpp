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
	//�쳣���
	if (
		sourceText.IsEmpty() ||								/*Դ�ı�����Ϊ��*/
		targetText.IsEmpty() ||								/*�������ı�����Ϊ��*/
		sourceText.GetLength() < targetText.GetLength()	||	/*�������ı��ĳ��Ȳ��ܴ���Դ�ı�*/
		beginIndex < 0 ||									/*��ʼѰ��λ�ò���С��0*/
		beginIndex > (sourceText.GetLength() - targetText.GetLength())/*����ʼѰ��λ�ô��� Դ�ı�-��Ѱ���ı� ʱ���������߼�����ʱҲ������Ѱ�ҵ����ı�*/
		)
		return L"";


	CString temp_sourceText = sourceText;//����sourceText��ʹ��������ݵ�ԭ�򣺵�ignoreCase = true ʱ���� sourceText ���е��ַ������Сд�ģ����Ե�����û����ȷ����ı��ˡ�

	//�����Сд��������Դ�Сд��ת��Сд
	if (ignoreCase)
	{
		sourceText.MakeLower();
		targetText.MakeLower();
	}

	//Ѱ��ָ���ı�
	int p = sourceText.Find(targetText, beginIndex);
	if (p == -1)//Ѱ�Ҳ���ָ���ı�
		return L"";

	return temp_sourceText.Left(p);
}

CString EasyText::Right(CString sourceText, CString targetText, int beginIndex, bool ignoreCase)
{
	//�쳣���
	if (
		sourceText.IsEmpty() ||									/*Դ�ı�����Ϊ��*/
		targetText.IsEmpty() ||									/*�������ı�����Ϊ��*/
		sourceText.GetLength() < targetText.GetLength() ||		/*�������ı��ĳ��Ȳ��ܴ���Դ�ı�*/
		beginIndex < 0 ||										/*��ʼѰ��λ�ò���С��0*/
		beginIndex > (sourceText.GetLength() - targetText.GetLength())	/*����ʼѰ��λ�ô��� Դ�ı�-��Ѱ���ı� ʱ���������߼�����ʱҲ������Ѱ�ҵ����ı�*/
		)
		return L"";

	CString temp_sourceText = sourceText;//����sourceText��ʹ��������ݵ�ԭ�򣺵�ignoreCase = true ʱ���� sourceText ���е��ַ������Сд�ģ����Ե�����û����ȷ����ı��ˡ�

	//�����Сд��������Դ�Сд��ת��Сд
	if (ignoreCase)
	{
		sourceText.MakeLower();
		targetText.MakeLower();
	}

	//Ѱ��ָ���ı�
	int p = sourceText.Find(targetText, beginIndex);
	if (p == -1)//Ѱ�Ҳ���ָ���ı�
		return L"";

	return temp_sourceText.Right(temp_sourceText.GetLength() - p - targetText.GetLength());
}

CString EasyText::Middle(CString sourceText, CString leftText, CString rightText, int beginIndex, bool ignoreCase)
{
	//�쳣���
	if (
		sourceText.IsEmpty() ||								/*Դ�ı�����Ϊ��*/
		leftText.IsEmpty() ||								/*����ı�����Ϊ��*/
		rightText.IsEmpty() ||								/*�ұ��ı�����Ϊ��*/
		sourceText.GetLength() < leftText.GetLength() ||	/*�������ı��ĳ��Ȳ��ܴ�������ı�*/
		sourceText.GetLength() < rightText.GetLength() ||	/*�������ı��ĳ��Ȳ��ܴ����ұ��ı�*/
		beginIndex < 0 ||									/*��ʼѰ��λ�ò���С��0*/
		beginIndex > (sourceText.GetLength() - leftText.GetLength() - rightText.GetLength())/*�������߼�����ʱ������ͬʱѰ�ҵ��������ߵ��ı�*/
		)
		return L"";

	CString temp_sourceText = sourceText;//����sourceText��ʹ��������ݵ�ԭ�򣺵�ignoreCase = true ʱ���� sourceText ���е��ַ������Сд�ģ����Ե�����û����ȷ����ı��ˡ�

	//�����Сд��������Դ�Сд��ת��Сд
	if (ignoreCase)
	{
		sourceText.MakeLower();
		leftText.MakeLower(); 
		rightText.MakeLower();
	}

	int a;	//��¼ ����ı�(leftText) ���ֵ�λ��
	int b;	//��¼ �ұ��ı�(rightText) ���ֵ�λ��

	//Ѱ�� ����ı�
	a = sourceText.Find(leftText, beginIndex);
	if (a == -1)//�Ҳ��� ����ı�
		return L"";

	//Ѱ�� �ұ��ı�
	b = sourceText.Find(rightText, a + leftText.GetLength());
	if (b == -1)//�Ҳ��� �ұ��ı�
		return L"";

	return temp_sourceText.Mid(a + leftText.GetLength(), b - a - leftText.GetLength());
}


bool EasyText::DivideText(CString sourceText, CString divedeText, CStringArray & cStringArray, bool ignoreCase)
{
	//�쳣���
	if (sourceText.IsEmpty() || divedeText.IsEmpty())
	{
		return false;
	}

	//�ǿյĻ�������еĳ�Ա
	if (cStringArray.IsEmpty() == false)
	{
		cStringArray.RemoveAll();
	}

	CString temp_sourceText = sourceText;//����Դ�ı�
	if (ignoreCase)
	{
		sourceText.MakeLower();
		divedeText.MakeLower();
	}

	int left = 0;//���
	int right = 0;//�ұ�
	int count = 0;//�ַ�����

	while (left<sourceText.GetLength())
	{
		left = right;
		right = sourceText.Find(divedeText, right + divedeText.GetLength());

		if (right == -1)
			break;
		else
		{
			count++;
			if (left == 0)//��һ��
				cStringArray.Add(temp_sourceText.Mid(0, right));
			else
				cStringArray.Add(temp_sourceText.Mid(left + divedeText.GetLength(), right - left - divedeText.GetLength()));
		}
	}

	if (count == 0)//�ָ�ʧ��
		return false;
	else//�����һ���ı��ӽ���
		cStringArray.Add(temp_sourceText.Right(temp_sourceText.GetLength() - left - divedeText.GetLength()));

	return true;

}