/**********************************************************************************
CBlueUI library.
Copyright (C) 2015  CBlueUI Studio<2842004379@qq.com>

Declaration
All rights reserved.
China

This software is released under the "CBlueUI License" (hereinafter referred to as the "License").
You may only use and distribute this software in accordance with the terms and conditions of the License.
Please make sure that you have read, understood, and accepted all the provisions of the License before using this software.
If you do not agree with any provisions of the License, you are not authorized to use this software.

This software is provided "as is" without any warranty, expressed or implied.
The author and copyright owner expressly disclaim any warranties, including but not limited to the implied warranties
of merchantability, fitness for a particular purpose, and non-infringement. In no event shall the author or copyright owner
be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to,
procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and
on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in
any way out of the use of this software, even if advised of the possibility of such damage.

For further details about the License, please refer to the license document.

声明：
保留所有权利
中国
本软件是根据CBlueUI许可证（下称“协议”）发布的，您只能在符合协议规定的条件下使用和分发本软件。
请确保在使用本软件之前，您已阅读、理解并接受协议的所有条款和条件。如果您不同意协议的任何规定，您将无权使用本软件。

本软件在不作任何明示或暗示的情况下，以“原样”提供。作者和版权所有者明确声明不提供任何形式的明示或暗示保证，包括但不限于
对该软件的适用性、适销性或特定用途的适用性的暗示保证。在任何情况下，作者和版权所有者对于使用本软件所导致的任何直接、间接、
附带的或特殊的损失或责任不承担任何责任。

如需详细了解协议的内容，请参考协议文档。

**********************************************************************************/


#ifndef CBLUEUI_LIBRARY_PRO_BLXDY_INC_H_
#define CBLUEUI_LIBRARY_PRO_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef _WIN32
#if defined(BUILD_SHARED_DLL)
#define UI_EXP __declspec(dllexport)
#else
#ifdef UI_USE_DLL
#define UI_EXP __declspec(dllimport)
#else
#define UI_EXP // use source code
#endif
#endif
#else
#define UI_EXP // use source code
#endif

#define MSGCALLBACK __stdcall

#if defined(_MSC_VER)
#define _API_INLINE __forceinline
#else
#define _API_INLINE inline
#endif

#ifdef USE_VLD_MEMORY_LEAK_CHECK
#include "@var_USE_VLD@"
#endif

// c std header
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <float.h>
#include <math.h>

#ifdef _MSC_VER

#if _MSC_VER >= 1600
#include <stdint.h>
#else
#include <limits.h>
#if (_MSC_VER < 1300)
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#else
typedef signed __int8 int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
#endif // (_MSC_VER < 1300)
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif // _MSC_VER >= 1600
#endif // _MSC_VER



// c++ std header
#include <queue>
#include <deque>
#include <string>
#include <algorithm>

#if defined(WIN32)

#ifdef CBLUEUI_USE_LIB_WXWIDGET
#include <WinSock2.h>
#else

#define _WINSOCKAPI_
#include <Windows.h>

#endif // CBLUEUI_USE_LIB_WXWIDGET

#include <io.h>
#include <tchar.h>
#include <wchar.h>
#endif // WIN32

#include "CCoreVirtualKeys.h"

//------------------------------------------------------------------------
// memory free
#define SAFEDEL(p) \
	do { \
		if (p) delete (p); \
		(p) = NULL; \
	} while (0)
#define SAFEDEL_ARRAY(p) \
	do { \
		if (p) delete[] (p); \
		(p) = NULL; \
	} while (0)
#define SAFEDEL_C(p) \
	do { \
		if (p) free((p)); \
	} while (0)

#define SKIP_CHAR_SPACE(p) \
	while ((p) && *(p) != '\0' && (*(p) == ' ' || *(p) == '\n' || *(p) == '\t' || *(p) == '\r')) ++(p)

//------------------------------------------------------------------------

#define CREATE_OBJECT(classname) (new classname)

#define MAX_(a, b) (((a) > (b)) ? (a) : (b))
#define MIN_(a, b) (((a) < (b)) ? (a) : (b))



#define BOOL_FALSE   0
#define BOOL_TRUE    1
#define BOOL_UNKNOWN 2


#define SBF_HORZ 0x01 // horizontal scroll type
#define SBF_VERT 0x02 // vertical scroll type

typedef unsigned long ULONG;
typedef unsigned char UBYTE;
typedef unsigned char UINT8;


#define CP_UTF16 44 // UTF-16 translation
#define CP_UTF32 45 // UTF-32 translation



#define DT_TEXT_VERTICAL             0x00400000 // 文本竖排(即旋转90°)
#define DT_TEXT_VERTICAL_CHINA       0x00800000 // 文本竖排(春联方式)
#define DT_TEXT_ICON_END             0x01000000 // 文本图标混排图标后置
#define DT_TEXT_ICON_VERTICAL_LAYOUT 0x02000000 // 文本图标混排垂直分布
#define DT_TEXT_RECT                 0x04000000 // 获得文本区域


#define SW_FULLMAXIMIZE 13

#if !defined(WIN32)

//
//  Code Page Default Values.
//  Please Use Unicode, either UTF-16 (as in WCHAR) or UTF-8 (code page CP_ACP)
//
#define CP_ACP        0  // default to ANSI code page
#define CP_OEMCP      1  // default to OEM  code page
#define CP_MACCP      2  // default to MAC  code page
#define CP_THREAD_ACP 3  // current thread's ANSI code page
#define CP_SYMBOL     42 // SYMBOL translations

#define CP_UTF7 65000 // UTF-7 translation
#define CP_UTF8 65001 // UTF-8 translation

#define WM_USER            0x0400
#define FALSE              0
#define TRUE               1
#define DT_TOP             0x00000000
#define DT_LEFT            0x00000000
#define DT_CENTER          0x00000001
#define DT_RIGHT           0x00000002
#define DT_VCENTER         0x00000004
#define DT_BOTTOM          0x00000008
#define DT_WORDBREAK       0x00000010
#define DT_SINGLELINE      0x00000020
#define DT_EXPANDTABS      0x00000040
#define DT_TABSTOP         0x00000080
#define DT_NOCLIP          0x00000100
#define DT_EXTERNALLEADING 0x00000200
#define DT_CALCRECT        0x00000400
#define DT_NOPREFIX        0x00000800
#define DT_INTERNAL        0x00001000
#define DT_EDITCONTROL     0x00002000
#define DT_END_ELLIPSIS    0x00008000


/*
 * Menu flags for Add/Check/EnableMenuItem()
 */
#define MF_BYCOMMAND  0x00000000L
#define MF_CHECKED    0x00000008L
#define MF_POPUP      0x00000010L
#define MF_BYPOSITION 0x00000400L
#define MF_SEPARATOR  0x00000800L

/*
 * Flags for TrackPopupMenu
 */
#define TPM_LEFTBUTTON   0x0000L
#define TPM_RIGHTBUTTON  0x0002L
#define TPM_LEFTALIGN    0x0000L
#define TPM_CENTERALIGN  0x0004L
#define TPM_RIGHTALIGN   0x0008L
#define TPM_TOPALIGN     0x0000L
#define TPM_VCENTERALIGN 0x0010L
#define TPM_BOTTOMALIGN  0x0020L

