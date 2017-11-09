#pragma once
#include "ImageLoader.h"
#include "User.h"
#include "GameMap.h"
#include "TriggerLoader.h"
#define MY_NEWMAP WM_USER+8			//自定义消息（新建地图）：新建地图窗口→主窗体
#define MY_LOADMAP WM_USER+9		//自定义消息（打开地图）：打开题图窗口→主窗体

#define MY_CHOOES_CHANGE WM_USER+10	//自定义消息（用户选择了另一个物体）：主窗体→触发编辑器
#define MY_TRIGGER_CHANGE WM_USER+11	//自定义消息（触发编辑器修改了数据）：触发编辑器→主窗体


class GV
{
#pragma region 单例设计模式
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
	//加载图片资源
	void LoadImageSrc();

	//加载用户数据
	void LoadUserData();

	//加载已存在的地图
	void LoadAllMap();

	//图片加载器
	ImageLoader *imageLoader;

	//用户数据
	User user;

	//用来判断用户是否已经登录
	bool isLogin;

	//已经存在的地图
	CStringArray mapFiles;

	//游戏地图信息
	GameMap gameMap;

	//触发器加载器
	TriggerLoader triggerLoader;

	//当前是否选中元素
	bool nowIsChooesElement;

	//当前选中元素触发器脚本
	CString nowChooesElementTriggerScript;

	//当前选中元素摘要（用于触发编辑器的显示）
	CString nowChooesElementInfo;

	//当前触发器编辑器是否显示
	bool isTriggerEditorShow;
};



/*
触发器类型

触发条件		备注							执行动作
OnEnterStart	//用户即将进入
OnEnterEnd		//用户完全进入

动作列表（每个动作都有一个ActionTag，方便处理）
SetPosition(#param1,#param2)		//设置用户位置（参数1，参数2）
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

HPLargerEqual(#param1,#param2)	//用户生命大于等于（参数1,参数2），参数1血量，参数2是执行对应的动作（传入ActionTag）
MPLargerEqual(#param1,#param2)		//用户魔法值大于等于（参数1,参数2）
LevelLargerEqual(#param1,#param2)	//用户等级大于等于（参数1,参数2）
*/