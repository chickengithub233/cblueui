#ifndef CBLUEUI_COPTIONSTATE_BLXDY_INC_H_
#define CBLUEUI_COPTIONSTATE_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {


class UI_EXP CSelectState
{
  public:
	CSelectState(CControlUI* ui);
	~CSelectState();

	void SetSelected(BOOL bSelect, BOOL noTrigger = FALSE);
	BOOL IsSelected() const;
	void ShellSelectAttribute(const BeString& szName, const BeString& szText);

  protected:
	CControlUI* m_host_ui;     // 宿主ui
	SelectState m_selectState; // 选中状态
};



}
#endif