#define TPM_HORIZONTAL 0x0000L /* Horz alignment matters more */
#define TPM_VERTICAL   0x0040L /* Vert alignment matters more */
#define TPM_NONOTIFY   0x0080L /* Don't send any notification msgs */
#define TPM_RETURNCMD  0x0100L


/*
 * AnimateWindow() Commands
 */
#define AW_HOR_POSITIVE 0x00000001
#define AW_HOR_NEGATIVE 0x00000002
#define AW_VER_POSITIVE 0x00000004
#define AW_VER_NEGATIVE 0x00000008
#define AW_CENTER       0x00000010
#define AW_HIDE         0x00010000
#define AW_ACTIVATE     0x00020000
#define AW_SLIDE        0x00040000
#define AW_BLEND        0x00080000

/*
 * WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
 */
#define HTERROR       (-2)
#define HTTRANSPARENT (-1)
#define HTNOWHERE     0
#define HTCLIENT      1
#define HTCAPTION     2
#define HTSYSMENU     3
#define HTGROWBOX     4
#define HTSIZE        HTGROWBOX
#define HTMENU        5
#define HTHSCROLL     6
#define HTVSCROLL     7
#define HTMINBUTTON   8
#define HTMAXBUTTON   9
#define HTLEFT        10
#define HTRIGHT       11
#define HTTOP         12
#define HTTOPLEFT     13
#define HTTOPRIGHT    14
#define HTBOTTOM      15
#define HTBOTTOMLEFT  16
#define HTBOTTOMRIGHT 17
#define HTBORDER      18

#define IDOK        1
#define IDCANCEL    2
#define WHEEL_DELTA 120

#define SW_HIDE            0
#define SW_SHOWNORMAL      1
#define SW_NORMAL          1
#define SW_SHOWMINIMIZED   2
#define SW_SHOWMAXIMIZED   3
#define SW_MAXIMIZE        3
#define SW_SHOWNOACTIVATE  4
#define SW_SHOW            5
#define SW_MINIMIZE        6
#define SW_SHOWMINNOACTIVE 7
#define SW_SHOWNA          8
#define SW_RESTORE         9
#define SW_SHOWDEFAULT     10
#define SW_FORCEMINIMIZE   11
#define SW_MAX             11



#ifdef __APPLE__
typedef bool BOOL;
#else
typedef int BOOL;
#endif

// typedef int                 BOOL;

typedef char CHAR;
typedef signed char INT8;
typedef unsigned char UCHAR;
typedef unsigned char UINT8;
typedef unsigned char BYTE;
typedef BYTE* LPBYTE;
typedef short SHORT;
typedef signed short INT16;
typedef unsigned short USHORT;
typedef unsigned short UINT16;
typedef unsigned short WORD;
typedef int INT;
typedef signed int INT32;
typedef unsigned int UINT;
typedef unsigned int UINT32;
typedef int LONG;
typedef unsigned long ULONG;
typedef unsigned long DWORD;
typedef long long int LONGLONG;
typedef long long int LONG64;
typedef long long int INT64;
typedef unsigned long long int ULONGLONG;
typedef unsigned long long int DWORDLONG;
typedef unsigned long long int ULONG64;
typedef unsigned long long int DWORD64;
typedef unsigned long long int UINT64;
typedef UINT32 COLORREF;
typedef DWORD DWORD_PTR;

// Calculate the base address of the structure based on the member address
#define CONTAINING_RECORD(address, type, field) ((type*)((PCHAR)(address) - (ULONG_PTR)(&((type*)0)->field)))
#define MAKELONG(a, b)                          ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define MAKEWPARAM(l, h)                        ((WPARAM)(DWORD)MAKELONG(l, h))
#define MAKELPARAM(l, h)                        ((LPARAM)(DWORD)MAKELONG(l, h))
#define LOWORD(l)                               ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)                               ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)                               ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)                               ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))
#define GetRValue(rgb)                          (LOBYTE(rgb))
#define GetGValue(rgb)                          (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)                          (LOBYTE((rgb) >> 16))
#define RGB(r, g, b)                            ((COLORREF)(((BYTE)(r) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(b)) << 16)))


#if defined(_WIN64) || defined(__APPLE__) || defined(__x86_64) || defined(__aarch64__)
typedef uint64_t ULONG_PTR;
typedef uint64_t UINT_PTR;
typedef int64_t LONG_PTR;
#else
typedef unsigned long ULONG_PTR;
typedef unsigned int UINT_PTR;
typedef long LONG_PTR;
#endif

typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;

typedef struct tagPOINT
{
	LONG x;
	LONG y;
} POINT;

typedef struct tagRECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT, *LPRECT;

typedef struct tagSIZE
{
	LONG cx;
	LONG cy;
} SIZE;

typedef struct tagSCROLLINFO
{
	UINT cbSize;
	UINT fMask;
	int nMin;
	int nMax;
	UINT nPage;
	int nPos;
	int nTrackPos;
} SCROLLINFO, *LPSCROLLINFO;


#endif

#if defined(UNICODE) || defined(_UNICODE)
#define _tchar_length(_pc) mbclen_utf16((const WCHAR*)(_pc))
#define _tcsistr           wcsistr

#ifdef WIN32
#define _L       L
#define __Txt(x) L##x
#define _Txt(x)  __Txt(x)
#define _tcsstr  wcsstr
#else
#define _L       u
#define __Txt(x) u##x
#define _Txt(x)  __Txt(x)
#define _tcsstr  wcsstr_char16
#endif

#else
#define _tchar_length(_pc) mbclen_utf8((const char*)(_pc))
#define _tcsistr           stristr
#define _tcsstr            strstr
#define _L

#define __Txt(x) u8##x
#define _Txt(x)  (const char*)__Txt(x)

#endif



#ifdef WIN32
#define _W(x)               L##x
#define UI_DEFAULT_CODEPAGE CP_ACP
#define vsprintf_w          vswprintf
#define sprintf_w           swprintf
#define wcslen_16           wcslen
#define wcscmp_16           wcscmp
#define wcsncmp_16          wcsncmp
#define wcsicmp_16          wcsicmp
#define wcsnicmp_16         wcsnicmp
#define wcschr_16           wcschr
#define wcsrchr_16          wcsrchr
#define wcsstr_16           wcsstr

#else
#define _W(x)               u##x
#define UI_DEFAULT_CODEPAGE CP_UTF8
#define vsprintf_w          vsnprintf_char16
#define sprintf_w           snprintf_char16
#define wcslen_16           wcslen_char16
#define wcscmp_16           wcscmp_char16
#define wcsncmp_16          wcsncmp_char16
#define wcsicmp_16          wcsicmp_char16
#define wcsnicmp_16         wcsnicmp_char16
#define wcschr_16           wcschr_char16
#define wcsrchr_16          wcsrchr_char16
#define wcsstr_16           wcsstr_char16
#define stricmp             strcasecmp
#define strnicmp            strncasecmp
#define wcsicmp             wcscasecmp
#define wcsnicmp            wcsncasecmp
#define iswascii(c)         (((c) & ~0x7f) == 0)

