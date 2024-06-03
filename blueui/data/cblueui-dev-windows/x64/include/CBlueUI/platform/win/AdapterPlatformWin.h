#ifndef CBLUEUI_WINPLATFORMADAPTER_INC_H_
#define CBLUEUI_WINPLATFORMADAPTER_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "core/CCoreBasePro.h"
#include "core/CCoreObject.h"
#include "bufferDC.h"

namespace BUI {

class UI_EXP AdapterPlatformWin : public IAdapterPlatform
{
  public:
	AdapterPlatformWin();
	AdapterPlatformWin(IManageHandler* manager, HWND m_hWnd);
	virtual ~AdapterPlatformWin();

	BOOL InitAdapt(IManageHandler* manager, HWND hwnd);
	BOOL AttachHwnd(HWND hwnd);
	BOOL DestoryAdapter();                                          ///< 释放管理对象占用的资源
	BOOL TranslateMessage(UINT uMsg, WPARAM wParam, LPARAM lParam); ///< 消息转发

	void OnPaintWin(HDC hdc, RECT& rcClip);

	/* IAdapterPlatform methods: */
	UINT MessageLoop() override;
	BOOL IsZoomed() override;
	BOOL IsWindowVisible() override;
	BOOL SendMessage(UINT uMsg, WPARAM wParam = 0L, LPARAM lParam = 0L) override;
	BOOL PostMessage(UINT uMsg, WPARAM wParam = 0L, LPARAM lParam = 0L) override;
	BOOL OnPlatformHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void GetClientRect(RECT* rc) override;
	void GetWindowRect(RECT* rc) override;
	void SetActiveWindow() override;
	void EnableWindow(BOOL enable) override;
	void ShowWindow(UINT model) override;
	void MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint) override;
	void InvalidateRect(RECT* rc, BOOL bSyncUpdate = FALSE) override;
	void ClientPointToScreen(POINT* pt) override;
	void ScreenPointToClient(POINT* pt) override;
	void GetCursorGloablPos(POINT* pt) override;
	BOOL AnimateWindow(DWORD dwTime, DWORD dwFlags) override;

  private:
	BOOL DispatchMsg(UINT uMsg, UINT ui_msg, WPARAM wp, WPARAM lp);
	UINT GetKeyModifies() const;

	void OpenSystemFile(WPARAM wp);
	void OpenSystemFont(WPARAM wp);
	void OpenSystemColor(WPARAM wp);

	void CheckSizeOfBufferDC();

  public:
	HWND m_hWnd; // 关联的句柄

	MemDC m_bufferDC;
	HDC m_hdcBackGround; // 背景画布
	HDC m_hDCPaint;
	WNDPROC m_pWndProc; // 存放HWND的窗口过程
	COLORREF m_bgColor;
	UINT m_wstyle;    // 窗口风格
	BOOL m_isMainWnd; // 是否是主窗口，默认为TRUE

  private:
	void* m_pThunk;
	RECT m_rcStore;
	POINT m_ptCaretPos;
};

}

#endif
