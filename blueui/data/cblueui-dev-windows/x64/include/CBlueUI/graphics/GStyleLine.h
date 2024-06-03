#ifndef CBLUEUI_CLINESTYLE_H_INCLUDED_
#define CBLUEUI_CLINESTYLE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include "core/CCoreBasePro.h"
#include "graphics/GSurface.h"
#include "cstring/String.h"
#include "cstring/StringA.h"

namespace BUI {

enum LineMode
{
	LM_NO_Line, // 无线条
	LM_Step,    // 步进式
	LM_Line,    // 直线
	LM_Spline,  // spline插值样条
};

class UI_EXP GPenInfo
{
  public:
	GPenInfo();
	~GPenInfo();

	void SetLineColor(GColor color); // 设置线颜色
	void SetLineType(PenType style); // 设置画笔类型
	void SetLineWidth(int weight);   // 设置线宽

	int GetLineWidth() const;
	GColor GetLineColor() const;
	PenType GetLineType() const;

	void ShellAttributePen(const BeString& szName, const BeString& szText);

  protected:
	PenType m_penType; // 实线，虚线等
	GColor m_pencolor; // 颜色
	int m_nPenWidth;   // 线宽
};

/**
 * @brief 线条样式
 *
 */
class UI_EXP GStyleLine : public GPenInfo
{
  public:
	GStyleLine();
	~GStyleLine();

	BOOL IsFillAreaPath() const;
	void FillAreaPath(BOOL bFill);
	void SetLineMode(LineMode mode);
	LineMode GetLineMode() const;

  protected:
	LineMode m_lineMode;
	BOOL m_bFillPath;
};

// 渐变背景
class UI_EXP GradientRoundRect
{
  public:
	GradientRoundRect(GColor color);
	GradientRoundRect(GBrushGradient* bru = NULL);
	~GradientRoundRect();

	void SetRoundRectRadius(RoundRectRadius& radius);
	void SetSolidColor(GColor color);
	void SetGraientColor(GBrushGradient* bru);
	void DrawBackGround(ISurface* pSurface, RECT& rcView);


  protected:
	GColor m_solid_color;
	GBrushGradient* m_bru;
	RoundRectRadius m_RoundRadius;
};




}
#endif
