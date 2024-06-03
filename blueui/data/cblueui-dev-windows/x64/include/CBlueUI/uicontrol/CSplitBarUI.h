#ifndef CBLUEUI_CSPLITCONTAINERUI_H_DDVU35K_FQX03_481VQ_45P5Z_YF0VD_INCLUDED_
#define CBLUEUI_CSPLITCONTAINERUI_H_DDVU35K_FQX03_481VQ_45P5Z_YF0VD_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {

class UI_EXP CSplitBarUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CSplitBarUI)
  protected:
	int m_nSlpitOffsetX;
	int m_nSlpitOffsetY;
	int m_nSlpitOffsetCacheX;
	int m_nSlpitOffsetCacheY;

  public:
	CSplitBarUI();
	~CSplitBarUI();

	void ChangeThemeColors(int theme) override;
	void CloneAttribute(CControlUI* clone) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	int GetSplitControlOffsetW() override;
	int GetSplitControlOffsetH() override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL OnNcHitTest(POINT pt) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
};




}
#endif
