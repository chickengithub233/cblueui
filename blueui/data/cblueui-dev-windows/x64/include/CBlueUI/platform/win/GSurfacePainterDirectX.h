#ifndef CBLUEUI_DISPLAY_GSURFACEPAINTER_DIRECTX_INC_H_
#define CBLUEUI_DISPLAY_GSURFACEPAINTER_DIRECTX_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "graphics/GSurface.h"
#include "platform/GSurfacePainter.h"

#include <d2d1.h>
#define DIRECTX_RELEASE_PTR(obj) \
	if (obj) \
	{ \
		(obj)->Release(); \
		(obj) = NULL; \
	}

namespace BUI {

class D2DFactoryHelper
{
  public:
	D2DFactoryHelper();

	~D2DFactoryHelper();

	ID2D1Factory* m_d2d_factory;
	ID2D1DCRenderTarget* m_pDCRT;
};

class GSurfacePainterDirectX : public GSurface
{
  public:
	ID2D1DCRenderTarget* m_pDCRT;
	ID2D1SolidColorBrush* m_pBlackBrush;

  public:
	GSurfacePainterDirectX(unsigned char* buf, int width, int height, int stride, int bpp, GSurfacePainter* platDevice = NULL);

	~GSurfacePainterDirectX();

	void SetClipBox(int x, int y, int w, int h, bool enable) override;
	void ResetClipBox() override;
	/* rect*/
	void FillRect(RECT rc, const GColor& color) override;

	void FillRoundRect(RECT rc, RoundRectRadius& radius, const GColor& color) override;

	void Rect(RECT rc, int size, const GColor& color, LineStyle* style = NULL) override;

	void RoundRect(RECT rc, RoundRectRadius& radius, int size, const GColor& color, LineStyle* style = NULL) override;
};

}
#endif
