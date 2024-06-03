#ifndef CBLUEUI_CEDITLINE_BLXDY_INC_H_
#define CBLUEUI_CEDITLINE_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CScrollBarUI.h"
#include "function/LexicalParser.h"

namespace BUI {

typedef short size_type_width;

struct CharSize
{
	size_type_width cx;
	size_type_width cy;
};

struct UnDoRecord
{
	UINT op_;     // 0 插入 1 删除
	int pos;      // 插入或者删除位置
	BeString str; // 文本
};

/// 编辑框属性标志
enum InputTextFlags
{
	InputFlags_None             = 0,       ///< None
	InputFlags_CharsDecimal     = 1 << 0,  ///< Allow 0123456789+-
	InputFlags_CharsOctal       = 1 << 1,  ///< Allow 01234567
	InputFlags_CharsHexadecimal = 1 << 2,  ///< Allow 0123456789ABCDEFabcdef
	InputFlags_CharsBinary      = 1 << 3,  ///< Allow 01
	InputFlags_CharsUppercase   = 1 << 4,  ///< Turn a..z into A..Z
	InputFlags_CharsNoBlank     = 1 << 5,  ///< Filter out spaces, tabs
	InputFlags_CharsScientific  = 1 << 6,  ///< Allow 0123456789.+-*/eE (Scientific notation input)
	InputFlags_Password         = 1 << 7,  ///< Password mode Allow ascii
	InputFlags_ReadOnly         = 1 << 8,  ///< Read-only mode
	InputFlags_WantReturn       = 1 << 9,  ///< Occurs when the input event ends. sendmessage [MSG_TEXT_RETURN]
	InputFlags_Multiline        = 1 << 10, ///< For internal use by InputTextMultiline()
	InputFlags_Wordwarp         = 1 << 11, ///< Word wrap
	InputFlags_NO_Modification  = 1 << 12, ///< do not modify text
	InputFlags_CheckValueRange  = 1 << 13, ///< check value of range
	InputFlags_Undo             = 1 << 14, ///< undo
	InputFlags_ConsoleModel     = 1 << 15, ///< console mode
	InputFlags_TextChange       = 1 << 16, ///< text change
	InputFlags_ShowLineNumber   = 1 << 17, ///< show line number
	InputFlags_ShowLineMark     = 1 << 18, ///< show line Mark
};

/**
 * @brief 编辑框外观信息
 *
 */
class UI_EXP CEditLineStyle
{
  public:
	CEditLineStyle(UINT textflags, RECT* ppview, GFont** ppfont);
	~CEditLineStyle();

	virtual BOOL GetRectTextView(RECT& rc);
	virtual void OnCheckContext();          // 属性发生变化，需要重新校验值的合法性
	virtual void OnChangeUpdate(UINT bits); // 变化处理事件，比如行宽改变，高度改变，需要更新位置信息等

	void SetEditEmptyTextTips(BeString str);

	PaddingInfo GetTextPadding() const;
	void SetTextPadding(int dl, int dt, int dr, int db);

	UINT GetTextFlags() const;
	BOOL IsTetxFlags(UINT flag) const;

	/**
	 * @brief 设置编辑框属性标志
	 *
	 * @param style 取@link InputTextFlags @endlink组合值
	 * @param op  ADD_FLAGS(添加属性) REMOVE_FLAGS(删除属性)
	 */
	void ModifyTextFlags(UINT style, UINT op = ADD_FLAGS);

	BOOL IsReadOnly() const;
	int GetLimitMaxCount() const;
	void SetLimitMaxCount(int c);

	int GetPercision() const;
	void SetPercision(int p);

	double GetValueMax() const;
	void SetValueMax(double va);

	double GetValueMin() const;
	void SetValueMin(double va);

	int GetSelectRowCount() const;
	void SetSelectRowCount(int c);

	int GetLastWrapWidth() const;
	void SetLastWrapWidth(int w);

	UINT GetTextAlign() const;
	void SetTextAlign(UINT align);

	int GetChangeCount() const;
	void AddChangeCount(int c);
	void ResetChangeCount();

