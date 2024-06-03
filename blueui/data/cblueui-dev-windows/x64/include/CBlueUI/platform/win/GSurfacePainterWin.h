#ifndef CBLUEUI_DISPLAY_GSURFACEPAINTER_WIN_INC_H_
#define CBLUEUI_DISPLAY_GSURFACEPAINTER_WIN_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "platform/GSurfacePainter.h"

namespace BUI {

class GSurfacePainterWin : public GSurfacePainter
{
  public:
	HDC m_dc;

  public:
	GSurfacePainterWin(HDC dc);
	virtual ~GSurfacePainterWin();

	GFont* SelectPainterFont(GFont* font) override;
	void SetPainterClipRect(int x, int y, int w, int h, bool enable, int orgX = 0, int orgY = 0) override;
	SIZE GetTextSize(LPCTSTR sztext, int nlen) override;
	void DoPaintTextMultiLine(int x, int y, TextMultilineInfo* multiText, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0) override;
	void DoPaintTextOutW(int x, int y, LPCWSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0) override;
	void DoPaintTextOutA(int x, int y, LPCSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0) override;
	void DoPaintTextOut(int x, int y, LPCTSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0) override;

	void DoPaintTextW(LPRECT lprc, LPCWSTR text, int c, COLORREF color, UINT format, int orgX = 0, int orgY = 0) override;
	void DoPaintTextA(LPRECT lprc, LPCSTR text, int c, COLORREF color, UINT format, int orgX = 0, int orgY = 0) override;
	void DoPaintText(LPRECT lprc, LPCTSTR text, int c, COLORREF color, UINT format, int orgX = 0, int orgY = 0) override;

	void DoPaintTextAngleW(int x, int y, float angle, LPCWSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0) override;
	void DoPaintTextAngleA(int x, int y, float angle, LPCSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0) override;
	void DoPaintTextAngle(int x, int y, float angle, LPCTSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0) override;
};

}
#endif
