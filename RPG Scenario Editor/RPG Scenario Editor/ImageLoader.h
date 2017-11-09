#pragma once

//图片素材（ImageConfig.sdonc）
struct SrcImage
{
	//存储格式：imgID=path
	//imgID：图片ID，除了逗号和换行，其他字符均可作为该图片的ID，但建议仅使用英文。
	//path：相对路径，注意前面不要加“/”
	CString imgID;//图片ID
	CString path;//相对路径
	CImage img;//图片素材
};


//静态图片资源（ElementConfig.sdonc）
struct StaticElementImage
{
	//存储格式：ID,imgID,x,y,w,h,color,canPass
	//ID：元素ID，该值必须唯一。
	//imgID：图片ID，该图片必须在ImageConfig中注册ID。
	//x,y：相对于该ID的图片的左上角位置
	//w,h：图片宽度和高度
	//color：透明色，-1表示无透明色。默认为-1
	//canPass:是否可以通过，0=可通过，非0不可通过。默认为0.
	CString id;
	CString imgID;
	int x, y, w, h;
	int color;
	bool canPass;
};


//标志-图片组
struct DynamicElementImageItem	//图片组名
{
	CString tag;
	CArray<CPoint> imgs;//图片组（坐标位置）
};


//动态图片资源（AnimationElementConfig.sdonc）
struct DynamicElementImage
{
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

	CString id;
	CString imgID;
	int w, h;

	CString imageGroups;//图片组

	int color;
	bool canPass;
	CString autoPlay;
	CString defalutTag;
	int interval;
};



class ImageLoader
{
public:
	ImageLoader();
	~ImageLoader();

	//开始加载资源
	void BeginLoad()
	{
		CString errorText;
		errorText = LoadSrcImages();
		if (errorText!=L"")
		{
			AfxMessageBox(L"加载图片资源出现错误！\r\n错误内容：\r\n" + errorText);
			exit(-1);
		}

		LoadStaticElementImage();
		LoadDynamicElementImage();
	}

	//开始释放资源
	void BeginRelease()
	{
		ReleaseSrcImages();
		ReleaseStaticElementImage();
		ReleaseDynamicElementImage();
	}


	CArray<SrcImage> srcImages;
	CArray<StaticElementImage> staticElementImages;
	CArray<DynamicElementImage> dynamicElementImages;

private:
	//检查关键文件是否存在
	void CheckSrc();


	//加载 图片素材（ImageConfig.sdonc）
	CString LoadSrcImages();

	//释放 图片素材
	void ReleaseSrcImages();



	//加载 静态图片资源（ElementConfig.sdonc）
	void LoadStaticElementImage();

	//释放 静态图片资源
	void ReleaseStaticElementImage();



	//加载 动态图片资源（AnimationElementConfig.sdonc）
	void LoadDynamicElementImage();

	//释放 动态图片资源
	void ReleaseDynamicElementImage();



	//往错误文本里添加一个错误解释
	void AddErrorText(CString &src, CString addSrc);

	//检查字符串是否是整数（参数二为是否允许是负数，参数三为是否允许空字符串）
	bool CheckStringInt(CString src, bool allowNegative = true, bool allowNull = true);

	//十六到十（不要包含0x，不要传入负数，否则返回0）
	int HexToInt(CString hex);

	CString basePath;//程序的运行路径（末尾包含“\”）
};

