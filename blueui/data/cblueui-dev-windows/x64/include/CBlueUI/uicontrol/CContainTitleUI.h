#ifndef CBLUEUI_CTITLECONTAINERUI_BLXDY_INC_H_
#define CBLUEUI_CTITLECONTAINERUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <memory>
#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "CNodeCell.h"
#include "platform/UIManager.h"

#define MAX_COLUMN_COUNT 64

namespace BUI {

enum BoxHitState
{
	HT_COL_HEILIGHT,
	HT_COL_DRAG,
	HT_LIST_ROW,
	HT_NC_NONE,
	HT_ROW_CHECKBOX,
	HT_ROW_FOLD,
};

// 网格选择模式
enum GridFillMode
{
	FillNull = 0, // 不填充
	FillRow,      // 填充行
	FillCol,      // 填充列
	FillCell      // 填充单元格
};

// 网格线风格
enum GridLineMode
{
	GridLineNone   = 0x00,
	GridLineX      = 0x01,
	GridLineY      = 0x02,
	GridLineBorder = 0x04
};

// 表头的单元格
class UI_EXP TableHeaderNodeCell : public CNodeCell, public MatchFeatures
{
  public:
	int m_nColWidth;        // 像素尺寸
	int m_nWidthOffset;     // 列宽调整时的增量
	SizeValue m_widthValue; // 像素尺寸的计算模式
	UINT m_uTxtAlign;
	int m_nColumShowPosition; // 列显示的位置, 小于0，代表位置不变
	BOOL m_bEnableSort;       // 是否支持排序
	BOOL m_bNoCase;           // 是否忽略大小写

	DataType m_sortType;       // 排序值类型
	OrderByType m_orderType;   // 排序方式
	UINT m_nMinWidth;          // 最小宽度
	UINT m_nMaxWidth;          // 最大宽度
	bool m_bEnableExChangePos; // 可移动标志
	PaddingInfo m_padding;     // 单元格内容的边距
	std::shared_ptr<CControlUI> m_pEditorUI;

	BeString m_cell_className;
	RECT m_rcClip;
	RECT m_rcClipCol;

  public:
	TableHeaderNodeCell();
	TableHeaderNodeCell(std::shared_ptr<CNodeData> valuedata, int nColWidth, SizeMode model, UINT nFormat);
	~TableHeaderNodeCell();

	void SetPadding(int l, int t, int r, int b);
	int Width() const;
	void SetWidth(SizeValue value);
	void SetWidthIncrement(int dw);

	void SetSizeMin(int min_);
	void SetSizeMax(int max_);

	void SetCellRect(int x, int y, int w, int h);

	void SetCellClipRect(int x, int y, int w, int h); // 设置表头单元格裁剪区域

	void SetColClipRect(int x, int y, int w, int h); // 设置整列(不包含表头)裁剪区域

	void SetCellClassName(BeString& name);
	void EnableSort(BOOL bSort);
	void EnableExchangePos(bool benbale);
	bool IsExchangePos() const;
	TableHeaderNodeCell* HitTestCell(POINT pt);
	TableHeaderNodeCell* HitTestCellLine(POINT pt, BOOL isTransposition);

	std::shared_ptr<CNodeData> CreateThisColNodeData();
	void OnDrawTitleCellText(ISurface* pSurface, RECT rcCell, COLORREF textColor, UINT textAlignFlag, int dx = 0, int dy = 0);

	virtual BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam);
};

