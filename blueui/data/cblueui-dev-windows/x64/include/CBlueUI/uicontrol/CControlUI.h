/**********************************************************************************
CBlueUI library.
Copyright (C) 2015  CBlueUI Studio<2842004379@qq.com>

Declaration
All rights reserved.
China

This software is released under the "CBlueUI License" (hereinafter referred to as the "License").
You may only use and distribute this software in accordance with the terms and conditions of the License.
Please make sure that you have read, understood, and accepted all the provisions of the License before using this software.
If you do not agree with any provisions of the License, you are not authorized to use this software.

This software is provided "as is" without any warranty, expressed or implied.
The author and copyright owner expressly disclaim any warranties, including but not limited to the implied warranties
of merchantability, fitness for a particular purpose, and non-infringement. In no event shall the author or copyright owner
be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to,
procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and
on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in
any way out of the use of this software, even if advised of the possibility of such damage.

For further details about the License, please refer to the license document.

声明：
保留所有权利
中国
本软件是根据CBlueUI许可证（下称“协议”）发布的，您只能在符合协议规定的条件下使用和分发本软件。
请确保在使用本软件之前，您已阅读、理解并接受协议的所有条款和条件。如果您不同意协议的任何规定，您将无权使用本软件。

本软件在不作任何明示或暗示的情况下，以“原样”提供。作者和版权所有者明确声明不提供任何形式的明示或暗示保证，包括但不限于
对该软件的适用性、适销性或特定用途的适用性的暗示保证。在任何情况下，作者和版权所有者对于使用本软件所导致的任何直接、间接、
附带的或特殊的损失或责任不承担任何责任。

如需详细了解协议的内容，请参考协议文档。

**********************************************************************************/
#ifndef CBLUEUI_CCONTROL_INC_H_
#define CBLUEUI_CCONTROL_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory>

#include "core/CCoreBasePro.h"
#include "core/CCoreObject.h"
#include "core/CTimerWheel.h"
#include "core/CCoreEventHandler.h"
#include "cstring/StringShort.h"
#include "function/MarkupItem.h"
#include "function/CSkinInfo.h"
#include "function/SettingInfo.h"
#include "function/Loggerdebug.h"
#include "function/MarkupItem.h"
#include "graphics/GColor.h"
#include "graphics/GSurface.h"
#include "graphics/GShadowContain.h"
#include "graphics/GImageIconInfo.h"

#include "syntax/syntax.common.bind.h"

namespace BUI {


/// 控件属性标志位
enum ControlFlag : uint64_t
{
	ControlFlag_StaticState                = 1ULL << 0,  ///< 设置控件进入静默状态.静默状态和禁用状态一样，不会响应消息
	ControlFlag_AllowFocusWhenClick        = 1ULL << 1,  ///< 用户左键允许获得键盘焦点
	ControlFlag_AllowCaptureMouseWhenClick = 1ULL << 2,  ///< 用户左键允许捕捉鼠标焦点
	ControlFlag_MouseHoverState            = 1ULL << 3,  ///< 鼠标是否悬停在控件内
	ControlFlag_FocusState                 = 1ULL << 4,  ///< 控件已经获得焦点
	ControlFlag_ContainFocusState          = 1ULL << 5,  ///< 开启容器焦点状态，默认不开启
	ControlFlag_MouseLButtonDownState      = 1ULL << 6,  ///< 鼠标左键按下
	ControlFlag_MouseHitTestReset          = 1ULL << 7,  ///< 鼠标命中被重置，需要重新计算
	ControlFlag_AutoScrollHorEnd           = 1ULL << 8,  ///< 水平滚动条自动滚动到最后
	ControlFlag_AutoScrollVerEnd           = 1ULL << 9,  ///< 垂直滚动条自动滚动到最后
	ControlFlag_Animating                  = 1ULL << 10, ///< 正在动画显示
	ControlFlag_UseClipZoom                = 1ULL << 11, ///< 使用用户限制视区.内部使用，不可设置
	ControlFlag_NoDrawClip                 = 1ULL << 12, ///< 禁用裁减
	ControlFlag_Delegater                  = 1ULL << 13, ///< 开启托管ui
	ControlFlag_DelegaterLinkState         = 1ULL << 14, ///< 是否已被加入到托管链表中
	ControlFlag_SupportTabKey              = 1ULL << 15, ///< 支持tab键
	ControlFlag_FixedInView                = 1ULL << 16, ///< 当控件位置变化时，是否将父控件的m_ptViewOrigin参与计算，也就是当为true时 固定到视区下，如滚动条控件
	ControlFlag_OnlyMoveInParent           = 1ULL << 17, ///< 仅在父控件视窗边界下移动
	ControlFlag_ZOverSpeedup               = 1ULL << 18, ///< 开启order覆盖过滤，提高速度.开启之后，如果控件被兄弟节点遮盖，将不会进行多余的绘制图形操作。
	ControlFlag_AutoSeatLayout             = 1ULL << 19, ///< 控件占位标志，为true代表控件可视状态变化时，布局位置不改变。为false代表，其他控件补位
	ControlFlag_ShowMarginOnCaptureMouse   = 1ULL << 20, ///< 显示外边距，当捕获鼠标时
	ControlFlag_ShowMarginOnFocus          = 1ULL << 21, ///< 显示外边距，当捕获焦点时
	ControlFlag_MarginState                = 1ULL << 22, ///< 外边距显示状态，内部使用，不可设置
	ControlFlag_MoveDraggingState          = 1ULL << 23, ///< 拖拽状态标志位
	ControlFlag_InterScrollState           = 1ULL << 24, ///< 内建滚动条，标志着控件和父控件的生命周期相同。不可单独强制释放
	ControlFlag_StorageUserSetting         = 1ULL << 25, ///< 存储用户的配置信息
	ControlFlag_RoundRadiusDrawLine        = 1ULL << 26, ///< 圆角以线条方式，非弧形过度
	ControlFlag_RoundRadiusParl            = 1ULL << 27, ///< 圆角以偏移方式，非弧形过度
	ControlFlag_HideWndWhenClick           = 1ULL << 28, ///< 当click up时，隐藏窗口
	ControlFlag_HideWhenLeave              = 1ULL << 29, ///< 当鼠标离开时时，隐藏控件
	ControlFlag_HideWhenCommited           = 1ULL << 30, ///< 在提交完成后自动隐藏控件
	ControlFlag_HideWhenFocusLost          = 1ULL << 31, ///< 在失去焦点后自动隐藏控件

