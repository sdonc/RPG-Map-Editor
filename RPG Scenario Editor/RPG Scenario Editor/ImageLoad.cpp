#include "stdafx.h"
#include "ImageLoader.h"


ImageLoader::ImageLoader()
{
	CheckSrc();
}


ImageLoader::~ImageLoader()
{
}

void ImageLoader::CheckSrc()
{
	EasyFile ef;
	EasyPath ep;

	basePath = ep.GetProgramDir();

	if (ef.IsFileExist(basePath + L"images") == false)
	{
		AfxMessageBox(L"程序关键目录：\"" + basePath + L"images\"不存在！");
		exit(-1);
	}

	if (ef.IsFileExist(basePath + L"images\\ImageConfig.sdonc") == false)
	{
		AfxMessageBox(L"图片配置文件：\"" + basePath + L"images\\ImageConfig.sdonc\"不存在！");
		exit(-1);
	}

	if (ef.IsFileExist(basePath + L"images\\ElementConfig.sdonc") == false)
	{
		AfxMessageBox(L"图片资源文件：\"" + basePath + L"images\\ElementConfig.sdonc\"不存在！");
		exit(-1);
	}

	if (ef.IsFileExist(basePath + L"images\\AnimationElementConfig.sdonc") == false)
	{
		AfxMessageBox(L"动画配置文件：\"" + basePath + L"images\\AnimationElementConfig.sdonc\"不存在！");
		exit(-1);
	}
}

CString ImageLoader::LoadSrcImages()
{
	EasyFile ef;
	EasyPath ep;
	EasyText et;
	CString src = ef.ReadCString(basePath + L"images\\ImageConfig.sdonc");

#pragma region 处理读进来的字符串
	CStringArray rows;
	CString temp;

	bool isOK = et.DivideText(src, L"\r\n", rows);//以换行符来分割字符串
	if (isOK == false)
	{
		AfxMessageBox(L"图片配置文件数据异常！");
		exit(-1);
	}

	//清除注释（从末尾开始往头遍历）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//取 // 的左边并且删除字符串首尾的空格。
		}
	}


	//清除空行（注意：不能放在“清除注释”的前面，因为有可能清除注释后那行变成空的）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}


	//调试输出一下读取到的文本
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"读入图片数据共：" + str + L"条。\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

#pragma region 加载图片资源
	ReleaseSrcImages();//删除旧的图片资源

	CString errorText;//错误文本
	for (int i = 0; i < rows.GetCount(); i++)
	{
		//检查语法错误
		if (rows.GetAt(i).Find(L"=") == -1 ||
			et.Left(rows.GetAt(i), L"=").Trim() == L"" || 
			et.Right(rows.GetAt(i), L"=").Trim() == L"")	//语法错误
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"语法错误。");
			continue;
		}


		//检查ID是否重复
		CString tempString = et.Left(rows.GetAt(i), L"=");
		CString tempString1 = L"";
		bool isCheckOK=true;
		for (int j = 0; j < srcImages.GetCount(); j++)
		{
			tempString1 = srcImages.GetAt(j).imgID;
			if (tempString == tempString1)
			{
				isCheckOK = false;
				AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"ID已重复。");
			}
		}
		if (isCheckOK==false)
		{
			continue;
		}


		//检查文件是否存在
		if (ef.IsFileExist(basePath + L"images\\" + et.Right(rows.GetAt(i), L"="))==false)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"图片不存在。");
			continue;
		}

		srcImages.Add(SrcImage{
			et.Left(rows.GetAt(i), L"="),
			et.Right(rows.GetAt(i), L"="),
			CImage()
		});
		srcImages[srcImages.GetCount() - 1].img.Load(basePath + L"images\\" + et.Right(rows.GetAt(i), L"="));
	}


#if _DEBUG
	if (errorText!=L"")
	{
		AfxMessageBox(errorText);
		OutputDebugString(errorText);
	}
#endif // _DEBUG


#pragma endregion
	
	return errorText;
}

void ImageLoader::ReleaseSrcImages()
{
	for (int i = 0; i < srcImages.GetCount(); i++)
	{
		srcImages[i].img.ReleaseGDIPlus();
	}
	srcImages.RemoveAll();

}

