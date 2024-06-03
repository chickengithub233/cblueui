
#ifndef CBLUEUI_CDATACELL_DDVU35K_FQX03_481VQ_45P_0VD_INCLUDED_
#define CBLUEUI_CDATACELL_DDVU35K_FQX03_481VQ_45P_0VD_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <memory>
#include "core/CCoreBasePro.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "uicontrol/CControlUI.h"
#include "graphics/GImage.h"
#include "CNodeData.h"

namespace BUI {


/*
 * 复选框状态属性
 */
class UI_EXP CheckBoxMode
{
  public:
	CheckBoxMode();
	~CheckBoxMode();

	void SetCheckState(SelectState state);
	SelectState CheckState() const;

	void SetCheckBoxRect(int x, int y, int w, int h);
	BOOL PtInCheckBox(POINT pt) const;
	RECT CheckBoxRect() const;
	void SetCheckBoxAction(std::shared_ptr<IActionNotify>& action);

  protected:
	RECT m_rcCheckBox;
	SelectState m_checkState;
	std::shared_ptr<IActionNotify> m_checkBoxAction; // 选择时执行的动作
};

/*
 * 匹配类型
 */
enum MATCH_TYPE
{
	MT_NONE, // 不匹配
	MT_NUM,  // 按数值范围匹配
	MT_TEXT, // 按文本匹配
	MT_ENUM  // 枚举匹配
};

/*
 * 匹配信息类
 */
class UI_EXP MatchFeatures
{
  public:
	MatchFeatures();
	~MatchFeatures();

	void SetMatchType(MATCH_TYPE type);
	MATCH_TYPE MatchType() const;

	void SetMatchText(BeString& str);
	BeString& MatchText();

	void SetMatchNumRange(int64_t mini, int64_t maxi);
	void GetMatchNumRange(int64_t& mini, int64_t& maxi) const;

  protected:
	MATCH_TYPE m_type;
	int64_t m_nRangeMin; // 数值匹配范围
	int64_t m_nRangeMax;
	BeString m_textMatch; // 文本匹配
};

struct TransmitDataObject
{
	std::shared_ptr<CNodeData> data; // 数据节点
	BeString text;
};

UI_EXP void InitItemState(ItemState& state);

/**
 * @brief 普通单元格
 *
 */
class UI_EXP CNodeCell
{
  public:
	RECT m_rcCell;
	ItemState m_state;
	BeString m_nameid;                       // 唯一标识
	IEventHandler* m_notifyHandler;          // 事件通知对象
	std::shared_ptr<CNodeData> m_rawdata;    // 数据节点
	std::shared_ptr<IActionNotify> m_action; // node状态变化触发事件.包含悬停，选中
	syntax_info* m_cmd_ast;                  // 自定义协议脚本格式语法树
  public:
	CNodeCell();
	CNodeCell(std::shared_ptr<CNodeData> valuedata);
	virtual ~CNodeCell();

	void BindAction(std::shared_ptr<IActionNotify> action);
	std::shared_ptr<IActionNotify> ActionOfNode() const;
	void DoNodeAction() const;

	void SetSyntaxAst(LPCTSTR str_script); // 设置内置脚本代码

	void SetName(BeString id);
	BeString& Name();

	void OnDrawNodeCell(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL);
	void SetNodeData(std::shared_ptr<CNodeData> valuedata);

	void AddNodeData(std::shared_ptr<CNodeData> valuedata, int w = 0, int h = 0, SizeMode stw = AdaptFill, SizeMode sth = AdaptFill);
	void InsertNodeData(int pos, std::shared_ptr<CNodeData> valuedata, int w = 0, int h = 0, SizeMode stw = AdaptFill, SizeMode sth = AdaptFill);

	void SetNotifyHandler(IEventHandler* notify); // 设置消息通知处理者
	BOOL NotifyMsg(UINT message, WPARAM wp, LPARAM lp);
	void NeedUpdateUI();     // 刷新单元格ui
	void NeedUpdateHostUI(); // 刷新宿主UI

	void ShellNodeCellAttribute(const BeString& szName, const BeString& szText); // 属性设置

	ItemState& GetNodeState();

	void Clear();

	BOOL PtInCell(POINT pt);
	void SetRect(int x, int y, int w, int h);

	RECT CellRect() const;

	std::shared_ptr<CNodeData>& GetNodeData();
};

/* 带有checkbox功能的单元格*/
class UI_EXP CNodeSpanCell : public CNodeCell
{
  public:
	CNodeSpanCell();
	CNodeSpanCell(std::shared_ptr<CNodeData> valuedata);
	~CNodeSpanCell();
	void SetMergeSpanYOffset(int dy);

	// void  OnDrawNodeCell(ISurface* pSurface, RECT rcCell, COLORREF textColor, UINT textAlignFlag);
  public:
	// int m_span_ver_index; // 有合并功能的单元格:垂直跨度的偏移量
	// int m_span_ver_count; // 合并单元格的数量
};

/* 带有checkbox功能的单元格*/
class UI_EXP CCheckBoxCell : public CNodeCell, public CheckBoxMode
{
  public:
	CCheckBoxCell();
	~CCheckBoxCell();
};




} // #namespace

#endif
