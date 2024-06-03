#ifndef CBLUEUI_CMARKSHAPESTYLE_H_INCLUDED_
#define CBLUEUI_CMARKSHAPESTYLE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include "core/CCoreBasePro.h"
#include "graphics/GSurface.h"

namespace BUI {

enum TypeMarkShape
{
	MS_NO_MARK = 0,    ///< 空
	MS_TRIANGLE,       ///< 三角形
	MS_TRIANGLE_DOWM,  ///< 朝下三角形
	MS_TRIANGLE_LEFT,  ///< 朝左三角形
	MS_TRIANGLE_RIGHT, ///< 朝右三角形
	MS_RECT,           ///< 矩形
	MS_CIRCLE,         ///< 圆形
	MS_DIAMOND,        ///< 钻石图形
	MS_CROSS,          ///< 交叉
	MS_STAR,           ///< 五角星
};

/**
 * @brief 标记类节点样式
 *
 */
class UI_EXP GStyleMarkShape
{
  public:
	GStyleMarkShape();
	~GStyleMarkShape();

	void SetMarkStyle(TypeMarkShape style);
	void SetMarkSize(double marksize);
	void SetMarkColor(COLORREF color);

	TypeMarkShape GetMarkStyle() const;
	double GetMarkSize() const;
	COLORREF GetMarkColor() const;

	void OnPaintMarkShape(ISurface* pSurface, int cx, int cy, const RECT& rcDiagram, RECT* rcClip);
	void OnPaintMarkShape(ISurface* pSurface, int cx, int cy, int size, const RECT& rcDiagram, RECT* rcClip);
	BOOL OnPtInMarkShape(POINT pt, int cx, int cy);

	void ShellMarkAttribute(const BeString& szName, const BeString& szText);

	static void PaintMarkShape(ISurface* pSurface, int cx, int cy, TypeMarkShape style, int size, COLORREF color, const RECT& rcDiagram, RECT* rcClip);
	static void PaintMarkShapeBorder(ISurface* pSurface, int cx, int cy, TypeMarkShape style, int marksize, int bordersize, COLORREF color, const RECT& rcDiagram, RECT* rcClip);
	static BOOL PtInMarkShape(POINT pt, int cx, int cy, TypeMarkShape style, int size);

  protected:
	TypeMarkShape m_markStyle;
	double m_nMarkSize;
	COLORREF m_MarkColor;
};

}
#endif
