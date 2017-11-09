
// RPG Scenario EditorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DlgLogin.h"			//��¼�Ի���
#include "DlgNewMap.h"			//�½���ͼ����
#include "DlgLoadMap.h"			//���ص�ͼ����
#include "DlgTriggerEditor.h"	//�����༭������
#include "afxwin.h"

#define ID_HOTKEY_CTRL_S 1	//����
#define ID_HOTKEY_CTRL_C 2	//����
#define ID_HOTKEY_CTRL_N 3	//�½���ͼ
#define ID_HOTKEY_CTRL_O 4	//���ļ�
#define ID_HOTKEY_DELETE 5	//ɾ��
#define ID_HOTKEY_SPACE  6	//�ո�


// CRPGScenarioEditorDlg �Ի���
class CRPGScenarioEditorDlg : public CDialogEx
{

// ����
public:
	CRPGScenarioEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RPGSCENARIOEDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	DECLARE_MESSAGE_MAP()
public:
	

	GV* gv;	//ȫ�ֹ�������

#pragma region ��ʼ����ر�

	//�������ʼ������
	void MyInit();

	//�����������
	void MyClose();

#pragma endregion

#pragma region ���½�Ԫ����Ϣ���
	//Ԫ������ͼλ�úʹ�С
	CRect elementDrawRect;

	//Ԫ������ͼ���豸���
	CDC *pElementImageDC;

	//Ԫ������ͼ���������Ӧ��λͼ
	CDC *pElementImageMemoryDC;
	CBitmap bmpElementBitmap;
	CBitmap* oldBmpElementBitmap;

	//�������½ǵ�����ͼ
	void PaintElement();

	//�����Ԫ���б���ѡ����Ŀ�ı䣨�ú�����������һЩѡ����Ŀ��ֵ��
	void OnElementSelectChange(int index);

	//��ǰ���ListCtrlѡ����
	int nowElementChoose;

	//�Ƿ�ѡ�е��Ǿ�̬����
	bool nowIsElementStatic;

	//��ǰ��Դ����
	int nowImageIndex;

	//��ǰͼƬ�ز�����
	int nowSrcImageIndex;

	//��ǰ��̬ͼƬ��ͼƬ��
	CArray<CPoint> nowElementImagePoint;

	//��ǰ��������
	int nowPlayIndex;

	//��ǰѡ��Ԫ�صĻ���λ��
	int nowElementDrawX;
	int nowElementDrawY;

	//��ǰԪ���Ƿ���Ҫ������ʾ
	bool nowIsElementZoom;

	//���ö�̬ͼƬ����һ֡
	void TimerDynamicNextImage();
#pragma endregion

#pragma region ��ͼԪ�����
	/*
	��Ⱦ˳��
	1����ͼ����
	2����ͼԪ��
	3����ʱ���󣨱����û���קĳ��ĳ��Ԫ���ƶ���
	4����ͼ��������û���ѡ��������
	5��ѡ�ж����û�ѡ����ĳ���������ڵ�ͼ�ϻ����������ľ��ο�
	*/

	CDC* mapMemoryDC;			//��ͼ����
	CDC* mapShowMemoryDC;		//��ʾ�����ĵ�ͼ����
	CDC* mapDC;					//��ͼ�м�StaticText�Ļ���DC

	CBitmap bmpMap;				//��ͼ������λͼ
	CBitmap bmpShowMap;			//��ʾ�����ĵ�ͼ������

	CRect mapElementShowRect;	//��ʾ�����ľ���
	CRect mapElementRect;		//������ͼ����
	CRect mapStaticTextRect;	//���Ƶ�ͼ��StaticRect�ľ��Σ���ߡ����ߡ���ȡ��߶ȣ�

	bool isShowGrid;			//�Ƿ�ʹ�����������
	int girdColor;				//������ɫ��Ĭ�ϣ�Ʒ��ɫ��

	const int girdWidth = 32;	//����������
	const int girdHeigth = 32;	//��������߶�

