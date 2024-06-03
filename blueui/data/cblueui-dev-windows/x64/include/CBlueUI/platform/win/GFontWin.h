#ifndef CBLUEUI_UIFONT_INCLUDED_
#define CBLUEUI_UIFONT_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "graphics/GExtentText.h"
#include "graphics/GPathStorage.h"

#include <vector>

namespace BUI {

class UI_EXP GFont
{
  public:
	GFont();

	~GFont();

	/**
	 * @brief Create a Font Object object
	 *
	 * @param name 字体名称
	 * @param fHeight 字体高度
	 * @param style 字体风格:SGFontStyle={FS_BOLD,FS_ITALIC,FS_UNDERLINE}
	 */
	void CreateFontObject(LPCTSTR name, int fHeight, UINT style);

	int FontPixelHeight() const;
	int FontPointHeight() const;
	UINT FontStyle() const;
	LPCTSTR FontName() const;

	SIZE GetTextSize(LPCTSTR text, int len = -1) const;
	SIZE GetTextSizeW(LPCWSTR text, int len = -1) const;
	SIZE GetTextSizeA(const char* text, int len = -1) const;

	void GetTextCharsSize(LPCTSTR text, std::vector<int>& outList) const; ///< 将字符串每个字符的宽度，读取到数组中

	int GetTextSizeWithNewline(LPCTSTR text, int len, TextMultilineInfo* textinfo, BOOL isOnlyMaxSize = FALSE) const;

	int GetTextGlyph(GPathStorage& path, LPCTSTR text, int len, int word_space = 0);

  protected:
	BeString m_fontname; // 字体名称
	int m_fHeight;       // 字体像素高度
	int m_pointHeight;   // 字体点高度
	UINT m_fStyle;

  public:
	HFONT m_hFontGDI;
	LOGFONT m_lf;
	int m_dy;
};

}

#endif