void ImageLoader::LoadStaticElementImage()
{
	//存储格式：ID,imgID,x,y,w,h,color,canPass
	//ID：元素ID，该值必须唯一。
	//imgID：图片ID，该图片必须在ImageConfig中注册ID。
	//x,y：相对于该ID的图片的左上角位置
	//w,h：图片宽度和高度
	//color：透明色，-1表示无透明色。默认为-1
	//canPass:是否可以通过，0=可通过，非0不可通过。默认为0.

	ReleaseStaticElementImage();//释放资源
	EasyFile ef;
	EasyPath ep;
	EasyText et;
	CString src = ef.ReadCString(basePath + L"images\\ElementConfig.sdonc");
	CString temp;
	bool isOK;//临时变量

#pragma region 处理读进来的字符串
	CStringArray rows;
	

	isOK = et.DivideText(src, L"\r\n", rows);//以换行符来分割字符串
	if (isOK == false)
	{
		AfxMessageBox(L"图片资源文件数据异常！");
		exit(-1);
	}

	//清除注释（从末尾开始往头遍历）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//取 // 的左边并且删除字符串首尾的空格。
		}
	}


	//清除空行（注意：不能放在“清除注释”的前面，因为有可能清除注释后那行变成空的）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}


	//调试输出一下读取到的文本
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"读入图片数据共：" + str + L"条。\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

#pragma region 读取参数

	CStringArray params;//存放每一行中的参数
	CString errorText=L"";
	
	for (int i = 0; i < rows.GetCount(); i++)
	{
		//处理系统变量
		//	#品红→ff00ff
		//	#黑色→000000
		//	#白色→ffffff
		temp = rows.GetAt(i);
		temp.Replace(L"#品红", L"FF00FF");
		temp.Replace(L"#黑色", L"0");
		temp.Replace(L"#白色", L"ffffff");
		rows.SetAt(i, temp);

		//分割参数
		et.DivideText(rows.GetAt(i), L",", params);

#pragma region 检查参数与自动补全

		//检查参数个数
		if (params.GetCount()>8)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"传入参数过多（最多有8个参数）。");
			continue;
		}
		else if (params.GetCount() < 6)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"传入参数过少（至少需要6个参数）。");
			continue;
		}
	

		//自动补齐参数
		if (params.GetCount()==6)
		{
			params.Add(L"-1");
			params.Add(L"0");
		}
		else if (params.GetCount() == 7)
		{
			params.Add(L"0");
		}


		//检查参数类型
		for (int j = 2; j <= 5; j++)
		{ 
			if (CheckStringInt(params.GetAt(j),true,true)==false)
			{
				temp.Format(L"%d", j + 1);
				AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"的第" + temp + L"个参数类型错误。该参数要求为纯数字。");
				continue;
			}
		}

		//检查ID是否为空
		if (params.GetAt(0).GetLength()==0)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"的参数1：ID，不能为空。");
			continue;
		}


		//检查图片资源图片是否链接正确
		bool isOK =false;
		for (int j = 0; j < srcImages.GetCount(); j++)
		{
			if (params.GetAt(1) == srcImages[j].imgID)
			{
				isOK = true;
				break;
			}
		}
		if (isOK ==false)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"的参数2：imgID，图片资源ID链接失败。");
			continue;
		}
		

		//检查透明色是否合法
		if (_ttoi(params.GetAt(6))<-1)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"的参数6：color，透明色数值错误。");
			continue;
		}
		

#pragma endregion	
		
#pragma region 读入参数


		//检查ID是否重复
		isOK = true;
		for (int j = 0; j < staticElementImages.GetCount(); j++)
		{
			if (params.GetAt(0) == staticElementImages[j].id)
			{
				isOK = false;
				AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"ID已重复。");
				break;
			}
		}
		if (isOK==false)
		{
			continue;
		}


		//待添加的判断↓↓↓↓↓↓↓↓↓↓↓↓↓

		//检查位置是否超出图片外

		//待添加的判断↑↑↑↑↑↑↑↑↑↑↑↑↑

		
		

		staticElementImages.Add(StaticElementImage{
			params.GetAt(0),
			params.GetAt(1),
			_ttoi(params.GetAt(2)),
			_ttoi(params.GetAt(3)),
			_ttoi(params.GetAt(4)),
			_ttoi(params.GetAt(5)),
			params.GetAt(6)==L"-1"?-1: HexToInt(params.GetAt(6)),
			params.GetAt(7)==L"0"?true:false
		});

