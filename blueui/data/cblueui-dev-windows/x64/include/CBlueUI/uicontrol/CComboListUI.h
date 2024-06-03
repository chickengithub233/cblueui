#ifndef CBLUEUI_COMBOBOX_BLXDY_INC_H_
#define CBLUEUI_COMBOBOX_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "platform/WindowPlatformInc.h"
#include "platform/UIManager.h"
#include "CEditTextUI.h"
#include "CNodeData.h"
#include "CNodeCell.h"
#include "CContainLayoutUI.h"

namespace BUI {

class CListBoxUI;
class CColorPickerUI;

/**
 * @brief 下拉弹出框管理对象
 *
 */
class UIManagerPopDropdown : public UIManager
{
  public:
	UIManagerPopDropdown();
	~UIManagerPopDropdown();

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;

	void Init(CControlUI* pResponseControl);
	void OnHostControlProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void DrapShow(BOOL bShow);

  public:
	WindowPlatform m_winplat;
	UINT m_first_startup;
	CControlUI* m_pHostUI; // 响应的父控件
	CControlUI* m_pDropUI; // 下拉窗口中的选项控件
};

/**
 * @brief 下拉控件基类，下拉弹出窗口采用单例模式。减少对窗口资源的消耗
 *
 */
class UI_EXP CComboBaseUI : public CEditTextUI
{
  protected:
	int m_nDropHeight;
	int m_nWidthMin;
	BOOL m_bDropKillFocus; // 弹窗失去焦点消息已发送
	BOOL m_bBtnEvent;      // 右侧点击事件开启
	BOOL m_bDropBtnDown;
	BOOL m_bTextStyleDisplay; // 文本风格展示. TRUE(文本展示),FALSE(CNodeData数据展示)

	std::shared_ptr<CNodeData> m_valuedata;

	CControlUI* m_pDragOfControl; // 下拉窗口中的选项控件
  public:
	CComboBaseUI();
	~CComboBaseUI();

	CNodeData* GetCurselNodeData() const;

	void SetDropMinWidth(int width);
	void SelectChange();
	void EnableTextDisplay(BOOL bText);

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void OnCreate() override;
	void OnCtrlKillFocus() override;
	void OnCtrlSetFocus() override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	void GetControlValueText(BasicStringBuffer& buffer) override;
	void SetControlValueText(const BeString& str) override;
	/* ICommitTarget override methods:*/
	void OnSummitTarget(FourCode four_code, LPCTSTR data) override;

	BOOL SendToPopWidgetMessage(UINT message, WPARAM wParam, LPARAM lParam); ///< 向下拉窗口发送消息
	virtual CControlUI* OnCreateDropUI(IManageHandler* pManager);            ///< 创建下拉响应控件
  protected:
	void GetDropBtnRect(RECT* rc);
	void ShowDropWindows(BOOL bShow);
	IManageHandler* GetPopManager();
};

/**
 * @brief 普通下拉列表
 *
 */
class UI_EXP CComboListUI : public CComboBaseUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CComboListUI)
  private:
	CListBoxUI* m_ListBox;
	int m_nShellSel; // 默认的选项
	bool m_bSubmitKey;
	short m_nColCount;    // 当前的列数目
	short m_nMaxColCount; // 最大列数目

  public:
	CComboListUI();
	~CComboListUI();

	int AddItem(std::shared_ptr<CNodeData> rawdata, const BeString& szTextID);
	int InsertItem(int nIndex, std::shared_ptr<CNodeData> rawdata, const BeString& szTextID);
	int DeleteItem(UINT nIndex); // 删除索引位置节点

	int GetCounts() const;
	int GetCurSel() const;              // 返回组合框中列表框中当前选中的项的下标。如果没有选中项，则返回-1。
	int SetItemHeight(int nItemHeight); // 设置下拉框高度
	void ResetContent();                // 清空所有项
	CNodeData* GetNodeDataByPos(int index) const;
	CNodeCell* GetNodeCellByPos(int index) const;
	CNodeCell* GetNodeCell(LPCTSTR nameid) const;
	BeString GetCurSelDataValue() const;

	void GetNodeTextID(int index, BeString& str) const; // 节点文本逻辑id
	int SetCurSel(int nSelect);
	void SetDropUIbgColors(COLORREF crBk);

	void OnParseItemData(XMLItem* pNode) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	void OnCreate() override;
	void OnControlSize() override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void OnBeginEdit();
	CControlUI* OnCreateDropUI(IManageHandler* pManager) override; // 创建下拉响应控件
};

/**
 * @brief 日期下拉框
 *
 */
class UI_EXP CComboDateUI : public CComboBaseUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CComboDateUI)

  public:
	CComboDateUI();
	~CComboDateUI();

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;

	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	CControlUI* OnCreateDropUI(IManageHandler* pManager) override; // 创建下拉响应控件
};

/**
 * @brief 范围选择框
 *
 */
class UI_EXP CComboDateRangeUI : public CComboBaseUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CComboDateRangeUI)

  public:
	CComboDateRangeUI();
	~CComboDateRangeUI();

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	CControlUI* OnCreateDropUI(IManageHandler* pManager) override;
};

/**
 * @brief 颜色拾取器
 *
 */
class UI_EXP CComboColorPickerUI : public CComboBaseUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CComboColorPickerUI)
  public:
	CComboColorPickerUI();
	~CComboColorPickerUI();
	void SetColorValue(COLORREF color);
	COLORREF GetColorValue() const;

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	CControlUI* OnCreateDropUI(IManageHandler* pManager) override;

	/* ICommitTarget override methods:*/
	void OnSummitTarget(FourCode four_code, LPCTSTR data) override;

  protected:
	COLORREF m_color_value;
};

/**
 * @brief 用户自定义的下拉控件
 *
 */
class UI_EXP CCustomComboxUI : public CComboBaseUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CCustomComboxUI)
  private:
	CContainLayoutUI m_container;

  public:
	CCustomComboxUI();
	~CCustomComboxUI();

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	CControlUI* OnCreateDropUI(IManageHandler* pManager) override; // 创建下拉响应控件

	void LoadDropboxUIData(const char* uidata);
	void LoadDropboxUIFile(const char* filename);
};



}

#endif