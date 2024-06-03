#ifndef CBLUEUI_LISTBOX_BLXDY_INC_H_
#define CBLUEUI_LISTBOX_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "CNodeCell.h"

namespace BUI {


/**
 * @brief 列表控件
 *
 */
class UI_EXP CListBoxUI : public CScrollAreaUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CListBoxUI)
  private:
	std::vector<std::shared_ptr<CCheckBoxCell>> m_vecItems;
	RoundRectRadius m_RoundRadiusHighlight; // 选中高亮圆角尺寸
	GImageIconInfo* m_pImgCheck[3];         // 复选框绘制图标(依次:未知，选中，未选中)
	CControlUI* m_pEditUI;                  // 编辑单元格控件
	int m_nMaxCapacity;                     // 限制元素个数，使用先进先出规则
	int m_nHighlightIndex;                  // 当前热点
	int m_nSelectedIndex;                   // 当前点击项
	int m_nFirstRowOfView;                  // 视区下显示的第一行
	int m_nInterval;                        // 间隔，默认为0
	short m_nRowHeight;                     // 行高
	short m_nColCount;                      // 当前展示列的个数

	int m_nColWidth;       // 当值<=0时：由控件自适应宽度。当值>0时：为指定了宽度
	UINT m_uItemHorAlign;  // 元素水平的对齐方式
	UINT m_uItemTextAlign; // 元素文本的对齐方式
	bool m_bShowCheckBox;  // 是否显示复选框
	bool m_bCommitTextID;  //  提交文本id
	bool m_bUpdate;

  public:
	CListBoxUI();
	~CListBoxUI();

	int AddItem(std::shared_ptr<CNodeData> rawdata, const BeString& szTextID);
	int InsertItem(int nIndex, std::shared_ptr<CNodeData> rawdata, const BeString& szTextID);
	int DeleteItem(int nIndex);
	void Clear(BOOL bErase = TRUE);
	BOOL IsExist(LPCTSTR text, BOOL ignore_case = FALSE);  // 是否已经存在
	BOOL IsInVisibleView(int nIndex) const;                // 是否在可视区域内
	int GetClikedItemSel() const;                          // 获得点击热点项
	int GetSelectedSel() const;                            // 获得选中索引
	void SelectedItem(int nIndex, BOOL do_trigger = TRUE); // 设置选择项 nIndex<0 时会清空选择项
	BOOL SelectedItemByName(LPCTSTR name);                 // 设置选择项,通过名字匹配
	bool IsCheckedState(int nIndex);                       // 检查子项是否被选中
	BOOL SetCheckedState(int nIndex, SelectState state);   // 让某一项勾选状态

	CNodeData* GetNodeData(int index) const; // 获得数据值

	void ShowMultiCheckBox(bool bMiltiple = false); // 是否可以多选
	void SetColCount(int colCount);                 // 设置列数目
	int GetColCount() const;
	int GetCounts() const;    // 获得项目总数
	int GetRowCounts() const; // 获得数据行总数

	CCheckBoxCell* GetListBoxItem(int index) const; // 获得项指针
	CCheckBoxCell* GetListBoxItemByName(LPCTSTR nameid) const;

	int GetColWidth() const; // 获得列宽和行高
	void SetColWidth(int ncolw);
	int GetRowHeight() const;
	void SetRowHeight(int nRowH);
	void SetCheckBoxImage(SelectState state, GImageIconInfo* img); // 设置复选框图案
	void SetEditCtrlUI(CControlUI* pctrl);                         // 设置编辑委托
	void SetItemRoundRadius(RoundRectRadius& radius);
	void SetItemRoundSize(int rx, int ry);
	void SetItemAlign(UINT align);     // 设置元素在控件中的布局风格
	void SetItemTextAlign(UINT align); // 设置元素文本布局风格
	BeString GetControlText() override;
	void GetControlValueText(BasicStringBuffer& buffer) override;
	void SetControlValueText(const BeString& str) override;
	void ChangeThemeColors(int theme) override;
	void OnCreate() override;
	void OnControlSize() override;

	void OnSaveConfigSetting(XMLItem* node) override;
	void OnLoadConfigSetting(XMLItem* node) override;
	void OnParseItemData(XMLItem* pNode) override;

	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnRButtonCliked(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnVSCrollBar(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	CControlUI* HitTestControl(POINT pt) override;
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;

	void PrintToFile(FILE* fp, LPCSTR space_prefix = " ", int colcount = 1);

  protected:
	void DrawRowBackIntervalFill(ISurface* pSurface, int rowbegin, int rowend, RECT* lpUpdate); // 用间隔颜色填充背景
	void MoveItem(int step);
	void OnReLayout();
	int HitTestRowItem(POINT pt);
	void RefillListItem(CCheckBoxCell* item);
	bool GetShowIndexRange(int* pItem, int* piCount) const;
	void RefreshChangeItem(int before, int cur);
	int GetPaddingLeft() const; // 获得元素的水平位置起点
	int GetNodeIndexWithName(LPCTSTR name) const;
	void DoCommitText();
};

}
#endif
