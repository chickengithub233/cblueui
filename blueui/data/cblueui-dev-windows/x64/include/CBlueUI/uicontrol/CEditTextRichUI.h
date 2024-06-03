#ifndef CBLUEUI_CEDITTEXTRICHUI_BLXDY_INC_H_
#define CBLUEUI_CEDITTEXTRICHUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "CEditLine.h"

#include "core/SafeVector.hpp"

namespace BUI {

/**
 * @brief 多行文本输入框(自主设计自绘，未使用系统原生编辑输入框,可方便移植到嵌入式平台)
 *
 */
class UI_EXP CEditRichUI : public CScrollAreaUI, public CEditLineStyle
{
	DECLARE_DYNAMIC_OBJ_CLASS(CEditRichUI)
  public:
	CEditRichUI();
	~CEditRichUI();

	void AppendEditText(LPCTSTR str, uint32_t len = -1, BOOL bRefresh = FALSE);
	void AppendEditTextA(LPCSTR str, uint32_t len = -1, BOOL bRefresh = FALSE);


	void AppendLastLine(LPCTSTR text, int count = -1, GFont* font = NULL, COLORREF* color = NULL, BOOL bRefresh = FALSE);

	void GetEditText(BeString& str);

	CEditLine* NewEditLine();

	CEditLine* GetEditLine(int pos) const;

	CEditLine* InsertLine(int pos, LPCTSTR text, int count = -1, BOOL bRefresh = TRUE);

	void DeleteLine(int pos, int count, BOOL bRefresh = TRUE);
	void Clear(BOOL bRefresh = TRUE);
	int GetlineCounts() const;
	void SelectSessionAll(BOOL isSelect, BOOL bRefresh);

	void SetMarkLeadSize(int w, BOOL bRefresh); ///< 设置行首标记栏宽度
	/* CEditLineStyle menthods:*/
	BOOL GetRectTextView(RECT& rc) override;

	/* CScrollAreaUI menthods:*/
	void OnControlSize() override;
	void OnShow(bool bShow) override;
	void OnCtrlKillFocus() override;
	void OnCtrlSetFocus() override; // ui控件获得焦点
	void OnFontChange() override;   // 字体更改
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

	/* override IControlUI methos:*/
	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;

	/* override CEditLineStyle methos:*/
	void OnChangeUpdate(UINT bits);

  protected:
	void DrawLineNumber(ISurface* pSurface, int firstline, int y0, const RECT& rcText, RECT* lpUpdate); // 绘制行号

	BOOL DoInputChar(WPARAM wParam, LPARAM lParam, BOOL isFocus);
	BOOL DoInputPreeditChar(WPARAM wParam, LPARAM lParam, BOOL isFocus);
	BOOL DoInputCommitChar(WPARAM wParam, LPARAM lParam, BOOL isFocus);
	void MergeLine(int line1, int line2);
	BOOL DeleteSession(RECT& rcUpdate);
	BOOL OnClickPoint(POINT pt);

	/**
	 * @brief 更根据鼠标定位到指定的行
	 *
	 * @param dy 相对第一行的高度
	 * @param div 输出距离行top的相对距离，用于计算光标在多行模式下的wrap子行位置
	 * @return int 返回命中行索引
	 */
	int FindLine(int dy, int& div);
	RECT GetRefreshRect(int line1, int line2);

	BOOL GetSelectedLinesRange(int& start, int& end); ///< 获得选中行的范围

	void ScrollHorzToPos(RECT& rcUpdate, int line, int pos, BOOL nearLeft); // 水平移动到指定字符
	void ScrollVertToPos(RECT& rcUpdate, int line, int pos, BOOL nearTop);  // 垂直移动到指定字符

	void MoveChars(int i);
	void MoveLine(int& line, int i, int dx);
	void UpdateSelectRangeState(int last_pos, RECT& rcUpdate);
	int GetScrollRangeX() const;
	int GetScrollRangeY(int no);

	int GetLineTextLeft(RECT& rcText) const;
	void PasteString();
	void CutString();
	void CopyString();

	void CaclLineBottomPos();
	void LineBottomPosChange(int pos, int step); // 插入数据时，同步更新y坐标值
	int BinarySearchLine(int left, int right, int dv) const;

  protected:
	std::vector<CEditLine*> m_lines;
	AtomicLock m_mutex_running;              // 状态锁定
	std::vector<CEditLine*> m_lines_editing; // 激活态的
	int m_select_first;
	int m_first_cursor_pos;
	int m_select_last;
	int m_last_cursor_pos;
	int m_ver_dx;    // 上下移动时记录偏移量
	int m_nMarkLead; // 行首标记显示
	POINT m_ptAutoMoveTrace;

	std::vector<GColor> m_headMarkColors; // 前置标记颜色表
	std::vector<GImage*> m_headMarkImgs;  // 前置标记图标表
};



}

#endif