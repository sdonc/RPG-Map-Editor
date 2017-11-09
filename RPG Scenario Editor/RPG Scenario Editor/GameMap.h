#pragma once
#include "EncodeMD5.h"

struct GameMapElement
{
	int index;//序号（便于删除和修改操作）
	CString id;	//元素ID
	CString type;	//元素类型
	int x, y;//元素在地图上的x和y坐标
	int w, h;//元素的宽和高
	CString params;//附加参数
};

class GameMap
{
public:
	GameMap();
	~GameMap();

	//设置地图的路径
	void SetPath(CString path);

	//设置地图高度
	void SetMapHeigth(int mapHeight);

	//设置地图宽度
	void SetMapWidth(int mapWeigth);

	//设置地图名
	void SetMapName(CString mapName);

	//取地图高度
	int GetMapHeigth();

	//取地图宽度
	int GetMapWidth();

	//取地图名
	CString GetMapName();

	//新建地图（需要先调用SetPath()来设置路径）
	void CreatMap(CString name = L"未命名",int hp = 100,int mp=100,int Level = 1);

	//加载游戏地图
	void LoadGameMap();
	
	//保存游戏地图
	void SaveGameMap();

	//加入元素并返回序号
	int AddElement(CString id, CString type, int x,int y, int w, int h, CString params);

	//设置元素x坐标
	void SetElementX(int index, int x);

	//获取元素X坐标
	int GetElementX(int index);

	//设置元素y坐标
	void SetElementY(int index, int y);

	//获取元素Y坐标
	int GetElementY(int index);

	//设置元素附加参数，如果该参数Tag不存在则自动添加参数
	void SetElementParam(int index, CString paramTag, CString paramValue);

	//获取元素附加参数
	CString GetElementParam(int index, CString paramTag);

	//删除元素的附加参数（传入Tag即可）
	void RemoveElementParam(int index, CString paramTag);

	//移除元素
	void RemoveElement(int index);


	//注：为了方便绘图，所以没有把该函数封装起来
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
	int nowIndex;//当前序号（用于标志渲染顺序）

	const CString salt = L"6	01334 06650 05992 18843 23164 31901 30300 03435 03402 02232\
		7	01729 22362 29276 29728 19173 29972 25343 11271 20490 00096\
		11	29930 31236 06517 19991 22975 21197 02435 24044 07299";

	CString path;
	int mapHeight;//地图高度
	int mapWidth;//地图宽度
	CString mapName;//地图名

	int gameUserHP;		//初始状态的用户血量
	int gameUserMP;		//初始状态的用户蓝量
	int gameUserLevel;	//初始状态的用户等级
	CString gameUserName;	//初始状态的用户名称
};

