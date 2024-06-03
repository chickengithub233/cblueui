/**********************************************************************************
CBlueUI library.
Copyright (C) 2015  CBlueUI Studio<2842004379@qq.com>

Declaration
All rights reserved.
China

This software is released under the "CBlueUI License" (hereinafter referred to as the "License").
You may only use and distribute this software in accordance with the terms and conditions of the License.
Please make sure that you have read, understood, and accepted all the provisions of the License before using this software.
If you do not agree with any provisions of the License, you are not authorized to use this software.

This software is provided "as is" without any warranty, expressed or implied.
The author and copyright owner expressly disclaim any warranties, including but not limited to the implied warranties
of merchantability, fitness for a particular purpose, and non-infringement. In no event shall the author or copyright owner
be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to,
procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and
on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in
any way out of the use of this software, even if advised of the possibility of such damage.

For further details about the License, please refer to the license document.

声明：
保留所有权利
中国
本软件是根据CBlueUI许可证（下称“协议”）发布的，您只能在符合协议规定的条件下使用和分发本软件。
请确保在使用本软件之前，您已阅读、理解并接受协议的所有条款和条件。如果您不同意协议的任何规定，您将无权使用本软件。

本软件在不作任何明示或暗示的情况下，以“原样”提供。作者和版权所有者明确声明不提供任何形式的明示或暗示保证，包括但不限于
对该软件的适用性、适销性或特定用途的适用性的暗示保证。在任何情况下，作者和版权所有者对于使用本软件所导致的任何直接、间接、
附带的或特殊的损失或责任不承担任何责任。

如需详细了解协议的内容，请参考协议文档。

**********************************************************************************/

#ifndef CBLUEUI_GRADIENTBRUSH_BLXDY_INC_H_
#define CBLUEUI_GRADIENTBRUSH_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <map>
#include "core/CCoreBasePro.h"
#include "core/CGeometryStruct.h"
#include "core/Transform2d.h"
#include "GColor.h"
#include "GPathStorage.h"

namespace BUI {

enum BrushStyle
{
	BRUSH_SOLID,
	GRADIENT_LINEAR,
	GRADIENT_RADIAL,
	GRADIENT_CONIC
};

// 2d trans_affine
struct TransformGradient : public Transform2d
{
	BrushStyle gradient_bru;

	TransformGradient()
	    : gradient_bru(GRADIENT_LINEAR)
	{}
};

UI_EXP void CalcLinearGradientTransform(double x1, double y1, double x2, double y2, TransformGradient& mtx, double gradient_d2 = 100.0);

UI_EXP void CalcRadialGradientTransform(double cx, double cy, double rx, double ry, double angle, TransformGradient& mtx, double gradient_d2 = 100.0);

UI_EXP void RotationGradientTransform(Transform2d& mtx, double dx, double dy);

class UI_EXP PathTransformAffine : public PathTransform
{
  public:
	PathTransformAffine();
	PathTransformAffine(Transform2d& mtx);
	Transform2d& GetTransform2d();
	virtual ~PathTransformAffine();
	void Transform(double* x, double* y) override;
	void Transform2x2(double* x, double* y) override;

  public:
	Transform2d m_affine;
};

/**
 * @brief 渐变的渲染颜色
 *   + Size() 返回颜色细腻程度。值越大，代表颜色细致
 *   + operator[] 返回颜色值
 */
class UI_EXP GradientColors
{
  public:
	GradientColors() {}

	virtual ~GradientColors() {}

	virtual void SetColorsSize(int size) = 0; // 设置颜色细腻程度

	virtual unsigned Size() const = 0;

	virtual GColor operator[](unsigned i) = 0;

	/**
	 * @brief 根据百分比获得颜色值
	 *
	 * @param k [0-1]百分比
	 * @return GColor
	 */
	virtual GColor GetColor(double k) = 0;
};

/**
 * @brief 双值线性颜色表
 *
 */
class UI_EXP GradientLinearColors : public GradientColors
{
  public:
	GradientLinearColors(const GColor& c1, const GColor& c2);
	virtual ~GradientLinearColors();

	UINT Size() const override;
	void SetColorsSize(int size) override;

	GColor operator[](unsigned i) override;

	GColor GetColor(double k) override;

  protected:
	unsigned m_size;
	GColor m_c1;
	GColor m_c2;
};

/**
 * @brief 双值线性颜色表(具有起点百分比)
 *
 */
class UI_EXP GradientLinearSegmentColors : public GradientLinearColors
{
  public:
	GradientLinearSegmentColors(double pos, const GColor& c1, const GColor& c2);
	virtual ~GradientLinearSegmentColors();


	GColor operator[](unsigned i) override;

  private:
	double m_start_pos; // 开始起点百分比[0,1]
};

/**
 * @brief 相位颜色表
 *
 */
class UI_EXP GradientLinearPhaseColors : public GradientColors
{
  public:
	GradientLinearPhaseColors(GColorHSV c1, GColorHSV c2);
	virtual ~GradientLinearPhaseColors();

	UINT Size() const override;
	void SetColorsSize(int size) override;

	GColor operator[](unsigned i) override;

	GColor GetColor(double k) override;

  private:
	unsigned m_size;
	GColorHSV m_c1;
	GColorHSV m_c2;

