
// RPG Scenario EditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RPG Scenario Editor.h"
#include "RPG Scenario EditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRPGScenarioEditorDlg 对话框

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


// CRPGScenarioEditorDlg 消息处理程序

BOOL CRPGScenarioEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MyInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRPGScenarioEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRPGScenarioEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//打开触发编辑器
void CRPGScenarioEditorDlg::OnBnClickedButton1()
{
	if (hasCreatMap == false)
	{
		AfxMessageBox(L"请先新建地图。");
		return;
	}

	int iWidth = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
	CRect rect;

	//窗口未创建
	if (dlgTriggerEditor.GetSafeHwnd() == 0)
		dlgTriggerEditor.Create(IDD_DIALOG_TRIGGER_EDIT);


	dlgTriggerEditor.GetWindowRect(rect);

	//居中显示
	dlgTriggerEditor.MoveWindow(
		(iWidth - rect.Width()) / 2,
		(iHeight - rect.Height()) / 2,
		rect.Width(),
		rect.Height()
	);

	dlgTriggerEditor.ShowWindow(SW_SHOW);
	gv->isTriggerEditorShow = true;


	//向触发器编辑器发送消息

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

//绘制左边地图元素列表中的元素
void CRPGScenarioEditorDlg::PaintElement()
{
	//异常检测
	if (nowImageIndex < 0 || nowElementChoose == -1 || m_list.GetItemCount() == 0)
	{
		return;
	}

	//填充背景
	pElementImageMemoryDC->FillSolidRect(0, 0, elementDrawRect.Width(), elementDrawRect.Height(), 13160660);

	//根据类型绘制不同的图片
	if (nowIsElementStatic)
	{
		//判断是否需要缩放图片
		if (nowIsElementZoom)
		{
			//如何透明缩放绘制一张图片？MaskBlt？
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
			//判断是否有透明色
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
		//判断是否需要缩放图片
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
			//判断是否有透明色
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

//当左边ListCtrl的选项被改变
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
		return;//选择的项目没有改变
	}
	else
	{
		lastIndex = index;//选择的项目发生了改变
	}
	

	//初始化：清除数据和停止播放动画
	nowElementImagePoint.RemoveAll();
	KillTimer(1);

	//步骤1：获取当前选中项的类型与对应的索引
	CString nowID = m_list.GetItemText(index, 1);//当前选中项的ID
	CString imgID;//当前选中元素的图片ID 
	nowIsElementStatic = m_list.GetItemText(index, 2) == L"静态" ? true : false;
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

	//步骤2：查找图片ID的索引
	nowSrcImageIndex = -1;
	for (int i = 0; i < gv->imageLoader->srcImages.GetCount(); i++)
	{
		if (imgID == gv->imageLoader->srcImages[i].imgID)
		{
			nowSrcImageIndex = i;
			break;
		}
	}

	//步骤3：对动态图片进行分析
	if (nowIsElementStatic == false)
	{
		nowElementImagePoint.RemoveAll();
		nowPlayIndex = -1;

		EasyText et;
		CStringArray imageGroup;

		et.DivideText(gv->imageLoader->dynamicElementImages[nowImageIndex].imageGroups, L";", imageGroup);

		//判断是否自动播放（自动播放的话就使用autoPlay所指向的Tag，否则就用defaultTag）
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
			nowPlayIndex = 0;//设置播放位置为第一帧
		}

	}

	//步骤4：计算该图片的绘制位置
	nowElementDrawX;
	nowElementDrawY;

	if (elementDrawRect.Width() < gv->imageLoader->staticElementImages[nowImageIndex].w ||
		elementDrawRect.Height() < gv->imageLoader->staticElementImages[nowImageIndex].h)
	{
		nowIsElementZoom = true;//需要缩放显示
	}
	else
	{
		nowIsElementZoom = false;//不需要缩放显示

		nowElementDrawX = (elementDrawRect.Width() - gv->imageLoader->staticElementImages[nowImageIndex].w) / 2;
		nowElementDrawY = (elementDrawRect.Height() - gv->imageLoader->staticElementImages[nowImageIndex].h) / 2;
	}

	//步骤5：显示元素的信息
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

	//步骤6：启动播放动画时钟
	if (nowIsElementStatic == false)
	{
		if (gv->imageLoader->dynamicElementImages[nowImageIndex].interval != 0)
		{
			SetTimer(1, gv->imageLoader->dynamicElementImages[nowImageIndex].interval, NULL);
		}
	}

	//步骤7：重绘缩率图位置
	pElementImageDC->FillSolidRect(0, 0, elementDrawRect.Width(), elementDrawRect.Height(), 0);
	PaintElement();
	//InvalidateRect(elementDrawRect);

	//判断是否正在添加元素
	if (isAddMapElement == true)
	{
		AddMapElementCancel();
		AddMapElementStart(nowID, m_list.GetItemText(index, 2));
	}
}

//计时器_选择下一张图片（用于左下角缩略图的播放图片）
void CRPGScenarioEditorDlg::TimerDynamicNextImage()
{
	nowPlayIndex++;
	if (nowPlayIndex > gv->imageLoader->dynamicElementImages.GetCount())
	{
		nowPlayIndex = 0;//循环播放
	}

	//重绘元素缩略图
	PaintElement();
}

//新建地图
void CRPGScenarioEditorDlg::CreatMap()
{
	//异常检测
	if (gv->gameMap.GetMapHeigth() == 0 || gv->gameMap.GetMapWidth() == 0)
	{
		AfxMessageBox(L"新建地图出现错误：地图的宽度或高度为0。");
		exit(-1);
	}
	//检查是否有正在编辑的地图
	if (hasCloseMap == false)
		CloseMap();
	hasCreatMap = false;


	//变量初始化
	isShowGrid = true;				//关闭显示网格
	selectIndex = -1;				//没有选中元素

	isAddMapElement = false;		//正在添加元素 = false
	willAddElementSrcIndex = -1;
	willAddElementIndex = -1;

	isChangeMapElement = false;		//正在修改元素位置 = false
	willChangeElementSrcIndex = -1;
	willChangeElementIndex = -1;

	ignoreIndex = -1;				//地图绘制忽略索引 = -1
	nowMousePointElementIndex = -1;	//地图选元素索引 = -1

	//绘图区初始化
	if (mapDC == NULL)
		mapDC = m_map.GetDC();

	m_map.GetClientRect(mapElementShowRect);//显示出来的矩形
	mapElementRect.SetRect(0, 0, gv->gameMap.GetMapWidth(), gv->gameMap.GetMapHeigth());//整个地图矩形

	//地图缓存初始化
	mapMemoryDC = new CDC();
	mapMemoryDC->CreateCompatibleDC(NULL);

	bmpMap.DeleteObject();
	bmpMap.CreateBitmap(gv->gameMap.GetMapWidth(), gv->gameMap.GetMapHeigth(), 1, 32, NULL);


	//错误警示！使用下面这句代码创建的位图仅有两位色彩，即黑白的。
	//bmpMap.CreateCompatibleBitmap(mapMemoryDC, mapElementRect.Width(), mapElementRect.Height());

	CBitmap * oldBitmap = mapMemoryDC->SelectObject(&bmpMap);
	oldBitmap->DeleteObject();//清除旧画板
	mapMemoryDC->FillSolidRect(0, 0, mapElementRect.Width(), mapElementRect.Height(), RGB(255, 255, 255));//填充背景为白色



	//显示区域地图缓冲初始化
	mapShowMemoryDC = new CDC();
	mapShowMemoryDC->CreateCompatibleDC(NULL);
	bmpShowMap.DeleteObject();
	bmpShowMap.CreateBitmap(mapElementShowRect.Width(), mapElementShowRect.Height(), 1, 32, NULL);

	//错误警示！使用下面这句代码创建的位图仅有两位色彩，即黑白的。
	//bmpShowMap.CreateCompatibleBitmap(mapShowMemoryDC, mapElementShowRect.Width(), mapElementShowRect.Height());

	oldBitmap = mapShowMemoryDC->SelectObject(&bmpShowMap);
	oldBitmap->DeleteObject();//清除旧画板


	//计算滚动条
	m_scrollBarX.SetScrollPos(0);
	m_scrollBarY.SetScrollPos(0);
	CalculateScrollBar(mapElementShowRect.Width(),mapElementShowRect.Height());

	//刷新重绘
	paintType = 0;
	RepaintMap();
	PaintMap();
	hasCreatMap = true;//新建地图完毕
}

//关闭地图
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

//计算滚动条
void CRPGScenarioEditorDlg::CalculateScrollBar(int cx, int cy)
{
	if (m_map.GetSafeHwnd() == 0)
		return;

	//重新计算地图显示区域的大小
	int showX, showY;//记录显示位置的x和y坐标
	showX = mapElementShowRect.left;
	showY = mapElementShowRect.top;
	//m_map.GetClientRect(mapElementShowRect);//显示出来的矩形
	mapElementShowRect.SetRect(showX, showY, cx, cy);


	//重新计算滚动条的矩形框
	SCROLLINFO scrollInfo;

	//计算水平滑块条
	scrollInfo.fMask = SIF_RANGE || SIF_PAGE;
	scrollInfo.nMin = 0;
	scrollInfo.nPage = 1;

	//判断高度是否超出范围
	if (mapElementRect.Height() > mapElementShowRect.Height())
	{
		//判断是否有余数
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


	//计算垂直滑块条
	scrollInfo.fMask = SIF_RANGE || SIF_PAGE;
	scrollInfo.nMin = 0;
	scrollInfo.nPage = 1;
	//判断高度是否超出范围
	if (mapElementRect.Width() > mapElementShowRect.Width())
	{
		//判断是否有余数
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

//地图滚动条滑块位置被改变
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

//普通绘图
void CRPGScenarioEditorDlg::PaintMap()
{
	//异常检查
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	//步骤1：将mapMemoryDC截取区域绘制到mapShowMemoryDC中
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

	//步骤2：绘制网格
	if (isShowGrid)
	{
		PaintGird();
	}

	//步骤3：绘制选中区域
	if (nowMousePointElementIndex != -1)
	{
		PaintFocusGrid(nowMousePointElementIndex);
	}

	//步骤4：在mapDC上绘制mapMemoryDC
	mapDC->BitBlt(0, 0, mapElementShowRect.Width(), mapElementShowRect.Height(), mapShowMemoryDC, 0, 0, SRCCOPY);

}

//添加元素时的绘图
void CRPGScenarioEditorDlg::PaintMap_AddElement()
{
	//异常检查
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	if (willAddElementSrcIndex == -1 || willAddElementIndex == -1)
		return;

	if (paintType != 1)
		return;

	//步骤1：将mapMemoryDC截取区域绘制到mapShowMemoryDC中
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

	//步骤2：绘制临时图像

	//中心点绘图法（即：鼠标所指位置时当前该图片的中心点位置，因此需要计算出该图片的左上角位置）
	int drawX, drawY;//左上角坐标

	if (willAddElementType == L"静态")
	{

		//网格辅助
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
		//网格辅助
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


	//步骤3：绘制网格
	if (isShowGrid)
	{
		PaintGird();
	}



	//步骤4：绘制选中区域
	if (nowMousePointElementIndex != -1)
	{
		PaintFocusGrid(nowMousePointElementIndex);
	}

	mapDC->BitBlt(0, 0, mapElementShowRect.Width(), mapElementShowRect.Height(), mapShowMemoryDC, 0, 0, SRCCOPY);

}

//修改元素位置时的绘图
void CRPGScenarioEditorDlg::PaintMap_ChangeElement()
{
	//异常检查
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	if (willChangeElementSrcIndex == -1 || willChangeElementIndex == -1)
		return;

	if (paintType != 2)
		return;



	//步骤1：将mapMemoryDC截取区域绘制到mapShowMemoryDC中
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


	//绘制被选择对象的图片
	int drawX, drawY;//左上角坐标
	int drawW, drawH;//宽度和高度
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

	if (willChangeElementType == L"静态")
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


	//绘制网格
	if (isShowGrid)
	{
		PaintGird();
	}

	//绘制选中区域
	if (nowMousePointElementIndex != -1)
	{
		PaintFocusGrid(nowMousePointElementIndex);
	}

	//绘制移动对象的矩形
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

//重绘地图（重绘地图只是绘制在内存区域上，并没有真正显示地图出来）
void CRPGScenarioEditorDlg::RepaintMap()
{
	//异常检查
	if (mapDC == NULL || mapShowMemoryDC == NULL || mapMemoryDC == NULL)
		return;

	//步骤1：用背景填充整个地图
	mapMemoryDC->FillSolidRect(mapElementRect, RGB(255, 255, 255));

	//步骤2：将所有元素绘制在地图上
	int srcIndex;//图片素材索引
	int index;//元素索引

	for (int i = 0; i < gv->gameMap.gameMapElements.GetCount(); i++)
	{
		if (ignoreIndex == i)
		{
			continue;
		}
		if (gv->gameMap.gameMapElements[i].type == L"静态")
		{
			//从静态图片组中查找索引
			index = -1;
			for (int j = 0; j < gv->imageLoader->staticElementImages.GetCount(); j++)
			{
				if (gv->imageLoader->staticElementImages[j].id == gv->gameMap.gameMapElements[i].id)
				{
					index = j;
					break;
				}
			}

			//从图片素材中找到索引
			srcIndex = -1;
			for (int j = 0; j < gv->imageLoader->srcImages.GetCount(); j++)
			{
				if (gv->imageLoader->staticElementImages[index].imgID == gv->imageLoader->srcImages[j].imgID)
				{
					srcIndex = j;
					break;
				}
			}

			//绘制元素图片
			if (gv->imageLoader->staticElementImages[index].color != -1)//有透明色
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
			else//无透明色
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
			//从动态图片组中查找索引
			index = -1;
			for (int j = 0; j < gv->imageLoader->dynamicElementImages.GetCount(); j++)
			{
				if (gv->imageLoader->dynamicElementImages[j].id == gv->gameMap.gameMapElements[i].id)
				{
					index = j;
					break;
				}
			}




			//从图片素材中找到索引
			srcIndex = -1;
			for (int j = 0; j < gv->imageLoader->srcImages.GetCount(); j++)
			{
				if (gv->imageLoader->dynamicElementImages[index].imgID == gv->imageLoader->srcImages[j].imgID)
				{
					srcIndex = j;
					break;
				}
			}

			//计算出front中的第一张图片的位置
			EasyText et;
			int tempX, tempY;
			CStringArray divide;
			CStringArray divide1;
			et.DivideText(gv->imageLoader->dynamicElementImages[index].imageGroups, L";", divide);

			//判断是否自动播放
			if (gv->imageLoader->dynamicElementImages[index].autoPlay == L"" ||
				gv->imageLoader->dynamicElementImages[index].autoPlay == L"null"
				)
			{
				//使用default的标志
				for (int j = 0; j < divide.GetCount(); j++)
				{
					if (divide[j].Find(gv->imageLoader->dynamicElementImages[index].defalutTag) != -1)
					{
						if (divide[j].Find(L"/") == -1)//只有一张图片素材
							divide1.Add(et.Right(divide[j], L"="));
						else
							et.DivideText(et.Right(divide[j], L"="), L"/", divide1);
						break;
					}
				}
			}
			else
			{
				//使用autoplay的标志
				for (int j = 0; j < divide.GetCount(); j++)
				{
					if (divide[j].Find(gv->imageLoader->dynamicElementImages[index].autoPlay) != -1)
					{
						if (divide[j].Find(L"/") == -1)//只有一张图片素材
							divide1.Add(et.Right(divide[j], L"="));
						else
							et.DivideText(et.Right(divide[j], L"="), L"/", divide1);
						break;
					}
				}
			}
			tempX = _ttoi(et.Left(divide1.GetAt(0), L","));
			tempY = _ttoi(et.Right(divide1.GetAt(0), L","));

			//绘制元素图片
			if (gv->imageLoader->dynamicElementImages[index].color != -1)//有透明色
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
			else//无透明色
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

	//步骤3、绘制地图边框
	mapMemoryDC->MoveTo(0, 0);
	mapMemoryDC->LineTo(mapElementRect.Width(), 0);
	mapMemoryDC->LineTo(mapElementRect.Width(), mapElementRect.Height());
	mapMemoryDC->LineTo(0, mapElementRect.Height());
	mapMemoryDC->MoveTo(0, 0);

	paintType = 0;
}

//绘制网格
void CRPGScenarioEditorDlg::PaintGird()
{

	int nowX, nowY;

	nowX = int(mapElementShowRect.left / girdWidth)*girdWidth;
	nowY = int(mapElementShowRect.top / girdHeigth)*girdHeigth;

	CPen pen;
	pen.CreatePen(PS_DOT, 1, girdColor);
	CPen *oldPen = (CPen*)mapShowMemoryDC->SelectObject(&pen);

	//绘制竖线
	while (nowX <= mapElementShowRect.left + mapElementShowRect.Width())
	{
		mapShowMemoryDC->MoveTo(nowX - mapElementShowRect.left, 0);
		mapShowMemoryDC->LineTo(nowX - mapElementShowRect.left, mapElementShowRect.Height());
		nowX = nowX + girdWidth;
	}

	//绘制横线
	while (nowY <= mapElementShowRect.top + mapElementShowRect.Height())
	{
		mapShowMemoryDC->MoveTo(0, nowY - mapElementShowRect.top);
		mapShowMemoryDC->LineTo(mapElementShowRect.Width(), nowY - mapElementShowRect.top);
		nowY = nowY + girdHeigth;
	}

	mapShowMemoryDC->SelectObject(oldPen);
	DeleteObject(pen);

}

//绘制选中元素
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

//绘制矩形的外边框
void CRPGScenarioEditorDlg::PaintOuterRect(CDC * dc, int x, int y, int w, int h, int penType, int penSize, COLORREF color)
{
	if (dc == NULL)
	{
		return;
	}

	CPen pen;
	pen.CreatePen(penType, penSize, color);
	CPen *oldPen = dc->SelectObject(&pen);

	//要加上外边框
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

//添加元素开始
void CRPGScenarioEditorDlg::AddMapElementStart(CString id, CString type)
{
	//提供被添加的元素的ID和图片ID
	//注：左边元素ListCtrl被双击事件，顶部“加入”按钮点击事件
	//前提：isAddMapElement = false
	//结束：isAddMapElement = true

	if (isAddMapElement != false)
		return;

	willAddElementID = id;
	willAddElementType = type;

	//计算出素材索引和图片索引
	willAddElementIndex = -1;
	willAddElementSrcIndex = -1;
	if (willAddElementType == L"静态")
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
	else//动态
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
		AfxMessageBox(L"图片资源匹配错误！");
		exit(-1);
	}



	//计算出源图像的x和y位置
	if (willAddElementType == L"静态")
	{
		srcX = gv->imageLoader->staticElementImages[willAddElementIndex].x;
		srcY = gv->imageLoader->staticElementImages[willAddElementIndex].y;
	}
	else
	{
		//查找动态图的第一张图片
		EasyText et;
		CStringArray divide;
		CStringArray divide1;
		et.DivideText(gv->imageLoader->dynamicElementImages[willAddElementIndex].imageGroups, L";", divide);

		//判断是否自动播放
		if (gv->imageLoader->dynamicElementImages[willAddElementIndex].autoPlay == L"" ||
			gv->imageLoader->dynamicElementImages[willAddElementIndex].autoPlay == L"null"
			)
		{
			//使用default的标志
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willAddElementIndex].defalutTag) != -1)
				{
					if (divide[i].Find(L"/") == -1)//只有一张图片素材
						divide1.Add(et.Right(divide[i], L"="));
					else
						et.DivideText(et.Right(divide[i], L"="), L"/", divide1);
					break;
				}
			}
		}
		else
		{
			//使用autoplay的标志
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willAddElementIndex].autoPlay) != -1)
				{
					if (divide[i].Find(L"/") == -1)//只有一张图片素材
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
	备忘：
	2、在PaintMap_AddElement里完成临时图片的绘制

	*/



	PaintMap();

	isAddMapElement = true;
}

//添加元素中
void CRPGScenarioEditorDlg::AddMapElementNow(int x, int y)
{
	//注：鼠标位置改变事件
	//前提：isAddMapElement = true
	if (isAddMapElement != true)
		return;

	static int lastX = -1, lastY = -1;
	if (lastX != x || lastY != y)
	{
		//鼠标位置改变
		lastX = x;
		lastY = y;
		PaintMap_AddElement();
	}

}

//添加元素取消
void CRPGScenarioEditorDlg::AddMapElementCancel()
{
	//注：中间StaticText鼠标右键点击事件，顶部“加入”按钮点击事件，左边元素ListCtrl表项被改变事件
	//前提：isAddMapElement = true
	//结束：isAddMapElement = false
	if (isAddMapElement != true)
		return;

	willAddElementID = L"";
	willAddElementType = L"";

	willAddElementIndex = -1;
	willAddElementSrcIndex = -1;

	isAddMapElement = false;
}

//添加元素结束
void CRPGScenarioEditorDlg::AddMapElementEnd(int x, int y)
{
	//提供最终鼠标点选的位置（相对于静态文本框）
	//注：鼠标左键点击事件
	//前提：isAddMapElement = true
	//结束：isAddMapElement = false

	if (isAddMapElement != true)
		return;


	//往ListCtrl里添加一项
	m_listMapElement.InsertItem(m_listMapElement.GetItemCount(), NULL);

	CString temp;
	temp.Format(L"%d", m_listMapElement.GetItemCount());
	m_listMapElement.SetItemText(m_listMapElement.GetItemCount() - 1, 0, temp);
	m_listMapElement.SetItemText(m_listMapElement.GetItemCount() - 1, 1, willAddElementID);
	m_listMapElement.SetItemText(m_listMapElement.GetItemCount() - 1, 2, willAddElementType);

	int addX, addY;
	addX = girdWidth * int((x + mapElementShowRect.left) / girdWidth);
	addY = girdHeigth * int((y + mapElementShowRect.top) / girdHeigth);

	//当前的x和y是那个对象的中心位置
	if (willAddElementType == L"静态")
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

//修改元素位置开始
void CRPGScenarioEditorDlg::ChangeMapElementPositionStart(int index)
{
	//提供被修改的元素的索引（ListCtrl上的下标）
	//注：鼠标左键按下事件
	//前提：isChangeMapElement = false
	//结束：isChangeMapElement = true
	if (isChangeMapElement != false)
		return;
	if (index == -1)
		return;

	//记录位置
	ignoreIndex = index;

	//从ListCtrl中获取ID和Type
	willChangeElementID = m_listMapElement.GetItemText(index, 1);
	willChangeElementType = m_listMapElement.GetItemText(index, 2);

	//计算出素材索引和图片索引
	willChangeElementIndex = -1;
	willChangeElementSrcIndex = -1;
	if (willChangeElementType == L"静态")
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
	else//动态
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
		AfxMessageBox(L"图片资源匹配错误！");
		exit(-1);
	}

	//计算该对象的图片在源素材图像的x和y位置
	if (willChangeElementType == L"静态")
	{
		srcX = gv->imageLoader->staticElementImages[willChangeElementIndex].x;
		srcY = gv->imageLoader->staticElementImages[willChangeElementIndex].y;
	}
	else
	{
		//查找动态图的第一张图片
		EasyText et;
		CStringArray divide;
		CStringArray divide1;
		et.DivideText(gv->imageLoader->dynamicElementImages[willChangeElementIndex].imageGroups, L";", divide);

		//判断是否自动播放
		if (gv->imageLoader->dynamicElementImages[willChangeElementIndex].autoPlay == L"" ||
			gv->imageLoader->dynamicElementImages[willChangeElementIndex].autoPlay == L"null"
			)
		{
			//使用default的标志
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willChangeElementIndex].defalutTag) != -1)
				{
					if (divide[i].Find(L"/") == -1)//只有一张图片素材
						divide1.Add(et.Right(divide[i], L"="));
					else
						et.DivideText(et.Right(divide[i], L"="), L"/", divide1);
					break;
				}
			}
		}
		else
		{
			//使用autoplay的标志
			for (int i = 0; i < divide.GetCount(); i++)
			{
				if (divide[i].Find(gv->imageLoader->dynamicElementImages[willChangeElementIndex].autoPlay) != -1)
				{
					if (divide[i].Find(L"/") == -1)//只有一张图片素材
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

	//计算鼠标点击相对于选中图片的位置
	int a = mouseInMapPoint.x;
	a = mapElementShowRect.left;
	a = gv->gameMap.gameMapElements[index].x;

	offsetX = mouseInMapPoint.x + mapElementShowRect.left - gv->gameMap.gameMapElements[index].x;
	offsetY = mouseInMapPoint.y + mapElementShowRect.top - gv->gameMap.gameMapElements[index].y;

	//重绘底图
	RepaintMap();
	PaintMap_ChangeElement();

	//修改绘图属性
	paintType = 2;

	 
	isChangeMapElement = true;
}

//修改元素位置中
void CRPGScenarioEditorDlg::ChangeMapElementPositionNow(int x, int y)
{
	//提供鼠标相对于静态文本框左上角的位置
	//注：鼠标位置改变事件
	//前提：isChangeMapElement = true
	if (isChangeMapElement != true)
		return;

	static int lastX = -1, lastY = -1;
	if (lastX != x || lastY != y)
	{
		//鼠标位置改变
		lastX = x;
		lastY = y;
		paintType = 2;
		mouseInMapPoint.x = x;
		mouseInMapPoint.y = y;
		PaintMap_ChangeElement();
	}
}

//修改元素位置取消
void CRPGScenarioEditorDlg::ChangeMapElementPositionCancel()
{
	//注：鼠标右键点击事件
	//前提：isChangeMapElement = true
	//结束：isChangeMapElement = false
	if (isChangeMapElement != true)
		return;

	willChangeElementID = L"";
	willChangeElementType = L"";

	willChangeElementIndex = -1;
	willChangeElementSrcIndex = -1;

	ignoreIndex = -1;
	isChangeMapElement = false;

	//重绘地图
	RepaintMap();
	PaintMap();

	paintType = 0;
}

//修改元素位置结束
void CRPGScenarioEditorDlg::ChangeMapElementPositionEnd(int x, int y)
{
	//注：鼠标左键放开事件
	//传入鼠标相对于StaitcText左上角的位置
	//前提：isChangeMapElement = true
	//结束：isChangeMapElement = false
	if (isChangeMapElement != true)
		return;

	//网格辅助
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

	//置选中对象
	nowMousePointElementIndex = ignoreIndex;

	//取消忽略元素
	ignoreIndex = -1;

	//重绘地图
	RepaintMap();
	paintType = 0;
	PaintMap();

	isChangeMapElement = false;
}

//从图片素材资源中查找索引，查找失败返回-1
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

//从静态图片中查找索引，查找失败返回-1
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

//从动态图片中查找索引，查找失败返回-1
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

//触发器列表表项被改变
void CRPGScenarioEditorDlg::OnTriggerSelectChange(int index)
{
	//清除数据
	m_listTriggerAction.DeleteAllItems();
	SetDlgItemText(IDC_EDIT_STORY, L"");

	//判断选择位置
	if (index == -1)
	{
		return;
	}

	//获取动作列表
	TriggerScript triggerScript;
	triggerAnalyzer.GetTriggerInfo(m_listElementTrigger.GetItemText(index, 1), triggerScript);
	actionAnalyzer.LoadActions(triggerScript.actions, triggerScript.actionCount);

	if (triggerScript.actionCount == 0)
	{
		return;
	}

	//显示动作列表
	CString temp;
	Action tempAction;

	for (int i = 0; i < triggerScript.actionCount; i++)
	{
		temp.Format(L"%d", i + 1);
		m_listTriggerAction.InsertItem(i, NULL);
		m_listTriggerAction.SetItemText(i, 0, temp);//序号

		actionAnalyzer.GetActionInfo(i, tempAction);
		m_listTriggerAction.SetItemText(i, 1, tempAction.name);//序号

		m_listTriggerAction.SetItemText(i, 2, tempAction.execute ? L"true" : L"false");//是否开启
	}

	//调整列宽
	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listTriggerAction);
}

//动作列表表项被改变
void CRPGScenarioEditorDlg::OnActionSelectChange(int index)
{
	if (index == -1)
	{
		return;
	}

	//获取动作信息
	Action action;
	actionAnalyzer.GetActionInfo(m_listTriggerAction.GetItemText(index, 1), action);

	//显示动作脚本信息
	SetDlgItemText(IDC_EDIT_STORY, action.params);
}

//显示当前选中元素的信息
void CRPGScenarioEditorDlg::ShowNowChooseInfo()
{
	static int lastChoose = -1;
	if (lastChoose != nowMousePointElementIndex)
	{
		lastChoose = nowMousePointElementIndex;//选中项改变
	}
	else
	{
		return;
	}

	//设置动作脚本文本
	SetDlgItemText(IDC_EDIT_STORY, L"");

	//当前没有选中项目
	if (nowMousePointElementIndex == -1)
	{
		SetDlgItemText(IDC_STATIC_NOW_ID, L"---");		//设置ID
		SetDlgItemText(IDC_STATIC_NOW_TYPE, L"---");	//设置类型
		SetDlgItemText(IDC_STATIC_NOW_X, L"---");		//设置x
		SetDlgItemText(IDC_STATIC_NOW_Y, L"---");		//设置y
		m_checkBoxNowChooseCanPass.SetCheck(BST_UNCHECKED);//设置“可否通过”
		return;
	}

#pragma region 基础信息显示
	//显示文本信息
	CString nowID = m_listMapElement.GetItemText(nowMousePointElementIndex, 1);
	CString nowType = m_listMapElement.GetItemText(nowMousePointElementIndex, 2);

	SetDlgItemText(IDC_STATIC_NOW_ID, nowID);		//设置ID
	SetDlgItemText(IDC_STATIC_NOW_TYPE, nowType);	//设置类型

	CString temp;

	temp.Format(L"%d", gv->gameMap.gameMapElements[nowMousePointElementIndex].x);
	SetDlgItemText(IDC_STATIC_NOW_X, temp);		//设置x

	temp.Format(L"%d", gv->gameMap.gameMapElements[nowMousePointElementIndex].y);
	SetDlgItemText(IDC_STATIC_NOW_Y, temp);		//设置y

	int index;
	if (gv->gameMap.gameMapElements[nowMousePointElementIndex].type == L"静态")
	{
		index = FindStaticIndex(gv->gameMap.gameMapElements[nowMousePointElementIndex].id);
		if (index != -1 && gv->imageLoader->staticElementImages[index].canPass)
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_CHECKED);//设置“可否通过”
		}
		else
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_UNCHECKED);//设置“可否通过”
		}
	}
	else
	{
		index = FindDynamicIndex(gv->gameMap.gameMapElements[nowMousePointElementIndex].id);
		if (index != -1 && gv->imageLoader->dynamicElementImages[index].canPass)
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_CHECKED);//设置“可否通过”
		}
		else
		{
			m_checkBoxNowChooseCanPass.SetCheck(BST_UNCHECKED);//设置“可否通过”
		}
	}


