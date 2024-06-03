#ifndef CBLUEUI_BASE_MARKUPITEM_BLXDY_INC_H_
#define CBLUEUI_BASE_MARKUPITEM_BLXDY_INC_H_

#include "core/CCoreBasePro.h"
#include "cstring/StringA.h"
#include "cstring/String.h"
#include <vector>


/* JSON Types: */
#define JSON_NULL   0
#define JSON_False  1
#define JSON_True   2
#define JSON_Object 3
#define JSON_Array  4
#define JSON_String 5
#define JSON_Number 6

namespace BUI {

UI_EXP void ParseLayoutModel(LPCTSTR szText, int* wl, int* hl, SizeMode* tw, SizeMode* th);

class UI_EXP XMLItemA
{
  public:
	XMLItemA();
	~XMLItemA();

	BeStringPairA& LabelPair();

	/**
	 * @brief 脱离dom结构
	 *
	 * @param isReleaseAllChild 当为TRUE时，并且释放所有孩子节点占用内存，初始化为NULL。为FALSE时 仅脱离dom结构，并保留孩子节点
	 */
	void BreakAway(BOOL isReleaseAllChild);

	// 释放所有孩子节点
	void ReleaseChild();

	size_t GetChildCounts() const;
	XMLItemA* GetChildObject(int index) const;
	BeStringPairA& AttrbuteTextPair(unsigned int i);

	unsigned int AttrbuteCount() const;

	void AppendAttrbute(BeStringA key, BeStringA value);

	XMLItemA* FirstChild() const;

	XMLItemA* LastChild() const;

	XMLItemA* PrevSibling() const;

	XMLItemA* NextSibling() const;

	XMLItemA* Parent() const;

	void RemoveAllAttrbute();              ///< 删除所有属性
	void RemoveAttrbute(const char* name); ///< 删除指定属性

	BOOL SetAttribute(const char* name, const BeStringA& str_value); ///< 设置属性值

	BOOL FindAttribute(const char* name, BeStringA& outstr);

	long FindAttributeInt(const char* name, long default_value);

	double FindAttributeFloat(const char* name, double default_value);

	XMLItemA* FindChildByName(const char* name) const;

	/**
	 * @brief 一次读取层级节点信息。通过不断匹配keyPath的方式向深层次节点查找，直到匹配。例如<a><b><c>123</c></b><c>
	 *
	 * @param keyPath  "a.b.c"(此时树状结构<a><b><c>123</c></b><c>)
	 * @return XMLItemA* 返回匹配的节点
	 */
	XMLItemA* FindObjectByKeyPath(const char* keyPath) const;

	/**
	 * @brief 根据执行属性名的值，为一次读取层级节点信息。通过不断匹配keyPath的方式向深层次节点查找，直到匹配
	 *
	 * @param attrName
	 * @param attrPath  "a.b.c"(此时树状结构<var id="a"><var id="b"><var id="c">123</c></b><c>)
	 * @return XMLItemA* 返回匹配的节点
	 */
	XMLItemA* FindObjectByAttributePath(const char* attrName, const char* attrPath) const;

	/**
	 * @brief 标准化树(将单一子节点，设置为节点的属性值)
	 *
	 * @param callback_free  释放节点回调函数
	 */
	void StandardizationItem(void (*callback_free)(XMLItemA* node) = NULL);

	XMLItemA* AppendChild(const char* key = NULL, const char* value = NULL, int type = -1);

	void Print(FILE* fp, BOOL bFormate, int depth);

	/**
	 * @brief 将otherNode克隆到this节点。用于存储
	 *
	 * @param otherNode  被克隆对象
	 */
	void Clone(XMLItemA* otherNode);

	// 不用递归的遍历时调用
	static XMLItemA* NextItem(XMLItemA* item);

  protected:
	XMLItemA* AllocXmlNode(int type);

