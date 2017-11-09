
// RPG Scenario EditorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "RPG Scenario EditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRPGScenarioEditorDlg �Ի���

CRPGScenarioEditorDlg::CRPGScenarioEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RPGSCENARIOEDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRPGScenarioEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ELEMENT, m_list);
	DDX_Control(pDX, IDC_STATIC_ELEMENT_CAN_PASS, m_checkElementCanPass);
	DDX_Control(pDX, IDC_STATIC_ELEMENT_IMAGE, m_elementImage);
	DDX_Control(pDX, IDC_LIST_MAP_ELEMENT, m_listMapElement);
	DDX_Control(pDX, IDC_LIST2, m_listElementTrigger);
	DDX_Control(pDX, IDC_LIST3, m_listTriggerAction);
	//DDX_Control(pDX, IDC_CHECK1, m_checkBoxTriggerActionEnable);
	//DDX_Control(pDX, IDC_CHECK2, m_checkBoxShowTextEnable);
	DDX_Control(pDX, IDC_STATIC_MAP, m_map);
	DDX_Control(pDX, IDC_SCROLLBAR_MAP_Y, m_scrollBarY);
	DDX_Control(pDX, IDC_SCROLLBAR_MAP_X, m_scrollBarX);
	DDX_Control(pDX, IDC_CHECK3, m_checkBoxGrid);
	DDX_Control(pDX, IDC_STATIC_NOW_IMAGE, m_staticTextNowMapChooes);
	DDX_Control(pDX, IDC_CHECK_NOW_CAN_PASS, m_checkBoxNowChooseCanPass);
}

BEGIN_MESSAGE_MAP(CRPGScenarioEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRPGScenarioEditorDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3_LOGIN, &CRPGScenarioEditorDlg::OnBnClickedButton3Login)
	ON_BN_CLICKED(IDC_BUTTON3_SIGN_OUT, &CRPGScenarioEditorDlg::OnBnClickedButton3SignOut)
	ON_MESSAGE(MY_NEWMAP, &CRPGScenarioEditorDlg::OnMyNewMap)
	ON_BN_CLICKED(IDC_BUTTON_FILE_NEW, &CRPGScenarioEditorDlg::OnBnClickedButtonFileNew)
	//ON_NOTIFY(HDN_ITEMCLICK, 0, &CRPGScenarioEditorDlg::OnHdnItemclickListElement)
	//ON_NOTIFY(LVN_HOTTRACK, IDC_LIST_ELEMENT, &CRPGScenarioEditorDlg::OnLvnHotTrackListElement)
	//ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_ELEMENT, &CRPGScenarioEditorDlg::OnLvnColumnclickListElement)
	//ON_NOTIFY(HDN_ITEMCHANGED, 0, &CRPGScenarioEditorDlg::OnHdnItemchangedListElement)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ELEMENT, &CRPGScenarioEditorDlg::OnNMClickListElement)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CRPGScenarioEditorDlg::OnBnClickedButtonDel)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_ADD_ELEMENT, &CRPGScenarioEditorDlg::OnBnClickedButtonAddElement)
	/*ON_BN_CLICKED(IDC_BUTTON3, &CRPGScenarioEditorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON9, &CRPGScenarioEditorDlg::OnBnClickedButton9)*/
	ON_BN_CLICKED(IDC_BUTTON_FILE_SAVE, &CRPGScenarioEditorDlg::OnBnClickedButtonFileSave)
	ON_MESSAGE(MY_LOADMAP, &CRPGScenarioEditorDlg::OnMyLoadMap)
	ON_BN_CLICKED(IDC_BUTTON_FILE_LOAD, &CRPGScenarioEditorDlg::OnBnClickedButtonFileLoad)
	ON_BN_CLICKED(IDC_CHECK3, &CRPGScenarioEditorDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON_REFLASH_MAP, &CRPGScenarioEditorDlg::OnBnClickedButtonReflashMap)
	//	ON_WM_KEYDOWN()
	ON_NOTIFY(NM_CLICK, IDC_LIST_MAP_ELEMENT, &CRPGScenarioEditorDlg::OnNMClickListMapElement)
	ON_WM_HOTKEY()
	ON_MESSAGE(MY_TRIGGER_CHANGE, &CRPGScenarioEditorDlg::OnMyTriggerChange)
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CRPGScenarioEditorDlg::OnNMClickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &CRPGScenarioEditorDlg::OnNMClickList3)

	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_BUTTON8, &CRPGScenarioEditorDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CRPGScenarioEditorDlg ��Ϣ�������

BOOL CRPGScenarioEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	MyInit();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRPGScenarioEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		PaintElement();
		switch (paintType)
		{
		case 0:PaintMap(); break;
		case 1:PaintMap_AddElement(); break;
		case 2:PaintMap_ChangeElement(); break;
		case 3:RepaintMap(); break;
		}

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRPGScenarioEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�򿪴����༭��
void CRPGScenarioEditorDlg::OnBnClickedButton1()
{
	if (hasCreatMap == false)
	{
		AfxMessageBox(L"�����½���ͼ��");
		return;
	}

	int iWidth = GetSystemMetrics(SM_CXSCREEN);//��Ļ���
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//��Ļ�߶�
	CRect rect;

	//����δ����
	if (dlgTriggerEditor.GetSafeHwnd() == 0)
		dlgTriggerEditor.Create(IDD_DIALOG_TRIGGER_EDIT);


	dlgTriggerEditor.GetWindowRect(rect);

	//������ʾ
	dlgTriggerEditor.MoveWindow(
		(iWidth - rect.Width()) / 2,
		(iHeight - rect.Height()) / 2,
		rect.Width(),
		rect.Height()
	);

	dlgTriggerEditor.ShowWindow(SW_SHOW);
	gv->isTriggerEditorShow = true;


	//�򴥷����༭��������Ϣ

	if (nowMousePointElementIndex != -1)
	{
		CString temp;
		temp.Format(L"%d", nowMousePointElementIndex);
		gv->nowChooesElementInfo = temp + L"," + m_listMapElement.GetItemText(nowMousePointElementIndex, 1) + L"," + m_listMapElement.GetItemText(nowMousePointElementIndex, 2);

		temp.Format(L"%d,%d", gv->gameMap.gameMapElements[nowMousePointElementIndex].x, gv->gameMap.gameMapElements[nowMousePointElementIndex].y);
		gv->nowChooesElementInfo = gv->nowChooesElementInfo + L"," + temp;

		gv->nowChooesElementTriggerScript = gv->gameMap.gameMapElements[nowMousePointElementIndex].params;

		dlgTriggerEditor.PostMessageW(MY_CHOOES_CHANGE, 0, 0);
	}


}

//������ߵ�ͼԪ���б��е�Ԫ��
void CRPGScenarioEditorDlg::PaintElement()
{
	//�쳣���
	if (nowImageIndex < 0 || nowElementChoose == -1 || m_list.GetItemCount() == 0)
	{
		return;
	}

	//��䱳��
	pElementImageMemoryDC->FillSolidRect(0, 0, elementDrawRect.Width(), elementDrawRect.Height(), 13160660);

	//�������ͻ��Ʋ�ͬ��ͼƬ
	if (nowIsElementStatic)
	{
		//�ж��Ƿ���Ҫ����ͼƬ
		if (nowIsElementZoom)
		{
			//���͸�����Ż���һ��ͼƬ��MaskBlt��
			gv->imageLoader->srcImages[nowSrcImageIndex].img.StretchBlt(
				*pElementImageMemoryDC,
				0, 0,
				elementDrawRect.Width(),
				elementDrawRect.Height(),
				gv->imageLoader->staticElementImages[nowImageIndex].x,
				gv->imageLoader->staticElementImages[nowImageIndex].y,
				gv->imageLoader->staticElementImages[nowImageIndex].w,
				gv->imageLoader->staticElementImages[nowImageIndex].h,
				SRCCOPY
			);
		}
		else
		{
			//�ж��Ƿ���͸��ɫ
			if (gv->imageLoader->staticElementImages[nowImageIndex].color != -1)
			{
				gv->imageLoader->srcImages[nowSrcImageIndex].img.TransparentBlt(
					*pElementImageMemoryDC,
					nowElementDrawX, nowElementDrawY,
					gv->imageLoader->staticElementImages[nowImageIndex].w,
					gv->imageLoader->staticElementImages[nowImageIndex].h,
					gv->imageLoader->staticElementImages[nowImageIndex].x,
					gv->imageLoader->staticElementImages[nowImageIndex].y,
					gv->imageLoader->staticElementImages[nowImageIndex].w,
					gv->imageLoader->staticElementImages[nowImageIndex].h,
					gv->imageLoader->staticElementImages[nowImageIndex].color
				);
			}
			else
			{
				gv->imageLoader->srcImages[nowSrcImageIndex].img.BitBlt(
					*pElementImageMemoryDC,
					nowElementDrawX, nowElementDrawY,
					gv->imageLoader->staticElementImages[nowImageIndex].w,
					gv->imageLoader->staticElementImages[nowImageIndex].h,
					gv->imageLoader->staticElementImages[nowImageIndex].x,
					gv->imageLoader->staticElementImages[nowImageIndex].y,
					SRCCOPY
				);
			}
		}
	}
	else
	{
		//�ж��Ƿ���Ҫ����ͼƬ
		if (nowIsElementZoom)
		{
			gv->imageLoader->srcImages[nowSrcImageIndex].img.StretchBlt(
				*pElementImageMemoryDC,
				0, 0,
				elementDrawRect.Width(),
				elementDrawRect.Height(),
				nowElementImagePoint[nowPlayIndex].x,
				nowElementImagePoint[nowPlayIndex].y,
				gv->imageLoader->dynamicElementImages[nowImageIndex].w,
				gv->imageLoader->dynamicElementImages[nowImageIndex].h,
				SRCCOPY
			);
		}
		else
		{
			//�ж��Ƿ���͸��ɫ
			if (gv->imageLoader->dynamicElementImages[nowImageIndex].color != -1)
			{
				gv->imageLoader->srcImages[nowSrcImageIndex].img.TransparentBlt(
					*pElementImageMemoryDC,
					nowElementDrawX, nowElementDrawY,
					gv->imageLoader->dynamicElementImages[nowImageIndex].w,
					gv->imageLoader->dynamicElementImages[nowImageIndex].h,
					nowElementImagePoint[nowPlayIndex].x,
					nowElementImagePoint[nowPlayIndex].y,
					gv->imageLoader->dynamicElementImages[nowImageIndex].w,
					gv->imageLoader->dynamicElementImages[nowImageIndex].h,
					gv->imageLoader->dynamicElementImages[nowImageIndex].color
				);
			}
			else
			{
				gv->imageLoader->srcImages[nowSrcImageIndex].img.BitBlt(
					*pElementImageMemoryDC,
					nowElementDrawX, nowElementDrawY,
					gv->imageLoader->dynamicElementImages[nowImageIndex].w,
					gv->imageLoader->dynamicElementImages[nowImageIndex].h,
					nowElementImagePoint[nowPlayIndex].x,
					nowElementImagePoint[nowPlayIndex].y,
					SRCCOPY
				);
			}
		}
	}

	pElementImageDC->BitBlt(0, 0, elementDrawRect.Width(), elementDrawRect.Height(), pElementImageMemoryDC, 0, 0, SRCCOPY);

}

