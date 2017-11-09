#pragma once

///  类名：EasyListCtrl（方便的超级列表框操作）

class EasyListCtrl
{
public:
	EasyListCtrl();
	~EasyListCtrl();

	/*
	函数名：自动调整列宽
	参数1 hwnd(必须)：ListCtrl句柄。Tip：可以使用 m_list.GetSaftHwnd()获取到。
	参数2 index(可空)：列索引（从0开始）。默认（index = -1）自动调整所有列的宽度。
	*/
	void AdjustColumnWidth(CListCtrl &cListCtrl, int index = -1);


	/*
	函数名：自动调整列宽
	参数1 hwnd(必须)：ListCtrl句柄。Tip：可以使用 m_list.GetSaftHwnd()获取到。
	参数2 index(必须)：列索引（从0开始）。
	参数3 single（可空）：（默认为 true）是否仅仅选中单行，true = 仅选中单行。
	如果要选中多行的话可以可以在第一次使用选择单行，然后第二
	次让single=false，之后再选中别的行
	*/
	void SelectRow(CListCtrl &cListctrl, int index, bool single = true);
};