#pragma endregion

#pragma region 触发器信息显示
	//显示触发器信息
	triggerAnalyzer.LoadScript(gv->gameMap.gameMapElements[nowMousePointElementIndex].params);

	//清除数据
	m_listElementTrigger.DeleteAllItems();
	m_listTriggerAction.DeleteAllItems();

	//加入触发器信息
	TriggerScript triggerScript;
	EasyListCtrl elc;
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		if (triggerAnalyzer.IsTriggerExist(gv->triggerLoader.triggerInfos[i].name))
		{
			m_listElementTrigger.InsertItem(i, 0);

			//序号
			temp.Format(L"%d", i + 1);
			m_listElementTrigger.SetItemText(i, 0, temp);

			//触发器名
			triggerAnalyzer.GetTriggerInfo(gv->triggerLoader.triggerInfos[i].name, triggerScript);
			m_listElementTrigger.SetItemText(i, 1, triggerScript.name);

			//动作数
			temp.Format(L"%d", triggerScript.actionCount);
			m_listElementTrigger.SetItemText(i, 2, temp);

			//是否开启
			m_listElementTrigger.SetItemText(i, 3, triggerScript.execute ? L"true" : L"false");

		}
	}

	//调整列宽
	elc.AdjustColumnWidth(m_listElementTrigger);