//�����ListCtrl��ѡ��ı�
void CRPGScenarioEditorDlg::OnElementSelectChange(int index)
{
	
	if (index == -1)
	{
		return;
	}
	nowElementChoose = index;
	static int lastIndex = -1;
	if (lastIndex == index)
	{
		return;//ѡ�����Ŀû�иı�
	}
	else
	{
		lastIndex = index;//ѡ�����Ŀ�����˸ı�
	}
	

	//��ʼ����������ݺ�ֹͣ���Ŷ���
	nowElementImagePoint.RemoveAll();
	KillTimer(1);

	//����1����ȡ��ǰѡ������������Ӧ������
	CString nowID = m_list.GetItemText(index, 1);//��ǰѡ�����ID
	CString imgID;//��ǰѡ��Ԫ�ص�ͼƬID 
	nowIsElementStatic = m_list.GetItemText(index, 2) == L"��̬" ? true : false;
	nowImageIndex = -1;
	if (nowIsElementStatic)
	{
		for (int i = 0; i < gv->imageLoader->staticElementImages.GetCount(); i++)
		{
			if (nowID == gv->imageLoader->staticElementImages[i].id)
			{
				nowImageIndex = i;
				imgID = gv->imageLoader->staticElementImages[i].imgID;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < gv->imageLoader->dynamicElementImages.GetCount(); i++)
		{
			if (nowID == gv->imageLoader->dynamicElementImages[i].id)
			{
				nowImageIndex = i;
				imgID = gv->imageLoader->dynamicElementImages[i].imgID;
				break;
			}
		}
	}

	//����2������ͼƬID������
	nowSrcImageIndex = -1;
	for (int i = 0; i < gv->imageLoader->srcImages.GetCount(); i++)
	{
		if (imgID == gv->imageLoader->srcImages[i].imgID)
		{
			nowSrcImageIndex = i;
			break;
		}
	}

	//����3���Զ�̬ͼƬ���з���
	if (nowIsElementStatic == false)
	{
		nowElementImagePoint.RemoveAll();
		nowPlayIndex = -1;

		EasyText et;
		CStringArray imageGroup;

		et.DivideText(gv->imageLoader->dynamicElementImages[nowImageIndex].imageGroups, L";", imageGroup);

		//�ж��Ƿ��Զ����ţ��Զ����ŵĻ���ʹ��autoPlay��ָ���Tag���������defaultTag��
		if (gv->imageLoader->dynamicElementImages[nowImageIndex].autoPlay != L"" &&
			gv->imageLoader->dynamicElementImages[nowImageIndex].autoPlay != L"null"
			)
		{
			for (int i = 0; i < imageGroup.GetCount(); i++)
			{
				if (imageGroup[i].Find(gv->imageLoader->dynamicElementImages[nowImageIndex].autoPlay) != -1)
				{
					CStringArray points;
					et.DivideText(et.Right(imageGroup.GetAt(i), L"="), L"/", points);
					for (int j = 0; j < points.GetCount(); j++)
					{
						nowElementImagePoint.Add(CPoint{
						_ttoi(et.Left(points.GetAt(j),L",")),
						_ttoi(et.Right(points.GetAt(j),L","))
						});
					}
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < imageGroup.GetCount(); i++)
			{
				if (imageGroup[i].Find(gv->imageLoader->dynamicElementImages[nowImageIndex].defalutTag) != -1)
				{
					CStringArray points;
					et.DivideText(et.Right(imageGroup.GetAt(i), L"="), L"/", points);

					for (int j = 0; j < points.GetCount(); j++)
					{
						nowElementImagePoint.Add(CPoint{
							_ttoi(et.Left(points.GetAt(j),L",")),
							_ttoi(et.Right(points.GetAt(j),L","))
						});
					}
					break;
				}
			}
		}
		if (nowElementImagePoint.GetCount() != 0)
		{
			nowPlayIndex = 0;//���ò���λ��Ϊ��һ֡
		}

	}

	//����4�������ͼƬ�Ļ���λ��
	nowElementDrawX;
	nowElementDrawY;

	if (elementDrawRect.Width() < gv->imageLoader->staticElementImages[nowImageIndex].w ||
		elementDrawRect.Height() < gv->imageLoader->staticElementImages[nowImageIndex].h)
	{
		nowIsElementZoom = true;//��Ҫ������ʾ
	}
	else
	{
		nowIsElementZoom = false;//����Ҫ������ʾ

		nowElementDrawX = (elementDrawRect.Width() - gv->imageLoader->staticElementImages[nowImageIndex].w) / 2;
		nowElementDrawY = (elementDrawRect.Height() - gv->imageLoader->staticElementImages[nowImageIndex].h) / 2;
	}

	//����5����ʾԪ�ص���Ϣ
	if (nowIsElementStatic)
	{
		SetDlgItemText(IDC_STATIC_ELEMENT_ID, nowID + L" (" + imgID + L")");
		CString temp;
		temp.Format(L"w:%d , h:%d", gv->imageLoader->staticElementImages[nowImageIndex].w, gv->imageLoader->staticElementImages[nowImageIndex].h);
		SetDlgItemText(IDC_STATIC_ELEMENT_INFO, temp);

		m_checkElementCanPass.SetCheck(gv->imageLoader->staticElementImages[nowImageIndex].canPass ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		SetDlgItemText(IDC_STATIC_ELEMENT_ID, nowID + L" (" + imgID + L")");
		CString temp;
		temp.Format(L"w:%d , h:%d", gv->imageLoader->dynamicElementImages[nowImageIndex].w, gv->imageLoader->dynamicElementImages[nowImageIndex].h);
		SetDlgItemText(IDC_STATIC_ELEMENT_INFO, temp);
		m_checkElementCanPass.SetCheck(gv->imageLoader->dynamicElementImages[nowImageIndex].canPass ? BST_CHECKED : BST_UNCHECKED);
	}

	//����6���������Ŷ���ʱ��
	if (nowIsElementStatic == false)
	{
		if (gv->imageLoader->dynamicElementImages[nowImageIndex].interval != 0)
		{
			SetTimer(1, gv->imageLoader->dynamicElementImages[nowImageIndex].interval, NULL);
		}
	}

	//����7���ػ�����ͼλ��
	pElementImageDC->FillSolidRect(0, 0, elementDrawRect.Width(), elementDrawRect.Height(), 0);
	PaintElement();
	//InvalidateRect(elementDrawRect);

	//�ж��Ƿ��������Ԫ��
	if (isAddMapElement == true)
	{
		AddMapElementCancel();
		AddMapElementStart(nowID, m_list.GetItemText(index, 2));
	}
}

//��ʱ��_ѡ����һ��ͼƬ���������½�����ͼ�Ĳ���ͼƬ��
void CRPGScenarioEditorDlg::TimerDynamicNextImage()
{
	nowPlayIndex++;
	if (nowPlayIndex > gv->imageLoader->dynamicElementImages.GetCount())
	{
		nowPlayIndex = 0;//ѭ������
	}

	//�ػ�Ԫ������ͼ
	PaintElement();
}

//�½���ͼ
void CRPGScenarioEditorDlg::CreatMap()
{
	//�쳣���
	if (gv->gameMap.GetMapHeigth() == 0 || gv->gameMap.GetMapWidth() == 0)
	{
		AfxMessageBox(L"�½���ͼ���ִ��󣺵�ͼ�Ŀ�Ȼ�߶�Ϊ0��");
		exit(-1);
	}
	//����Ƿ������ڱ༭�ĵ�ͼ
	if (hasCloseMap == false)
		CloseMap();
	hasCreatMap = false;


	//������ʼ��
	isShowGrid = true;				//�ر���ʾ����
	selectIndex = -1;				//û��ѡ��Ԫ��

	isAddMapElement = false;		//�������Ԫ�� = false
	willAddElementSrcIndex = -1;
	willAddElementIndex = -1;

	isChangeMapElement = false;		//�����޸�Ԫ��λ�� = false
	willChangeElementSrcIndex = -1;
	willChangeElementIndex = -1;

	ignoreIndex = -1;				//��ͼ���ƺ������� = -1
	nowMousePointElementIndex = -1;	//��ͼѡԪ������ = -1

	//��ͼ����ʼ��
	if (mapDC == NULL)
		mapDC = m_map.GetDC();

	m_map.GetClientRect(mapElementShowRect);//��ʾ�����ľ���
	mapElementRect.SetRect(0, 0, gv->gameMap.GetMapWidth(), gv->gameMap.GetMapHeigth());//������ͼ����

	//��ͼ�����ʼ��
	mapMemoryDC = new CDC();
	mapMemoryDC->CreateCompatibleDC(NULL);

	bmpMap.DeleteObject();
	bmpMap.CreateBitmap(gv->gameMap.GetMapWidth(), gv->gameMap.GetMapHeigth(), 1, 32, NULL);


	//����ʾ��ʹ�����������봴����λͼ������λɫ�ʣ����ڰ׵ġ�
	//bmpMap.CreateCompatibleBitmap(mapMemoryDC, mapElementRect.Width(), mapElementRect.Height());

	CBitmap * oldBitmap = mapMemoryDC->SelectObject(&bmpMap);
	oldBitmap->DeleteObject();//����ɻ���
	mapMemoryDC->FillSolidRect(0, 0, mapElementRect.Width(), mapElementRect.Height(), RGB(255, 255, 255));//��䱳��Ϊ��ɫ



	//��ʾ�����ͼ�����ʼ��
	mapShowMemoryDC = new CDC();
	mapShowMemoryDC->CreateCompatibleDC(NULL);
	bmpShowMap.DeleteObject();
	bmpShowMap.CreateBitmap(mapElementShowRect.Width(), mapElementShowRect.Height(), 1, 32, NULL);

	//����ʾ��ʹ�����������봴����λͼ������λɫ�ʣ����ڰ׵ġ�
	//bmpShowMap.CreateCompatibleBitmap(mapShowMemoryDC, mapElementShowRect.Width(), mapElementShowRect.Height());

	oldBitmap = mapShowMemoryDC->SelectObject(&bmpShowMap);
	oldBitmap->DeleteObject();//����ɻ���


	//���������
	m_scrollBarX.SetScrollPos(0);
	m_scrollBarY.SetScrollPos(0);
	CalculateScrollBar(mapElementShowRect.Width(),mapElementShowRect.Height());

	//ˢ���ػ�
	paintType = 0;
	RepaintMap();
	PaintMap();
	hasCreatMap = true;//�½���ͼ���
}

//�رյ�ͼ
void CRPGScenarioEditorDlg::CloseMap()
{
	if (hasCloseMap)
	{
		return;
	}



	mapMemoryDC->DeleteDC();
	mapShowMemoryDC->DeleteDC();

	bmpMap.DeleteObject();
	bmpShowMap.DeleteObject();

	hasCloseMap = true;
}

//���������
void CRPGScenarioEditorDlg::CalculateScrollBar(int cx, int cy)
{
	if (m_map.GetSafeHwnd() == 0)
		return;

	//���¼����ͼ��ʾ����Ĵ�С
	int showX, showY;//��¼��ʾλ�õ�x��y����
	showX = mapElementShowRect.left;
	showY = mapElementShowRect.top;
	//m_map.GetClientRect(mapElementShowRect);//��ʾ�����ľ���
	mapElementShowRect.SetRect(showX, showY, cx, cy);


	//���¼���������ľ��ο�
	SCROLLINFO scrollInfo;

	//����ˮƽ������
	scrollInfo.fMask = SIF_RANGE || SIF_PAGE;
	scrollInfo.nMin = 0;
	scrollInfo.nPage = 1;

	//�жϸ߶��Ƿ񳬳���Χ
	if (mapElementRect.Height() > mapElementShowRect.Height())
	{
		//�ж��Ƿ�������
		if ((mapElementRect.Height() - mapElementShowRect.Height()) % scrollBarPerChange == 0)
			scrollInfo.nMax = (mapElementRect.Height() - mapElementShowRect.Height()) / scrollBarPerChange;
		else
			scrollInfo.nMax = int((mapElementRect.Height() - mapElementShowRect.Height()) / scrollBarPerChange) + 1;
	}
	else
	{
		scrollInfo.nMax = 0;
	}
	m_scrollBarY.SetScrollInfo(&scrollInfo, true);


	//���㴹ֱ������
	scrollInfo.fMask = SIF_RANGE || SIF_PAGE;
	scrollInfo.nMin = 0;
	scrollInfo.nPage = 1;
	//�жϸ߶��Ƿ񳬳���Χ
	if (mapElementRect.Width() > mapElementShowRect.Width())
	{
		//�ж��Ƿ�������
		if ((mapElementRect.Width() - mapElementShowRect.Width()) % scrollBarPerChange == 0)
			scrollInfo.nMax = (mapElementRect.Width() - mapElementShowRect.Width()) / scrollBarPerChange;
		else
			scrollInfo.nMax = int((mapElementRect.Width() - mapElementShowRect.Width()) / scrollBarPerChange) + 1;
	}
	else
	{
		scrollInfo.nMax = 0;
	}
	m_scrollBarX.SetScrollInfo(&scrollInfo, true);
}

//��ͼ����������λ�ñ��ı�
void CRPGScenarioEditorDlg::OnMapScrollValueChange(bool vertical)
{
	if (mapElementShowRect.Width() < mapElementRect.Width() && vertical == false)
	{
		mapElementShowRect.SetRect(
			m_scrollBarX.GetScrollPos() * scrollBarPerChange,
			mapElementShowRect.top,
			m_scrollBarX.GetScrollPos() * scrollBarPerChange + mapElementShowRect.Width(),
			mapElementShowRect.top + mapElementShowRect.Height());

		PaintMap();
		return;
	}

	if (mapElementShowRect.Height() < mapElementRect.Height() && vertical == true)
	{
		mapElementShowRect.SetRect(
			mapElementShowRect.left,
			m_scrollBarY.GetScrollPos() * scrollBarPerChange,
			mapElementShowRect.left + mapElementShowRect.Width(),
			m_scrollBarY.GetScrollPos() * scrollBarPerChange + mapElementShowRect.Height());

		PaintMap();
		return;
	}

}

//��ͨ��ͼ
void CRPGScenarioEditorDlg::PaintMap()
{
	//�쳣���
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	//����1����mapMemoryDC��ȡ������Ƶ�mapShowMemoryDC��
	mapShowMemoryDC->BitBlt(
		0,
		0,
		mapElementShowRect.Width(),
		mapElementShowRect.Height(),
		mapMemoryDC,
		mapElementShowRect.left,
		mapElementShowRect.top,
		SRCCOPY
	);

	//����2����������
	if (isShowGrid)
	{
		PaintGird();
	}

	//����3������ѡ������
	if (nowMousePointElementIndex != -1)
	{
		PaintFocusGrid(nowMousePointElementIndex);
	}

	//����4����mapDC�ϻ���mapMemoryDC
	mapDC->BitBlt(0, 0, mapElementShowRect.Width(), mapElementShowRect.Height(), mapShowMemoryDC, 0, 0, SRCCOPY);

}

//���Ԫ��ʱ�Ļ�ͼ
void CRPGScenarioEditorDlg::PaintMap_AddElement()
{
	//�쳣���
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	if (willAddElementSrcIndex == -1 || willAddElementIndex == -1)
		return;

	if (paintType != 1)
		return;

	//����1����mapMemoryDC��ȡ������Ƶ�mapShowMemoryDC��
	mapShowMemoryDC->BitBlt(
		0,
		0,
		mapElementShowRect.Width(),
		mapElementShowRect.Height(),
		mapMemoryDC,
		mapElementShowRect.left,
		mapElementShowRect.top,
		SRCCOPY
	);

	//����2��������ʱͼ��

	//���ĵ��ͼ�������������ָλ��ʱ��ǰ��ͼƬ�����ĵ�λ�ã������Ҫ�������ͼƬ�����Ͻ�λ�ã�
	int drawX, drawY;//���Ͻ�����

	if (willAddElementType == L"��̬")
	{

		//������
		if (isShowGrid)
		{
			//drawX = (girdWidth + 1) * int((mouseInMapPoint.x) / (girdWidth + 1));
			//drawY = (girdHeigth + 1)* int((mouseInMapPoint.y) / (girdHeigth + 1));

			drawX = girdWidth * int((mouseInMapPoint.x + mapElementShowRect.left) / girdWidth) - mapElementShowRect.left;
			drawY = girdHeigth * int((mouseInMapPoint.y + mapElementShowRect.top) / girdHeigth) - mapElementShowRect.top;

		}
		else
		{
			drawX = mouseInMapPoint.x - gv->imageLoader->staticElementImages[willAddElementIndex].w / 2;
			drawY = mouseInMapPoint.y - gv->imageLoader->staticElementImages[willAddElementIndex].h / 2;
		}


		if (gv->imageLoader->staticElementImages[willAddElementIndex].color != -1)
		{
			gv->imageLoader->srcImages[willAddElementSrcIndex].img.TransparentBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				gv->imageLoader->staticElementImages[willAddElementIndex].w,
				gv->imageLoader->staticElementImages[willAddElementIndex].h,
				gv->imageLoader->staticElementImages[willAddElementIndex].x,
				gv->imageLoader->staticElementImages[willAddElementIndex].y,
				gv->imageLoader->staticElementImages[willAddElementIndex].w,
				gv->imageLoader->staticElementImages[willAddElementIndex].h,
				gv->imageLoader->staticElementImages[willAddElementIndex].color
			);
		}
		else
		{
			gv->imageLoader->srcImages[willAddElementSrcIndex].img.BitBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				gv->imageLoader->staticElementImages[willAddElementIndex].w,
				gv->imageLoader->staticElementImages[willAddElementIndex].h,
				srcX, srcY, SRCCOPY);
		}


	}
	else
	{
		//������
		if (isShowGrid)
		{
			drawX = girdWidth * int((mouseInMapPoint.x) / girdWidth);
			drawY = girdHeigth* int((mouseInMapPoint.y) / girdHeigth);
		}
		else
		{
			drawX = mouseInMapPoint.x - gv->imageLoader->dynamicElementImages[willAddElementIndex].w / 2;
			drawY = mouseInMapPoint.y - gv->imageLoader->dynamicElementImages[willAddElementIndex].h / 2;
		}



		if (gv->imageLoader->dynamicElementImages[willAddElementIndex].color != -1)
		{
			gv->imageLoader->srcImages[willAddElementSrcIndex].img.TransparentBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].w,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].h,
				srcX, srcY,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].w,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].h,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].color
			);
		}
		else
		{
			gv->imageLoader->srcImages[willAddElementSrcIndex].img.BitBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].w,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].h,
				srcX, srcY, SRCCOPY);
		}
	}


	//����3����������
	if (isShowGrid)
	{
		PaintGird();
	}



	//����4������ѡ������
	if (nowMousePointElementIndex != -1)
	{
		PaintFocusGrid(nowMousePointElementIndex);
	}

	mapDC->BitBlt(0, 0, mapElementShowRect.Width(), mapElementShowRect.Height(), mapShowMemoryDC, 0, 0, SRCCOPY);

}