	BeString GetTextTips() const;
	void SetTextTips(BeString& str);

	int GetFontHeight() const; // 字体高度

	void SetLineSpacingHeight(int size);
	int GetLineSpacingHeight() const; // 行间距

	int GetDefaultLineHeight() const; // 获得默认行高
	GFont* GetPublicFont();

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | text-align <br/>文本对齐方式  | text-align="left,vcenter" 取值left,right,center,top,bottom,vcenter的组合  |
	 * | text-padding <br/>文本内边缩进|  text-padding="10,10,10,10"   |
	 * | empty-tips <br/>空内容时的提示文本|  empty-tips="请输入授权码"   |
	 * | input-range <br/>数值输入范围，超出范围输入无响应    |  input-range="0,100"   |
	 * | input-min  <br/>数值输入最小值，超出范围输入无响应 | input-min="0" |
	 * | input-max  <br/>数值输入最大值，超出范围输入无响应 | input-max="100"  |
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
	 * |            |  ShowLineNumber: show line number   |
	 * |            |  ShowLineMark: show line highlight mark   |
	 * |            |    |
	 * | undo-size <br/>最大撤销步骤          |  undo-size="20"   |
	 * | allow-max-count <br/>允许输入字符数量最大限制          |  allow-max-count="64"   |
	 * | precision <br/>数值显示精度            |  precision="1" 保留1位小数点   |
	 */
	void ShellLineAttribute(const BeString& szName, const BeString& szText);



  public:
	BeString m_tipsText;       // 提示文字
	PaddingInfo m_textPadding; // 编辑区偏移
	// TokenColors* m_tokColors;  // 词法颜色方案
	// LexicalParser* m_syntax;   // 词法解析器
	UINT m_textFlag;
	int m_nLineSpaceing;   // 行间距
	int m_nMaxLimitCount;  // 最大输入字符个数
	int m_nPrecision;      // 精度
	double m_nMinValue;    // 最大值
	double m_nMaxValue;    // 最小值
	SIZE m_roundSize;      // 边框圆角尺寸
	int m_nSelectCount;    // 选中的行数量
	int m_nChangeCount;    // 编辑次数
	UINT m_horAlign;       // 文本水平对齐方式
	RECT* m_pRcClient;     // 文本可视区域二级指针
	GFont** m_ppfont;      // 字体二级指针
	int m_nHexGroupCount;  // 16进制数值，n个字节为一组，以空格分组
	int m_last_warp_width; // 上一次计算的宽度
	int m_nUndoMaxSize;    // 撤销步骤最大值
	int m_lead_width;      // 行号宽度尺寸
	std::deque<UnDoRecord> m_undo_;
	std::deque<UnDoRecord> m_undo_back_;
};

struct CharStyle
{
	int refcount;
	GFont* font;
	COLORREF color;
};

struct WordWrapLineInfo
{
	const TCHAR* sz;
	int start_pos;        // 每一小行的起点
	int end_pos;          // 每一小行的起点
	int width;            // 每一小行的宽度
	int select_rect_left; // 选中文本的字符宽度信息，避免重复计算
	int select_rect_width;
};

/**
 * @brief 行编辑类
 *
 */
class UI_EXP CEditLine
{
  public:
	CEditLine(CEditLineStyle* style);
	~CEditLine();

	void OnMessageEdit(UINT message, WPARAM wp, LPARAM lp);

	int InsertChars(int pos, LPCTSTR text, int count = -1, GFont* font = NULL, COLORREF* color = NULL);
	int AppendPreimeChars(LPCTSTR text, int count = -1, GFont* font = NULL, COLORREF* color = NULL);
	void EndPreInput(LPCTSTR text, int count = -1);
	BeString GetText() const;
	LPCTSTR GetTextPtr(int pos);
	BOOL IsEmpty() const;

	void SetCharStyle(int pos, int count, GFont* font = NULL, COLORREF* color = NULL);
	void ClearCharStyle(); ///< 清除文本自定义风格

