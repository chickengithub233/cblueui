#ifndef CBLUEUI_CTREEDATACELL_INCLUDED_
#define CBLUEUI_CTREEDATACELL_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNodeCell.h"

namespace BUI {

// 树单元格容器类
class UI_EXP CTreeRowCell
{
  public:
	CTreeRowCell();
	~CTreeRowCell();

	UINT Size() const;
	void Clear();

	void AppendDataCell(std::shared_ptr<CNodeSpanCell>& cell);
	BOOL InsertDataCell(int column, std::shared_ptr<CNodeSpanCell>& cell);
	void RemoveDataCell(int column);

	CNodeSpanCell* GetSubCell(int col);
	void OnAllocNodeCell(int nCol, int count);
	void OnDeleteCol(int nCol, int count);

	void OnNodeCollapsed();
	void OnSetNodeRect(int col, int x, int y, int w, int h);
	void OnDrawTreeCell(int col, ISurface* pSurface, RECT rcCell, COLORREF textColor, UINT textAlignFlag);

	// 设置单元格的选中状态，全部选中
	BOOL SetCellSelected(int start, int end, BOOL bSelt);

  protected:
	std::vector<std::shared_ptr<CNodeSpanCell> > m_rowOfcells;
};

enum MatchMask
{
	zero_match         = 0x00,
	search_mask_shift  = 1,
	default_mask_shift = 1 << 1
};

class UI_EXP CTreeModelNode : public CheckBoxMode, public CTreeRowCell
{
  public:
	RECT rcRow;
	RECT rcExpand;     // 折叠按钮有效区域
	BOOL bCollapsed;   // 是否折叠 true 折叠
	UINT uflagVisable; // 可见性标志
	int context_x;     // 保留去掉
	int row_y;         // 行y坐标

	int depth;         // 深度
	int LineNumber;    // 行号
	ItemState m_state; // 状态

	CTreeModelNode* prev; // 选中态链表
	CTreeModelNode* next;

	CTreeModelNode* parent;
	CTreeModelNode* firstChild;
	CTreeModelNode* lastChild;
	CTreeModelNode* prevSibling;
	CTreeModelNode* nextSibling;

	std::shared_ptr<IActionNotify> clickAction; // 点击时执行的动作
  public:
	CTreeModelNode();
	~CTreeModelNode();

	/**
	 * @brief   设置集合竞价右键菜单组显示类型
	 * @return  void
	 * @param show  <table>
	 * <tr><th>Date       <th>Version <th>Author  <th>Description
	 * <tr><td>2019-11-17 <td>1.0     <td>wangh     <td>内容
	 * </table>
	 */
	void SetCellVisable(BOOL show);
	/**
	 * @brief func是一个普通成员函数
	 *
	 * @param a [in] param a
	 * @param b [in, out] param b
	 * @param c [out] output
	 * @return int
	 * @retval
	 * 1 : result1；
	 * 2 : result2；
	 * @see f()
	 */
	void SetCellMatched(BOOL matched);

	void SetClickAction(std::shared_ptr<IActionNotify> action);
	void SetExpandRect(int x, int y, int w, int h);
	BOOL PtInExpandRect(POINT pt);

	BOOL IsVisable(UINT mask) const;

	int NodeDepth() const;

	void OnTranslateLanguage();

	inline BOOL IsHasChild() { return firstChild != NULL; }
};

/// 树状控件模型属性标志
enum TreeViewModelFlags
{
	TVMF_ShowCheckBox      = 1 << 0, ///< 显示复选框
	TVMF_ExpandBtnTriStyle = 1 << 1, ///< 折叠按钮风格为三角形
	TVMF_ShowTreeLineStyle = 1 << 2, ///< 显示层级线条
	TVMF_TreeNodeMovable   = 1 << 3, ///< 节点可被移动重排
};

/**
 * @brief 树状控件模型
 *
 */
class UI_EXP CTreeViewModel : public MouseDragHelper
{
  public:
	CTreeViewModel();
	~CTreeViewModel();

