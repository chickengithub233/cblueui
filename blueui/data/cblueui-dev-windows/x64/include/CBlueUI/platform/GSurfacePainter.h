#ifndef CBLUEUI_DISPLAY_GSURFACEPAINTER_INC_H_
#define CBLUEUI_DISPLAY_GSURFACEPAINTER_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "graphics/GColor.h"
#include "GFont.h"

namespace BUI {

/**
 * @brief 平台相关的绘制
 *
 */
class UI_EXP GSurfacePainter
{
  public:
	GFont* m_curFont;

  public:
	GSurfacePainter();
	virtual ~GSurfacePainter();

	virtual GFont* GetPainterCurrentFont();
	virtual SIZE GetTextSize(LPCTSTR sztext, int nlen);
	virtual SIZE GetTextSizeW(LPCWSTR sztext, int nlen);
	virtual SIZE GetTextSizeA(LPCSTR sztext, int nlen);

	virtual GFont* SelectPainterFont(GFont* font);

	virtual void SetPainterClipRect(int x, int y, int w, int h, bool enable, int orgX = 0, int orgY = 0);

	virtual void DoPaintTextMultiLine(int x, int y, TextMultilineInfo* multiText, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0);

	virtual void DoPaintTextOutW(int x, int y, LPCWSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0);
	virtual void DoPaintTextOutA(int x, int y, LPCSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0);
	virtual void DoPaintTextOut(int x, int y, LPCTSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0);

	virtual void DoPaintTextW(LPRECT lprc, LPCWSTR text, int c, COLORREF color, UINT format, int orgX = 0, int orgY = 0);
	virtual void DoPaintTextA(LPRECT lprc, LPCSTR text, int c, COLORREF color, UINT format, int orgX = 0, int orgY = 0);
	virtual void DoPaintText(LPRECT lprc, LPCTSTR text, int c, COLORREF color, UINT format, int orgX = 0, int orgY = 0);

	virtual void DoPaintTextAngleW(int x, int y, float angle, LPCWSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0);

	virtual void DoPaintTextAngleA(int x, int y, float angle, LPCSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0);

	virtual void DoPaintTextAngle(int x, int y, float angle, LPCTSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP, int orgX = 0, int orgY = 0);
};

}
#endif
