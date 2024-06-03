/*
 * Geometry Data Structure Definition
 */

#ifndef CBLUEUI_CBASEUTILS_BLXDY_INC_H_
#define CBLUEUI_CBASEUTILS_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "CCoreBasePro.h"

namespace BUI {


/**
 * @brief 二维向量
 *
 */
class UI_EXP GVectorF
{
  public:
	double dx;
	double dy;

  public:
	GVectorF();
	GVectorF(double x, double y);
	GVectorF(int x, int y);
	GVectorF(long x, long y);
	GVectorF(const GVectorF& vt);
	~GVectorF();

	double Length() const;
	GVectorF NormalVector() const; // 获得法向量

	void Normalization(); // 标准化向量
	void PositiveSign();  // 正向化
	void Inverse();       // 反向

	double DotProduct(const GVectorF& other) const; // 向量点乘

	const GVectorF& operator=(const GVectorF& other);
	GVectorF operator-(const GVectorF& other) const;
	GVectorF operator+(const GVectorF& other) const;
	GVectorF operator*(double k) const;

	const GVectorF& operator-=(const GVectorF& other);
	const GVectorF& operator+=(const GVectorF& other);
	const GVectorF& operator*=(double k);
};

class UI_EXP GPointF
{
  public:
	GPointF();
	GPointF(double x_, double y_);
	~GPointF();

	const GPointF& operator=(const GPointF& other);

	GPointF Translation(const GVectorF& vt, double add = 0.0) const;
	// GPointF operator-(const GVectorF& vt);
	// GPointF operator+(const GVectorF& vt);

  public:
	double x;
	double y;
};

///* 坐标点移动迭代器*/
// class UI_EXP GPointFIterator
//{
// public:
//	GPointFIterator(GPointF & pt, GVectorF & vt);
//	~GPointFIterator();
//
//	const GPointF& operator++();
//	const GPointF& operator--();
// public:
//	GPointF m_point;
//	GPointF m_point;
//	GVectorF m_v_step;
// };




/**
 * @brief 二维平面上的点(long)
 *
 */
class UI_EXP GPoint
{
  public:
	GPoint();
	GPoint(long x_, long y_);
	~GPoint();
	void Translate(long dx_, long dy_);
	void Swap();

	// 向量内积,结果为数值
	long DotProduct(const GPoint& b);

	const GPoint& operator=(const GPoint& other);
	GPoint operator-(const GPoint& other);
	GPoint operator+(const GPoint& other);
	GPoint operator*(long k);

  public:
	long x;
	long y;
};

typedef GPoint GVector;

/**
 * @brief 二维平面上的点(double)
 *
 */
class UI_EXP Point2Double
{
  public:
	Point2Double();
	Point2Double(double x_, double y_);
	~Point2Double();
	void Translate(double dx_, double dy_);
	const Point2Double& operator=(const Point2Double& other);
	// const Point2Double& operator-(const Point2Double& other);

  public:
	double x;
	double y;
};

/**
 * @brief 矩形(int)
 *
 */
class UI_EXP GRect
{
  public:
	GRect();
	GRect(int l, int t, int r, int b);
	GRect(const GRect& rt);

  public:
	BOOL IsRectEmpty() const;
	BOOL IsInRect(int x, int y) const;

	void Normalization();

	int Width() const;

	void SetWidth(int w);

	int Height() const;

	void SetHeight(int h);

	void OffsetRect(int x, int y);

	void SetPoint(int x, int y);

	void SetSize(int w, int h);

	void SetRect(int l, int t, int r, int b);

	void SetRect(const GRect& rt);

	GPoint CenterPoint() const;

	int Length() const;

	int Area() const;

	BOOL IntersectRect(const GRect& rt);

	BOOL IntersectRect(const GRect& rt1, const GRect& rt2);

	void UnionRect(const GRect& rt);

	void UnionRect(const GRect& rt1, const GRect& rt2);

	void InflateRect(int l, int t, int r, int b);

	void InflateRect(int x, int y);

	void InflateRect(const GRect& rt);

	void DeflateRect(int l, int t, int r, int b);

	void DeflateRect(int x, int y);

	void SwapLeftRight();

	void SwapTopBottom();

	void Swap();

	void SetRectEmpty();

	void Translate(int dx_, int dy_);

	RECT ToRECT() const;

	const GRect& operator=(const GRect& rt);

	BOOL operator==(const GRect& rt) const;

	BOOL operator!=(const GRect& rt) const;

	const GRect& operator&=(const GRect& rt);

	const GRect& operator|=(const GRect& rt);

	GRect operator&(const GRect& rt) const;

	GRect operator|(const GRect& rt) const;


  public:
	int left;
	int right;
	int top;
	int bottom;
};

/**
 * @brief 尺寸(int)
 *
 */
class UI_EXP GSize
{
  public:
	GSize();
	GSize(int cx_, int cy_);
	~GSize();

	const GSize& operator=(const GSize& other);

  public:
	int cx;
	int cy;
};



}

#endif