	/**
	 * @brief 设置树模型标志
	 *
	 * @param style 取@link TreeViewModelFlags @endlink组合值
	 * @param op  ADD_FLAGS(添加属性) REMOVE_FLAGS(删除属性)
	 */
	void ModifyTreeViewModelFlags(UINT style, UINT op = ADD_FLAGS, BOOL bRefresh = FALSE);
	UINT IsHasTreeViewModelFlags(UINT flags) const;
	UINT GetTreeViewModelFlags() const;

	void ChangeModelThemeColors(int theme);
	void SetLevelLineColor(COLORREF color);

	int GetRowHeight() const; // 数据行高度
	void SetRowHeight(int h); // 设置行高度
	int GetNodeChildCount(CTreeModelNode* node);
	void SetLevelLineType(PenType type); // 设置层级线风格，虚线、实线
	void SetItemRoundRadius(RoundRectRadius& radius);
	void SetItemRoundSize(int rx, int ry);
	void SetSpacing(int space);
	void SetExpandSize(int size);
	void SetChildOffsetX(int size);
	void SetCheckBoxSize(int size);

	void SetSearchMode(BOOL bSearch);
	void SetCheckBoxImage(SelectState state, GImageIconInfo* img); // 设置复选框图案
	void MatchTextNode(LPCTSTR str);                               // 搜索匹配的节点

	BOOL Expand(CTreeModelNode* hItem, BOOL bExpand);  // 设定项是否展开 true 展开
	BOOL IsExpand(CTreeModelNode* hItem) const;        // 判断定项是否展开
	BOOL IsInVisibleView(CTreeModelNode* hItem) const; // 是否在可视区域内
	void Clear(BOOL bErase = TRUE);                    // 删除此函数将删除节点的所有子节点
	BOOL RemoveItem(CTreeModelNode* hItem);

	BOOL IsTreeEmpty() const;

	CTreeModelNode* RootNode();
	CTreeModelNode* InsertTreeNode(CTreeModelNode* parent, CTreeModelNode* prev, std::shared_ptr<CNodeSpanCell> item);

	void PrintToFile(FILE* fp, LPCSTR space_prefix = " ") const;

	CTreeModelNode* SelectItem(CTreeModelNode* item);
	CTreeModelNode* SetHighLightItem(CTreeModelNode* item);
	CTreeModelNode* GetTreeLeafEntry(CTreeModelNode* node);
	CTreeModelNode* GetTreeUpEntry(CTreeModelNode* node);
	CTreeModelNode* MoveTreeNodeStep(CTreeModelNode* node, int step);
	CTreeModelNode* PtInTreeNode(int dy);
	CTreeModelNode* GetRowNode(int row) const;
	CNodeData* GetNodeData(int row, int col) const;

  protected:
	void OnTranslateLanguage();
	void SetAllSelectState(bool state); // 重置所有节点的选中状态
	UINT GetRowCount() const;
	void ReBuildDepth();
	void DrawTreeCell(CNodeSpanCell* pCell, RECT rcView, COLORREF textColor, UINT textAlignFlag);
	BOOL PtInTreeItemCheckBox(CTreeModelNode* hItem, POINT pt);
	BOOL PtInExpandBtn(CTreeModelNode* hItem, POINT pt);
	void SetTreeItemCheckBox(CTreeModelNode* hItem, SelectState state);
	void SetChildItemCheckState(CTreeModelNode* hchild, SelectState nstate);
	void DrawTreeItem(ISurface* pSurface, RECT* lpUpdate, CTreeModelNode* node, COLORREF color, int dx = 0);
	void DrawTreeDataCell(ISurface* pSurface, int paintState, RECT* lpUpdate, CTreeModelNode* node, RECT rcCell, COLORREF color);

	void DrawTreeItemLevelLine(ISurface* pSurface, RECT& rcView, CTreeModelNode* node, COLORREF color, int fontHeight, int firstRow, int scroll_x, int scroll_y);

