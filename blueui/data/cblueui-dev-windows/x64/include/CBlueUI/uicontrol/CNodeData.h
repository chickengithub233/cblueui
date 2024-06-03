
#ifndef CBLUEUI_CNODEDATA_0BDC91A2_2B9AC59FEE36_INCLUDED_
#define CBLUEUI_CNODEDATA_0BDC91A2_2B9AC59FEE36_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <memory>
#include "core/CCoreBasePro.h"
#include "core/CCoreEventHandler.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "cstring/StringBufferBasic.h"
#include "graphics/GImageIconInfo.h"
#include "graphics/GStyleLine.h"
#include "graphics/GSurface.h"
#include "function/SettingInfo.h"

namespace BUI {

class CControlUI;

enum OrderByType
{
	OrderByASC,  ///< 升序(A~Z)
	OrderByDESC, ///< 降序(Z~A)
	OrderByNONE  ///< 初始顺序
};

enum DataType
{
	DataNum,   ///< 整数
	DataFloat, ///< 浮点数
	DataText,  ///< 文本
};

/// 值包装器
struct ValuePack
{
	long long lNum;
	double fNum;
	BeString sText;
};

/// 排序数据
struct SortData
{
	ValuePack sort_value;
	int sort_i;
};

extern bool CompareValueLong(SortData& v1, SortData& v2);
extern bool CompareValueDouble(SortData& v1, SortData& v2);
extern bool CompareValueText(SortData& v1, SortData& v2);
extern bool CompareValueTextNoCase(SortData& v1, SortData& v2);

/**
 * @brief 排序功能和属性的封装
 *
 */
class UI_EXP CSortContainer
{
  public:
	CSortContainer();
	~CSortContainer();

	void AppendSortData(SortData& data);
	void DeleteSortData(int sort_i);
	void ClearSortData();
	const SortData& At(UINT i) const;

	void SetOrderType(OrderByType order);
	void SetSortType(DataType dtype, BOOL nocase = FALSE);

	void SetPauseStatus(BOOL bPause);
	DataType GetSortDataType() const;

	void DoSort();

  protected:
	void NeedReSort();

  protected:
	BOOL m_bPauseSort;       // 暂停排序
	BOOL m_bNeedReRost;      // 是否需要重排
	OrderByType m_OrderType; // 排序方式
	DataType m_SortType;     // 排序数据类型
	BOOL m_bNoCase;
	std::vector<SortData> m_sortdata;
};

struct ElementLayout
{
	int nWidth_;
	int nHeight_;
	SizeMode nWidMode_;
	SizeMode nHeiMode_;
	SIZE szAdapt_;
};

/**
 * @brief 可视化的数据结构，包含数据交互和绘制功能
 *
 */
class UI_EXP CNodeData : public ICommitTarget
{
	DECLARE_DYNAMIC_OBJ_CLASS_BASE(CNodeData)
  public:
	CNodeData();
	virtual ~CNodeData();

	virtual int ChildCounts();
	virtual std::shared_ptr<CNodeData> GetChildNode(int pos);

	virtual void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT align, PathTransInfo* clipborderpath = NULL);

	/// 获得打印字符串
	virtual void GetPrintText(BasicStringBufferA& str);
	/// 传入编辑器显示的文本. node   --> editor
	virtual void NodeDataToEditor(BeString& str);
	/// 接收编辑器传来的数据. editor --> node
	virtual void EditorToNodeData(const BeString& str);
	/// 比较内容文本
	virtual int Compare(LPCTSTR text, BOOL ignore_case = FALSE);

	/// 获取数据值,也可用于排序
	virtual void GetValueData(DataType type, ValuePack& sortData);
	/// 设置布局信息
	virtual void SetElementLayout(int w, int h, SizeMode stw, SizeMode sth);
	/// 获得布局信息
	virtual void GetElementLayout(ElementLayout& ele);
	/// 获得布局自适应宽度
	virtual UINT GetNodeAdaptWidth(const GFont* font);
	virtual UINT GetNodeAdaptHeight(const GFont* font);

