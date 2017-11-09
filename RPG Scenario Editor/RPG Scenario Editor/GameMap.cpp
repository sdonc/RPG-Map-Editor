#include "stdafx.h"
#include "GameMap.h"


GameMap::GameMap()
{
	
}


GameMap::~GameMap()
{
}

void GameMap::SetPath(CString path)
{
	this->path = path;
}

void GameMap::SetMapHeigth(int mapHeight)
{
	this->mapHeight = mapHeight;
}

void GameMap::SetMapWidth(int mapWeigth)
{
	this->mapWidth = mapWeigth;
}

void GameMap::SetMapName(CString mapName)
{
	this->mapName = mapName;
}

int GameMap::GetMapHeigth()
{
	return mapHeight;
}

int GameMap::GetMapWidth()
{
	return mapWidth;
}



CString GameMap::GetMapName()
{
	return mapName;
}

void GameMap::CreatMap(CString name, int hp, int mp, int Level)
{
	EasyFile ef;
	if (ef.IsFileExist(path)==false)
	{
		ef.CreatFile(path);
	}
	gameUserHP = hp;
	gameUserMP = mp;
	gameUserLevel = Level;
	gameUserName = name;
	gameMapElements.RemoveAll();

	SaveGameMap();
}

void GameMap::LoadGameMap()
{
	EasyFile ef;
	EasyPath ep;
	EasyText et;

	//文件存储格式

	/*
	<Map Info>
		<MapName>xxxxx</MapName>
		<Width>1024</Width>
		<Heigth>768</Heigth>
		<Hash>md5</Hash>（MD5针对的是<Map Data>和</Map Data>中的所有数据，包括制表符）
	</Map Info>

	<User Data>
		<UserName>未命名</UserName>
		<HP>100</HP>
		<MP>100</MP>
		<Level>1</Level>
	</User Data>

	<Map Data>
		<Index></Index><ID></ID><Type></Type><X></X><Y></Y><Parameters>param里面有不同的分隔符(<Tag>value</Tag>)</Parameters>
		...
	</Map Data>
	*/
	
	//清除数据
	gameMapElements.RemoveAll();

	//读取数据
	CString str = ef.ReadCString(path);
	if (str.GetLength()==0)
	{
		AfxMessageBox(L"读取地图出现异常。");
		exit(-1);
	}

	//读取地图名
	CString temp = et.Middle(str,L"<MapName>",L"</MapName>");
	if (temp.Trim()==L"")
	{
		AfxMessageBox(L"读取地图出现异常。");
		exit(-1);
	}
	mapName = temp;

	//读取地图宽度
	temp = et.Middle(str, L"<Width>", L"</Width>");
	if (temp.Trim() == L"")
	{
		AfxMessageBox(L"读取地图出现异常。");
		exit(-1);
	}
	mapWidth = _ttoi(temp);

	//读取地图高度
	temp = et.Middle(str, L"<Heigth>", L"</Heigth>");
	if (temp.Trim() == L"")
	{
		AfxMessageBox(L"读取地图出现异常。");
		exit(-1);
	}
	mapHeight = _ttoi(temp);

	//读取地图MD5
	CString mapMD5 = et.Middle(str, L"<Hash>", L"</Hash>");
	if (mapMD5.Trim() == L"")
	{
		AfxMessageBox(L"读取地图出现异常。");
		exit(-1);
	}

	//读取游戏用户相关信息
	gameUserHP = _ttoi(et.Middle(str, L"<HP>", L"</HP>", 0, L"100"));
	gameUserMP = _ttoi(et.Middle(str, L"<MP>", L"</MP>", 0, L"100"));
	gameUserLevel = _ttoi(et.Middle(str, L"<Level>", L"</Level>", 0, L"1"));
	gameUserName = et.Middle(str, L"<UserName>", L"</UserName>", 0, L"未命名");


	//预处理<Map Data>
	EncodeMD5 md5;
	temp = L"<Map Data>" + et.Middle(str, L"<Map Data>", L"</Map Data>") + L"</Map Data>" + salt;
	string text(CW2A(temp.GetBuffer()));
	md5.update(text);
	temp.ReleaseBuffer();
	temp = md5.toString().c_str();

	/*
	if (mapMD5!= temp)
	{
		AfxMessageBox(L"地图数据被非法篡改。");
		exit(-1);
	}
	*/

	//读取地图元素数据
	temp = et.Middle(str, L"<Map Data>\r\n", L"\r\n</Map Data>");
	CStringArray rows;
	et.DivideText(temp, L"\r\n", rows);

	for (int i = 0; i < rows.GetCount(); i++)
	{
		gameMapElements.Add(GameMapElement());
		gameMapElements[i].index = _ttoi(et.Middle(rows.GetAt(i), L"<Index>", L"</Index>"));
		gameMapElements[i].id = et.Middle(rows.GetAt(i), L"<ID>", L"</ID>");
		gameMapElements[i].type = et.Middle(rows.GetAt(i), L"<Type>", L"</Type>");
		gameMapElements[i].x = _ttoi(et.Middle(rows.GetAt(i), L"<X>", L"</X>"));
		gameMapElements[i].y = _ttoi(et.Middle(rows.GetAt(i), L"<Y>", L"</Y>"));
		gameMapElements[i].w = _ttoi(et.Middle(rows.GetAt(i), L"<W>", L"</W>"));
		gameMapElements[i].h = _ttoi(et.Middle(rows.GetAt(i), L"<H>", L"</H>"));
		gameMapElements[i].params = et.Middle(rows.GetAt(i), L"<Parameters>", L"</Parameters>");
	}


	//计算出最大的序号
	int temp_max=0;
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (i==0)
		{
			temp_max = gameMapElements[i].index;
		}
		else
		{
			if (temp_max<gameMapElements[i].index)
			{
				temp_max = gameMapElements[i].index;
			}
		}
	}
	nowIndex = temp_max;
	
}

