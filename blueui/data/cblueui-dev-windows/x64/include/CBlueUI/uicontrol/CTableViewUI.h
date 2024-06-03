#ifndef CBLUEUI_CTABLEVIEW_BLXDY_INC_H_
#define CBLUEUI_CTABLEVIEW_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory>
#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "CContainTitleUI.h"
#include "core/CCoreEventHandler.h"
#include "platform/UIManager.h"

namespace BUI {

/**
 * @brief 表格行
 *
 */
class UI_EXP TableRow : public CheckBoxMode, public IEventHandler
{
  public:
	RECT m_rcCell;
	std::vector<std::shared_ptr<CNodeSpanCell> > m_datacells;
	BeString m_szData;      // 用户文本数据位
	ItemState m_state;      // 状态
	int m_nDataPos;         // 在缓冲区的索引
	int m_nCustomRowHeight; // 自定义高度(负值表示行高使用容器的统一高度)
	uint32_t m_nCalcPos;    // 定位计算数据

	IEventHandler* m_notifyHandler;                // 事件通知到UI对象
	std::shared_ptr<IActionNotify> m_selectAction; // 选中状态变化事件

	///* 选中状态缓存链表，减少查找开销，降低能耗*/
	// TableRow* next;
	// TableRow* prev;
  public:
	TableRow(int columnCount, BeString rowData, COLORREF titleColor, COLORREF textColor);
	~TableRow();

	CNodeSpanCell* GetCellObject(int col) const;

	inline int GetTableRowHeight(int h) const;

	void SetNotifyHandler(IEventHandler* notify); // 设置消息通知处理者 notify = CTableViewUI

	void SetRowHeightCustom(int rowHeight); // 设置自定义行高，适合每行高度不一致的场景
	// 设置单元格对象
	void SetCellObject(int nCol, std::shared_ptr<CNodeSpanCell>& objCell);
	void OnAllocNodeCell(int nCol, int count);
	void OnDeleteCol(int nCol, int count);
	BOOL SetVisable(BOOL bShow, BOOL bfresh = TRUE);
	BOOL SetSelected(BOOL bSelt, BOOL bfresh = TRUE);

	// 设置单元格的选中状态，全部选中
	BOOL SetCellSelected(int start, int end, BOOL bSelt, BOOL bfresh = TRUE);
	BOOL SetDisable(BOOL bDisable, BOOL bfresh = TRUE);
	void OnTranslateLanguage();
	int Size() const;
	void NeedUpdateUI();

	BOOL OnMessageHandler(UINT message, WPARAM wp, LPARAM lp) override;
};

/**
 * @brief 表格控件
 *
 */
class UI_EXP CTableViewUI : public CContainTitleUI, public CSortContainer
{
	DECLARE_DYNAMIC_OBJ_CLASS(CTableViewUI)
  private:
	COLORSTYLE m_ChkboxColors;              // 复选框颜色风格
	RoundRectRadius m_RoundRadiusHighlight; // 选中高亮圆角尺寸
	// TableRow m_select_head_list;            // 选中状态的链表，表头无意义
	std::vector<TableRow*> m_vecRows;
	std::vector<int> m_vecVisualRs; // 可见列表
	BOOL m_bHasRs;
	int m_nNoWidth;      // 序号列的当前宽度
	UINT m_uGridMode;    // 网格线模式 enum GridLineMode
	int m_nHighLightRow; // 高亮行
	int m_nLastTimeHit;  // 最近一次的点击行

	int m_nEditRowIndex; // 正在编辑的单元格 (row, col)
	int m_nEditColIndex;

	bool m_bShowColNum;   // 是否显示行号
	bool m_bShowCheckBox; // 是否显示check
	bool m_bEnableEdit;   // 是否可以编辑
	bool m_bSelectAll;    // 把当前所有可见行，标记为勾选状态

	bool m_bSuportSplitPage; // 是否支持分页
	int m_nPageSize;         // 页大小
	int m_nPageCurSel;       // 当前页索引

	int m_nCurSortCol;    // 当前排序列号
	int m_nRowHeight;     // 行高
	int m_limitRowCounts; // 限制加载行数

	int m_nCustomHeightRowCount; // 自定义行高的数量
	int m_updateCustomCount;

  public:
	CTableViewUI();
	~CTableViewUI();

	/* CContainTitleUI override methods: */
	void ChangeThemeColors(int theme) override;
	void OnControlSize() override;
	void OnChangeHeaderColWidth() override;
	void OnDbClickCell(int nRow, int nCol);
	void OnInsertColumn(int ncol, int sum) override;
	void OnDeleteColumn(int ncol, int sum) override;
	void OnSortColum(int ncol, OrderByType ordertype, DataType sortType, BOOL bNoCase) override;
	void OnPaintMovingColum(int ncol, int dx, ISurface* pSurface, RECT* lpUpdate) override;


	void OnClickColumHeader(UINT nCol);
	/**
	 * data cell interface
	 */
	TableRow* InsertRow(int nRow, LPCTSTR szRowData = NULL); ///< 成功插入，返回行对象。失败，返回空指针
	TableRow* AppendRow(LPCTSTR szRowData = NULL);

	TableRow* InsertRow(int nRow, BeString szRowData);
	TableRow* AppendRow(BeString szRowData);

