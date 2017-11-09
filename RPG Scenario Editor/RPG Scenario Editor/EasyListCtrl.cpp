#include "stdafx.h"
#include "EasyListCtrl.h"


EasyListCtrl::EasyListCtrl()
{
}


EasyListCtrl::~EasyListCtrl()
{
}

void EasyListCtrl::AdjustColumnWidth(CListCtrl &cListCtrl, int index)
{
	if (index < -1)//λ�ò��Ϸ���ע������-1�ǵ��������е��п�
		return;

	HWND hWnd = cListCtrl.GetSafeHwnd();//��ȡListCtrl���ھ��
	if (hWnd == 0)
		return;

	int columns = cListCtrl.GetHeaderCtrl()->GetItemCount();//ȡ����
	if (index == -1)
	{
		for (int i = 0; i <columns; i++)
			SendMessageA(hWnd, 4126, i, -2);
	}
	else if(index<columns)
	{
		SendMessageA(hWnd, 4126, index, -2);
	}

	//SendMessageA(hWnd,4126,)
}


void EasyListCtrl::SelectRow(CListCtrl & cListctrl, int index, bool single)
{
	//�쳣���
	if (index == -1 || cListctrl.GetItemCount() == 0 || index > cListctrl.GetItemCount() - 1)
	{
		return;
	}

	//ȫ����ȡ��ѡ��
	if (single)
	{
		for (int i = 0; i < cListctrl.GetItemCount(); i++)
		{
			cListctrl.SetItemState(i, 0, LVIS_SELECTED | LVIS_FOCUSED);//ȡ��ѡ��
		}
	}

	//ѡ��ָ����
	cListctrl.EnsureVisible(index, FALSE); //�������Զ���������80��
	cListctrl.SetFocus();  //set list focus
	cListctrl.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED); //ѡ����

}