//�޸�Ԫ��λ��ʱ�Ļ�ͼ
void CRPGScenarioEditorDlg::PaintMap_ChangeElement()
{
	//�쳣���
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	if (willChangeElementSrcIndex == -1 || willChangeElementIndex == -1)
		return;

	if (paintType != 2)
		return;



	//����1����mapMemoryDC��ȡ������Ƶ�mapShowMemoryDC��
	mapShowMemoryDC->BitBlt(
		0,
		0,
		mapElementShowRect.Width(),
		mapElementShowRect.Height(),
		mapMemoryDC,
		mapElementShowRect.left,
		mapElementShowRect.top,
		SRCCOPY
	);


	//���Ʊ�ѡ������ͼƬ
	int drawX, drawY;//���Ͻ�����
	int drawW, drawH;//��Ⱥ͸߶�
	if (isShowGrid)
	{
		drawX = girdWidth * int((mouseInMapPoint.x + mapElementShowRect.left) / girdWidth) - mapElementShowRect.left;
		drawY = girdHeigth * int((mouseInMapPoint.y + mapElementShowRect.top) / girdHeigth) - mapElementShowRect.top;


		//drawX = girdWidth * int(mouseInMapPoint.x / girdWidth);
		//drawY = girdHeigth* int(mouseInMapPoint.y / girdHeigth);
	}
	else
	{
		drawX = mouseInMapPoint.x - offsetX;
		drawY = mouseInMapPoint.y - offsetY;
	}

	if (willChangeElementType == L"��̬")
	{
		drawW = gv->imageLoader->staticElementImages[willChangeElementIndex].w;
		drawH = gv->imageLoader->staticElementImages[willChangeElementIndex].h;

		if (gv->imageLoader->staticElementImages[willChangeElementIndex].color != -1)
		{
			gv->imageLoader->srcImages[willChangeElementSrcIndex].img.TransparentBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				gv->imageLoader->staticElementImages[willChangeElementIndex].w,
				gv->imageLoader->staticElementImages[willChangeElementIndex].h,
				gv->imageLoader->staticElementImages[willChangeElementIndex].x,
				gv->imageLoader->staticElementImages[willChangeElementIndex].y,
				drawW,
				drawH,
				gv->imageLoader->staticElementImages[willChangeElementIndex].color
			);
		}
		else
		{
			gv->imageLoader->srcImages[willChangeElementSrcIndex].img.BitBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				drawW, drawH,
				srcX, srcY, SRCCOPY);
		}


	}
	else
	{
		drawW = gv->imageLoader->dynamicElementImages[willChangeElementIndex].w;
		drawH = gv->imageLoader->dynamicElementImages[willChangeElementIndex].h;
		if (gv->imageLoader->dynamicElementImages[willChangeElementIndex].color != -1)
		{
			gv->imageLoader->srcImages[willChangeElementSrcIndex].img.TransparentBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				drawW, drawH,
				srcX, srcY,
				drawW, drawH,
				gv->imageLoader->dynamicElementImages[willChangeElementIndex].color
			);
		}
		else
		{
			gv->imageLoader->srcImages[willChangeElementSrcIndex].img.BitBlt(
				*mapShowMemoryDC,
				drawX, drawY,
				drawW, drawH,
				srcX, srcY, SRCCOPY);
		}
	}


	//��������
	if (isShowGrid)
	{
		PaintGird();
	}

	//����ѡ������
	if (nowMousePointElementIndex != -1)
	{
		PaintFocusGrid(nowMousePointElementIndex);
	}

	//�����ƶ�����ľ���
	PaintOuterRect(
		mapShowMemoryDC,
		drawX, drawY,
		drawW, drawH,
		PS_SOLID,
		2,
		RGB(0, 0, 255)
	);

	mapDC->BitBlt(0, 0, mapElementShowRect.Width(), mapElementShowRect.Height(), mapShowMemoryDC, 0, 0, SRCCOPY);
}

