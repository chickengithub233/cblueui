/****************************************************************************
 *
 * 虚拟窗口类
 *
 * BUI窗口控件，并不是windows那种含有窗口句柄的窗口。是我们ui架构中自我实现的类似窗口的一个容器控件
 * 可以实现自动UI布局，和拖拽，调整大小，自动适应滚动范围
 ****************************************************************************/

#ifndef CBLUEUI_VIRWINDOWS_BLXDY_INC_H_
#define CBLUEUI_VIRWINDOWS_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "CNodeData.h"

namespace BUI {

enum DragMode
{
	DragAnywhere, ///< 无论何时都可以拖拽
	DragCaption,  ///< 仅当标题栏可以拖拽
	DragDisable   ///< 不可拖拽
};

enum ContainerFlag
{
	Contain_mainContain      = 1 << 0,  ///< 主容器
	Contain_showCaption      = 1 << 1,  ///< 是否显示标题栏，标题栏具有双击展开，显示文本的功能
	Contain_UpdateView       = 1 << 2,  ///< 更新视窗滚动范围
	Contain_EnableChangeSize = 1 << 3,  ///< 是否可以从右下角调整自身大小
	Contain_IsZoom           = 1 << 4,  ///< 是否最小化
	Contain_EnableZoom       = 1 << 5,  ///< 最大最小化功能是否可用
	Contain_ShowCloseBtn     = 1 << 6,  ///< 展示关闭按钮
	Contain_ShowScrollBar    = 1 << 7,  ///< 是否显示滚动条
	Contain_DragMoveWidget   = 1 << 8,  ///< 鼠标按下拖动窗口标识
	Contain_bkImgFullFill    = 1 << 9,  ///< 背景图片全覆盖填充
	Contain_ShowGridStandard = 1 << 10, ///< 显示水平垂直的标准化网格线
	Contain_ShowGridBlock    = 1 << 11, ///< 显示网格间隔填充模式
	Contain_GroupLineStyle   = 1 << 12, ///< 静态分组线样式
	Contain_HideAfterDelay   = 1 << 13, ///< 在一段延时之后隐藏自己
};

/**
 * @brief 无布局功能的容器类,控件的位置全靠用户的绝对位置来确定。改变控件位置，需要开发者控制。
 *
 */
class UI_EXP CContainerUI : public CScrollAreaUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CContainerUI)
  protected:
	COLORSTYLE m_titleBkColors;   // 标题栏背景颜色风格
	COLORSTYLE m_titleTextColors; // 标题栏文本颜色风格
	COLORSTYLE m_gridColors;      // 网格线颜色风格
	int m_grid_line_spacing;      // 网格线间距
	RECT m_rcZoom;                // 最小化记录原先的位置信息
	UINT m_nCaptionHeight;        // 标题栏高度
	UINT m_uModel;                // 模态标志，0-非模态 1- 模态
	UINT m_uHit;
	UINT m_uHitClick;
	DragMode m_dragMode;
	SIZE m_minSize;             // 窗口最小尺寸
	SIZE m_maxSize;             // 窗口最大尺寸
	SIZE m_szText;              // 文本尺寸
	UINT m_containFlags;        // ContainerFlag
	GImageIconInfo* m_pBkImage; // 背景图片
	MouseState m_closeState;    // 关闭按钮区域的鼠标状态监视

	CBrushGradientSet m_bkGradientBru;      // 背景渐变画刷
	CBrushGradientSet m_bkTitleGradientBru; // 标题背景渐变画刷

	CTimerTask m_timer_hide_delay;

	// int border_gradient_size;                //边框阴影尺寸
  public:
	CContainerUI();
	~CContainerUI();

	/**
	 * @brief 设置容器控件特有属性标志
	 *
	 * @param style 取@link ContainerFlag @endlink组合值
	 * @param op  ADD_FLAGS(添加属性) REMOVE_FLAGS(删除属性)
	 */
	void ModifyContainerFlags(UINT style, UINT op = ADD_FLAGS);
	UINT IsHasContainerFlags(UINT flags) const;

	void UpdateHideDelayMs(int ms); // 更新自动隐藏延时

	void SetBkImage(GImageIconInfo* img);
	SIZE GetChildMaxViewSize() const; ///< 获得所有子控件的可见范围
	void SetCaptionHeight(int h);
	void SetDragType(DragMode type);
	UINT DoModal(int nMesc = 0);

	void ChangeThemeColors(int theme) override;
	void OnControlSize() override;

	BOOL OnNcHitTest(POINT pt) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;

	BOOL OnVSCrollBar(WPARAM wParam, LPARAM lParam) override;
	BOOL OnHSCrollBar(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | back-image <br/>背景填充图        | back-image="资源标识符"	    |
	 * | contain-flags<br/>容器功能标志位   |	"-"前缀代表删除属性<br/>如 contain-flags="showCaption,-EnableZoom"		  |
	 * |                                 | MainContain :主容器和普通容器应用的主题色不同 	    |
	 * |                                 | showCaption :是否展示title标题栏	    |
	 * |                                 | EnableChangeSize :用户无法调整容器尺寸	    |
	 * |                                 | EnableZoom :是否显示最大最小化按钮	    |
	 * |                                 | ShowCloseBtn :是否显示关闭按钮	    |
	 * |                                 | DragMoveWidget : 窗口移动	    |
	 * |                                 | bkImgFullFill : 背景图是否铺满	    |
	 * |                                 | ShowGridStandard : 显示水平垂直的标准化网格线	    |
	 * |                                 | ShowGridBlock : 显示网格间隔填充模式	    |
	 * |                                 | GroupLineStyle: 静态分组线样式 |
	 * |                                 | HideAfterDelay：在一段延时之后隐藏自己|
	 * |                                 | 	    |
	 * | drag <br/>控件拖拽移动属性         | none :不移动	    |
	 * |                                 | title :拖拽标题栏时移动	    |
	 * |                                 | anywhere :拖拽任意位置移动	    |
	 * |                                 | 	    |
	 * | back-gradient <br/>背景渐变色                      | back-gradient="normal:资源标识符;light:资源标识符;selected:资源标识符;disable:资源标识符"	    |
	 * | back-gradient-normal <br/>背景常规状态渐变色        | back-gradient-normal="资源标识符"	    |
	 * | back-gradient-light <br/>背景高亮状态渐变色         | back-gradient-light="资源标识符"		    |
	 * | back-gradient-selected <br/>背景选中状态渐变色      | back-gradient-selected="资源标识符"		    |
	 * | back-gradient-disable <br/>背景禁用渐变色           | back-gradient-disable="资源标识符"		    |
	 * |          | 	    |
	 * | title-gradient <br/>标题栏渐变色                      | title-gradient="normal:资源标识符;light:资源标识符;selected:资源标识符;disable:资源标识符"	    |
	 * | title-gradient-normal <br/>背景常规状态渐变色        | title-gradient-normal="资源标识符"	    |
	 * | title-gradient-light <br/>背景高亮状态渐变色         | title-gradient-light="资源标识符"		    |
	 * | title-gradient-selected <br/>背景选中状态渐变色      | title-gradient-selected="资源标识符"		    |
	 * | title-gradient-disable <br/>背景禁用渐变色           | title-gradient-disable="资源标识符"		    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	void Zoomed();
	void DragMove(POINT pt);
	void OnChangeChildsPos();
	void GetCloseRect(RECT* rc);
	UINT HitTestType(POINT point);
};

/**
 * @brief NodeData容器
 *
 */
class UI_EXP CNodeDataListUI : public CContainerUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataListUI)
  public:
	CNodeDataListUI();
	~CNodeDataListUI();

	CNodeDataLists* GetNodeDataList();
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void OnParseItemData(XMLItem* pNode) override;

  protected:
	CNodeDataLists m_nodeList;
};



}
#endif
