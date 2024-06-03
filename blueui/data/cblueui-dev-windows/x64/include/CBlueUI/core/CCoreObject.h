#ifndef CBLUEUI_CBASEOBJECT_BLXDY_INC_H_
#define CBLUEUI_CBASEOBJECT_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _VECTOR_
#include <vector>
#endif

#include "CCoreBasePro.h"
#include "CCoreEventHandler.h"

namespace BUI {

/**
 * @brief 信号槽基类
 */
class UI_EXP IXSlotBase
{
  public:
	IXSlotBase();
	virtual ~IXSlotBase();
	bool IsVaild() const;
	void SetVaildState(bool bValid);

  protected:
	bool m_bVaild;
};

/**
 * @brief 信号槽管理策略，当槽对象释放时，绑定关系自动删除
 */
class UI_EXP ST_Policy
{
  public:
	ST_Policy();
	~ST_Policy();

	void AddSlot(IXSlotBase* pSlot);

	void Clear();

	void RemoveSlot(IXSlotBase* pSlot);

  private:
	std::vector<IXSlotBase*> m_slots;
};

enum LayoutFlags
{
	ForceResetLayout = 1 << 0, // 重置布局
};

/**
 * @brief 布局基类
 */
class UI_EXP ILayout
{
  public:
	ILayout();
	virtual ~ILayout();

	virtual bool IsVaild();
	virtual bool IsVisibleLayout();
	virtual void SetLayoutInfo(int w, int h, SizeMode tw, SizeMode th);
	virtual void GetLayoutInfo(int& w, int& h, SizeMode& tw, SizeMode& th);
	virtual void SetPadding(int l, int r, int t, int b);
	virtual void SetAlignment(AlignmentStyle hor, AlignmentStyle ver);
	virtual void Layout(int x, int y, int w, int h, UINT flags = 0);              ///< 容器的在（x, y）的位置下。计算容器里对象的具体位置
	virtual BOOL OnLayoutMessageProc(UINT message, WPARAM wParam, LPARAM lParam); ///< (重载函数)布局对象消息处理函数
	virtual void RebuildLayout(bool isForceUpdate);                               ///< 重新布局
	virtual bool IsHasAdaptLayout();

	virtual LayoutType GetLayoutType()   = 0; ///< 获得布局类型
	virtual int GetAdaptWidth(int expH)  = 0; ///< 获得自适应宽度
	virtual int GetAdaptHeight(int expW) = 0; ///< 获得自适应高度

	virtual int GetSplitOffsetW() = 0; ///< 获得拆分宽度偏移
	virtual int GetSplitOffsetH() = 0; ///< 获得拆分高度偏移

	virtual ILayout* FindLayoutByName(LPCTSTR name) = 0;
	virtual ILayout* GetParentLayout()              = 0;
};

/**
 * @brief 控件UI基类
 */
class UI_EXP IControlUI : public IEventHandler
{
  public:
	IControlUI();
	virtual ~IControlUI();
	/* sup base control ui*/
	virtual int LayoutAdaptWidth(int expH)  = 0;
	virtual int LayoutAdaptHeight(int expW) = 0;

	virtual int GetSplitControlOffsetW() = 0; ///< 获得拆分宽度偏移
	virtual int GetSplitControlOffsetH() = 0; ///< 获得拆分高度偏移

	virtual void Layout(int x, int y, int w, int h, UINT flags = 0) = 0;

	virtual RECT GetPosition() = 0; // 获得布局位置，用来测试鼠标命中

	virtual bool IsVisibleLayout() = 0;
};

/// 控件扩展属性标志位
enum UIManagerFlag
{
	UIManagerFlag_WhenBuildIgnoreLayout = 1 << 0, ///< 在构建完成之后在初始化控件位置信息
};

/**
 * @brief 窗口事件管理控制者
 */
class UI_EXP IManageHandler : public IEventHandler
{
  public:
	IManageHandler();
	virtual ~IManageHandler();
	virtual ILayout* LayoutBox() = 0;


	virtual void SetDockHandler(IDockHandler* dockMgr) = 0;

	virtual void SetPaintOptions(UINT options) = 0;

	virtual UINT GetPaintOptions() = 0;

	virtual void ClientPointToScreen(POINT* pt) = 0;
	virtual void ScreenPointToClient(POINT* pt) = 0;

	virtual void NeedUpdate(RECT* rc, BOOL bSynch) = 0;

