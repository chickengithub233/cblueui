#include "00_uidemo.h"

UidemoHandler::UidemoHandler(IManageHandler* pM)
    : CManagerHandler(pM)
    , m_isNeedDestory(FALSE)
{
	m_pkeysdfsfd = NULL;
	m_plabversion = NULL;
	m_pbuild_time = NULL;
	m_pminbtn = NULL;
	m_pmaxbtn = NULL;
	m_pclosebtn = NULL;
	m_pswitch_lang = NULL;
	m_pinput_theme = NULL;
	m_pinput_script = NULL;
	m_pbtnRunScriptTest = NULL;
	m_psilder_gaosi = NULL;
	m_pmacdeskui = NULL;
	m_pmaindisplay = NULL;
}

UidemoHandler::~UidemoHandler()
{
	if (m_isNeedDestory == FALSE)
		return;
	SAFEDEL(m_pkeysdfsfd);
	SAFEDEL(m_plabversion);
	SAFEDEL(m_pbuild_time);
	SAFEDEL(m_pminbtn);
	SAFEDEL(m_pmaxbtn);
	SAFEDEL(m_pclosebtn);
	SAFEDEL(m_pswitch_lang);
	SAFEDEL(m_pinput_theme);
	SAFEDEL(m_pinput_script);
	SAFEDEL(m_pbtnRunScriptTest);
	SAFEDEL(m_psilder_gaosi);
	SAFEDEL(m_pmacdeskui);
	SAFEDEL(m_pmaindisplay);
}

void UidemoHandler::InitUI(BOOL isNeedDestory)
{
	m_isNeedDestory = isNeedDestory;
	IManageHandler* pManger = GetUIManager();
	if (pManger == NULL)
		return;
	BIND_CTL_VARIABLE_BY_NAME(pManger, CContainLayoutUI, m_pkeysdfsfd, _T("keysdfsfd"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CLabelUI, m_plabversion, _T("labversion"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CLabelUI, m_pbuild_time, _T("build_time"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CButtonSysUI, m_pminbtn, _T("minbtn"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CButtonSysUI, m_pmaxbtn, _T("maxbtn"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CButtonSysUI, m_pclosebtn, _T("closebtn"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CComboListUI, m_pswitch_lang, _T("switch_lang"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CComboListUI, m_pinput_theme, _T("input_theme"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CComboListUI, m_pinput_script, _T("input_script"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CButtonUI, m_pbtnRunScriptTest, _T("btnRunScriptTest")); // tr:自动化应用
	BIND_CTL_VARIABLE_BY_NAME(pManger, CSliderUI, m_psilder_gaosi, _T("silder_gaosi"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CListBoxUI, m_pmacdeskui, _T("macdeskui"));
	BIND_CTL_VARIABLE_BY_NAME(pManger, CContainTabUI, m_pmaindisplay, _T("maindisplay"));
}

BOOL UidemoHandler::OnMessageHandler(UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
		case MSG_BIND_UI:
			InitUI();
			break;
		default:
			break;
	}
	return FALSE;
}
