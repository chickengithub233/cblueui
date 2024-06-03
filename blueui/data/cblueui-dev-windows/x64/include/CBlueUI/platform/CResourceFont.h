#ifndef CBLUEUI_CRESOURCEFONT_BLXDY_INC_H_
#define CBLUEUI_CRESOURCEFONT_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "platform/GFont.h"

#include <map>

namespace BUI {

enum FONT_SIZE_LEVEL
{
	FLS_LEVEL_0 = 0x01, // 标题字体(值越大，字体越小)
	FLS_LEVEL_0_LOW,
	FLS_LEVEL_1,
	FLS_LEVEL_2,
	FLS_LEVEL_2_LOW,
	FLS_LEVEL_3,
	FLS_LEVEL_4,
	FLS_LEVEL_4_LOW,
	FLS_LEVEL_5,
	FLS_LEVEL_5_LOW,
	FLS_LEVEL_6,
	FLS_LEVEL_7
};

class UI_EXP CResourceFont
{
  private:
	GFont* m_FontNormal[FLS_LEVEL_7];    // 7级普通文体
	GFont* m_FontUnderline[FLS_LEVEL_7]; // 7级下划线字体
	GFont* m_FontBold[FLS_LEVEL_7];      // 7级粗体
	GFont* m_FontItalic[FLS_LEVEL_7];    // 7级斜体
	std::map<BeString, GFont*> mapFont;  // 字体缓存
  public:
	CResourceFont();
	~CResourceFont();

	void AddFont(const BeString& keyid, GFont* hFont);
	GFont* GetFont(LPCTSTR keyid);
	GFont* GetFont(LPCTSTR lpName, int lfHeight, UINT style);
	GFont* GetDefaultFont(SGFontStyle style, FONT_SIZE_LEVEL level);
	void UpdateDefaultFont(SGFontStyle style, int level, GFont* font);
};

/* 字体资源工具集 */
namespace UtilsFont {

	UI_EXP GFont* GetDefaultFont(SGFontStyle style = FS_NORMAL, FONT_SIZE_LEVEL level = FLS_LEVEL_5);

	UI_EXP GFont* GetHFont(LPCTSTR lpName, int lfHeight, UINT style);

	UI_EXP void AddFont(const BeString& keyid, GFont* hFont);
	UI_EXP GFont* GetHFont(LPCTSTR keyid);

	UI_EXP SIZE GetStringSizeByVerChina(const GFont* font, LPCTSTR str); ///< 获得竖排格式(春联样式)文本尺寸
};

/// 安装字体管理对象
extern "C" UI_EXP void InstallResourceFont(CResourceFont* fontMgr);

/// 获得字体管理对象
extern "C" UI_EXP CResourceFont* ResourceFont();

}
#endif
