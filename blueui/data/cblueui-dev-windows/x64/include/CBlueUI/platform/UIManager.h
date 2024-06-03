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
#ifndef CBLUEUI_MANAGER_BLXDY_INC_H_
#define CBLUEUI_MANAGER_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
#include <vector>
#include <deque>
#include <map>
#include <list>

#ifndef CBLUEUI_DISPLAY_SURFACEENGINE_PAN_INC_H_
#include "graphics/GSurface.h"
#endif

#include "core/UtilsRect.h"
#include "layout/CLayoutManager.h"
#include "plugins/CScriptPlugin.h"

namespace BUI {

class CControlUI;

/**
 * @brief 控件UI管理器，负责消息转发和定位
 *
 */
class UI_EXP UIManager : public IManageHandler
{
	DECLARE_DYNAMIC_OBJ_CLASS_BASE(UIManager)
  protected:
	std::shared_ptr<IAdapterPlatform> m_platform; // 平台框架适配器(win32, gtk, qt, mac)等
	std::vector<CControlUI*> m_vecNoParCtrl;      // 父控件为NULL的控件, 不接受鼠标消息的控件在最后
	std::vector<CControlUI*> m_vecKeyBord;        // 快捷键响应

	std::vector<CControlUI*> m_popuiStatck; // 弹出栈

	std::list<CControlUI*> m_listTabFocus; // 响应Tab 焦点切换键的控件顺序

	char m_nameid[16];
	CLayoutBox m_layRootBox; // 布局管理
	CControlUI* m_pRoot;
	CControlUI* m_pHover;
	CControlUI* m_pEvent; // 事件产生消息的控件
	CControlUI* m_pEventKey;
	CControlUI* m_pFocus;        // 焦点空间
	CControlUI* m_pMouseCapture; // 捕获鼠标的控件
	CControlUI* m_pTipBox;
	CControlUI* m_pPopCtrl; // 模拟doModel的虚拟控件，消息由m_pPopCtrl托管

	IDockHandler* m_dockHandler; // dock manager handler

	UINT m_nMgrFlagsEx;           // 扩展控制和状态参数
	int m_blur_size;              // 高斯模糊卷积窗口大小，默认为0
	CursorMouse m_current_cursor; // 当前光标
	UINT m_paintOptions;
	XImageInfo* m_tempPixDC;
	UINT m_tempPixType;
	CControlUI* m_tempUI;
	COLORREF m_bkColor;

	RECT m_rcAsync[2];                   // 异步刷新区域缓存
	int m_nAsyncRefresh[2];              // 帧是否需要刷新标志位
	std::atomic<int> m_nAsyncCur;        // 异步刷新当前帧绘制索引
	std::atomic<int> m_nAsyncBuf;        // 异步刷新下一帧绘制索引
	std::atomic<int> m_nAsyncCurRunning; // 当前帧正在绘制

	GImage* m_pCanvasBuf; // 缓存当前画面
	RECT m_rcCanvas;      // 缓存画面的区域

	POINT m_drag_pt;
	RECT m_drag_rc;
	SIZE m_initSize;
	BOOL m_bCanMove;          // 可拖拽移动窗口
	bool m_hideWhenKillFocus; // 失去焦点是隐藏窗口
	bool m_bMouseCapture;     // 是否已经捕获鼠标资源

	bool m_bMouseDrop; // 鼠标是否在拖拽
	bool m_bCleaning;  // 正在清理控件
  public:
	UIManager();
	virtual ~UIManager();

	UINT InitPlatformAdapter(std::shared_ptr<IAdapterPlatform> adapter);
	IAdapterPlatform* GetAdapterPlatform() const;

	void SetHideWhenKillFocus(bool hide);
	BOOL DestoryManger();                             ///< 释放管理对象占用的资源
	UINT DoModal();                                   ///< 模态化
	void TipTrack(int x, int y, LPCTSTR lpSz = NULL); ///< 提示框显示位置 x, y 是相对窗口
	void TipHide();
	void RebuildControls();                                                ///< 重建manger上的所有控件
	void AppendTabFocusControl(CControlUI* pTabFocus);                     ///< 将控件追加到到Tab list
	void RemoveTabFocusControl(CControlUI* pTabFocus);                     ///< 将控件删除Tab list
	void ChangeTabFocusControl(CControlUI* pAfter, CControlUI* pTabFocus); ///< 变更Tab 顺序

	BOOL RegisterUIControl(CControlUI* pCtrl); ///< 注册控件到管理类中
	BOOL LogoffUIControl(CControlUI* pCtrl);   ///< 注销控件到管理类中

	BOOL RegisterShortCutControl(CControlUI* pCtrl); ///< 快捷键控件注册到管理类中
	BOOL LogoffShortCutControl(CControlUI* pCtrl);   ///< 快捷键控件注销到管理类中

	SIZE GetRootControlSize() const; ///< 获得第一个控件的尺寸
	void UpdateLayout();             ///< 更新布局

