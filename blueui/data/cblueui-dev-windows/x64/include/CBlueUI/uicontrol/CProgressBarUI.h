
#ifndef CBLUEUI_CPROGRESSBARUI_BLXDY_INC_H_
#define CBLUEUI_CPROGRESSBARUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {


/**
 * @brief 进度条
 *
 */
class UI_EXP CProgressBarUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CProgressBarUI)
  protected:
	double m_fMin;
	double m_fMax;
	double m_fValue; // 当前值
	int m_nBarSize;  // 滑条的大小
	int m_nAnimPos;
	GradientColors* m_stopcolors[UIS_COUNT];
	CTimerTask m_anim_timer;
	int m_nSliceSize;     // 切片(slic)风格.片大小
	int m_nSliceInterval; // 片间隔
  public:
	CProgressBarUI();
	~CProgressBarUI();

	double Value() const;

	void SetValue(double value);

	void SetRange(double min_, double max_);

	void SetRangeMax(double max_);

	void SetSliderStyle(bool bHor);

	void SetRingStyle(BOOL bRing); ///< 设置环状风格

	void ChangeThemeColors(int theme) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | bar-flags<br/>进度条功能标志位   |	"-"前缀代表删除属性<br/>	  |
	 * |                                 | ring :环形 	    |
	 * |                                 | horizontal :横向条状	    |
	 * |                                 | vertical :纵向条状	    |
	 * |                                 | default :自动根据宽高识别横向还是纵向    |
	 * |                                 | AnimLoding:动画加载风格    |
	 * |                                 |        |
	 * | gradient-colors <br/>渐变颜色         | gradient-colors="资源标识符"	    |
	 * | Range <br/>选取范围        | Range="0,100"		    |
	 * | value <br/>当前值        | value="50"		    |
	 * | slice-size <br/>切片风格大小        | slice-size="10"		   |
	 * | slice-interval <br/>切片风格间隔        | slice-interval="5"		   |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintShadow(ISurface* pSurface, bool inset, RECT* lpUpdate) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void GetControlValueText(BasicStringBuffer& buffer) override;

  protected:
	BOOL IsHorzLayout() const;
	void FillBarRect(ISurface* pSurface, const RECT& rc, const RECT& rcPaint, GradientColors* gradcolors, const GColor& color, BOOL isHorz = TRUE);
};

class UI_EXP CSliderUI : public CProgressBarUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CSliderUI)
  protected:
	double m_precision;      // 最小的刻度值
	int m_nMinor;            // 小刻度数量
	int m_nMajor;            // 大刻度数量
	int m_nMinorTickSize;    // 小刻度线长
	int m_nMajorTickSize;    // 大刻度线长
	int m_nPointerSize;      // 滑块大小
	int m_nMinorTickPenSize; // 小刻度线宽
	int m_nMajorTickPenSize; // 大刻度线宽
	int m_nTickLabelSpacing; // 标签文本和坐标轴刻度线的间隔
	TickMarkPositon m_tickMarkStyle;

	COLORSTYLE m_minorTickColor; // 小刻度颜色
	COLORSTYLE m_majorTickColor; // 大刻度颜色

	double m_trackpos;
	double m_fPreviewValue;   // 实时滑动的值
	double m_fValue2;         // 经过刻度约束后的值
	double m_fPreviewValue2;  // 实时滑动第二个值
	unsigned m_nDegreeOffset; // 刻度边缘偏移量

	BeString m_labelFormat;
	POINT m_pt;
	UINT m_uHitThumb;

	BOOL m_isSelectRangeMode; // 范围选择模式
  public:
	CSliderUI();
	~CSliderUI();

	void SetValue(double value, BOOL bRefresh = TRUE);
	void SetValue2(double value, BOOL bRefresh = TRUE);
	void GetSelectRange(double& v1, double& v2);

	void SetDegreeOffset(int d);
	void SetTickLineSize(int minorSize, int majorSize);
	void SetTickCount(int minor, int major);
	void SetLabelFormat(LPCTSTR str);
	void SetPrecision(double precis);

	void SetTickMarkCount(TickMarkID id, int c);
	void SetTickMarkLineSize(TickMarkID id, int tickSize = 4);
	void SetTickMarkStyle(TickMarkID id, TickMarkPositon style = TickOnOutside);

	void ChangeThemeColors(int theme) override;
	void OnControlSize() override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void GetControlValueText(BasicStringBuffer& buffer) override;

  private:
	int getSliderlength();
	UINT hitTestThumb(POINT pt);
	bool normalizeValue(bool preview_value_flag);
	void moveSteps(int offset);
	void DrawTickLine(ISurface* pSurface, int x, int y, TickMarkPositon style, GColor& color_minor, GColor& color_major);
	void DrawTickPoint(ISurface* pSurface, int x, int y, GColor& color_minor, GColor& color_major);
};


}

#endif
