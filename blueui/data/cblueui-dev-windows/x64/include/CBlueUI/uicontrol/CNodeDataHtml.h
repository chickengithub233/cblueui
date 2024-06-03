#ifndef CBLUEUI_CNODEDATAHTML_INCLUDED_
#define CBLUEUI_CNODEDATAHTML_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory>
#include "core/CCoreBasePro.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "platform/GFont.h"
#include "CNodeData.h"

namespace BUI {

class UI_EXP LabelItem
{
  public:
	LabelItem();
	~LabelItem();

  public:
	BeString text;
	BeString href;
	COLORREF color;
	SIZE sz;
	int font_height;
	int font_style;
	BOOL isNewLine;
	GFont* hFont;
};

struct HtmlItemDataStyle
{
	GFont* font;
	COLORREF textColor;
	int font_style;
	int font_height;
};

/**
 * @brief HTML文本
 *
 */
class UI_EXP CNodeHtmlTextData : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeHtmlTextData)
  protected:
	std::vector<std::shared_ptr<LabelItem> > m_Labels;
	UINT m_align;
	BOOL m_bWordWrap;
	int m_dataindex;
	BOOL m_select_font_when_draw; // 绘制时选择字体
  public:
	CNodeHtmlTextData();
	~CNodeHtmlTextData();
	void SetAlign(UINT align);
	void Clear(BOOL bErase = TRUE);
	void SetSelectFontWhenDraw(BOOL select); // 绘制时选择字体
	void Addlabel(LPCTSTR szText, COLORREF color, int size, GFont* font, LPCTSTR szLinkref = NULL);
	void SetItemText(int index, BeString szText);
	void SetHtmlText(const TCHAR* htmltext, GFont* font = NULL);
	void SetDataIndex(int i);
	int LabelCounts() const;
	int FindItem(LPCTSTR text, BOOL noCase = FALSE) const; // noCase:TRUE 不区分大小写。缺省:区分大小写
	void OnParseHtmlItemData(XMLItem* pNode, HtmlItemDataStyle style);
	void OnParseHtmlData(XMLItem* pNode, GFont* font, COLORREF textColor);

	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;

	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;       // 传入编辑器显示的文本. node   --> editor
	void EditorToNodeData(const BeString& str) override; // 接收编辑器传来的数据. editor --> node

	void GetValueData(DataType type, ValuePack& sortData) override; // 获取数据值,也可用于排序
	void OnParseNodeData(XMLItem* pNode, CControlUI* parent) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;
	void OnTranslateLanguage() override;

  protected:
	virtual void OnRefreshHtml();

	SIZE AdaptSize() const;
	int AdaptFixedWidth(int w) const;

	int GetLineHeight(int s, int e) const;
};


}



#endif