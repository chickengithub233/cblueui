#ifndef CBLUEUI_CPOPCONTROLUI_H_DDVU35K_FQX03_481VQ_45P5Z_YF0VD_INCLUDED_
#define CBLUEUI_CPOPCONTROLUI_H_DDVU35K_FQX03_481VQ_45P5Z_YF0VD_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "layout/CLayoutManager.h"

namespace BUI {

class UI_EXP CPopControlUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CPopControlUI)
  protected:
	CLayoutBox m_layout;
	timer_handler* m_timer_close;
	BOOL m_bModel;
	BOOL m_bCloseWhenKillFocus; // true :控件失去焦点时，会自动关闭。 false:需要用户主动关闭
  public:
	CPopControlUI();
	~CPopControlUI();
	void SetSelfCloseOnKillFocus(bool bActive);
	void CenterPosition();
	void LoadUI(char* filen);
	UINT DoModal(int nMesc = 0);

	void OnControlSize() override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};




}
#endif