	/// 保存控件属性
	virtual void OnSaveConfigSetting(XMLItem* node);
	virtual void OnParseNodeData(XMLItem* pNode, CControlUI* parent);
	virtual void ShellNodeDataAttribute(const BeString& szName, const BeString& szText);
	/// 设置可视化区域
	virtual void SetClipRect(RECT& rc);

	/// 翻译
	virtual void OnTranslateLanguage();
	/// 定位控件
	virtual CControlUI* HitTestCellControl(POINT pt);
	virtual CControlUI* FindCellControl(LPCTSTR name);
	/// 添加子node
	virtual BOOL AddChildNodeData(std::shared_ptr<CNodeData> valuedata);
	virtual BOOL InsertChildNodeData(int pos, std::shared_ptr<CNodeData> valuedata);
	virtual BOOL RemoveChildNodeData(int pos);

	void StorageNodeAdaptWidth(UINT size);
	void StorageNodeAdaptHeight(UINT size);

	void DrawNodeTextW(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT align, LPCWSTR text, int length);
	void DrawNodeTextA(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT align, LPCSTR text, int length);
	/* ICommitTarget override methods:*/
	void OnSummitTarget(FourCode four_code, LPCTSTR data) override;

  protected:
	std::shared_ptr<ElementLayout> m_obj_layout;
};

/**
 * @brief Create a Node Data object
 *
 * @param typeName 预留参数
 * @param desClassName 预留参数
 * @param className 类名称
 */
UI_EXP CNodeData* CreateNodeData(const TCHAR* typeName, const TCHAR* desClassName, const TCHAR* className);

/**
 * @brief 可视化节点列表，包含xyz三个方向的布局。
 *
 */
class UI_EXP CNodeDataLists : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataLists)
  public:
	CNodeDataLists(LayoutBoxType type = LayoutBoxType::HORIZONTAL);
	virtual ~CNodeDataLists();

	void SetLayoutType(LayoutBoxType type);

	/// 设置数据的索引，排序的时候会用改索引下的nodedata进行排序
	void SetValueIndex(int index);
	/// 两个布局对象的间隔
	void SetLayoutInterval(int spacer);
	/// 设置内边距
	void SetPadding(int left, int top, int right, int bottom);

	/* CNodeData method:*/
	int ChildCounts() override;
	std::shared_ptr<CNodeData> GetChildNode(int pos) override;

	void OnParseNodeData(XMLItem* pNode, CControlUI* parent) override;
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;

	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	int Compare(LPCTSTR text, BOOL ignore_case = FALSE) override;

	void GetValueData(DataType type, ValuePack& sortData) override;

	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;
	void OnTranslateLanguage() override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;
	CControlUI* HitTestCellControl(POINT pt) override;
	CControlUI* FindCellControl(LPCTSTR name) override;

	BOOL AddChildNodeData(std::shared_ptr<CNodeData> valuedata) override;
	BOOL InsertChildNodeData(int pos, std::shared_ptr<CNodeData> valuedata) override;
	BOOL RemoveChildNodeData(int pos) override;
	void RemoveAll();

	// void  EnableItem(int nIndex, BOOL bEnable);
	// void  VisableItem(int nIndex, BOOL bVisable);
	// void  Enable(BOOL bEnable);
	// void  Visable(BOOL bVisable);


  protected:
	void LayoutNodeLayered(RECT rcCell, ISurface* pSurface, int paintState, COLORREF textColor, UINT textAlign, PathTransInfo* clipborderpath);
	void LayoutNodeHor(RECT rcCell, ISurface* pSurface, int paintState, COLORREF textColor, UINT textAlign, PathTransInfo* clipborderpath);
	void LayoutNodeVer(RECT rcCell, ISurface* pSurface, int paintState, COLORREF textColor, UINT textAlign, PathTransInfo* clipborderpath);

  protected:
	int m_value_index;
	std::vector<std::shared_ptr<CNodeData>> m_nodes;
	LayoutBoxType m_boxType; // 布局方式
	int m_nInterval;         // 两个布局对象的间隔
	PaddingInfo m_padding;
};

