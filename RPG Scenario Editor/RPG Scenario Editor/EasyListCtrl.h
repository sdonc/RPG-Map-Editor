#pragma once

///  ������EasyListCtrl������ĳ����б�������

class EasyListCtrl
{
public:
	EasyListCtrl();
	~EasyListCtrl();

	/*
	���������Զ������п�
	����1 hwnd(����)��ListCtrl�����Tip������ʹ�� m_list.GetSaftHwnd()��ȡ����
	����2 index(�ɿ�)������������0��ʼ����Ĭ�ϣ�index = -1���Զ����������еĿ�ȡ�
	*/
	void AdjustColumnWidth(CListCtrl &cListCtrl, int index = -1);


	/*
	���������Զ������п�
	����1 hwnd(����)��ListCtrl�����Tip������ʹ�� m_list.GetSaftHwnd()��ȡ����
	����2 index(����)������������0��ʼ����
	����3 single���ɿգ�����Ĭ��Ϊ true���Ƿ����ѡ�е��У�true = ��ѡ�е��С�
	���Ҫѡ�ж��еĻ����Կ����ڵ�һ��ʹ��ѡ���У�Ȼ��ڶ�
	����single=false��֮����ѡ�б����
	*/
	void SelectRow(CListCtrl &cListctrl, int index, bool single = true);
};

