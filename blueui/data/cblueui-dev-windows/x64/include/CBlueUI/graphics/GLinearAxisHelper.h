/*
 * 轴坐标计算辅助类
 */

#ifndef CBLUEUI_GLINEARAXISHELPER_BLXDY_INC_H_
#define CBLUEUI_GLINEARAXISHELPER_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "core/CCoreBasePro.h"
#include "core/CGeometryStruct.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "GSurface.h"

#define LA_HT_NONE        0x00
#define LA_HT_THUMB       0x01
#define LA_HT_THUMB_LEFT  0x02
#define LA_HT_THUMB_RIGHT 0x03

namespace BUI {

/**
 * @brief 滚动视窗范围控制类
 * +--------------+=================+---------------+
 * m_dataMin      m_showMin         m_showMax       m_dataMax
 */
class UI_EXP ScrollZoom
{
  public:
	ScrollZoom();
	virtual ~ScrollZoom();

	// 获得v在范围内的百分比 p= (v-min)/(max-min)
	inline double GetPercentValue(double v)
	{
		double k = (v - m_dataMin) / (m_dataMax - m_dataMin);
		return k;
	}

	// 获得真实显示的值，p为百分占比
	inline double GetValue(double p)
	{
		double k = p / (m_dataMax - m_dataMin) + m_dataMin;
		return k;
	}

	void SetScrollZoomPageStart(double page);
	void SetScrollZoomPageEnd(double page);
	void SetScrollInfo(double min_, double max_, double page_start, double page_end);
	void SetScrollZoomRange(double dblMin, double dblMax);

	void SetDataRange(double fmin, double fmax);
	void SetInitRange(double fmin, double fmax);
	void SetShowRange(double fmin, double fmax);

	void GetDataRange(double& fmin, double& fmax);
	void GetInitRange(double& fmin, double& fmax);
	void GetShowRange(double& fmin, double& fmax);

	void SetScrollZoomSelectRange(double begin, double end);         ///< 设置滚动选中范围百分比
	void GetScrollZoomSelectRange(double& begin, double& end) const; ///< 获得滚动选中范围百分比

	void SetScrollZoomMinPage(int page);

	void SetUnitPrecision(double percision); ///< 设置最小单位
	BOOL IsScrollVaild() const;

	void EnableZoomd(BOOL enable);

	BOOL NotifyZoomRange(double v); ///< 向区域中通知，新加入的值，如果在可视范围内，则不变更

	void StorageTrackPage();
	double GetPageOffset(double p); // 获得p百分比偏移量
	double GetPageStartOffset();    // 获得滑块起点偏移量
	double GetPageEndOffset();      // 获得滑块终点偏移量

	void MovePageToEnd();
	void MovePageToStart();

	UINT HitScrollThumbStates(POINT pt, GVectorF vAxis) const;

	BOOL OnChangePageRange(double k, double minunit, UINT hit);

  public:
	/* init range*/
	double m_initMin;
	double m_initMax;

	/* data range*/
	double m_dataMin;
	double m_dataMax;

	/* show range*/
	double m_showMin;
	double m_showMax;

	double m_t; // 时间流逝参数，轴在时间维度规律动态变化

	double m_dblPageStart; // 选中范围[0,1]
	double m_dblPageEnd;

	double m_dblPageStartTrack;
	double m_dblPageEndTrack;

	double m_mult_k;
	double m_precision;

	int m_nMinor;            // 小刻度数量
	int m_nMajor;            // 大刻度数量
	int m_nMinorTickSize;    // 小刻度线长
	int m_nMajorTickSize;    // 大刻度线长
	int m_nMinorTickPenSize; // 小刻度线宽
	int m_nMajorTickPenSize; // 大刻度线宽

	TickMarkPositon m_MajorMarkStyle;
	int m_nTickLabelSpacing; // 标签文本和坐标轴刻度线的间隔
	float m_textAngle;       // 文本相对于法向量的角度