#pragma endregion





#pragma region 与触发编辑器交互
	//向触发器编辑器发送消息
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

//绘制当前选中元素的缩略图
void CRPGScenarioEditorDlg::PaintNowChoose()
{
	//初始化
	if (mapNowChooseDC == NULL)
	{
		mapNowChooseDC = m_staticTextNowMapChooes.GetDC();			//获取设备
		m_staticTextNowMapChooes.GetClientRect(mapNowChooseDCRect);	//获取宽度
		mapNowChooseMemoyDC->CreateCompatibleDC(NULL);				//创建缓冲区设备
		bmpMapNowChoose.CreateBitmap(								//创建对应的位图
			mapNowChooseDCRect.Width(),
			mapNowChooseDCRect.Height(),
			1, 32, NULL
		);
		CBitmap* oldBitmap = mapNowChooseDC->SelectObject(&bmpMapNowChoose);//选择刚刚新建的位图
		oldBitmap->DeleteObject();//删除旧画板
	}


}

//获取鼠标点击处的元素的索引（如果鼠标处点击的没有元素，则返回-1）
int CRPGScenarioEditorDlg::GetPointElementIndex(int x, int y)
{
	if (hasCreatMap == false)
		return -1;

	//查找鼠标是否进入了矩形（从末尾往前找，这样可以获取最上层的那个矩形）
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

//是否点在矩形内（包含边界）
inline bool CRPGScenarioEditorDlg::isPointInRect(CRect & rect, int left, int top)
{
	if (left >= rect.left && left <= rect.left + rect.right &&
		top >= rect.top && top <= rect.top + rect.bottom
		)
		return true;
	else
		return false;
}

//点的坐标是否落在中间大的StaticText控件内
bool CRPGScenarioEditorDlg::isPointInMap(CPoint & point)
{
	//判断鼠标是否点击了中间那个大的StaticText
	CRect rect;
	m_map.GetWindowRect(rect);
	ScreenToClient(&rect);

	if (isPointInRect(rect, point.x, point.y))
		return true;
	else
		return false;
}

//热键 Ctrl + S 保存地图
void CRPGScenarioEditorDlg::OnHotkeyCtrlS()
{
	if (hasCreatMap)
	{
		OnBnClickedButtonFileSave();
	}
}

//热键 Ctrl + C 复制元素
void CRPGScenarioEditorDlg::OnHotkeyCtrlC()
{
	if ( hasCreatMap == true && nowMousePointElementIndex != -1
		&& isAddMapElement == false && isChangeMapElement == false)
	{
		//获取当前选择元素的ID和类型
		CString nowID, nowType;
		nowID = m_listMapElement.GetItemText(nowMousePointElementIndex, 1);
		nowType = m_listMapElement.GetItemText(nowMousePointElementIndex, 2);

		//调用添加元素
		AddMapElementStart(nowID, nowType);
	}

	
}

//热键 Delete 删除元素
void CRPGScenarioEditorDlg::OnHotkeyDelete()
{
	if (hasCreatMap==false || nowMousePointElementIndex==-1)
	{
		return;
	}
	OnBnClickedButtonDel();
}

//热键 Ctrl + N 新建地图
void CRPGScenarioEditorDlg::OnHotkeyCtrlN()
{
	OnBnClickedButtonFileNew();
}

//热键 Ctrl + O 打开地图
void CRPGScenarioEditorDlg::OnHotkeyCtrlO()
{
	OnBnClickedButtonFileLoad();
}

//本程序的初始化函数
void CRPGScenarioEditorDlg::MyInit()
{
	//置随机数种子
	srand((unsigned)time(NULL));

	//获取共享数据类
	gv = GV::GetInstance();

	//初始化资源
	gv->LoadImageSrc();
	gv->LoadAllMap();
	gv->LoadUserData();


#pragma region 将图片数据加入ListCtrl
	EasyListCtrl elc;
	m_list.InsertColumn(0, L"#");
	m_list.InsertColumn(1, L"名称");
	m_list.InsertColumn(2, L"类型");
	m_list.InsertColumn(3, L"宽度");
	m_list.InsertColumn(4, L"高度");

	//加入静态资源
	CString temp;
	int count;//list当前的item数
	for (int i = 0; i < gv->imageLoader->staticElementImages.GetCount(); i++)
	{
		temp.Format(L"%d", i + 1);
		m_list.InsertItem(i, temp);//标题

		m_list.SetItemText(i, 1, gv->imageLoader->staticElementImages[i].id);
		m_list.SetItemText(i, 2, L"静态");

		temp.Format(L"%d", gv->imageLoader->staticElementImages[i].w);
		m_list.SetItemText(i, 3, temp);

		temp.Format(L"%d", gv->imageLoader->staticElementImages[i].h);
		m_list.SetItemText(i, 4, temp);
	}
	count = m_list.GetItemCount();


	//加入动态资源
	for (int i = 0; i < gv->imageLoader->dynamicElementImages.GetCount(); i++)
	{
		temp.Format(L"%d", count + i);
		m_list.InsertItem(i + count, temp);//标题

		m_list.SetItemText(i + count, 1, gv->imageLoader->dynamicElementImages[i].id);
		m_list.SetItemText(i + count, 2, L"动态");

		temp.Format(L"%d", gv->imageLoader->dynamicElementImages[i].w);
		m_list.SetItemText(i + count, 3, temp);

		temp.Format(L"%d", gv->imageLoader->dynamicElementImages[i].h);
		m_list.SetItemText(i + count, 4, temp);
	}


	//设置风格
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格

	elc.AdjustColumnWidth(m_list);
#pragma endregion

#pragma region 左下角缩略图初始化
	//初始化左下角的元素缩略图
	m_elementImage.GetWindowRect(&elementDrawRect);//获取控件的屏幕坐标
	ScreenToClient(&elementDrawRect);
	pElementImageDC = m_elementImage.GetDC();//获取StaticText控件的设备句柄
	nowImageIndex = -1;//置当前元素ListCtrl的选择项为-1（因为程序刚启动时用户没有选择表项）

	//将画布设置和缩略图框的大小相同
	bmpElementBitmap.CreateCompatibleBitmap(pElementImageDC, elementDrawRect.Width(), elementDrawRect.Height());

	//将缩略图内存DC与缩略图DC关联
	pElementImageMemoryDC = new CDC();
	pElementImageMemoryDC->CreateCompatibleDC(pElementImageDC);

	//清除旧的画板
	oldBmpElementBitmap = pElementImageMemoryDC->SelectObject(&bmpElementBitmap);
	oldBmpElementBitmap->DeleteObject();
#pragma endregion

#pragma region 触发编辑器初始化

	gv->triggerLoader.LoadTriggerConfig();


	//触发器ListCtrl
	m_listElementTrigger.InsertColumn(0, L"#");
	m_listElementTrigger.InsertColumn(1, L"名称");
	m_listElementTrigger.InsertColumn(2, L"动作数");
	m_listElementTrigger.InsertColumn(3, L"开启");

	//调整列宽
	elc.AdjustColumnWidth(m_listElementTrigger);


	//设置风格
	dwStyle = m_listElementTrigger.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listElementTrigger.SetExtendedStyle(dwStyle); //设置扩展风格


	//动作列表ListCtrl
	m_listTriggerAction.InsertColumn(0, L"#");
	m_listTriggerAction.InsertColumn(1, L"名称");
	m_listTriggerAction.InsertColumn(2, L"开启");

	//设置风格
	dwStyle = m_listTriggerAction.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listTriggerAction.SetExtendedStyle(dwStyle); //设置扩展风格

	//调整列宽
	elc.AdjustColumnWidth(m_listTriggerAction);

#pragma endregion

#pragma region 地图初始化
	isShowGrid = true;				//关闭显示网格
	m_checkBoxGrid.SetCheck(BST_CHECKED);//默认开启网格辅助
	girdColor = 8421504;			//网格默认颜色 = #灰色
	selectIndex = -1;				//没有选中元素
	hasCreatMap = false;			//已经新建地图 = false
	hasCloseMap = true;				//已经关闭地图 = true
	paintType = -1;					//地图绘制关闭
	ignoreIndex = -1;				//地图绘制忽略索引 = -1

	//添加元素的相关变量初始化
	isAddMapElement = false;		//正在添加元素 = false
	willAddElementSrcIndex = -1;
	willAddElementIndex = -1;

	//修改元素位置的相关变量初始化
	isChangeMapElement = false;		//正在修改元素位置 = false
	willChangeElementSrcIndex = -1;
	willChangeElementIndex = -1;

	//滚动条初始化
	scrollBarPerChange = 10;

	//获取地图画板DC
	mapDC = m_map.GetDC();

	//禁用滚动条
	m_scrollBarX.EnableScrollBar(ESB_DISABLE_BOTH);
	m_scrollBarY.EnableScrollBar(ESB_DISABLE_BOTH);

	//右边ListCtrl初始化
	m_listMapElement.InsertColumn(0, L"#");
	m_listMapElement.InsertColumn(1, L"ID");
	m_listMapElement.InsertColumn(2, L"类型");
	m_listMapElement.InsertColumn(3, L"层");
	elc.AdjustColumnWidth(m_listMapElement);

	//设置风格
	dwStyle = m_listMapElement.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listMapElement.SetExtendedStyle(dwStyle); //设置扩展风格


	//画板位置初始化
	m_map.GetWindowRect(&mapStaticTextRect);//获取控件的屏幕坐标
	ScreenToClient(&mapStaticTextRect);


#pragma endregion

#pragma region 地图选中元素相关初始化




#pragma endregion

#pragma region 注册热键
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_S, MOD_CONTROL, 83);	//Ctrl + s	保存地图
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_C, MOD_CONTROL, 67);	//Ctrl + c	复制元素
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_DELETE, NULL, 46);			//Delete	删除元素

	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_N, MOD_CONTROL, 78);	//Ctrl + n	新建地图
	RegisterHotKey(this->GetSafeHwnd(), ID_HOTKEY_CTRL_O, MOD_CONTROL, 79);	//Ctrl + o	打开地图

