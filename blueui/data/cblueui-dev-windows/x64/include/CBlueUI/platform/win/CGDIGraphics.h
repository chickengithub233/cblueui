#ifndef CBLUEUI_CGDIGRAPHICS_BYMD_INC_H_
#define CBLUEUI_CGDIGRAPHICS_BYMD_INC_H_

#include "core/CCoreBasePro.h"
#include "bufferDC.h"

class UI_EXP CGDIGraphics
{
  private:
	CGDIGraphics();
	~CGDIGraphics();

  public:
	/* geometry common */
	static void Line(HDC hdc, int x1, int y1, int x2, int y2);

	// static void   Polygon(HDC hdc, POINT* pts, int nlen);

	static void Rect(HDC hdc, RECT rc, COLORREF color);
	static void FillRect(HDC hdc, RECT rc, COLORREF color);

	// static void   Ellipse(HDC hdc, int x, int y, int rx, int ry);

	// static void   BSpline(HDC hdc, POINT* pt, int count, COLORREF color, int width);

	// static void   DrawSpring(HDC hdc, RECT rc, bool bHor, bool bFill, COLORREF crColor);

	// static void   DrawScrollArrow(HDC hdc, int x, int y, int dir);

	/* text */
	static SIZE GetStringSize(HDC hdc, LPCTSTR lpstr, int len);
	static void DrawString(HDC hdc, LPCTSTR szText, int nlen, RECT rc, COLORREF color, UINT nAlign);
	static void DrawMultText(HDC hdc, LPCTSTR szText, int nlen, RECT rc, COLORREF color, UINT nAlign);
	static void GetMultTextSize(HDC hdc, LPCTSTR szText, int nlen, SIZE* sz);
	static void DrawTextOut(HDC hdc, LPCTSTR szText, int nlen, int x, int y, COLORREF color);

	/**
	 * @brief 带角度的文本输出
	 *
	 * @param hdc  目标DC
	 * @param cx   旋转中心
	 * @param cy
	 * @param x    文本左上角位置
	 * @param y
	 * @param angle  旋转角度
	 * @param sztext 文本内容
	 * @param nlen   文本长度
	 * @param color  文本颜色
	 */
	static void DrawStringAngle(HDC hdc, int cx, int cy, int x, int y, float angle, LPCTSTR sztext, int nlen, COLORREF color);

	// static void   GetHICONSize(HICON hIco, SIZE* lpszie);
};


#endif