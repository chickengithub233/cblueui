#ifndef CBLUEUI_CSKININFO_BLXDY_INC_H_
#define CBLUEUI_CSKININFO_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <atomic>
#include "core/CCoreBasePro.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "XmlStorageA.h"
#include "XmlStorage.h"

namespace BUI {


/**
 * @brief 提取单个皮肤文件中的风格信息
 *
 */
class UI_EXP CSkinStyle
{
  public:
	typedef std::vector<BeStringPairA> list_string_pair;

  public:
	CSkinStyle();
	~CSkinStyle();

	void LoadSkinFile(LPCTSTR file);

	size_t SkinCount() const;

	BeString ModuleName();
	const list_string_pair* FindSkin(const BeString& skinid);
	const list_string_pair* FindStyle(const BeString& stylename);

  private:
	std::map<BeString, list_string_pair> m_share_styles; // 风格储存
	std::map<BeString, list_string_pair> m_skins;        // 皮肤
	BeString m_skin_module_name;                         // 模块名
#ifdef _DEBUG
	BeString m_skin_file_full_name;
#endif
};

/**
 * @brief 皮肤管理类
 *
 */
class UI_EXP CManagerSkin
{

  public:
	CManagerSkin();
	~CManagerSkin();

	void LoadSkinFile(LPCTSTR file);

	size_t Size();

	CSkinStyle* GetSkinFile(LPCTSTR skin_module_name); ///< 获得皮肤文件对象
  private:
	std::map<BeString, CSkinStyle> m_skin_files; // 所有皮肤映射关系
};

/**
 * @brief 语言翻译类
 *
 */
class UI_EXP CLanguageTranslator
{
  public:
	CLanguageTranslator();
	~CLanguageTranslator();


	/**
	 * @brief : 加载语言文件
	 * @return: void
	 * @param : LPCSTR file 文件路径
	 * @param : BOOL bClear TRUE:清除原来的语言映射关系。
	 */
	void LoadLanguageFile(LPCTSTR file, BOOL bClear = TRUE);

	BOOL TranslateToBeString(BeString& out_text, LPCTSTR text, BOOL init = FALSE);

	void ClearFromLanguages();

  private:
	BOOL FindFromLanguagesKey(BeString& text_key, LPCTSTR keyid);

  private:
	std::map<BeString, BeString> m_languages_pre; // 当前语言列表 EN -> ZH
	std::map<BeString, BeString> m_languages;     // 文件中加载的翻译语言映射表 ZH -> RU

	std::map<BeString, BeString> m_trans_result_buf_w; // 结果缓存
};

extern "C" {

/**
 * @brief 安装语言管理对象
 *
 */
UI_EXP void InstallLanguageTranslator(CLanguageTranslator* lang_trans);

/**
 * @brief 获得语言管理对象
 *
 */
UI_EXP CLanguageTranslator* LanguageTranslator();

UI_EXP BOOL LangTranslateToBeString(BeString& out_text, LPCTSTR text, BOOL init = FALSE);

UI_EXP BOOL LangTranslate(BeString& outstr, LPCTSTR text);
}


}


#endif