#if defined(UNICODE) || defined(_UNICODE)
#define _tcslen       wcslen_char16
#define _tcscmp       wcscmp_char16
#define _tcschr       wcschr_char16
#define _tcsrchr      wcsrchr_char16
#define _tcsncmp      wcsncmp_char16
#define _tcsicmp      wcsicmp_char16
#define _tcsnicmp     wcsnicmp_char16
#define _stprintf_s   snprintf_char16
#define _istspace     iswspace
#define _istalpha     iswalpha
#define _istdigit     iswdigit
#define _istascii     iswascii
#define _istprint     iswprint
#define _tcstoll      wcstoll_char16
#define _tcstod       wcstod_char16
#define _stscanf      swscanf
#define _tcsclen(_pc) wcslen((const WCHAR*)(_pc))
#else
#define _tcslen       strlen
#define _tcscmp       strcmp
#define _tcschr       strchr
#define _tcsrchr      strrchr
#define _tcsncmp      strncmp
#define _tcsicmp      strcasecmp
#define _tcsnicmp     strncasecmp
#define _stprintf_s   snprintf
#define _istspace     isspace
#define _istalpha     isalpha
#define _istdigit     isdigit
#define _istascii     isascii
#define _istprint     isprint
#define _tcstoll      strtoll
#define _tcstod       strtod
#define _stscanf      sscanf
#define _tcsclen(_pc) mbslen_utf8((const char*)(_pc))
#endif

typedef char16_t WCHAR;
typedef const WCHAR* LPCWSTR;
typedef const char* LPCSTR;
typedef WCHAR* LPWSTR;
typedef char *PCHAR, *LPCH, *PCH, *LPSTR;
#if defined(UNICODE) || defined(_UNICODE)
typedef WCHAR TCHAR;
#else
typedef char TCHAR;
#endif
typedef const TCHAR* LPCTSTR;

#endif

typedef struct tagRANGE
{
	LONG min;
	LONG max;
} RANGE;

#define WIDTH_RECT(rect)  ((rect).right - (rect).left)
#define HEIGHT_RECT(rect) ((rect).bottom - (rect).top)

#define SQRT2 1.4142135623

#ifndef PI
#define PI 3.1415926535897932384626433832795 /* pi*/
#endif

#ifndef PI_HALF
#define PI_HALF 1.5707963267948966192313216916398 /* pi * 0.5 */
#endif

#ifndef PI_DOUBLE
#define PI_DOUBLE 6.283185307179586476925286766559 /* pi * 2 */
#endif

#ifndef RADIAN_K
#define RADIAN_K 0.01745329251994329576923690768489 /* pi / 180.0 */
#endif


#ifndef MATH_E
#define MATH_E 2.7182818284590452354 /* e */
#endif

#define MATH_SQUARE(a)        ((a) * (a))
#define MATH_CUBE(a)          ((a) * (a) * (a))
#define BITBOOL(value, check) ((value) & (check)) // value & DT_RIGHT

#define ALIGN_BYTE(d, a)  (((d) + (a - 1)) & ~(a - 1))
#define STRIDEBYTE(width) (((width) + 31) & ~31) // scanline 4 byte alignment

#define LODWORD(_qw) ((DWORD)(_qw))
#define HIDWORD(_qw) ((DWORD)(((_qw) >> 32) & 0xffffffff))


#define RECT_TRANSLATE(rc, dx, dy) \
	rc.left += dx; \
	rc.right += dx; \
	rc.top += dy; \
	rc.bottom += dy;

#define COPY_ATTRIBUTE(obj, var) var = (obj)->var;

#define CHECK_NULL_OBJECT() \
	if (this == NULL) return
#define CHECK_NULL_OBJECT_RETURN(r) \
	if (this == NULL) return (r)


typedef void (*OnActionProc)();

/// UtilsCursor 管理光标句柄，避免重复生成对象
enum CursorMouse
{
	CursorArrow       = 0,
	CursorIbeam       = 1,
	CursorWait        = 2,
	CursorCross       = 3,
	CursorUparrow     = 4,
	CursorSize        = 5, /* OBSOLETE: use CursorSizeAll */
	CursorIcon        = 6, /* OBSOLETE: use CursorArrow */
	CursorSizeNWSE    = 7,
	CursorSizeNESW    = 8,
	CursorSizeWE      = 9,
	CursorSizeNS      = 10,
	CursorSizeAll     = 11,
	CursorNo          = 12,
	CursorHand        = 13,
	CursorAppstarting = 14, /* not in win3.1 */
	CursorHelp        = 15,
	CursorHSplit      = 16,
	CursorVSplit      = 17,
};

enum SelectState
{
	StateUnknow     = 0, ///< 未知
	StateSelected   = 1, ///< 勾选
	StateUnselected = 2, ///< 未勾选
};

// 控件展示状态
enum ShowStatus
{
	BeNormal = 0, ///< 常规
	BeHighLight,  ///< 热点
	BeSelected,   ///< 按下
	BeDisable     ///< 禁用
};

#define UIS_COUNT 4


#define CHECK_STATE_UNKNOWN    0 ///< 未知
#define CHECK_STATE_SELECT     1 ///< 勾选
#define CHECK_STATE_UNSELECT   2 ///< 未勾选
#define CHECK_STATE_NO_SOPPORT 3 ///< 无勾选框功能


#define STATE_NORMAL 0x01 ///< 常规
#define STATE_SELECT 0x02 ///< 被选择
#define STATE_HOVEN  0x04 ///< 热点

enum ActionObject
{
	ACTION_ON_MOUSE    = 0x01,
	ACTION_ON_KEYBOARD = 0x02,
	ACTION_ON_DATA     = 0x04
};

enum ActionEvent
{
	ACTION_DOWN = 0,
	ACTION_UP,
	ACTION_CLICK_DOUBLE,
	ACTION_DATA_CHANGE,
	ACTION_MAX_COUNT
};

struct MSGREPKGINFO
{
	UINT msg;
	WPARAM wp;
	LPARAM lp;
};

///  消息ID
enum XMessageType
{
	MSG_BEGIN = (WM_USER + 1100),

	MSG_REPACKAGING,

	/* 鼠标统一消息格式：LOWORD(wp) 鼠标button的类型， HIWORD(wp) 键盘控制键位修饰, lp=坐标(x,y) */
	MSG_MOUSE_BUTTON_DOWN,
	MSG_MOUSE_BUTTON_UP,
	MSG_MOUSE_BUTTON_CLICK,
	MSG_MOUSE_ENTER,
	MSG_MOUSE_MOVE,
	MSG_MOUSE_LEAVE,
	/* 滑轮消息： wp = WParamWheel */
	MSG_MOUSE_WHEEL,
	MSG_MOUSE_CURSOR_POS, // 获取当前光标位置 lp = POINT*

