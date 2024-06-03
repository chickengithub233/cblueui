#ifndef CBLUEUI_CEDITTEXTUI_BLXDY_INC_H_
#define CBLUEUI_CEDITTEXTUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "CEditLine.h"
#include "CNodeData.h"

namespace BUI {

/**
 * @brief 单行文本输入框(自主设计自绘，未使用系统原生编辑输入框,可方便移植到嵌入式平台)
 *
 */
class UI_EXP CEditTextUI : public CControlUI, public CEditLineStyle, public CEditLine
{
	DECLARE_DYNAMIC_OBJ_CLASS(CEditTextUI)
  public:
	CEditTextUI();
	~CEditTextUI();

	void SetEditText(LPCTSTR str, BOOL bRefresh = FALSE);
	void GetEditText(BeString& str);

	bool InsertChars(int pos, const TCHAR* str, int count, BOOL bClear = FALSE);
	void Clear(BOOL bRefresh = TRUE);

	double GetNumber() const;
	void SetNumber(double value, BOOL noTrigger = FALSE);

	void SelectSessionAll(BOOL isSelect, BOOL bRefresh);

	RECT GetEditClient(); // 获得输入编辑区

	BOOL MoveChars(int i);
	void MoveCurLast();
	bool DestoryCaretCursor();
	void SaveCurrentRollBack(); // 将当前文本保存为回滚内容
	void DoRollBack();          // 执行回滚动作

	void SetControlValueText(const BeString& str) override;
	void OnControlSize() override;
	void OnShow(bool bShow) override;
	void OnCtrlKillFocus() override;
	void OnCtrlSetFocus() override; // ui控件获得焦点
	void OnFontChange() override;   // 字体更改
	void GetControlValueText(BasicStringBuffer& buffer) override;
	// void  OnShow(bool bShow) override;
	// BOOL  OnTimerEvent(unsigned int timerid, UINT umsec) override;
	// BOOL  OnNcHitTest(POINT pt) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam) override;

	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnChar(WPARAM wParam, LPARAM lParam) override;

	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | text-file <br/>加载文件内容  | text-file="文件路径"   |
	 * |            |     |
	 * | CEditLineStyle继承而来           |     |
	 * | text-align <br/>文本对齐方式  | text-align="left,vcenter" 取值left,right,center,top,bottom,vcenter的组合  |
	 * | text-padding <br/>文本内边缩进|  text-padding="10,10,10,10"   |
	 * | empty-tips <br/>空内容时的提示文本|  empty-tips="请输入授权码"   |
	 * | input-range <br/>数值输入范围，超出范围输入无响应    |  input-range="0,100"   |
	 * | input-type <br/>输入类型控制|  "-"号前缀表示删除   |
	 * |            |  Decimal: Allow 0123456789+-  |
	 * |            |  Hexadecimal: Allow 0123456789ABCDEFabcdef   |
	 * |            |  Octal: Allow 01234567   |
	 * |            |  Binary: Allow 01   |
	 * |            |  Uppercase: Turn a..z into A..Z   |
	 * |            |  NoBlank: Filter out spaces, tabs   |
	 * |            |  Scientific: Allow 0123456789.+-/*eE(Scientific notation input) |
	 * |            |  Password: Password mode Allow ascii   |
	 * |            |  ReadOnly: Read-only mode  |
	 * |            |  Multiline: For internal use by InputTextMultiline()  |
	 * |            |  wordwarp: Word wrap   |
	 * |            |  noModify: do not modify text   |
	 * |            |  undo: undo   |
	 * |            |  console: console mode   |
	 * |            |    |
	 * | undo-size <br/>最大撤销步骤          |  undo-size="20"   |
	 * | allow-max-count <br/>允许输入字符数量最大限制          |  allow-max-count="64"   |
	 * | precision <br/>数值显示精度            |  precision="1" 保留1位小数点   |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	/* override IControlUI menthos:*/
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;
	/* CEditLineStyle menthods:*/
	BOOL GetRectTextView(RECT& rc) override;

