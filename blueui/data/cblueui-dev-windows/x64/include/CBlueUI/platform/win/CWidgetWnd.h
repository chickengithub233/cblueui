#ifndef CBLUEUI_WINDOWS_INC_H_
#define CBLUEUI_WINDOWS_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WINSOCKAPI_
#include <Windows.h>
#include <CommCtrl.h>

#include "core/CCoreBasePro.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "DragDropImpl.h"


#define UI_WNDSTYLE_CONTAINER (0)
#define UI_WNDSTYLE_FRAME     (WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN) ///< 主框架
#define UI_WNDSTYLE_CHILD     (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS)            ///< 子窗口
#define UI_WNDSTYLE_DIALOG    (WS_VISIBLE | WS_POPUP)                              ///< 弹出框

#define UI_WNDSTYLE_EX_FRAME  (WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

/**
 * @brief CWidgetWnd 窗口 SDK封装 比CWnd要更快更小巧
 *
 */
class UI_EXP CWidgetWnd
{
	DECLARE_DYNAMIC_OBJ_CLASS_BASE(CWidgetWnd)
  public:
	HWND m_hWnd;
	BeString m_varName; ///< 窗口的变量标识，根据这个字符标识，可以查询到窗口对象
	CIDropTarget* m_pDropTarget;
	void* m_pThunk;     ///< Thunk技术
	SIZE m_szMinWindow; ///< 窗口最小尺寸
	UINT m_nExitCode;
	UINT m_nHitTest; ///< 当前的hitest值
	WNDPROC m_pfnSuperWindowProc;
	bool m_bMouseTrack;
	bool m_bHitTest;  ///< 是否可以调整大小
	bool m_bDragMove; ///< 是否可以拖拽移动
	COLORREF m_bgColor;

  public:
	CWidgetWnd(void);
	virtual ~CWidgetWnd(void);
	void EnableAdjust(bool bHittest); ///< 禁用窗口拉伸功能

	/**
	 * @brief 创建一个主框架风格的窗口
	 */
	HWND CreateFrame(LPCTSTR pstrWndName, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	HWND CreateFrame(LPCTSTR pstrWndName, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);


	/**
	 * @brief 创建一个自定义风格的窗口
	 */
	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);

	operator HWND() const { return m_hWnd; } ///< 类型转换

	void CenterWindow(); ///< 居中显示

	void ShowWindow(BOOL bVisable); ///< 非模态显示

	void SetTitle(LPCTSTR title); ///< 设置标题
	void SetOpacity(BYTE nOpacity);
	void SetBgColor(COLORREF color);
	void EnableWindow(BOOL bEnable);
	void EnableDragMove(BOOL bEnable);
	void SetIcon(UINT nRes); ///< 设置图标
	void SetVarName(LPCTSTR lpVarName);
	UINT DoModal(); ///< 模态显示
	void EndDialog(UINT uRetCode);
	void OnOK();
	void OnCancel();
	void EnableDragDrop(bool bDropEnable);
	void ShowTaskbarIcon(bool bShow); ///< 是否在任务栏图标(不是托盘图标哦)
	void Close(UINT nRet = IDOK);

	void SetMinSize(int cx, int cy); ///< 设置窗口大小最小尺寸
	virtual void OnInitWindows();    ///< 创建完成后调用

	virtual LPCTSTR GetWndClassName(); ///< 返回注册窗口类的名

	LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0L, LPARAM lParam = 0L); ///< 消息发送接口
	LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0L, LPARAM lParam = 0L);

	virtual BOOL DefWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnMessage(UINT message, WPARAM wParam, LPARAM lParam, LPCTSTR szName);
	virtual void OnFinalMessage();

	virtual LRESULT OnLButtonDown(WPARAM wParam = 0L, LPARAM lParam = 0L);
	virtual LRESULT OnLButtonUp(WPARAM wParam = 0L, LPARAM lParam = 0L);

	virtual LRESULT OnRButtonDown(WPARAM wParam = 0L, LPARAM lParam = 0L);

	virtual LRESULT OnRButtonUp(WPARAM wParam = 0L, LPARAM lParam = 0L);

	virtual LRESULT OnMouseMove(WPARAM wParam = 0L, LPARAM lParam = 0L);

	virtual LRESULT OnMouseLeave(WPARAM wParam = 0L, LPARAM lParam = 0L);

	virtual LRESULT OnKeyDown(WPARAM wParam = 0L, LPARAM lParam = 0L);
	virtual LRESULT OnKeyUp(WPARAM wParam = 0L, LPARAM lParam = 0L);
	virtual LRESULT OnChar(WPARAM wParam = 0L, LPARAM lParam = 0L);
	virtual void OnPaint(HDC hdc, RECT* inVaildRect);

	virtual LRESULT OnPaintBackGround(HDC hdc, RECT* lprcPaint);

	virtual LRESULT OnSize(WPARAM wParam = 0L, LPARAM lParam = 0L);
	virtual LRESULT OnNcHitTest(WPARAM wParam = 0L, LPARAM lParam = 0L);

	virtual bool OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD* pdwEffect);

  private:
	bool RegisterWindowClass();

	UINT HitTest(POINT pt);
};

/**
 * @brief 弹出式透明层级窗口
 *
 */
class UI_EXP CLayeredWnd : public CWidgetWnd
{
	DECLARE_DYNAMIC_OBJ_CLASS(CLayeredWnd)
  private:
	HFONT m_hFont;
	HFONT m_hFontDefault;
	BeString m_str;

  public:
	CLayeredWnd(void);
	~CLayeredWnd(void);
	BOOL DefWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND CreateLayeredWnd(RECT rcPostion);

	void UpadateWnd(int nAlpha = 200);
	/// Fill in the shadow window alpha blend bitmap with shadow image pixels
	void MakeShadow(UINT32* pShadBits, RECT* rcParent, COLORREF color, int ndark);

	/// Helper to calculate the alpha-premultiled valuefora pixel
	inline DWORD PreMultiply(COLORREF cl, unsigned char nAlpha)
	{
		// It's strange that the byte order of RGB in 32b BMP is reverse to in COLORREF
		return (GetRValue(cl) * (DWORD)nAlpha / 255) << 16 | (GetGValue(cl) * (DWORD)nAlpha / 255) << 8 | (GetBValue(cl) * (DWORD)nAlpha / 255);
	}
};

extern "C" UI_EXP CWidgetWnd* CreateWidgetWindow(const TCHAR* className, LPCTSTR ctlName, LPCTSTR text, HWND hwnd, RECT rc, UINT nstyle);






#endif