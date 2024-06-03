#ifndef CBLUEUI_CLAYOUTCONTAINUI_BLXDY_INC_H_
#define CBLUEUI_CLAYOUTCONTAINUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "CContainerUI.h"
#include "layout/CLayoutManager.h"

namespace BUI {

/**
 * @brief 有布局功能的容器类
 *
 */
class UI_EXP CContainLayoutUI : public CContainerUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CContainLayoutUI)
  protected:
	CLayoutBox m_layoutBox;

  public:
	CContainLayoutUI();
	~CContainLayoutUI();

	int GetZCurSel();
	void SetZCurSel(int index);

	CLayoutBox& GetBoxContainLayout();

	void OnShow(bool bShow) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | contain-layout <br/>容器布局信息  | 示例 contain-layout="box-type:horizontal;cursel:0;interval:5;padding:10,10,10,10"   |
	 * |                                 | box-type布局方式： horizontal :水平布局	vertical :垂直布局  Layered :层叠布局   |
	 * |                                 | cursel 当前布局索引 	    |
	 * |                                 | interval 布局元素之间的间隔		    |
	 * |                                 | padding 布局的边距		    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	void SetLayoutCurSel(int index);
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;
	ILayout* BoxLayoutMgr() override;
	void GetLayoutViewRect(RECT* rc) override;
};

/**
 * @brief 有布局功能的移动特效容器类
 *
 */
class UI_EXP CAutoMoveContainUI : public CContainLayoutUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CAutoMoveContainUI)
  private:
	timer_handler* m_uMoveTimer;
	int m_MoveStep;
	int m_timerSpeed;

  public:
	CAutoMoveContainUI();
	~CAutoMoveContainUI();

	void SetMoveStep(int step);
	void SetTimerSpace(int ms);

	void OnCreate() override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  private:
	void OnTimerMoveEvent();
};

/**
 * @brief 带箭头风格，有布局功能的容器类
 *
 */
class UI_EXP CLayoutArrowContainUI : public CContainLayoutUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CLayoutArrowContainUI)
  public:
	CLayoutArrowContainUI();
	~CLayoutArrowContainUI();

	void SetArrowAlign(UINT align);
	void SetArrowSize(int size);

	void GetLayoutViewRect(RECT* rc) override;

	BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate) override;

	void CloneAttribute(CControlUI* clone) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	UINT m_ArrowFlag; // 箭头方向
	int m_nArrowSize; // 箭头大小
};

/**
 * @brief 文本提示器
 *
 */
class UI_EXP CTipBoxUI : public CLayoutArrowContainUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CTipBoxUI)
  public:
	CTipBoxUI();
	~CTipBoxUI();

	void PopTips(LPCTSTR szTipText, int x, int y);

	void ChangeThemeColors(int theme) override;
	void OnCreate() override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;

  private:
	CControlUI* m_tips_ui;
};

}

#endif
