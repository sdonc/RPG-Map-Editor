
// RPG Scenario EditorDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DlgLogin.h"			//登录对话框
#include "DlgNewMap.h"			//新建地图窗口
#include "DlgLoadMap.h"			//加载地图窗口
#include "DlgTriggerEditor.h"	//触发编辑器窗口
#include "afxwin.h"

#define ID_HOTKEY_CTRL_S 1	//保存
#define ID_HOTKEY_CTRL_C 2	//复制
#define ID_HOTKEY_CTRL_N 3	//新建地图
#define ID_HOTKEY_CTRL_O 4	//打开文件
#define ID_HOTKEY_DELETE 5	//删除
#define ID_HOTKEY_SPACE  6	//空格


// CRPGScenarioEditorDlg 对话框
class CRPGScenarioEditorDlg : public CDialogEx
{

// 构造
public:
	CRPGScenarioEditorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RPGSCENARIOEDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	DECLARE_MESSAGE_MAP()
public:
	

	GV* gv;	//全局共享数据

#pragma region 初始化与关闭

	//本程序初始化函数
	void MyInit();

	//本程序的销毁
	void MyClose();

#pragma endregion

#pragma region 左下角元素信息相关
	//元素缩略图位置和大小
	CRect elementDrawRect;

	//元素缩略图的设备句柄
	CDC *pElementImageDC;

	//元素缩略图缓冲区与对应的位图
	CDC *pElementImageMemoryDC;
	CBitmap bmpElementBitmap;
	CBitmap* oldBmpElementBitmap;

	//绘制左下角的缩略图
	void PaintElement();

	//当左边元素列表框的选中项目改变（该函数用来计算一些选中项目的值）
	void OnElementSelectChange(int index);

	//当前左边ListCtrl选中项
	int nowElementChoose;

	//是否选中的是静态类型
	bool nowIsElementStatic;

	//当前资源索引
	int nowImageIndex;

	//当前图片素材索引
	int nowSrcImageIndex;

	//当前动态图片的图片组
	CArray<CPoint> nowElementImagePoint;

	//当前播放索引
	int nowPlayIndex;

	//当前选中元素的绘制位置
	int nowElementDrawX;
	int nowElementDrawY;

	//当前元素是否需要缩放显示
	bool nowIsElementZoom;

	//设置动态图片的下一帧
	void TimerDynamicNextImage();
#pragma endregion

#pragma region 地图元素相关
	/*
	渲染顺序
	1、地图背景
	2、地图元素
	3、临时对象（比如用户拖拽某个某个元素移动）
	4、地图网格（如果用户勾选网格辅助）
	5、选中对象（用户选中了某个对象，则在地图上绘制这个对象的矩形框）
	*/

	CDC* mapMemoryDC;			//地图缓冲
	CDC* mapShowMemoryDC;		//显示出来的地图缓冲
	CDC* mapDC;					//地图中间StaticText的画板DC

	CBitmap bmpMap;				//地图缓冲区位图
	CBitmap bmpShowMap;			//显示出来的地图缓冲区

	CRect mapElementShowRect;	//显示出来的矩形
	CRect mapElementRect;		//整个地图矩形
	CRect mapStaticTextRect;	//绘制地图的StaticRect的矩形（左边、顶边、宽度、高度）

	bool isShowGrid;			//是否使用网格辅助设计
	int girdColor;				//网格颜色（默认：品红色）

	const int girdWidth = 32;	//辅助网格宽度
	const int girdHeigth = 32;	//辅助网格高度

	int selectIndex;			//当前选中元素的矩形区域（-1表示没有选中）。注：在空白区域点击右键可以取消选中。

	//新建地图
	void CreatMap();
	bool hasCreatMap;			//是否已经新建好了地图（true = 已经新建；false = 未新建）

	//关闭地图
	void CloseMap();
	bool hasCloseMap;			//是否已经关闭了地图（true = 已经关闭；false = 未关闭）

	//滚动条改变值（默认是10像素）：即滚动条拖动一个像素等于实际地图拖动10个像素
	int scrollBarPerChange;

	//滚动条重计算
	void CalculateScrollBar(int cx,int cy);

	//地图滑块条位置被改变事件（vertical = true 表示垂直滚动条位置发生改变）
	void OnMapScrollValueChange(bool vertical);

	//重绘忽略的下标（如果该下标不为-1，则当重绘地图时遇到该下标则continue）
	int ignoreIndex;

	#pragma region 各类绘图事件
	int paintType;//-1=地图绘制关闭 0=PaintMap	1=PaintMap_AddElement  2=PaintMap_ChangeElement  3=RepaintMap

	//普通绘图（窗口大小改变，滑块条拖拽等）
	//刷新显示（合成位图），绘制网格，绘制选中矩形
	void PaintMap();
	
	//添加元素绘图
	void PaintMap_AddElement();

	//修改元素位置绘图
	void PaintMap_ChangeElement();

	//重绘地图（地图数据改变、程序读取完地图）
	//重绘背景、所有元素
	//注：该函数耗时较大，应尽量少用
	void RepaintMap();
	
	//绘制网格
	void PaintGird();

	//绘制选中元素
	void PaintFocusGrid(int index);

	//绘制外边框
	void PaintOuterRect(CDC* dc,int x,int y,int w,int h,int penType = PS_SOLID,int penSize=1, COLORREF color=0);

	//自动重绘时钟
	void TimerRepaint();
	#pragma endregion

