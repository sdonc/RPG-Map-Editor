#pragma once
#include "ImageLoader.h"
#include "User.h"
#include "GameMap.h"
#include "TriggerLoader.h"
#define MY_NEWMAP WM_USER+8			//�Զ�����Ϣ���½���ͼ�����½���ͼ���ڡ�������
#define MY_LOADMAP WM_USER+9		//�Զ�����Ϣ���򿪵�ͼ��������ͼ���ڡ�������

#define MY_CHOOES_CHANGE WM_USER+10	//�Զ�����Ϣ���û�ѡ������һ�����壩��������������༭��
#define MY_TRIGGER_CHANGE WM_USER+11	//�Զ�����Ϣ�������༭���޸������ݣ��������༭����������


class GV
{
#pragma region �������ģʽ
private:
	GV();
	~GV();
	static GV* gv;
public:
	static GV* GetInstance()
	{
		if (gv == NULL)
		{
			gv = new GV();

		}
		return gv;
	}

#pragma endregion



public:
	//����ͼƬ��Դ
	void LoadImageSrc();

	//�����û�����
	void LoadUserData();

	//�����Ѵ��ڵĵ�ͼ
	void LoadAllMap();

	//ͼƬ������
	ImageLoader *imageLoader;

	//�û�����
	User user;

	//�����ж��û��Ƿ��Ѿ���¼
	bool isLogin;

	//�Ѿ����ڵĵ�ͼ
	CStringArray mapFiles;

	//��Ϸ��ͼ��Ϣ
	GameMap gameMap;

	//������������
	TriggerLoader triggerLoader;

	//��ǰ�Ƿ�ѡ��Ԫ��
	bool nowIsChooesElement;

	//��ǰѡ��Ԫ�ش������ű�
	CString nowChooesElementTriggerScript;

	//��ǰѡ��Ԫ��ժҪ�����ڴ����༭������ʾ��
	CString nowChooesElementInfo;

	//��ǰ�������༭���Ƿ���ʾ
	bool isTriggerEditorShow;
};



/*
����������

��������		��ע							ִ�ж���
OnEnterStart	//�û���������
OnEnterEnd		//�û���ȫ����

�����б�ÿ����������һ��ActionTag�����㴦��
SetPosition(#param1,#param2)		//�����û�λ�ã�����1������2��
SubHP(#param1)
AddHP(#param1)
SetHP(#param1)

SubMP(#param1)
AddMP(#param1)
SetMP(#param1)

SubLevel(#param1)
AddLevel(#param1)
SetLevel(#param1)

ShowText()

HPLargerEqual(#param1,#param2)	//�û��������ڵ��ڣ�����1,����2��������1Ѫ��������2��ִ�ж�Ӧ�Ķ���������ActionTag��
MPLargerEqual(#param1,#param2)		//�û�ħ��ֵ���ڵ��ڣ�����1,����2��
LevelLargerEqual(#param1,#param2)	//�û��ȼ����ڵ��ڣ�����1,����2��
*/