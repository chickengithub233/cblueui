#ifndef CBLUEUI_CTABCONTAINUI_BLXDY_INC_H_
#define CBLUEUI_CTABCONTAINUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CContainLayoutUI.h"
#include "CNodeCell.h"

namespace BUI {

// 标签页的容器
class UI_EXP CContainTabUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CContainTabUI)
  private:
	std::map<UINT, std::pair<CContainLayoutUI*, BOOL>> m_mapTabPages;
	int m_uCurSel;
	bool m_bNeedReLayout;

  public:
	CContainTabUI();
	~CContainTabUI();

	int GetTabCurSel();
	void SetTabCurSel(UINT nID);
	void RemoveTabPage(UINT nID);
	void AddTabPage(UINT nID, CContainLayoutUI* pTabPageUI, BOOL bAutoDestory = TRUE);

	void OnControlSize() override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | cursel <br/>当前选中页索引                      | cursel="1"	    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void Layout(int x, int y, int w, int h, UINT flags) override;

  private:
	void ShowTabCtrls(UINT nID, bool bVisable);
};

}

#endif