	ControlFlag_TabKeyFocus               = 1ULL << 32, ///< tab focus
	ControlFlag_ForceLayoutWhenSizeChange = 1ULL << 33, ///< 在理想情况下。控件大小不变时，包含的子布局也不变。但是在特殊情况时，有时子布局的可见性由外部变量的状态决定
	                                                    ///< ForceLayout参数在窗口不变时，同样触发重新布局的事件
	ControlFlag_UseParentTextColor       = 1ULL << 34,  ///< 使用父控件的文本颜色
	ControlFlag_UseParentForegroundColor = 1ULL << 35,  ///< 使用父控件的前景颜色
	ControlFlag_UseParentBorderColor     = 1ULL << 36,  ///< 使用父控件的边框颜色
	ControlFlag_DisableTheme             = 1ULL << 37,  ///< 当主题变化时，控件颜色值不更新，由开发者决定，目的是为了保持切换主题时，一些不变的元素
	ControlFlag_TextChanged              = 1ULL << 38,  ///< 文本被改变标志位
	ControlFlag_FontChanged              = 1ULL << 39,  ///< 字体被改变标志位

	ControlFlag_PopupProperties    = 1ULL << 40, ///< 具有弹出属性，管理者根据此属性，自动管理弹出控件的焦点
	ControlFlag_DoNotTriggerEvents = 1ULL << 41, ///< 不触发绑定的动作事件
};

/**
 * @brief 控件基类
 *
 */
class UI_EXP CControlUI : public ICommitTarget, public IControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS_BASE(CControlUI)

  public:
	BeString m_strVarName; // 控件标识名
	UINT m_nID;            // 当ID为0 时，控件只改变自己的状态，只发送特定的消息, 保持与微软一样的使用规则

	IManageHandler* m_pMangerUI; // 管理类
	CControlUI* m_pParent;       // 父节点
	CControlUI* m_pFirstChild;   // 第一个孩子节点
	CControlUI* m_pLastChild;    // 最后的孩子节点
	CControlUI* m_pNextSibling;  // 下一个兄弟节点
	CControlUI* m_pPrevSibling;  // 上一个兄弟节点

	CControlUI* m_gc_prev_; // 垃圾回收链表
	CControlUI* m_gc_next_;

	CControlUI* m_break_prev_; // 托管UI链表
	CControlUI* m_break_next_;
	RECT m_rcAbsolute; // 在实际窗口下的绝对位置(代表控件的实际位置和尺寸)
  protected:
	IEventHandler* m_eventHandler; // 消息响应委托对象
	BeString m_strText;            // 控件的文本
	BeString m_skinModuleName;     // 皮肤大类别
	BeString m_skinStyleName;      // 皮肤小类别
	BeString m_strCaptureFile;     // 截图保存位置
	Location m_locationinfo;       // 控件在父控件中的相对位置信息 Location Info
	POINT m_ptViewOrigin;          // 控件视窗下的左上角原点位置偏移量。默认为（0，0）

