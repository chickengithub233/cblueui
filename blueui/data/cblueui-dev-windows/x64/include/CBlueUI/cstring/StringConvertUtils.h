#ifndef CBLUEUI_STRINGCONVERTUTILS_BLXDY_INC_H_
#define CBLUEUI_STRINGCONVERTUTILS_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "core/CCoreCharFunction.h"
#include "StringBufferBasic.h"
#include <string>
#include <vector>

namespace std {

#ifdef WIN32
using w16string = std::wstring;
#else
using w16string = std::u16string;
#endif

#ifdef UNICODE
using tstring = std::w16string;
#else
using tstring   = std::string;
#endif
}

namespace UtilsString {

/**
 * @brief 判断字符串是否为ASCII
 *
 */
UI_EXP bool IsASCIITextA(const char* str, int len = -1);

/**
 * @brief 判断字符串是否为ASCII
 *
 */
UI_EXP bool IsASCIITextW(LPCWSTR str, int len = -1);

/**
 * @brief 判断字符串是否为ASCII
 *
 */
UI_EXP bool IsASCIIText(LPCTSTR str, int len = -1);

/**
 * @brief 判断字符是否是UTF8编码方式
 *
 */
UI_EXP bool IsUTF8(const char* str);

/**
 * @brief 判断字符是否是GBK编码方式
 *
 */
UI_EXP bool IsGBK(const char* str);

UI_EXP int ConverterMultiByteToWideChar(UINT CodePage, const char* lpMultiByteStr, int cbMultiByte, WCHAR* lpWideCharStr, int cchWideChar);


UI_EXP int ConverterWideCharToMultiByte(UINT CodePage, const WCHAR* lpWideCharStr, int cchWideChar, char* lpMultiByteStr, int cbMultiByte);



/**
 * @brief convert unicode to utf8
 *
 * @param buf 输出utf8格式字符缓冲
 * @param buf_size
 * @param wide_char 宽字符编码
 * @return int 返回utf8字节数
 */
UI_EXP int WideCharToUtf8(char* buf, int buf_size, unsigned int wide_char);

/**
 * @brief convert utf8 to unicode
 *
 * @param out_char 输出unicode字符
 * @param in_text 起始字符
 * @param in_text_end 结束字符
 * @return int 返回转换utf8占用字节数
 */
UI_EXP int Utf8CharToWide(unsigned int* out_char, const char* in_text, const char* in_text_end);


/**
 * @brief 格式转换
 *
 */
UI_EXP int ToMultiByte(const char* src, int len, BasicStringBufferA& outstr, UINT cp_from, UINT cp_to);

/**
 * @brief unicode字符转换为多字符集(GBK,ISO)
 *
 * @param wc unicode宽字符
 * @param len 转换长度
 * @param outstr 转换后的多字符集
 * @param cp_to 多字符集编码 GBK, ISO
 */
UI_EXP int UnicodeToMultiByte(const WCHAR* wc, int len, BasicStringBufferA& outstr, UINT cp_to = CP_UTF8);

/**
 * @brief 多字符集(GBK,ISO) 转换为unicode字符
 *
 * @param src 多字符集串
 * @param len 转换长度
 * @param outstr 转换后的unicode字符集
 * @param cp_from  多字符集编码 GBK, ISO
 */
UI_EXP int MultiByteToUnicode(const char* src, int len, BasicStringBufferW& outstr, UINT cp_from);

enum ChinaPinyinOption
{
	PY_MASK_FULLNAME     = 1,      // bit0:  1代表全拼 0 代表简称
	PY_MASK_FIRST_CAPS   = 1 << 1, // bit1:  1首字母大写 0 全部小写
	PY_MASK_ALL_CAPS     = 1 << 2, // bit2:  1全部大写 0 全部小写
	PY_MASK_INSERT_SPACE = 1 << 3, // bit3:  1汉字间插入空格 0 不插入符号
};

/**
 * @brief 转换为拼音
 *
 * @param utf8Str utf8格式字符
 * @param options :ChinaPinyinOption
 * @param [#out] result:
 */
UI_EXP void UnicodeToChinaPinyin(LPCSTR utf8Str, UINT options, std::string& result);

UI_EXP BOOL IsLittleEnding(); ///< 是否是小端模式
UI_EXP BOOL IsStackPtr(void* p);

UI_EXP BOOL IsDecimalFormateA(const char* str, int len = -1); ///< 是否满足小数输入格式
UI_EXP BOOL IsIntegerA(const char* str, int len = -1);
UI_EXP BOOL IsIdentfierA(const char* str, int len = -1);

UI_EXP BOOL IsDecimalFormateW(const WCHAR* str, int len = -1); ///< 是否满足小数输入格式
UI_EXP BOOL IsIntegerW(const WCHAR* str, int len = -1);
UI_EXP BOOL IsIdentfierW(const WCHAR* str, int len = -1);

UI_EXP BOOL IsDecimalFormate(const TCHAR* str, int len = -1); ///< 是否满足小数输入格式

UI_EXP BOOL IsInteger(const TCHAR* str, int len = -1);

UI_EXP BOOL IsIdentfier(const TCHAR* str, int len = -1);

UI_EXP int GetIntegerCharCount(int v); ///< 获得整数需要的十进制位数位数

UI_EXP int GetCharsCount(LPCTSTR text, int count); ///< 返回字符个数

UI_EXP LPCSTR FindNextBracketA(LPCSTR text, char start_bracket, char end_bracket, int levels = 0); ///< 返回括号分组的结束位置

UI_EXP LPCWSTR FindNextBracketW(LPCWSTR text, WCHAR start_bracket, WCHAR end_bracket, int levels = 0); ///< 返回括号分组的结束位置

UI_EXP std::vector<std::string> SplitWithCharA(const char* str, const char* pattern, int count = 0, BOOL skip_bracket = FALSE);

UI_EXP std::vector<std::string> SplitWithTextA(std::string str, std::string pattern, int count = 0);

UI_EXP std::vector<std::w16string> SplitWithCharW(const WCHAR* str, const WCHAR* pattern, int count = 0, BOOL skip_bracket = FALSE);

UI_EXP std::vector<std::w16string> SplitWithTextW(std::w16string str, std::w16string pattern, int count = 0);

UI_EXP void SplitAttribute(const TCHAR* text, std::vector<std::pair<std::tstring, std::tstring>>& result, TCHAR SplitCharacter = (TCHAR)';');


/**
 * @brief 计算器解析器
 *
 */
UI_EXP bool CalculatorValue(double& value, const char* str, int len = -1);

/**
 * @brief 将基于base进制的字符串转换为字节流
 *
 */
UI_EXP void ConvertBaseTextToBytes(BasicStringBufferA& out_buf, int& len, LPCTSTR str, int base);

/**
 * @brief 获取上级目录
 *
 */
UI_EXP void GetPrevDirPath(LPCTSTR fullname, BasicStringBuffer& prev_path);

UI_EXP void GetPrevDirPathA(LPCSTR fullname, BasicStringBufferA& prev_path);

UI_EXP void GetPrevDirPathW(LPCWSTR fullname, BasicStringBufferW& prev_path);
/**
 * @brief 获取文件后缀
 *
 * @param isComplete 完整后缀比如xxxx.tar.gz(.tar.gz称之为完整后缀)
 */
UI_EXP void GetFileSuffix(LPCTSTR fullname, BasicStringBuffer& suffix, BOOL isComplete = TRUE);

UI_EXP void GetFileSuffixA(LPCSTR fullname, BasicStringBufferA& suffix, BOOL isComplete = TRUE);

UI_EXP void GetFileSuffixW(LPCWSTR fullname, BasicStringBufferW& suffix, BOOL isComplete = TRUE);


/**
 * @brief 获取不包含后缀的文件名
 *
 * @param isComplete  完整后缀
 */
UI_EXP void GetFileBaseName(LPCTSTR fullname, BasicStringBuffer& basename, BOOL isComplete = TRUE);


UI_EXP void GetFileBaseNameA(LPCSTR fullname, BasicStringBufferA& basename, BOOL isComplete = TRUE);

UI_EXP void GetFileBaseNameW(LPCWSTR fullname, BasicStringBufferW& basename, BOOL isComplete = TRUE);

/**
 * @brief 获取文件名称
 *
 */
UI_EXP void GetFileName(LPCTSTR fullname, BasicStringBuffer& filename);

/**
 * @brief 获取路径，不包含文件
 *
 */
UI_EXP void GetFilePath(LPCTSTR fullname, BasicStringBuffer& filepath);

/**
 * @brief 解析对齐方式
 *
 */
UI_EXP void ParseToAlign(UINT& align, LPCTSTR value);


/**
 * @brief 整数转换为文本。(2，8，10，16 进制)
 * @param        num: 待转换的数值
 * @param        base: 目标字符串的进制
 * @param [#out] outstr :输出到目标字符串
 *
 */
UI_EXP void IntToString(int num, int base, BasicStringBuffer& target);

/**
 * @brief 解析数值。(可识别模式 156.e-2，0b1101,0o154,0x1245,#5421)
 *
 * @param        str: 扫描字符串开始位置
 * @param        end: 扫描字符串结束位置
 * @param [#out] value :输出数值
 * @param [#out] is_percent_value :输出数值是否为百分比模式
 * @param [#out] next_ptr :输出下一次解析的指针位置

 * @return 返回下一次解析的指针位置。若一次解析全部，则返回空
 */
UI_EXP bool ParserNumericalValueA(const char* str, const char* end, char** next_ptr, double& value, int& is_percent_value);
UI_EXP bool ParserNumericalValueW(const WCHAR* str, const WCHAR* end, WCHAR** next_ptr, double& value, int& is_percent_value);
UI_EXP bool ParserNumericalValue(const TCHAR* str, const TCHAR* end, TCHAR** next_ptr, double& value, int& is_percent_value);


/**
 * @brief 解析进制整数。(2，8，10，16 进制)
 *
 */
UI_EXP int ParserToIntA(const char* str, int base = 10);
UI_EXP int ParserToIntW(const WCHAR* str, int base = 10);
UI_EXP int ParserToInt(const TCHAR* str, int base = 10);

/// 解析画笔类型 solid, dot, dash, dash-dot, dash-dot-dot
UI_EXP PenType ParserPenType(const TCHAR* str);

/// 跳过指定字符
UI_EXP void SkipSpaceOrChar(const char** str, char c);

/**
 * @brief 解析以逗号分隔的数值
 *
 * @param str 输入
 * @param value 输出缓冲数组
 * @param num_values 缓冲大小
 * @param next 下次扫描位置
 */
UI_EXP bool ParseCsvDoubles(const char* str, double* value, int num_values, char** next);

}

