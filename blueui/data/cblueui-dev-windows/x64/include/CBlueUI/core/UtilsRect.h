#ifndef CBLUEUI_UNTILSRECT_AND_MATH_BLXDY_INC_H_
#define CBLUEUI_UNTILSRECT_AND_MATH_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <string>

#include "core/CCoreBasePro.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "cstring/StringShort.h"


#include <time.h>

/**
 * @brief 高精度时间差计算类
 *
 */
class CElapsed
{
  private:
	long long begin_clock_;

  public:
	CElapsed() { begin_clock_ = clock(); }

	~CElapsed(){};

	long long Stop()
	{
		long long endtime = clock();
		return endtime - begin_clock_;
	}

	void Start() { begin_clock_ = clock(); }
};

#ifdef _WIN32

class CElapsedWin
{
  private:
	LARGE_INTEGER StartingTime;
	LARGE_INTEGER Frequency;

  public:
	CElapsedWin()
	{
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&StartingTime);
	}

	~CElapsedWin(){};

	LONGLONG Stop()
	{
		LARGE_INTEGER EndingTime;
		QueryPerformanceCounter(&EndingTime);
		LONGLONG cycles = EndingTime.QuadPart - StartingTime.QuadPart;

		// ElapsedMicroseconds.QuadPart *= 1000000;
		// ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

		return cycles;
	}

	void Start()
	{
		QueryPerformanceCounter(&StartingTime);
		// QueryPerformanceCounter(&StartingTime);
	}
};
#endif




struct LayoutPosition
{
	RECT rcview;
	SIZE sz;

	LayoutPosition()
	{
		rcview = {0};
		sz     = {0};
	}
};

namespace UtilsMath {

/**
 * @brief 判断点是否在线段上
 *
 * @param pt 测试点
 * @param p1 线段起点
 * @param p2 线段终点
 * @param nWeight 线宽
 * @return BOOL TRUE 在线段上
 */
UI_EXP BOOL PtInLine(POINT pt, POINT p1, POINT p2, int nWeight);



/**
 * @brief 判断点是否在points点围成的区域内
 *
 */
UI_EXP BOOL PtInRegion(POINT pt, std::vector<POINT>& points);
UI_EXP BOOL PtInRegion(POINT pt, const POINT points[], int nlen);

/**
 * @brief 线段在各自延长线上存在交点
 *
 */
UI_EXP BOOL LineCrossPoint(POINT line1_p1, POINT line1_p2, POINT line2_p1, POINT line2_p2, POINT& ptCross);

/**
 * @brief 线段上的交点，不包括各自延长线
 *
 */
UI_EXP BOOL LineCrossPointInside(POINT line1_p1, POINT line1_p2, POINT line2_p1, POINT line2_p2, POINT& ptCross);

/**
 * @brief 根据尺寸列表，计算在区域中的位置
 *
 * @param objs 元素数组
 * @param len 个数
 * @param rcBox 显示区域
 * @param align 对齐方式
 * @param bHorz 水平布局 Or 垂直布局
 * @param interval 元素之间的间距
 * @param bReverse 正向 Or 反向
 */
UI_EXP void RectLayoutCalculator(LayoutPosition* objs, int len, RECT rcBox, UINT align, BOOL bHorz, int interval, BOOL bReverse);

/**
 * @brief 三角形顶点源
 *
 * @param pt[] 三角形顶点
 */
UI_EXP void TrianglePoint(POINT pt[], RECT rect, int dir, int size);

/**
 * @brief 同号
 *
 */
UI_EXP BOOL IsSameSign(double v1, double v2);


/**
 * @brief  向量基于x轴的夹角
 *
 * @return 值域(-PI, PI]
 */
UI_EXP double VectorAngle(double x1, double y1, double x2, double y2);

};

namespace UtilsRect {

/**
 * @brief 点是否在矩形区域内
 *
 */
UI_EXP BOOL PointInRect(const RECT* lprc1, POINT pt);

/**
 * @brief 点是否在矩形区域内
 *
 */
UI_EXP BOOL PointInRect(const RECT* lprc1, LONG x, LONG y);

/**
 * @brief 设置矩形为空（0,0,0,0）
 *
 */
UI_EXP void SetRectEmpty(RECT* lprc1);

/**
 * @brief 设置矩形尺寸
 *
 * @param lprc1
 * @param l 左边
 * @param t 顶部
 * @param r 右边
 * @param b 底部
 */
UI_EXP void SetRect(RECT* lprc1, int l, int t, int r, int b);

UI_EXP BOOL IsRectangleEmpty(const RECT* lprcSrc1);

/**
 * @brief lprc1与lprc2矩形，是否有交集
 *
 * @return TRUE:有交集，FALSE:无交集
 */
UI_EXP BOOL IsRectIntersect(LPRECT lprc1, LPRECT lprc2);

/**
 * @brief 求lprcSrc1与lprcSrc2矩形交集
 *
 * @param lprcDst 输出矩形的交集
 * @return TRUE:有交集，FALSE:无交集
 */
UI_EXP BOOL IntersectRectangle(LPRECT lprcDst, const RECT* lprcSrc1, const RECT* lprcSrc2);

/**
 * @brief 求lprcSrc1与lprcSrc2矩形并集
 *
 * @param lprcDst 输出矩形的并集
 * @return TRUE:有并集，FALSE:无并集（lprcSrc1与lprcSrc2都为空时）
 */
UI_EXP BOOL UnionRectangle(LPRECT lprcDst, const RECT* lprcSrc1, const RECT* lprcSrc2);

/**
 * @brief 矩形(lprc1)内是否包含矩形(lprc2)
 *
 */
UI_EXP BOOL IsRectContain(LPRECT lprc1, LPRECT lprc2);

/**
 * @brief 矩形(lprc1)与矩形(lprc2)，是否相等
 *
 */
UI_EXP BOOL IsRectEqual(LPRECT lprc1, LPRECT lprc2);

/**
 * @brief 矩形(pRect)，边距缩小或放大
 *
 */
UI_EXP BOOL DeflateRect(LPRECT pRect, int l, int t, int r, int b);

/**
 * @brief 矩形(pRect)，边距缩小或放大
 *
 */
UI_EXP BOOL DeflateRect(LPRECT pRect, int dx, int dy); // 缩小或放大

/**
 * @brief 矩形(pRect)平移
 *
 */
UI_EXP BOOL OffsetRect(LPRECT pRect, int dx, int dy);

/**
 * @brief 矩形(pRect)坐标标准化(左边必须小于右边，底部大于顶部)
 *
 */
UI_EXP void Normal(RECT& rect); // 标准化矩形

};


#endif