	void RefreshTreeNode(CTreeModelNode* node1, CTreeModelNode* node2, int base_x, int width);
	BOOL GetTreeNodeCellYBound(CTreeModelNode* node, int& y1, int& y2) const;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | treemodel-flags<br/>树模型功能标志位   |	"-"前缀代表删除属性<br/>如 treemodel-flags="showCaption,-EnableZoom"		  |
	 * |                                 | ShowCheckBox :显示复选框 	    |
	 * |                                 | ExpandBtnTriStyle :折叠按钮风格为三角形	    |
	 * |                                 | ShowTreeLine :显示层级线条	    |
	 * |                                 | TreeNodeMovable :节点可被移动重排    |
	 * |                                 |     |
	 * | sub-line-offset <br/>子节点层级线偏移量         | sub-line-offset="15"	    |
	 * | interval <br/>元素间隔             | interval="5"	    |
	 * | rowHeight <br/>行高               | rowHeight="25"	    |
	 * | line-type-level <br/>层级画笔风格  | solid, dot, dash, dash-dot, dash-dot-dot   |
	 * | cursel <br/>设置当前选中项         | cursel="行号"		    |
	 */
	void ShellModelAttribute(const BeString& szName, const BeString& szText);

	/* this override methods:*/
	virtual void OnInvalidateRect(RECT* rc, BOOL bClient) = 0;

	virtual int GetModelColumCount() = 0;

	virtual POINT GetScrollOffsetPoint() = 0;

	virtual void OnSelectItem(CTreeModelNode* item) = 0;

  private:
	void DoPrintToFile(FILE* fp, CTreeModelNode* hItem, LPCSTR prefix, int depth) const;
	void FreeTreeItem(CTreeModelNode* hItem);

	SelectState GetChildItemCheckState(CTreeModelNode* hItem); // 获得子节点的选中状态

	CTreeModelNode* AllocTreeObject(); // 分配节点

	void ReclaimTreeObject(CTreeModelNode* entry); // 回收节点

	void ItemMatched(CTreeModelNode* hItem);

	void ItemChildMatched(CTreeModelNode* hItem);

	void BuildDepth(CTreeModelNode* node, int depth, UINT& row_i);

	void BuildVisibleList(CTreeModelNode* node); // 重置可视顺序链表

	CTreeModelNode* FindTreeNodeByLineNum(CTreeModelNode* node, int row) const;

  protected:
	CTreeModelNode m_root;
	std::deque<CTreeModelNode*> m_alloc_node_buffer; // 节点内存池
	int m_nPoolSize;
	UINT m_nRowCount;
	UINT m_nTotolCount;
	int m_nItemHeight;    // 项的高度
	int m_nInterval;      // 元素之间的间隔
	int m_nExpandWidth;   // 扩展线宽度
	int m_nCheckBoxSize;  // 选中和扩展按钮的大小
	int m_nSubLineOffset; // 子节点线偏移量

	UINT m_uTreeModelFlags; // 功能标志位
	UINT m_uMatchMask;      // 匹配掩码
	PenType m_levelLineType;
	RoundRectRadius m_RoundRadiusHighlight; // 选中高亮圆角尺寸
	GImageIconInfo* m_pImgCheck[3];         // 复选框绘制图标(依次:未知，选中，未选中)

	CTreeModelNode* m_hBeginShowNode; // 可见首行
	CTreeModelNode* m_hSelectedItem;  // 当前选中项
	CTreeModelNode* m_hHovenItem;     // 当前热点项

	CTreeModelNode* m_hDropItem; // 拖拽目标节点

	MouseDragHelper m_dragMgr; // 节点移动管理
	MouseHoverState m_expandHover;

	COLORSTYLE m_treeLevelLineColors; // 层级线颜色
	COLORSTYLE m_ChkboxColors;        // 复选框颜色风格
};


} // #namespace

#endif