	CNodeSpanCell* GetCellItem(int nRow, int nCol) const; ///< 获得单元格容器节点
	CNodeData* GetCellNodeData(int nRow, int nCol) const; ///< 获得单元格数据对象

	BOOL RemoveRows(int nRows, int count = 1);   ///< 删除
	BOOL RemoveSelectRows(BOOL bRefresh = TRUE); ///< 删除选中行
	void Clear(BOOL bErase = TRUE);              ///< 清空

	TableRow* GetRow(int nRow) const;
	TableRow* FindRowPositionByUserData(LPCTSTR szdata) const; ///< 根据行用户数据，得到行的位置

	void SetTransposition(bool transposition); ///< 设置行列转置

	void SetItemRoundRadius(RoundRectRadius& radius);
	void SetItemRoundSize(int rx, int ry);

	void SetPageSize(unsigned size); ///< 设置分页尺寸
	void SetPageCurSel(int sel);     ///< 设置当前页
	void EnableMultPage(bool bSup);  ///< 设置分页功能可用性
	BOOL IsSupportMultPage() const;  ///< 分页功能是否可用
	int GetPageCounts() const;       ///< 分页数量

	int HitTestCol(int x, int y);
	int RowCounts() const;       ///< 行总数
	int VisableRowCount() const; ///< 可见行总数
	int GetNodeIndexWithName(LPCTSTR name) const;
	void SetCurSel(int row, int count, BOOL bRefresh = TRUE); ///< 设置当前选中行

	void ShowNumText(bool bShow); ///< 显示行号
	void ShowMultiCheckBox(bool bShow);
	void CheckBox(int nRow, SelectState state);

	void CheckBoxAll(bool bCheck, BOOL bErase = TRUE);
	void VisableAll(bool bShow, BOOL bErase = TRUE);
	void SelectAll(bool bSlted, BOOL bErase = TRUE);

	void SetVisibleResultList(std::vector<int>& rs); ///< 设定可现实行的索引列表
	void ClearVisibleResultList();                   ///< 恢复原状
	BOOL JumpViewRow(int index, BOOL bTop);          ///< 滚动到指定索引行
	int GetRowHeight() const;                        ///< 数据行高度
	void SetRowHeight(int h);                        ///< 设置行高度
	BOOL IsInVisibleView(int pos) const;             ///< 是否在可视区域内
	UINT GridLineStyle() const;
	void SetGridLineStyle(UINT nStyle);
	void ShowEditor(int nRow, int nCol);
	void HideEditor(int nCol);
	void PrintToFile(FILE* fp, LPCSTR space_prefix = " "); ///< 打印数据信息

	// 保存表格数据到xml格式的node节点，该格式和ui文件中的数据初始化格式相同
	void SaveDataToStringWithXml(XMLItem* node);

	void OnClickHeader(POINT pt); ///< 表头点击事件回调虚函数
	void SortColumn();
	void DrawAllCheckBox(ISurface* pSurface, RECT* lpUpdate, COLORREF color);
	BOOL DoPaintNumCtrl(ISurface* pSurface, RECT* lpUpdate);
	void GetCheckedRows(BOOL bChecked, std::vector<TableRow*>& outlist) const;
	void GetSelectedRows(BOOL bSelected, std::vector<TableRow*>& outlist) const;

	/* CControlUI override methods: */
	void OnParseItemData(XMLItem* pNode) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | limit-rows<br/>可加载的最大行数，用于调试大文件   |		  |
	 * | rowHeight <br/>行高               | rowHeight="25"	    |
	 * | line-type-level <br/>层级画笔风格  | solid, dot, dash, dash-dot, dash-dot-dot   |
	 * | cursel <br/>设置当前选中项         | cursel="行号"		    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnChar(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	CControlUI* HitTestControl(POINT pt) override;

	void OnReLayout() override;

  private:
	void DoPaintColum(int col, int nShowRow, int endrow, ISurface* pSurface, RECT* lpUpdate);
	void DrawGridFill(ISurface* pSurface, int rowbegin, int rowend, RECT rcAbs, RECT* lpUpdate);

	void DrawRowBackIntervalFill(ISurface* pSurface, int rowbegin, int rowend, RECT* lpUpdate); // 用间隔颜色填充背景

	UINT HitTestFlag(POINT pt);
	int HitTestRow(POINT pt);

	TableRow* GetTableRow(int visable_index) const;
	int GetRealRowPos(int visable_index) const;           // 根据视觉序号，获得数据在内存当中的位置
	void GetShowIndexRange(int& begin, int& count) const; // 获得当前可见的行信息

	int GetPageCapacity(int page) const;

	int CalcLeadWidth() const;

	void CalcAllCustomHeightPos();

	void GetCellRect(int nRow, int nCol, RECT* lprect) const;

	int GetBeforeRowVisableCount(int nRow) const; // 在nRow前面的可见行数量

	void RefreshRowsRect(int r1, int r2, int c1, int c2);

	int GetMoveRowIndex(int pos, BOOL bPrev) const; // 获得下一个行号

	BOOL MoveRow(BOOL bPrev);

	BOOL IsInClientViewBody(int index); // 判断当前行是否在可视化范围内

	BOOL IsInClientViewBody(const TableRow* row);

	BOOL IsShowEditor() const;

	int GetPageOfRows(int p) const; // 获得当前页的行数量

	void Commit(LPCTSTR text);

	int BinarySearchRow(int left, int right, int dv) const;
};


}
#endif