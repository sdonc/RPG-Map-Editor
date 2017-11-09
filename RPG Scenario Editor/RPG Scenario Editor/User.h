#pragma once
class User
{
public:
	User();
	~User();

	//�����û�����
	bool LoadUserData();

	//�����û�����
	bool SaveUserData();

	//����������¼
	//����ֵ����¼�ɹ������棬ʧ�ܷ��ؼ�
	bool Login(CString userID, CString password);

	//��������ע��
	//����ֵ��true = ע��ɹ� ��false = �û����Ѵ���
	bool Register(CString userID, CString password);

private:
	CString basePath;//�����·��
	CStringArray userData;//�洢��ʽ��#param1,#param2��#param1���û�����hashֵ�����Σ���#param2�������hashֵ�����Σ���


	EasyFile ef;
	EasyPath ep;
	EasyText et;

	//����������ȡ���û���+����+�Ρ���Ĺ�ϣֵ
	//����ֵ��ע��ɹ������棬ʧ�ܷ��ؼ�
	CString GetHash(CString userID, CString password);

	const CString salt = L"6	01334 06650 05992 18843 23164 31901 30300 03435 03402 02232\
		7	01729 22362 29276 29728 19173 29972 25343 11271 20490 00096\
		11	29930 31236 06517 19991 22975 21197 02435 24044 07299 31998";

	const CString salt1 = L"33	12191 13514 27186 04976 12993 23903 30404 01541 04195 10648\
		37	25094 01115 09645 18163 14561 29064 11572 22138 24118 13063\
		38	19570 25802 10602 16452 25722 14522 18375 19430 28068 30799";
};

