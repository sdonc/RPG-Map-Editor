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
		AfxMessageBox(L"����ؼ�Ŀ¼��\"" + basePath + L"images\"�����ڣ�");
		exit(-1);
	}

	if (ef.IsFileExist(basePath + L"images\\ImageConfig.sdonc") == false)
	{
		AfxMessageBox(L"ͼƬ�����ļ���\"" + basePath + L"images\\ImageConfig.sdonc\"�����ڣ�");
		exit(-1);
	}

	if (ef.IsFileExist(basePath + L"images\\ElementConfig.sdonc") == false)
	{
		AfxMessageBox(L"ͼƬ��Դ�ļ���\"" + basePath + L"images\\ElementConfig.sdonc\"�����ڣ�");
		exit(-1);
	}

	if (ef.IsFileExist(basePath + L"images\\AnimationElementConfig.sdonc") == false)
	{
		AfxMessageBox(L"���������ļ���\"" + basePath + L"images\\AnimationElementConfig.sdonc\"�����ڣ�");
		exit(-1);
	}
}

CString ImageLoader::LoadSrcImages()
{
	EasyFile ef;
	EasyPath ep;
	EasyText et;
	CString src = ef.ReadCString(basePath + L"images\\ImageConfig.sdonc");

#pragma region ������������ַ���
	CStringArray rows;
	CString temp;

	bool isOK = et.DivideText(src, L"\r\n", rows);//�Ի��з����ָ��ַ���
	if (isOK == false)
	{
		AfxMessageBox(L"ͼƬ�����ļ������쳣��");
		exit(-1);
	}

	//���ע�ͣ���ĩβ��ʼ��ͷ������
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//ȡ // ����߲���ɾ���ַ�����β�Ŀո�
		}
	}


	//������У�ע�⣺���ܷ��ڡ����ע�͡���ǰ�棬��Ϊ�п������ע�ͺ����б�ɿյģ�
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}


	//�������һ�¶�ȡ�����ı�
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"����ͼƬ���ݹ���" + str + L"����\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

#pragma region ����ͼƬ��Դ
	ReleaseSrcImages();//ɾ���ɵ�ͼƬ��Դ

	CString errorText;//�����ı�
	for (int i = 0; i < rows.GetCount(); i++)
	{
		//����﷨����
		if (rows.GetAt(i).Find(L"=") == -1 ||
			et.Left(rows.GetAt(i), L"=").Trim() == L"" || 
			et.Right(rows.GetAt(i), L"=").Trim() == L"")	//�﷨����
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�﷨����");
			continue;
		}


		//���ID�Ƿ��ظ�
		CString tempString = et.Left(rows.GetAt(i), L"=");
		CString tempString1 = L"";
		bool isCheckOK=true;
		for (int j = 0; j < srcImages.GetCount(); j++)
		{
			tempString1 = srcImages.GetAt(j).imgID;
			if (tempString == tempString1)
			{
				isCheckOK = false;
				AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"ID���ظ���");
			}
		}
		if (isCheckOK==false)
		{
			continue;
		}


		//����ļ��Ƿ����
		if (ef.IsFileExist(basePath + L"images\\" + et.Right(rows.GetAt(i), L"="))==false)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"ͼƬ�����ڡ�");
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
	//�洢��ʽ��ID,imgID,x,y,w,h,color,canPass
	//ID��Ԫ��ID����ֵ����Ψһ��
	//imgID��ͼƬID����ͼƬ������ImageConfig��ע��ID��
	//x,y������ڸ�ID��ͼƬ�����Ͻ�λ��
	//w,h��ͼƬ��Ⱥ͸߶�
	//color��͸��ɫ��-1��ʾ��͸��ɫ��Ĭ��Ϊ-1
	//canPass:�Ƿ����ͨ����0=��ͨ������0����ͨ����Ĭ��Ϊ0.

	ReleaseStaticElementImage();//�ͷ���Դ
	EasyFile ef;
	EasyPath ep;
	EasyText et;
	CString src = ef.ReadCString(basePath + L"images\\ElementConfig.sdonc");
	CString temp;
	bool isOK;//��ʱ����

#pragma region ������������ַ���
	CStringArray rows;
	

	isOK = et.DivideText(src, L"\r\n", rows);//�Ի��з����ָ��ַ���
	if (isOK == false)
	{
		AfxMessageBox(L"ͼƬ��Դ�ļ������쳣��");
		exit(-1);
	}

	//���ע�ͣ���ĩβ��ʼ��ͷ������
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//ȡ // ����߲���ɾ���ַ�����β�Ŀո�
		}
	}


	//������У�ע�⣺���ܷ��ڡ����ע�͡���ǰ�棬��Ϊ�п������ע�ͺ����б�ɿյģ�
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}


	//�������һ�¶�ȡ�����ı�
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"����ͼƬ���ݹ���" + str + L"����\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

