#ifndef CBLUEUI_CPAGINATIONUI_INC_H_
#define CBLUEUI_CPAGINATIONUI_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "CControlUI.h"

namespace BUI {


class UI_EXP CPaginationUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CPaginationUI)
  private:
	int m_nTotalOfPage;
	int m_nFirstOfPage;
	int m_nVisableCountPage;
	int m_nSelectOfPage;
	int m_nHeightOfItem;
	int m_nHighLightIndex;
	UINT m_nHitFlag;

  public:
	CPaginationUI();
	~CPaginationUI();

	void SetPageCount(int c); // 设定控件的页数量
	int GetSelPage();
	BOOL PrevMovePage();
	BOOL NextMovePage();
	BOOL SetSelPage(int nPage);

	BOOL OnNcHitTest(POINT pt) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};


}
#endif