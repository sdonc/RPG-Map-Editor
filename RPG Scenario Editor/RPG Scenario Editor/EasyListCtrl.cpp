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
	if (index < -1)//位置不合法。注：输入-1是调整所有列的列宽
		return;

	HWND hWnd = cListCtrl.GetSafeHwnd();//获取ListCtrl窗口句柄
	if (hWnd == 0)
		return;

	int columns = cListCtrl.GetHeaderCtrl()->GetItemCount();//取列数
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
	//异常检测
	if (index == -1 || cListctrl.GetItemCount() == 0 || index > cListctrl.GetItemCount() - 1)
	{
		return;
	}

	//全部行取消选中
	if (single)
	{
		for (int i = 0; i < cListctrl.GetItemCount(); i++)
		{
			cListctrl.SetItemState(i, 0, LVIS_SELECTED | LVIS_FOCUSED);//取消选中
		}
	}

	//选中指定行
	cListctrl.EnsureVisible(index, FALSE); //滚动条自动滚动到第80行
	cListctrl.SetFocus();  //set list focus
	cListctrl.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED); //选中行

}