#pragma endregion


	}

	
#if _DEBUG
	if (errorText != L"")
	{
		OutputDebugString(errorText);
		AfxMessageBox(errorText);
	}
	else
	{
		CString str;
		str.Format(L"读取静态资源数据（共：%d个）", staticElementImages.GetCount());
		for (int i = 0; i < staticElementImages.GetCount(); i++)
		{
			str = str + L"\r\nID = " + staticElementImages[i].id;
			str = str + L"\r\n\t imgID = " + staticElementImages[i].imgID;

			temp.Format(L"(%d,%d)", staticElementImages[i].x, staticElementImages[i].y);
			str = str + L"\r\n\t x,y = " + temp;

			temp.Format(L"%d", staticElementImages[i].w);
			str = str + L"\r\n\t w = " + temp;

			temp.Format(L"%d", staticElementImages[i].h);
			str = str + L"\r\n\t h = " + temp;
		
			temp.Format(L"%d", staticElementImages[i].color);
			str = str + L"\r\n\t color = " + temp;
			
			str = str + L"\r\n\t canPass = " + (staticElementImages[i].canPass?L"true":L"false");

			str = str + L"\r\n";
		}
		ef.WriteCString(ep.GetProgramDir()+L"test\\LoadElementConfig.txt",str);
	}
#endif // _DEBUG


#pragma endregion


}

void ImageLoader::ReleaseStaticElementImage()
{
	staticElementImages.RemoveAll();
}

void ImageLoader::LoadDynamicElementImage()
{
	ReleaseDynamicElementImage();
	EasyFile ef;
	EasyPath ep;
	EasyText et;
	CString src = ef.ReadCString(basePath + L"images\\AnimationElementConfig.sdonc");
	CString temp;//临时变量
	bool isOK;//临时变量

	//存储格式：ID,imgID,w,h,{tag1=x,y/x,y/x,y...;tag2=x,y/x,y/x,y...},color,canPass,autoPlay,defalutTag,interval
	//ID：元素ID，该值必须唯一。
	//imgID：图片ID，该图片必须在ImageConfig中注册ID。
	//w,h：图片宽度和高度
	//{tag1=x,y/x,y/x,y...;tag2=x,y/x,y/x,y...}：图片组，其中里面用分号';'隔开多个图片组，每个图片组前有一个标志，用来索引这个图片组，其中系统默认的标志有：front、back、right和left
	//color：透明色，-1表示无透明色。默认为-1。系统可用变量有：#品红、#黑色、#白色
	//canPass:是否可以通过，0=可通过，非0不可通过。默认为0.
	//autoPlay：自动播放哪个图片组，null或空字符串表示不自动播放
	//defalutTag:当autoPlay不自动播放时有效，默认播放图片索引（Tag）中的哪个
	//interval：播放间隔，单位：毫秒

#pragma region 处理读进来的字符串
	CStringArray rows;

	isOK = et.DivideText(src, L"\r\n", rows);//以换行符来分割字符串
	if (isOK == false)
	{
		AfxMessageBox(L"动画配置文件数据异常！");
		exit(-1);
	}

	//清除注释（从末尾开始往头遍历）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//取 // 的左边并且删除字符串首尾的空格。
		}
	}


	//清除空行（注意：不能放在“清除注释”的前面，因为有可能清除注释后那行变成空的）
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}


	//调试输出一下读取到的文本
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"读入图片数据共：" + str + L"条。\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

