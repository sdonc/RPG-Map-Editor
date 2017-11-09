#pragma once


///  ������EasyFile��������ļ�������


class EasyFile
{
public:
	EasyFile();
	~EasyFile();

	/*
	���������½��ļ�
	����1 path(����)�����������ļ�������·��
	����1 mandatory(�ɿ�)��Ĭ��Ϊ�١�ǿ�ƴ�����������������ļ��Ѿ����ڣ���ɾ���ļ�Ȼ���½�һ���յ��ļ���
	���أ������ɹ������棬ʧ�ܷ��ؼ�
	*/
	bool CreatFile(CString path, bool mandatory = false);


	/*
	��������ɾ���ļ�
	����1 path(����)�����������ļ�������·��
	���أ�ɾ���ɹ������棬ʧ�ܷ��ؼ�
	*/
	bool RemoveFile(CString path);


	/*
	��������д���ļ��ַ���
	����1 path(����)����д���ļ�������·��
	����2 content(�ɿ�)����д���ļ�������
	����2 mandatory(�ɿ�)��Ĭ��Ϊ�١�ǿ��д��
	���أ��ɹ�д�뷵���棬ʧ�ܷ��ؼ�
	*/
	bool WriteCString(CString path, CString content , bool mandatory=false);


	/*
	���������ļ��Ƿ����
	���� path(���ɿ�)�����жϵ��ļ�·��
	���أ��ļ����ڷ����棬�����ڷ��ؼ�
	*/
	bool IsFileExist(CString path);

	/*
	��������д���ļ��ַ���
	����1 path(����)������ȡ�ļ���·��
	����2 defaultContent(�ɿ�)��Ĭ���ı������ָ���ļ������ڣ�����Ĭ�ϵ��ı�������Ĭ�Ϸ��ؿ��ַ�����
	���أ���ȡ�ɹ�����ָ���ļ����ַ�����ʧ�ܷ��ؿ��ַ���
	��ע�������������������Կ��ַ�(wchar_t)����ȡ��
	*/
	CString ReadCString(CString path, CString defaultContent=NULL);


	/*
	���������ļ���λ
	����1 path(����)������λ���ļ�
	���أ��ɹ������棬ʧ�ܷ��ؼ١�
	���ܣ�����Դ��������ѡ���Ǹ��ļ�
	*/
	bool Select(CString path);


	/*
	��������ö���ļ���������������Ŀ¼������
	����1 path(����)����ö�ٵ��ļ���
	����2 files(����)����ö�ٵ����ļ�·������
	����3 type(�ɿ�)��ö�ٵ��ļ����ͣ�Ĭ��Ϊö�������ļ���ʾ����L"jpg"��L"map"
	����4 fullPath(�ɿ�)���Ƿ񷵻�ȫ·������Ϊtrueʱ��
	���أ�����ö�ٵ��ļ��ĸ�����
	*/
	int EnumFile(CString path, CStringArray & files, CString type = L"*", bool fullPath = false);


private:
	CFile file;
};