//�ػ��ͼ���ػ��ͼֻ�ǻ������ڴ������ϣ���û��������ʾ��ͼ������
void CRPGScenarioEditorDlg::RepaintMap()
{
	//�쳣���
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	//����1���ñ������������ͼ
	mapMemoryDC->FillSolidRect(mapElementRect, RGB(255, 255, 255));

	//����2��������Ԫ�ػ����ڵ�ͼ��
	int srcIndex;//ͼƬ�ز�����
	int index;//Ԫ������

	for (int i = 0; i < gv->gameMap.gameMapElements.GetCount(); i++)
	{
		if (ignoreIndex == i)
		{
			continue;
		}
		if (gv->gameMap.gameMapElements[i].type == L"��̬")
		{
			//�Ӿ�̬ͼƬ���в�������
			index = -1;
			for (int j = 0; j < gv->imageLoader->staticElementImages.GetCount(); j++)
			{
				if (gv->imageLoader->staticElementImages[j].id == gv->gameMap.gameMapElements[i].id)
				{
					index = j;
					break;
				}
			}

			//��ͼƬ�ز����ҵ�����
			srcIndex = -1;
			for (int j = 0; j < gv->imageLoader->srcImages.GetCount(); j++)
			{
				if (gv->imageLoader->staticElementImages[index].imgID == gv->imageLoader->srcImages[j].imgID)
				{
					srcIndex = j;
					break;
				}
			}

			//����Ԫ��ͼƬ
			if (gv->imageLoader->staticElementImages[index].color != -1)//��͸��ɫ
			{
				gv->imageLoader->srcImages[srcIndex].img.TransparentBlt(
					*mapMemoryDC,
					gv->gameMap.gameMapElements[i].x,
					gv->gameMap.gameMapElements[i].y,
					gv->imageLoader->staticElementImages[index].w,
					gv->imageLoader->staticElementImages[index].h,
					gv->imageLoader->staticElementImages[index].x,
					gv->imageLoader->staticElementImages[index].y,
					gv->imageLoader->staticElementImages[index].w,
					gv->imageLoader->staticElementImages[index].h,
					gv->imageLoader->staticElementImages[index].color
				);
			}
			else//��͸��ɫ
			{
				gv->imageLoader->srcImages[srcIndex].img.BitBlt(
					*mapMemoryDC,
					gv->gameMap.gameMapElements[i].x,
					gv->gameMap.gameMapElements[i].y,
					gv->imageLoader->staticElementImages[index].w,
					gv->imageLoader->staticElementImages[index].h,
					gv->imageLoader->staticElementImages[index].x,
					gv->imageLoader->staticElementImages[index].y,
					SRCCOPY
				);
			}
		}
		else
		{
			//�Ӷ�̬ͼƬ���в�������
			index = -1;
			for (int j = 0; j < gv->imageLoader->dynamicElementImages.GetCount(); j++)
			{
				if (gv->imageLoader->dynamicElementImages[j].id == gv->gameMap.gameMapElements[i].id)
				{
					index = j;
					break;
				}
			}




			//��ͼƬ�ز����ҵ�����
			srcIndex = -1;
			for (int j = 0; j < gv->imageLoader->srcImages.GetCount(); j++)
			{
				if (gv->imageLoader->dynamicElementImages[index].imgID == gv->imageLoader->srcImages[j].imgID)
				{
					srcIndex = j;
					break;
				}
			}

			//�����front�еĵ�һ��ͼƬ��λ��
			EasyText et;
			int tempX, tempY;
			CStringArray divide;
			CStringArray divide1;
			et.DivideText(gv->imageLoader->dynamicElementImages[index].imageGroups, L";", divide);

			//�ж��Ƿ��Զ�����
			if (gv->imageLoader->dynamicElementImages[index].autoPlay == L"" ||
				gv->imageLoader->dynamicElementImages[index].autoPlay == L"null"
				)
			{
				//ʹ��default�ı�־
				for (int j = 0; j < divide.GetCount(); j++)
				{
					if (divide[j].Find(gv->imageLoader->dynamicElementImages[index].defalutTag) != -1)
					{
						if (divide[j].Find(L"/") == -1)//ֻ��һ��ͼƬ�ز�
							divide1.Add(et.Right(divide[j], L"="));
						else
							et.DivideText(et.Right(divide[j], L"="), L"/", divide1);
						break;
					}
				}
			}
			else
			{
				//ʹ��autoplay�ı�־
				for (int j = 0; j < divide.GetCount(); j++)
				{
					if (divide[j].Find(gv->imageLoader->dynamicElementImages[index].autoPlay) != -1)
					{
						if (divide[j].Find(L"/") == -1)//ֻ��һ��ͼƬ�ز�
							divide1.Add(et.Right(divide[j], L"="));
						else
							et.DivideText(et.Right(divide[j], L"="), L"/", divide1);
						break;
					}
				}
			}
			tempX = _ttoi(et.Left(divide1.GetAt(0), L","));
			tempY = _ttoi(et.Right(divide1.GetAt(0), L","));

			//����Ԫ��ͼƬ
			if (gv->imageLoader->dynamicElementImages[index].color != -1)//��͸��ɫ
			{
				gv->imageLoader->srcImages[srcIndex].img.TransparentBlt(
					*mapMemoryDC,
					gv->gameMap.gameMapElements[i].x,
					gv->gameMap.gameMapElements[i].y,
					gv->imageLoader->dynamicElementImages[index].w,
					gv->imageLoader->dynamicElementImages[index].h,
					tempX, tempY,
					gv->imageLoader->dynamicElementImages[index].w,
					gv->imageLoader->dynamicElementImages[index].h,
					gv->imageLoader->dynamicElementImages[index].color
				);
			}
			else//��͸��ɫ
			{
				gv->imageLoader->srcImages[srcIndex].img.BitBlt(
					*mapMemoryDC,
					gv->gameMap.gameMapElements[i].x,
					gv->gameMap.gameMapElements[i].y,
					gv->imageLoader->dynamicElementImages[index].w,
					gv->imageLoader->dynamicElementImages[index].h,
					tempX, tempY,
					SRCCOPY
				);
			}
		}
	}

	//����3�����Ƶ�ͼ�߿�
	mapMemoryDC->MoveTo(0, 0);
	mapMemoryDC->LineTo(mapElementRect.Width(), 0);
	mapMemoryDC->LineTo(mapElementRect.Width(), mapElementRect.Height());
	mapMemoryDC->LineTo(0, mapElementRect.Height());
	mapMemoryDC->MoveTo(0, 0);

	paintType = 0;
}

//��������
void CRPGScenarioEditorDlg::PaintGird()
{

	int nowX, nowY;

	nowX = int(mapElementShowRect.left / girdWidth)*girdWidth;
	nowY = int(mapElementShowRect.top / girdHeigth)*girdHeigth;

	CPen pen;
	pen.CreatePen(PS_DOT, 1, girdColor);
	CPen *oldPen = (CPen*)mapShowMemoryDC->SelectObject(&pen);

	//��������
	while (nowX <= mapElementShowRect.left + mapElementShowRect.Width())
	{
		mapShowMemoryDC->MoveTo(nowX - mapElementShowRect.left, 0);
		mapShowMemoryDC->LineTo(nowX - mapElementShowRect.left, mapElementShowRect.Height());
		nowX = nowX + girdWidth;
	}

	//���ƺ���
	while (nowY <= mapElementShowRect.top + mapElementShowRect.Height())
	{
		mapShowMemoryDC->MoveTo(0, nowY - mapElementShowRect.top);
		mapShowMemoryDC->LineTo(mapElementShowRect.Width(), nowY - mapElementShowRect.top);
		nowY = nowY + girdHeigth;
	}

	mapShowMemoryDC->SelectObject(oldPen);
	DeleteObject(pen);

}

//����ѡ��Ԫ��
void CRPGScenarioEditorDlg::PaintFocusGrid(int index)
{
	if (index == -1)
	{
		return;
	}
	PaintOuterRect(
		mapShowMemoryDC,
		gv->gameMap.gameMapElements[index].x - mapElementShowRect.left,
		gv->gameMap.gameMapElements[index].y - mapElementShowRect.top,
		gv->gameMap.gameMapElements[index].w,
		gv->gameMap.gameMapElements[index].h,
		PS_SOLID,
		2,
		RGB(255, 0, 0)
	);
}

//���ƾ��ε���߿�
void CRPGScenarioEditorDlg::PaintOuterRect(CDC * dc, int x, int y, int w, int h, int penType, int penSize, COLORREF color)
{
	if (dc == NULL)
	{
		return;
	}

	CPen pen;
	pen.CreatePen(penType, penSize, color);
	CPen *oldPen = dc->SelectObject(&pen);

	//Ҫ������߿�
	dc->MoveTo(
		x - penSize,
		y - penSize
	);

	dc->LineTo(
		x + penSize + w,
		y - penSize
	);

	dc->LineTo(
		x + penSize + w,
		y + penSize + h
	);

	dc->LineTo(
		x - penSize,
		y + penSize + h
	);

	dc->LineTo(
		x - penSize,
		y - penSize
	);


	dc->SelectObject(oldPen);
	pen.DeleteObject();


}

//���Ԫ�ؿ�ʼ
void CRPGScenarioEditorDlg::AddMapElementStart(CString id, CString type)
{
	//�ṩ����ӵ�Ԫ�ص�ID��ͼƬID
	//ע�����Ԫ��ListCtrl��˫���¼������������롱��ť����¼�
	//ǰ�᣺isAddMapElement = false
	//������isAddMapElement = true

	if (isAddMapElement != false)
		return;

	willAddElementID = id;
	willAddElementType = type;

	//������ز�������ͼƬ����
	willAddElementIndex = -1;
	willAddElementSrcIndex = -1;
	if (willAddElementType == L"��̬")
	{
		for (int i = 0; i < gv->imageLoader->staticElementImages.GetCount(); i++)
		{
			if (gv->imageLoader->staticElementImages[i].id == willAddElementID)
			{
				willAddElementIndex = i;
				break;
			}
		}
		for (int i = 0; i < gv->imageLoader->srcImages.GetCount(); i++)
		{
			if (gv->imageLoader->srcImages[i].imgID == gv->imageLoader->staticElementImages[willAddElementIndex].imgID)
			{
				willAddElementSrcIndex = i;
				break;
			}
		}
	}
	else//��̬
	{
		for (int i = 0; i < gv->imageLoader->dynamicElementImages.GetCount(); i++)
		{
			if (gv->imageLoader->dynamicElementImages[i].id == willAddElementID)
			{
				willAddElementIndex = i;
				break;
			}
		}
		for (int i = 0; i < gv->imageLoader->srcImages.GetCount(); i++)
		{
			if (gv->imageLoader->srcImages[i].imgID == gv->imageLoader->dynamicElementImages[willAddElementIndex].imgID)
			{
				willAddElementSrcIndex = i;
				break;
			}
		}
	}
	if (willAddElementIndex == -1 || willAddElementSrcIndex == -1)
	{
		AfxMessageBox(L"ͼƬ��Դƥ�����");
		exit(-1);
	}



	//�����Դͼ���x��yλ��
	if (willAddElementType == L"��̬")
	{
		srcX = gv->imageLoader->staticElementImages[willAddElementIndex].x;
		srcY = gv->imageLoader->staticElementImages[willAddElementIndex].y;
	}
	else
	{
		//���Ҷ�̬ͼ�ĵ�һ��ͼƬ
		EasyText et;
		CStringArray divide;
		CStringArray divide1;
		et.DivideText(gv->imageLoader->dynamicElementImages[willAddElementIndex].imageGroups, L";", divide);

		//�ж��Ƿ��Զ�����
		if (gv->imageLoader->dynamicElementImages[willAddElementIndex].autoPlay == L"" ||
			gv->imageLoader->dynamicElementImages[willAddElementIndex].autoPlay == L"null"
			)
		{
			//ʹ��default�ı�־
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willAddElementIndex].defalutTag) != -1)
				{
					if (divide[i].Find(L"/") == -1)//ֻ��һ��ͼƬ�ز�
						divide1.Add(et.Right(divide[i], L"="));
					else
						et.DivideText(et.Right(divide[i], L"="), L"/", divide1);
					break;
				}
			}
		}
		else
		{
			//ʹ��autoplay�ı�־
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willAddElementIndex].autoPlay) != -1)
				{
					if (divide[i].Find(L"/") == -1)//ֻ��һ��ͼƬ�ز�
						divide1.Add(et.Right(divide[i], L"="));
					else
						et.DivideText(et.Right(divide[i], L"="), L"/", divide1);
					break;
				}
			}
		}
		srcX = _ttoi(et.Left(divide1.GetAt(0), L","));
		srcY = _ttoi(et.Right(divide1.GetAt(0), L","));
	}


	/*
	������
	2����PaintMap_AddElement�������ʱͼƬ�Ļ���

	*/



	PaintMap();

	isAddMapElement = true;
}

//���Ԫ����
void CRPGScenarioEditorDlg::AddMapElementNow(int x, int y)
{
	//ע�����λ�øı��¼�
	//ǰ�᣺isAddMapElement = true
	if (isAddMapElement != true)
		return;

	static int lastX = -1, lastY = -1;
	if (lastX != x || lastY != y)
	{
		//���λ�øı�
		lastX = x;
		lastY = y;
		PaintMap_AddElement();
	}

}

//���Ԫ��ȡ��
void CRPGScenarioEditorDlg::AddMapElementCancel()
{
	//ע���м�StaticText����Ҽ�����¼������������롱��ť����¼������Ԫ��ListCtrl����ı��¼�
	//ǰ�᣺isAddMapElement = true
	//������isAddMapElement = false
	if (isAddMapElement != true)
		return;

	willAddElementID = L"";
	willAddElementType = L"";

	willAddElementIndex = -1;
	willAddElementSrcIndex = -1;

	isAddMapElement = false;
}

