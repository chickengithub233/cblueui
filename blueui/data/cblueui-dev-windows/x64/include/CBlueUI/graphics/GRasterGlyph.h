#ifndef CBLUEUI_CGLYPHRASTER_BLXDY_INC_H_
#define CBLUEUI_CGLYPHRASTER_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"

class UI_EXP GRasterGlyph
{
  public:
	GRasterGlyph(const UINT8* font, unsigned glyph_index);
	GRasterGlyph(const UINT8* bits);

	GRasterGlyph(const UINT8* bits, UINT w, UINT h);

	~GRasterGlyph();

	void Attach(const UINT8* font, unsigned glyph_index);
	void Attach(const UINT8* bits);
	UINT width() const;
	UINT height() const;

	const UINT8* Bits() const;

  protected:
	const UINT8* m_bits;
	UINT m_width_;
	UINT m_height_;
};

/* bitmap mono font (点阵位图字体等宽字体)*/
class UI_EXP UIFontBM
{
  public:
	UIFontBM(unsigned char* bits, int w, int h);

	~UIFontBM();

	unsigned char* GetGlphyByIndex(int i) const;

	UINT Width() const;
	UINT Height() const;
	UINT GlphySize() const;

  protected:
	unsigned char* bitmapdata_;
	UINT w_;
	UINT h_;
};


#endif
