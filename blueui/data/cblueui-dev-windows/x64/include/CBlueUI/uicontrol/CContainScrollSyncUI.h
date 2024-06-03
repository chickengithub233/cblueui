#ifndef CBLUEUI_CSCROLLSYNCCONTAINUI_BLXDY_INC_H_
#define CBLUEUI_CSCROLLSYNCCONTAINUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CContainLayoutUI.h"

namespace BUI {

class UI_EXP CContainScrollSyncUI : public CContainLayoutUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CContainScrollSyncUI)
  public:
	CContainScrollSyncUI();
	~CContainScrollSyncUI();

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  private:
	BOOL OnIOSync(UINT message, WPARAM wParam, LPARAM lParam);

  private:
	BOOL m_bSyncing;
};


}

#endif
