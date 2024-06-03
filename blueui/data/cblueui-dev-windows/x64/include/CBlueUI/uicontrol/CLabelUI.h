#ifndef CBLUEUI_LABEL_BLXDY_INC_H_
#define CBLUEUI_LABEL_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CNodeDataQuote.h"
#include "graphics/GStyleMarkShape.h"

namespace BUI {

/**
 * @brief 普通标签控件
 *
 */
class UI_EXP CLabelUI : public CControlUI, public CTextLayout
{
	DECLARE_DYNAMIC_OBJ_CLASS(CLabelUI)
  public:
	CLabelUI();
	~CLabelUI();

	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;
	void ChangeThemeColors(int theme) override;
	void OnCreate() override;
	void OnControlSize() override;
	void OnCtrlKillFocus() override;

	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | text-align <br/>文本对齐方式  | text-align="left,vcenter" 取值left,right,center,top,bottom,vcenter的组合  |
	 * |  |tailicon:图标和文本翻转，图标在后，文本在前  |
	 * |  |HorizontalDirection: 图标和文本水平布局  |
	 * |  |VerticalDirection: 图标和文本垂直布局  |
	 * |  |TextVerticalColumn: 文本旋转90垂直布局  |
	 * |  |TextVerticalColumnChina:中文竖排垂直布局  |
	 * |  |  |
	 * | icon <br/>图标   | 图标资源符  |
	 * | icon-interval <br/>文本和图标间隔  | icon-interval="5" |
	 *
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};

/**
 * @brief mark标记
 *
 */
class UI_EXP CStaticMarkUI : public GStyleMarkShape, public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CStaticMarkUI)
  public:
	CStaticMarkUI();
	~CStaticMarkUI();

	BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};

/**
 * @brief 线条控件
 *
 */
class UI_EXP CLineUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CLineUI)
  public:
	CLineUI();
	~CLineUI();

	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	int m_line_size;
	GPointF m_pt1; // 第一个点(x,y),值为百分比坐标系
	GPointF m_pt2; // 第二个点(x,y),值为百分比坐标系

	PenType m_line_bru_type;
};

struct ArrowPoint
{
	CControlUI* ui;
	SizeValue x;
	SizeValue y;

	ArrowPoint()
	    : ui(NULL)
	{}
};

/**
 * @brief 跨越式箭头控件
 *
 */
class UI_EXP CLineArrowUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CLineArrowUI)
  public:
	CLineArrowUI();
	~CLineArrowUI();

	BOOL HitTest(POINT pt) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;
	void OnParseItemData(XMLItem* pNode) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	int m_arc_size;
	int m_arrow_size;
	int m_line_size;
	PenType m_line_bru_type;
	ArrowPoint m_point_start;
	ArrowPoint m_point_end;
};



}
#endif