/*
 * 刻度线风格封装类
 */

#ifndef CBLUEUI_GTICKMARKSSTYLE_BLXDY_INC_H_
#define CBLUEUI_GTICKMARKSSTYLE_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "core/CCoreBasePro.h"

namespace BUI {
class UI_EXP GTickMarksStyle
{
  public:
	GTickMarksStyle();
	~GTickMarksStyle();

  public:
	int m_ntickCount;            // 小刻度数量
	int m_nTickSize;             // 小刻度线长
	TickMarkPositon m_markModel; // 刻度位置
	COLORREF m_tickColor;        // 线颜色
};


}

#endif