#pragma region 读取参数

	CStringArray params;
	CStringArray params_group;//图片组参数
	CStringArray params_group_point;//图片组参数中的坐标
	CString errorText = L"";//错误文本
	DynamicElementImageItem temp_item;//对应当前行的图片组数据
	CString temp_imageGroup;//当前行对应的图片组文本

	for (int i = 0; i < rows.GetCount(); i++)
	{
		//清除数据
		temp_item.imgs.RemoveAll();
		temp_item.tag = L"";
		params.RemoveAll();
		params_group.RemoveAll();
		params_group_point.RemoveAll();
		temp_imageGroup = L"";

//		tampDynamicElementImage.imageGroups.RemoveAll();

		//处理系统变量
		//	#品红→ff00ff
		//	#黑色→000000
		//	#白色→ffffff
		temp = rows.GetAt(i);
		temp.Replace(L"#品红", L"FF00FF");
		temp.Replace(L"#黑色", L"0");
		temp.Replace(L"#白色", L"ffffff");
		rows.SetAt(i, temp);
		

		//提取图片组参数
		if (rows.GetAt(i).Find(L"{")==-1 || rows.GetAt(i).Find(L"}") == -1)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"语法错误。大括号不存在或不匹配。");
			continue;
		}
		else if (rows.GetAt(i).Find(L"{") > rows.GetAt(i).Find(L"}"))
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"语法错误。大括号不存在或不匹配。");
			continue;
		}


		//检查图片组
		temp = et.Middle(rows.GetAt(i), L"{", L"}");
		temp_imageGroup = temp;
		if (temp.Trim()==L"")
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"图片组无数据。");
			continue;
		}
		
		
		//将图片组的数据从当前行中移除
		rows.SetAt(i, et.Left(rows.GetAt(i), L"{") + et.Right(rows.GetAt(i), L"}"));//注意这个逗号的保留
		/*
		示例输入：
		user,mapImg3,36,39,{front=20,29/56,29/92,29/128,29;left=20,80/56,80/92,80/128,80;right=20,171/56,171/92,171/128,171;back=20,121/56,121/92,121/128,121},#品红,1,front,front,200

		输出：
		user,mapImg3,36,39,,#品红,1,front,front,200
		*/

		#pragma region 图片组检查

		//分割组图片组的文本

		isOK = et.DivideText(temp, L";", params_group);

		if (isOK == false)//只有一行数据
		{
			params_group.RemoveAll();
			params_group.Add(temp);
		}

		isOK = true;
		CString leftStr, rightStr;//图片组参数中等号的左右两边的文本
		CString temp_x,temp_y;//图片组中参数中的坐标文本
		for (int j = 0; j < params_group.GetCount(); j++)
		{
			params_group_point.RemoveAll();
			temp_item.tag = L"";
			temp_item.imgs.RemoveAll();

			//对图片组的标志和参数进行检查
			if (params_group.GetAt(j).Find(L"=")==-1)
			{
				AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"中，图片组{" + params_group.GetAt(j) + L"}语法错误。");
				isOK = false;
				break;
			}

			leftStr = et.Left(params_group.GetAt(j), L"=").Trim();
			rightStr = et.Right(params_group.GetAt(j), L"=").Trim();
			if (leftStr==L"")//Tag为空
			{
				AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"中，图片组{" + params_group.GetAt(j) + L"}的标志Tag为空。");
				isOK = false;
				break;
			}
			if (rightStr == L"")//图片组为空
			{
				AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"中，图片组{" + params_group.GetAt(j) + L"}的参数为空。");
				isOK = false;
				break;
			}

			
			//读取图片组的参数
			if (et.DivideText(rightStr, L"/", params_group_point)==false)//只有一个参数
			{
				params_group_point.RemoveAll();
				params_group_point.Add(rightStr);
			}
			//将图片组参数加入到图片组结构体中
			temp_item.tag = leftStr;
			for (int k = 0; k < params_group_point.GetCount(); k++)
			{

			#pragma region 检查语法和空值和参数类型
				//检查语法
				if (params_group_point.GetAt(k).Find(L",") == -1)
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"行\"" +
						rows.GetAt(i) + L"\"中，图片组{" +
						params_group.GetAt(j) + L"}的第" +
						tempText +
						L"个参数\"" +
						params_group_point.GetAt(k) +
						L"\"语法错误。");
					goto hasErr;
				}



				//检查空值
				temp_x = et.Left(params_group_point.GetAt(k), L",");
				temp_y = et.Right(params_group_point.GetAt(k), L",");
				if (temp_x == L"")
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"行\"" +
						rows.GetAt(i) + L"\"中，图片组{" +
						params_group.GetAt(j) + L"}的第" +
						tempText +
						L"个参数\"" +
						params_group_point.GetAt(k) +
						L"\"横坐标x的值为空。");
					goto hasErr;
				}
				if (temp_y == L"")
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"行\"" +
						rows.GetAt(i) + L"\"中，图片组{" +
						params_group.GetAt(j) + L"}的第" +
						tempText +
						L"个参数\"" +
						params_group_point.GetAt(k) +
						L"\"纵坐标y的值为空。");
					goto hasErr;
				}



				//检查参数的类型
				if (CheckStringInt(temp_x) == false)
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"行\"" +
						rows.GetAt(i) + L"\"中，图片组{" +
						params_group.GetAt(j) + L"}的第" +
						tempText +
						L"个参数\"" +
						params_group_point.GetAt(k) +
						L"\"纵坐标y的值必须为纯数字。");
					goto hasErr;
				}
				if (CheckStringInt(temp_y) == false)
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"行\"" +
						rows.GetAt(i) + L"\"中，图片组{" +
						params_group.GetAt(j) + L"}的第" +
						tempText +
						L"个参数\"" +
						params_group_point.GetAt(k) +
						L"\"纵坐标y的值必须为纯数字。");
					goto hasErr;
				}