	int m_minPageHasUnit;    // 最小页展示的单位数量
	int m_minPageScreenSize; // 滑块在屏幕的最小尺寸
	UINT m_nLAHit;
	POINT m_ptTrace;
	POINT m_ptThumb[4];
	POINT m_ptZoomS;
	POINT m_ptZoomE;
	BOOL m_isZoomEnable;
};

class UI_EXP GLinearAxisHelper
{
  public:
	GLinearAxisHelper(const POINT& pt0, const POINT& pt1, const POINT& ptCenter, const ScrollZoom& axisinfo, GVectorF* vn_label = NULL);
	GLinearAxisHelper(const GPointF& pt0, const GPointF& pt1, const POINT& ptCenter, const ScrollZoom& axisinfo, GVectorF* vn_label = NULL);
	~GLinearAxisHelper();

	double GetFirstMinorValue(); // 获得第一个可见的小刻度起点值
	double GetFirstMajorValue(); // 获得第一个可见的大刻度起点值

	// 获得tick line 的法线偏移量
	void GetTickMarkLineDeta(double& d1, double& d2, TickMarkPositon type, int size, int direct);

	inline BOOL IsInViewport(double v) const
	{
		double k = (v - m_showMin) / (m_showMax - m_showMin);
		if (k >= 0 && k - 1.0 < DBL_EPSILON) return TRUE;
		return FALSE;
	}

	// 获得v在轴上对应的点。(高频小函数，使用内联方式加速)
	inline GPointF GetScreenPointByValue(double v)
	{
		GPointF pt  = m_begin;
		GVectorF vt = m_vpk * (v - m_showMin);
		pt          = pt.Translation(vt);

		return pt;
	}

	// 获得v在轴上对应的点。(高频小函数，使用内联方式加速)
	inline GPointF GetScreenPointByPercent(double k)
	{
		GPointF pt  = m_begin;
		GVectorF vt = m_vp * k;
		pt          = pt.Translation(vt);
		return pt;
	}

	// 获得dv在轴上对应的增量向量。(高频小函数，使用内联方式加速)
	inline GVectorF GetScreenVectorByValue(double dv) { return m_vpk * dv; }

	/**
	 * @brief 绘制沿轴方向的线
	 *
	 * @param v1 起点
	 * @param v2 终点
	 * @param dn 表示在法线方向上的偏移量
	 * @param color 线条颜色
	 * @param size 大小
	 * @param style 风格（实线，虚线等）
	 */
	void DrawBaseLine(ISurface* pSurface, double v1, double v2, const GVectorF& dn, const GColor& color, int size = 1, LineStyle* style = NULL);

	/**
	 * @brief 绘制沿着法线方向的线
	 *
	 * @param v 计算值
	 * @param dn1 法线方向起点偏移
	 * @param dn2 法线方向终点偏移
	 * @param color 线条颜色
	 * @param size 大小
	 * @param style 风格（实线，虚线等）
	 */
	void DrawNormalVectorLine(ISurface* pSurface, double v, const GVectorF& dn1, const GVectorF& dn2, const GColor& color, int size = 1, LineStyle* style = NULL);

	RECT GetLabelTextRect(ISurface* pSurface, double v, const GVectorF& dn, LPCTSTR text, int len, SIZE szTxt);

	void DrawNormalVectorTextAngle(ISurface* pSurface, double v, const GVectorF& dn, LPCTSTR text, int len, double text_angle, COLORREF& color);

	void DrawCursor(ISurface* pSurface, const GPointF& pt1, const GColor& color, int size);

  private:
	void initHelper(GVectorF& vp, const POINT& ptCenter, const ScrollZoom& axisinfo, GVectorF* vn_label);

  public:
	GPointF m_begin;    // 起点
	GVectorF m_vp;      // 距离向量
	GVectorF m_vi;      // 单位向量
	GVectorF m_vn;      // 单位法向量
	GVectorF m_vnd;     // 法线方向偏移向量
	GVectorF m_vdMinor; // 小步进向量
	GVectorF m_vdMajor; // 大步进向量

	/* data range*/
	double m_dataMin;
	double m_dataMax;

	/* show range*/
	double m_showMin;
	double m_showMax;

	double m_minor; // 小步进
	double m_major; // 大步进
	double m_k;     // 数值映射到屏幕坐标时的系数
	GVectorF m_vpk; // 预乘系数m_k，减少一次乘法运算
};




}

#endif