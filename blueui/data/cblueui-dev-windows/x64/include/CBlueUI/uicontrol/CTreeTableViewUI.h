#ifndef CBLUEUI_CTreeTableViewUI_BLXDY_INC_H_
#define CBLUEUI_CTreeTableViewUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CContainTitleUI.h"
#include "CTreeViewModel.h"

namespace BUI {

/**
 * @brief 树状表格
 *
 */
class UI_EXP CTreeTableViewUI : public CContainTitleUI, public CTreeViewModel
{
	DECLARE_DYNAMIC_OBJ_CLASS(CTreeTableViewUI)
  public:
	CTreeTableViewUI();
	~CTreeTableViewUI();

	void ShowNumText(BOOL bShow);
	UINT GridLineStyle() const;
	void SetGridLineStyle(UINT nStyle);
	CTreeModelNode* InsertTreeItem(CTreeModelNode* parent, CTreeModelNode* prev, std::shared_ptr<CNodeSpanCell> item);
	void GetTreeNodeCellRect(CTreeModelNode* node, int col, RECT* rc) const;

	void OnReLayout() override;
	void OnControlSize() override;

	void ChangeThemeColors(int theme) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void OnChangeHeaderColWidth() override;
	void OnPaintMovingColum(int ncol, int dx, ISurface* pSurface, RECT* lpUpdate) override;
	void OnInsertColumn(int ncol, int sum) override;
	void OnDeleteColumn(int ncol, int sum) override;

	/**
	 * @brief 命令控制和属性设置接口 集成于@link CTreeViewModel @endlink @link CContainTitleUI @endlink
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	void OnParseItemData(XMLItem* pNode) override;
	void ParseTreeItemData(XMLItem* pNode, CTreeModelNode* parent, int index);
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	CControlUI* HitTestControl(POINT pt) override;

  protected:
	POINT GetScrollOffsetPoint() override;
	int GetModelColumCount() override;
	void OnInvalidateRect(RECT* rc, BOOL bClient) override;
	void OnSelectItem(CTreeModelNode* item) override;

	void OnDbClickCell(CTreeModelNode* node, int nCol);
	void ShowEditor(CTreeModelNode* node, int nCol);
	int CalcLeadWidth() const;

	void GetShowIndexRange(int& begin, int& count); // 获得当前可见的行信息
	BOOL DoPaintNumCtrl(ISurface* pSurface, RECT* lpUpdate);
	void DoPaintColum(int col, int fix_width, int nShowRow, int endRow, int dx, int client_view_top, COLORREF crtext, ISurface* pSurface, RECT* lpUpdate);
	void DrawGridFill(ISurface* pSurface, int rowbegin, int rowend, RECT rcAbs, RECT* lpUpdate);

	void DrawRowBackIntervalFill(ISurface* pSurface, int rowbegin, int rowend, RECT* lpUpdate); // 用间隔颜色填充背景

  private:
	UINT m_uGridMode;
	BOOL m_bEnableEdit;          // 是否可以编辑
	BOOL m_bShowColNum;          // 是否显示行号
	CTreeModelNode* m_hEditItem; // 正在编辑的单元格 (row, col)
	int m_nEditColIndex;
};

}
#endif