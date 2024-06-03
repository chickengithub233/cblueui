#ifndef CBLUEUI_CTABLEMODEL_BLXDY_INC_H_
#define CBLUEUI_CTABLEMODEL_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <memory>
#include <vector>
#include "core/CCoreBasePro.h"
#include "core/SignalSlotX.hpp"
#include "CTableViewUI.h"
#include "CNodeData.h"

#include <functional>
#include <string>

namespace BUI {

typedef std::function<GImageIconInfo*()> GetGImageIconInfoFunc; // 图标选取函数
typedef std::function<COLORREF()> GetTextUserColorFunc;         // 自定义文本颜色选取函数。不设置则采取默认
typedef std::function<int()> GetIntFunc;                        // 整数选取函数

/* text of data and icon of text*/
class UI_EXP CNodeDataImageFunc : public CNodeData
{
  public:
	CNodeDataImageFunc(GetGImageIconInfoFunc func_img = nullptr, GetTextUserColorFunc func_color = nullptr);
	virtual ~CNodeDataImageFunc();

	/* CNodeData method:*/
	void GetPrintText(BasicStringBufferA& str) override;
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;

  protected:
	void DrawPrefixTextW(ISurface* pSurface, RECT rcCell, COLORREF textColor, UINT textAlignFlag, LPCWSTR text, int length);

	void DrawPrefixTextA(ISurface* pSurface, RECT rcCell, COLORREF textColor, UINT textAlignFlag, LPCSTR text, int length);

  protected:
	GetGImageIconInfoFunc m_func_img;
	GetTextUserColorFunc m_func_text_color;
};

/* text of data and icon of text*/
class UI_EXP CNodeDataTextQuote : public CNodeDataImageFunc
{
  public:
	CNodeDataTextQuote(std::string& str, GetGImageIconInfoFunc func_img = nullptr, GetTextUserColorFunc func_color = nullptr);
	virtual ~CNodeDataTextQuote();

	/* CNodeData method:*/
	void GetPrintText(BasicStringBufferA& str) override;
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;

	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;

  protected:
	std::string& m_text;
};

/* text of gradient background*/
class UI_EXP CNodeDataTextGradientQuote : public CNodeDataTextQuote, public GradientRoundRect
{

  public:
	CNodeDataTextGradientQuote(std::string& str, GetGImageIconInfoFunc func_img = nullptr, GetTextUserColorFunc func_color = nullptr);
	~CNodeDataTextGradientQuote();
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
};

/* int num of data*/
class UI_EXP CNodeDataIntQuote : public CNodeDataImageFunc
{
  public:
	CNodeDataIntQuote(int& value, GetGImageIconInfoFunc func_img = nullptr, GetTextUserColorFunc func_color = nullptr);
	virtual ~CNodeDataIntQuote();

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;

  public:
	int& m_value_int;
};

/* float of data*/
class UI_EXP CNodeDataDoubleQuote : public CNodeDataImageFunc
{
  public:
	CNodeDataDoubleQuote(double& value, int& precision, GetGImageIconInfoFunc func_img = nullptr, GetTextUserColorFunc func_color = nullptr);
	virtual ~CNodeDataDoubleQuote();

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;

  public:
	double& m_value_double;
	int& m_value_precision;
};






}
#endif