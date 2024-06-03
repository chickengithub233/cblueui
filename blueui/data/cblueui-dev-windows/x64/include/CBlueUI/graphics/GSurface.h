#ifndef CBLUEUI_DISPLAY_SURFACEENGINE_PAN_INC_H_
#define CBLUEUI_DISPLAY_SURFACEENGINE_PAN_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include "core/CCoreBasePro.h"
#include "core/MathMatrix.h"
#include "platform/GSurfacePainter.h"
#include "GColor.h"
#include "GImage.h"
#include "GBrushGradient.h"
#include "GPathStorage.h"
#include "GPathStorageSVG.h"
#include "GRasterGlyph.h"

namespace BUI {

enum LineCapStyle
{
	BUTT,
	SQUARE,
	ROUND
};

struct LineStyle
{
	PenType type_;
	LineCapStyle linecap_;
	LineCapStyle joincap_;
	int dash_offset_;

	LineStyle(PenType type = PenTypeSoild, LineCapStyle cap = ROUND, int ds_offset = 0)
	    : type_(type)
	    , dash_offset_(ds_offset)
	    , linecap_(cap)
	    , joincap_(cap)
	{}
};

/**
 * 阴影特效信息
 */
struct ShadowInfo
{
	SIZE trans;   // 阴影平移
	SIZE scale;   // 缩放尺寸(单位像素)。当>0 向外扩张。当<0时向内收紧
	SIZE blur;    // 模糊半径。当半径为<=0时，为实色阴影。
	BOOL inset;   // TRUE:内阴影;FALSE:外阴影（默认FALSE）
	GColor color; // 颜色
	RECT rcBox;   // 阴影区域

	ShadowInfo();
};


/**
 * 路径变换信息
 */
struct PathTransInfo
{
	int dx; // 相对偏移量
	int dy;
	GPathStorage* path; // 路径原始数据
	PathConvType conv;  // 变换方式

	PathTransInfo(GPathStorage* vs, PathConvType type = CONV_NONE)
	    : dx(0)
	    , dy(0)
	    , path(vs)
	    , conv(type)
	{}
};

UI_EXP void ShellTextGlyphEffect(TransAlongSinglePath& ge, const BeString& szName, const BeString& szText);

/*
meet(默认值) : 保持纵横比缩放viewBox适应viewport，使 svg 尽可能的显示在 viewport 里，会在 scale_x 和 scale_y 中选择最小的值作为缩放标准。

slice : 保持纵横比同时比例小的方向放大填满viewport，使 svg 完全铺满 viewport，会在 scale_x 和 scale_y 中选择最大的值作为缩放标准。

none : 扭曲纵横比以充分适应viewport
*/
enum ImageRatioStyle
{
	meet_style, // keep aspect ratio scaling
	slice_style,
	none_style
};

/**
 * @brief 图形接口
 *
 */
class UI_EXP ISurface
{
  public:
	ISurface();
	~ISurface();

	virtual void DoDrawEvent(SurEvent* ev);

	virtual XPixelFormat GetPixelFormat() = 0;

	virtual double GetPixelRatio() = 0;

	virtual BlendCompType SetBlendCompType(BlendCompType op = comp_none) = 0;

	virtual void SetClipBox(int x, int y, int w, int h, bool enable) = 0;

	virtual void GetClipBox(int* x, int* y, int* w, int* h) = 0;

	virtual void ResetClipBox() = 0;

	virtual GSurfacePainter* PlatformPainter() = 0;

	virtual GFont* SelectFontObject(GFont* font) = 0;

	virtual GFont* GetCurrentFontObject() = 0;

	virtual void PaintTextMultiLine(int x, int y, TextMultilineInfo* multiText, COLORREF color, UINT align = DT_LEFT | DT_TOP) = 0;

	virtual void PaintTextOutW(int x, int y, LPCWSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP) = 0;

	virtual void PaintTextOutA(int x, int y, LPCSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP) = 0;

	virtual void PaintTextOut(int x, int y, LPCTSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP) = 0;

	virtual void PaintTextW(LPRECT lprc, LPCWSTR text, int c, COLORREF color, UINT format) = 0;

	virtual void PaintTextA(LPRECT lprc, LPCSTR text, int c, COLORREF color, UINT format) = 0;

	virtual void PaintText(LPRECT lprc, LPCTSTR text, int c, COLORREF color, UINT format) = 0;

