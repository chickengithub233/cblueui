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
#ifndef CBLUEUI_SGENGINE_CORE_SGImage_PRO_H_INCLUDED_
#define CBLUEUI_SGENGINE_CORE_SGImage_PRO_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include "core/CCoreBasePro.h"
#include "core/CTimerWheel.h"
#include "GColor.h"

namespace BUI {


/**
 * @brief
 *
 */
class UI_EXP GImage
{
  public:
	GImage();
	virtual ~GImage();

	virtual bool LoadBufferImage(unsigned char* buffer, UINT dwSize);

	UBYTE* Buffer() const;

	SIZE ImageSize(BOOL isPixelFormat = FALSE) const;


	void AllocImage(int w, int h, XPixelFormat fmt, BOOL clear); // 分配表面内存
	XPixelFormat GetPixelFormat() const;
	// 获得多帧图片的某一帧
	void GetXImageInfoInFrames(XImageInfo* info, BOOL isHroz, int current, int frameCounts) const;

	// 获得整张图片
	void GetXImageInfo(XImageInfo* info) const;

	// 获得某一区域
	void GetXImageInfoInArea(XImageInfo* info, int x, int y, int w, int h) const;

	int Stride() const;
	int StrideAbs() const;
	UINT PixelBitCounts() const;

	void Destory();

	void CopyForm(const unsigned char* data, int w, int h, int bpp);

	// 根据透明度。生成阴影格式。必须是具有alpha通道图像
	void MakeShaddow(int dx, int dy, int blursize, const GColor& color);

	void SaveAsImageFile(LPCTSTR file_png_path, LPCTSTR fmt);
	static BOOL SaveAsJPG(LPCTSTR file_png_path, const unsigned char* data, int w, int h, XPixelFormat fmt, int stride);

  protected:
	int m_iWidth;
	int m_iHeight;
	UINT m_nBpp;
	int m_nStride;
	unsigned char* m_pBuffer;
	XPixelFormat m_pixelformat; // 像素格式
};

class UI_EXP IGIFHost
{
  public:
	IGIFHost()
	    : next(NULL)
	    , prev(NULL){};
	~IGIFHost(){};
	virtual void OnUpdataUI(){};
	virtual void OnUpdataAll(){};
	virtual void OnFreeObject(){};

  public:
	IGIFHost* next;
	IGIFHost* prev;
};

class UI_EXP GImageGIF : public GImage
{

  public:
	GImageGIF();
	virtual ~GImageGIF();

	bool LoadBufferImage(unsigned char* buffer, UINT dwSize) override;

	/* gif api*/
	int LayerCounts() const;
	int Delay(int l) const;
	int GetCurPos() const;

	void AddHost(IGIFHost* host);

  protected:
	void OnTimerGif();

  protected:
	int m_nLayers;
	int* m_nDelays;
	timer_handler* m_timer_;
	UINT m_nCurpos;

	IGIFHost m_head; // ui 列表
};

}
#endif
