#pragma once

///  ������EasyPth�������·��·��������
///  ���ߣ�sdonc
///  ���ڣ�2017-10-18
///  �汾��1.0
///  ��ַ��www.sdonc.com
///  ��Ȩ����Ȩ��ԭ�������У���Դ�����ѧϰ��ο���ʹ�ñ�Դ��ʱ�뱣������Ȩ������������Ϣ��

class EasyPath
{
public:
	EasyPath();
	~EasyPath();

	/*
	��������ȡ����Ŀ¼
	���أ����ص�ǰ��������ʱ���ڵ�Ŀ¼
	ʾ��������ֵ��F:\VS_Project\MFC\Model\ModelForPRG\Debug\
	*/
	CString GetProgramDir();


	/*
	��������ȡ���г�����
	���أ����ص�ǰ���������
	����1 suffix���ɿգ���������׺����Ĭ��Ϊtrue��
	ʾ��������ֵ��suffix = true����test.exe
		  ����ֵ��suffix = false����test
	*/
	CString GetProgramName(bool suffix=true);

};

