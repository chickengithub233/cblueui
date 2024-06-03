#ifndef CBLUEUI_CSCROLLBAR_BLXDY_INC_H_
#define CBLUEUI_CSCROLLBAR_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CNodeData.h"

namespace BUI {

typedef struct
{
	RECT rcLbtn;    ///< 上部按钮
	RECT rcLChanel; ///< 上部通道
	RECT rcThumb;   ///< 滑块
	RECT rcRChanel; ///< 下部通道
	RECT rcRbtn;    ///< 下部按钮
} ScrollRect;

/**
 * @brief 滚动条
 *
 */
class UI_EXP CScrollBarUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CScrollBarUI)
  private:
	ScrollRect m_SbarRect; // 滚动条组件的区域
	SCROLLINFO m_SbarInfo;
	POINT m_ScrollPoint;
	UINT m_SBarDrawStyle;     // 滚动条的显示风格
	UINT m_nBar;              // SBF_VERT 或者 SBF_HORZ
	int m_nArrowSize;         // 滚动条按钮的尺寸
	int m_nThumbMinSize;      // 滚动条滑块的尺寸
	UINT m_bRectType;         // 用一个字节的几位表示鼠标位置  0x01左箭头  0x02拇指  0x04右通道  0x08左通道按下 0x10拇指按下  0x20右通道按下 0x00无状态
	bool m_bAutoAdjustPage;   // 当为TRUE：根据自身尺寸调整滚动页的大小，实现智能
	bool m_bInterScroll;      // 内建滚动条，标志着控件和父控件的生命周期相同。不可单独强制释放
	bool m_bShowArrow;        // 是否展示箭头
	bool m_bflipY;            // 翻转
	bool m_bSmallWhenNoHover; // 非焦点状态时，以缩小比例方式显示
  public:
	CScrollBarUI();
	~CScrollBarUI();

	void ChangeThemeColors(int theme) override;
	void OnCreate() override;
	void OnControlSize() override;
	void OnShow(bool bShow) override;
	void SetScrollInner(bool bInner);

	void SetAutoAdjustPage(bool bAdjust);
	void SetScrollType(UINT nType); // nType = SBF_HORZ Or SBF_VERT

	void SetSmallWhenNoFocus(bool bSmall); // 非焦点状态时，以缩小比例方式显示

	void Flip(bool bflip);
	BOOL IsValid() const;            // true代表滚动条是可以滚动的
	BOOL IsValidNoCheckPage() const; // true代表滚动参数有效（不检查page参数的有效性）

	BOOL SetScrollPosEnd();      // 设置滚动位置到末尾
	BOOL IsScrollPosEnd() const; // 是否到达最大位置

	int GetScrollPos();
	BOOL SetScrollPos(int nNewPos, BOOL bRedraw = TRUE); // 设置和获取滚动位置
	BOOL SetScrollPosWithPercentage(int percent);        // 设置位置百分比.定义域[0,100]
	int GetPercentage() const;                           // 获得百分比.值域[0,100]

	BOOL SetScrollRange(int nMinPos, int nMaxPos); // 设置范围
	BOOL SetScrollPage(int nPage);                 // 设置页大小
	int GetScrollPage() const;

	UINT GetScrollMaxValue(); // 获得最大值
	UINT GetScrollDistance(); // 游标的活动行程距离
	BOOL UpdataSBarRect();    // 更新滚动个区域的位置
	void SetArrowSize(int nArrowSize = 17);
	bool ShowPageArrowButton(bool bShow); // 设置箭头可见性


	CControlUI* HitTestControl(POINT pt) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | orientation <br/>滚动条类型   |horizontal :水平, vertical :垂直  |
	 * | draw-style <br/>滑块风格     | rect :矩形, rd : 圆角矩形 	    |
	 * | arrow-size <br/>箭头区域尺寸大小         | arrow-size="17"	    |
	 * | scroll-pos-percent <br/>设置滚动位置百分比        | scroll-pos-percent="50" 50%		    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	BOOL OnNcHitTest(POINT pt) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wp, LPARAM lp) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
};

// 滚动条控件
class UI_EXP CScrollAreaUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CScrollAreaUI)
  protected:
	int m_nWheelSpeed;
	int m_nBarWidth;
	CScrollBarUI* m_pScrollHor;
	CScrollBarUI* m_pScrollVer;
	AlignmentStyle m_uHorBarAlign;
	AlignmentStyle m_uVerBarAlign;
	BOOL m_bForbidHor;                            // 禁用水平滚动 true is ban
	BOOL m_bForbidVer;                            // 禁用垂坠滚动
	BOOL m_bDisplayBarWhenMouseEnters;            // TRUE:表示当鼠标进入区域才显示, FALSE:表示一直展示
	CNodeDataLists m_nodeListWhenEmpty;           // 列表为空时显示内容
	std::vector<COLORREF> m_back_interval_colors; // 背景行间隔颜色映射表
  public:
	CScrollAreaUI();
	virtual ~CScrollAreaUI();
	void OnCreate() override;
	void OnControlSize() override;
	void GetLayoutViewRect(RECT* rc) override; // 获得可视区域的位置信息

	void SetBackIntervalColor(std::vector<COLORREF>& colors); // 设置背景网格间隔颜色表

	void ResetScrollBarRange();
	void ScrollJumpToView(RECT& rc); // 让rc处于可见范围内

	void RefreshClientRect(RECT rc);
	void ScreenToClientPoint(POINT& pt) const;
	void SetScrollBarUISize(int size);

	void SetEmptyTipImage(GImageIconInfo* img);
	void SetEmptyTipText(BeString text);

	int GetScrollbarPos(UINT nBar = SBF_HORZ) const;
	void SetScrollbarPos(UINT nBar, int pos);

	void SetScrollbarRange(UINT nBar, int nMin, int nMax);
	int GetScrollbarRange(UINT nBar = SBF_HORZ) const;
	int GetScrollDistance(UINT nBar = SBF_HORZ) const;

	int GetScrollbarPage(UINT nBar = SBF_HORZ) const;

	BOOL IsScrollVaild(UINT nBar = SBF_HORZ) const;

	void SetScrollbarPosWithPercentage(UINT nBar, int percent);
	int GetScrollbarPercentage(UINT nBar = SBF_HORZ) const;
	void SetScrollbarPosEnd(UINT nBar = SBF_HORZ);
	CScrollBarUI* GetScrollbarUI(UINT nBar = SBF_HORZ) const;

	void EnableScrollBarAutoHide(BOOL enable);
	void ForbidScrollBar(UINT nBar, BOOL bBan);
	void SetScrollbarAlign(UINT nBar, AlignmentStyle uAlign);
	void UpdateScrollBarPostion(RECT* lpRect);
	void SetWheelSpeed(UINT speed); // 设置滑动速度


	void DoPaintEmptyTips(ISurface* pSurface, RECT& rcPaint, RECT* lpUpdate);

	void ChangeThemeColors(int theme) override;
	void OnParseItemData(XMLItem* pNode) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseWheel(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseEnter(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnHSCrollBar(WPARAM wParam, LPARAM lParam) override;
	BOOL OnVSCrollBar(WPARAM wParam, LPARAM lParam) override;
	void CloneAttribute(CControlUI* clone) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	void ShowChildScrollBar(BOOL show);
	UINT GetScrollStateCode() const; // 获取状态码
};



}
#endif