	virtual void PaintTextAngleW(int x, int y, float angle, LPCWSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP) = 0;

	virtual void PaintTextAngleA(int x, int y, float angle, LPCSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP) = 0;

	virtual void PaintTextAngle(int x, int y, float angle, LPCTSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP) = 0;

	virtual void PaintFontTextOut(void* font, int x1, int y1, LPCSTR text, int c, COLORREF color) = 0;

	virtual SIZE GetTextSize(LPCTSTR sztext, int nlen) = 0;

	virtual SIZE GetTextSizeW(LPCWSTR sztext, int nlen) = 0;

	virtual SIZE GetTextSizeA(LPCSTR sztext, int nlen) = 0;
	/* line */
	virtual void Line(int x1, int y1, int x2, int y2, int size, const GColor& color, LineStyle* style = NULL) = 0;

	virtual void Arc(double x, double y, double rx, double ry, double a1, double a2, int size, const GColor& color, LineStyle* style = NULL) = 0;

	virtual void BezierDiv(POINT pt[4], int size, const GColor& color, LineStyle* style = NULL) = 0;

	virtual void BezierDivCurve3(POINT pt[3], int size, const GColor& color, LineStyle* style = NULL) = 0;

	/* rect*/
	virtual void FillRect(RECT rc, const GColor& color) = 0;

	virtual void FillRoundRect(RECT rc, RoundRectRadius& radius, const GColor& color) = 0;

	virtual void Rect(RECT rc, int size, const GColor& color, LineStyle* style = NULL) = 0;

	virtual void RoundRect(RECT rc, RoundRectRadius& radius, int size, const GColor& color, LineStyle* style = NULL) = 0;

	/* circle */
	virtual void FillEllipse(int x, int y, int rx, int ry, const GColor& color) = 0;

	virtual void Ellipse(int x, int y, int rx, int ry, int size, const GColor& color, LineStyle* style = NULL) = 0;

	/* path2*/
	virtual void FillPath(const PathTransInfo& pathInfo, const GColor& color, BOOL bin_render = FALSE) = 0;

	virtual void DrawPath(const PathTransInfo& pathInfo, const GColor& color, int size = 1, LineStyle* style = NULL) = 0;

	virtual void FillPathGradient(const PathTransInfo& pathInfo, GradientColors* colors, TransformGradient& mtx) = 0;

	virtual void DrawPathGradient(const PathTransInfo& pathInfo, GradientColors* colors, TransformGradient& mtx, int size = 1, LineStyle* style = NULL) = 0;

	virtual void DrawPathPattern(const PathTransInfo& pathInfo, XImageInfo* patten_texture, int size = 1, int alpha = 255, double scale = 1) = 0;

	virtual void DrawCheckBox(RECT rc, const GColor& color, UINT nState, int size) = 0;

	virtual void DrawSpring(RECT rc, bool bHor, bool bFill, const GColor& crColor) = 0;

	virtual void Fill3DTriangularPlane(Point3 p1, Point3 p2, Point3 p3, const GColor& color) = 0;
	/* expand button*/
	virtual void DrawExpandButton(POINT ptCenter, int nSize, bool bCollapsed, const GColor& color) = 0;

	virtual void DrawExpandTriButton(POINT pointCenter, int nSize, bool bCollapsed, const GColor& color) = 0;

	/* image */
	virtual void DrawImageRatioStyle(XImageInfo* pSrcSurface, int x, int y, int w, int h, ImageRatioStyle ratio_type = none_style, double angle = 0, double scale = 1.0, FilterType filterMode = Filter_None) = 0;

	virtual void DrawImageRect(XImageInfo* pSrcSurface, int x, int y, int w, int h, RoundRectRadius* radius = NULL, double angle = 0, FilterType filterMode = Filter_None, int alpha = 0xff) = 0;

	virtual void DrawImageEllipse(XImageInfo* pSrcSurface, int cx, int cy, int rx, int ry, double angle = 0, double scalex = 1.0, FilterType filterMode = Filter_None, int alpha = 0xff) = 0;

	virtual void DrawImage(const PathTransInfo& pathInfo, XImageInfo* pSrcSurface, Transform2d* img_mtx, FilterType filterMode = Filter_None, int alpha = 0xff) = 0;

	virtual void GetImageRatioTransform2d(Transform2d* img_mtx, const XImageInfo* pSrcSurface, int x, int y, int w, int h, ImageRatioStyle ratio_type, double angle, double scale) = 0;