// 表头结构对象
class UI_EXP CContainTitleUI : public CScrollAreaUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CContainTitleUI)
  protected:
	std::vector<std::shared_ptr<TableHeaderNodeCell>> m_vecHeaderInfo; // 列信息数组
	std::vector<int> m_vecFilterRs;                                    // 可见的过滤结果
	std::shared_ptr<CControlUI> m_pDefEditorUI;                        // 默认全局编辑框,如果需要为某一列指定自己的编辑控件。可在列中设定

	COLORSTYLE m_titleBkColors;     // 标题栏背景颜色风格
	COLORSTYLE m_titleTextColors;   // 标题栏文本颜色风格
	COLORSTYLE m_gridColors;        // 网格线颜色风格
	COLORSTYLE m_LineNumTextColors; // 行号文本颜色风格
	COLORREF m_crMoveCol;           // 移动行背景色
	PenType m_gridlineStyle;        // 网格线风格
	GridFillMode m_gridFillMode;    // 网格填充风格
	GFont* m_pTitleFont;            // 标题字体
	int m_nTrackWidth;              // 跟踪时的尺寸
	int m_nTrackPosX;               // 跟踪的位置
	int m_nTrackCol;                // 调整宽度原始状态

	int m_nHighLightCol;  // 高亮列索引
	int m_nLastSelectCol; // 上一次选中列索引

	TableHeaderNodeCell* m_pDragColCell;
	TableHeaderNodeCell* m_pSortCell;

	UINT m_uTitleHitFlag; // 鼠标状态标志
	int m_nLeadWidth;     // 前导宽度
	int m_nTitleHeight;   // 标题高度
	int m_FixColumCount;  // 表格表头固定功能,默认-1，无固定操作.

	int m_nMoveSourceCol; // 移动列索引
	int m_nMoveTargetCol; // 移动目标列索引

	bool m_bChangeWidth; // 调整列宽使能

	bool m_bTransposition; //  行列转置

	UINT m_uColBar; // 列增长方向滚动条
	UINT m_uRowBar; // 行增长方向滚动条

  public:
	CContainTitleUI();
	~CContainTitleUI();

	COLORREF GridLineColor() const;

	BOOL IsFixColum(int col) const;
	int SetColumFilterList(std::vector<int>& rs); // 设定可现实行的索引列表
	void ClearColumFilterList();                  // 恢复原状
	PenType GetGridLineStyle() const;
	void SetGridLineStyle(PenType penStyle);     // 设置网格线风格
	void SetMovingColor(COLORREF cr);            // 设置移动列的背景色
	void SetGridFillMode(GridFillMode fillmode); // 设置网格填充风格，行填充，列填充，单元格填充
	void SetLeadWidth(int nWidth);               // 设置容器左侧边宽度
	int GetLeadWidth() const;
	int GetColumWidthSum() const;     // 获得标题栏的总宽度
	int TitleHeight() const;          // 标题高度
	void SetTitleHeight(int h);       // 设置标题高度
	void SetFixColCount(int c);       // 设置前缀固定行数量
	UINT TextAlign(UINT nCol) const;  // 获得列文本对齐方式
	int GetColWidth(UINT nCol) const; // 获得列宽

	UINT GetRowScrollBarTypeID() const; // 获得行增长方向的滚动条类别。当表格行列转置时，用来分别滚动条行为

	UINT GetColScrollBarTypeID() const; // 获得列增长方向的滚动条类别。当表格行列转置时，用来分别滚动条行为

	// colum impl
	int GetColumPos(int col) const;                 // 获得数据排序后的真实索引
	TableHeaderNodeCell* GetColumn(int ncol) const; // 获得标题栏单元格对象
	void SwapTitleColum(int c1, int c2);            // 交换列
	void MoveColumPos(int col, int ins_col);        // 移动列到ins_col位置
	void SetTitleFont(GFont* font);                 // 设置标题栏字体

	BOOL GetColumCellXBound(int col, int& x1, int& x2) const;
	int ColumnCount() const;              // 获得实际标题栏列总数
	int VisableColumnCount() const;       // 获得可见标题栏列总数
	void ClearColumn(BOOL bErase = TRUE); // 清空所有列
	void RemoveColum(UINT nCol);          // 删除指定列, nCol表示一级表头
	int SetColumns(std::vector<std::shared_ptr<TableHeaderNodeCell>>& titlelist);
	int InsertColumn(int nCol, std::shared_ptr<TableHeaderNodeCell> titleCell);
	int AppendColumn(std::shared_ptr<TableHeaderNodeCell> titleCell);

	int FindColumnIndexByName(BeString& name) const; // 根据名称id查询列号

	int GetColumnIndexByName(LPCTSTR szID) const; // 根据名称获得索引
	void SetColumnName(int nCol, LPCTSTR szID);   // 设置列字符ID
	void SetColWidth(UINT nCol, SizeValue value); // 设置列宽


	void SetEditorUI(std::shared_ptr<CControlUI> pEditor);                // 设置全局的输入编辑控件
	void SetColumEditorUI(int nCol, std::shared_ptr<CControlUI> pEditor); // 设置列编辑ui

	BOOL JumpViewCol(int index, BOOL bLeft); ///< 滚动到指定索引列

	// 子类重载接口列表
	virtual void OnReLayout();
	virtual void OnChangeHeaderColWidth();
	virtual void OnInsertColumn(int ncol, int sum);
	virtual void OnDeleteColumn(int ncol, int sum);
	virtual void OnSortColum(int ncol, OrderByType ordertype, DataType sortType, BOOL bNoCase);
	virtual void OnPaintMovingColum(int ncol, int dx, ISurface* pSurface, RECT* lpUpdate);

	void ChangeThemeColors(int theme) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | title-height <br/>设置标题栏高度  | title-height="30"	    |
	 * | fixcol <br/>固定列索引  | fixcol="2"	    |
	 * | grid-line <br/>网格线风格  | 取值：solid , dot , dash , dash-dot , dash-dot-dot	    |
	 * | grid-type <br/> 单元格选中模式 | 四种模式：行选中，列选中，单元格选中，无选中。取值:row , col, cell, none   |
	 * | grid-colors <br/>网格线颜色  | 	    |
	 * | title-back-colors <br/>标题栏背景颜色  | 	    |
	 * | title-text-colors <br/>标题栏文本颜色  | 	    |
	 * | column-resize-enable <br/>列宽可调整  | 	column-resize-enable="true"    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
	void OnParseItemData(XMLItem* pNode) override;
	void OnControlSize() override;
	BOOL OnNcHitTest(POINT pt) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonCliked(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	int LayoutAdaptWidth(int expH) override;

	CControlUI* HitTestControl(POINT pt) override;

  protected:
	void GetColumnAreaRect(int col, RECT* rc); // 获得列显示区域,包含了title高度
	int PtInColumn(int x, int y);
	int PtInTargetColumn(int x, int y);
	int GetFixColumWidth() const;
	BOOL PtInTitle(POINT pt) const;
	TableHeaderNodeCell* GetAbsColumn(int ncol) const; // 获得标题栏单元格对象
	BOOL MoveCol(BOOL bPrev, BOOL bRefresh);           // 移动列
  private:
	UINT hitTestColLine(POINT pt) const;
	TableHeaderNodeCell* hitTestHeaderCell(POINT pt) const;
	TableHeaderNodeCell* hitTestHeaderCellLine(POINT pt) const;
};



}

#endif