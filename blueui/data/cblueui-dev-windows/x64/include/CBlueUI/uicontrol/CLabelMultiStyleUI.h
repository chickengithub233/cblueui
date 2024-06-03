#ifndef CBLUEUI_CLABELMULTISTYLEUI_BLXDY_INC_H_
#define CBLUEUI_CLABELMULTISTYLEUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CNodeDataHtml.h"

namespace BUI {

/**
 * @brief HTML风格的标签控件
 *
 */
class UI_EXP CLabelMultiStyleUI : public CControlUI, public CNodeHtmlTextData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CLabelMultiStyleUI)
  public:
	CLabelMultiStyleUI();
	~CLabelMultiStyleUI();

	void OnParseItemData(XMLItem* pNode) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | text-align <br/>文本对齐方式  | text-align="left,vcenter" 取值left,right,center,top,bottom,vcenter的组合  |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;

  protected:
	void OnRefreshHtml() override;
};



}

#endif