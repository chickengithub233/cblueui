#ifndef CBLUEUI_CCAROUSELUI_INC_H_
#define CBLUEUI_CCAROUSELUI_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {

class GImage;

struct CarouselItem
{
	GImage* img;
	BeString textID;
	UINT cmdID;
};

enum MOVE_MODE
{
	AM_LEFT,
	AM_MID,
	AM_RIGHT
};

class UI_EXP CCarouselUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CCarouselUI)
  private:
	std::vector<CarouselItem> m_pages;
	int m_nCurSel;
	BOOL m_bAnimation;

  public:
	CCarouselUI();
	~CCarouselUI();

	void AddCarouselPage(GImage* img, UINT cmd, const BeString& szID);
	void SetCurSel(int sel);
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	void OnParseItemData(XMLItem* pNode) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

	void PaintFront(ISurface* pSurface, RECT* lpUpdate);

  private:
	void Animation(int before, int mid, int after, int mode);
};





}

#endif
