#ifndef CBLUEUI_PLATFORMDEF_BYMD_INC_H_
#define CBLUEUI_PLATFORMDEF_BYMD_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <memory>

#include "CWidgetWnd.h"
#include "CShadowWnd.h"
#include "CWidgetOverlayWnd.h"
#include "TrayIcon.h"
#include "CGDIGraphics.h"
#include "AdapterPlatformWin.h"

namespace BUI {

class UI_EXP WindowPlatform
{
  public:
	WindowPlatform();
	~WindowPlatform();

	void CreatePlatform(WindowPlatform* parent, LPCTSTR title, UINT style, RECT rc);
	std::shared_ptr<IAdapterPlatform> CreateAapter(IManageHandler* manager, BOOL isMain = TRUE);

	void CenterWindow();
	UINT DoModal();
	BOOL IsShow() const;

  public:
	CWidgetWnd wnd_;
};


}



#endif