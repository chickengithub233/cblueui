#ifndef CBLUEUI_XML_XMLSTORAGEA_BLXDY_INC_H_
#define CBLUEUI_XML_XMLSTORAGEA_BLXDY_INC_H_

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


typedef BOOL (*TransformTextProcA)(BeStringA& outstr, LPCSTR text);

namespace BUI {


/**
 * @brief xml文件储存类。xml文件中大量重复标签，采用共享字符串的方式，减少内存占用
 *
 */
class UI_EXP XmlStorageA
{
  private:
	TransformTextProcA m_key_transform;
	XMLItemA m_treeRoot;
	BeString m_filebaseName;
	std::vector<BeStringA> m_share;

  public:
	static void SaveAsXmlFile(const XMLItemA* root, const char* filepath);

	XmlStorageA(TransformTextProcA func = NULL);
	XmlStorageA(const char* file_utf8, TransformTextProcA func = NULL);
	XmlStorageA(const WCHAR* file, TransformTextProcA func = NULL);

	~XmlStorageA();

	XMLItemA* Root(); ///< 跟节点

	/**
	 * @brief 加载xml格式数据
	 *
	 * @param xmlText 数据
	 * @param len 数据长度
	 * @param no_write TRUE代表xmlText是不可写字符串，解析常量字符串时，需要标记为TRUE
	 */
	int LoadBuffer(const char* xmlText, int len = -1, BOOL no_write = FALSE);

	/**
	 * @brief 加载json数据并转换为xml树结构
	 *
	 * @param jsonText 数据
	 * @param len 数据长度
	 */
	int LoadBufferJson(const char* jsonText, int len = -1);

	BeStringA AddShareLabel(const char* str, int len, BOOL isKey = FALSE);
	BeString FileBaseName() const;
};

#if !defined(UNICODE) && !defined(_UNICODE)
typedef XmlStorageA XmlStorage;
#endif

}
#endif