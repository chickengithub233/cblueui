#ifndef CBLUEUI_USTRINGA_BLXDY_INC_H_
#define CBLUEUI_USTRINGA_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include <atomic>
#include "core/CCoreBasePro.h"
#include "StringConvertUtils.h"
#define ALIGN_SIZE     (7) // 编译器的对齐字节数
#define MIN_ALLOC_SIZE 32  // 最小分配大小

struct StringHeadInfoA
{
	std::atomic_long nRefs; // 引用记数 当前拥有此块内存的对象个数. 引用为0表示空字符串
	size_t nDataLength;     // 字符使用长度
	size_t nAllocLength;    // 分配长度
	char* after_tr;         // 翻译后的文本

	StringHeadInfoA()
	    : nRefs(1)
	    , nDataLength(0)
	    , nAllocLength(0)
	    , after_tr(NULL)
	{}

	char* data() // 存放字符串的地方
	{
		return (char*)(this + 1);
	}
};

/**
 * @brief 字符串(内置引用计数，copy on write)。
 *
 */
class UI_EXP BeStringA
{
  public:
	BeStringA();
	BeStringA(int nLength); ///< nLength是预分配长度
	BeStringA(const BeStringA& stringSrc);

	BeStringA(char ch, int repeats);
	BeStringA(LPCSTR lpsz, int nlen = -1);

	BeStringA(LPCWSTR lpsz, int nlen = -1, UINT codepage = CP_UTF8);
	~BeStringA();

	static void utf8_to_ansi(LPCSTR text, BeStringA& str);

	const char* c_str() const; ///< 获得内存数据

	const BeStringA& operator=(const BeStringA& stringSrc);
	const BeStringA& operator=(LPCSTR lpsz);
	const BeStringA& operator=(LPCWSTR unicode);
	const BeStringA& operator=(char ch);

	BeStringA operator+(const BeStringA& src) const;
	BeStringA operator+(LPCSTR pstr) const;
	const BeStringA& operator+=(const BeStringA& src);
	const BeStringA& operator+=(LPCSTR pstr);
	const BeStringA& operator+=(const char ch);

	bool operator==(const BeStringA& str) const;
	bool operator==(LPCSTR lpsz) const;
	bool operator!=(const BeStringA& str) const;
	bool operator!=(LPCSTR lpsz) const;
	bool operator<(const BeStringA& str) const;
	bool operator>(const BeStringA& str) const;
	bool operator<=(const BeStringA& str) const;
	bool operator>=(const BeStringA& str) const;

	char& operator[](int nIndex) const;

	size_t length() const; ///< 得到字符长度

	size_t capacity() const; ///< 得到分配的内存长度

	bool is_empty() const; ///< 判断字符长度是否为0

	bool is_number() const; ///< 判断是否全部为整数

	bool is_email(); ///< 判断是否是邮箱

	bool is_ipv4(); ///< 判断是否是IPV4地址
	bool is_ipv6(); ///< 判断是否是IPV6地址

	bool is_decimal_number() const; ///< 判断是否为小数

	bool is_true() const;  ///< true
	bool is_false() const; ///< false

	int repeat_counts(char ch); ///< 字符重复的次数

	void empty();

	int erase(int nIndex, int nCount = 1);
	int append(LPCSTR lpsz);
	int append(const char ch);
	int append(LPCSTR lpsz, unsigned int nlen);
	int append(const BeStringA& strSrc);
	int append(const BeStringA& strSrc, unsigned int nlen);

	void join_path(const char* str);

	int insert(int nIndex, char ch); ///< 在nIndex前面插入
	int insert(int nIndex, LPCSTR pstr, int len = -1);

	int replace_char(char chOld, char chNew); ///< 替换
	int replace_string(LPCSTR lpszOld, LPCSTR lpszNew);

	int toInt(bool ExprRecognition = true) const; ///< 转换成数字,当ExprRecognition为true可进行四则运算

	double tofloat(bool ExprRecognition = true) const; ///< 转换 浮点型

	void trim(); ///< 整理字符串, 清除指定字符串
	void trim_left();
	void trim_right();
	void remove(char chTarget);
	void remove(LPCSTR lpszTargets);
	void remove_float_last_zero(); ///<  去除浮点数多余的0后缀
	void make_upper();
	void make_lower();

	BeStringA mid(int nStart, int nCount) const;

	int compare(LPCSTR lpsz) const; ///< 区分大小写 ，<0 表示 自己strself小于lpsz （stringSrc）
	int compare(const BeStringA& stringSrc) const;

	int compare_no_case(LPCSTR lpsz) const; ///< 不区分大小写
	int compare_no_case(const BeStringA& stringSrc) const;

	void format(LPCSTR lpszFormat, ...);
	int find(char ch) const; ///< 查找
	int find(char ch, int nStart) const;
	int reverse_find(char ch) const;
	int find(LPCSTR lpszSub) const;
	int find(LPCSTR lpszSub, int nStart) const;
	int find_one_of(LPCSTR lpszCharSet) const; ///< 得到第一个匹配lpszCharSet中其中一个字符的位置 调用_tcspbrk

  private:
	StringHeadInfoA* get_data() const; // 获得指定的数据结构
	void release();                    // 若引用<= 1释放内存 引用记数器并判断是否删除内存
	void release(StringHeadInfoA* pData);

	void free_string_data(StringHeadInfoA* pData); // 释放指定结构

	void init_string();

	void formate_v(LPCSTR lpszFormat, va_list argList); // 格式化

	int safe_strlen(LPCSTR lpsz);

	void assign_copy(int nSrcLen, LPCSTR lpszSrcData); // 分配字符空间

	void alloc_buffer(int nLen); // 分配内存 并将内存块的数据长度设置为 nLen

	void copy_before_write(); // 脱离数据块

	void free_real_memory(char* pFree);

	unsigned int get_alloc_memsize(unsigned int nlen); // 返回值是内存块的大小

	char* alloc_real_memory(unsigned int nSize);

	static BOOL is_valid_string(LPCSTR lpsz, int nLength = -1);

  private:
	char* m_pchData;
};

class UI_EXP BeStringPairA
{
  public:
	BeStringA m_name;
	BeStringA m_value;

	BeStringPairA();
	BeStringPairA(const BeStringA& name, const BeStringA& value);
	BeStringPairA(const BeStringPairA& pair);
	~BeStringPairA();
};



#if !defined(UNICODE) && !defined(_UNICODE)
typedef BeStringA BeString;
typedef BeStringPairA BeStringPair;
#endif



#endif