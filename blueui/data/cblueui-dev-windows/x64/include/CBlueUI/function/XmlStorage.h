#ifndef CBLUEUI_XML_XMLSTORAGEW_BLXDY_INC_H_
#define CBLUEUI_XML_XMLSTORAGEW_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <assert.h>
#include <string>
#include <vector>

#include "core/CCoreBasePro.h"
#include "cstring/StringA.h"
#include "cstring/String.h"
#include "MarkupItem.h"


typedef BOOL (*TransformTextProcW)(BeStringW& outstr, LPCWSTR text);

namespace BUI {

/**
 * @brief xml文件储存类。xml文件中大量重复标签，采用共享字符串的方式，减少内存占用
 *
 */
class UI_EXP XmlStorageW
{
  private:
	TransformTextProcW m_key_transform;
	XMLItemW m_treeRoot;
	BeStringW m_filebaseName;
	std::vector<BeStringW> m_share;

  public:
	static void SaveAsXmlFile(const XMLItemW* root, const char* filepath);

	XmlStorageW(TransformTextProcW func = NULL);
	XmlStorageW(const char* file_utf8, TransformTextProcW func = NULL);
	XmlStorageW(const WCHAR* file, TransformTextProcW func = NULL);
	~XmlStorageW();

	XMLItemW* Root(); ///< 跟节点

	/**
	 * @brief 加载xml格式数据
	 *
	 * @param data 数据
	 * @param len 数据长度
	 * @param no_write TRUE代表xmlText是不可写字符串，解析常量字符串时，需要标记为TRUE
	 */
	int LoadBuffer(const char* data, int len = -1, BOOL no_write = FALSE);

	/**
	 * @brief 加载json数据并转换为xml树结构
	 *
	 * @param jsonText 数据
	 * @param len 数据长度
	 */
	int LoadBufferJson(const char* jsonText, int len = -1);

	BeStringW AddShareLabel(const char* str, int len, BOOL isKey = FALSE);
	BeStringW FileBaseName() const;
};

#if defined(UNICODE) || defined(_UNICODE)
typedef XmlStorageW XmlStorage;
#endif


}
#endif