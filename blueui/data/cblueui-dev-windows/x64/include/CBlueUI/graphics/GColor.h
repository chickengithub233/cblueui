#ifndef CBLUEUI_CCOLORUNTILS_INCLUDED_
#define CBLUEUI_CCOLORUNTILS_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"

namespace UtilsColor {

/**
 * @brief 彩色转换为灰度颜色
 *
 */
UI_EXP COLORREF GrayColor(COLORREF color);

UI_EXP COLORREF HSVColor(float h, float s = 1, float v = 1, UINT alpha = 255);
UI_EXP LPCTSTR ParseColor(LPCTSTR lpcolor, LPCTSTR end, COLORREF* out_color);
UI_EXP bool ParseStringToColor(const TCHAR* lpcolor, COLORREF* color);
UI_EXP bool ParseColorStyle(const TCHAR* lpcolor, COLORSTYLE* colors);

UI_EXP BOOL ParseHSVColor(LPCTSTR lpcolor, float* h, float* s, float* v, float* alpha);

UI_EXP COLORREF Get24PhaseColor(int i);

UI_EXP void RGBToHSV(COLORREF color, float* h, float* s, float* v);

/**
 * @brief RGBToHSV HSVToRGB相互转换
 *
 * @param r,g,b: [0,1]
 * @param h : [0,360]
 * @param s :[0,1] 饱和度
 * @param v :[0,1]
 */
UI_EXP void RGBToHSV(float r, float g, float b, float* h, float* s, float* v);
UI_EXP void HSVToRGB(float* r, float* g, float* b, float h, float s, float v);

/**
 * @brief RGBToHSL和HSLToRGB相互转换
 *
 * @param r,g,b: [0,1]
 * @param h : [0,360]
 * @param s :[0,1] 饱和度
 * @param l :[0,1]
 */
UI_EXP void RGBToHSL(float r, float g, float b, float* h, float* s, float* l);
UI_EXP void HSLToRGB(float* r, float* g, float* b, float h, float s, float l);

/**
 * @brief 获得系统内置风格
 *
 * @param theme 内置主题编号
 * @param i 颜色类别，比如背景，前景
 * @return COLORSTYLE
 */
COLORSTYLE GetColorStyle(int theme, int i);


/**
 * @brief 添加自定义主题配色方案
 *
 */
void UpdateCustomThemeColors(int i, COLORSTYLE& colors);

/**
 * @brief 清空
 *
 */
void ClearCustomThemeColors(int pos);

/**
 * @brief 获得自定义主题对应位置的颜色
 *
 */
BOOL GetCustomThemeColors(int pos, COLORSTYLE& colors);

};

/**
 * @brief 包含rgba分量的颜色
 *
 */
class UI_EXP GColor
{
  public:
	GColor();
	GColor(ULONG color);
	GColor(ULONG color, UINT8 alpha);
	GColor(UINT8 ir, UINT8 ig, UINT8 ib, UINT8 ia = 255);

	~GColor();

	const GColor& operator=(const GColor& other);
	bool operator==(const GColor& other);
	bool operator!=(const GColor& other);

	GColor& ToAlphaSoild(int a); // 转换透明度到实色[0-255],0代表全透明

	COLORREF ToGray(); // 转换为灰度值

	COLORREF ToABGR() const; ///< 打包为占4字节的整数

	GColor ToComplementaryColor() const; // 互补色

	GColor DistanceColorWithHSV(float dh, float ds = 0.0, float dv = 0.0) const; // 邻近色

	void ToHsvColor(float& h, float& s, float& v); // 转换颜色为HSV顺序

  public:
	UINT8 r;
	UINT8 g;
	UINT8 b;
	UINT8 a; // 0:全透明，255不透明
};

/**
 * @brief 包含hsva分量的颜色
 *
 */
class UI_EXP GColorHSV
{
  public:
	GColorHSV();
	GColorHSV(float h_, float s_ = 1, float v_ = 1, UINT8 ia = 255);
	~GColorHSV();

	GColor ToRGBColor();

  public:
	float h; // [0~360]
	float s; // [0~1]
	float v; // [0~1]
	UINT a;  // [0~1]
};




#endif