//���Ԫ�ؽ���
void CRPGScenarioEditorDlg::AddMapElementEnd(int x, int y)
{
	//�ṩ��������ѡ��λ�ã�����ھ�̬�ı���
	//ע������������¼�
	//ǰ�᣺isAddMapElement = true
	//������isAddMapElement = false

	if (isAddMapElement != true)
		return;


	//��ListCtrl�����һ��
	m_listMapElement.InsertItem(m_listMapElement.GetItemCount(), NULL);

	CString temp;
	temp.Format(L"%d", m_listMapElement.GetItemCount());
	m_listMapElement.SetItemText(m_listMapElement.GetItemCount() - 1, 0, temp);
	m_listMapElement.SetItemText(m_listMapElement.GetItemCount() - 1, 1, willAddElementID);
	m_listMapElement.SetItemText(m_listMapElement.GetItemCount() - 1, 2, willAddElementType);

	int addX, addY;
	addX = girdWidth * int((x + mapElementShowRect.left) / girdWidth);
	addY = girdHeigth * int((y + mapElementShowRect.top) / girdHeigth);

	//��ǰ��x��y���Ǹ����������λ��
	if (willAddElementType == L"��̬")
	{
		if (isShowGrid)
		{
			gv->gameMap.AddElement(
				willAddElementID,
				willAddElementType,
				addX, addY,
				gv->imageLoader->staticElementImages[willAddElementIndex].w,
				gv->imageLoader->staticElementImages[willAddElementIndex].h,
				L"");
		}
		else
		{
			gv->gameMap.AddElement(
				willAddElementID,
				willAddElementType,
				x - gv->imageLoader->staticElementImages[willAddElementIndex].w / 2 + mapElementShowRect.left,
				y - gv->imageLoader->staticElementImages[willAddElementIndex].h / 2 + mapElementShowRect.top,
				gv->imageLoader->staticElementImages[willAddElementIndex].w,
				gv->imageLoader->staticElementImages[willAddElementIndex].h,
				L"");
		}

	}
	else
	{
		if (isShowGrid)
		{
			gv->gameMap.AddElement(
				willAddElementID,
				willAddElementType,
				addX, addY,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].w,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].h,
				L"");
		}
		else
		{
			gv->gameMap.AddElement(
				willAddElementID,
				willAddElementType,
				x - gv->imageLoader->dynamicElementImages[willAddElementIndex].w / 2 + mapElementShowRect.left,
				y - gv->imageLoader->dynamicElementImages[willAddElementIndex].h / 2 + mapElementShowRect.top,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].w,
				gv->imageLoader->dynamicElementImages[willAddElementIndex].h,
				L"");
		}

	}


	RepaintMap();
	paintType = 0;
	PaintMap();
	/*
		willAddElementID = L"";
		willAddElementType = L"";

		willAddElementIndex = -1;
		willAddElementSrcIndex = -1;
	*/

	isAddMapElement = false;
}

//�޸�Ԫ��λ�ÿ�ʼ
void CRPGScenarioEditorDlg::ChangeMapElementPositionStart(int index)
{
	//�ṩ���޸ĵ�Ԫ�ص�������ListCtrl�ϵ��±꣩
	//ע�������������¼�
	//ǰ�᣺isChangeMapElement = false
	//������isChangeMapElement = true
	if (isChangeMapElement != false)
		return;
	if (index == -1)
		return;

	//��¼λ��
	ignoreIndex = index;

	//��ListCtrl�л�ȡID��Type
	willChangeElementID = m_listMapElement.GetItemText(index, 1);
	willChangeElementType = m_listMapElement.GetItemText(index, 2);

	//������ز�������ͼƬ����
	willChangeElementIndex = -1;
	willChangeElementSrcIndex = -1;
	if (willChangeElementType == L"��̬")
	{
		for (int i = 0; i < gv->imageLoader->staticElementImages.GetCount(); i++)
		{
			if (gv->imageLoader->staticElementImages[i].id == willChangeElementID)
			{
				willChangeElementIndex = i;
				break;
			}
		}
		for (int i = 0; i < gv->imageLoader->srcImages.GetCount(); i++)
		{
			if (gv->imageLoader->srcImages[i].imgID == gv->imageLoader->staticElementImages[willChangeElementIndex].imgID)
			{
				willChangeElementSrcIndex = i;
				break;
			}
		}
	}
	else//��̬
	{
		for (int i = 0; i < gv->imageLoader->dynamicElementImages.GetCount(); i++)
		{
			if (gv->imageLoader->dynamicElementImages[i].id == willChangeElementID)
			{
				willChangeElementIndex = i;
				break;
			}
		}
		for (int i = 0; i < gv->imageLoader->srcImages.GetCount(); i++)
		{
			if (gv->imageLoader->srcImages[i].imgID == gv->imageLoader->dynamicElementImages[willChangeElementIndex].imgID)
			{
				willChangeElementSrcIndex = i;
				break;
			}
		}
	}
	if (willChangeElementIndex == -1 || willChangeElementSrcIndex == -1)
	{
		AfxMessageBox(L"ͼƬ��Դƥ�����");
		exit(-1);
	}

	//����ö����ͼƬ��Դ�ز�ͼ���x��yλ��
	if (willChangeElementType == L"��̬")
	{
		srcX = gv->imageLoader->staticElementImages[willChangeElementIndex].x;
		srcY = gv->imageLoader->staticElementImages[willChangeElementIndex].y;
	}
	else
	{
		//���Ҷ�̬ͼ�ĵ�һ��ͼƬ
		EasyText et;
		CStringArray divide;
		CStringArray divide1;
		et.DivideText(gv->imageLoader->dynamicElementImages[willChangeElementIndex].imageGroups, L";", divide);

		//�ж��Ƿ��Զ�����
		if (gv->imageLoader->dynamicElementImages[willChangeElementIndex].autoPlay == L"" ||
			gv->imageLoader->dynamicElementImages[willChangeElementIndex].autoPlay == L"null"
			)
		{
			//ʹ��default�ı�־
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willChangeElementIndex].defalutTag) != -1)
				{
					if (divide[i].Find(L"/") == -1)//ֻ��һ��ͼƬ�ز�
						divide1.Add(et.Right(divide[i], L"="));
					else
						et.DivideText(et.Right(divide[i], L"="), L"/", divide1);
					break;
				}
			}
		}
		else
		{
			//ʹ��autoplay�ı�־
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willChangeElementIndex].autoPlay) != -1)
				{
					if (divide[i].Find(L"/") == -1)//ֻ��һ��ͼƬ�ز�
						divide1.Add(et.Right(divide[i], L"="));
					else
						et.DivideText(et.Right(divide[i], L"="), L"/", divide1);
					break;
				}
			}
		}
		srcX = _ttoi(et.Left(divide1.GetAt(0), L","));
		srcY = _ttoi(et.Right(divide1.GetAt(0), L","));
	}

	//��������������ѡ��ͼƬ��λ��
	int a = mouseInMapPoint.x;
	a = mapElementShowRect.left;
	a = gv->gameMap.gameMapElements[index].x;

	offsetX = mouseInMapPoint.x + mapElementShowRect.left - gv->gameMap.gameMapElements[index].x;
	offsetY = mouseInMapPoint.y + mapElementShowRect.top - gv->gameMap.gameMapElements[index].y;

	//�ػ��ͼ
	RepaintMap();
	PaintMap_ChangeElement();

	//�޸Ļ�ͼ����
	paintType = 2;

	 
	isChangeMapElement = true;
}

//�޸�Ԫ��λ����
void CRPGScenarioEditorDlg::ChangeMapElementPositionNow(int x, int y)
{
	//�ṩ�������ھ�̬�ı������Ͻǵ�λ��
	//ע�����λ�øı��¼�
	//ǰ�᣺isChangeMapElement = true
	if (isChangeMapElement != true)
		return;

	static int lastX = -1, lastY = -1;
	if (lastX != x || lastY != y)
	{
		//���λ�øı�
		lastX = x;
		lastY = y;
		paintType = 2;
		mouseInMapPoint.x = x;
		mouseInMapPoint.y = y;
		PaintMap_ChangeElement();
	}
}

//�޸�Ԫ��λ��ȡ��
void CRPGScenarioEditorDlg::ChangeMapElementPositionCancel()
{
	//ע������Ҽ�����¼�
	//ǰ�᣺isChangeMapElement = true
	//������isChangeMapElement = false
	if (isChangeMapElement != true)
		return;

	willChangeElementID = L"";
	willChangeElementType = L"";

	willChangeElementIndex = -1;
	willChangeElementSrcIndex = -1;

	ignoreIndex = -1;
	isChangeMapElement = false;

	//�ػ��ͼ
	RepaintMap();
	PaintMap();

	paintType = 0;
}

//�޸�Ԫ��λ�ý���
void CRPGScenarioEditorDlg::ChangeMapElementPositionEnd(int x, int y)
{
	//ע���������ſ��¼�
	//������������StaitcText���Ͻǵ�λ��
	//ǰ�᣺isChangeMapElement = true
	//������isChangeMapElement = false
	if (isChangeMapElement != true)
		return;

	//������
	if (isShowGrid)
	{
		int addX, addY;
		addX = girdWidth * int((x + mapElementShowRect.left) / girdWidth);
		addY = girdHeigth * int((y + mapElementShowRect.top) / girdHeigth);

		gv->gameMap.gameMapElements[ignoreIndex].x = addX;
		gv->gameMap.gameMapElements[ignoreIndex].y = addY;
	}
	else
	{
		gv->gameMap.gameMapElements[ignoreIndex].x = x + mapElementShowRect.left - offsetX;
		gv->gameMap.gameMapElements[ignoreIndex].y = y + mapElementShowRect.top - offsetY;
	}

	//��ѡ�ж���
	nowMousePointElementIndex = ignoreIndex;

	//ȡ������Ԫ��
	ignoreIndex = -1;

	//�ػ��ͼ
	RepaintMap();
	paintType = 0;
	PaintMap();

	isChangeMapElement = false;
}

//��ͼƬ�ز���Դ�в�������������ʧ�ܷ���-1
int CRPGScenarioEditorDlg::FindSrcIndex(CString imgID)
{
	if (imgID == L"" || gv->imageLoader->srcImages.GetCount() == 0)
	{
		return -1;
	}

	for (int i = 0; i < gv->imageLoader->srcImages.GetCount(); i++)
	{
		if (gv->imageLoader->srcImages[i].imgID == imgID)
		{
			return i;
		}
	}
	return -1;
}

//�Ӿ�̬ͼƬ�в�������������ʧ�ܷ���-1
int CRPGScenarioEditorDlg::FindStaticIndex(CString id)
{
	if (id == L"" || gv->imageLoader->staticElementImages.GetCount() == 0)
	{
		return -1;
	}
	for (int i = 0; i < gv->imageLoader->staticElementImages.GetCount(); i++)
	{
		if (gv->imageLoader->staticElementImages[i].id == id)
		{
			return i;
		}
	}
	return -1;
}

//�Ӷ�̬ͼƬ�в�������������ʧ�ܷ���-1
int CRPGScenarioEditorDlg::FindDynamicIndex(CString id)
{
	if (id == L"" || gv->imageLoader->dynamicElementImages.GetCount() == 0)
	{
		return -1;
	}
	for (int i = 0; i < gv->imageLoader->dynamicElementImages.GetCount(); i++)
	{
		if (gv->imageLoader->dynamicElementImages[i].id == id)
		{
			return i;
		}
	}
	return -1;
}

//�������б����ı�
void CRPGScenarioEditorDlg::OnTriggerSelectChange(int index)
{
	//�������
	m_listTriggerAction.DeleteAllItems();
	SetDlgItemText(IDC_EDIT_STORY, L"");

	//�ж�ѡ��λ��
	if (index == -1)
	{
		return;
	}

	//��ȡ�����б�
	TriggerScript triggerScript;
	triggerAnalyzer.GetTriggerInfo(m_listElementTrigger.GetItemText(index, 1), triggerScript);
	actionAnalyzer.LoadActions(triggerScript.actions, triggerScript.actionCount);

	if (triggerScript.actionCount == 0)
	{
		return;
	}

	//��ʾ�����б�
	CString temp;
	Action tempAction;

	for (int i = 0; i < triggerScript.actionCount; i++)
	{
		temp.Format(L"%d", i + 1);
		m_listTriggerAction.InsertItem(i, NULL);
		m_listTriggerAction.SetItemText(i, 0, temp);//���

		actionAnalyzer.GetActionInfo(i, tempAction);
		m_listTriggerAction.SetItemText(i, 1, tempAction.name);//���

		m_listTriggerAction.SetItemText(i, 2, tempAction.execute ? L"true" : L"false");//�Ƿ���
	}

	//�����п�
	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listTriggerAction);
}

//�����б����ı�
void CRPGScenarioEditorDlg::OnActionSelectChange(int index)
{
	if (index == -1)
	{
		return;
	}

	//��ȡ������Ϣ
	Action action;
	actionAnalyzer.GetActionInfo(m_listTriggerAction.GetItemText(index, 1), action);

	//��ʾ�����ű���Ϣ
	SetDlgItemText(IDC_EDIT_STORY, action.params);
}

