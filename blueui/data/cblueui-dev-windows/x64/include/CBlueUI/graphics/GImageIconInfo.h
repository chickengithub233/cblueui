#ifndef CBLUEUI_SGIMAGESTATUS_PRO_H_INC_
#define CBLUEUI_SGIMAGESTATUS_PRO_H_INC_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include "core/CCoreBasePro.h"
#include "GSurface.h"

namespace BUI {
/**
 * @brief 包含多种状态(常规,鼠标悬停,鼠标按下,禁用)的图标
 *
 */
class UI_EXP GImageIconInfo
{
  public:
	GImageIconInfo();
	virtual ~GImageIconInfo();

	virtual BOOL IsEmpty() = 0;

	virtual void ExtentSize(UINT paintStatus, SIZE& sz, BOOL isPixelFormat = FALSE) = 0;

	virtual void ShellImageAttribute(const BeString& szName, const BeString& szText) = 0;

	virtual void DoPaintImage(ISurface* pSurface, UINT paintStatus, int x, int y, GPathStorage* path, PathConvType conv, Transform2d* img_mtx = NULL, FilterType filterMode = Filter_None) = 0;
	virtual void DoPaintImageRect(ISurface* pSurface, UINT paintStatus, const RECT& rect, double xScale = 1.0, double yScale = 1.0)                                                        = 0;

	virtual void DoPaintImageTextureRatioStyle(ISurface* pSurface, UINT paintStatus, const RECT& rcBox, ImageRatioStyle ratio_type = none_style, double angle = 0, double scale = 1.0) = 0;

	virtual void DoPaintImageTextureEllipse(ISurface* pSurface, UINT paintStatus, int x, int y, int rx, int ry, double angle = 0, double scalex = 1.0) = 0;
};

/**
 * @brief 多个状态得图像，分布在相同的图片文件中
 *
 */
class UI_EXP GImageIconSingle : public GImageIconInfo
{
  public:
	GImageIconSingle();
	~GImageIconSingle();

	void SetFrames(UINT count);
	void SetHorzLayout(BOOL bHorz);
	void SetImage(GImage* img);
	void SetStateIndex(UINT normal, UINT hot, UINT down, UINT disable);

	/* GImageIconInfo override methods:*/
	BOOL IsEmpty() override;
	void ExtentSize(UINT paintStatus, SIZE& sz, BOOL isPixelFormat = FALSE) override;
	void ShellImageAttribute(const BeString& szName, const BeString& szText) override;

	void DoPaintImage(ISurface* pSurface, UINT paintStatus, int x, int y, GPathStorage* path, PathConvType conv, Transform2d* img_mtx = NULL, FilterType filterMode = Filter_None) override;
	void DoPaintImageRect(ISurface* pSurface, UINT paintStatus, const RECT& rect, double xScale = 1.0, double yScale = 1.0) override;
	void DoPaintImageTextureRatioStyle(ISurface* pSurface, UINT paintStatus, const RECT& rcBox, ImageRatioStyle ratio_type = none_style, double angle = 0, double scale = 1.0) override;

	void DoPaintImageTextureEllipse(ISurface* pSurface, UINT paintStatus, int x, int y, int rx, int ry, double angle = 0, double scalex = 1.0) override;

  protected:
	GImage* m_image;
	BOOL m_bHorz;                  // 图片帧排列方式
	UINT m_nFrames;                // 图片帧数
	UINT m_nStateIndex[UIS_COUNT]; // 4种状态(常规,鼠标悬停,鼠标按下,禁用)帧索引
};

/**
 * @brief 多个状态得图像，分布在不同的图片文件中
 *
 */
class UI_EXP GImageIconMulti : public GImageIconInfo
{
  public:
	GImageIconMulti();
	~GImageIconMulti();

	void SetImageAllSame(GImage* img);
	void SetImage(UINT paintStatus, GImage* img);

	/* GImageIconInfo override methods: */
	BOOL IsEmpty() override;
	void ExtentSize(UINT paintStatus, SIZE& sz, BOOL isPixelFormat = FALSE) override;
	void ShellImageAttribute(const BeString& szName, const BeString& szText) override;
	void DoPaintImage(ISurface* pSurface, UINT paintStatus, int x, int y, GPathStorage* path, PathConvType conv, Transform2d* img_mtx = NULL, FilterType filterMode = Filter_None) override;
	void DoPaintImageRect(ISurface* pSurface, UINT paintStatus, const RECT& rect, double xScale = 1.0, double yScale = 1.0) override;
	void DoPaintImageTextureRatioStyle(ISurface* pSurface, UINT paintStatus, const RECT& rcBox, ImageRatioStyle ratio_type = none_style, double angle = 0, double scale = 1.0) override;

	void DoPaintImageTextureEllipse(ISurface* pSurface, UINT paintStatus, int x, int y, int rx, int ry, double angle = 0, double scalex = 1.0) override;

  protected:
	GImage* m_image[UIS_COUNT]; // 4种状态图像(常规,鼠标悬停,鼠标按下,禁用)
};


}
#endif