void GameMap::SaveGameMap()
{
	//文件存储格式

	/*
	<Map Info>
		<MapName>xxxxx</MapName>
		<Width>1024</Width>
		<Heigth>768</Heigth>
		<Hash>md5</Hash>（MD5针对的是<Map Data>和</Map Data>中的所有数据，包括制表符）
	</Map Info>

	<User Data>
		<UserName>未命名</UserName>
		<HP>100</HP>
		<MP>100</MP>
		<Level>1</Level>
	</User Data>

	<Map Data>
		<Index></Index><ID></ID><Type></Type><X></X><Y></Y><Parameters>分割符为###</Parameters>
		...
	</Map Data>
	*/
	
	EasyFile ef;
	EasyPath ep;
	EasyText et;

	CString writeStr, temp,mapData;

	//检查文件是否存在
	if (ef.IsFileExist(path)==false)
	{
		ef.CreatFile(path);
	}

	//生成Map Data
	mapData = L"";
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (i != 0)
		{
			mapData = mapData + L"\r\n";
		}

		//temp.Format(L"%d", gameMapElements[i].index);
		temp.Format(L"%d", i);
		mapData = mapData+ L"\t<Index>" + temp + L"</Index>";

		mapData = mapData + L"<ID>" + gameMapElements[i].id + L"</ID>";
		mapData = mapData + L"<Type>" + gameMapElements[i].type + L"</Type>";

		temp.Format(L"%d", gameMapElements[i].x);
		mapData = mapData + L"<X>" + temp + L"</X>";

		temp.Format(L"%d", gameMapElements[i].y);
		mapData = mapData + L"<Y>" + temp + L"</Y>";

		temp.Format(L"%d", gameMapElements[i].w);
		mapData = mapData + L"<W>" + temp + L"</W>";

		temp.Format(L"%d", gameMapElements[i].h);
		mapData = mapData + L"<H>" + temp + L"</H>";

		temp = gameMapElements[i].params;
		mapData = mapData + L"<Parameters>" + gameMapElements[i].params + L"</Parameters>";//改进：可用正则表达式
	}
	mapData = L"<Map Data>\r\n" + mapData + L"\r\n</Map Data>";


	//生成校验地图md5值
	CString mapMd5 = mapData + salt;;
	string text(CW2A(mapMd5.GetBuffer()));
	EncodeMD5 md5;
	mapMd5.ReleaseBuffer();
	mapMd5 = md5.toString().c_str();


	//生成 Map Info
	CString mapInfo;
	mapInfo = mapInfo + L"\t<MapName>" + mapName + L"</MapName>";

	temp.Format(L"%d", mapWidth);
	mapInfo = mapInfo + L"\r\n\t<Width>" + temp + L"</Width>";

	temp.Format(L"%d", mapHeight);
	mapInfo = mapInfo + L"\r\n\t<Heigth>" + temp + L"</Heigth>";

	mapInfo = mapInfo + L"\r\n\t<Hash>" + mapMd5 + L"</Hash>";

	mapInfo = L"<Map Info>\r\n" + mapInfo + L"\r\n<Map Info>";

	//生成 User Data
	CString userData;
	userData = L"\t<UserName>" + gameUserName + L"</UserName>";

	temp.Format(L"%d",gameUserHP);
	userData= userData+ L"<HP>" + temp + L"</HP>";

	temp.Format(L"%d", gameUserMP);
	userData = userData + L"<MP>" + temp + L"</MP>";

	temp.Format(L"%d", gameUserLevel);
	userData = userData + L"<Level>" + temp + L"</Level>";

	userData = L"<User Data>\r\n" + userData + L"\r\n<User Data>";


	//生成最终要保存的数据
	writeStr = mapInfo + L"\r\n\r\n" + userData + "\r\n\r\n" + mapData;
	ef.WriteCString(path, writeStr, true);
	
}