	int CharCount() const;
	int FindLocateCoord(RECT& rcText, int dx, int dy);
	int GetPixelWidth(int count) const;
	BOOL DeleteChars(int pos, int count);
	BOOL DeleteSelectChars();
	void SelectRange(int pos, int count);

	void SetErrorCodeState(int code);
	int ErrorCodeState() const;
	/**
	 * @brief 重新计算换行信息，在视窗区域变化和每插入和删除一个字符时触发
	 *
	 * @param width
	 * @return int 返回高度差=新高度 - 旧高度
	 */
	int UpdateWordWrapLine(int width);
	void UpdateCharsSize(int pos, int count);

	int CharCursorPos() const;
	void SetCharCursorPos(int cursor);

	int CharFixHeadPos() const;
	void SetCharFixHeadPos(int pos);

	int LineBottomPos() const;
	void SetLineBottomPos(int pos);

	int GetLineWidth() const;
	int GetLineHeight(BOOL isSingleLine = FALSE) const;

	int GetPreInputPos() const;
	int GetPreInputLength() const;

	int GetWraplineHeight(int sub_line, BOOL nearTop) const;
	int GetWraplineIndex(int cursor) const;
	int GetWraplineCount() const;

	void AppendSelectText(BasicStringBuffer& buffer) const;
	void AppendText(BeString& buffer) const;
	void DrawLineCursor(ISurface* psurface, int paintState, int dx, RECT rcLine, COLORSTYLE& textcolor, POINT& ptCursor);
	void DrawLineTextOut(ISurface* psurface, int paintState, int dx, RECT rcLine, COLORREF crbgSelected, COLORSTYLE& textcolor, UINT txtFlags);

  protected:
	void DrawWrapLineTextOut(ISurface* psurface, int paintState, int dx, RECT rcLine, COLORREF crbgSelected, COLORSTYLE& textcolor, UINT txtFlags);
	void DrawTextRangePos(ISurface* psurface, GFont* defaultFont, int start, int end, int& x0, int& y0, const TCHAR*& p, RECT& rcLine, COLORREF& textcolor);
	void insertCharsInternal(int pos, LPCTSTR text, int count, GFont* font, COLORREF* color);
	int GetBytesLength(LPCTSTR text, int pos, int count);
	BOOL CheckDecimal(const TCHAR* text);
	int PreCheckBeforeInsert(int pos, LPCTSTR text, int count, UINT textFlag, BasicStringBuffer& buffer);

	void GetCharFont(int pos, GFont*& font);
	CharStyle* GetCharStyle2(int pos) const;

  protected:
	CEditLineStyle* m_style;
	BeString m_text;
	std::vector<CharSize> m_sizes;       // 单个字符尺寸
	std::vector<CharStyle*> m_charStyle; // 单个字符风格
	std::vector<int> m_charState;        // 词法高亮状态表

	SIZE m_lineSize;     // 行尺寸
	int m_cursor_pos;    // position of the text cursor within the string
	int m_cursor_offset; // 光标字符处的字符总宽度
	int m_select_start;  // selection start point
	int m_select_count;

	int m_select_rect_left; // 选中文本的字符宽度信息，避免重复计算
	int m_select_rect_width;

	int m_stringBytes;   // 字符字节数
	int m_stringCount;   // 字符个数
	int m_preInputPos;   // 输入法预输入文本开始位置
	int m_preInputCount; // 预输入字符个数(注意不是字符占用的字节数)

	int m_fix_head_pos;   // 固定前缀位置，[0,m_fix_head_pos]不可编辑，删除
	int m_nLineBottomPos; // 文本行底线位置

	int m_nErrorCode; // 错误状态码标记，值越大错误越严重。0表示无错误。可用于错误突出显示
	/* 换行结构信息， 用于自动换行处理*/
	std::vector<WordWrapLineInfo> m_wordwrap; // 换行信息
	int m_fisrt_printf_pos;                   // 第一个可打印字符的位置
	int m_fisrt_printf_head;                  // 第一个可打印字符的宽度
};


}

#endif
