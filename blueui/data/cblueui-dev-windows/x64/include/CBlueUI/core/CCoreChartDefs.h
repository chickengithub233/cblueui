#ifndef CBLUEUI_CCOR_CHART_DEFS_BLXDY_INC_H_
#define CBLUEUI_CCOR_CHART_DEFS_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCoreBasePro.h"

enum CandlesType
{
	KLINE,
	KLINE_USA
};

/// K线样式详情
struct CandlesStyle
{
	COLORREF linecolor; ///< 线颜色
	COLORREF upcolor;   ///< 上行颜色
	COLORREF downcolor; ///< 下行颜色
	COLORREF textcolor; ///< 文本颜色

	CandlesType type;

	CandlesStyle()
	    : linecolor(0x7D7D7D)
	    , upcolor(0x0A0FF3)
	    , downcolor(0x056E0F)
	    , textcolor(0x111111)
	    , type(CandlesType::KLINE)
	{}
};

/// 季度盒子,样式详情
struct BoxPlotStyle
{
	COLORREF linecolor; ///< 线颜色
	COLORREF fillcolor; ///< 填充颜色

	BoxPlotStyle()
	    : linecolor(0x7D7D7D)
	    , fillcolor(0x9999F8)
	{}
};


#endif