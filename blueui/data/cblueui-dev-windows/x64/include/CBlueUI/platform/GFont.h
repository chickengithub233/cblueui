#ifndef CBLUEUI_UIFONT_PLATFORM_BLXDY_INC_H_
#define CBLUEUI_UIFONT_PLATFORM_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef FT2_BUILD_LIBRARY
#include "platform/SDL2/OnTTF/GFontTTF.h"
#elif (defined CBLUEUI_USE_LIB_QT)
#include "platform/qt/GFontQt.h"
#elif (defined USE_LIB_FLTK)
#include "platform/fltk/GFontFLTK.h"
#elif (defined CBLUEUI_USE_LIB_GTK3)
#include "platform/gtk3/GFontGTK.h"
#elif (defined CBLUEUI_USE_LIB_GTKMM4)
#include "platform/gtkmm4/GFontGTKMM.h"
#elif (defined CBLUEUI_USE_LIB_WXWIDGET)
#include "platform/wxWidget/GFontWxWidgets.h"
#elif defined __APPLE__
#include "platform/SDL2/OnCocoa/GFontCocoa.h"
#elif defined _WIN32
#include "platform/win/GFontWin.h"
#endif



#endif
