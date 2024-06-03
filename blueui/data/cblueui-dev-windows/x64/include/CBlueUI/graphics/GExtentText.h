#ifndef CBLUEUI_GEXTENTTEXT_INCLUDED_
#define CBLUEUI_GEXTENTTEXT_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include <vector>

struct SinglelineText
{
	SIZE sz;
	LPCTSTR text;
	int len;

	SinglelineText()
	    : text(NULL)
	    , len(0)
	{
		sz.cx = sz.cy = 0;
	}
};

#define MAX_MULTI_LINES 10

class UI_EXP TextMultilineInfo
{
  public:
	TextMultilineInfo();
	~TextMultilineInfo();

	int GetLineCount() const;
	SIZE GetMaxSize() const;
	SinglelineText GetSinglelineText(int index) const;

	/**
	 * @brief  添加单行信息
	 *
	 * @param  info: 单行信息
	 * @param  isOnlyMaxSize: TRUE 只计算最大的尺寸，此时每一行的信息不记录
	 */
	void AddSinglelineText(SinglelineText info, BOOL isOnlyMaxSize = TRUE);

  protected:
	int m_lines; // 行数
	SIZE m_max_size;
	SinglelineText m_line_size[MAX_MULTI_LINES];
	std::vector<SinglelineText> m_line_size_ex;
};





#endif