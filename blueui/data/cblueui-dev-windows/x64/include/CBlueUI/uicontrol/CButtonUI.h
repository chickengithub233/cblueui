#ifndef CBLUEUI_BUTTON_BLXDY_INC_H_
#define CBLUEUI_BUTTON_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CLabelUI.h"
#include "CBaseSelectState.h"
#include "CNodeCell.h"
#include "CNodeData.h"
#include "graphics/GImageIconInfo.h"
#include "graphics/GPathStorage.h"

class GPathStorageSVG;

namespace BUI {

enum ButtonStyle
{
	TextButton, ///< 文本风格
	IconButton  ///< 图标风格
};

/**
 * @brief 按钮
 *
 */
class UI_EXP CButtonUI : public CLabelUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonUI)
  protected:
	SIZE m_szTextDown; // 文本按下偏移量
  public:
	CButtonUI();
	~CButtonUI();

	void SetButtonStyle(ButtonStyle style);
	void SetTextOffsetWhenMouseDown(int dx, int dy); ///< 设置鼠标在按下状态时，文本的偏移量

	void ChangeThemeColors(int theme) override;
	void OnCreate() override;
	void Activate() override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam) override;

	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;
	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | offset-click <br/>点击文本和图表偏移量                      | offset-click="10,10"       |
	 * | click <br/>触发按钮事件                      | 任意值       |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};

/**
 * @brief 系统按钮
 *
 */
class UI_EXP CButtonSysUI : public CButtonUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonSysUI)
  public:
	CButtonSysUI();
	~CButtonSysUI();

	void SetSysButtonType(CmdEventType btnType);

	void ChangeThemeColors(int theme) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate) override;

	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | sysType <br/>系统按钮类型                      | sysType="close" <br/>退出按钮       |
	 * |                                              | sysType="max"  <br/>最大化按钮      |
	 * |                                              | sysType="fullscreen"  <br/>全屏    |
	 * |                                              | sysType="min" <br/>最小化按钮       |
	 * |                                              | sysType="remove"  <br/>删除        |
	 * |                                              | sysType="hide"  <br/>隐藏式关闭     |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  private:
	void drawSysButton(ISurface* pSurface, RECT rect);     ///< 绘制系统按钮
	void drawCloseButton(ISurface* pSurface, RECT rect);   ///< 绘制关闭按钮
	void drawMinSizeButton(ISurface* pSurface, RECT rect); ///< 绘制最小化按钮
	void drawMaxSizeButton(ISurface* pSurface, RECT rect); ///< 绘制最小化按钮
  private:
	UINT m_uSysType;
};

/**
 * @brief 菜单按钮
 *
 */
class UI_EXP CButtonMenuUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonMenuUI)
  private:
	UINT_PTR m_uCmdID;
	UINT m_uFlags;
	int m_nIicoWidth;
	BOOL m_bIsSubPopWnd; // 标识子菜单是实体窗口句柄，还是抽象的ui类型控件
	BeString m_textid;
	GImageIconInfo* m_icon;

  public:
	CButtonMenuUI();
	~CButtonMenuUI();

	UINT CheckMenuItem(UINT nCheck);

	BOOL MenuInfo(UINT nFlags, UINT_PTR nID, LPCTSTR lpszTextID = NULL, GImageIconInfo* const icon = NULL);

	void CloneAttribute(CControlUI* clone) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void OnCtrlKillFocus() override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | image <br/>图标                      | image="标识符或者路径"    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  private:
	void darwCheckFlag(ISurface* pSurface, RECT rc, COLORREF color);
	void showPopMenu(CControlUI* pPopUI, bool bShow);
	void showParentPopMenu(bool bShow);
};

/**
 * @brief SVG图标按钮
 *
 */
class UI_EXP CButtonSVGUI : public CButtonUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonSVGUI)
  private:
	GPathStorageSVG* m_svgPath;

  public:
	CButtonSVGUI();
	~CButtonSVGUI();

	void CloneAttribute(CControlUI* clone) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | image <br/>图标                      | image="SVG标识符或者路径"    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;
};