	/* shadow and blur*/
	virtual void FillShadow(const PathTransInfo& pathInfo, ShadowInfo* shadowinfo)                                        = 0;
	virtual void DrawShadow(const PathTransInfo& pathInfo, ShadowInfo* shadowinfo, int size = 1, LineStyle* style = NULL) = 0;

	virtual void Blur(int x, int y, int w, int h, int blur_size)                                           = 0;
	virtual void BlurStoreBackground(int x, int y, int w, int h, int blur_size)                            = 0; // 存储当前画布区域背景
	virtual void BlurFront(int x, int y, int w, int h, int dx, int dy, int widget, const GColor color)     = 0;
	virtual void BlendFrom(int x, int y, int w, int h, XImageInfo* from, GColor color, BlendCompType comp) = 0;

	virtual void Gray(int x, int y, int w, int h, int conv_type) = 0;
	/* svg */
	virtual void PaintSVG(GPathStorageSVG* svg, VIEW_BOX* box) = 0;
	/* gouraud render */
	virtual void GouraudRender(POINT p1, POINT p2, POINT p3, const GColor& c1, const GColor& c2, const GColor& c3) = 0;

	virtual void DrawTextMono(unsigned char* data, int x, int y, int w, int h, const GColor& color) = 0;

	virtual void GlyphRaster(const RECT& rc, const GRasterGlyph* glyphBin, const GColor& color) = 0;

	virtual void GlyphRaster(int x, int y, const GRasterGlyph* glyphBin, const GColor& color) = 0;

	virtual void CopyFrom(const XImageInfo& img, LPRECT rcSrc, int dx = 0, int dy = 0) = 0; // 拷贝像素

	virtual void CopyTo(const XImageInfo& img, LPRECT rcSrc, int dx = 0, int dy = 0) = 0; // 拷贝像素

	virtual void GetXImageInfo(XImageInfo* info, LPRECT rcSrc) = 0; // 获得图像区域

	virtual void Clear(const GColor& color) = 0; // 清除画面

	virtual void SaveAsImageFile(LPCTSTR file, RECT& rc) = 0; // 保存画面
};

/**
 * @brief 实现图形接口
 *
 */
class UI_EXP GSurface : public ISurface
{
  protected:
	GSurfacePainter* m_platformPainter;

	LONG m_iWidth;
	LONG m_iHeight;
	LONG m_nBpp;
	LONG m_nStride;
	LONG m_OrgX;
	LONG m_OrgY;
	/* clip box*/
	LONG m_iClipX;
	LONG m_iClipY;
	LONG m_iClipW;
	LONG m_iClipH;
	unsigned char* m_buf;
	XPixelFormat m_pixelformat; // 像素格式

	unsigned char* m_buf_z; // z-buffer data [0-255],值越大像素越靠近观察者
	/* trans scale*/
	double m_scaleFactor;
	Transform2d m_trans_storage;
	Transform2d* m_pTrans;
	/* pen info*/
	LineCapStyle m_penCap;
	PenType m_penStyle;
	int m_dash_len;
	int m_cap_len;
	/* brush color*/
	GColor m_solidcolor;
	BlendCompType m_comp_type;

  public:
	GSurface(unsigned char* buf, int width, int height, int stride, int bpp, GSurfacePainter* platDevice = NULL);
	virtual ~GSurface();

	/* attribute info */
	unsigned char* Buffer();
	int Width();
	int Height();
	int Stride();
	int StrideAbs();

	int PixelBitCounts() const;
	void SetViewportOrg(int x, int y);
	void GetViewportOrg(int* x, int* y);

	void SetPixelFormat(XPixelFormat fmt);

	void SetLineCap(LineCapStyle cap);
	void SetPenStyle(PenType style, int dashx, int dashy);

	/* attch 3d z-buffer memory alloc size*/
	void AttachZbuffer(unsigned char* zbuf);

	/* pre init */
	void Attach(unsigned char* buf, int width, int height, int stride, int bpp);

	void AttachPlatformPainter(GSurfacePainter* platDevice);

	double SetPixelRatio(double scaleFactor);

	/* ISurface methods:*/
	virtual XPixelFormat GetPixelFormat();
	virtual double GetPixelRatio();
	virtual BlendCompType SetBlendCompType(BlendCompType op = comp_none);
	virtual void SetClipBox(int x, int y, int w, int h, bool enable);
	virtual void GetClipBox(int* x, int* y, int* w, int* h);
	virtual void ResetClipBox();
	virtual GSurfacePainter* PlatformPainter();
	virtual void DoDrawEvent(SurEvent* ev);