	int selectIndex;			//��ǰѡ��Ԫ�صľ�������-1��ʾû��ѡ�У���ע���ڿհ��������Ҽ�����ȡ��ѡ�С�

	//�½���ͼ
	void CreatMap();
	bool hasCreatMap;			//�Ƿ��Ѿ��½����˵�ͼ��true = �Ѿ��½���false = δ�½���

	//�رյ�ͼ
	void CloseMap();
	bool hasCloseMap;			//�Ƿ��Ѿ��ر��˵�ͼ��true = �Ѿ��رգ�false = δ�رգ�

	//�������ı�ֵ��Ĭ����10���أ������������϶�һ�����ص���ʵ�ʵ�ͼ�϶�10������
	int scrollBarPerChange;

	//�������ؼ���
	void CalculateScrollBar(int cx,int cy);

	//��ͼ������λ�ñ��ı��¼���vertical = true ��ʾ��ֱ������λ�÷����ı䣩
	void OnMapScrollValueChange(bool vertical);

	//�ػ���Ե��±꣨������±겻Ϊ-1�����ػ��ͼʱ�������±���continue��
	int ignoreIndex;

	#pragma region �����ͼ�¼�
	int paintType;//-1=��ͼ���ƹر� 0=PaintMap	1=PaintMap_AddElement  2=PaintMap_ChangeElement  3=RepaintMap

	//��ͨ��ͼ�����ڴ�С�ı䣬��������ק�ȣ�
	//ˢ����ʾ���ϳ�λͼ�����������񣬻���ѡ�о���
	void PaintMap();
	
	//���Ԫ�ػ�ͼ
	void PaintMap_AddElement();

	//�޸�Ԫ��λ�û�ͼ
	void PaintMap_ChangeElement();

	//�ػ��ͼ����ͼ���ݸı䡢�����ȡ���ͼ��
	//�ػ汳��������Ԫ��
	//ע���ú�����ʱ�ϴ�Ӧ��������
	void RepaintMap();
	
	//��������
	void PaintGird();

	//����ѡ��Ԫ��
	void PaintFocusGrid(int index);

	//������߿�
	void PaintOuterRect(CDC* dc,int x,int y,int w,int h,int penType = PS_SOLID,int penSize=1, COLORREF color=0);

	//�Զ��ػ�ʱ��
	void TimerRepaint();
	#pragma endregion

	//���Ԫ�����޸�Ԫ��λ�ù�������
	int srcX;//����Դ�زĵ�x�����ڶ�̬ͼƬ�Ļ��ƣ����û���������Ҫÿ�ζ���ѯһ��λ�ã��ܺķ�CPU��
	int srcY;//����Դ�زĵ�y
	CPoint mouseInMapPoint;//��������StaitcText���Ͻǵ�λ��

	#pragma region ���Ԫ������
	void AddMapElementStart(CString id, CString type);
	void AddMapElementNow(int x, int y);
	void AddMapElementCancel();
	void AddMapElementEnd(int x, int y);


	bool isAddMapElement;		//�����Ԫ�ء����ȣ�true = �������Ԫ�أ�false = δ��ʼ/�Ѿ������Ԫ�أ�
	CString willAddElementID;
	CString willAddElementType;
	int willAddElementSrcIndex;	//ͼƬ�������±꣩
	int willAddElementIndex;	//�ز����������Ǿ�̬��Դ��̬��Դ���±꣩
	#pragma endregion


	#pragma region �޸�Ԫ��λ������
	void ChangeMapElementPositionStart(int index);
	void ChangeMapElementPositionNow(int x, int y);
	void ChangeMapElementPositionCancel();
	void ChangeMapElementPositionEnd(int x, int y);

	bool isChangeMapElement;		//���޸�Ԫ��λ�á����ȣ�true = �����޸�λ�ã�false = δ��ʼ/�޸���ϣ�
	CString willChangeElementID;
	CString willChangeElementType;
	int willChangeElementSrcIndex;	//ͼƬ�������±꣩
	int willChangeElementIndex;		//�ز����������Ǿ�̬��Դ��̬��Դ���±꣩
	int offsetX,offsetY;			//�����λ��������Ǹ�������ľ������Ͻǵ�λ��
	#pragma endregion