	MSG_NCHITTEST,
	MSG_KEYDWON,
	MSG_KEYUP,
	MSG_KEY_SHORTCUT,
	MSG_CHAR,
	MSG_IMECHAR,
	MSG_IME_PREEDIT_CHAR,
	MSG_IME_COMPOSITION,
	MSG_IME_COMPOSITION_POS,


	MSG_SYSTEM_OPEN_FILE,   ///< 选择文件对话框<table><tr><td>Value 1 </td> <td>Description 1 </td> </tr><tr><td>Value 2 </td> <td>Description 2 </td> </tr></table>
	MSG_SYSTEM_OPEN_FONT,   ///< 选择字体对话框<table><tr><td>Value 1 </td> <td>Description 1 </td> </tr><tr><td>Value 2 </td> <td>Description 2 </td> </tr></table>
	MSG_SYSTEM_OPEN_COLOR,  ///< 选择颜色对话框
	MSG_CLIPBOARD_COPY,     ///< 剪切板复制  wp = LPCTSTR lp=length
	MSG_CLIPBOARD_PASTE,    ///< 剪切板粘贴  lp = BeString*
	MSG_CARETCURSOR_CREATE, ///< wp = 0 creat， 1 destory， lp = height
	MSG_CARETCURSOR_SHOW,   ///< wp = 0 show， 1 hide
	MSG_CARETCURSOR_POS,    ///< lp = point
	MSG_DRAG_ENTER,         ///< drag 消息，  wp =0 lp =0
	MSG_DRAG_OVER,
	MSG_DRAG_LEAVE,
	MSG_DRAG_DROP,
	MSG_THEME_CHANGED, ///< 切换主题，wp= 主题id
	// widget msg
	MSG_WND_SETFOCUS,
	MSG_WND_KILLFOCUS,
	MSG_WND_CURSOR_SET,
	MSG_WND_SIZE,
	MSG_WND_MOVE_XY,
	MSG_WND_MOVE_SIZE,
	MSG_WND_MOVE_DRAG,
	MSG_WND_CLOSE,
	MSG_WND_SHOW,
	MSG_WND_ISZOOMED,       ///< 是否最大化
	MSG_WND_ISVISIBLE,      ///< 是否可见
	MSG_WND_CLIENTRECT_GET, ///< 客户区
	MSG_WND_RECT_GET,       ///< 屏幕区
	MSG_WND_SETCAPTURE,     ///< 捕获
	MSG_WND_RELEASECAPTURE, ///< 捕获释放
	MSG_WND_ACTIVE,         ///< 激活状态
	MSG_WND_IDLE,           ///< 窗口空闲状态
	MSG_WND_SET_BK_COLOR,   ///< 设置背景颜色
	MSG_WND_SET_CAN_MOVE,   ///< 设置窗口可以在客户区拖拽移动
	MSG_WND_NCHITTEST,      ///< 移动窗口
	MSG_WND_HTCAPTION_MOVE, ///< 移动窗口
	MSG_WND_GET_SIZE,       ///< 获得窗口大小 wp = SIZE*
	MSG_WND_ASYNC_PAINT,    ///< 异步刷新消息
	MSG_WND_SET_TITLE,      ///< 设置窗口标题 wp = LPCTSTR
	MSG_WND_SET_STYLE,      ///< 设置窗口风格 wp = UINT
	MSG_GETWORKAREA,        ///< 获得桌面大小
	MSG_TEST_FOCUSNAME,     ///< 测试焦点名称
	MSG_DO_MODAL,           ///< 模态窗口

	MSG_REDRAW_ALL,   ///< 刷新整个窗口
	MSG_REDRAW,       ///< 重绘消息 lp = bSynch TRUE立即刷新
	MSG_REDRAW_ASYNC, ///< 异步重绘消息 lp = rect*
	// manager of event id
	MSG_MANAGER_BIND_UI,           // 绑定ui控件
	MSG_MANAGER_INSTALL_ADAPT,     // 安装适配器
	MSG_MANAGER_DRAW_CONTROLS,     // 管理类绘制出控件入口消息
	MSG_MANAGER_DESTORY,           // 管理类销毁事件
	MSG_MANAGER_APAPTER_DESTORY,   // 适配器销毁事件
	MSG_MANAGER_SETFOCUS,          // 设置焦点控件       wp = ui of pointer
	MSG_MANAGER_SETCAPTURE,        // 设置鼠标焦点控件       wp = ui of pointer
	MSG_MANAGER_CAPTURE_POPUI,     // 将控件加入弹出响应栈，此属性具有高优先级   wp = ui of pointer
	MSG_MANAGER_SETTABKEY,         // Tab键焦点设置
	MSG_MANAGER_CONTROL_SHOW,      // 通知ui隐藏掉了
	MSG_MANAGER_REGISTER_UI,       // 注册或注销ui, wp=0/1， lp = ui of pointer
	MSG_MANAGER_REGISTER_SHORTCUT, // 快捷键注册或注销ui, wp=0/1， lp = ui of pointer
	MSG_MANAGER_REGISTER_KEYTAB,   // TAB焦点注册或注销ui, wp=0/1， lp = ui of pointer
	MSG_MANAGER_TIPBOX,            // Tips信息 lp = show

	MSG_MANAGER_SET_CANVAS_BUFFER, // 设置接收画面缓存数据源和区域 wp = GImage* , lp = RECT*
	MSG_MANAGER_PAINT_BACK,
	MSG_MANAGER_PAINT_SET_BLUR_SIZE, // 设置高斯模糊大小
	MSG_MANAGER_LOAD_CONFIG_SETTING, // 加载配置生效

	MSG_DOCK_HITSTSTE_CHANGED, // dock 命中变换 wp = int

	// 控件交互类消息
	MSG_CONTROL_FONT_CHANGE, // 字体改变
	MSG_CONTROL_KILLFOCUS,
	MSG_CONTROL_SETFOCUS,
	MSG_CONTROL_SHOW,   // 设置可见性 wp = BOOL
	MSG_CONTROL_ENABLE, // 设置可用性 wp = BOOL
	MSG_CONTROL_REGIST, // Manger内部使用消息   注册和注销ui控件在管理类中 lp = pCtrl
	MSG_CONTROL_LOGOFF,
	MSG_CONTROL_DESTORY,
	MSG_CONTROL_SET_TEXT,         // 设置文本
	MSG_CONTROL_SELECT_ALL,       // 选中所有
	MSG_CONTROL_SET_CONTEXT_DATA, // 设置内容数据  lp = LPCTSTR
	MSG_CONTROL_SET_VALUE_COLOR,  // 设置拾取器颜色
	MSG_CONTROL_SIZE,             // 控件位置更新
	MSG_CONTROL_SIZE_ON_CHILD,    // 子控件位置更新
	MSG_CONTROL_SETCURSOR_ID,     // 设置光标
	MSG_CONTROL_ADDTABPAGE,
	MSG_CONTROL_SETTABSEL,
	MSG_CONTROL_SET_DELEGATER,
	MSG_CONTROL_JOIN_CHILD,         // 子控件状态， 1：加入，0：退出
	MSG_CONTROL_JOIN_OPTION,        // 选项动作控件， 1：加入，0：退出
	MSG_CONTROL_IS_POPSTYLE,        // 判断控件是否是模态 wp= BOOL*
	MSG_CONTROL_IS_SELECT,          // 判断控件是否选中 wp= BOOL*
	MSG_CONTROL_IOSYNC,             // io同步，io指的是鼠标键盘设备的输入输出事件
	MSG_CONTROL_ZORDER_SET,         // 设置置顶顺序
	MSG_CONTROL_SYSBUTTON,          // 按钮事件 wp=  this， lp = event type
	MSG_CONTROL_PAINT_PREVIOUS,     // BUI控件绘制前预处理 wp = ISurface*  lp = lprect
	MSG_CONTROL_PAINTBACK,          // BUI控件绘制消息 wp = hdc  lp = lprect
	MSG_CONTROL_REFRESH_RECT,       // 重绘区域消息 wp = rect*
	MSG_CONTROL_CLEAR_CHILDS,       // 由父控件发起，释放所有子控件
	MSG_CONTROL_HSCROLL,            // 当滚动条位置发生变化时，发送变更消息 LPARAM 表示发送消息的BUI控件指针
	MSG_CONTROL_VSCROLL,            // 同上
	MSG_CONTROL_COUNT_STEP,         // 计数控制消息 wp = int
	MSG_CONTROL_ADD_NODEDATA,       // 添加node
	MSG_CONTROL_LANGUAGE_TRANSLATE, // 语言更新，翻译事件