#pragma endregion


}

//本程序在关闭前执行的函数
void CRPGScenarioEditorDlg::MyClose()
{
	ReleaseDC(pElementImageDC);//释放元素缩略图画布句柄
	gv->imageLoader->BeginRelease();

	//释放左下角缩略图设备
	if (pElementImageMemoryDC != NULL)
		pElementImageMemoryDC->DeleteDC();
	if (pElementImageDC != NULL)
		pElementImageDC->DeleteDC();
	bmpElementBitmap.DeleteObject();

	//关闭地图
	CloseMap();
	mapDC->DeleteDC();


	//释放程序右上角缩略图的相关设备
	if (mapNowChooseDC != NULL)
	{
		mapNowChooseDC->DeleteDC();
		mapNowChooseMemoyDC->DeleteDC();
		bmpMapNowChoose.DeleteObject();
	}
}

//程序即将关闭
void CRPGScenarioEditorDlg::OnClose()
{

	MyClose();
	CDialogEx::OnCancel();//屏蔽该句代码可以禁止程序关闭
}

//注册按钮
void CRPGScenarioEditorDlg::OnBnClickedButton3Login()
{
	int iWidth = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
	CRect rect;

	//窗口未创建
	if (dlgLogin.GetSafeHwnd() == 0)
		dlgLogin.Create(IDD_DIALOG_LOGIN);


	dlgLogin.GetWindowRect(rect);

	//居中显示
	dlgLogin.MoveWindow(
		(iWidth - rect.Width()) / 2,
		(iHeight - rect.Height()) / 2,
		rect.Width(),
		rect.Height()
	);

	dlgLogin.ShowWindow(SW_SHOW);

}

