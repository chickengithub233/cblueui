#ifndef CBLUEUI_SETTING_LITE_BLXDY_INC_H_
#define CBLUEUI_SETTING_LITE_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "core/CCoreBasePro.h"
#include "MarkupItem.h"

namespace BUI {

/**
 * @brief 配置读写类(支持json，xml格式)且读取方式更灵活
 *
 */
class UI_EXP CSettingInfo
{
  public:
	CSettingInfo();
	~CSettingInfo();

	//  清空所有节点
	void Clear();

	/**
	 * @brief 加载配置，解析后的格式为DOM树结构
	 *
	 * @param data 数据流
	 * @param no_write 数据流是否是常量,通常用在程序内部存储在全局常量区的数据流。
	 * @param filetyme 数据格式，xml / json
	 */
	void LoadBuffer(const char* data, BOOL no_write = FALSE, UINT filetyme = 0);

	// 从文件中加载。会自动的根据文件后缀名称匹配
	void LoadFile(const TCHAR* filePath);

	/**
	 * @brief 另存到指定文件目录
	 *
	 * @param filePath 目标输出文件路径
	 * @param is_format 输出格式，xml / json
	 */
	void SaveAsFile(const TCHAR* filePath = NULL, BOOL is_format = TRUE);

	// 根节点
	XMLItem* Root();

	// 当前加载的文件路径
	BeString FilePath();

  protected:
	XMLItem m_treeRoot;
	BeString m_filefullname;
};

extern "C" {

/**
 * @brief 安装全局配置信息对象
 *
 */
UI_EXP void InstallSetingInfo(CSettingInfo* config);

/**
 * @brief 获得全局配置信息对象
 *
 */
UI_EXP CSettingInfo* GetCSettingInfo();
}


}


#endif