	// cell of event id
	MSG_NODE_ROW_SHOW,    // 单元格容器可见性消息, wp = TRUE/FALSE
	MSG_NODE_CELL_REFESH, // 单元格UI更新 wp = this
	MSG_NODE_ROW_REFESH,  // 行容器UI更新 wp = this

	// 文本消息
	MSG_DATA_CHANGED,   // 数据变化事件 wp = (0, id) lp  = this
	MSG_EDIT_INPUT_END, // 文本输入完成 wp = (0, id) lp  = this

	// editor of event id
	MSG_EDIT_CHAR,          // 编辑框文本输入消息 wp = (0, id) lp  = this
	MSG_TEXT_RETURN,        // 文本编辑按下return时
	MSG_TEXT_ESCAPE,        // 文本编辑按下ESCAPE时
	MSG_EDIT_FINISHED,      // 当在编辑框内输入控制键时候会触发此消息
	MSG_EDIT_CURSOR_TOLOW,  // 光标水平朝低方向
	MSG_EDIT_CURSOR_TOHIGH, // 光标水平朝高方向
	MSG_EDIT_CURSOR_TOUP,   // 光标垂直朝低方向
	MSG_EDIT_CURSOR_TODOWN, // 光标垂直朝高方向
	// datetime of event id
	MSG_DATETIME_CHANGE,

	// tipbox of event id
	MSG_TRACKTIP_TEXT, // 设置跟踪提示文本消息 wp = string lp=(x, y)
	MSG_TRACKTIP_HIDE, // 隐藏跟踪提示文本消息

	// checkbox of event id
	MSG_OPTION_HIDE,      // 复选框不可见
	MSG_OPTION_CHANGED,   // 复选框 wp = this
	MSG_OPTION_SET_STATE, // 设置复选框状态 wp=0/1

	MSG_TABVIEW_SHOW_TEXT_ID, // 标签页显示控制 wp = this lp = text id
	MSG_TABVIEW_HIDE_TEXT_ID,

	// scrollbar of event id

	MSG_SCROLL_H_RANGE_CHANGE, // 滚动控件范围变化 wp = Control* lp = (SBF_HORZ, max)
	MSG_SCROLL_V_RANGE_CHANGE,
	MSG_SCROLL_RELAYOUT,     // 内建滚动条可视状态改变重新布局
	MSG_SCROLL_SYNC,         // 滚动同步消息 wp = SBF_HORZ
	MSG_SCROLL_SET_POS,      // wp = SBF_HORZ
	MSG_MOUSEWHEEL_MAXRANGE, // 滚动到最大值触发
	// tree of event id
	// MSG_TREE_SELECT_CHANGE_STR,   // 树ITEM 被点击时会发送 item的文本

	// combobox of event id
	MSG_COMBOX_HOST_RSP_UI,         // 下拉弹窗绑定宿主UI
	MSG_COMBOX_HOST_DROP_UI,        // 下拉弹窗绑定UI
	MSG_COMBOX_DROP_KILLFOCUS,      // 下拉弹窗 失去焦点
	MSG_COMBOX_DROP_KILLFOCUS_POST, // 异步消息
	MSG_COMBOX_DROP_LBUTTON_POST,   // 异步消息
	MSG_COMBOX_DROPSHOW,            // 下拉框 显示
	MSG_COMBOX_SELECTED,            // 下拉框 选择变更
	MSG_COMBOX_GET_DROP_RECT,       // 下拉框 区域

	// web event id
	MSG_WEB_TAB_TITLE_CHANGE,
	MSG_WEB_TAB_RELEASE,
	MSG_WEB_NEW_POPUP,
	MSG_WEB_NEW_WINDOWS,

	// pop menu of event id
	MSG_POPMENU_CHILD_SHOW,  // 显示位置的消息 wP为1或0 lp预留
	MSG_POPMENU_PARENT_SHOW, // 显示位置的消息 wP为1或0 lp预留
	MSG_POPMENU_GET_HOST,    // 显示位置的消息 wP为 CControl**
	MSG_POPMENU_SET_PARENT,  // 显示位置的消息 wP为 host ui
	MSG_POPMENU_TRACE,       // wp = flags, lp = point
	MSG_POPMENU_SHOW,        // 显示位置的消息 wP为1或0 lp预留
	MSG_POPMENU_POSITON,     // 传入一个点，输出这个点在桌面屏幕的位置 wP预留 lp = POINT*
	MSG_POPMENU_DROPPOP,     // 菜单弹出消息
	MSG_POPMENU_MOVESIZE,    // 设置弹出窗口位置 lp = LPRECT


	// chart event id
	MSG_CHART_AXIS_ZOOM_VALUE_NOTIFY, // 坐标系zoom更新  wp = double lp= 轴序号。这个轴序号代表的是第一坐标轴，第二坐标轴。
	MSG_CHART_AXIS_UPDATE_T,          // 坐标系时间流逝Time更新
	MSG_CHART_COORD_HITTEST,          // 坐标系当前命中， 和MSG_MOUSE_MOVE一样的参数
	MSG_CHART_SET_MARK_STYLE,
	MSG_CHART_SET_MARK_SIZE,
	MSG_CHART_SET_MARK_COLOR,
	MSG_CHART_BAR_DRAW,
	MSG_CHART_BAR_HITTEST,       // bar 鼠标是否命中
	MSG_CHART_BAR_ISVISIBLE,     // bar 是否可见
	MSG_CHART_SERIES_TO_PATH,    // series转换为path wp=name lp = CChartElePath*
	MSG_CHART_ELEMENT_COMMAND,   // 图表元素自定义命令 wp= cmd id lp = user point data
	MSG_CHART_ELEMENT_UPDATE_V1, // 图表元素值v1更新
	MSG_CHART_ELEMENT_UPDATE_V2, // 图表元素值v2更新

