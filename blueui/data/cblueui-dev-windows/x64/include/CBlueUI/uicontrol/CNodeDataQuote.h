
#ifndef CBLUEUI_CNODEDATAQUOTE_0BDC91A2_2B9AC59FEE36_INCLUDED_
#define CBLUEUI_CNODEDATAQUOTE_0BDC91A2_2B9AC59FEE36_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <memory>
#include "CNodeData.h"

namespace BUI {

/**
 * @brief 图标和文本布局工具类
 *
 */
class UI_EXP CTextLayout
{
  public:
	CTextLayout();
	~CTextLayout();

	void SetControlIcon(GImageIconInfo* icon); ///< 设置图标
	void SetTextAlign(UINT formate);           ///< 设置图片和文本组合整体的对齐方式
	UINT GetTextAlign() const;
	BOOL IsHasTextAlign(UINT bits) const;

	void DrawLabel(ISurface* pSurface, RECT rcView, int paintStates, LPCTSTR text, COLORREF color, RECT* lpUpdate);

	SIZE GetLayoutStringSize(const GFont* font, LPCTSTR str);

	GImageIconInfo* GetGImageIconInfo() const;

  protected:
	UINT m_nTextAlign;          // 文本对齐方式
	GImageIconInfo* m_iconInfo; // 图标
	int m_icon_interval;        // 图标和文本的间隔
};

/**
 * @brief 引用类型的图标
 *
 */
class UI_EXP CNodeDataImageQuote : public CNodeData
{
  public:
	CNodeDataImageQuote(GImageIconInfo*& normal);
	~CNodeDataImageQuote();
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;

	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;

  protected:
	GImageIconInfo*& m_image;
};

/* Quote BeString of data**/
class UI_EXP CNodeDataTextLayoutQuote : public CNodeData
{
  public:
	CNodeDataTextLayoutQuote(CTextLayout& text_layout, BeString& text);
	~CNodeDataTextLayoutQuote();
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;

	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;

  protected:
	CTextLayout& m_textlayout;
	BeString& m_text;
};


} // #namespace




#endif