	std::shared_ptr<CNodeDataLists> GetHeadNodeDataList();
	std::shared_ptr<CNodeDataLists> GetTailNodeDataList();

  protected:
	void UpdateOffsetX(BOOL isToLow);
	void SelectEnd(int end, BOOL check);
	BOOL DoInputChar(WPARAM wParam, LPARAM lParam, BOOL isFocus);
	BOOL DoInputPreeditChar(WPARAM wParam, LPARAM lParam, BOOL isFocus);
	BOOL DoInputCommitChar(WPARAM wParam, LPARAM lParam, BOOL isFocus);
	BOOL DeleteSession(BOOL only_delete_select, BOOL bRefresh = FALSE);
	BOOL OnClickPoint(POINT pt);

	int GetScrollRangeX() const;
	void SendToCommitMSG(BOOL commit);
	void PasteString();
	void CutString();
	void CopyString();

	void GetPrefixIconRect(RECT* rc); // 前缀图标区域
	void GetSuffixIconRect(RECT* rc); // 后缀图标区域


  protected:
	TCHAR m_back_buffer[32];
	BasicStringBuffer m_str_rollback; // back up 将上一次的有效输入备份

	int m_selet_start;
	int m_horz_offset;
	RECT m_rcEdit;
	POINT m_ptAutoMoveTrace;
	BOOL m_bLBDownInEditView;                             // 鼠标在可编辑区域内按下
	std::shared_ptr<CNodeDataLists> m_pefixAndSuffixdata; // 前缀后缀扩展(可放置图表，文本之类)
	std::shared_ptr<CNodeDataLists> m_headdata;
	std::shared_ptr<CNodeDataLists> m_taildata;
};

/**
 * @brief 编辑输入组合体容器
 *
 */
class UI_EXP CEditList
{
  public:
	CEditList();
	~CEditList();

	CNodeDataLists& GetNodeDataList();

  protected:
	void AddEditUI(CEditTextUI* edit);
	void Clear();
	void SetVerJmpStep(int step);
	void SetEditFont(GFont* font);
	BOOL OnMessageHandlerList(UINT uMsg, WPARAM wp, LPARAM lp);
	BOOL DoKeyDown(WPARAM wp, LPARAM lp);
	BOOL MoveNext(int i, BOOL selectall);

	int GetEditControlCount() const;
	int GetFocusEditIndex() const;
	int GetEditControlValue(int pos) const;
	BeString GetEditControlText(int pos) const;

  protected:
	CNodeDataLists m_nodedatalist;
	std::vector<CEditTextUI*> m_edit_list;
	int m_ver_step; // top，bottom移动步长
};

/**
 * @brief 辑输入组合体
 *
 */
class UI_EXP CEditCombinationUI : public CEditList, public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CEditCombinationUI)
  public:
	CEditCombinationUI();
	~CEditCombinationUI();

	void SetEditControlCount(int count);

	void OnCreate() override;
	BOOL OnNcHitTest(POINT pt) override;
	BOOL OnMessageHandler(UINT msg, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	/* CEditCombinationUI override:*/
	virtual void OnEditFormate();

  protected:
	void CreateEditControls();

  protected:
	BeString m_separate_str;
	int m_edit_count;
};

/**
 * @brief IP地址输入框
 *
 */
class UI_EXP CEditIPAddressUI : public CEditCombinationUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CEditIPAddressUI)
  public:
	CEditIPAddressUI();
	~CEditIPAddressUI();

	void OpenIPV6(BOOL isopen);
	void GetIPAddress(int& a, int& b, int& c, int& d, int& e, int& f) const;
	BOOL OnChar(WPARAM wParam, LPARAM lParam) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	/* CEditCombinationUI override:*/
	void OnEditFormate() override;
};


}

#endif