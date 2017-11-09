#pragma once

///  ������EasyText��������ı�������
///  ������������Ҫ��һЩ��ݴ����ı��ķ������ϣ������ȡ�ı���������ݡ�ɾ���ı�ǰ��Ŀո�ȡ�

class EasyText
{
public:
	EasyText();
	~EasyText();

	/*
	��������ȡ�ı����
	���ܣ���Դ�ı�(sourceText)�н�Ŀ���ı�(targetText)��ߵ��ı�ȡ���������ظ��ı������Ŀ���ı��Ҳ����򷵻ؿ��ַ�����
	������
	sourceText						Դ�ı�
	targetText						��Ѱ���ı�
	beginIndex	�ɿ�(Ĭ�� = 0)		��ʼѰ��λ�ã�λ�ô�0��ʼ������ò����������0��ʼ��
	ignoreCase	�ɿ�(Ĭ�� = false)	���Դ�Сд��true = ���Դ�Сд��
	ʾ����Left("123456789abcdefg","56") ���� 1234
	*/
	CString Left(CString sourceText, CString targetText,int beginIndex = 0, bool ignoreCase = false);
	
	/*
	��������ȡ�ı��ұ�
	���ܣ���Դ�ı�(sourceText)�н�Ŀ���ı�(targetText)�ұߵ��ı�ȡ���������ظ��ı������Ŀ���ı��Ҳ����򷵻ؿ��ַ�����
	������
	sourceText						Դ�ı�
	targetText						��Ѱ���ı�
	beginIndex	�ɿ�(Ĭ�� = 0)		��ʼѰ��λ�ã�λ�ô�0��ʼ������ò����������0��ʼ��
	ignoreCase	�ɿ�(Ĭ�� = false)	���Դ�Сд��true = ���Դ�Сд��
	ʾ����Right("123456789abcdefg","789") ���� abcdefg
	*/
	CString Right(CString sourceText, CString targetText, int beginIndex = 0, bool ignoreCase = false);
	
	
	/*
	��������ȡ�ı��м�
	���ܣ���Դ�ı�(sourceText)�н�����ı�(leftText)���ұ��ı�(rightText)֮����ı�ȡ���������ظ��ı���������ı����ұ��ı���һ���Ҳ����򷵻ؿ��ַ�����
	������
	sourceText						Դ�ı�
	leftText						����ı�
	rightText						�ұ��ı�
	beginIndex	�ɿ�(Ĭ�� = 0)		��ʼѰ��λ�ã�λ�ô�0��ʼ������ò����������0��ʼ��
	ignoreCase	�ɿ�(Ĭ�� = false)	���Դ�Сд��true = ���Դ�Сд��
	ʾ����Mid("123456789abcdefg","4","c")  ���� 56789ab
	*/
	CString Middle(CString sourceText,CString leftText, CString rightText, int beginIndex = 0,bool ignoreCase=false);


	/*
	���������ָ��ı�
	���ܣ���divedeText���ָ�sourceText
	������
	sourceText						Դ�ı�
	divedeText						�����ָ���ı�
	CStringArray��ָ�������		������ַ�������
	ignoreCase	�ɿ�(Ĭ�� = false)	���Դ�Сд��true = ���Դ�Сд��
	���أ��ָ�ɹ������棬ʧ�ܷ��ؼ١�
	*/
	bool DivideText(CString sourceText, CString divedeText, _Out_ CStringArray & cStringArray, bool ignoreCase = false);
};

