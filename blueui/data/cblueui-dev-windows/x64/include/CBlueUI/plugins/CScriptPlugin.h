#ifndef CBLUEUI_CSCRIPTPLUGIN_BLXDY_INC_H_
#define CBLUEUI_CSCRIPTPLUGIN_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "core/CCoreBasePro.h"

#ifndef _WIN32
#include <dlfcn.h>
#endif

namespace BUI {

/**
 * @brief 插件功能函数提取类
 *
 */
#ifdef _WIN32
class UI_EXP DynamicLibrary
{
  public:
	explicit DynamicLibrary(const char* filename);
	~DynamicLibrary();
	void* get(const char* symbol) const;

  private:
	HMODULE lib_;
};
#else
class UI_EXP DynamicLibrary
{
  public:
	explicit DynamicLibrary(const char* filename, int flag = RTLD_NOW);
	~DynamicLibrary();
	void* get(const char* symbol) const;

  private:
	void* lib_;
};
#endif

}




#endif