//注销登录按钮
void CRPGScenarioEditorDlg::OnBnClickedButton3SignOut()
{
	if (gv->isLogin == false)
	{
		AfxMessageBox(L"您还未登录。");
		return;
	}
	gv->isLogin = false;
	AfxMessageBox(L"已注销登录。");
}

//新建地图消息（自定义消息）
afx_msg LRESULT CRPGScenarioEditorDlg::OnMyNewMap(WPARAM wParam, LPARAM lParam)
{
	EasyPath ep;
	gv->gameMap.SetPath(ep.GetProgramDir() + L"maps\\" + gv->gameMap.GetMapName() + L".map");
	gv->gameMap.CreatMap();
	CreatMap();
	AfxMessageBox(L"新建地图成功！");
	return 0;
}

//载入新建地图窗口
void CRPGScenarioEditorDlg::OnBnClickedButtonFileNew()
{
	//登录检测
	if (gv->isLogin==false)
	{
		AfxMessageBox(L"请先登录。");
		return;
	}


	int iWidth = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
	int iHeight = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
	CRect rect;

	//窗口未创建
	if (dlgNewMap.GetSafeHwnd() == 0)
		dlgNewMap.Create(IDD_DIALOG_NEW_MAP, this);

	dlgNewMap.GetWindowRect(rect);

	//居中显示
	dlgNewMap.MoveWindow(
		(iWidth - rect.Width()) / 2,
		(iHeight - rect.Height()) / 2,
		rect.Width(),
		rect.Height()
	);

	dlgNewMap.ShowWindow(SW_SHOW);
}

