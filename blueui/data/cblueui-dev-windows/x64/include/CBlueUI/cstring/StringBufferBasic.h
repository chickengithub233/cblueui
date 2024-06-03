#ifndef CBLUEUI_STRING_STRINGBUFFERBASIC_BLXDY_INC_H_
#define CBLUEUI_STRING_STRINGBUFFERBASIC_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "core/CCoreCharFunction.h"

int check_text_len_a(const char* str, int len);
int check_text_len_w(const WCHAR* str, int len);

/**
 * @brief 绑定字符流，会改变字符流数据(多字符集)
 *
 */
class UI_EXP BasicStringBufferA
{
  public:
	/**
	 * @param source 源字符
	 * @param capacity  源字符容量
	 */
	BasicStringBufferA(char* source, int capacity);
	~BasicStringBufferA();
	size_t length() const;     ///< 字符串长度
	const char* c_str() const; ///< 源字符串

	void append(const char* str, int len = -1); ///< 尾部添加字符串
	void append(char ch, int repeat = 1);       ///< 尾部添加单个字符
	void update(int pos, char ch);              ///< 更新值

	int replace_char(char chOld, char chNew);                 ///< 替换字符
	int replace_string(const char* chOld, const char* chNew); ///< 替换字符串
	void reversal();                                          ///< 倒转字符串
	void trim();                                              ///< 剔除字符串头尾空白符(空格、换行、tab)
	void trim_left();                                         ///< 剔除字符串前缀空白符(空格、换行、tab)
	void trim_right();                                        ///< 剔除字符串末尾空白符(空格、换行、tab)
	void trim_all();                                          ///< 剔除字符串任意位置空白符(空格、换行、tab)
	void format_ellipsis(const char* str, UINT align);        ///< 长度超出范围时显示省略号
	void format(const char* lpszFormat, ...);                 ///< 格式化打印
	void format_v(const char* lpszFormat, va_list args);


	void insert(int nIndex, const char* str, int count = -1); ///< 插入字符串
	void erase(int nIndex, int nCount = 1);                   ///< 删除字符
	void remove_float_last_zero();                            ///< 去除浮点数多余的0后缀
	void remove_float_scientific_zero();                      ///< 去除科学计数法多余的0后缀
	void add_numeric_thousand_separator();                    ///< 数字千分分隔符
	void clear();                                             ///< 清空字符串
	void resize(unsigned len);
	void init(const char* str, int count = -1);
	void init(const WCHAR* wstr, int count = -1, unsigned int CodePage = CP_UTF8);

	void join_path(const char* str);
	bool is_empty() const; ///< 是否为空
  protected:
	void _alloc_size(int size);

  private:
	void operator=(const BasicStringBufferA&);

  private:
	char* m_data_ptr;
	char* m_source_; // 缓冲区
	int m_buf_len;   // 固定缓冲容量
	int m_nCapacity; // 字符重新分配容量
};

/**
 * @brief 绑定字符流，会改变字符流数据(宽字符集)
 *
 */
class UI_EXP BasicStringBufferW
{
  public:
	BasicStringBufferW(WCHAR* source, int capacity);
	~BasicStringBufferW();

	size_t length() const;
	const WCHAR* c_str() const;

	void append(const WCHAR* str, int len = -1);
	void append(WCHAR ch, int repeat = 1);
	void update(int pos, WCHAR ch);

	int replace_char(WCHAR chOld, WCHAR chNew);
	int replace_string(const WCHAR* chOld, const WCHAR* chNew);
	void reversal();                                    ///< 倒转字符串
	void trim();                                        ///< 剔除字符串头尾空白符(空格、换行、tab)
	void trim_left();                                   ///< 剔除字符串前缀空白符(空格、换行、tab)
	void trim_right();                                  ///< 剔除字符串末尾空白符(空格、换行、tab)
	void trim_all();                                    ///< 剔除字符串任意位置空白符(空格、换行、tab)
	void format_ellipsis(const WCHAR* str, UINT align); ///< 长度超出范围时显示省略号
	void format(const WCHAR* lpszFormat, ...);
	void format_v(const WCHAR* lpszFormat, va_list args);
	void insert(int nIndex, const WCHAR* str, int count = -1);
	void erase(int nIndex, int nCount = 1);
	void remove_float_last_zero();
	void remove_float_scientific_zero();
	void add_numeric_thousand_separator(); ///< 数字千分分隔符

	void clear();
	void resize(unsigned len);
	void init(const char* str, int count = -1, unsigned int CodePage = CP_UTF8);
	void init(const WCHAR* wstr, int count = -1);

	void join_path(const WCHAR* wstr);
	bool is_empty() const; ///< 是否为空
  protected:
	void _alloc_size(int size);

  private:
	void operator=(const BasicStringBufferW&);

  private:
	WCHAR* m_data_ptr;
	WCHAR* m_source_;
	int m_buf_len;
	int m_nCapacity;
};


#ifdef _UNICODE
typedef BasicStringBufferW BasicStringBuffer;
#else
typedef BasicStringBufferA BasicStringBuffer;
#endif

#endif