	virtual BOOL IsWindowFullMax()                                   = 0;
	virtual BOOL SendMsg(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual BOOL PostMsg(UINT message, WPARAM wParam, LPARAM lParam) = 0;

	virtual BOOL ToFocusHandler(UINT message, WPARAM wParam, LPARAM lParam) = 0;

	virtual BOOL ToHotHandler(UINT message, WPARAM wParam, LPARAM lParam) = 0;

	/**
	 * @brief 设置控件扩展风格
	 *
	 * @param style 取@link ControlFlag @endlink组合值
	 * @param op  ADD_FLAGS(添加属性) REMOVE_FLAGS(删除属性)
	 */
	virtual void ModifyManagerFlags(UINT style, UINT op = ADD_FLAGS) = 0;

	virtual UINT IsHasManagerFlags(UINT flags) = 0;

	virtual UINT GetManagerFlags() = 0;
};

// 平台适配器
class UI_EXP IAdapterPlatform
{
  public:
	IAdapterPlatform();
	virtual ~IAdapterPlatform();

	void SetManageHandler(IManageHandler* handler);
	IManageHandler* ManageHandler() const;

	virtual BOOL OnPlatformHandler(UINT message, WPARAM wp, LPARAM lp);

	virtual UINT MessageLoop() = 0;

	virtual BOOL IsZoomed() = 0;

	virtual BOOL IsWindowVisible() = 0;

	virtual BOOL SendMessage(UINT uMsg, WPARAM wParam = 0L, LPARAM lParam = 0L) = 0;
	virtual BOOL PostMessage(UINT uMsg, WPARAM wParam = 0L, LPARAM lParam = 0L) = 0;

	/* window methods:*/
	virtual void GetClientRect(RECT* rc) = 0;

	virtual void GetWindowRect(RECT* rc) = 0;

	virtual void SetActiveWindow() = 0;

	virtual void EnableWindow(BOOL enable) = 0;

	virtual void ShowWindow(UINT model) = 0;

	virtual void MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint) = 0;

	virtual void InvalidateRect(RECT* rc, BOOL bSyncUpdate = FALSE) = 0;

	virtual void ClientPointToScreen(POINT* pt) = 0;

	virtual void ScreenPointToClient(POINT* pt) = 0;

	virtual void GetCursorGloablPos(POINT* pt) = 0;

	virtual BOOL AnimateWindow(DWORD dwTime, DWORD dwFlags) = 0;

  protected:
	IManageHandler* m_manager;
	UINT m_showState; // 窗口显示状态
};

enum MouseHoverState
{
	MS_NULL,   // 鼠标未命中
	MS_HOVER1, // 鼠标悬停热点
};

/**
 * @brief 鼠标命中状态
 *
 */
class UI_EXP MouseHitStatus
{
  public:
	MouseHitStatus();
	~MouseHitStatus();

	void ResetState();
	BOOL HitMouseState(RECT* rc, POINT pt);
	BOOL ClearMouseState();

  public:
	MouseHoverState m_mouseState;
};

enum DragStateFlag
{
	DRAG_NULL,
	DRAG_BEGIN,
	DRAG_MOVING,
	DRAG_END
};

/**
 * @brief 鼠标拖拽
 *
 */
class UI_EXP MouseDragHelper
{
  public:
	MouseDragHelper();
	~MouseDragHelper();

	void SetBeginDragPoint(POINT pt);
	void UpdateCurrentDragPoint(POINT pt);

	SIZE MoveOffset() const;
	POINT TargetPoint() const;

	void SetDragState(DragStateFlag state);
	DragStateFlag DragState() const;

	void SetDragMoveEnable(BOOL bEnableDrag);
	BOOL IsDragMoveEnable() const;

  public:
	BOOL m_bEnableDragMove;
	POINT m_ptBegin;
	SIZE m_moveOffset;
	DragStateFlag m_dgState;
};

class UI_EXP VisibleProperty
{
  public:
	VisibleProperty();
	~VisibleProperty();
	BOOL IsVisable() const;
	void SetVisable(BOOL bShow);

  protected:
	BOOL m_bVisbale;
};

/**
 * @brief dock层叠窗口
 */
class UI_EXP IDockOverlayHandler : public IEventHandler
{
  public:
	IDockOverlayHandler();
	virtual ~IDockOverlayHandler();

	void SetDockManager(IDockHandler* mgr);

	virtual void SetSideRect(RECT rc);

  protected:
	IDockHandler* m_host_mgr;
};




}


#endif