/**
 * @brief 数值解析工具类
 *
 */
class UI_EXP NumericalValueList
{
  public:
	NumericalValueList(BOOL isConvFloat = TRUE);
	NumericalValueList(NumericalValue* valuebuf, int captily, BOOL isConvFloat = TRUE);
	~NumericalValueList();

	void ParseText(LPCTSTR str, LPCTSTR delimiter = (LPCTSTR)_Txt(","));
	void ParseTextW(LPCWSTR str, LPCWSTR delimiter = _W(","));
	void ParseTextA(const char* str, const char* delimiter);

	double operator[](int nIndex) const;
	UINT ValueMode(int nIndex) const;
	RECT ToRect() const;

  private:
	int m_count;
	int m_captily;
	NumericalValue m_value[8];
	NumericalValue* m_value_ex;
	BOOL m_isConvFloat;
};

/**
 * class: StringConstList 常量字符串数组
 */
class UI_EXP StringConstList
{
  public:
	StringConstList(LPCTSTR* buf, int buf_size);
	~StringConstList();

	void Add(LPCTSTR text);
	UINT Size() const;
	int IsFind(LPCTSTR string, BOOL ignore_case = TRUE) const;
	int IsCompare(LPCTSTR string, BOOL ignore_case = TRUE) const;

  private:
	LPCTSTR* m_text_buf;
	UINT m_count;
	UINT m_captily;
};

#ifdef UNICODE
#define SplitWithChar SplitWithCharW
#define SplitWithText SplitWithTextW
#else
#define SplitWithChar SplitWithCharA
#define SplitWithText SplitWithTextA
#endif


#endif
