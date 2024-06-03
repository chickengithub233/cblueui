#ifndef CBLUEUI_COPTIONCONTAINUI_BLXDY_INC_H_
#define CBLUEUI_COPTIONCONTAINUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CContainLayoutUI.h"
#include "CButtonUI.h"

namespace BUI {

class UI_EXP COptionUI : public CButtonNodeUI, public CSelectState
{
	DECLARE_DYNAMIC_OBJ_CLASS(COptionUI)
  public:
	COptionUI();
	~COptionUI();

	void ChangeThemeColors(int theme) override;
	void OnCreate() override;
	void OnShow(bool bShow) override;
	void Activate() override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintShadow(ISurface* pSurface, bool inset,  RECT* lpUpdate) override;
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	void GetControlValueText(BasicStringBuffer& buffer) override;

  protected:
	int m_dir; // 标签页方向
};

// 单选容器，每次收到MSG_OPTION_CHANGED 消息会向其它控件发送取消选中消息
class UI_EXP CContainOptionUI : public CContainLayoutUI, public CSelectState
{
	DECLARE_DYNAMIC_OBJ_CLASS(CContainOptionUI)
  public:
	CContainOptionUI();
	~CContainOptionUI();

	void ShellAttribute(const BeString& szName, const BeString& szText);
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;

  private:
	BOOL m_bSyncing;
	std::vector<CControlUI*> m_option_uis;
};


}

#endif