#pragma endregion

				
				
			}


		}
		if (isOK==false)
		{
hasErr:		continue;
		}

#pragma endregion

		#pragma region 读取参数
		et.DivideText(rows.GetAt(i), L",", params);

		//检查参数个数
		if (params.GetCount()!=10)
		{
			CString str;
			str.Format(L"%d", params.GetCount());
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数不足。当前参数仅有"+ str+L"个，该行参数必须为10个。");
			continue;
		}


		//检查id是否为空
		temp = params.GetAt(0);
		if (temp.Trim()==L"")
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"ID为空。");
			continue;
		}

		//检查ID是否重复
		isOK = true;
		for (int j = 0; j < dynamicElementImages.GetCount(); j++)
		{
			if (params.GetAt(0)== dynamicElementImages[j].id)
			{
				isOK = false;
				break;
			}
		}
		if (isOK==false)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数1：ID重复。");
			continue;
		}


		//检查图片ID是否存在
		isOK = false;
		for (int j = 0; j < srcImages.GetCount(); j++)
		{
			if (params.GetAt(1)== srcImages[j].imgID)
			{
				isOK = true;
			}
		}
		if (isOK == false)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数2：图片ID不存在。");
			continue;
		}


		//检查宽度
		if (CheckStringInt(params.GetAt(2))==false)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数3：图片宽度必须为纯数字。");
			continue;
		}


		//检查高度
		if (CheckStringInt(params.GetAt(3)) == false)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数4：图片高度必须为纯数字。");
			continue;
		}

		//检查透明色是否正确
		if (_ttoi(params.GetAt(5))<-1)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数6：透明色参数错误。");
			continue;
		}


		//处理自动播放图片组
		if (params.GetAt(7)==L"null")
		{
			params.SetAt(7, L"");
		}
		
		//检查自动播放图片组对应的图片组Tag是否存在
		if (temp_imageGroup.Find(params.GetAt(7))==-1)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数8：自动播放图片组Tag不存在");
			continue;
		}




		//处理默认播放图片组
		if (params.GetAt(8) == L"null")
		{
			params.SetAt(8, L"");
		}

		//检查默认播放图片组对应的图片组Tag是否存在
		if (temp_imageGroup.Find(params.GetAt(8)) == -1)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数9：默认播放图片组Tag不存在");
			continue;
		}



		//处理时间间隔
		if (CheckStringInt(params.GetAt(9))==false)
		{
			AddErrorText(errorText, L"行\"" + rows.GetAt(i) + L"\"参数10：时间间隔必须为纯数字。");
			continue;
		}

		

		dynamicElementImages.Add(DynamicElementImage{
		params.GetAt(0),
		params.GetAt(1),
		_ttoi(params.GetAt(2)),
		_ttoi(params.GetAt(3))
		});

		dynamicElementImages[dynamicElementImages.GetCount() - 1].color = (params.GetAt(5) == L"-1" ? -1 : HexToInt(params.GetAt(5)));
		dynamicElementImages[dynamicElementImages.GetCount() - 1].canPass = params.GetAt(6) == L"0" ? true : false;
		dynamicElementImages[dynamicElementImages.GetCount() - 1].autoPlay = params.GetAt(7);
		dynamicElementImages[dynamicElementImages.GetCount() - 1].defalutTag = params.GetAt(8);
		dynamicElementImages[dynamicElementImages.GetCount() - 1].interval = _ttoi(params.GetAt(9));

		dynamicElementImages[dynamicElementImages.GetCount() - 1].imageGroups = temp_imageGroup;


		#pragma endregion
		

	}