	RECT m_rcTrackDrag; // 控件拖拽开始时的绝对位置
	RECT m_rcChipZoom;  // 控件的可视区域, 小于或等于父控件的尺寸 m_rcChipZoom <= m_pParent->m_rcAbsolute

	COLORSTYLE m_bgColors;   // 背景风格(background)
	COLORSTYLE m_fgColors;   // 前景风格(foreground),前景指画面中的内容和边框。文本是一种特殊的前景风格，所以独立出来
	COLORSTYLE m_textColors; // 文本风格
	COLORSTYLE m_borderColors;

	RoundRectRadius m_RoundRadius; // 边框圆角尺寸
	UBYTE m_roundRadiusFlags;      // 圆角标志是否为百分比，刚好8Bit，0:像素值，1:百分比,从左上角开始顺时针0~7
	MarginInfo m_marginOnHover;    // 热点状态时外边距，用于突出控件的热点状态，提升交互体验
	CursorMouse m_idCursor;        // 光标ID

	GFont* m_pFont;       // 控件context字体
	uint64_t m_nCtlFlags; // 控制和状态参数

	UINT m_borderSize; // 边框宽度

	ICommitTarget* m_commit_target;            // 数据提交对象
	FourCode m_draw_style;                     // 控件绘制样式。比如复选框有单选和多选样式。滚动条的圆角还是矩形风格等。用此字段设置
	BeString m_popTipText;                     // 弹出提示文本
	std::shared_ptr<CControlUI> m_popBoxUI;    // pop of ui
	std::shared_ptr<PopControlInfo> m_popUser; // pop of attribute
	ActionList m_action;                       // 事件绑定机制对象

	std::vector<std::shared_ptr<ILayout>> m_absord_uis; // 粘连布局列表，实现吸附功能
	ST_Policy m_sigPolicy;                              // 信号管理策略
	syntax_info* m_cmd_ast;                             // 自定义协议脚本格式语法树

	XMLItem* m_save_node; // 属性保存节点，也可以是数据同步节点

	BeString m_strMinAdapter; // 最小显示的文本占位符
	ILayout* m_pCtrlOfLayout; // 管理控件本身的布局对象

	GShadowContain m_shadow_contain; // 阴影特效容器(包含内外阴影)

	UBYTE m_vKeyCtrl; // 快捷键控制码
	UBYTE m_vKeyCode; // 快捷键码
	UBYTE m_uHitFlag; // 调整命中标记

	/**
	 * @brief 全部为0代表可见
	 *        bit0: 表示控件自身的可视状态
	 *        bit1: 表示父控件的可视状态
	 *        bit2: 表示鼠标进入时才有可视状态
	 */
	UBYTE m_uVisible;

	/**
	 * @brief 全部为0代表可用
	 *        bit0 表示控件自身的可用状态
	 *        bit1 表示父控件的禁用状态
	 *        bit2: nodecell禁用状态
	 */
	UBYTE m_uEnable;

	/**
	 * @brief ShowModel
	 *        OnNever 从不绘制
	 *        OnAlways 一直绘制
	 *        OnHighLight 高亮时绘制
	 */
	UBYTE m_bkShowTiming;
	UBYTE m_borderShowTiming;

  private:
	CControlUI(const CControlUI&);
	CControlUI& operator=(const CControlUI&);

  public:
	CControlUI();
	virtual ~CControlUI();

	/**
	 * @brief 创建虚拟控件:创建过程中，会将控件加入到全局的垃圾管理机制中。用于在程序退出时，释放内存
	 *
	 * @param pManger 管理对象 不能为空对象
	 * @param strObjName 控件的检索标识符号，可用来查找控件
	 * @param strText 控件文本内容
	 * @param style   控件风格
	 * @param rc      位置信息
	 * @param parent  父控件指针
	 * @param nID     整型检索ID
	 * @return BOOL   TRUE 创建成功 FALSE创建失败
	 */
	BOOL Create(IManageHandler* pManger, LPCTSTR strObjName, LPCTSTR strText, DWORD style, RECT rc, CControlUI* parent = NULL, UINT nID = 0);
	BOOL Create(IManageHandler* pManger, LPCTSTR strObjName, LPCTSTR strText, DWORD style, int x, int y, int cx, int cy, CControlUI* pPar = NULL, UINT nID = 0);


	/**
	 * @brief 插入子控件
	 *
	 * @param pNewChild 待插入的子控件UI
	 * @param ppRev  子控件的上一个兄弟节点
	 */
	void InsertChild(CControlUI* pNewChild, CControlUI* pPrev);
	BOOL RemoveChild(CControlUI* pChild);

