#ifndef CBLUEUI_CKEYBOARDEDITUI_BLXDY_INC_H_
#define CBLUEUI_CKEYBOARDEDITUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CControlUI.h"
#include "CEditTextUI.h"

namespace BUI {

/**
 * @brief 快捷键输入框
 *
 */
class UI_EXP CEditKeyBoardUI : public CEditTextUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CEditKeyBoardUI)
  private:
	UINT m_vInputKeyCtrl; // 快捷键控制码
	UINT m_vInputKeyCode; // 快捷键码
  public:
	CEditKeyBoardUI();
	~CEditKeyBoardUI();

	UINT KeyCtrl() const;
	UINT KeyCode() const;
	void SetKeyBoard(const TCHAR* text);

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnChar(WPARAM wParam, LPARAM lParam) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};


}

#endif
