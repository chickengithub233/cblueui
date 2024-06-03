#ifndef CBLUEUI_CHECKBOX_BLXDY_INC_H_
#define CBLUEUI_CHECKBOX_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "CControlUI.h"
#include "CBaseSelectState.h"

namespace BUI {

/**
 * @brief 复选框
 *
 */
class UI_EXP CCheckBoxUI : public CControlUI, public CSelectState
{
	DECLARE_DYNAMIC_OBJ_CLASS(CCheckBoxUI)
  private:
	GImageIconInfo* m_pImgCheck[3]; // 复选框绘制图标(依次:未知，选中，未选中)
	GImageIconInfo* m_pImageIcon;   // 控件图标
  public:
	CCheckBoxUI();
	~CCheckBoxUI();

	void SetCheckBoxImage(SelectState state, GImageIconInfo* img); ///< 设置复选框图片

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void Activate() override;
	void GetControlValueText(BasicStringBuffer& buffer) override;
	void SetControlValueText(const BeString& str) override;
	BOOL OnNcHitTest(POINT pt) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | selected <br/选中状态                      | true/false    |
	 * | cmd <br/命令                      | showcontrol(linechartPage,tab_bar_set,isSelect(btnchar01));  |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	/* override IControlUI menthos:*/
	int LayoutAdaptWidth(int expH) override;
};

class UI_EXP CBinaryBoxUI : public CCheckBoxUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CBinaryBoxUI)
  private:
	BeString m_strTrue;
	BeString m_strFalse;

  public:
	CBinaryBoxUI();
	~CBinaryBoxUI();

	BOOL SetCheckStateText(LPCTSTR strTrue = NULL, LPCTSTR strfalse = NULL); ///< 设置两种状态的显示文本

	void ChangeThemeColors(int theme) override;
	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | text <br/> 打开和关闭时的文本用分号隔开| text="On;Off" |
	 * | back-on-colors <br/> 打开时背景颜色| 同back-colors |
	 * | front-on-colors <br/> 打开时滑块颜色| 同front-colors |
	 * | text-on-colors <br/> 打开时文字颜色| 同text-colors |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintShadow(ISurface* pSurface, bool inset, RECT* lpUpdate) override;

	/* override IControlUI menthos:*/
	int LayoutAdaptWidth(int expH) override;
};


}


#endif