//��ʾ��ǰѡ��Ԫ�ص���Ϣ
void CRPGScenarioEditorDlg::ShowNowChooseInfo()
{
	static int lastChoose = -1;
	if (lastChoose != nowMousePointElementIndex)
	{
		lastChoose = nowMousePointElementIndex;//ѡ����ı�
	}
	else
	{
		return;
	}

	//���ö����ű��ı�
	SetDlgItemText(IDC_EDIT_STORY, L"");

	//��ǰû��ѡ����Ŀ
	if (nowMousePointElementIndex == -1)
	{
		SetDlgItemText(IDC_STATIC_NOW_ID, L"---");		//����ID
		SetDlgItemText(IDC_STATIC_NOW_TYPE, L"---");	//��������
		SetDlgItemText(IDC_STATIC_NOW_X, L"---");		//����x
		SetDlgItemText(IDC_STATIC_NOW_Y, L"---");		//����y
		m_checkBoxNowChooseCanPass.SetCheck(BST_UNCHECKED);//���á��ɷ�ͨ����
		return;
	}

#pragma region ������Ϣ��ʾ
	//��ʾ�ı���Ϣ
	CString nowID = m_listMapElement.GetItemText(nowMousePointElementIndex, 1);
	CString nowType = m_listMapElement.GetItemText(nowMousePointElementIndex, 2);

	SetDlgItemText(IDC_STATIC_NOW_ID, nowID);		//����ID
	SetDlgItemText(IDC_STATIC_NOW_TYPE, nowType);	//��������

	CString temp;

	temp.Format(L"%d", gv->gameMap.gameMapElements[nowMousePointElementIndex].x);
	SetDlgItemText(IDC_STATIC_NOW_X, temp);		//����x

	temp.Format(L"%d", gv->gameMap.gameMapElements[nowMousePointElementIndex].y);
	SetDlgItemText(IDC_STATIC_NOW_Y, temp);		//����y

	int index;
	if (gv->gameMap.gameMapElements[nowMousePointElementIndex].type == L"��̬")
	{
		index = FindStaticIndex(gv->gameMap.gameMapElements[nowMousePointElementIndex].id);
		if (index != -1 && gv->imageLoader->staticElementImages[index].canPass)
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_CHECKED);//���á��ɷ�ͨ����
		}
		else
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_UNCHECKED);//���á��ɷ�ͨ����
		}
	}
	else
	{
		index = FindDynamicIndex(gv->gameMap.gameMapElements[nowMousePointElementIndex].id);
		if (index != -1 && gv->imageLoader->dynamicElementImages[index].canPass)
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_CHECKED);//���á��ɷ�ͨ����
		}
		else
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_UNCHECKED);//���á��ɷ�ͨ����
		}
	}


#pragma endregion

#pragma region ��������Ϣ��ʾ
	//��ʾ��������Ϣ
	triggerAnalyzer.LoadScript(gv->gameMap.gameMapElements[nowMousePointElementIndex].params);

	//�������
	m_listElementTrigger.DeleteAllItems();
	m_listTriggerAction.DeleteAllItems();

	//���봥������Ϣ
	TriggerScript triggerScript;
	EasyListCtrl elc;
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		if (triggerAnalyzer.IsTriggerExist(gv->triggerLoader.triggerInfos[i].name))
		{
			m_listElementTrigger.InsertItem(i, 0);

			//���
			temp.Format(L"%d", i + 1);
			m_listElementTrigger.SetItemText(i, 0, temp);

			//��������
			triggerAnalyzer.GetTriggerInfo(gv->triggerLoader.triggerInfos[i].name, triggerScript);
			m_listElementTrigger.SetItemText(i, 1, triggerScript.name);

			//������
			temp.Format(L"%d", triggerScript.actionCount);
			m_listElementTrigger.SetItemText(i, 2, temp);

			//�Ƿ���
			m_listElementTrigger.SetItemText(i, 3, triggerScript.execute ? L"true" : L"false");

		}
	}

	//�����п�
	elc.AdjustColumnWidth(m_listElementTrigger);

#pragma endregion





#pragma region �봥���༭������
	//�򴥷����༭��������Ϣ
	if (dlgTriggerEditor.GetSafeHwnd() != 0 && gv->isTriggerEditorShow == true)
	{
		temp.Format(L"%d", nowMousePointElementIndex);
		gv->nowChooesElementInfo = temp + L"," + nowID + L"," + nowType;

		temp.Format(L"%d,%d", gv->gameMap.gameMapElements[nowMousePointElementIndex].x, gv->gameMap.gameMapElements[nowMousePointElementIndex].y);
		gv->nowChooesElementInfo = gv->nowChooesElementInfo + L"," + temp;


		gv->nowChooesElementTriggerScript = triggerAnalyzer.GetScript();

		dlgTriggerEditor.PostMessageW(MY_CHOOES_CHANGE, 0, 0);
	}
#pragma endregion




}

//���Ƶ�ǰѡ��Ԫ�ص�����ͼ
void CRPGScenarioEditorDlg::PaintNowChoose()
{
	//��ʼ��
	if (mapNowChooseDC == NULL)
	{
		mapNowChooseDC = m_staticTextNowMapChooes.GetDC();			//��ȡ�豸
		m_staticTextNowMapChooes.GetClientRect(mapNowChooseDCRect);	//��ȡ���
		mapNowChooseMemoyDC->CreateCompatibleDC(NULL);				//�����������豸
		bmpMapNowChoose.CreateBitmap(								//������Ӧ��λͼ
			mapNowChooseDCRect.Width(),
			mapNowChooseDCRect.Height(),
			1, 32, NULL
		);
		CBitmap* oldBitmap = mapNowChooseDC->SelectObject(&bmpMapNowChoose);//ѡ��ո��½���λͼ
		oldBitmap->DeleteObject();//ɾ���ɻ���
	}


}

//��ȡ���������Ԫ�ص������������괦�����û��Ԫ�أ��򷵻�-1��
int CRPGScenarioEditorDlg::GetPointElementIndex(int x, int y)
{
	if (hasCreatMap == false)
		return -1;

	//��������Ƿ�����˾��Σ���ĩβ��ǰ�ң��������Ի�ȡ���ϲ���Ǹ����Σ�
	for (int i = gv->gameMap.gameMapElements.GetCount() - 1; i >= 0; i--)
	{
		int a = gv->gameMap.gameMapElements[i].x;
		a = gv->gameMap.gameMapElements[i].y;
		a = gv->gameMap.gameMapElements[i].w;
		a = gv->gameMap.gameMapElements[i].h;

		if (isPointInRect(
			CRect(
				gv->gameMap.gameMapElements[i].x,
				gv->gameMap.gameMapElements[i].y,
				gv->gameMap.gameMapElements[i].w,
				gv->gameMap.gameMapElements[i].h),
			x + mapElementShowRect.left,
			y + mapElementShowRect.top
		))
		{
			return i;
		}
	}

	return -1;
}

//�Ƿ���ھ����ڣ������߽磩
inline bool CRPGScenarioEditorDlg::isPointInRect(CRect & rect, int left, int top)
{
	if (left >= rect.left && left <= rect.left + rect.right &&
		top >= rect.top && top <= rect.top + rect.bottom
		)
		return true;
	else
		return false;
}

//��������Ƿ������м���StaticText�ؼ���
bool CRPGScenarioEditorDlg::isPointInMap(CPoint & point)
{
	//�ж�����Ƿ������м��Ǹ����StaticText
	CRect rect;
	m_map.GetWindowRect(rect);
	ScreenToClient(&rect);

	if (isPointInRect(rect, point.x, point.y))
		return true;
	else
		return false;
}

//�ȼ� Ctrl + S �����ͼ
void CRPGScenarioEditorDlg::OnHotkeyCtrlS()
{
	if (hasCreatMap)
	{
		OnBnClickedButtonFileSave();
	}
}

//�ȼ� Ctrl + C ����Ԫ��
void CRPGScenarioEditorDlg::OnHotkeyCtrlC()
{
	if ( hasCreatMap == true && nowMousePointElementIndex != -1
		&& isAddMapElement == false && isChangeMapElement == false)
	{
		//��ȡ��ǰѡ��Ԫ�ص�ID������
		CString nowID, nowType;
		nowID = m_listMapElement.GetItemText(nowMousePointElementIndex, 1);
		nowType = m_listMapElement.GetItemText(nowMousePointElementIndex, 2);

		//�������Ԫ��
		AddMapElementStart(nowID, nowType);
	}

	
}

//�ȼ� Delete ɾ��Ԫ��
void CRPGScenarioEditorDlg::OnHotkeyDelete()
{
	if (hasCreatMap==false || nowMousePointElementIndex==-1)
	{
		return;
	}
	OnBnClickedButtonDel();
}

//�ȼ� Ctrl + N �½���ͼ
void CRPGScenarioEditorDlg::OnHotkeyCtrlN()
{
	OnBnClickedButtonFileNew();
}

//�ȼ� Ctrl + O �򿪵�ͼ
void CRPGScenarioEditorDlg::OnHotkeyCtrlO()
{
	OnBnClickedButtonFileLoad();
}