	//��ͼƬ�ز���Դ�в�������������ʧ�ܷ���-1
	int FindSrcIndex(CString imgID);

	//�Ӿ�̬ͼƬ�в�������������ʧ�ܷ���-1
	int FindStaticIndex(CString id);

	//�Ӷ�̬ͼƬ�в�������������ʧ�ܷ���-1
	int FindDynamicIndex(CString id);

	#pragma region ��ͼѡ��Ԫ����Ϣ���
	CDC* mapNowChooseDC;//��ͼ��ǰѡ������ͼ�豸
	CDC* mapNowChooseMemoyDC;//��ͼ��ǰѡ��������ͼ����
	CBitmap bmpMapNowChoose;//��ͼ��ǰѡ��������ͼλͼ
	CRect mapNowChooseDCRect;//��ͼ��ǰѡ��������ͼ�����
	
	TriggerAnalyzer triggerAnalyzer;	//��ǰԪ�صĴ������ű�
	ActionAnalyzer actionAnalyzer;		//��ǰԪ�صĶ����ű�

	//�������б����ı�
	void OnTriggerSelectChange(int index);
	//int nowTriggerSelect;//��ǰ������ListCtrlѡ����

	//�����б����ı�
	void OnActionSelectChange(int index);
	//int nowActionSelect;//��ǰ������ListCtrlѡ����

	//��ʾ��ǰѡ��Ԫ�ص���Ϣ
	void ShowNowChooseInfo();

	//���Ƶ�ǰѡ��Ԫ�ص�����ͼ
	void PaintNowChoose();

	//��ȡ���������Ԫ�ص������������괦�����û��Ԫ�أ��򷵻�-1��
	int GetPointElementIndex(int x, int y);
	int nowMousePointElementIndex;//��ǰ���ѡ�У�����ListCtrlѡ�У�������Ӧ��ListCtrl�±�

	//��������Ƿ����ھ�����
	bool isPointInRect(CRect &rect, int left, int top);

	//��������Ƿ������м���StaticText�ؼ���
	bool isPointInMap(CPoint &point);
	#pragma endregion

#pragma endregion

#pragma region �ȼ����

	//����
	void OnHotkeyCtrlS();

	//����
	void OnHotkeyCtrlC();

	//�½���ͼ
	void OnHotkeyCtrlN();

	//�򿪵�ͼ
	void OnHotkeyCtrlO();

	//ɾ��Ԫ��
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
	
	CButton m_checkBoxGrid;					//�Ƿ���ʾ����
	CButton m_checkBoxNowChooseCanPass;		//��ǰѡ�е�Ԫ���Ƿ����ͨ��
	CButton m_checkElementCanPass;			//���Ԫ���б�����ѡ�����Ƿ����ͨ��
	CButton m_checkBoxTriggerActionEnable;	//�Ƿ���������
	CButton m_checkBoxShowTextEnable;		//�Ƿ�������ʾ�ı�

	CStatic m_staticTextNowMapChooes;		//��ǰѡ��Ԫ������ͼ
	CStatic m_elementImage;					//���½�Ԫ������ͼ
	CStatic m_map;							//��ͼ��ͼ��

	CListCtrl m_listMapElement;				//��ͼԪ���б��м�δ֪��
	CListCtrl m_listElementTrigger;			//�������б����Ͻǣ�
	CListCtrl m_listTriggerAction;			//�����б��ұ��м䣩
	CListCtrl m_list;						//Ԫ���б���ߣ�
	
	CScrollBar m_scrollBarX;				//��ͼ���������
	CScrollBar m_scrollBarY;				//��ͼ���������

	DlgLogin dlgLogin;						//��¼�Ի���
	DlgNewMap dlgNewMap;					//�½���ͼ�Ի���
	DlgTriggerEditor dlgTriggerEditor;		//�����༭���Ի���


	
};
