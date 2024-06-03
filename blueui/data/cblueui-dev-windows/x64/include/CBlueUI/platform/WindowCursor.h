#ifndef CBLUEUI_RESMANAGERCURSOR_BLXDY_INC_H_
#define CBLUEUI_RESMANAGERCURSOR_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <string>

#include "core/CCoreBasePro.h"


#if (defined _WIN32) && !(defined CBLUEUI_USE_LIB_QT)

namespace UtilsCursor {
UI_EXP CursorMouse SetMouseCursor(CursorMouse cursor);
}

class UI_EXP CWaitingCursor
{
  public:
	CWaitingCursor();
	~CWaitingCursor();

  protected:
	CursorMouse m_hOrigCursor;
};

/**
 * @brief ini配置文件操作类
 *
 */
namespace UtilsRWIniFile {

UI_EXP int GetIntValue(const LPCTSTR file, const LPCTSTR section, const LPCTSTR key);

UI_EXP void GetStringValue(const LPCTSTR file, const LPCTSTR section, const LPCTSTR key, LPTSTR buffer, int bufsize);

UI_EXP int SetIntValue(const LPCTSTR file, const LPCTSTR section, const LPCTSTR key, int nValue);

UI_EXP void SetStringValue(const LPCTSTR file, const LPCTSTR section, const LPCTSTR key, const LPCTSTR value);

};


#endif





#endif