//������ĳ�ʼ������
void CRPGScenarioEditorDlg::MyInit()
{
	//�����������
	srand((unsigned)time(NULL));

	//��ȡ����������
	gv = GV::GetInstance();

	//��ʼ����Դ
	gv->LoadImageSrc();
	gv->LoadAllMap();
	gv->LoadUserData();


#pragma region ��ͼƬ���ݼ���ListCtrl
	EasyListCtrl elc;
	m_list.InsertColumn(0, L"#");
	m_list.InsertColumn(1, L"����");
	m_list.InsertColumn(2, L"����");
	m_list.InsertColumn(3, L"���");
	m_list.InsertColumn(4, L"�߶�");

	//���뾲̬��Դ
	CString temp;
	int count;//list��ǰ��item��
	for (int i = 0; i < gv->imageLoader->staticElementImages.GetCount(); i++)
	{
		temp.Format(L"%d", i + 1);
		m_list.InsertItem(i, temp);//����

		m_list.SetItemText(i, 1, gv->imageLoader->staticElementImages[i].id);
		m_list.SetItemText(i, 2, L"��̬");

		temp.Format(L"%d", gv->imageLoader->staticElementImages[i].w);
		m_list.SetItemText(i, 3, temp);

		temp.Format(L"%d", gv->imageLoader->staticElementImages[i].h);
		m_list.SetItemText(i, 4, temp);
	}
	count = m_list.GetItemCount();


	//���붯̬��Դ
	for (int i = 0; i < gv->imageLoader->dynamicElementImages.GetCount(); i++)
	{
		temp.Format(L"%d", count + i);
		m_list.InsertItem(i + count, temp);//����

		m_list.SetItemText(i + count, 1, gv->imageLoader->dynamicElementImages[i].id);
		m_list.SetItemText(i + count, 2, L"��̬");

		temp.Format(L"%d", gv->imageLoader->dynamicElementImages[i].w);
		m_list.SetItemText(i + count, 3, temp);

		temp.Format(L"%d", gv->imageLoader->dynamicElementImages[i].h);
		m_list.SetItemText(i + count, 4, temp);
	}


	//���÷��
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_list.SetExtendedStyle(dwStyle); //������չ���

	elc.AdjustColumnWidth(m_list);
#pragma endregion

#pragma region ���½�����ͼ��ʼ��
	//��ʼ�����½ǵ�Ԫ������ͼ
	m_elementImage.GetWindowRect(&elementDrawRect);//��ȡ�ؼ�����Ļ����
	ScreenToClient(&elementDrawRect);
	pElementImageDC = m_elementImage.GetDC();//��ȡStaticText�ؼ����豸���
	nowImageIndex = -1;//�õ�ǰԪ��ListCtrl��ѡ����Ϊ-1����Ϊ���������ʱ�û�û��ѡ����

	//���������ú�����ͼ��Ĵ�С��ͬ
	bmpElementBitmap.CreateCompatibleBitmap(pElementImageDC, elementDrawRect.Width(), elementDrawRect.Height());

	//������ͼ�ڴ�DC������ͼDC����
	pElementImageMemoryDC = new CDC();
	pElementImageMemoryDC->CreateCompatibleDC(pElementImageDC);

	//����ɵĻ���
	oldBmpElementBitmap = pElementImageMemoryDC->SelectObject(&bmpElementBitmap);
	oldBmpElementBitmap->DeleteObject();
#pragma endregion

#pragma region �����༭����ʼ��

	gv->triggerLoader.LoadTriggerConfig();


	//������ListCtrl
	m_listElementTrigger.InsertColumn(0, L"#");
	m_listElementTrigger.InsertColumn(1, L"����");
	m_listElementTrigger.InsertColumn(2, L"������");
	m_listElementTrigger.InsertColumn(3, L"����");

	//�����п�
	elc.AdjustColumnWidth(m_listElementTrigger);


	//���÷��
	dwStyle = m_listElementTrigger.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listElementTrigger.SetExtendedStyle(dwStyle); //������չ���


	//�����б�ListCtrl
	m_listTriggerAction.InsertColumn(0, L"#");
	m_listTriggerAction.InsertColumn(1, L"����");
	m_listTriggerAction.InsertColumn(2, L"����");

	//���÷��
	dwStyle = m_listTriggerAction.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listTriggerAction.SetExtendedStyle(dwStyle); //������չ���

	//�����п�
	elc.AdjustColumnWidth(m_listTriggerAction);

#pragma endregion

#pragma region ��ͼ��ʼ��
	isShowGrid = true;				//�ر���ʾ����
	m_checkBoxGrid.SetCheck(BST_CHECKED);//Ĭ�Ͽ���������
	girdColor = 8421504;			//����Ĭ����ɫ = #��ɫ
	selectIndex = -1;				//û��ѡ��Ԫ��
	hasCreatMap = false;			//�Ѿ��½���ͼ = false
	hasCloseMap = true;				//�Ѿ��رյ�ͼ = true
	paintType = -1;					//��ͼ���ƹر�
	ignoreIndex = -1;				//��ͼ���ƺ������� = -1

	//���Ԫ�ص���ر�����ʼ��
	isAddMapElement = false;		//�������Ԫ�� = false
	willAddElementSrcIndex = -1;
	willAddElementIndex = -1;

	//�޸�Ԫ��λ�õ���ر�����ʼ��
	isChangeMapElement = false;		//�����޸�Ԫ��λ�� = false
	willChangeElementSrcIndex = -1;
	willChangeElementIndex = -1;

	//��������ʼ��
	scrollBarPerChange = 10;

	//��ȡ��ͼ����DC
	mapDC = m_map.GetDC();

	//���ù�����
	m_scrollBarX.EnableScrollBar(ESB_DISABLE_BOTH);
	m_scrollBarY.EnableScrollBar(ESB_DISABLE_BOTH);

	//�ұ�ListCtrl��ʼ��
	m_listMapElement.InsertColumn(0, L"#");
	m_listMapElement.InsertColumn(1, L"ID");
	m_listMapElement.InsertColumn(2, L"����");
	m_listMapElement.InsertColumn(3, L"��");
	elc.AdjustColumnWidth(m_listMapElement);

	//���÷��
	dwStyle = m_listMapElement.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listMapElement.SetExtendedStyle(dwStyle); //������չ���


	//����λ�ó�ʼ��
	m_map.GetWindowRect(&mapStaticTextRect);//��ȡ�ؼ�����Ļ����
	ScreenToClient(&mapStaticTextRect);


#pragma endregion

#pragma region ��ͼѡ��Ԫ����س�ʼ��




#pragma endregion

#pragma region ע���ȼ�
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_S, MOD_CONTROL, 83);	//Ctrl + s	�����ͼ
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_C, MOD_CONTROL, 67);	//Ctrl + c	����Ԫ��
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_DELETE, NULL, 46);			//Delete	ɾ��Ԫ��

	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_N, MOD_CONTROL, 78);	//Ctrl + n	�½���ͼ
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_O, MOD_CONTROL, 79);	//Ctrl + o	�򿪵�ͼ

#pragma endregion


}

//�������ڹر�ǰִ�еĺ���
void CRPGScenarioEditorDlg::MyClose()
{
	ReleaseDC(pElementImageDC);//�ͷ�Ԫ������ͼ�������
	gv->imageLoader->BeginRelease();

	//�ͷ����½�����ͼ�豸
	if (pElementImageMemoryDC != NULL)
		pElementImageMemoryDC->DeleteDC();
	if (pElementImageDC != NULL)
		pElementImageDC->DeleteDC();
	bmpElementBitmap.DeleteObject();

	//�رյ�ͼ
	CloseMap();
	mapDC->DeleteDC();


	//�ͷų������Ͻ�����ͼ������豸
	if (mapNowChooseDC != NULL)
	{
		mapNowChooseDC->DeleteDC();
		mapNowChooseMemoyDC->DeleteDC();
		bmpMapNowChoose.DeleteObject();
	}
}

//���򼴽��ر�
void CRPGScenarioEditorDlg::OnClose()
{

	MyClose();
	CDialogEx::OnCancel();//���θþ������Խ�ֹ����ر�
}

//ע�ᰴť
void CRPGScenarioEditorDlg::OnBnClickedButton3Login()
{
	int iWidth = GetSystemMetrics(SM_CXSCREEN);//��Ļ���
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//��Ļ�߶�
	CRect rect;

	//����δ����
	if (dlgLogin.GetSafeHwnd() == 0)
		dlgLogin.Create(IDD_DIALOG_LOGIN);


	dlgLogin.GetWindowRect(rect);

	//������ʾ
	dlgLogin.MoveWindow(
		(iWidth - rect.Width()) / 2,
		(iHeight - rect.Height()) / 2,
		rect.Width(),
		rect.Height()
	);

	dlgLogin.ShowWindow(SW_SHOW);

}

//ע����¼��ť
void CRPGScenarioEditorDlg::OnBnClickedButton3SignOut()
{
	if (gv->isLogin == false)
	{
		AfxMessageBox(L"����δ��¼��");
		return;
	}
	gv->isLogin = false;
	AfxMessageBox(L"��ע����¼��");
}

//�½���ͼ��Ϣ���Զ�����Ϣ��
afx_msg LRESULT CRPGScenarioEditorDlg::OnMyNewMap(WPARAM wParam, LPARAM lParam)
{
	EasyPath ep;
	gv->gameMap.SetPath(ep.GetProgramDir() + L"maps\\" + gv->gameMap.GetMapName() + L".map");
	gv->gameMap.CreatMap();
	CreatMap();
	AfxMessageBox(L"�½���ͼ�ɹ���");
	return 0;
}

//�����½���ͼ����
void CRPGScenarioEditorDlg::OnBnClickedButtonFileNew()
{
	//��¼���
	if (gv->isLogin==false)
	{
		AfxMessageBox(L"���ȵ�¼��");
		return;
	}


	int iWidth = GetSystemMetrics(SM_CXSCREEN);//��Ļ���
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//��Ļ�߶�
	CRect rect;

	//����δ����
	if (dlgNewMap.GetSafeHwnd() == 0)
		dlgNewMap.Create(IDD_DIALOG_NEW_MAP, this);

	dlgNewMap.GetWindowRect(rect);

	//������ʾ
	dlgNewMap.MoveWindow(
		(iWidth - rect.Width()) / 2,
		(iHeight - rect.Height()) / 2,
		rect.Width(),
		rect.Height()
	);

	dlgNewMap.ShowWindow(SW_SHOW);
}

//��������Ԫ��
void CRPGScenarioEditorDlg::OnNMClickListElement(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	OnElementSelectChange(pLVCD->iItem);

	*pResult = 0;
}

//ʱ����Ϣ
void CRPGScenarioEditorDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		TimerDynamicNextImage();//�ػ��ͼԪ��
		break;
	case 2:
		TimerRepaint();//ȫ���ػ��¼�
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

//ɾ��Ԫ�ذ�ť�¼�
void CRPGScenarioEditorDlg::OnBnClickedButtonDel()
{
	//����ͼ�Ƿ��
	if (hasCreatMap == false)
	{
		AfxMessageBox(L"��ͼδ�򿪡�");
		return;
	}

	//����Ƿ�ѡ��Ԫ��
	if (nowMousePointElementIndex == -1)
	{
		AfxMessageBox(L"����ѡ��Ԫ�ء�");
		return;
	}

	//����Ƿ��������Ԫ�ػ����ƶ�Ԫ��
	if (isAddMapElement)
	{
		AfxMessageBox(L"����ȡ�����Ԫ�ء�");
		return;
	}
	if (isChangeMapElement)
	{
		AfxMessageBox(L"��������ƶ�Ԫ�ء�");
		return;
	}


	//ɾ��Ԫ��
	gv->gameMap.gameMapElements.RemoveAt(nowMousePointElementIndex);

	//ListCtrlˢ����ʾ
	m_listMapElement.DeleteAllItems();
	CString temp;
	for (int i = 0; i < gv->gameMap.gameMapElements.GetCount(); i++)
	{
		m_listMapElement.InsertItem(i, NULL);
		temp.Format(L"%d", i + 1);
		m_listMapElement.SetItemText(i, 0, temp);//���
		m_listMapElement.SetItemText(i, 1, gv->gameMap.gameMapElements[i].id);//ID
		m_listMapElement.SetItemText(i, 2, gv->gameMap.gameMapElements[i].type);//����

		temp.Format(L"%d", gv->gameMap.gameMapElements[i].index);
		m_listMapElement.SetItemText(i, 3, temp);//����
	}

	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listMapElement);

	//�޸�ѡ��
	nowMousePointElementIndex = -1;

	//�ػ��ͼ
	RepaintMap();
	PaintMap();
}

//�����ڴ��ڳߴ类����
void CRPGScenarioEditorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//���¼��㻬����
	CalculateScrollBar(cx,cy);

	//���¼�����ʾ����
	//if (m_map.GetSafeHwnd() == 0)
	//{
	//	return;
	//}
	//int left, top;
	//left = mapElementShowRect.left;
	//top = mapElementShowRect.top;
	//m_map.GetClientRect(mapElementShowRect);//��ʾ�����ľ���

	//mapElementShowRect.SetRect(left, top, mapElementShowRect.Width(), mapElementShowRect.Height());
	if (hasCreatMap)
	{
		bmpShowMap.DeleteObject();
		bmpShowMap.CreateBitmap(mapElementShowRect.Width(), mapElementShowRect.Height(), 1, 32, NULL);
		CBitmap* oldBitmap = mapShowMemoryDC->SelectObject(&bmpShowMap);
		if (oldBitmap != NULL)
		{
			oldBitmap->DeleteObject();//����ɻ���
		}

	}
	PaintMap();
	
}

//������ˮƽ�����¼�
void CRPGScenarioEditorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	int tempPos = pScrollBar->GetScrollPos();
	int min, max;
	pScrollBar->GetScrollRange(&min, &max);
	switch (nSBCode)
	{
	case SB_THUMBPOSITION://�϶�����
		pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT://�����ߵļ�ͷ
		if (tempPos > min)
			tempPos--;
		pScrollBar->SetScrollPos(tempPos);
		break;
	case SB_LINERIGHT://����ұߵļ�ͷ
		if (tempPos < max)
			tempPos++;
		pScrollBar->SetScrollPos(tempPos);
		break;
	}
	OnMapScrollValueChange(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//��������ֱ�����¼�
void CRPGScenarioEditorDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int tempPos = pScrollBar->GetScrollPos();
	int min, max;
	pScrollBar->GetScrollRange(&min, &max);
	switch (nSBCode)                 //���������Ϣ
	{
	case SB_LINELEFT:
		if (tempPos > min)
			tempPos--;
		pScrollBar->SetScrollPos(tempPos);
		break;
	case SB_LINERIGHT:
		if (tempPos < max)
			tempPos++;
		pScrollBar->SetScrollPos(tempPos);
		break;
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos(nPos);
		break;
	}
	OnMapScrollValueChange(true);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

//�����������¼�
void CRPGScenarioEditorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//��ͼδ����
		return;

	//�ж��Ƿ�����StaticText
	if (isPointInMap(point) == false)
		return;

	//�ж��Ƿ��������Ԫ��
	if (isAddMapElement == true)
	{

		AddMapElementEnd(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);


		isAddMapElement = false;
		AddMapElementStart(willAddElementID, willAddElementType);
		return;
	}

	//�ж��Ƿ�ѡ��Ԫ��
	mouseInMapPoint.x = point.x - mapStaticTextRect.left;
	mouseInMapPoint.y = point.y - mapStaticTextRect.top;
	nowMousePointElementIndex = GetPointElementIndex(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);

	//�봥���༭��������Ҫ���Ƿ�ѡ����Ԫ�أ�
	if (nowMousePointElementIndex == -1)
		gv->nowIsChooesElement = false;
	else
		gv->nowIsChooesElement = true;

	//��ʾ��ǰѡ��Ԫ�ص���Ϣ
	ShowNowChooseInfo();

	EasyListCtrl elc;
	elc.SelectRow(m_listMapElement, nowMousePointElementIndex);
	if (nowMousePointElementIndex != -1 && isChangeMapElement == false)//���ѡ����Ԫ��
	{
		ChangeMapElementPositionStart(nowMousePointElementIndex);
		return;
	}

	PaintMap();


	CDialogEx::OnLButtonDown(nFlags, point);
}

