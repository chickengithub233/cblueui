#ifndef CBLUEUI_CWIDGETOVERLAYWND_INC_H_
#define CBLUEUI_CWIDGETOVERLAYWND_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreObject.h"
#include "graphics/GImage.h"
#include "CWidgetWnd.h"

/**
 * @brief 层叠窗口
 *
 */
class UI_EXP CWidgetOverlayWnd : public CWidgetWnd
{
  public:
	CWidgetOverlayWnd(void);
	~CWidgetOverlayWnd(void);

	HWND CreateLayeredWnd(RECT rcPostion, BOOL isTransStyle = FALSE, BOOL isShow = FALSE);

	void UpdateOverlayPosition(RECT rcPostion);

	void SetBkImage(BUI::GImage* img);
	void SetBlenderAlpha(int blender);
	void UpdateWindow();
	BOOL IsCreated() const;
	BOOL DefWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual void PaintPixels(HDC hdc, void* pixel, int w, int h, int bpp, int nAlpha);

  protected:
	void UpadateWnd(int nAlpha = 100);
	int m_blender_alpha;
	BUI::GImage* m_pImg;
};

class UI_EXP CWidgetOverlaySideWnd : public CWidgetOverlayWnd, public BUI::IDockOverlayHandler
{
  public:
	CWidgetOverlaySideWnd(void);
	~CWidgetOverlaySideWnd(void);

	/*
	      1
	    4 0 2
	      3
	*/
	void SetSideType(UINT t);

	void PaintPixels(HDC hdc, void* pixel, int w, int h, int bpp, int nAlpha) override;

  private:
	void OnHitTestResult(int t);

  private:
	UINT m_side_type;
	int m_hit_type;
};



#endif