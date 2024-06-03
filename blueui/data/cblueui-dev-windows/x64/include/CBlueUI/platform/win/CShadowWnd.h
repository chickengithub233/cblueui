#ifndef CBLUEUI_SHADOW_BYMD_INC_H_
#define CBLUEUI_SHADOW_BYMD_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"

enum ShadowStatus
{
	SS_ENABLED        = 1,      // Shadow is enabled, if not, the following one is always FALSE
	SS_VISABLE        = 1 << 1, // Shadow window is visible
	SS_PARENTVISIBLE  = 1 << 2, // Parent window is visible, if not, the above one is always FALSE
	SS_DISABLEDBYAERO = 1 << 3  // Shadow is enabled, but do not show because areo is enabled
};

LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class UI_EXP CShadowWnd
{
  public:
	CShadowWnd(void);

  public:
	virtual ~CShadowWnd(void);

	// protected:

	// Instance handle, used to register window class and create window
	static HINSTANCE s_hInstance;

	// Layered window APIs
	typedef BOOL(WINAPI* pfnUpdateLayeredWindow)(HWND hWnd, HDC hdcDst, POINT* pptDst, SIZE* psize, HDC hdcSrc, POINT* pptSrc, COLORREF crKey, BLENDFUNCTION* pblend, DWORD dwFlags);
	static pfnUpdateLayeredWindow s_UpdateLayeredWindow;

	// Vista compatibility APIs
	static BOOL s_bVista; // Whether running on Win Vista
	typedef HRESULT(WINAPI* pfnDwmIsCompositionEnabled)(BOOL* pfEnabled);
	static pfnDwmIsCompositionEnabled s_DwmIsCompositionEnabled;

	HWND m_hWnd;
	void* m_pThunk;
	HWND m_hParentWnd;
	LONG_PTR m_OriParentProc; // Original WndProc of parent window


	BYTE m_Status;

	unsigned char m_nDarkness;  // Darkness, transparency of blurred area
	unsigned char m_nSharpness; // Sharpness, width of blurred border of shadow window
	signed char m_nSize;        // Shadow window size, relative to parent window size

	// The X and Y offsets of shadow window,
	// relative to the parent window, at center of both windows (not top-left corner), signed
	signed char m_nxOffset;
	signed char m_nyOffset;

	// Restore last parent window size, used to determine the update strategy when parent window is resized
	LPARAM m_WndSize;

	// Set this to TRUE if the shadow should not be update until next WM_PAINT is received
	BOOL m_bUpdate;
	BOOL m_bAllfill;
	RECT m_rcHwnd; // shadow rect
	SIZE m_size;
	COLORREF m_Color; // Color of shadow

	// 程序接口 用户需要用到的函数
  public:
	// 全局初始化
	static BOOL Initialize(HINSTANCE hInstance);
	// 创建
	void Create(HWND hParentWnd);

	// 设置各种参数
	// 阴影边框的尺寸  ，效果的明显程度（越大越淡） 阴影的深度 位置信息，和颜色
	BOOL SetShowParm(int nShadowSize = 0, int nSharpness = 5, int nDarkness = 200, int nPosX = 5, int nPosY = 5, COLORREF color = 0x000000);

	// 设置全部填充
	void SetAllFill(BOOL bAll);
	void Update(HWND hParent);
	// Show or hide the shadow, depending on the enabled status stored in m_Status
	void Show(HWND hParent);

	void OnFinalMessage();

  protected:
	// static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	// Fill in the shadow window alpha blend bitmap with shadow image pixels
	void MakeShadow(UINT32* pShadBits, HWND hParent, RECT* rcParent);

	// Helper to calculate the alpha-premultiled valuefora pixel
	inline DWORD PreMultiply(COLORREF cl, unsigned char nAlpha)
	{
		// It's strange that the byte order of RGB in 32b BMP is reverse to in COLORREF
		return (GetRValue(cl) * (DWORD)nAlpha / 255) << 16 | (GetGValue(cl) * (DWORD)nAlpha / 255) << 8 | (GetBValue(cl) * (DWORD)nAlpha / 255);
	}
};


#endif
