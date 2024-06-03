#ifndef CBLUEUI_LOGER_UNTILS_BLXDY_INC_H_
#define CBLUEUI_LOGER_UNTILS_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"

UI_EXP void PrintfToOutputA(const char* str);
UI_EXP void PrintfToOutputW(const WCHAR* str);

namespace BUI {

/**
 * @brief 打印到调试输出窗口
 *
 */
class UI_EXP DebugLoger
{
  public:
	DebugLoger();
	DebugLoger(const char* file, int line, const char* funcname, bool is_short_name = true);
	~DebugLoger();

	void printA(const char* pszFormat, ...);
	void printW(const WCHAR* pszFormat, ...);

  protected:
	int m_line;
	const char* m_file;
	const char* m_function;
	const char* m_category;
};

}


#if defined(_DEBUG)
#define DTRACE_FORMATE_A(formate, ...) BUI::DebugLoger(__FILE__, __LINE__, __FUNCTION__).printA(formate, __VA_ARGS__)
#define DTRACE_A(msg)                  BUI::DebugLoger(__FILE__, __LINE__, __FUNCTION__).printA("%s", msg)

#define DTRACE_FORMATE_W(formate, ...) BUI::DebugLoger(__FILE__, __LINE__, __FUNCTION__).printW(formate, __VA_ARGS__)
#define DTRACE_W(msg)                  BUI::DebugLoger(__FILE__, __LINE__, __FUNCTION__).printW(_W("%s"), msg)
#else
#define DTRACE_FORMATE_A(formate, ...) BUI::DebugLoger(__FILE__, __LINE__, __FUNCTION__).printA(formate, __VA_ARGS__)
#define DTRACE_A(msg)                  void(0)

#define DTRACE_FORMATE_W(formate, ...) void(0)
#define DTRACE_W(msg)                  void(0)
#endif

#ifdef _UNICODE
#define DTRACE_FORMATE DTRACE_FORMATE_W
#define DTRACE         DTRACE_W
#else
#define DTRACE_FORMATE DTRACE_FORMATE_A
#define DTRACE         DTRACE_A
#endif

#define PRINT_CLASS(name) DTRACE_FORMATE("%s = %d", #name, sizeof(name))

#endif