	virtual GFont* SelectFontObject(GFont* font);
	virtual GFont* GetCurrentFontObject();

	virtual void PaintTextMultiLine(int x, int y, TextMultilineInfo* multiText, COLORREF color, UINT align = DT_LEFT | DT_TOP);

	virtual void PaintTextOutW(int x, int y, LPCWSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP);
	virtual void PaintTextOutA(int x, int y, LPCSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP);
	virtual void PaintTextOut(int x, int y, LPCTSTR text, int c, COLORREF color, UINT align = DT_LEFT | DT_TOP);

	virtual void PaintTextW(LPRECT lprc, LPCWSTR text, int c, COLORREF color, UINT format);
	virtual void PaintTextA(LPRECT lprc, LPCSTR text, int c, COLORREF color, UINT format);
	virtual void PaintText(LPRECT lprc, LPCTSTR text, int c, COLORREF color, UINT format);

	virtual void PaintTextAngleW(int x, int y, float angle, LPCWSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP);
	virtual void PaintTextAngleA(int x, int y, float angle, LPCSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP);
	virtual void PaintTextAngle(int x, int y, float angle, LPCTSTR sztext, int nlen, COLORREF color, UINT align = DT_LEFT | DT_TOP);

	virtual void PaintFontTextOut(void* font, int x1, int y1, LPCSTR text, int c, COLORREF color);

	virtual SIZE GetTextSize(LPCTSTR sztext, int nlen);
	virtual SIZE GetTextSizeW(LPCWSTR sztext, int nlen);
	virtual SIZE GetTextSizeA(LPCSTR sztext, int nlen);
	/* path */

	/* line and curve*/
	virtual void Line(int x1, int y1, int x2, int y2, int size, const GColor& color, LineStyle* style = NULL);
	virtual void Arc(double x, double y, double rx, double ry, double a1, double a2, int size, const GColor& color, LineStyle* style = NULL);

	/**
	 * @brief 贝塞尔曲线（4控制点）
	 *
	 * @param pt 控制点
	 * @param width 曲线宽度
	 * @param color 曲线颜色
	 * @param lineStyle
	 * @param nCapType
	 */
	virtual void BezierDiv(POINT pt[4], int size, const GColor& color, LineStyle* style = NULL);
	virtual void BezierDivCurve3(POINT pt[3], int size, const GColor& color, LineStyle* style = NULL);

	/* rect */
	virtual void FillRect(RECT rc, const GColor& color);
	virtual void FillRoundRect(RECT rc, RoundRectRadius& radius, const GColor& color);
	virtual void Rect(RECT rc, int size, const GColor& color, LineStyle* style = NULL);
	virtual void RoundRect(RECT rc, RoundRectRadius& radius, int size, const GColor& color, LineStyle* style = NULL);

	/* Ellipse */
	virtual void FillEllipse(int x, int y, int rx, int ry, const GColor& color);
	virtual void Ellipse(int x, int y, int rx, int ry, int size, const GColor& color, LineStyle* style = NULL);

	virtual void FillPath(const PathTransInfo& pathInfo, const GColor& color, BOOL bin_render = FALSE);
	virtual void DrawPath(const PathTransInfo& pathInfo, const GColor& color, int size = 1, LineStyle* style = NULL);

	virtual void FillPathGradient(const PathTransInfo& pathInfo, GradientColors* colors, TransformGradient& mtx);

	virtual void DrawPathGradient(const PathTransInfo& pathInfo, GradientColors* colors, TransformGradient& mtx, int size = 1, LineStyle* style = NULL);

	virtual void DrawPathPattern(const PathTransInfo& pathInfo, XImageInfo* patten_texture, int size = 1, int alpha = 255, double scale = 1);

	/* 3d draw*/
	virtual void Fill3DTriangularPlane(Point3 p1, Point3 p2, Point3 p3, const GColor& color);


	/* other poly */
	virtual void DrawCheckBox(RECT rc, const GColor& color, UINT nState, int size);

	virtual void DrawSpring(RECT rc, bool bHor, bool bFill, const GColor& crColor);

	virtual void DrawExpandButton(POINT ptCenter, int nSize, bool bCollapsed, const GColor& color);

