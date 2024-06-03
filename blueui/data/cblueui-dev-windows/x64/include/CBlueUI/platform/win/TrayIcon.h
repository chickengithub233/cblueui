#ifndef CBLUEUI_TRAYICON_BYMD_INC_H_
#define CBLUEUI_TRAYICON_BYMD_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _MSC_VER

#include <windows.h>
#include <shellapi.h>

#endif

#include "core/CCoreBasePro.h"

namespace BUI {

class UI_EXP CTrayIcon
{
  private:
	NOTIFYICONDATA m_trayData;
	HWND m_hWnd;
	UINT m_uMessage;
	HICON m_hIcon;
	bool m_bEnabled;
	bool m_bVisible;

  public:
	CTrayIcon(void);
	~CTrayIcon(void);

  public:
	void CreateTrayIcon(HWND _RecvHwnd, UINT _IconIDResource, LPCTSTR _ToolTipText = NULL, UINT _Message = NULL);
	void DeleteTrayIcon();
	bool SetTooltipText(LPCTSTR _ToolTipText);
	bool SetTooltipText(UINT _IDResource);

	bool SetIcon(HICON _Hicon);
	bool SetIcon(LPCTSTR _IconFile);
	bool SetIcon(UINT _IDResource);
	HICON GetIcon() const;
	void SetHideIcon();
	void SetShowIcon();
	void RemoveIcon();

	bool Enabled() { return m_bEnabled; };

	bool IsVisible() { return !m_bVisible; };
};

}

#endif
