#ifndef CBLUEUI_CSTEPNUMEDIT_BLXDY_INC_H_
#define CBLUEUI_CSTEPNUMEDIT_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CEditTextUI.h"

namespace BUI {

enum EditSpinBtnSide
{
	LeftSide,  ///< 操作按钮在左侧
	RightSide, ///< 操作按钮在右侧
	BothSide   ///< 操作按钮在两侧
};

/**
 * @brief 步长输入框
 *
 */
class UI_EXP CEditSpinBoxUI : public CEditTextUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CEditSpinBoxUI)
  private:
	double m_fPerStep;
	int m_spinSize;
	UINT m_nHitArea;
	timer_handler* m_timer_add_id;
	DWORD m_DownTick;
	EditSpinBtnSide m_btnSide; // 操作按钮位置
  public:
	CEditSpinBoxUI();
	~CEditSpinBoxUI();

	void DoRollBack(); // 执行回滚动作(C++重写覆盖函数)

	void UpdateNumberBit(int bit, BOOL add); ///< 更新某一位数值
	BOOL SetEditSpinBtnSide(EditSpinBtnSide side);

	void SetControlValueText(const BeString& str) override;
	void OnControlSize() override;
	BOOL OnNcHitTest(POINT pt) override;

	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyUp(WPARAM wParam, LPARAM lParam) override;
	void CloneAttribute(CControlUI* clone) override;



	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | edit-step <br/>数值步长  | edit-step="0.01"	或者 edit-step="5"    |
	 * | editbtnside <br/>编辑按钮风格  | editbtnside="LeftSide"  BothSide   |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	/*CEditLineStyle override methods:*/
	void OnCheckContext() override;

  private:
	void GetIncreRect(RECT* rc);
	void GetDecreRect(RECT* rc);
	void OnTimerNumberEvent();
};

}

#endif