	// 布局消息机制协议
	MSG_LAYOUT_SET_DPI,     // 设置布局的缩放比例 wp =缩放值.范围(0, 100]
	MSG_LAYOUT_SHOW,        // 设置布局的可见状态 wp = 1 true, 0 false
	MSG_LAYOUT_REMOVE_ALL,  // 删除所有布局
	MSG_LAYOUT_ADD_ITEM,    // wp = layout 指针, lp = TRUE 代表当容器生命周期结束时，自动释放此子对象
	MSG_LAYOUT_SET_BOXTYPE, // 设置容器类布局的类型 wp = layoutType
	MSG_LAYOUT_SET_OFFSET,  // 设置布局边界偏移量 wp= offset value , lp = 0~3

	DLM_LAYOUT_COMMIT_OFFSET,      // 设置提交偏移量
	MSG_LAYOUT_SET_INTERVAL,       // 设置布局之间的间隔 wp = 间隔大小
	MSG_LAYOUT_SET_CROSS_OFFSET,   // 设置布局之间的间隔 wp = 大小
	MSG_LAYOUT_SET_REVERSE,        // 设置布局反序 wp = BOOL
	MSG_LAYOUT_SET_KEEPLASTINVIEW, // 设置布局保持在可见视窗 wp = BOOL
	MSG_LAYOUT_SET_CURSEL,         // 当前布局项
	MSG_LAYOUT_SET_PARENT,         // 设置父布局
	MSG_LAYOUT_SET_NAME,           // 设置布局名称
	MSG_LAYOUT_SEARCH_NAME,        // 查找布局 wp = ILayout**  lp=LPCTSTR
	MSG_LAYOUT_RESET,              // 重置布局
	MSG_LAYOUT_SET_BOX_TYPE,       // 设置盒子布局类型 wp = LayoutType
	// 动画消息
	MSG_ANIMATION,
	MSG_ANIMATE_REQ_BACK,
	MSG_ANIMATE_REQ_FRONT,
	MSG_ANIMATE_FRAME, // 动画输出
	MSG_SYSTEM_QUIT,   // 垃圾响应推出消息
	MSG_USER           // 用户消息定义位置，UI内部使用了1000个消息号，避免消息冲突
};

#define UI_LOGOFF 0
#define UI_LOGIN  1

enum CmdEventType
{
	NORMAL,       ///< 普通
	MINSIZE,      ///< 最小化
	MAXSIZE,      ///< 最大化
	FULLSIZE,     ///< 全屏
	REMOVE,       ///< 删除
	CLOSE,        ///< 关闭并销毁窗口
	CLOSE_CUSTOM, ///< 用户关闭行为
	HIDE,         ///< 隐藏但不销毁窗口
	HIDE_PARENT,  ///< 隐藏父容器
	SUBMIT,       ///< 提交
	CANCEL,       ///< 取消
};

//**********************************************************************
// 位获取掩码
//**********************************************************************
#define MASK_BIT_0 0x01
#define MASK_BIT_1 0x02
#define MASK_BIT_2 0x04
#define MASK_BIT_3 0x08

#define MASK_BIT_4 0x10
#define MASK_BIT_5 0x20
#define MASK_BIT_6 0x40
#define MASK_BIT_7 0x80


//**********************************************************************
// 动画模板类型
//**********************************************************************

#define AM_TOLEFT  0x01 // 左向左运动
#define AM_TORIGHT 0x02 // 向右运动
#define AM_TODOWN  0x04 // 向下运动
#define AM_TOUP    0x08 // 向上运动
#define AM_BLEND   0x10 // 模糊
#define AM_HIDE    0x20 // 隐藏


#define HOR_SHOW 0x01
#define HOR_HIDE 0x02
#define VER_SHOW 0x04
#define VER_HIDE 0x08


#define DAM_SHOW (HOR_SHOW | VER_SHOW)
#define DAM_HIDE (HOR_HIDE | VER_HIDE)

// 方向，从左向右，从上到下为正方向
enum DirectionTrend
{
	FORWARD  = 0x01, // 正方向
	NEGATIVE = 0x02  // 负方向
};

enum AlignmentStyle
{
	Left,
	Center,
	Right,
	Top,
	Bottom
};

enum LayoutBoxType
{
	HORIZONTAL, ///< 水平分布(x轴方向)
	VERTICAL,   ///< 垂直分布(y轴方向)
	LAYERED     ///< 层叠分布(z轴方向)
};

/// SizeType尺寸类型，布局中的占位计算方法
enum SizeMode
{
	AdaptSelf,  ///< 元素自适应
	AdaptFill,  ///< 剩余填充自适应
	FixedValue, ///< 固定值
	Percentage  ///< 百分比
};

struct SizeValue
{
	SizeMode type;
	int size;

	SizeValue()
	    : type(Percentage)
	    , size(0)
	{}
};

enum LayoutType
{
	NULL_LAYTYPE = 0, // 未知类型
	LAY_HBOX,         // layout盒子
	LAY_VBOX,
	LAY_LAYERED, // 分层布局
	CTL,         // BUI控件
	NODE_DATA,   // node data
	Widget,      // widget控件
	Spacer       // 间隔器
};

enum ShowModel
{
	OnNever     = 0,    ///< 从不绘制
	OnAlways    = 0x01, ///< 一直绘制
	OnFocus     = 0x02, ///< 焦点时绘制
	OnHighLight = 0x04, ///< 高亮时绘制
};

enum PaintOption
{
	BackBufferSurface = 1 << 0, ///< 创建一块与窗口大小一致的渲染表面，可提高绘图稳定性和速度。不开启时，每次以刷新区域到小创建表面，并在绘制结束时销毁
};

//**********************************************************************
// 布局和对齐方式
//**********************************************************************
#define LAYOUT_TOP    0x01 // 顶部
#define LAYOUT_BOTTOM 0x02 // 底部
#define LAYOUT_LEFT   0x04 // 左边
#define LAYOUT_RIGHT  0x08 // 右边
#define LAYOUT_CENTER 0x10 // 中部
// 控件分布的方式
#define LAYOUT_HORIZONTAL 0x01 // 水平布局
#define LAYOUT_VERTICAL   0x02 // 垂直布局

#define ALIGNMENT_LEFT   0x01 // 左对齐
#define ALIGNMENT_RIGHT  0x02 // 右对齐
#define ALIGNMENT_TOP    0x04 // 顶部对齐
#define ALIGNMENT_BOTTOM 0x08 // 底部对齐
#define ALIGNMENT_CENTER 0x10 // 居中

#define LAYOUT_H_LEFT   0x01 // 左
#define LAYOUT_H_CENTER 0x02 // 中
#define LAYOUT_H_RIGHT  0x04 // 右
#define LAYOUT_H_FIXED  0x08 // 固定

#define LAYOUT_V_TOP    0x10 // 顶
#define LAYOUT_V_CENTER 0x20 // 中
#define LAYOUT_V_BOTTOM 0x40 // 底
#define LAYOUT_V_FIXED  0x80 // 固定（由用户指定位置）