int GameMap::AddElement(CString id, CString type, int x, int y, int w, int h, CString params)
{
	
	nowIndex++;
	gameMapElements.Add(GameMapElement{ nowIndex, id, type, x, y,w,h,params });
	
	return nowIndex;
}

void GameMap::SetElementX(int index, int x)
{
	
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			gameMapElements[i].x = x;
			break;
		}
	}
	
}

int GameMap::GetElementX(int index)
{
	
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			return gameMapElements[i].x;
		}
	}
	
	return -1;
}

void GameMap::SetElementY(int index, int y)
{
	
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			gameMapElements[i].y = y;
			break;
		}
	}
	
}

int GameMap::GetElementY(int index)
{
	
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			return gameMapElements[i].y;
		}
	}
	
	return -1;
	
}

void GameMap::SetElementParam(int index, CString paramTag, CString paramValue)
{
	
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			gameMapElements[i].params = gameMapElements[i].params + L"<" + paramTag + L">" + paramValue + L"</" + paramTag + L">";
			return;
		}
	}
	
}

CString GameMap::GetElementParam(int index, CString paramTag)
{
	
	EasyText et;
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			if (gameMapElements[i].params.Find(L"<"+ paramTag +L">")!=-1 &&
				gameMapElements[i].params.Find(L"</" + paramTag + L">")!=-1)
			{
				return et.Middle(gameMapElements[i].params, L"<" + paramTag + L">", L"</" + paramTag + L">");
			}
		}
	}
	
	return L"";
	
}

void GameMap::RemoveElementParam(int index, CString paramTag)
{
	
	EasyText et;
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			if (gameMapElements[i].params.Find(L"<" + paramTag + L">") != -1 &&
				gameMapElements[i].params.Find(L"</" + paramTag + L">") != -1)
			{
				gameMapElements[i].params = et.Left(gameMapElements[i].params, L"<" + paramTag + L">") +
					et.Right(gameMapElements[i].params, L"</" + paramTag + L">");
				break;
			}
			
		}
	}
	
}

void GameMap::RemoveElement(int index)
{
	
	for (int i = 0; i < gameMapElements.GetCount(); i++)
	{
		if (gameMapElements[i].index == index)
		{
			gameMapElements.RemoveAt(i);
			return;
		}
	}
	
}

void GameMap::SetHP(int hp)
{
	if (hp>=0)
	{
		gameUserHP = hp;
	}
}

void GameMap::SetMP(int mp)
{
	if (mp>=0)
	{
		gameUserMP = mp;
	}
}

void GameMap::SetLevel(int level)
{
	if (level>=0)
	{
		gameUserLevel = level;
	}
}

void GameMap::SetUserName(CString name)
{
	if (name !=L"")
	{
		gameUserName = name;
	}
}

int GameMap::GetHP()
{
	return gameUserHP;
}

int GameMap::GetMP()
{
	return gameUserMP;
}

int GameMap::GetLevel()
{
	return gameUserLevel;
}

CString GameMap::GetGameUserName()
{
	return gameUserName;
}