#pragma endregion



#if _DEBUG
	if (errorText!=L"")
	{
		AfxMessageBox(errorText);
	}
	else 
	{
		CString str;
		
		str.Format(L"动态图片数据（共%d个）", dynamicElementImages.GetCount());
		
		for (int i = 0; i < dynamicElementImages.GetCount(); i++)
		{
			str = str + L"\r\nID = " + dynamicElementImages[i].id;
			str = str + L"\r\n\timgID = " + dynamicElementImages[i].imgID;

			temp.Format(L"%d", dynamicElementImages[i].w);
			str = str + L"\r\n\tw = " + temp;

			temp.Format(L"%d", dynamicElementImages[i].h);
			str = str + L"\r\n\th = " + temp;

			str = str + L"\r\n\timageGroups = " + dynamicElementImages[i].imageGroups;

			temp.Format(L"%d", dynamicElementImages[i].color);
			str = str + L"\r\n\tcolor = " + temp;

			str = str + L"\r\n\tcanPass = " + (dynamicElementImages[i].canPass?L"true":L"false");
			str = str + L"\r\n\tautoPlay = " + dynamicElementImages[i].autoPlay;
			str = str + L"\r\n\tdefalutTag = " + dynamicElementImages[i].defalutTag;

			temp.Format(L"%d", dynamicElementImages[i].interval);
			str = str + L"\r\n\tinterval = " + temp;
			str = str + L"\r\n";
		}
		
		ef.WriteCString(basePath + L"test\\LoadDynamicElementImages.txt",str);

	}


#endif // _DEBUG



}

void ImageLoader::ReleaseDynamicElementImage()
{
	dynamicElementImages.RemoveAll();
}

inline void ImageLoader::AddErrorText(CString &src, CString addSrc)
{
	if (src == L"")
	{
		src = addSrc;
	}
	else
	{
		src = src + L"\r\n" + addSrc;
	}
}

bool ImageLoader::CheckStringInt(CString src, bool AllowNegative, bool allowNull)
{
	//检查空值
	if (src.GetLength()==0 && allowNull == true)
	{
		return true;
	}
	else if (src.GetLength() == 0)
	{
		return false;
	}


	//检查负数
	if (AllowNegative==true)
	{
		//检查是否是负数
		if (src.GetLength()==1 && src.GetAt(0)=='-')
		{
			return false;
		}
		else if(src.GetLength() >1 && src.GetAt(0) == '-')
		{
			src.SetAt(0, '0');//将第一位的负号设置成0，方便后面的判断
		}
	}

	long i = src.GetLength() - 1;
	for (; i >= 0; i--)
		if (src.GetAt(i)<0x30 || src.GetAt(i)>0x39) break;

	if (i >= 0)//不是全数字
	{
		return false;
	}
	else//均为数字
	{
		return true;
	}
}

int ImageLoader::HexToInt(CString hex)
{
	if (hex == L"")
	{
		return 0;
	}
	
	int sum = 0;
	bool begin=false;//是否开始计算
	hex.MakeLower();//转成小写

	for (int i = 0; i < hex.GetLength(); i++)
	{
		if (begin== false && hex.GetAt(i)!='0')
		{
			begin = true;
		}
		if (begin)
		{
			if (hex.GetAt(i)>='0' && hex.GetAt(i)<='9')
			{
				sum += (hex.GetAt(i) - '0') * int(pow(16, hex.GetLength() - i - 1));
			}
			else if (hex.GetAt(i) >= 'a' && hex.GetAt(i) <= 'f')
			{
				sum += (hex.GetAt(i) - 'a' + 10) * int(pow(16, hex.GetLength() - i - 1));
			}
			else//不是十六进制数
			{
				return 0;
			}
		}
	}
	return sum;
}

