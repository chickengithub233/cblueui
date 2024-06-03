#ifndef CBLUEUI_CCOLORPICKERUI_BLXDY_INC_H_
#define CBLUEUI_CCOLORPICKERUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CEditTextUI.h"
#include "CNodeData.h"

namespace BUI {

/**
 * @brief 颜色拾取器
 *
 */
class UI_EXP CColorPickerUI : public CEditList, public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CColorPickerUI)
  private:
	float m_h;
	float m_s;
	float m_v;

	POINT m_ptTri[3]; // 三角形色域
	UINT m_cHit;

  public:
	CColorPickerUI();
	~CColorPickerUI();

	COLORREF GetColorValue();
	void SetColor(COLORREF color, bool refresh = true);
	void SetHSVColor(float h, float s, float v, bool refresh = true);

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | value <br/>设置当前颜色                      | value="0xFF00AC"       |
	 * |                                              | value="#AC00FF"       |
	 * |                                              | value="rgb(10,52,180)"       |
	 * |                                              | value="hsv(10,100,100,255)"       |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText);
	void OnCreate() override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL OnMouseMove(WPARAM wp, LPARAM lp) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

  private:
	UINT IsInAreaType(POINT pt);
	void GetColorRect(RECT& rc) const;
	void GetColorRadius(RECT& rc, int& r, int& r_ring) const;
	void CreateEditControl();
	void SetEditControlText();
	BOOL HitPointValue(POINT pt);
	BOOL HitPointTri(POINT pt);
	BOOL OnEditChange();
};





}

#endif