/**
 * @brief 实色图形
 *
 */
class UI_EXP CNodeDataSolidColor : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataSolidColor)
  public:
	CNodeDataSolidColor();
	~CNodeDataSolidColor();

	void SetColor(const GColor& color);
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT align, PathTransInfo* clipborderpath = NULL) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	GColor m_solid_color;
};

/**
 * @brief 包含控件的可视化节点
 *
 */
class UI_EXP CNodeDataControl : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataControl)
  public:
	CNodeDataControl();
	CNodeDataControl(std::shared_ptr<CControlUI> ui, BOOL bDelega = TRUE);
	virtual ~CNodeDataControl();

	void SetControl(std::shared_ptr<CControlUI> ui, BOOL bDelega);

	/* CNodeData method:*/
	void NodeDataToEditor(BeString& str) override;

	void EditorToNodeData(const BeString& str) override;

	void GetValueData(DataType type, ValuePack& sortData) override;
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;

	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;
	void OnParseNodeData(XMLItem* pNode, CControlUI* parent) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

	CControlUI* HitTestCellControl(POINT pt) override;
	CControlUI* FindCellControl(LPCTSTR name) override;

	void SetClipRect(RECT& rc) override;

  protected:
	std::shared_ptr<CControlUI> m_data_ui;
};

/**
 * @brief 图片节点
 *
 */
class UI_EXP CNodeDataImage : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataImage)
  public:
	CNodeDataImage();
	CNodeDataImage(GImageIconInfo* normal);
	~CNodeDataImage();

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;
	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;

  protected:
	GImageIconInfo* m_image;
};

/* icon of data*/
class UI_EXP CNodeDataIconPrefix : public CNodeData
{
  public:
	CNodeDataIconPrefix();
	CNodeDataIconPrefix(GImageIconInfo* normal, COLORREF color);
	virtual ~CNodeDataIconPrefix();
	void SetTextStyle(GImageIconInfo* normal, COLORREF color);
	void SetFont(GFont* font);
	/* CNodeData method:*/
	// void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;

	// virtual void NodeDataToEditor(BeString& str) = 0;

	// virtual void EditorToNodeData(const BeString& str) = 0;

	// virtual void GetValueData(DataType type, ValuePack& sortData) = 0;

	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	void DrawPrefixText(ISurface* pSurface, RECT rcCell, COLORREF textColor, UINT textAlignFlag, LPCTSTR text, int length, PathTransInfo* clipborderpath = NULL);

  protected:
	GImageIconInfo* m_image;
	COLORREF m_textUserColor; // 自定义文本颜色。最高位0为无效，非0为有效
	GFont* m_font;            // 字体
};

/* text of data and icon of text*/
class UI_EXP CNodeDataText : public CNodeDataIconPrefix
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataText)
  public:
	CNodeDataText();
	CNodeDataText(BeString text);
	virtual ~CNodeDataText();
	void SetValue(BeString text);

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	int Compare(LPCTSTR text, BOOL ignore_case = FALSE) override;
	void GetValueData(DataType type, ValuePack& sortData) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;
	void OnSaveConfigSetting(XMLItem* node) override;

	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;
	void OnTranslateLanguage() override;

  protected:
	BeString m_text;
};

/* text align */
class UI_EXP CNodeDataTextAlign : public CNodeDataText
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataTextAlign)
  public:
	CNodeDataTextAlign();
	CNodeDataTextAlign(BeString text);
	virtual ~CNodeDataTextAlign();

	void SetAlign(UINT formate); ///< 设置图片和文本的对齐方式

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	UINT GetNodeAdaptWidth(const GFont* font) override;
	UINT GetNodeAdaptHeight(const GFont* font) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	SIZE GetLayoutStringSize(ISurface* pSurface, LPCTSTR str);

  protected:
	UINT m_nTextAlign; //  文本对齐方式
};