//鼠标点击左边元素
void CRPGScenarioEditorDlg::OnNMClickListElement(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	OnElementSelectChange(pLVCD->iItem);

	*pResult = 0;
}

//时钟消息
void CRPGScenarioEditorDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		TimerDynamicNextImage();//重绘地图元素
		break;
	case 2:
		TimerRepaint();//全局重绘事件
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

//删除元素按钮事件
void CRPGScenarioEditorDlg::OnBnClickedButtonDel()
{
	//检查地图是否打开
	if (hasCreatMap == false)
	{
		AfxMessageBox(L"地图未打开。");
		return;
	}

	//检查是否选中元素
	if (nowMousePointElementIndex == -1)
	{
		AfxMessageBox(L"请先选中元素。");
		return;
	}

	//检查是否正在添加元素或者移动元素
	if (isAddMapElement)
	{
		AfxMessageBox(L"请先取消添加元素。");
		return;
	}
	if (isChangeMapElement)
	{
		AfxMessageBox(L"请先完成移动元素。");
		return;
	}


	//删除元素
	gv->gameMap.gameMapElements.RemoveAt(nowMousePointElementIndex);

	//ListCtrl刷新显示
	m_listMapElement.DeleteAllItems();
	CString temp;
	for (int i = 0; i < gv->gameMap.gameMapElements.GetCount(); i++)
	{
		m_listMapElement.InsertItem(i, NULL);
		temp.Format(L"%d", i + 1);
		m_listMapElement.SetItemText(i, 0, temp);//序号
		m_listMapElement.SetItemText(i, 1, gv->gameMap.gameMapElements[i].id);//ID
		m_listMapElement.SetItemText(i, 2, gv->gameMap.gameMapElements[i].type);//类型

		temp.Format(L"%d", gv->gameMap.gameMapElements[i].index);
		m_listMapElement.SetItemText(i, 3, temp);//类型
	}

	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listMapElement);

	//修改选中
	nowMousePointElementIndex = -1;

	//重绘地图
	RepaintMap();
	PaintMap();
}