#pragma region ��ȡ����

	CStringArray params;//���ÿһ���еĲ���
	CString errorText=L"";
	
	for (int i = 0; i < rows.GetCount(); i++)
	{
		//����ϵͳ����
		//	#Ʒ���ff00ff
		//	#��ɫ��000000
		//	#��ɫ��ffffff
		temp = rows.GetAt(i);
		temp.Replace(L"#Ʒ��", L"FF00FF");
		temp.Replace(L"#��ɫ", L"0");
		temp.Replace(L"#��ɫ", L"ffffff");
		rows.SetAt(i, temp);

		//�ָ����
		et.DivideText(rows.GetAt(i), L",", params);

#pragma region ���������Զ���ȫ

		//����������
		if (params.GetCount()>8)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����������ࣨ�����8����������");
			continue;
		}
		else if (params.GetCount() < 6)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����������٣�������Ҫ6����������");
			continue;
		}
	

		//�Զ��������
		if (params.GetCount()==6)
		{
			params.Add(L"-1");
			params.Add(L"0");
		}
		else if (params.GetCount() == 7)
		{
			params.Add(L"0");
		}


		//����������
		for (int j = 2; j <= 5; j++)
		{ 
			if (CheckStringInt(params.GetAt(j),true,true)==false)
			{
				temp.Format(L"%d", j + 1);
				AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�ĵ�" + temp + L"���������ʹ��󡣸ò���Ҫ��Ϊ�����֡�");
				continue;
			}
		}

		//���ID�Ƿ�Ϊ��
		if (params.GetAt(0).GetLength()==0)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�Ĳ���1��ID������Ϊ�ա�");
			continue;
		}


		//���ͼƬ��ԴͼƬ�Ƿ�������ȷ
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
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�Ĳ���2��imgID��ͼƬ��ԴID����ʧ�ܡ�");
			continue;
		}
		

		//���͸��ɫ�Ƿ�Ϸ�
		if (_ttoi(params.GetAt(6))<-1)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�Ĳ���6��color��͸��ɫ��ֵ����");
			continue;
		}
		

#pragma endregion	
		
#pragma region �������


		//���ID�Ƿ��ظ�
		isOK = true;
		for (int j = 0; j < staticElementImages.GetCount(); j++)
		{
			if (params.GetAt(0) == staticElementImages[j].id)
			{
				isOK = false;
				AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"ID���ظ���");
				break;
			}
		}
		if (isOK==false)
		{
			continue;
		}


		//����ӵ��жϡ�������������������������

		//���λ���Ƿ񳬳�ͼƬ��

		//����ӵ��жϡ�������������������������

		
		

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
		str.Format(L"��ȡ��̬��Դ���ݣ�����%d����", staticElementImages.GetCount());
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
	CString temp;//��ʱ����
	bool isOK;//��ʱ����

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

#pragma region ������������ַ���
	CStringArray rows;

	isOK = et.DivideText(src, L"\r\n", rows);//�Ի��з����ָ��ַ���
	if (isOK == false)
	{
		AfxMessageBox(L"���������ļ������쳣��");
		exit(-1);
	}

	//���ע�ͣ���ĩβ��ʼ��ͷ������
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Find(L"//") != -1)
		{
			rows.SetAt(i, et.Left(temp, L"//"));//ȡ // ����߲���ɾ���ַ�����β�Ŀո�
		}
	}


	//������У�ע�⣺���ܷ��ڡ����ע�͡���ǰ�棬��Ϊ�п������ע�ͺ����б�ɿյģ�
	for (int i = rows.GetCount() - 1; i >= 0; i--)
	{
		temp = rows.GetAt(i);
		if (temp.Trim() == L"")
		{
			rows.RemoveAt(i);
		}
	}


	//�������һ�¶�ȡ�����ı�
#ifdef _DEBUG
	CString str;
	str.Format(L"%d", rows.GetCount());
	OutputDebugString(L"����ͼƬ���ݹ���" + str + L"����\r\n");

	for (int i = 0; i < rows.GetCount(); i++)
		OutputDebugString(rows.GetAt(i) + L"\r\n");
#endif

#pragma endregion