	void OnShowWindow(bool bShow); ///< 窗口显示状态

	BOOL OnDrawControls(ISurface* pSurface, RECT* lpValidateRect);

	BOOL DrawBgControls(ISurface* pSurface, RECT* lpValidateRect, CControlUI* pCtrl);

	void SetCanvasBuffer(GImage* canvas, RECT* rcArea); ///< 缓存画面

	void NeedUpdate(RECT* rc, BOOL bSynch) override; ///< 更新区域
	BOOL BringTopMost(CControlUI* pCtrol);           ///< 控件的Z-Order最高优先级
	BOOL BringBottomMost(CControlUI* pCtrol);        ///< 控件的Z-Order最低优先级

	CControlUI* SetFocusUI(CControlUI* pFocus); ///< 指定控件获得输入焦点
	CControlUI* FindContrlByID(UINT nID);       ///< 查找控件
	CControlUI* FindContrlByPoint(POINT pt);
	CControlUI* FindContrlByClassName(LPCTSTR ctrlName);
	CControlUI* FindContrlByClassNameA(const char* ctrlName);
	CControlUI* HitTestControl(POINT pt);
	CControlUI* PopModalControl();

	/* IManageHandler method: */
	void SetDockHandler(IDockHandler* dockMgr) override;
	ILayout* LayoutBox() override;
	void SetPaintOptions(UINT options) override;
	UINT GetPaintOptions() override;
	void ClientPointToScreen(POINT* pt) override;
	void ScreenPointToClient(POINT* pt) override;
	BOOL IsWindowFullMax() override;
	BOOL SendMsg(UINT message, WPARAM wParam, LPARAM lParam) override; ///< 同步消息
	BOOL PostMsg(UINT message, WPARAM wParam, LPARAM lParam) override; ///< 异步消息

	BOOL ToFocusHandler(UINT message, WPARAM wParam, LPARAM lParam) override;   ///< 发送到焦点控件
	BOOL ToHotHandler(UINT message, WPARAM wParam, LPARAM lParam) override;     ///< 发送到热点控件
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override; ///< 消息处理过程

	/**
	 * @brief 设置控件扩展风格
	 *
	 * @param style 取@link ControlFlag @endlink组合值
	 * @param op  ADD_FLAGS(添加属性) REMOVE_FLAGS(删除属性)
	 */
	void ModifyManagerFlags(UINT style, UINT op = ADD_FLAGS) override;
	UINT IsHasManagerFlags(UINT flags) override;
	UINT GetManagerFlags() override;

  private:
	void AddPopupUI(CControlUI*);    // 添加到弹出队列
	void RemovePopupUI(CControlUI*); // 添加到弹出队列
	BOOL HitTestPopupUI(POINT pt);

	void OnRefreshAsync(RECT* rc);                                // 异步刷新区域
	void OnAsyncPaintHandler();                                   // 异步刷新响应函数
	BOOL OnMouseMove(UINT message, WPARAM wParam, LPARAM lParam); ///< 消息转发过程
	CControlUI* NextTabKeyFocus(CControlUI* pCurFocus);           ///< 下一个tab 控件
};


}

/// 在全局范围内寻找控件，并绑定赋值
#define BIND_CTL_VARIABLE_BY_NAME(pM, Type, pVar, lpName) \
	do { \
		pVar = NULL; \
		pVar = dynamic_cast<Type*>(GCManager()->FindManageOfControl(pM, lpName)); \
	} while (0)

/// 自动绑定控件
#define BIND_CTL_VARIABLE_BY_NAME_AUTO(pM, pParent, Type, pVar, lpName) \
	do { \
		pVar                    = NULL; \
		CControlUI* __parent_0o = pParent; \
		if (__parent_0o) \
			pVar = dynamic_cast<Type*>((CControlUI*)__parent_0o->FindControlByName(lpName)); \
		else \
			pVar = dynamic_cast<Type*>(GCManager()->FindManageOfControl(pM, lpName)); \
	} while (0)

/// 将变量pVar 绑定到lpName的控件地址，从此可以用指针访问。不需要每次查找
#define BIND_ALL_CTL_VARIABLE_BY_NAME(pM, Type, uilist, lpName) \
	do { \
		uilist.clear(); \
		std::vector<CControlUI*> vec; \
		int len = GCManager()->FindManageOfAllControl(pM, lpName, vec); \
		for (int i = 0; i < len; ++i) \
		{ \
			Type* pVar = dynamic_cast<Type*>(vec[i]); \
			if (pVar) uilist.push_back(pVar); \
		} \
	} while (0)

/// 将变量pVar 绑定到nid的控件地址，从此可以用指针访问。不需要每次查找
#define BIND_CTL_VARIABLE_BY_nID(pM, Type, pVar, nid) \
	do { \
		pVar = NULL; \
		pVar = dynamic_cast<Type*>(GCManager()->FindControlByID(pM, nid)); \
	} while (0)




#endif
