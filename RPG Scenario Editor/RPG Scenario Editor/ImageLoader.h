#pragma once

//ͼƬ�زģ�ImageConfig.sdonc��
struct SrcImage
{
	//�洢��ʽ��imgID=path
	//imgID��ͼƬID�����˶��źͻ��У������ַ�������Ϊ��ͼƬ��ID���������ʹ��Ӣ�ġ�
	//path�����·����ע��ǰ�治Ҫ�ӡ�/��
	CString imgID;//ͼƬID
	CString path;//���·��
	CImage img;//ͼƬ�ز�
};


//��̬ͼƬ��Դ��ElementConfig.sdonc��
struct StaticElementImage
{
	//�洢��ʽ��ID,imgID,x,y,w,h,color,canPass
	//ID��Ԫ��ID����ֵ����Ψһ��
	//imgID��ͼƬID����ͼƬ������ImageConfig��ע��ID��
	//x,y������ڸ�ID��ͼƬ�����Ͻ�λ��
	//w,h��ͼƬ��Ⱥ͸߶�
	//color��͸��ɫ��-1��ʾ��͸��ɫ��Ĭ��Ϊ-1
	//canPass:�Ƿ����ͨ����0=��ͨ������0����ͨ����Ĭ��Ϊ0.
	CString id;
	CString imgID;
	int x, y, w, h;
	int color;
	bool canPass;
};


//��־-ͼƬ��
struct DynamicElementImageItem	//ͼƬ����
{
	CString tag;
	CArray<CPoint> imgs;//ͼƬ�飨����λ�ã�
};


//��̬ͼƬ��Դ��AnimationElementConfig.sdonc��
struct DynamicElementImage
{
	//�洢��ʽ��ID,imgID,w,h,{tag1=x,y/x,y/x,y...;tag2=x,y/x,y/x,y...},color,canPass,autoPlay,defalutTag,interval
	//ID��Ԫ��ID����ֵ����Ψһ��
	//imgID��ͼƬID����ͼƬ������ImageConfig��ע��ID��
	//w,h��ͼƬ��Ⱥ͸߶�
	//{tag1=x,y/x,y/x,y...;tag2=x,y/x,y/x,y...}��ͼƬ�飬���������÷ֺ�';'�������ͼƬ�飬ÿ��ͼƬ��ǰ��һ����־�������������ͼƬ�飬����ϵͳĬ�ϵı�־�У�front��back��right��left
	//color��͸��ɫ��-1��ʾ��͸��ɫ��Ĭ��Ϊ-1��ϵͳ���ñ����У�#Ʒ�졢#��ɫ��#��ɫ
	//canPass:�Ƿ����ͨ����0=��ͨ������0����ͨ����Ĭ��Ϊ0.
	//autoPlay���Զ������ĸ�ͼƬ�飬null����ַ�����ʾ���Զ�����
	//defalutTag:��autoPlay���Զ�����ʱ��Ч��Ĭ�ϲ���ͼƬ������Tag���е��ĸ�
	//interval�����ż������λ������

	CString id;
	CString imgID;
	int w, h;

	CString imageGroups;//ͼƬ��

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

	//��ʼ������Դ
	void BeginLoad()
	{
		CString errorText;
		errorText = LoadSrcImages();
		if (errorText!=L"")
		{
			AfxMessageBox(L"����ͼƬ��Դ���ִ���\r\n�������ݣ�\r\n" + errorText);
			exit(-1);
		}

		LoadStaticElementImage();
		LoadDynamicElementImage();
	}

	//��ʼ�ͷ���Դ
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
	//���ؼ��ļ��Ƿ����
	void CheckSrc();


	//���� ͼƬ�زģ�ImageConfig.sdonc��
	CString LoadSrcImages();

	//�ͷ� ͼƬ�ز�
	void ReleaseSrcImages();



	//���� ��̬ͼƬ��Դ��ElementConfig.sdonc��
	void LoadStaticElementImage();

	//�ͷ� ��̬ͼƬ��Դ
	void ReleaseStaticElementImage();



	//���� ��̬ͼƬ��Դ��AnimationElementConfig.sdonc��
	void LoadDynamicElementImage();

	//�ͷ� ��̬ͼƬ��Դ
	void ReleaseDynamicElementImage();



	//�������ı������һ���������
	void AddErrorText(CString &src, CString addSrc);

	//����ַ����Ƿ���������������Ϊ�Ƿ������Ǹ�����������Ϊ�Ƿ�������ַ�����
	bool CheckStringInt(CString src, bool allowNegative = true, bool allowNull = true);

	//ʮ����ʮ����Ҫ����0x����Ҫ���븺�������򷵻�0��
	int HexToInt(CString hex);

	CString basePath;//���������·����ĩβ������\����
};