	//添加元素与修改元素位置公共变量
	int srcX;//来自源素材的x（便于动态图片的绘制，如果没有这个则需要每次都查询一次位置，很耗费CPU）
	int srcY;//来自源素材的y
	CPoint mouseInMapPoint;//鼠标相对于StaitcText左上角的位置

	#pragma region 添加元素流程
	void AddMapElementStart(CString id, CString type);
	void AddMapElementNow(int x, int y);
	void AddMapElementCancel();
	void AddMapElementEnd(int x, int y);


	bool isAddMapElement;		//“添加元素”进度（true = 正在添加元素，false = 未开始/已经添加完元素）
	CString willAddElementID;
	CString willAddElementType;
	int willAddElementSrcIndex;	//图片索引（下标）
	int willAddElementIndex;	//素材索引（就是静态资源或动态资源的下标）
	#pragma endregion


	#pragma region 修改元素位置流程
	void ChangeMapElementPositionStart(int index);
	void ChangeMapElementPositionNow(int x, int y);
	void ChangeMapElementPositionCancel();
	void ChangeMapElementPositionEnd(int x, int y);

	bool isChangeMapElement;		//“修改元素位置”进度（true = 正在修改位置，false = 未开始/修改完毕）
	CString willChangeElementID;
	CString willChangeElementType;
	int willChangeElementSrcIndex;	//图片索引（下标）
	int willChangeElementIndex;		//素材索引（就是静态资源或动态资源的下标）
	int offsetX,offsetY;			//鼠标点击位置相对于那个被点击的矩形左上角的位置
	#pragma endregion

	//从图片素材资源中查找索引，查找失败返回-1
	int FindSrcIndex(CString imgID);

	//从静态图片中查找索引，查找失败返回-1
	int FindStaticIndex(CString id);

	//从动态图片中查找索引，查找失败返回-1
	int FindDynamicIndex(CString id);

	#pragma region 地图选中元素信息相关
	CDC* mapNowChooseDC;//地图当前选中缩略图设备
	CDC* mapNowChooseMemoyDC;//地图当前选中项缩略图缓冲
	CBitmap bmpMapNowChoose;//地图当前选中项缩略图位图
	CRect mapNowChooseDCRect;//地图当前选中项缩略图框矩形
	
	TriggerAnalyzer triggerAnalyzer;	//当前元素的触发器脚本
	ActionAnalyzer actionAnalyzer;		//当前元素的动作脚本

	//触发器列表表项被改变
	void OnTriggerSelectChange(int index);
	//int nowTriggerSelect;//当前触发器ListCtrl选中项

	//动作列表表项被改变
	void OnActionSelectChange(int index);
	//int nowActionSelect;//当前触发器ListCtrl选中项

	//显示当前选中元素的信息
	void ShowNowChooseInfo();

	//绘制当前选中元素的缩略图
	void PaintNowChoose();

	//获取鼠标点击处的元素的索引（如果鼠标处点击的没有元素，则返回-1）
	int GetPointElementIndex(int x, int y);
	int nowMousePointElementIndex;//当前鼠标选中（或者ListCtrl选中）的所对应的ListCtrl下标

	//点的坐标是否落在矩形内
	bool isPointInRect(CRect &rect, int left, int top);

	//点的坐标是否落在中间大的StaticText控件内
	bool isPointInMap(CPoint &point);
	#pragma endregion

#pragma endregion

#pragma region 热键相关

	//保存
	void OnHotkeyCtrlS();

	//复制
	void OnHotkeyCtrlC();

	//新建地图
	void OnHotkeyCtrlN();

	//打开地图
	void OnHotkeyCtrlO();

	//删除元素
	void OnHotkeyDelete();

#pragma endregion

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonFileNew();
	afx_msg void OnNMClickListElement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3Login();
	afx_msg void OnBnClickedButton3SignOut();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonAddElement();
	afx_msg void OnBnClickedButtonFileSave();
	afx_msg void OnBnClickedButtonFileLoad();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButtonReflashMap();
	afx_msg void OnNMClickListMapElement(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton8();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg LRESULT OnMyNewMap(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyLoadMap(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyTriggerChange(WPARAM wParam, LPARAM lParam);

	virtual void OnOK();
	virtual void OnCancel();
	
	CButton m_checkBoxGrid;					//是否显示网格
	CButton m_checkBoxNowChooseCanPass;		//当前选中的元素是否可以通过
	CButton m_checkElementCanPass;			//左边元素列表现行选中项是否可以通过
	CButton m_checkBoxTriggerActionEnable;	//是否启动动作
	CButton m_checkBoxShowTextEnable;		//是否启动显示文本

	CStatic m_staticTextNowMapChooes;		//当前选中元素缩略图
	CStatic m_elementImage;					//左下角元素缩略图
	CStatic m_map;							//地图绘图区

	CListCtrl m_listMapElement;				//地图元素列表（中间未知）
	CListCtrl m_listElementTrigger;			//触发器列表（右上角）
	CListCtrl m_listTriggerAction;			//动作列表（右边中间）
	CListCtrl m_list;						//元素列表（左边）
	
	CScrollBar m_scrollBarX;				//地图横向滚动条
	CScrollBar m_scrollBarY;				//地图纵向滚动条

	DlgLogin dlgLogin;						//登录对话框
	DlgNewMap dlgNewMap;					//新建地图对话框
	DlgTriggerEditor dlgTriggerEditor;		//触发编辑器对话框


	
};
