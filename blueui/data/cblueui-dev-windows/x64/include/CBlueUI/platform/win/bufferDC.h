#ifndef CBLUEUI_GDI_MEMDC_BYMD_INC_H_
#define CBLUEUI_GDI_MEMDC_BYMD_INC_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"

/**
 * @brief HDC裁剪类。用于对HDC的视窗进行限制
 *
 */
class UI_EXP RenderClip
{
  private:
	HDC m_hDC;
	HRGN m_hRgn;
	HRGN m_hOldRgn;

  public:
	RenderClip();
	~RenderClip();

	/**
	 * @brief 矩形裁剪
	 *
	 * @param hDC 设备
	 * @param rc  可见区域
	 */
	void GenerateClip(HDC hDC, RECT rc);

	/**
	 * @brief 圆角裁剪
	 *
	 * @param hDC     设备
	 * @param rcItem  可见区域
	 * @param width   圆角宽度
	 * @param height  圆角高度
	 */
	void GenerateRoundClip(HDC hDC, RECT rcItem, int width, int height);

	/**
	 * @brief 释放裁剪限制
	 *
	 */
	void ReleaseClip();
};

/**
 * @brief 内存HDC类(离屏DC)
 *
 */
class UI_EXP MemDC
{
  public:
	MemDC();
	~MemDC();

	/**
	 * @brief 创建内存DC
	 *
	 * @param hdc 源设备
	 * @param rc  源区域
	 * @param bpp 像素格式位深度
	 * @param byAlpha  画布的透明度 透明(0)~不透明(255)
	 * @param bCopyBits 是否拷贝 hdc 中的画面到内存HDC中
	 */
	MemDC(HDC hdc, RECT rc, int bpp = 24, unsigned char byAlpha = 0xff, BOOL bCopyBits = TRUE, int scan_bottom = 1);

	/**
	 * @brief 创建内存DC
	 *
	 * @param hdc 源设备
	 * @param rc  源区域
	 * @param lpblnit 是否拷贝 hdc 中的画面到内存HDC中
	 * @param bpp 像素格式位深度
	 * @param byAlpha  画布的透明度 透明(0)~不透明(255)

	 */
	bool CreateMemDCWithPixels(HDC hdc, RECT rc, void* lpblnit, int bpp = 24, unsigned char byAlpha = 0xff, int scan_bottom = 1);

	bool CreateMemDC(HDC hdc, RECT rc, int bpp = 24, unsigned char byAlpha = 0xff, BOOL bCopyBits = TRUE, int scan_bottom = 1);

	/**
	 * @brief 更新画面的亮度
	 *
	 * @param nlight 亮度值 0 ~ 255。 0 is light， 255 is dark
	 */
	void SetBrightness(int nlight);

	/**
	 * @brief 用透明的方式投影到目标hdc上
	 *
	 */
	void AlphaBit();

	void Release();

	int Width();
	int Height();
	int Left();
	int Top();

	int Stride();
	int BitPixel();

	void InitializeGL();

	static BOOL InitializeGLFunctions(HWND hwnd, HDC hdc);

  private:
	MemDC(const MemDC&);
	MemDC& operator=(const MemDC&);
	// 创建一个设备无关的位图 pBits指向数据位
	HBITMAP CreateDIBHBitmap(HDC hdc, int cx, int cy, void** pBits, int scan_bottom);

	void DeInitializeGL();

  public:
	HDC m_hdc;     // 与原DC
	HDC m_hMemDC;  // 创建的兼容内存DC
	char* m_pBits; // 位图数据 从上到下，从左到右 ， BGRA 的排列
	HGLRC m_hRC;   // WGL资源句柄
	BITMAPINFO bi;

  private:
	HBITMAP m_hBmp;     // 位图
	HBITMAP m_hBmpOld;  // 位图
	int m_nScanlineLen; // 扫描线字节数
	RECT m_rcDst;       // 表示m_hMemDC对应m_hDC中的区域，也就是绘制完成后需要将图像拷贝输出的区域
	BOOL m_bCopyBits;   // 代表是否将原DC的背景拷贝回来
	int m_bpp;
	unsigned char m_nAlpha; // 输出到原DC的透明度
};




#endif
