#ifndef CBLUEUI_CTREELISTUI_BLXDY_INC_H_
#define CBLUEUI_CTREELISTUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CContainTitleUI.h"
#include "CTreeViewModel.h"

namespace BUI {

/**
 * @brief 树状列表
 *
 */
class UI_EXP CTreeListUI : public CScrollAreaUI, public CTreeViewModel
{
	DECLARE_DYNAMIC_OBJ_CLASS(CTreeListUI)
  public:
	CTreeListUI();
	~CTreeListUI();

	CTreeModelNode* InsertTreeItem(CTreeModelNode* parent, CTreeModelNode* prev, std::shared_ptr<CNodeSpanCell> item);


	void OnReLayout();
	void ChangeThemeColors(int theme) override;
	void OnControlSize() override;
	void OnParseItemData(XMLItem* pNode) override;
	void ParseTreeItemData(XMLItem* pNode, CTreeModelNode* parent);
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	CControlUI* HitTestControl(POINT pt) override;

	/**
	 * @brief 命令控制和属性设置接口 集成于@link CTreeViewModel @endlink @link CScrollAreaUI @endlink
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;

  protected:
	int CalcHorzScrollRangMax(const GFont* font) const;
	void OnInvalidateRect(RECT* rc, BOOL bClient) override;
	int GetModelColumCount() override;
	POINT GetScrollOffsetPoint() override;
	void OnSelectItem(CTreeModelNode* item) override;

	void DrawRowBackIntervalFill(ISurface* pSurface, int rowbegin, int rowend, RECT* lpUpdate); // 用间隔颜色填充背景
  private:
	void GetShowIndexRange(int& begin, int& count); // 获得当前可见的行信息
};

}
#endif