  public:
	XMLItemA* parent;
	XMLItemA* firstChild;
	XMLItemA* lastChild;
	XMLItemA* prevSibling;
	XMLItemA* nextSibling;
	BeStringPairA label;
	std::vector<BeStringPairA> attributeList;
	int type_;
};

class UI_EXP XMLItemW
{
  public:
	XMLItemW();
	~XMLItemW();

	BeStringPairW& LabelPair();


	/**
	 * @brief 脱离dom结构
	 *
	 * @param isReleaseAllChild 当为TRUE时，并且释放所有孩子节点占用内存，初始化为NULL。为FALSE时 仅脱离dom结构，并保留孩子节点
	 */
	void BreakAway(BOOL isReleaseAllChild);

	// 释放所有孩子节点
	void ReleaseChild();

	size_t GetChildCounts() const;
	XMLItemW* GetChildObject(int index) const;
	BeStringPairW& AttrbuteTextPair(unsigned int i);

	unsigned int AttrbuteCount() const;

	void AppendAttrbute(BeStringW key, BeStringW value);

	XMLItemW* FirstChild() const;

	XMLItemW* LastChild() const;

	XMLItemW* PrevSibling() const;

	XMLItemW* NextSibling() const;

	XMLItemW* Parent() const;

	void RemoveAllAttrbute(); ///< 删除所有属性

	void RemoveAttrbute(const WCHAR* name); ///< 删除指定属性

	BOOL SetAttribute(const WCHAR* name, const BeStringW& str_value); ///< 设置属性值

	BOOL FindAttribute(const WCHAR* name, BeStringW& outstr);

	long FindAttributeInt(const WCHAR* name, long default_value);

	double FindAttributeFloat(const WCHAR* name, double default_value);

	XMLItemW* FindChildByName(const WCHAR* name) const;

	/**
	 * @brief 一次读取层级节点信息。通过不断匹配keyPath的方式向深层次节点查找，直到匹配。例如<a><b><c>123</c></b><c>
	 *
	 * @param keyPath  "a.b.c"(此时树状结构<a><b><c>123</c></b><c>)
	 * @return XMLItemA* 返回匹配的节点
	 */
	XMLItemW* FindObjectByKeyPath(const WCHAR* keyPath) const;

	/**
	 * @brief 根据执行属性名的值，为一次读取层级节点信息。通过不断匹配keyPath的方式向深层次节点查找，直到匹配
	 *
	 * @param attrName
	 * @param attrPath  "a.b.c"(此时树状结构<var id="a"><var id="b"><var id="c">123</c></b><c>)
	 * @return XMLItemA* 返回匹配的节点
	 */
	XMLItemW* FindObjectByAttributePath(const WCHAR* attrName, const WCHAR* attrPath) const;

	/**
	 * @brief 标准化树(将单一子节点，设置为节点的属性值)
	 *
	 * @param callback_free  释放节点回调函数
	 */
	void StandardizationItem(void (*callback_free)(XMLItemW* node) = NULL);

	XMLItemW* AppendChild(const WCHAR* key = NULL, const WCHAR* value = NULL, int type = -1);

	void Print(FILE* fp, BOOL bFormate, int depth);

	/**
	 * @brief 将otherNode克隆到this节点。用于存储
	 *
	 * @param otherNode  被克隆对象
	 */
	void Clone(XMLItemW* otherNode);

	// 不用递归的遍历时调用
	static XMLItemW* NextItem(XMLItemW* item);

  protected:
	XMLItemW* AllocXmlNode(int type);

  public:
	XMLItemW* parent;
	XMLItemW* firstChild;
	XMLItemW* lastChild;
	XMLItemW* prevSibling;
	XMLItemW* nextSibling;
	BeStringPairW label;
	std::vector<BeStringPairW> attributeList;
	int type_;
};

#if defined(UNICODE) || defined(_UNICODE)
typedef XMLItemW XMLItem;
#else
typedef XMLItemA XMLItem;
#endif

}

#endif