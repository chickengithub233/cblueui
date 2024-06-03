#ifndef CBLUEUI_CPOPMENUCONTAINUI_H_DDVU35K_FQX03_481VQ_45P5Z_YF0VD_INCLUDED_
#define CBLUEUI_CPOPMENUCONTAINUI_H_DDVU35K_FQX03_481VQ_45P5Z_YF0VD_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CContainLayoutUI.h"
#include "layout/CLayoutManager.h"

namespace BUI {

class UI_EXP CContainMenuUI : public CContainLayoutUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CContainMenuUI)
  protected:
	CLayoutBox m_layout;
	timer_handler* m_timer_close;
	CContainMenuUI* m_pParnetPop; // 上一级菜单，控件对象指针
	BOOL m_bModel;
	BOOL m_bCloseWhenKillFocus; // true :控件失去焦点时，会自动关闭。 false:需要用户主动关闭
	SIZE m_ExpectSize;          // 期望的尺寸
	POINT m_point;
	UINT m_nAlignFlag;

  public:
	CContainMenuUI();
	~CContainMenuUI();
	void SetSelfCloseOnKillFocus(bool bActive);
	UINT_PTR GetMenuID() const;
	BOOL TrackDropPop(UINT nFlags, int x, int y);

	void LoadUI(char* file);

	void OnControlSize() override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
};




}
#endif