	GColorHSV m_cdx;
};

/**
 * @brief 自定义位置线性颜色表
 *
 */
class UI_EXP GradientStopsColors : public GradientColors
{

  public:
	GradientStopsColors();
	virtual ~GradientStopsColors();
	void AddColor(double offset, const GColor& color);

	void SetProfilePoint(std::map<double, GColor>& points);

	void SetRangeOfKey(double fmin, double fmax);
	void ClearProfilePoint();

	BOOL IsColorEmpty() const;

	int ProfilePointSize() const;
	void BuildLutColorBuffer();

	/* GradientColors override method:*/
	void SetColorsSize(int size) override;
	unsigned Size() const override;
	GColor operator[](unsigned i) override;
	GColor GetColor(double k) override;

  private:
	void Release();

  private:
	std::map<double, GColor> m_profile_point; // key:在[m_min, m_max]的值。默认范围为[0~1]
	double m_min;
	double m_max;
	unsigned m_Lut_size;
	GColor* m_colorbuffer;
	unsigned m_capacity;
};

/**
 * @brief 渐变画刷由渐变方式和渐变颜色两部分组成
 *
 */
class UI_EXP GBrushGradient
{
  public:
	GBrushGradient();
	virtual ~GBrushGradient();
	void SetGradientColors(GradientColors* colors); ///< 设置不同状态下的颜色表
	GradientColors* GetStatusColors() const;
	TransformGradient& GradientTransMtx();

	BOOL GetColor(double k, GColor& out_color); ///< 获得颜色表中位置(k)的映射颜色

	virtual void ApplyBrushTransform(PathTransform* trans);
	virtual void ApplyBrushRect(RECT rc) = 0;

  protected:
	GradientColors* m_stopcolors;
	TransformGradient m_mtx;
};

/**
 * @brief 线性渐变画刷
 *
 */
class UI_EXP GBrushGradientLinear : public GBrushGradient
{
  public:
	GBrushGradientLinear();
	GBrushGradientLinear(const GPointF& p1, const GPointF& p2);
	GBrushGradientLinear(double x1, double y1, double x2, double y2);
	~GBrushGradientLinear();

	void SetPosition(const GPointF& p1, const GPointF& p2); // 线性渲染的起始坐标。坐标由百分比表示
	void ShellGradientAttribute(const BeString& szName, const BeString& szText);

	void ApplyBrushTransform(PathTransform* trans) override;
	void ApplyBrushRect(RECT rc) override;

  protected:
	GPointF m_pt1;
	GPointF m_pt2;
};

/**
 * @brief 中心放射渐变画刷
 *
 */
class UI_EXP GBrushGradientRadial : public GBrushGradient
{
  public:
	GBrushGradientRadial();
	GBrushGradientRadial(float x, float y, float r, float fx, float fy, float angle = 0);
	~GBrushGradientRadial();

	void SetRotateAngle(float angle);
	void SetPosition(const GPointF& ptcenter, float r, float fx, float fy); // 放射渲染的中心坐标。坐标由百分比表示
	void ShellGradientAttribute(const BeString& szName, const BeString& szText);

	void ApplyBrushTransform(PathTransform* trans) override;
	void ApplyBrushRect(RECT rc) override;

  protected:
	GPointF m_ptcenter;
	float m_r;
	float m_fx;
	float m_fy;
	float m_angle; // 起点偏移左侧水平基线角度。[0~360]
};

/**
 * @brief 圆周渐变画刷
 *
 */
class UI_EXP GBrushGradientConic : public GBrushGradient
{
  public:
	GBrushGradientConic();
	GBrushGradientConic(float x, float y, float angle = 0);
	~GBrushGradientConic();
	void SetRotateAngle(float angle);          // 设置旋转角度
	void SetPosition(const GPointF& ptcenter); // 放射渲染的中心坐标。坐标由百分比表示
	void ShellGradientAttribute(const BeString& szName, const BeString& szText);

	void ApplyBrushTransform(PathTransform* trans) override;
	void ApplyBrushRect(RECT rc) override;

  protected:
	GPointF m_ptcenter;
	float m_r;
	float m_fx;
	float m_fy;
	float m_angle;
};

/**
 * @brief 普通，高亮，选中，禁用四种状态下渐变画刷的封装类
 *
 */
class UI_EXP CBrushGradientSet
{
  public:
	CBrushGradientSet();
	~CBrushGradientSet();

	void SetBrushGradient(ShowStatus state, GBrushGradient* bru);
	GBrushGradient* GetBrushGradient(ShowStatus state) const;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | gradient <br/>背景渐变色                      | gradient="normal:资源标识符;light:资源标识符;selected:资源标识符;disable:资源标识符"	    |
	 * | gradient-normal <br/>背景常规状态渐变色        | gradient-normal="资源标识符"	    |
	 * | gradient-light <br/>背景高亮状态渐变色         | gradient-light="资源标识符"		    |
	 * | gradient-selected <br/>背景选中状态渐变色      | gradient-selected="资源标识符"		    |
	 * | gradient-disable <br/>背景禁用渐变色          | gradient-disable="资源标识符"		    |
	 */

	BOOL ShellGradientAttrbuite(LPCTSTR szName, LPCTSTR szText);

  protected:
	GBrushGradient* m_bru[UIS_COUNT];
};




}
#endif