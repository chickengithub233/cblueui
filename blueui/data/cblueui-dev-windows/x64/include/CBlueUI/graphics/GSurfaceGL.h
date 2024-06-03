#ifdef CBLUEUI_USE_LIB_GRAPHICS_GL

#ifndef CBLUEUI_GSURFACEGL_INCLUDED_
#define CBLUEUI_GSURFACEGL_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "graphics/GImage.h"

#ifdef _WIN32
#include "platform/win/bufferDC.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include "platform/win/wglext.h"
#else
#include "graphics-gl/system-gl.h"

class OpenGLContext;
class FBO;
#endif



namespace BUI {

class GOffscreen
{
  public:
	GOffscreen();
	GOffscreen(int w, int h);
	~GOffscreen();

	bool IsVaild() const;               ///< 有效画布，返回TRUE
	void ResizeOffscreen(int w, int h); ///< 重置大小
	void BeginDraw();
	void EndDraw();

	bool GetFrameBufferPixels(XImageInfo* info); ///< 获取GPU显存像素缓存到CPU内存
  private:
#ifdef _WIN32
	HDC m_hdc;
	MemDC m_device;
#else
	std::shared_ptr<OpenGLContext> m_ctx;
	std::unique_ptr<FBO> m_fbo;
#endif
};
}

#endif


#endif