	BOOL SendParentMessage(UINT message, WPARAM wParam, LPARAM lParam) const;
	BOOL SendToManager(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
	void SendToAllChilds(UINT message, WPARAM wParam, LPARAM lParam); ///< 将消息传递给每一个子控件响应
	void SetEventHandler(IEventHandler* hander);                      ///< 设置消息托管

	void SetParent(CControlUI* pParent); ///< 设置父控件
	CControlUI* Parent() const;          ///< 父控件
	CControlUI* FirstChild() const;      ///< 第一个孩子节点
	CControlUI* LastChild() const;       ///< 最后的孩子节点
	CControlUI* NextSibling() const;     ///< 下一个兄弟节点
	CControlUI* PrevSibling() const;     ///< 上一个兄弟节点
	CControlUI* DelegaterPrev() const;   ///< 托管链表前向指针
	CControlUI* DelegaterNext() const;   ///< 托管链表后向指针



	/**
	 * @brief 设置控件风格
	 *
	 * @param style 取@link ControlFlag @endlink组合值
	 * @param op  ADD_FLAGS(添加属性) REMOVE_FLAGS(删除属性)
	 */
	void ModifyControlFlags(uint64_t style, UINT op = ADD_FLAGS);
	uint64_t IsHasControlFlags(uint64_t flags) const;
	uint64_t GetControlFlags() const;

	LPCTSTR Text() const;
	void SetControlText(BeString str, BOOL bRefresh = FALSE); ///< 设置文本

	void SetAdaptMinText(BeString str); ///< 布局最小适应文本

	void SetVarName(const BeString& str);
	void SetVarNameA(const char* varname);
	void SetVarNameW(const WCHAR* varname);

	void SetCommitTarget(ICommitTarget* obj); ///< 设置数据提交对象

	void AddAbsordLayout(std::shared_ptr<ILayout> layout);
	void DelAbsordLayout(std::shared_ptr<ILayout> layout);

	/// 获取颜色外观
	COLORSTYLE GetControlColorsStyle(ColorSceneType type);
	/// 设置颜色外观
	void SetControlColorsStyle(ColorSceneType type, COLORSTYLE colors);

	void SetAttributeSaveNode(XMLItem* node); ///< 设置属性保存节点
	XMLItem* GetAttributeSaveNode() const;    ///< 获得属性保存节点
	void DoSaveAttributeToNode();             ///< 保存控件属性到(SetSaveNode(node))注册的节点

	void SetBorderRoundFlags(int pos, int flags);
	void SetBorderRoundSize(RoundRectRadius& radius);
	void GetRoundRadius(RoundRectRadius& ra) const;

	/// 获得阴影容器对象
	GShadowContain& GetShadowContain();

	GFont* GetFont() const;
	void SetFont(GFont* font);     ///< 设置字体
	void SetFontSize(int nHeight); ///< 设置字体大小
	void SetBorderSize(UINT size);
	void SetPositionX(int x);
	void SetPositionY(int y);
	void SetPositionXY(int x, int y);
	int SaveAsImage(LPCTSTR outpng);     ///< 保存控件图像为png
	int SaveAsLongImage(LPCTSTR outpng); ///< 保存为长图
	int Width() const;
	void SetWidth(int w);

	int Height() const;
	void SetHeight(int h);

	void BindAction(std::shared_ptr<IActionNotify> notify);
	void TriggerAction();

	void SetCaptureCtl(); ///< 捕获鼠标
	void ReleaseCaptureCtl();

	void BreakAwayUITree();                       ///< 脱离父控件树
	void SetClipZoom(int x, int y, int w, int h); ///< 设置控件可视裁剪区域。约束控件的显示区域

	BOOL BringBottomMost();                           ///< 将控件移动到所有兄弟控件中的第一个
	BOOL BringTopMost();                              ///< 将控件移动到所有兄弟控件中的最后一个
	BOOL TestOrder() const;                           ///< 判断是否被其他控件遮盖 TRUE 代表遮盖
	void TipTrack(int x, int y, LPCTSTR lpSz = NULL); ///< 提示框显示位置 x, y 是相对窗口
	void TipHide();

	void ShowControl(bool bShow, bool notify_layout = true); ///< 显示虚拟窗口
	void SetVisibleWhenMouseHover(BOOL open);                ///< 设置只在鼠标悬停时，显示控件
	BOOL IsVisible() const;                                  ///< 控件在父控件中的显示状态
	BOOL IsFocused() const;                                  ///< 焦点状态

	void EnableControl(bool bEnable, bool refresh = true);         ///< TRUE:启用控件. FALSE:禁用控件
	void EnableNodeFlagControl(bool bEnable, bool refresh = true); ///< nodedata包含的控件。表示node是否被禁用
	BOOL IsEnabled() const;                                        ///< TRUE 代表可用

	BOOL IsBkShowTiming() const;
	void SetBkShowTiming(ShowModel mode);     ///< 背景绘制时机
	void SetBorderShowTiming(ShowModel mode); ///< 边框绘制时机

	BOOL IsCreateSucceed() const; ///< 是否是成功的对象 true创建成功
	BOOL IsShortCutVaild();
	void EnableShortCut(bool benable);
	void SetShortCut(int vKey);
	void SetShortCutCtrlCode(UBYTE vKey);
	BOOL DoShortCut(UBYTE ctrl, UBYTE vKey);

	void EnableBorderAdjustFlag(UINT alignborder = ALIGN_LEFT, bool bEnable = true); ///< 设置边框调整使能
	void SetToolTipText(LPCTSTR lpszTip);                                            ///< 设置提示文本
	void SetToolTipText(BeString strTip);

	void SetPopTipUI(std::shared_ptr<CControlUI> popui, std::shared_ptr<PopControlInfo> popinfo); ///< 设置弹出pop显示ui

	void PopTipUI(BOOL bShow); ///<  展示pop状态

	BOOL HitTestPopUI(POINT pt); ///< 是否命中弹出控件

	void GetRectInScreen(LPRECT lpRect); ///< 获得在HWND中的绝对位置
	void SetControlMouseCursor(CursorMouse id);

	void SetFocus();           ///< 取得焦点 和HWND焦点不要混淆 ，这是不一样的东西，只是函数名称我为了好记住
	void Scroll(int x, int y); ///< 视区的坐标原点偏移

	void Refresh(BOOL bSynch = FALSE);   ///< 窗口失效重绘
	void RefreshThreadSafe();            ///< 在gui线程之外时调安全的刷新函数
	void RefreshRect(RECT* lprcUpdate);  ///< 窗口失效重绘
	void GetDragPos(RECT* lprect) const; ///< 窗口拖拽的原始位置

	void OnDestory(); ///< 控件销毁

	void UpdateAdaptLayout() const; ///< 更新adapt布局


	BOOL MoveControl(RECT rect, BOOL bRepaint = TRUE);
	BOOL MoveControl(int x, int y, int w, int h, BOOL bRepaint = TRUE); ///< 移动控件位置。(x,y)代表父控件坐标空间值
	void MoveDragControl(int dx, int dy, BOOL bRepaint = TRUE);         ///< 拖拽移动。（dx，dy）移动距离向量

	/**
	 * @brief  将控件移动到以(xScale, yScale)百分比的中心点
	 *
	 * @param  rcView 视区位置信息
	 * @param  xScale yScale 控件中心坐标
	 * @param  w h 控件尺寸，为0时保持当前大小
	 * @param  bRepaint 需要刷新重绘
	 */
	void MoveCenterByPercent(RECT* rcView, float xScale = 0.5, float yScale = 0.5, int w = 0, int h = 0, BOOL bRepaint = TRUE);

	void ResetLayoutChilds(UINT flags = 0); ///< 重置子布局

	void SetSkinModule(BeString& skinGroup); ///< 设置皮肤id
	void SetSkinStyle(BeString& skinName);   ///< 设置皮肤id



	/**
	 * @brief  设置控件绘制的风格样式，同一种控件的表现样式可以有多种。
	 * 输入值只有前四位字符有效。一个控件表现形式在实际中不会很多。不用整形的目的是增强可读性
	 *
	 * @param  draw_style 类型由四个ASCII字符的组合。
	 */
	void SetDrawStyleWithFourCode(LPCTSTR draw_style);
	BOOL IsDrawStyleWithFourCode(TCHAR a = '\0', TCHAR b = '\0', TCHAR c = '\0', TCHAR d = '\0') const;

	void GetSkinModule(BeStringShort64& moduleName);
	void GetSkinStyle(BeStringShort64& styleName);
	RECT GetControlRect() const;
	RECT GetControlClientRect() const; ///<  返回基于客户区的坐标
	RECT GetControlScreenRect() const; ///<  返回基于屏幕的坐标

	RECT GetOppositePosition(RECT rcContainer, RECT rcChild) const; ///< 返回rcChild相对rcrcContainer坐标系的位置
	SIZE GetStringSize(LPCTSTR str) const;                          ///< 获得字符串尺寸
	POINT ViewOrigin() const;                                       ///< 坐标原点偏移量
	ILayout* GetAttchLayout() const;                                ///< 获得管理控件自身的布局对象
	ShowStatus GetPaintStatus(bool ignoreLButton = true) const;     ///< 获得控件状态
	POINT GetClientPoint(double w_percent, double h_percent);       ///< 获得控件坐标系下百分比的绝对位置

	void InsertGCChain(CControlUI* prev, CControlUI* next);
	void DeleteGCChain(CControlUI* prev, CControlUI* next);

	// void  InsertKeyTabChain(CControlUI* prev, CControlUI* next);
	// void  DeleteKeyTabChain(CControlUI* prev, CControlUI* next);

	CControlUI* FindTabFocusControl(BOOL isNext) const; ///< 获得接下来的焦点控件

	void NotifyMangerIsDestory(); ///< 告知管理者已销毁

	IManageHandler* GetManagerUI() const;
	ST_Policy* GetSignalPolicy();

	BOOL TranslateSyncMsg(UINT message, WPARAM wParam, LPARAM lParam);          ///< 向上层转发同步消息
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override; ///< 虚拟控件最终消息处理过程

	/**
	 * @brief  查找(通过控件的SetEventHandler()指定的事件处理对象来寻找)
	 *
	 * @param  handler
	 * @param  vec
	 * @return int
	 */
	int FindChildControlByHandler(IEventHandler* handler, std::vector<CControlUI*>& vec);

	/**
	 * @brief  在当前控件之下查找所有同名控件
	 *
	 * @param  szName
	 * @param  vec
	 * @param  isRecursiveCall 是否递归（包含递归的子控件）
	 * @return int 控件个数
	 */
	int FindAllControlByName(LPCTSTR szName, std::vector<CControlUI*>& vec, BOOL isRecursiveCall = TRUE) const;

	/// 在当前控件之下查找控件
	CControlUI* FindControlByName(LPCTSTR szName, BOOL isRecursiveCall = TRUE) const;

	CControlUI* GetParent() const;          ///< 获得父窗口
	CControlUI* GetParentOnTopMost() const; ///< 获得最顶层父窗口

	CControlUI* HitTestChildControl(POINT pt) const; ///< 定位到子控件对象

	CControlUI* NextFocusControl(BOOL isPrev = FALSE) const;

	void SaveSettingConfig(); ///< 保存配置
	/* virtual menthos:*/
	virtual CControlUI* HitTestControl(POINT pt); ///< 根据位置得到最终的定位控件 <table><tr><td>Value 1 </td> <td>Description 1 </td> </tr><tr><td>Value 2 </td> <td>Description 2 </td> </tr></table>
	virtual void GetLayoutViewRect(RECT* rc);
	virtual BeString GetControlText();
	virtual void GetControlValueText(BasicStringBuffer& buffer); ///< 获得控件所表达的数据的文本，比如复选框的状态("0"/"1"),方便上层统一操作

	virtual void SetControlValueText(const BeString& str); ///< 设置控件所表达的数据的文本，比如复选框的状态("0"/"1"),方便上层统一操作
	virtual ILayout* BoxLayoutMgr();                       ///< 容器布局对象
	virtual void Activate();
	virtual CControlUI* Clone();               ///< 克隆对象
	virtual void ChangeThemeColors(int theme); ///< 切换主题色


	/**
	 * @brief 命令控制和属性设置接口
	 *
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | text <br/>设置控件文本                      | text="按钮"       |
	 * | back-colors        <br/> 背景颜色            | back-colors="normal:0x343434;light:rgb(20,20,20,255);selected:hsv(25,100,100,255);disable:#343434"		  |
	 * | front-colors       <br/> 前景颜色            | front-colors="normal:0x343434;light:rgb(20,20,20,255);selected:hsv(25,100,100,255);disable:#343434"		  |
	 * | text-colors        <br/> 文本颜色            | text-colors="normal:0x343434;light:rgb(20,20,20,255);selected:hsv(25,100,100,255);disable:#343434"		  |
	 * | border-colors      <br/> 边框颜色            | border-colors="normal:0x343434;light:rgb(20,20,20,255);selected:hsv(25,100,100,255);disable:#343434"					  |
	 * | border-size       <br/> 边框画笔大小         | border-size="2"				  |
	 * | round-radius      <br/> 控件圆角            | round-radius="left-top:10,10;right-top:10,10;right-bottom:10,10;left-bottom:10,10"			  |
	 * |                                            | round-radius="rx:10;ry:10"			  |
	 * | font              <br/> 设置字体            | font="name"		|
	 * | border-show       <br/> 边框显示属性        | 取值 never:不显示, always:显示, highlight:鼠标悬停时显示, focus:控件获得焦点时显示		  |
	 * | back-show         <br/> 背景显示属性        | 取值 never:不显示, always:显示, highlight:鼠标悬停时显示, focus:控件获得焦点时显示				  |
	 * | shadow            <br/> 阴影特效          | shadow="dx,dy,blur,spread,color,inset"	shadow="3,3,2,0,rgb(0,0,0,100),inset;3,3,2,0,rgb(0,0,0,100),inset"		  |
	 * | visible           <br/> 可见性              | 取值 true/false		  |
	 * | enable            <br/> 可用性/禁用状态     | 取值 true/false				  |
	 * | tooltip           <br/> 提示文本            | tooltip="这是一段鼠标悬停时的提示文本内容"			  |
	 * | nID               <br/> 控件整数ID          | nID="101"		  |
	 * | skin-id           <br/> 皮肤唯一标识符,查找皮肤时的关键key             |	skin-id="skin_white"		  |
	 * | cursor            <br/> 光标                | 取值：arrow,ibeam,hand,wait,cross,uparrow,size,icon,sizenwse,sizenesw,sizewe,sizens,sizeall,no		  |
	 * | isShortCut        <br/> 是否可以响应快捷键   | true/false		  |
	 * | shortcut          <br/> 响应快捷键          | shortcut="ctrl+B"			  |
	 * | refresh           <br/> 刷新控件            |	true/false		  |
	 * | margin-hot        <br/> 热点时的边缘膨胀尺寸   | margin="2,2,2,2"	左上右下的顺序		  |
	 * | control-flags     <br/> 功能标志位          |	"-"前缀代表删除属性<br/>如 control-flags="AllowFocusWhenClick,-SupportTabKey"		  |
	 * |                                             | StaticState :静态控件，不响应键盘和鼠标				  |
	 * |                                             | AllowFocusWhenClick :用户单击时可控件获取焦点			  |
	 * |                                             | AllowCaptureMouseWhenClick :用户左键时，捕获鼠标			  |
	 * |                                             | SupportTabKey :支持tab获得焦点			  |
	 * |                                             | AutoSeatLayout :自动占位布局			  |
	 * |                                             | ShowMarginOnCaptureMouse :鼠标悬停时，显示边缘膨胀特效			  |
	 * |                                             | ShowMarginOnFocus :获得焦点时，显示边缘膨胀特效			  |
	 * |                                             | RoundRadiusDrawLine :控件圆角			  |
	 * |                                             | RoundRadiusParl: 控件Parl四边形  |
	 * |                                             | HideWndWhenClick :单击时隐藏窗口			  |
	 * |                                             | forcelayout:控件尺寸变化时，强制重新计算布局位置			  |
	 * |                                             | use-par-color-fg : 控件前景颜色，使用父控件的			  |
	 * |                                             | use-par-color-border : 控件边框颜色，使用父控件的			  |
	 * |                                             | use-par-color-text : 控件文本颜色，使用父控件的			  |
	 * |                                             | DisableTheme :禁用主题颜色			  |
	 * |                                             | ZOverSpeedup :控件多到影响性能时启用<br/>启用后会用算法计算控件的遮盖信息，快速定位			  |
	 * |                                             | StorageUserSetting :自动存储控件内容到全局配置文件					  |
	 * |                                             | FixedOnView : 控件坐标原点改变时，此控件固定不变			  |
	 * |                                             | OnlyMoveInParent : 仅在父控件视窗下移动|
	 * | datafile          <br/>  数据文件          | datafile="文件路径"		  |
	 * |         |			  |

	 */
	virtual void ShellAttribute(const BeString& szName, const BeString& szText);

	// 将属性应用到tagert目标
	BOOL ShellAttributeToChildControl(const BeString& childname, const BeString& szName, const BeString& szText);

	// virtual void JsonFormateAttribute(JsonObject& setting);                    ///< 将对象转换为json文本
	// virtual void LoadJsonFormateAttribute(JsonObject& setting);                ///< 应用json配置

	virtual void OnParseItemData(XMLItem* pNode); ///< 解析xml文件对应的数据

	virtual void OnSaveConfigSetting(XMLItem* node); ///< 保存控件属性到全局配置文件
	virtual void OnLoadConfigSetting(XMLItem* node); ///< 加载控件属性

	virtual void OnCreate();      ///< 产生时间是窗口创建之后显示之前
	virtual void OnFontChange();  ///< 字体更改
	virtual void OnControlSize(); ///< 控件尺寸改变时触发
	virtual void OnShow(bool bShow);
	virtual void OnCtrlKillFocus(); ///< ui控件失去焦点
	virtual void OnCtrlSetFocus();  ///< ui控件获得焦点

	virtual BOOL HitTest(POINT pt);                         ///< 点击测试
	virtual BOOL OnKillFocus(WPARAM wParam, LPARAM lParam); ///< 当管理的句柄HWND失去焦点时 进入此函数，也就是此函数实际上是窗口 MSG_WND_KILLFOCUS的响应
	virtual BOOL OnHSCrollBar(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnVSCrollBar(WPARAM wParam, LPARAM lParam);

	virtual BOOL OnSetCursor(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNcHitTest(POINT pt);
	virtual BOOL OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnMouseEnter(WPARAM wParam, LPARAM lParam); ///< 在鼠标进入控件时触发
	virtual BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnMouseWheel(WPARAM wParam, LPARAM lParam); ///< 鼠标滑轮消息

	virtual BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnRButtonDown(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnRButtonUp(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnRButtonCliked(WPARAM wParam, LPARAM lParam);

	virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam); ///< 键盘消息
	virtual BOOL OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnChar(WPARAM wParam, LPARAM lParam);

	virtual BOOL OnTimerEvent(unsigned int timerid, UINT umsec);               ///< 定时器事件响应
	virtual BOOL OnPaintControl(ISurface* pSurface, LPRECT lprcUpdate = NULL); ///< lprcUpdate :控件的局部更新区域， 为 NULL 表示全部更新

	/// lpUpdate 表示需要重绘的区域，这个区域的坐标表示是基于HWND窗口坐标系下的。也就是绝对位置。
	virtual BOOL DoPaintShadow(ISurface* pSurface, bool inset, RECT* lpUpdate);
	virtual BOOL DoPaintBackGround(ISurface* pSurface, RECT* lpUpdate); ///< 绘制背景
	virtual BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate);           ///< 绘制前景
	virtual BOOL DoPaintBorder(ISurface* pSurface, RECT* lpUpdate);     ///< 绘制边框
	virtual BOOL DoPaintFinished(ISurface* pSurface, RECT* lpUpdate);   ///< 绘制结束事件，极少场景需要用到

	virtual BOOL OnDropBegin(); ///< 鼠标拖拽开始
	virtual BOOL OnDropEnd();   ///< 鼠标拖拽结束

	virtual void CloneAttribute(CControlUI* clone); ///< 克隆属性

	/* override IControlUI menthos:*/
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;

	int GetSplitControlOffsetW() override;
	int GetSplitControlOffsetH() override;

	void Layout(int x, int y, int w, int h, UINT flags) override;
	bool IsVisibleLayout() override;
	RECT GetPosition() override;

	void SetLauoutInfo(ILayout* parent, int w, int h, SizeMode stw, SizeMode sth);

	void ChangeManager(IManageHandler* pMagr); ///< 改变控件的管理对象(将抽象控件改变实际窗口的作用域)。

	/* static menthos:*/
	static void ChangeParent(CControlUI* pThis, CControlUI* pNewpar, CControlUI* pAfterchild);
	static void ParseShortCutText(const char* text, UINT& vCtrl, UINT& vKey); ///< 解析快捷键
	static BeString ConvertShortCutCodeToText(UINT vCtrl, UINT vKey);         ///< 快捷键转换为字符串
  private:
	BOOL updateForceParentColors(uint64_t flags);
	void updateChildColors(uint64_t checkbit = -1);

	void doShowChanged(bool show);  ///< 可见性改变时响应函数
	void doThemeChanged(int index); ///< 主题发生改变响应函数
  protected:
	void UpdateMarginStateFlag(); ///< 更新margin状态标志位
	RECT GetMarginAreaRect() const;
	BOOL SetMouseCursor(CursorMouse id); ///< 设置系统光标
	void InsertBreakChain(CControlUI* prev, CControlUI* next);
	void DeleteBreakChain(CControlUI* prev, CControlUI* next);
	void ClientToHWNDScreen(); ///< 将控件坐标转换为窗口下的坐标
	void RePlotChildPos();
	void AdjustLayoutControlSize(POINT pt); ///< 用户调整控件大小
	BOOL IsRedrawHovn() const;
	void NotifyChildControlEnableChange(bool bEnable); ///< 父控件被禁用时，同步更新子控件禁用状态
	void NotifyChildControlVisableChange(bool bShow);  ///< 父控件被隐藏时，同步更新子控件隐藏状态

	static UBYTE ReturnBitFlag(UBYTE value, UINT bit_pos, BOOL bEnable);
};

extern "C" {

/// 根据读取的XML信息创建控件
UI_EXP CControlUI* CreateControl(const TCHAR* className, IManageHandler* pM, LPCTSTR ctlName, LPCTSTR text, CControlUI* pPar, RECT rc, UINT nID, UINT nstyle);
}



}





#endif
