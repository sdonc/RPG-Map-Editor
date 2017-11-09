#pragma once
#include "EncodeMD5.h"

struct GameMapElement
{
	int index;//��ţ�����ɾ�����޸Ĳ�����
	CString id;	//Ԫ��ID
	CString type;	//Ԫ������
	int x, y;//Ԫ���ڵ�ͼ�ϵ�x��y����
	int w, h;//Ԫ�صĿ�͸�
	CString params;//���Ӳ���
};

class GameMap
{
public:
	GameMap();
	~GameMap();

	//���õ�ͼ��·��
	void SetPath(CString path);

	//���õ�ͼ�߶�
	void SetMapHeigth(int mapHeight);

	//���õ�ͼ���
	void SetMapWidth(int mapWeigth);

	//���õ�ͼ��
	void SetMapName(CString mapName);

	//ȡ��ͼ�߶�
	int GetMapHeigth();

	//ȡ��ͼ���
	int GetMapWidth();

	//ȡ��ͼ��
	CString GetMapName();

	//�½���ͼ����Ҫ�ȵ���SetPath()������·����
	void CreatMap(CString name = L"δ����",int hp = 100,int mp=100,int Level = 1);

	//������Ϸ��ͼ
	void LoadGameMap();
	
	//������Ϸ��ͼ
	void SaveGameMap();

	//����Ԫ�ز��������
	int AddElement(CString id, CString type, int x,int y, int w, int h, CString params);

	//����Ԫ��x����
	void SetElementX(int index, int x);

	//��ȡԪ��X����
	int GetElementX(int index);

	//����Ԫ��y����
	void SetElementY(int index, int y);

	//��ȡԪ��Y����
	int GetElementY(int index);

	//����Ԫ�ظ��Ӳ���������ò���Tag���������Զ���Ӳ���
	void SetElementParam(int index, CString paramTag, CString paramValue);

	//��ȡԪ�ظ��Ӳ���
	CString GetElementParam(int index, CString paramTag);

	//ɾ��Ԫ�صĸ��Ӳ���������Tag���ɣ�
	void RemoveElementParam(int index, CString paramTag);

	//�Ƴ�Ԫ��
	void RemoveElement(int index);


	//ע��Ϊ�˷����ͼ������û�аѸú�����װ����
	CArray<GameMapElement> gameMapElements;

	
	void SetHP(int hp);
	void SetMP(int mp);
	void SetLevel(int level);
	void SetUserName(CString name);

	int GetHP();
	int GetMP();
	int GetLevel();
	CString GetGameUserName();

private:
	int nowIndex;//��ǰ��ţ����ڱ�־��Ⱦ˳��

	const CString salt = L"6	01334 06650 05992 18843 23164 31901 30300 03435 03402 02232\
		7	01729 22362 29276 29728 19173 29972 25343 11271 20490 00096\
		11	29930 31236 06517 19991 22975 21197 02435 24044 07299";

	CString path;
	int mapHeight;//��ͼ�߶�
	int mapWidth;//��ͼ���
	CString mapName;//��ͼ��

	int gameUserHP;		//��ʼ״̬���û�Ѫ��
	int gameUserMP;		//��ʼ״̬���û�����
	int gameUserLevel;	//��ʼ״̬���û��ȼ�
	CString gameUserName;	//��ʼ״̬���û�����
};