//主窗口窗口尺寸被更改
void CRPGScenarioEditorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//重新计算滑块条
	CalculateScrollBar(cx,cy);

	//重新计算显示区域
	//if (m_map.GetSafeHwnd() == 0)
	//{
	//	return;
	//}
	//int left, top;
	//left = mapElementShowRect.left;
	//top = mapElementShowRect.top;
	//m_map.GetClientRect(mapElementShowRect);//显示出来的矩形

	//mapElementShowRect.SetRect(left, top, mapElementShowRect.Width(), mapElementShowRect.Height());
	if (hasCreatMap)
	{
		bmpShowMap.DeleteObject();
		bmpShowMap.CreateBitmap(mapElementShowRect.Width(), mapElementShowRect.Height(), 1, 32, NULL);
		CBitmap* oldBitmap = mapShowMemoryDC->SelectObject(&bmpShowMap);
		if (oldBitmap != NULL)
		{
			oldBitmap->DeleteObject();//清除旧画板
		}

	}
	PaintMap();
	
}

//滑块条水平滚动事件
void CRPGScenarioEditorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	int tempPos = pScrollBar->GetScrollPos();
	int min, max;
	pScrollBar->GetScrollRange(&min, &max);
	switch (nSBCode)
	{
	case SB_THUMBPOSITION://拖动滑块
		pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT://点击左边的箭头
		if (tempPos > min)
			tempPos--;
		pScrollBar->SetScrollPos(tempPos);
		break;
	case SB_LINERIGHT://点击右边的箭头
		if (tempPos < max)
			tempPos++;
		pScrollBar->SetScrollPos(tempPos);
		break;
	}
	OnMapScrollValueChange(false);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//滑块条垂直滚动事件
void CRPGScenarioEditorDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int tempPos = pScrollBar->GetScrollPos();
	int min, max;
	pScrollBar->GetScrollRange(&min, &max);
	switch (nSBCode)                 //处理滚动信息
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

//鼠标左键按下事件
void CRPGScenarioEditorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//地图未创建
		return;

	//判断是否点击了StaticText
	if (isPointInMap(point) == false)
		return;

	//判断是否正在添加元素
	if (isAddMapElement == true)
	{

		AddMapElementEnd(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);


		isAddMapElement = false;
		AddMapElementStart(willAddElementID, willAddElementType);
		return;
	}

	//判断是否选中元素
	mouseInMapPoint.x = point.x - mapStaticTextRect.left;
	mouseInMapPoint.y = point.y - mapStaticTextRect.top;
	nowMousePointElementIndex = GetPointElementIndex(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);

	//与触发编辑器交互需要（是否选中了元素）
	if (nowMousePointElementIndex == -1)
		gv->nowIsChooesElement = false;
	else
		gv->nowIsChooesElement = true;

	//显示当前选择元素的信息
	ShowNowChooseInfo();

	EasyListCtrl elc;
	elc.SelectRow(m_listMapElement, nowMousePointElementIndex);
	if (nowMousePointElementIndex != -1 && isChangeMapElement == false)//鼠标选中了元素
	{
		ChangeMapElementPositionStart(nowMousePointElementIndex);
		return;
	}

	PaintMap();


	CDialogEx::OnLButtonDown(nFlags, point);
}

