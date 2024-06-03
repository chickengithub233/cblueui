#ifndef CBLUEUI_FILESYSTEM_BLXDY_INC_H_
#define CBLUEUI_FILESYSTEM_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <string>

#include "core/CCoreBasePro.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "cstring/StringShort.h"

enum DirectoryType
{
	Directory_APP,    ///< app当前运行目录
	Directory_Desktop ///< 桌面目录
};

enum OpenFileModel
{
	OPEN_FILE      = 0x01, // 选择单个文件
	OPEN_FILE_SAVE = 0x02, // 保存文件夹
	OPEN_FILES     = 0x04, // 选择多个文件
	OPEN_DIR       = 0x08, // 选择文件夹
};

struct FileTreeInfo
{
	BeString file_name;
	BeString file_full_name;
	BOOL isDir;
	std::vector<FileTreeInfo> childs;

	FileTreeInfo() { isDir = TRUE; }
};

namespace UtilsFileSystem {

UI_EXP BeString GetSystemDir(DirectoryType type);

/// 验证文件夹是否存在
UI_EXP BOOL IsExistsW(LPCWSTR folder);

/// 验证文件夹是否存在
UI_EXP BOOL IsExistsA(LPCSTR folder);

/// 创建文件夹
UI_EXP BOOL MakeDirA(LPCSTR folder);

/// 创建文件夹
UI_EXP BOOL MakeDirW(LPCWSTR folder);

/**
 * @brief 获取指定目录的子目录列表
 *
 * @param vecDir [out] 存放返回结果
 * @param folder [in] 检索目录
 * @param depth [in] 递归检索次数，0(不限次数)
 * @param isTreeResult 结果是否保留层级树状结构
 * @return UI_EXP
 */
UI_EXP void GetDirectorys(FileTreeInfo& fsTree, int depth = 0, BOOL isTreeResult = FALSE);

/**
 * @brief 获得当前文件夹内的全部文件
 *
 * @param vecFile [out] 存放返回结果
 * @param folder [in] 检索目录
 * @param postfix [in] 后缀名称，为空检索所有文件(.zip .txt .exe .dmg .png .jpg )
 * @param depth  [in] 递归检索次数，-1(不限次数),
 * @param isTreeResult 结果是否保留层级树状结构
 * @return UI_EXP
 */

UI_EXP void GetFiles(FileTreeInfo& fsTree, LPCTSTR postfix, int depth = 0, BOOL isTreeResult = FALSE);


/**
 * @brief 获得当前文件夹内的全部文件
 *
 * @param LPCTSTR filter e.g. "C file(*.c *.cpp *.h);;pic(*.png *.xpm)";
 * @return UI_EXP
 */
UI_EXP void GetOpenPath(OpenFileModel model, LPCTSTR title, LPCTSTR filter, LPCTSTR init_path, BasicStringBuffer* path, std::vector<BeString>* pathlist = NULL);


#ifdef UNICODE
#define IsExists IsExistsW
#else
#define IsExists IsExistsA
#endif
};

// ui open file event Info




#ifdef UNICODE

struct WParamOpenFile
{
	UINT open_type;
	std::w16string title;
	std::map<std::w16string, std::w16string> filter;
	std::vector<std::w16string> outpaths;
};

#else

struct WParamOpenFile
{
	UINT open_type;
	std::string title;
	std::map<std::string, std::string> filter;
	std::vector<std::string> outpaths;
};

#endif


struct WParamOpenFont
{
	BOOL isSuccess;
	TCHAR faceName[32];
	int height;
	int weight;
	bool isItalic;
};

struct WParamOpenColor
{
	BOOL isSuccess;
	COLORREF color;
};


#endif