/* text of gradient background*/
class UI_EXP CNodeDataTextGradient : public CNodeDataText, public GradientRoundRect
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataTextGradient)
  public:
	CNodeDataTextGradient();
	CNodeDataTextGradient(BeString& text);
	~CNodeDataTextGradient();
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
};

/* image of gradient background*/
class UI_EXP CNodeDataImageGradient : public CNodeDataImage, public GradientRoundRect
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataImageGradient)
  public:
	CNodeDataImageGradient();
	CNodeDataImageGradient(GImageIconInfo* normal);
	~CNodeDataImageGradient();
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;
};

/* int num of data*/
class UI_EXP CNodeDataInt : public CNodeDataIconPrefix
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataInt)
  public:
	CNodeDataInt(int value = 0);
	virtual ~CNodeDataInt();
	void SetValue(int value);

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  public:
	int m_num;
};

/* float of data*/
class UI_EXP CNodeDataDouble : public CNodeDataIconPrefix
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataDouble)
  public:
	CNodeDataDouble(double value = 0.0);
	virtual ~CNodeDataDouble();
	void SetValue(double value);

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  public:
	double m_value;
};

/* color of data*/
class UI_EXP CNodeDataColor : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataColor)
  public:
	CNodeDataColor(COLORREF color = 0);
	virtual ~CNodeDataColor();
	void SetValue(COLORREF color);

	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  public:
	COLORREF m_color;
};

/* date of data. formate: yyyy-mm-dd*/
class UI_EXP CNodeDataDate : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataDate)
  public:
	CNodeDataDate(long ymd = 0);
	virtual ~CNodeDataDate();
	void SetValue(double ymd);
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  public:
	long m_ymd;
};

/* datetime of data. formate: yyyy-mm-dd hh:mm:ss*/
class UI_EXP CNodeDataDateTime : public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataDateTime)
  public:
	CNodeDataDateTime(long ymd = 19010223, long hms = 0);
	virtual ~CNodeDataDateTime();
	void SetValue(long ymd, long hms);
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void GetPrintText(BasicStringBufferA& str) override;
	void NodeDataToEditor(BeString& str) override;
	void EditorToNodeData(const BeString& str) override;
	void GetValueData(DataType type, ValuePack& sortData) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  public:
	long m_ymd;
	long m_hms;
};

/* BarOfPercent of data*/
class UI_EXP CNodeDataBarOfPercent : public CNodeDataDouble
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataBarOfPercent)
  public:
	CNodeDataBarOfPercent(double percent = 0.0);
	virtual ~CNodeDataBarOfPercent();

	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
};

/* int enum data node*/
class UI_EXP CNodeDataEnum : public CNodeDataInt
{
  public:
	typedef BeString (*CallbackIntTransFn)(int);

  public:
	CNodeDataEnum(int value, CallbackIntTransFn trans);
	virtual ~CNodeDataEnum();

	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;

  private:
	CallbackIntTransFn m_trans; // 翻译函数
};

/* text enum data node*/
class UI_EXP CNodeDataEnumText : public CNodeDataText
{
  public:
	typedef BeString (*CallbackTextTransFn)(BeString&);

  public:
	CNodeDataEnumText(BeString value, CallbackTextTransFn trans);
	virtual ~CNodeDataEnumText();

	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;

  private:
	CallbackTextTransFn m_trans; // 翻译函数
};

/* text enum data node*/
class UI_EXP CNodeDataPlaceRect : public CNodeData
{
  public:
	CNodeDataPlaceRect(RECT* m_pRect);
	virtual ~CNodeDataPlaceRect();

	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;

  private:
	RECT* m_pRect;
};

struct WParamAddNodeData
{
	std::shared_ptr<CNodeData> nodedata;
	const TCHAR* target;
};



} // #namespace




#endif
