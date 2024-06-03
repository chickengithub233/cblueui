#ifndef CBLUEUI_CSVGPATHSTORAGE_H_INCLUDED_
#define CBLUEUI_CSVGPATHSTORAGE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory>
#include <map>
#include "GPathStorage.h"
#include "GBrushGradient.h"
#include "function/MarkupItem.h"

namespace BUI {

struct svg_view_box
{
	double x      = 0;
	double y      = 0;
	double width  = 0;
	double height = 0;
};

struct svg_view_port
{
	double width  = 0;
	double height = 0;
};

enum svg_align
{
	xMinYMin,
	xMinYMid,
	xMinYMax,
	xMidYMin,
	xMidYMid,
	xMidYMax,
	xMaxYMin,
	xMaxYMid,
	xMaxYMax
};

enum svg_preserve_aspect_ratio
{
	meet,
	slice,
	none
};

enum svg_text_align
{
	start,
	middle,
	end
};

struct GradientBrushInfo
{
	TransformGradient gra_transform;
	std::shared_ptr<GradientColors> colors_type;
	BrushStyle grafunc_type;

	union transinfo
	{
		struct linear
		{
			double x1, y1, x2, y2;
		} linear_;

		struct radial
		{
			double cx, cy, r, fx, fy;
		} radial_;
	} transpos;
};

class UI_EXP MetaPathStyle
{
  public:
	unsigned index;
	BeString textid;
	BeString title;
	Transform2d transform;

	GColor fill_color;
	GColor stroke_color;

	UINT line_join; //<line_join_e
	UINT line_cap;  //<line_cap_e
	double miter_limit;
	double stroke_width;

	double dash_offset;
	std::vector<float> dash_arrary;
	svg_text_align textalign;
	unsigned fontsize;
	char fontname[11];
	bool fontweight;
	bool fill_flag;
	bool stroke_flag;
	bool even_odd_flag;
	bool dash_flag;

	GradientBrushInfo gra_brush;

	// Empty constructor
	MetaPathStyle()
	    : index(0)
	    , fill_color(0, 0, 0)
	    , stroke_color(0, 0, 0)
	    , fill_flag(true)
	    , stroke_flag(false)
	    , even_odd_flag(false)
	    , line_join(0)
	    , line_cap(0)
	    , miter_limit(4.0)
	    , stroke_width(1.0)
	    , dash_flag(false)
	    , dash_offset(0)
	    , fontsize(0)
	    , fontweight(false)
	    , textalign(svg_text_align::start)
	{
		memset(fontname, 0, sizeof(fontname));
	}

	// Copy constructor
	MetaPathStyle(const MetaPathStyle& attr)
	    : index(attr.index)
	    , fill_color(attr.fill_color)
	    , stroke_color(attr.stroke_color)
	    , fill_flag(attr.fill_flag)
	    , stroke_flag(attr.stroke_flag)
	    , even_odd_flag(attr.even_odd_flag)
	    , line_join(attr.line_join)
	    , line_cap(attr.line_cap)
	    , miter_limit(attr.miter_limit)
	    , stroke_width(attr.stroke_width)
	    , transform(attr.transform)
	    , dash_flag(attr.dash_flag)
	    , dash_offset(attr.dash_offset)
	    , fontsize(attr.fontsize)
	    , fontweight(attr.fontweight)
	    , textalign(attr.textalign)
	    , dash_arrary(attr.dash_arrary)
	    , gra_brush(attr.gra_brush)
	{
		int maxlen = MIN_(sizeof(fontname), sizeof(attr.fontname));
		memcpy(fontname, attr.fontname, maxlen);
	}
};

/**
 * @brief SVG路径读取类
 *
 */
class UI_EXP GPathStorageSVG : public GPathStorage
{
  public:
	GPathStorageSVG();
	~GPathStorageSVG();

	BOOL LoadFile(const char* fname);
	BOOL LoadData(const char* buffer, int size);
	int PathCounts() const;
	MetaPathStyle& MetaStyle(int i);

	void GetSize(int& w, int& h);

  protected:
	void AddMetaStyle(MetaPathStyle& style, int start_id);

  private:
	void OnParsingMetaMain(XMLItemA* node, MetaPathStyle& style);
	void OnParsingViewBox(XMLItemA* node);
	// int  OnParsingUseType(MetaPathStyle& style, XMLItemA* node, svg_view_box& useBox);

	int OnParsingPath(XMLItemA* node, MetaPathStyle& style);
	int OnParsingLine(XMLItemA* node, MetaPathStyle& style);

	int OnParsingRect(XMLItemA* node, MetaPathStyle& style);
	int OnParsingCircle(XMLItemA* node, MetaPathStyle& style);
	int OnParsingEllipse(XMLItemA* node, MetaPathStyle& style);
	int OnParsingPolygon(XMLItemA* node, MetaPathStyle& style);
	int OnParsingPolyline(XMLItemA* node, MetaPathStyle& style);
	BOOL OnParsingMetaStyle(MetaPathStyle* attr, XMLItemA* node);
	BOOL OnParsingGraphStyle(MetaPathStyle* attr, const char* key, const char* value, XMLItemA* usenode);
	BOOL OnParsingGradient(MetaPathStyle* attr, XMLItemA* node);

  public:
	std::map<std::string, GradientBrushInfo> m_share_colors;
	std::vector<MetaPathStyle> m_style_storage;
	BeString m_title;
	Transform2d m_transform;
	double m_unit;
	svg_view_box m_view_box;
	svg_view_port m_view_port;

	svg_preserve_aspect_ratio m_AspectRatio;
	svg_align m_align;
	double m_xScale;
	double m_yScale;
	double m_x;
	double m_y;

  protected:
	XMLItemA* m_root;
};



}
#endif
