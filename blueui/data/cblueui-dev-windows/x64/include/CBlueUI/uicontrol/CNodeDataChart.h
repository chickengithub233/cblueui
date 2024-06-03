
#ifndef CBLUEUI_CNODEDATACHART_XBYMD_INCLUDED_
#define CBLUEUI_CNODEDATACHART_XBYMD_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <memory>
#include "CNodeData.h"
#include "graphics/GStyleMarkShape.h"

namespace BUI {

/**
 * @brief mark标记
 *
 */
class UI_EXP CNodeDataLegendMark : public GStyleMarkShape, public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataLegendMark)
  public:
	CNodeDataLegendMark();
	~CNodeDataLegendMark();
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;
};

/**
 * @brief 线条标记
 *
 */
class UI_EXP CNodeDataLegendLine : public GPenInfo, public CNodeData
{
	DECLARE_DYNAMIC_OBJ_CLASS(CNodeDataLegendLine)
  public:
	CNodeDataLegendLine();
	CNodeDataLegendLine(GPointF p1, GPointF p2);

	~CNodeDataLegendLine();
	/* CNodeData method:*/
	void OnDrawNodeData(ISurface* pSurface, int paintState, RECT rcCell, COLORREF textColor, UINT textAlignFlag, PathTransInfo* clipborderpath = NULL) override;
	void ShellNodeDataAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	GPointF m_pt1;
	GPointF m_pt2;
};


} // #namespace




#endif