#pragma region ��ȡ����

	CStringArray params;
	CStringArray params_group;//ͼƬ�����
	CStringArray params_group_point;//ͼƬ������е�����
	CString errorText = L"";//�����ı�
	DynamicElementImageItem temp_item;//��Ӧ��ǰ�е�ͼƬ������
	CString temp_imageGroup;//��ǰ�ж�Ӧ��ͼƬ���ı�

	for (int i = 0; i < rows.GetCount(); i++)
	{
		//�������
		temp_item.imgs.RemoveAll();
		temp_item.tag = L"";
		params.RemoveAll();
		params_group.RemoveAll();
		params_group_point.RemoveAll();
		temp_imageGroup = L"";

//		tampDynamicElementImage.imageGroups.RemoveAll();

		//����ϵͳ����
		//	#Ʒ���ff00ff
		//	#��ɫ��000000
		//	#��ɫ��ffffff
		temp = rows.GetAt(i);
		temp.Replace(L"#Ʒ��", L"FF00FF");
		temp.Replace(L"#��ɫ", L"0");
		temp.Replace(L"#��ɫ", L"ffffff");
		rows.SetAt(i, temp);
		

		//��ȡͼƬ�����
		if (rows.GetAt(i).Find(L"{")==-1 || rows.GetAt(i).Find(L"}") == -1)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�﷨���󡣴����Ų����ڻ�ƥ�䡣");
			continue;
		}
		else if (rows.GetAt(i).Find(L"{") > rows.GetAt(i).Find(L"}"))
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�﷨���󡣴����Ų����ڻ�ƥ�䡣");
			continue;
		}


		//���ͼƬ��
		temp = et.Middle(rows.GetAt(i), L"{", L"}");
		temp_imageGroup = temp;
		if (temp.Trim()==L"")
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"ͼƬ�������ݡ�");
			continue;
		}
		
		
		//��ͼƬ������ݴӵ�ǰ�����Ƴ�
		rows.SetAt(i, et.Left(rows.GetAt(i), L"{") + et.Right(rows.GetAt(i), L"}"));//ע��������ŵı���
		/*
		ʾ�����룺
		user,mapImg3,36,39,{front=20,29/56,29/92,29/128,29;left=20,80/56,80/92,80/128,80;right=20,171/56,171/92,171/128,171;back=20,121/56,121/92,121/128,121},#Ʒ��,1,front,front,200

		�����
		user,mapImg3,36,39,,#Ʒ��,1,front,front,200
		*/

		#pragma region ͼƬ����

		//�ָ���ͼƬ����ı�

		isOK = et.DivideText(temp, L";", params_group);

		if (isOK == false)//ֻ��һ������
		{
			params_group.RemoveAll();
			params_group.Add(temp);
		}

		isOK = true;
		CString leftStr, rightStr;//ͼƬ������еȺŵ��������ߵ��ı�
		CString temp_x,temp_y;//ͼƬ���в����е������ı�
		for (int j = 0; j < params_group.GetCount(); j++)
		{
			params_group_point.RemoveAll();
			temp_item.tag = L"";
			temp_item.imgs.RemoveAll();

			//��ͼƬ��ı�־�Ͳ������м��
			if (params_group.GetAt(j).Find(L"=")==-1)
			{
				AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�У�ͼƬ��{" + params_group.GetAt(j) + L"}�﷨����");
				isOK = false;
				break;
			}

			leftStr = et.Left(params_group.GetAt(j), L"=").Trim();
			rightStr = et.Right(params_group.GetAt(j), L"=").Trim();
			if (leftStr==L"")//TagΪ��
			{
				AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�У�ͼƬ��{" + params_group.GetAt(j) + L"}�ı�־TagΪ�ա�");
				isOK = false;
				break;
			}
			if (rightStr == L"")//ͼƬ��Ϊ��
			{
				AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�У�ͼƬ��{" + params_group.GetAt(j) + L"}�Ĳ���Ϊ�ա�");
				isOK = false;
				break;
			}

			
			//��ȡͼƬ��Ĳ���
			if (et.DivideText(rightStr, L"/", params_group_point)==false)//ֻ��һ������
			{
				params_group_point.RemoveAll();
				params_group_point.Add(rightStr);
			}
			//��ͼƬ��������뵽ͼƬ��ṹ����
			temp_item.tag = leftStr;
			for (int k = 0; k < params_group_point.GetCount(); k++)
			{

			#pragma region ����﷨�Ϳ�ֵ�Ͳ�������
				//����﷨
				if (params_group_point.GetAt(k).Find(L",") == -1)
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"��\"" +
						rows.GetAt(i) + L"\"�У�ͼƬ��{" +
						params_group.GetAt(j) + L"}�ĵ�" +
						tempText +
						L"������\"" +
						params_group_point.GetAt(k) +
						L"\"�﷨����");
					goto hasErr;
				}



				//����ֵ
				temp_x = et.Left(params_group_point.GetAt(k), L",");
				temp_y = et.Right(params_group_point.GetAt(k), L",");
				if (temp_x == L"")
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"��\"" +
						rows.GetAt(i) + L"\"�У�ͼƬ��{" +
						params_group.GetAt(j) + L"}�ĵ�" +
						tempText +
						L"������\"" +
						params_group_point.GetAt(k) +
						L"\"������x��ֵΪ�ա�");
					goto hasErr;
				}
				if (temp_y == L"")
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"��\"" +
						rows.GetAt(i) + L"\"�У�ͼƬ��{" +
						params_group.GetAt(j) + L"}�ĵ�" +
						tempText +
						L"������\"" +
						params_group_point.GetAt(k) +
						L"\"������y��ֵΪ�ա�");
					goto hasErr;
				}



				//������������
				if (CheckStringInt(temp_x) == false)
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"��\"" +
						rows.GetAt(i) + L"\"�У�ͼƬ��{" +
						params_group.GetAt(j) + L"}�ĵ�" +
						tempText +
						L"������\"" +
						params_group_point.GetAt(k) +
						L"\"������y��ֵ����Ϊ�����֡�");
					goto hasErr;
				}
				if (CheckStringInt(temp_y) == false)
				{
					CString tempText;
					tempText.Format(L"%d", k + 1);
					AddErrorText(errorText,
						L"��\"" +
						rows.GetAt(i) + L"\"�У�ͼƬ��{" +
						params_group.GetAt(j) + L"}�ĵ�" +
						tempText +
						L"������\"" +
						params_group_point.GetAt(k) +
						L"\"������y��ֵ����Ϊ�����֡�");
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

		#pragma region ��ȡ����
		et.DivideText(rows.GetAt(i), L",", params);

		//����������
		if (params.GetCount()!=10)
		{
			CString str;
			str.Format(L"%d", params.GetCount());
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"�������㡣��ǰ��������"+ str+L"�������в�������Ϊ10����");
			continue;
		}


		//���id�Ƿ�Ϊ��
		temp = params.GetAt(0);
		if (temp.Trim()==L"")
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"IDΪ�ա�");
			continue;
		}

		//���ID�Ƿ��ظ�
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
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����1��ID�ظ���");
			continue;
		}


		//���ͼƬID�Ƿ����
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
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����2��ͼƬID�����ڡ�");
			continue;
		}


		//�����
		if (CheckStringInt(params.GetAt(2))==false)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����3��ͼƬ��ȱ���Ϊ�����֡�");
			continue;
		}


		//���߶�
		if (CheckStringInt(params.GetAt(3)) == false)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����4��ͼƬ�߶ȱ���Ϊ�����֡�");
			continue;
		}

		//���͸��ɫ�Ƿ���ȷ
		if (_ttoi(params.GetAt(5))<-1)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����6��͸��ɫ��������");
			continue;
		}


		//�����Զ�����ͼƬ��
		if (params.GetAt(7)==L"null")
		{
			params.SetAt(7, L"");
		}
		
		//����Զ�����ͼƬ���Ӧ��ͼƬ��Tag�Ƿ����
		if (temp_imageGroup.Find(params.GetAt(7))==-1)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����8���Զ�����ͼƬ��Tag������");
			continue;
		}




		//����Ĭ�ϲ���ͼƬ��
		if (params.GetAt(8) == L"null")
		{
			params.SetAt(8, L"");
		}

		//���Ĭ�ϲ���ͼƬ���Ӧ��ͼƬ��Tag�Ƿ����
		if (temp_imageGroup.Find(params.GetAt(8)) == -1)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����9��Ĭ�ϲ���ͼƬ��Tag������");
			continue;
		}



		//����ʱ����
		if (CheckStringInt(params.GetAt(9))==false)
		{
			AddErrorText(errorText, L"��\"" + rows.GetAt(i) + L"\"����10��ʱ��������Ϊ�����֡�");
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
		
		str.Format(L"��̬ͼƬ���ݣ���%d����", dynamicElementImages.GetCount());
		
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
	//����ֵ
	if (src.GetLength()==0 && allowNull == true)
	{
		return true;
	}
	else if (src.GetLength() == 0)
	{
		return false;
	}


	//��鸺��
	if (AllowNegative==true)
	{
		//����Ƿ��Ǹ���
		if (src.GetLength()==1 && src.GetAt(0)=='-')
		{
			return false;
		}
		else if(src.GetLength() >1 && src.GetAt(0) == '-')
		{
			src.SetAt(0, '0');//����һλ�ĸ������ó�0�����������ж�
		}
	}

	long i = src.GetLength() - 1;
	for (; i >= 0; i--)
		if (src.GetAt(i)<0x30 || src.GetAt(i)>0x39) break;

	if (i >= 0)//����ȫ����
	{
		return false;
	}
	else//��Ϊ����
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
	bool begin=false;//�Ƿ�ʼ����
	hex.MakeLower();//ת��Сд

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
			else//����ʮ��������
			{
				return 0;
			}
		}
	}
	return sum;
}

