#ifndef CBLUEUI_CCORECHARFUNCTION_BLXDY_INC_H_
#define CBLUEUI_CCORECHARFUNCTION_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCoreBasePro.h"

extern "C" {


UI_EXP char* stristr(const char* inBuffer, const char* inSearchStr); ///< 匹配字串，返回匹配起始位置(忽略大小写)


UI_EXP WCHAR* wcsistr(const WCHAR* inBuffer, const WCHAR* inSearchStr); ///< 忽略大小写查找子串。返回匹配起始位置(忽略大小写)


UI_EXP int mbclen_utf8(const char* p); ///< 获取utf8字符占用字节数


UI_EXP int mbclen_utf16(const WCHAR* p); ///< 获取utf16字符占用字节数


UI_EXP size_t mbslen_utf8(const char* p); ///< 获取utf8字符个数

/**
 * @brief ucs-2符号个数
 *
 */
UI_EXP size_t wcsclen_char16(const WCHAR* s);

/**
 * @brief ucs-2字节个数
 *
 */
UI_EXP size_t wcslen_char16(const WCHAR* s);

/**
 * comparison
 */

UI_EXP int wcsncmp_char16(const WCHAR* s1, const WCHAR* s2, size_t count);
UI_EXP int wcscmp_char16(const WCHAR* s1, const WCHAR* s2);


/**
 * Ignore case comparison
 */
UI_EXP int wcsnicmp_char16(const WCHAR* s1, const WCHAR* s2, size_t count);
UI_EXP int wcsicmp_char16(const WCHAR* s1, const WCHAR* s2);

UI_EXP WCHAR* wcschr_char16(const WCHAR* str, WCHAR ch);
UI_EXP WCHAR* wcsrchr_char16(const WCHAR* str, WCHAR ch);
UI_EXP WCHAR* wcsstr_char16(const WCHAR* wcs1, const WCHAR* wcs2);

UI_EXP double wcstod_char16(WCHAR const* str, WCHAR** endptr);

UI_EXP long long wcstoll_char16(WCHAR const* str, WCHAR** endptr, int base);

UI_EXP int swscanf_char16(const WCHAR* buffer, const WCHAR* format, ...);
UI_EXP int vswscanf_char16(const WCHAR* buffer, const WCHAR* format, va_list arg);
/**
 * Tiny vprintf implementation
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list
 * \return The number of characters that are WRITTEN into the buffer, not counting the terminating null character
 */
UI_EXP int snprintf_char16(WCHAR* s, size_t n, const WCHAR* format, ...);

UI_EXP int vsnprintf_char16(WCHAR* s, size_t n, const WCHAR* format, va_list arg);

UI_EXP int fctprintf_char16(void (*out)(WCHAR ch, void* arg), void* arg, const WCHAR* format, ...);

typedef char32_t ucs4_t;

struct char_conv_type
{
  public:
	int (*xxx_mbtowc)(ucs4_t* pwc, unsigned char const* s, size_t n) = NULL;
	int (*xxx_wctomb)(unsigned char* r, ucs4_t wc, size_t n)         = NULL;
};

UI_EXP void init_conv_type(char_conv_type& conv, UINT from_cp, UINT to_cp);

UI_EXP int conv_chars(const char_conv_type& conv, const char* utf8str, int slen, char* outbuf, int outsize);

UI_EXP int conv_utf8_to_utf16(const char* utf8str, int slen, WCHAR* outbuf, int osize);
UI_EXP int conv_utf16_to_utf8(const WCHAR* wstr, int wlen, char* outbuf, int osize);
UI_EXP int conv_unicode_to_utf8(const ucs4_t* wstr, int wlen, char* outbuf, int osize);
UI_EXP int conv_utf8_to_unicode(const char* utf8str, int slen, ucs4_t* outbuf, int osize);
}



#endif