	virtual void DrawExpandTriButton(POINT pointCenter, int nSize, bool bCollapsed, const GColor& color);

	/* image */

	/**
	 * @brief 绘制纹理图案
	 *
	 * @param pSrcSurface 纹理数据
	 * @param x 目标起点
	 * @param y
	 * @param w 目标宽高
	 * @param h
	 * @param sx 源图像起点
	 * @param sy
	 * @param sw 源图像宽高
	 * @param sh
	 * @param ratio_type 纵横比的方式
	 * @param angle 旋转角度
	 * @param scale 缩放比例
	 */
	virtual void DrawImageRatioStyle(XImageInfo* pSrcSurface, int x, int y, int w, int h, ImageRatioStyle ratio_type = none_style, double angle = 0, double scale = 1.0, FilterType filterMode = Filter_None);

	virtual void DrawImageRect(XImageInfo* pSrcSurface, int x, int y, int w, int h, RoundRectRadius* radius = NULL, double angle = 0, FilterType filterMode = Filter_None, int alpha = 0xff);
	virtual void DrawImageEllipse(XImageInfo* pSrcSurface, int cx, int cy, int rx, int ry, double angle = 0, double scalex = 1.0, FilterType filterMode = Filter_None, int alpha = 0xff);

	virtual void DrawImage(const PathTransInfo& pathInfo, XImageInfo* pSrcSurface, Transform2d* img_mtx, FilterType filterMode = Filter_None, int alpha = 0xff);

	virtual void GetImageRatioTransform2d(Transform2d* img_mtx, const XImageInfo* pSrcSurface, int x, int y, int w, int h, ImageRatioStyle ratio_type, double angle, double scale);
	/* svg */
	virtual void PaintSVG(GPathStorageSVG* svg, VIEW_BOX* box);

	/* shadow and blur*/
	virtual void FillShadow(const PathTransInfo& pathInfo, ShadowInfo* shadowinfo);
	virtual void DrawShadow(const PathTransInfo& pathInfo, ShadowInfo* shadowinfo, int size = 1, LineStyle* style = NULL);

	virtual void Blur(int x, int y, int w, int h, int widget);

	virtual void BlurStoreBackground(int x, int y, int w, int h, int blur_size); // 存储当前画布区域背景
	virtual void BlurFront(int x, int y, int w, int h, int dx, int dy, int blur_size, const GColor color);
	virtual void BlendFrom(int x, int y, int w, int h, XImageInfo* from, GColor color, BlendCompType comp);

	virtual void Gray(int x, int y, int w, int h, int conv_type); // 灰度显示。conv_type表示灰度公式
	/* gouraud render */
	virtual void GouraudRender(POINT p1, POINT p2, POINT p3, const GColor& c1, const GColor& c2, const GColor& c3);

	virtual void DrawTextMono(unsigned char* data, int x, int y, int w, int h, const GColor& color);

	virtual void GlyphRaster(const RECT& rc, const GRasterGlyph* glyphBin, const GColor& color);
	virtual void GlyphRaster(int x, int y, const GRasterGlyph* glyphBin, const GColor& color);

	virtual void CopyFrom(const XImageInfo& img, LPRECT rcSrc, int dx = 0, int dy = 0); // 拷贝像素
	virtual void CopyTo(const XImageInfo& img, LPRECT rcSrc, int dx = 0, int dy = 0);   // 拷贝像素

	virtual void GetXImageInfo(XImageInfo* info, LPRECT rcSrc); // 获得图像区域

	virtual void Clear(const GColor& color); // 清除画面

	virtual void SaveAsImageFile(LPCTSTR file, RECT& rc); // 保存画面

	void DrawColorPicker(float h, RECT rect);
	void FilterGray();

	RECT GetClipRect() const;
	/*static common */
};

class UI_EXP ClipBoxSurface
{
  private:
	ISurface* m_pSurface;
	RECT m_rcOrgBox;
  public:
	ClipBoxSurface();
	~ClipBoxSurface();

	ClipBoxSurface(ISurface* pSurface, const RECT* rcClip, BOOL intersection = TRUE);

	/**
	 * @brief 裁剪表面
	 *
	 * @param pSurface 目标
	 * @param rcClip 可视区域
	 */
	void GenerateClip(ISurface* pSurface, const RECT* rcClip, BOOL intersection = TRUE);

	void ReleaseClip();

	RECT GetClipRect();

};



}

#endif