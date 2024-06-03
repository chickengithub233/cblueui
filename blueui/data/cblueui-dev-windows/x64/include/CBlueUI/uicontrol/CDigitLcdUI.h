#ifndef CBLUEUI_CDIGITLCDUI_H_INCLUDED_
#define CBLUEUI_CDIGITLCDUI_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {

/**
 * @brief 液晶数字控件
 *
 */
class UI_EXP CDigitLcdUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CDigitLcdUI)
  public:
	CDigitLcdUI();
	~CDigitLcdUI();

	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintShadow(ISurface* pSurface, bool inset, RECT* lpUpdate) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	/* override IControlUI menthos:*/
	int LayoutAdaptWidth(int expH) override;

  protected:
	void DrawDigitLCD(ISurface* pSurface, const RECT& rc, int r, GColor color, UINT flags, PathTransInfo* pathinfo_shadow = NULL);
	UINT m_horAlign;
	BeString m_tipsText;
	int m_pensize;
};




}
#endif