//������̧���¼�
void CRPGScenarioEditorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//��ͼδ����
		return;

	if (isChangeMapElement)
	{
		ChangeMapElementPositionEnd(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

//����ƶ��¼�
void CRPGScenarioEditorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//��ͼδ����
		return;

	static bool isLastMouseInRect;//�Ƿ��ϴ�����ھ�����
	//�ж��Ƿ���StaticText��
	if (isPointInMap(point))
	{
		if (isChangeMapElement)//�����޸�Ԫ��λ��
		{
			ChangeMapElementPositionNow(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);
		}
		else if (isAddMapElement == true)//�������Ԫ��
		{
			paintType = 1;
			mouseInMapPoint.x = point.x - mapStaticTextRect.left;
			mouseInMapPoint.y = point.y - mapStaticTextRect.top;
			PaintMap_AddElement();
			isLastMouseInRect = true;
		}
	}
	else
	{
		//ԭ��
		//��isLastMouseInRectΪ���ʱ��˵���ϴ���껹��StaticText�ڣ�Ȼ���������뿪��StaticText��
		//�����Ҫ�ػ�StaticText���򣬵���֮���������һֱû�н���StaticText�ڣ����Բ����ٴ��ػ��ˣ�
		//��߳�������Ч�ʡ�
		if (isLastMouseInRect == true)
		{
			paintType = 0;
			PaintMap();
			isLastMouseInRect = false;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

//����Ҽ������¼�
void CRPGScenarioEditorDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//��ͼδ����
		return;

	//�ж��Ƿ�����StaticText
	if (isPointInMap(point))
	{
		//�������Ԫ��
		if (isAddMapElement == true)
		{
			AddMapElementCancel();
			RepaintMap();//�ػ��ͼ
			PaintMap();//����ͼˢ����ʾ����
			isAddMapElement = false;
			paintType = 0;
		}
		else if (isChangeMapElement)//�����޸�Ԫ��λ��
		{
			ChangeMapElementPositionCancel();
			paintType = 0;
		}
	}


	CDialogEx::OnRButtonDown(nFlags, point);
}

//���Ԫ�ذ�ť����¼�
void CRPGScenarioEditorDlg::OnBnClickedButtonAddElement()
{
	if (hasCreatMap == false)
	{
		AfxMessageBox(L"�����½���ͼ��");
		return;
	}

	if (isAddMapElement == true)
	{
		AddMapElementCancel();
	}
	else
	{
		if (nowElementChoose != -1)
		{
			AddMapElementStart(m_list.GetItemText(nowElementChoose, 1), m_list.GetItemText(nowElementChoose, 2));
		}
	}
}

//���ûس����˳�
void CRPGScenarioEditorDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}

//����ESC���˳�
void CRPGScenarioEditorDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}
/*
���ûس���ESC���˳�������
ʵ�ʲ�����
��һ�����������򵼣�ѡ��Ŀ��Ի����Ӧ��CXXXDlg������

�ڶ�����ѡ����Ϣ��ѡ�����дWM_CLOSE��Ϣ��Ӧ������

��������ѡ���麯����ѡ�����дOnCancel��OnOk����������

���Ĳ�����OnCancel��OnOk������������������
*/

void CRPGScenarioEditorDlg::OnBnClickedButtonFileSave()
{
	//��¼���
	if (gv->isLogin == false)
	{
		AfxMessageBox(L"���ȵ�¼��");
		return;
	}


	if (hasCreatMap == true)
	{
		gv->gameMap.SaveGameMap();
		AfxMessageBox(L"��ͼ�ѱ��档");
		PaintMap();
	}
	else
	{
		AfxMessageBox(L"�����½���ͼ��");
	}
}

//���ص�ͼ��Ϣ���Զ�����Ϣ��
afx_msg LRESULT CRPGScenarioEditorDlg::OnMyLoadMap(WPARAM wParam, LPARAM lParam)
{
	//�رյ�ͼ
	if (hasCreatMap)
	{
		CloseMap();
	}

	//���ص�ͼ
	gv->gameMap.LoadGameMap();

	//������ͼ
	CreatMap();

	//�м�ListCtrl��ʼ��
	m_listMapElement.DeleteAllItems();
	CString temp;
	for (int i = 0; i < gv->gameMap.gameMapElements.GetCount(); i++)
	{
		m_listMapElement.InsertItem(i, NULL);
		temp.Format(L"%d", i + 1);
		m_listMapElement.SetItemText(i, 0, temp);//#

		m_listMapElement.SetItemText(i, 1, gv->gameMap.gameMapElements[i].id);//ID
		m_listMapElement.SetItemText(i, 2, gv->gameMap.gameMapElements[i].type);//����

		temp.Format(L"%d", gv->gameMap.gameMapElements[i].index);
		m_listMapElement.SetItemText(i, 3, temp);//��
	}

	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listMapElement);

	return 0;
}

//���ص�ͼ��ť����¼�
void CRPGScenarioEditorDlg::OnBnClickedButtonFileLoad()
{
	//��¼���
	if (gv->isLogin == false)
	{
		AfxMessageBox(L"���ȵ�¼��");
		return;
	}


	if (hasCreatMap)
	{
		int temp = MessageBox(L"��ǰ�����ڱ༭�ĵ�ͼ���Ƿ�Ҫ���棿", L"ѯ��", MB_ICONQUESTION | MB_YESNOCANCEL);
		if (temp == IDYES)
		{
			gv->gameMap.SaveGameMap();

			DlgLoadMap dlgLoadMap;
			dlgLoadMap.DoModal();
		}
		else if (temp == IDNO)
		{
			DlgLoadMap dlgLoadMap;
			dlgLoadMap.DoModal();
		}
		else
		{
			return;
		}
	}
	DlgLoadMap dlgLoadMap;
	dlgLoadMap.DoModal();
}

//��������ѡ��ѡ���¼�
void CRPGScenarioEditorDlg::OnBnClickedCheck3()
{
	int temp = m_checkBoxGrid.GetCheck();
	switch (temp)
	{
	case BST_UNCHECKED:
		isShowGrid = false;
		break;
	case BST_CHECKED:
		isShowGrid = true;
		break;
	}
	PaintMap();
}

//ˢ����ʾ��ͼ
void CRPGScenarioEditorDlg::OnBnClickedButtonReflashMap()
{
	if (hasCreatMap)
	{
		PaintMap();
	}
}

//��ͼ����Ԫ��ListCtrl����¼�
void CRPGScenarioEditorDlg::OnNMClickListMapElement(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	nowMousePointElementIndex = pLVCD->iItem;
	ShowNowChooseInfo();
	if (nowMousePointElementIndex != -1)
	{
		PaintMap();
	}

	*pResult = 0;
}

//�ȼ��¼�
void CRPGScenarioEditorDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{

	switch (nHotKeyId)
	{
	case ID_HOTKEY_CTRL_S://����
		OnHotkeyCtrlS();
		break;
	case ID_HOTKEY_CTRL_C://����
		OnHotkeyCtrlC();
		break;
	case ID_HOTKEY_CTRL_N://�½���ͼ
		OnHotkeyCtrlN();
		break;
	case ID_HOTKEY_CTRL_O://���ļ�
		OnHotkeyCtrlO();
		break;
	case ID_HOTKEY_DELETE://ɾ��
		OnHotkeyDelete();
		break;

	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//�����ű����޸ģ��Զ�����Ϣ��
afx_msg LRESULT CRPGScenarioEditorDlg::OnMyTriggerChange(WPARAM wParam, LPARAM lParam)
{
	//���õ�ǰѡ��Ԫ�صĴ�������Ϣ
	gv->gameMap.gameMapElements[nowMousePointElementIndex].params = gv->nowChooesElementTriggerScript;

#pragma region ��������Ϣ��ʾ
	CString temp;

	//��ʾ��������Ϣ
	triggerAnalyzer.LoadScript(gv->gameMap.gameMapElements[nowMousePointElementIndex].params);

#if _DEBUG
	int a = triggerAnalyzer.GetTriggerCount();
	a = gv->triggerLoader.triggerInfos.GetCount();
#endif // _DEBUG

	//�������
	m_listElementTrigger.DeleteAllItems();
	m_listTriggerAction.DeleteAllItems();

	//���봥������Ϣ
	TriggerScript triggerScript;
	EasyListCtrl elc;
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		CString temp1 = gv->triggerLoader.triggerInfos[i].name;
		if (triggerAnalyzer.IsTriggerExist(gv->triggerLoader.triggerInfos[i].name))
		{
			m_listElementTrigger.InsertItem(i, 0);

			//���
			temp.Format(L"%d", i + 1);
			m_listElementTrigger.SetItemText(i, 0, temp);

			//��������
			triggerAnalyzer.GetTriggerInfo(gv->triggerLoader.triggerInfos[i].name, triggerScript);
			m_listElementTrigger.SetItemText(i, 1, triggerScript.name);

			//������
			temp.Format(L"%d", triggerScript.actionCount);
			m_listElementTrigger.SetItemText(i, 2, temp);

			//�Ƿ���
			m_listElementTrigger.SetItemText(i, 3, triggerScript.execute ? L"true" : L"false");

			//���ڿ����Ĵ��������и�����ʾ
			if (triggerScript.execute)
			{
				elc.SelectRow(m_listElementTrigger, i, false);
			}
		}
	}

	//�����п�
	elc.AdjustColumnWidth(m_listElementTrigger);
#pragma endregion

	return 0;
}

//���������ƶ�
void CRPGScenarioEditorDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);
	if (hasCreatMap)
	{
		PaintMap();
	}

	// TODO: �ڴ˴������Ϣ����������
}

//�����ƶ����
void CRPGScenarioEditorDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	if (hasCreatMap)
	{
		PaintMap();
	}
	// TODO: �ڴ˴������Ϣ����������
}

//������ListCtrl���ѡ��
void CRPGScenarioEditorDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	OnTriggerSelectChange(pLVCD->iItem);

	*pResult = 0;
}

//����ListCtrl�б�ѡ��
void CRPGScenarioEditorDlg::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	OnActionSelectChange(pLVCD->iItem);
	*pResult = 0;
}

//���ڼ���״̬���ı��¼�
void CRPGScenarioEditorDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	switch (nState)
	{
	case WA_ACTIVE:		//��ý���
		KillTimer(2);
		SetTimer(2, 50, NULL);//ÿ�����20֡
		break;
	case WA_INACTIVE:	//ʧȥ����
		KillTimer(2);
		SetTimer(2, 100, NULL);//ÿ�����10֡
		break;
	default:
		break;
	}


	// TODO: �ڴ˴������Ϣ����������
}

//��ͼ�ػ�ʱ��
void CRPGScenarioEditorDlg::TimerRepaint()
{
	if (IsIconic())
	{
		KillTimer(2);
	}
	if (hasCreatMap == false)
	{
		return;
	}
	switch (paintType)
	{
	case 0:PaintMap(); break;
	case 1:PaintMap_AddElement(); break;
	case 2:PaintMap_ChangeElement(); break;
	case 3:RepaintMap(); break;
	}
}

//ListCtrlɾ��ѡ��Ԫ��
void CRPGScenarioEditorDlg::OnBnClickedButton8()
{
	OnBnClickedButtonDel();
}
