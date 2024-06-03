
#ifndef CBLUEUI_GSTRINGW_BLXDY_INC_H_
#define CBLUEUI_GSTRINGW_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <stdlib.h>
#include <atomic>
#include "core/CCoreBasePro.h"
#include "StringConvertUtils.h"

#define ALIGN_SIZE_U     (7) // 编译器的对齐字节数
#define MIN_ALLOC_SIZE_U 32  // 最小分配大小

struct StringHeadInfoU
{
	std::atomic_long nRefs; // 引用记数 当前拥有此块内存的对象个数. 引用为0表示空字符串
	size_t nDataLength;     // 字符使用长度
	size_t nAllocLength;    // 分配长度
	WCHAR* after_tr;        // 翻译后的文本

	StringHeadInfoU()
	    : nRefs(1)
	    , nDataLength(0)
	    , nAllocLength(0)
	    , after_tr(NULL)
	{}

	WCHAR* data()
	{
		return (WCHAR*)(this + 1); // 存放字符串的地方
	}
};

/**
 * @brief 宽字符串UCS2编码(内置引用计数，copy on write)。备注：wchat_t在不同平台下占用字节不一样
 *
 */
class UI_EXP BeStringW
{
  public:
	BeStringW();
	BeStringW(int nLength); ///< nLength是预分配长度
	BeStringW(const BeStringW& stringSrc);
	BeStringW(WCHAR ch, int repeats);

	BeStringW(LPCWSTR lpsz, int nlen = -1);

	BeStringW(LPCSTR lpsz, int nlen = -1, UINT codepage = CP_ACP);
	~BeStringW();
	const WCHAR* c_str() const; ///< 获得内存数据

	const BeStringW& operator=(const BeStringW& stringSrc);
	const BeStringW& operator=(LPCWSTR lpsz);
	const BeStringW& operator=(LPCSTR ansi);
	const BeStringW& operator=(WCHAR ch);

	BeStringW operator+(const BeStringW& src) const;
	BeStringW operator+(LPCWSTR pstr) const;
	const BeStringW& operator+=(const BeStringW& src);
	const BeStringW& operator+=(LPCWSTR pstr);
	const BeStringW& operator+=(const WCHAR ch);

	bool operator==(const BeStringW& str) const;
	bool operator==(LPCWSTR lpsz) const;
	bool operator!=(const BeStringW& str) const;
	bool operator!=(LPCWSTR lpsz) const;
	bool operator<(const BeStringW& str) const;
	bool operator>(const BeStringW& str) const;
	bool operator<=(const BeStringW& str) const;
	bool operator>=(const BeStringW& str) const;

	WCHAR& operator[](int nIndex) const;
	size_t length() const; ///< 得到WCHAR字符个数。注意与符号个数区分。在UCS2编码下。稀有字符可能占用2个WCHAR长度

	size_t capacity() const; ///< 得到已经分配的内存字符长度

	bool is_empty() const; ///< 判断字符长度是否为0

	bool is_number() const; ///< 判断是否全部为整数

	bool is_email(); ///< 判断是否是邮箱

	bool is_ipv4(); ///< 判断是否是IPV4地址
	bool is_ipv6(); ///< 判断是否是IPV6地址

	bool is_decimal_number() const; ///< 判断是否为小数

	bool is_true() const;  ///< true
	bool is_false() const; ///< false

	int repeat_counts(WCHAR ch); ///< 字符重复的次数

	void empty();

	int erase(int nIndex, int nCount = 1);
	int append(LPCWSTR lpsz);
	int append(const WCHAR ch);
	int append(LPCWSTR lpsz, unsigned int nlen);
	int append(const BeStringW& strSrc);
	int append(const BeStringW& strSrc, unsigned int nlen);

	void join_path(const WCHAR* wstr);

	int insert(int nIndex, WCHAR ch); ///< 在nIndex前面插入
	int insert(int nIndex, LPCWSTR pstr, int len = -1);

	int replace_char(WCHAR chOld, WCHAR chNew); ///< 替换
	int replace_string(LPCWSTR lpszOld, LPCWSTR lpszNew);

	int toInt(bool ExprRecognition = true) const; ///< 转换成数字

	double tofloat(bool ExprRecognition = true) const; ///< 转换 浮点型

	void trim(); ///< 整理字符串, 清除指定字符串
	void trim_left();
	void trim_right();
	void remove(WCHAR chTarget);
	void remove(LPCWSTR lpszTargets);
	void remove_float_last_zero(); ///<  去除浮点数多余的0后缀
	void make_upper();
	void make_lower();

	BeStringW mid(int nStart, int nCount) const;

	int compare(LPCWSTR lpsz) const; ///< 区分大小写 ，<0 表示 自己strself小于lpsz （stringSrc）
	int compare(const BeStringW& stringSrc) const;

	int compare_no_case(LPCWSTR lpsz) const; ///< 不区分大小写
	int compare_no_case(const BeStringW& stringSrc) const;

	void format(LPCWSTR lpszFormat, ...);
	int find(WCHAR ch) const; ///< 查找
	int find(WCHAR ch, int nStart) const;
	int reverse_find(WCHAR ch) const;
	int find(LPCWSTR lpszSub) const;
	int find(LPCWSTR lpszSub, int nStart) const;

  private:
	StringHeadInfoU* get_data() const; //< 获得指定的数据结构
	void release();                    //< 若引用<= 1释放内存 引用记数器并判断是否删除内存
	void release(StringHeadInfoU* pData);

	void free_string_data(StringHeadInfoU* pData); // 释放指定结构

	void init_string();

	void formate_v(LPCWSTR lpszFormat, va_list argList); // 格式化

	int safe_strlen(LPCWSTR lpsz);

	void assign_copy(int nSrcLen, LPCWSTR lpszSrcData); // 分配字符空间

	void alloc_buffer(int nLen); // 分配内存 并将内存块的数据长度设置为 nLen

	void copy_before_write(); // 脱离数据块

	void free_real_memory(char* pFree); // 字符内存释放

	unsigned int get_alloc_memsize(unsigned int nlen); // 返回值是内存块的大小

	char* alloc_real_memory(unsigned int nSize); // 字符内存分配

	static BOOL is_valid_string(LPCWSTR lpsz, int nLength = -1);

  private:
	WCHAR* m_pchData; // 底层 字符串指针
};

class UI_EXP BeStringPairW
{
  public:
	BeStringW m_name;
	BeStringW m_value;

	BeStringPairW();
	BeStringPairW(const BeStringW& name, const BeStringW& value);
	BeStringPairW(const BeStringPairW& pair);
	~BeStringPairW();
};

#if defined(UNICODE) || defined(_UNICODE)
typedef BeStringW BeString;
typedef BeStringPairW BeStringPair;
#endif



#endif