#define DIRECTION_AUTO      0x00 // 自适应
#define DIRECTION_RIGHTWARD 0x01 // 向右的
#define DIRECTION_LEFTWARD  0x02 // 向右
#define DIRECTION_UP        0x04 // 向上
#define DIRECTION_DOWN      0x08 // 向下

#define ALIGN_TOP     0x00000001
#define ALIGN_LEFT    0x00000002
#define ALIGN_CENTER  0x00000004
#define ALIGN_RIGHT   0x00000008
#define ALIGN_VCENTER 0x00000010
#define ALIGN_BOTTOM  0x00000020
#define ALIGN_BORDER  0x00000040

enum PenType
{
	PenTypeSoild,
	PenTypeDash,       // -------
	PenTypeDot,        // .......
	PenTypeDashDot,    // _._._._
	PenTypeDashDotDot, // _.._.._
};

enum WindowStyles
{
	WIDGET_FRAME_MAIN = 1UL << 1, // main frame
	WIDGET_FRAME_POP  = 1UL << 2, // pop frame
	WIDGET_TOOL       = 1UL << 3, // pop frame
	WIDGET_RESIZABLE  = 1UL << 4, // variable size
	WIDGET_VISIBLE    = 1UL << 5, // visible
	WIDGET_DISABLED   = 1UL << 6, // disable
	WIDGET_TOPMOST    = 1UL << 7, // top most
	WIDGET_TRANS      = 1UL << 8, // transparent
};

#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
	ClassName(const ClassName&); \
	void operator=(const ClassName&);

enum KeyCtrlCode
{
	CodeOpen  = 1 << 0,
	CodeWin   = 1 << 1,
	CodeCtrl  = 1 << 2,
	CodeAlt   = 1 << 3,
	CodeShift = 1 << 4,
};

enum TickMarkID
{
	TickMinor = 1 << 0,
	TickMajor = 1 << 1,
};

enum TickMarkPositon
{
	TickNone      = 0,
	TickOnInside  = 1 << 0, ///< 向里
	TickOnOutside = 1 << 1, ///< 向外
	TickOnCross   = 1 << 2  ///< 交叉
};

/// 实色状态外观
struct COLORSTYLE
{
	COLORREF crNormal;   ///< 常规显示颜色
	COLORREF crHigh;     ///< 高光热点显示颜色
	COLORREF crSelected; ///< 选中热点显示颜色
	COLORREF crDisable;  ///< 禁用颜色
};

#define INIT_COLORSTYLE(c, n, h, d) \
	c.crNormal   = n; \
	c.crHigh     = h; \
	c.crSelected = h; \
	c.crDisable  = d;

#define INIT_COLORSTYLE_DEFAULT(c, n, h) \
	c.crNormal   = n; \
	c.crHigh     = h; \
	c.crSelected = h; \
	c.crDisable  = 0xC9C7C6;

#define INIT_COLORSTYLE_FULL(c, n, h, s, d) \
	c.crNormal   = n; \
	c.crHigh     = h; \
	c.crSelected = s; \
	c.crDisable  = d;

struct TipsBoxInfo
{
	LONG x;
	LONG y;
	const TCHAR* tips;
};

struct TRIANGLE
{
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
};

/// 自定义半径的圆角尺寸
struct RoundRectRadius
{
	short rx1;
	short ry1;
	short rx2;
	short ry2;
	short rx3;
	short ry3;
	short rx4;
	short ry4;

	RoundRectRadius()
	{
		rx1 = rx2 = rx3 = rx4 = 0;
		ry1 = ry2 = ry3 = ry4 = 0;
	}

	RoundRectRadius(int rx, int ry)
	{
		rx1 = rx2 = rx3 = rx4 = rx;
		ry1 = ry2 = ry3 = ry4 = ry;
	}

	RoundRectRadius(int rx1_, int ry1_, int rx2_, int ry2_, int rx3_, int ry3_, int rx4_, int ry4_)
	{
		rx1 = rx1_;
		rx2 = rx2_;
		rx3 = rx3_;
		rx4 = rx4_;

		ry1 = ry1_;
		ry2 = ry2_;
		ry3 = ry3_;
		ry4 = ry4_;
	}

	BOOL IsZero() { return !rx1 && !rx2 && !rx3 && !rx4 && !ry1 && !ry2 && !ry3 && !ry4; }
};

struct PopControlInfo
{
	float x;
	float y;
	POINT offset; // point offset
	UINT align;   // DT_TOP DT_LEFT
	UINT style;   // 弹出风格，包括焦点方式状
};

/// 数据文本格式
enum DataTextFormat
{
	Format_Auto, ///< 根据文件后缀名自动识别
	Format_JSON, ///< json格式
	Format_XML,  ///< xml格式
};

/// 像素格式
enum XPixelFormat
{
	PixelFormat_rgb = 0,
	PixelFormat_bgr,
	PixelFormat_rgba,
	PixelFormat_bgra,
	PixelFormat_abgr,
	PixelFormat_argb
};

/// 画面缓存结构信息
struct XImageInfo
{
	UBYTE* pixels;            ///< 画面内存位置
	int bpp;                  ///< 画面像素比特位数量
	LONG width;               ///< 能够清晰显示所需宽度(视网膜屏幕下，同一个物理单位包含的像素点更多。而图片的度量单位是像素)
	LONG height;              ///< 能够清晰显示所需高度
	int stride;               ///< 画面一行扫描宽度
	LONG pixelwidth;          ///< 像素宽度
	LONG pixelheight;         ///< 像素高度
	XPixelFormat pixelformat; ///< 像素格式

	XImageInfo()
	    : pixels(NULL)
	    , width(0)
	    , height(0)
	    , stride(0)
	    , bpp(0)
	    , pixelwidth(0)
	    , pixelheight(0)
	    , pixelformat(PixelFormat_rgb)
	{}
};

enum FilterType
{
	Filter_None,
	Filter_Gray,
};

/// 图元混合方式
enum BlendCompType
{
	comp_none,        ///< C = A*(1-a) + B*a;透明度混合
	comp_plus,        ///< C = A + B;发光物体叠加()
	comp_multiply,    ///< C = A * B;不发光物体叠加
	comp_plus_weight, ///< C = A + B;权重叠加
};

#define ADD_FLAGS    0 ///< 添加属性
#define REMOVE_FLAGS 1 ///< 删除属性

enum PathConvType
{
	CONV_NONE,      // 无转换
	CONV_BSPLINE,   // 样条转换
	CONV_CURVE_INC, // 曲线inc转换,内存友好型
	CONV_CURVE_DIV  // 曲线div转换
};

/// 外观场景类别
enum ColorSceneType
{
	ColorOfBackground, ///< 背景
	ColorOfForeground, ///< 前景
	ColorOfText,       ///< 文本
	ColorOfBorder,     ///< 边框
};

enum MouseState
{
	MS_NO_IN,
	MS_HOVER,
	MS_LB_DOWN,
	MS_LB_UP
};

