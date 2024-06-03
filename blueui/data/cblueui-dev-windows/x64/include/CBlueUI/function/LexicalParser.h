#ifndef CBLUEUI_LEXICALPARSER_BLXDY_INC_H_
#define CBLUEUI_LEXICALPARSER_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <string>
#include "core/CCoreBasePro.h"
#include "cstring/StringConvertUtils.h"

namespace BUI {

enum TokenMarcoType
{
	MASK_Comment      = 1 << 24,
	MASK_KeyWord      = 1 << 25,
	MASK_Identifier   = 1 << 26,
	MASK_Const_String = 1 << 27,
	MASK_Const_Number = 1 << 28,
	MASK_Separator    = 1 << 29,
	MASK_Operator     = 1 << 30,
};

enum SyntaxParserLanguage
{
	C = 0,
	CPlusPlus,
	Java,
	Python,
	CSharp,
	Rust,
	Go,
	GLSL,
	HLSL,
	JavaScript,
	Lua,
	CoffeeScript,
	TypeScript,
	Swift,
	Kotlin,
	ObjectiveC,
	ObjectiveCPlusPlus,
	ActionScript,
	Scala
};

struct TokenLocation
{
	UINT type    = 0;
	int location = 0;
	int length   = 0;
	std::tstring value;
};

class UI_EXP TokenColors
{
  public:
	TokenColors();
	~TokenColors();

	void ConfigLanguage(SyntaxParserLanguage lang);

	void SetTokenColor(TokenMarcoType toktype, int pos, COLORREF color);

	BOOL GetTokenColor(UINT type, COLORREF& color) const;

  protected:
	std::map<UINT, COLORREF> m_mmTokenstyle;
};

class UI_EXP LexicalParser
{
  public:
	LexicalParser();
	~LexicalParser();

	std::vector<TokenLocation> Lex(const TCHAR* data, BOOL skipSpace = TRUE);
	/* config lang:*/
	void SetWordConmmet(std::vector<std::pair<std::tstring, std::tstring> >& veclist);
	void SetWordString(std::vector<std::pair<std::tstring, std::tstring> >& veclist);
	void SetWordSeparated(std::vector<std::tstring>& veclist);
	void SetWordEscape(std::vector<std::tstring>& veclist);
	void SetWordKey(std::vector<std::tstring>& veclist);

	/* find position:*/
	int FindPositionWordEscape(const TCHAR* p);
	int FindPositionWordSeparated(const TCHAR* p);
	int FindPositionWordKey(const TCHAR* p);

  protected:
	int LexWordComment(const TCHAR*& p, UINT& type);
	int LexWordString(const TCHAR*& p, UINT& type);
	int LexWordSeparated(const TCHAR*& p, UINT& type);
	int IsNumber(const TCHAR* p, int len);
	int IsWordIdentifier(const TCHAR* p);
	void PushTocken(std::vector<TokenLocation>& token_list, const TCHAR* data, const TCHAR* ps, const TCHAR* p, UINT type, BOOL skipSpace);

  protected:
	std::vector<std::pair<std::tstring, std::tstring> > m_word_comment; // 注释符号组
	std::vector<std::pair<std::tstring, std::tstring> > m_word_string;  // 字符串组

	std::vector<std::tstring> m_word_separated; // 分隔符和运算符
	std::vector<std::tstring> m_word_escape;    // 转义字符
	std::vector<std::tstring> m_word_key;       // 关键字
};

// class UI_EXP SyntaxHighlight
//{
// public:
//	SyntaxHighlight();
//	~SyntaxHighlight();

//};
}


#endif