//鼠标左键抬起事件
void CRPGScenarioEditorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//地图未创建
		return;

	if (isChangeMapElement)
	{
		ChangeMapElementPositionEnd(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

//鼠标移动事件
void CRPGScenarioEditorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//地图未创建
		return;

	static bool isLastMouseInRect;//是否上次鼠标在矩形里
	//判断是否在StaticText内
	if (isPointInMap(point))
	{
		if (isChangeMapElement)//正在修改元素位置
		{
			ChangeMapElementPositionNow(point.x - mapStaticTextRect.left, point.y - mapStaticTextRect.top);
		}
		else if (isAddMapElement == true)//正在添加元素
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
		//原因：
		//当isLastMouseInRect为真的时候，说明上次鼠标还在StaticText内，然后这次鼠标离开了StaticText，
		//因此需要重绘StaticText区域，但是之后由于鼠标一直没有进入StaticText内，所以不用再次重绘了，
		//提高程序运行效率。
		if (isLastMouseInRect == true)
		{
			paintType = 0;
			PaintMap();
			isLastMouseInRect = false;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

//鼠标右键按下事件
void CRPGScenarioEditorDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (hasCreatMap == false)//地图未创建
		return;

	//判断是否点击了StaticText
	if (isPointInMap(point))
	{
		//正在添加元素
		if (isAddMapElement == true)
		{
			AddMapElementCancel();
			RepaintMap();//重绘地图
			PaintMap();//将地图刷新显示出来
			isAddMapElement = false;
			paintType = 0;
		}
		else if (isChangeMapElement)//正在修改元素位置
		{
			ChangeMapElementPositionCancel();
			paintType = 0;
		}
	}


	CDialogEx::OnRButtonDown(nFlags, point);
}

//添加元素按钮点击事件
void CRPGScenarioEditorDlg::OnBnClickedButtonAddElement()
{
	if (hasCreatMap == false)
	{
		AfxMessageBox(L"请先新建地图。");
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

//禁用回车键退出
void CRPGScenarioEditorDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

//禁用ESC键退出
void CRPGScenarioEditorDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}
/*
禁用回车、ESC键退出程序步骤
实际操作：
第一步，进入类向导，选中目标对话框对应的CXXXDlg类名。

第二步，选择“消息”选项卡，复写WM_CLOSE消息响应函数。

第三步，选择“虚函数”选项卡，复写OnCancel和OnOk两个函数。

第四步：在OnCancel和OnOk函数里屏蔽所有内容
*/

void CRPGScenarioEditorDlg::OnBnClickedButtonFileSave()
{
	//登录检测
	if (gv->isLogin == false)
	{
		AfxMessageBox(L"请先登录。");
		return;
	}


	if (hasCreatMap == true)
	{
		gv->gameMap.SaveGameMap();
		AfxMessageBox(L"地图已保存。");
		PaintMap();
	}
	else
	{
		AfxMessageBox(L"请先新建地图。");
	}
}

//加载地图消息（自定义消息）
afx_msg LRESULT CRPGScenarioEditorDlg::OnMyLoadMap(WPARAM wParam, LPARAM lParam)
{
	//关闭地图
	if (hasCreatMap)
	{
		CloseMap();
	}

	//加载地图
	gv->gameMap.LoadGameMap();

	//创建地图
	CreatMap();

	//中间ListCtrl初始化
	m_listMapElement.DeleteAllItems();
	CString temp;
	for (int i = 0; i < gv->gameMap.gameMapElements.GetCount(); i++)
	{
		m_listMapElement.InsertItem(i, NULL);
		temp.Format(L"%d", i + 1);
		m_listMapElement.SetItemText(i, 0, temp);//#

		m_listMapElement.SetItemText(i, 1, gv->gameMap.gameMapElements[i].id);//ID
		m_listMapElement.SetItemText(i, 2, gv->gameMap.gameMapElements[i].type);//类型

		temp.Format(L"%d", gv->gameMap.gameMapElements[i].index);
		m_listMapElement.SetItemText(i, 3, temp);//层
	}

	EasyListCtrl elc;
	elc.AdjustColumnWidth(m_listMapElement);

	return 0;
}

//加载地图按钮点击事件
void CRPGScenarioEditorDlg::OnBnClickedButtonFileLoad()
{
	//登录检测
	if (gv->isLogin == false)
	{
		AfxMessageBox(L"请先登录。");
		return;
	}


	if (hasCreatMap)
	{
		int temp = MessageBox(L"当前有正在编辑的地图，是否要保存？", L"询问", MB_ICONQUESTION | MB_YESNOCANCEL);
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

//网格辅助复选框被选中事件
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

//刷新显示地图
void CRPGScenarioEditorDlg::OnBnClickedButtonReflashMap()
{
	if (hasCreatMap)
	{
		PaintMap();
	}
}

//地图现有元素ListCtrl点击事件
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

//热键事件
void CRPGScenarioEditorDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{

	switch (nHotKeyId)
	{
	case ID_HOTKEY_CTRL_S://保存
		OnHotkeyCtrlS();
		break;
	case ID_HOTKEY_CTRL_C://复制
		OnHotkeyCtrlC();
		break;
	case ID_HOTKEY_CTRL_N://新建地图
		OnHotkeyCtrlN();
		break;
	case ID_HOTKEY_CTRL_O://打开文件
		OnHotkeyCtrlO();
		break;
	case ID_HOTKEY_DELETE://删除
		OnHotkeyDelete();
		break;

	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//触发脚本被修改（自定义消息）
afx_msg LRESULT CRPGScenarioEditorDlg::OnMyTriggerChange(WPARAM wParam, LPARAM lParam)
{
	//设置当前选中元素的触发器信息
	gv->gameMap.gameMapElements[nowMousePointElementIndex].params = gv->nowChooesElementTriggerScript;

#pragma region 触发器信息显示
	CString temp;

	//显示触发器信息
	triggerAnalyzer.LoadScript(gv->gameMap.gameMapElements[nowMousePointElementIndex].params);

#if _DEBUG
	int a = triggerAnalyzer.GetTriggerCount();
	a = gv->triggerLoader.triggerInfos.GetCount();
#endif // _DEBUG

	//清除数据
	m_listElementTrigger.DeleteAllItems();
	m_listTriggerAction.DeleteAllItems();

	//加入触发器信息
	TriggerScript triggerScript;
	EasyListCtrl elc;
	for (int i = 0; i < gv->triggerLoader.triggerInfos.GetCount(); i++)
	{
		CString temp1 = gv->triggerLoader.triggerInfos[i].name;
		if (triggerAnalyzer.IsTriggerExist(gv->triggerLoader.triggerInfos[i].name))
		{
			m_listElementTrigger.InsertItem(i, 0);

			//序号
			temp.Format(L"%d", i + 1);
			m_listElementTrigger.SetItemText(i, 0, temp);

			//触发器名
			triggerAnalyzer.GetTriggerInfo(gv->triggerLoader.triggerInfos[i].name, triggerScript);
			m_listElementTrigger.SetItemText(i, 1, triggerScript.name);

			//动作数
			temp.Format(L"%d", triggerScript.actionCount);
			m_listElementTrigger.SetItemText(i, 2, temp);

			//是否开启
			m_listElementTrigger.SetItemText(i, 3, triggerScript.execute ? L"true" : L"false");

			//对于开启的触发器进行高亮显示
			if (triggerScript.execute)
			{
				elc.SelectRow(m_listElementTrigger, i, false);
			}
		}
	}

	//调整列宽
	elc.AdjustColumnWidth(m_listElementTrigger);
#pragma endregion

	return 0;
}

//窗口正在移动
void CRPGScenarioEditorDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);
	if (hasCreatMap)
	{
		PaintMap();
	}

	// TODO: 在此处添加消息处理程序代码
}

//窗口移动完毕
void CRPGScenarioEditorDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	if (hasCreatMap)
	{
		PaintMap();
	}
	// TODO: 在此处添加消息处理程序代码
}

//触发器ListCtrl表项被选中
void CRPGScenarioEditorDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	OnTriggerSelectChange(pLVCD->iItem);

	*pResult = 0;
}

//动作ListCtrl列表被选中
void CRPGScenarioEditorDlg::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NMLISTVIEW* pLVCD = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
	OnActionSelectChange(pLVCD->iItem);
	*pResult = 0;
}

//窗口激活状态被改变事件
void CRPGScenarioEditorDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	switch (nState)
	{
	case WA_ACTIVE:		//获得焦点
		KillTimer(2);
		SetTimer(2, 50, NULL);//每秒绘制20帧
		break;
	case WA_INACTIVE:	//失去焦点
		KillTimer(2);
		SetTimer(2, 100, NULL);//每秒绘制10帧
		break;
	default:
		break;
	}


	// TODO: 在此处添加消息处理程序代码
}

//地图重绘时钟
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

//ListCtrl删除选中元素
void CRPGScenarioEditorDlg::OnBnClickedButton8()
{
	OnBnClickedButtonDel();
}