enum SGFontStyle
{
	FS_NORMAL        = 0,      ///< normal
	FS_BOLD          = 1,      ///< bold
	FS_ITALIC        = 1 << 1, ///< italic
	FS_UNDERLINE     = 1 << 2, ///< under line
	FS_STRIKETHROUGH = 1 << 3, ///< delete line
};

/// 值大于0代表向外扩展， 小于0代表向内扩展
struct MarginInfo
{
	short left;
	short right;
	short top;
	short bottom;

	MarginInfo() { left = right = top = bottom = 0; }
};

struct PaddingInfo
{
	short left;
	short right;
	short top;
	short bottom;

	PaddingInfo() { left = right = top = bottom = 0; }
};

/// Location Info
struct Location
{
	int X;
	int Y;
	int Width;
	int Height;
};

/// mouse wheel event Info
struct WParamWheel
{
	UINT fwkwys;
	BOOL isPixelDelta;
	int xDelta;
	int yDelta;
};

/// key event Info
struct WParamKeyboard
{
	UINT keyModifier; /* alt , mak, ctl, win */
	UINT key;
};

/// InputMethod event Info
struct WParamInputMethod
{
	UINT keyModifier; /* alt , shift, ctl, win */
	LPCTSTR text;
};

/// ui paint back event Info
struct LParamControlBack
{
	XImageInfo* imgbuf;
	RECT* rcupdate;
};

// mouse event Info
enum MouseButton
{
	ButtonNone  = 0,
	ButtonLeft  = 1 << 1,
	ButtonMid   = 1 << 2,
	ButtonRight = 1 << 3,
};

enum MouseKeyModifier
{
	Modifier_No      = 0x00000000,
	Modifier_Shift   = 1 << 1,
	Modifier_Control = 1 << 2,
	Modifier_Alt     = 1 << 3,
	Modifier_Meta    = 1 << 4,
};

typedef LRESULT (*LPMsgFun)(WPARAM wp, LPARAM lp);

template <typename TDst, typename TSrc> TDst UnionCastType(TSrc src)
{
	union
	{
		TDst uDst;
		TSrc uSrc;
	} uMedia;

	uMedia.uSrc = src;
	return uMedia.uDst;
}

#define MEMBER_FUNADDR(pAddr) UnionCastType<DWORD>(pAddr)

struct ItemState
{
	bool isEnable   : 1; ///< 可用性(true:可用)
	bool isVisable  : 1; ///< 可见性(true可见)
	bool isHover    : 1; ///< 高亮属性(true:高亮)
	bool isSelected : 1; ///< 选中状态(true:被选中)

	bool isPainted     : 1; ///< 保留
	bool isLBDown      : 1; ///< 保留
	bool isEditable    : 1; ///< 可编辑，可改变
	bool isUseColormap : 1; ///< 使用颜色映射
};

struct ColorPicker
{
	float h;
	RECT rc;
};

/// 画布类的消息事件结构
struct SurEvent
{
	UINT nID;
	WPARAM inParam;
	WPARAM retParam;
};

#define PM_SET_CLIPBOX_HDC 0x0000A001
#define PM_SET_CLIPBOX     0x0000A002
#define PM_GET_CLIPBOX     0x0000A003
#define PM_RELEASE_CLIPBOX 0x0000A004

#define PM_COLOR_PICKER 0x0000A005
#define PM_GRAY         0x0000A007

struct VIEW_BOX
{
	LONG x, y, w, h;
};

/// ui msg info
struct EVENTINFO
{
	UINT message; ///< msg type
	WPARAM wParam;
	LPARAM lParam;
	UINT nID;       ///< sender id
	LPCTSTR szName; ///< sender name
};

// data buffer
struct DataBuffer
{
	BYTE* data;
	int size;

	DataBuffer()
	    : data(NULL)
	    , size(0)
	{}
};

/// value model
struct NumericalValue
{
	double v;
	UINT mode; // 百分比模式

	NumericalValue()
	    : v(0)
	    , mode(0)
	{}
};

typedef void* (*Constructor)(); ///< 指向函数的指针,这个函数返回一个CObject

/* RuntimeInfo */
struct UI_EXP RuntimeInfo
{
	TCHAR* m_lpszClassName;    ///< 存放类名
	RuntimeInfo* m_pNextClass; ///< 类型的指针
	Constructor constructor_;

	static RuntimeInfo* pFirstClass; ///< 静态变量，链表头部
	static void* CreateObject(const TCHAR* classname);
};

struct UI_EXP UI_CLASS_INIT
{
	UI_CLASS_INIT(RuntimeInfo* pNewClass);
};

#define RUNTIME_XCLASS(class_name) class_name::GetRunTimeInfo##class_name()


#define _CONCAT_TXT(H, x) H## #x
#define CONCAT_TXT(H, x)  _CONCAT_TXT(H, x)

/// HEAD文件中声明在类中
#define DECLARE_DYNAMIC_OBJ_CLASS_BASE(class_name) \
  public: \
	static RuntimeInfo helper##class_name; \
	static RuntimeInfo* GetRunTimeInfo##class_name() { return &helper##class_name; } \
	virtual const TCHAR* GetObjectClassName() { return CONCAT_TXT(_L, class_name); } \
\
  protected: \
	virtual void* CreateObjectThis() { return (void*)(new class_name()); }

#define DECLARE_DYNAMIC_OBJ_CLASS(class_name) \
  public: \
	static RuntimeInfo helper##class_name; \
	static RuntimeInfo* GetRunTimeInfo##class_name() { return &helper##class_name; } \
	const TCHAR* GetObjectClassName() override { return CONCAT_TXT(_L, class_name); } \
\
  protected: \
	void* CreateObjectThis() override { return (void*)(new class_name()); }

/// CXX 文件中 类实现的前面
#define IMPLEMENT_DYNAMIC_OBJ_CLASS(class_name) \
	static void* Create##class_name() { return (void*)(new class_name()); } \
	extern UI_CLASS_INIT _init_##class_name; \
	TCHAR _lpsz##class_name[]                  = CONCAT_TXT(_L, class_name); \
	RuntimeInfo class_name::helper##class_name = {_lpsz##class_name, NULL, Create##class_name}; \
	UI_CLASS_INIT _init_##class_name(&class_name::helper##class_name);


/// 获得高清屏的缩放比，此值和系统DPI无关。只用于分辨高清屏
extern "C" UI_EXP double get_pixel_buf_scale_value();

/// 设置屏幕缩放系数
extern "C" UI_EXP void set_pixel_buf_scale_value(double scale);
/// 角度转换为弧度
extern "C" UI_EXP double to_radians(double degrees);

/// 获得系统DPI缩放比例
extern "C" UI_EXP double get_system_point_dpi_scale();


#if defined(_DEBUG)
#define DEBUG_ASSERT(var)             (assert(var))
#define DEBUG_ASSERT_RETURN(var, ret) (assert(var))
#else
#define DEBUG_ASSERT(var) \
	if (!(var)) return;
#define DEBUG_ASSERT_RETURN(var, ret) \
	if (!(var)) return ret;
#endif



#endif