/**
 * @brief 切图按钮(普通，高亮，选中，禁用四种状态)横排和竖排皆可，顺序打乱也可以。
 *        结合实际开发经验，开发和美工属于不同的部门，虽然两个部门都有规范，但是人员流动带来的变动导致规范无法成型。此类支持美工任意切图。
 */
class UI_EXP CButtonImageUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonImageUI)
  public:
	CButtonImageUI();
	~CButtonImageUI();

	void CloneAttribute(CControlUI* clone) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | icon <br/>图标                      | icon="SVG标识符或者路径"    |
	 * | scale <br/>图标缩放比例                      | scale="0.5,0.5"    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;

  protected:
	GImageIconInfo* m_iconInfo;
	double m_scale_x;
	double m_scale_y;
};

/**
 * @brief 开关按钮控件，支持两种状态
 *
 */
class UI_EXP CButtonSwitchImageUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonSwitchImageUI)
  protected:
	BOOL m_bSelected;
	GImageIconInfo* m_sw_icon[2];

  public:
	CButtonSwitchImageUI();
	~CButtonSwitchImageUI();

	BOOL GetCheck();            // 获得Check状态  true 表示选中
	void SetCheck(BOOL bCheck); // 设置Check状态

	void CloneAttribute(CControlUI* clone) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | selected <br/选中状态                      | true/false    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;
};

/**
 * @brief 渐变按钮
 *
 */
class UI_EXP CButtonGradientUI : public CButtonUI, public CBrushGradientSet
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonGradientUI)
  public:
	CButtonGradientUI();
	~CButtonGradientUI();

	void CloneAttribute(CControlUI* clone) override;
	BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | back-gradient <br/>背景渐变色                      | back-gradient="normal:资源标识符;light:资源标识符;selected:资源标识符;disable:资源标识符"	    |
	 * | back-gradient-normal <br/>背景常规状态渐变色        | back-gradient-normal="资源标识符"	    |
	 * | back-gradient-light <br/>背景高亮状态渐变色         | back-gradient-light="资源标识符"		    |
	 * | back-gradient-selected <br/>背景选中状态渐变色      | back-gradient-selected="资源标识符"		    |
	 * | back-gradient-disable <br/>背景禁用渐变色           | back-gradient-disable="资源标识符"		    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};

/**
 * @brief 正多边形按钮，支持渐变
 *
 */
class UI_EXP CButtonPolygonUI : public CButtonGradientUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonPolygonUI)
  public:
	CButtonPolygonUI();
	~CButtonPolygonUI();

	void SetEdgeCount(int count);   ///< 设置边数量
	void SetAngleStart(int offset); ///< 设置旋转起始角度

	void OnControlSize() override;
	BOOL HitTest(POINT pt) override;
	BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintShadow(ISurface* pSurface, bool inset, RECT* lpUpdate) override;
	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | edge-count <br/>边数量                      | edge-count="6" 正6边形	    |
	 * | angle-start <br/>顶点起始角度         | angle-start="120" [0-360] 	    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  private:
	int m_edge_count;  // 边数量
	int m_angle_start; // 顶点起始角度
	GPathStorage m_path_storage;
};

/**
 * @brief 纹理按钮，支持渐变，和纹理图案
 *
 */
class UI_EXP CButtonTextureUI : public CButtonGradientUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonTextureUI)
  public:
	CButtonTextureUI();
	~CButtonTextureUI();

	BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate) override;
	BOOL DoPaintShadow(ISurface* pSurface, bool inset,  RECT* lpUpdate) override;

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | edge-count <br/>边数量                      | edge-count="6" 正6边形	    |
	 * | angle-start <br/>顶点起始角度         | angle-start="120" [0-360] 	    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;

  private:
	GPathStorage m_path_storage;
};

/**
 * @brief 组合复杂的按钮
 *
 */
class UI_EXP CButtonNodeUI : public CButtonUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CButtonNodeUI)
  public:
	CButtonNodeUI();
	~CButtonNodeUI();

	CNodeDataLists* GetNodeDataList();
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void OnParseItemData(XMLItem* pNode) override;
	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | node-layout <br/>边数量                      | node-layout="x"	    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	CNodeDataLists m_nodeList;
};




}
#endif