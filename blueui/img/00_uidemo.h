#ifndef UIVIEW_UIDEMOHANDLER_INC_H_
#define UIVIEW_UIDEMOHANDLER_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBlueUI.h"

/* UidemoHandler Event handler. */
class UidemoHandler : public CManagerHandler
{
  public:
	UidemoHandler(IManageHandler* pM);
	virtual ~UidemoHandler();

	void InitUI(BOOL isNeedDestory = FALSE);
	BOOL OnMessageHandler(UINT message, WPARAM wp, LPARAM lp) override;

  protected:
	/* All named ui controls */
	BOOL m_isNeedDestory;
	CContainLayoutUI* m_pkeysdfsfd;
	CLabelUI* m_plabversion;
	CLabelUI* m_pbuild_time;
	CButtonSysUI* m_pminbtn;
	CButtonSysUI* m_pmaxbtn;
	CButtonSysUI* m_pclosebtn;
	CComboListUI* m_pswitch_lang;
	CComboListUI* m_pinput_theme;
	CComboListUI* m_pinput_script;
	CButtonUI* m_pbtnRunScriptTest; // tr:自动化应用
	CSliderUI* m_psilder_gaosi;
	CListBoxUI* m_pmacdeskui;
	CContainTabUI* m_pmaindisplay;
};

#endif
