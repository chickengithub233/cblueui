#ifndef CBLUEUI_POPWINDOWBOX_BLXDY_INC_H_
#define CBLUEUI_POPWINDOWBOX_BLXDY_INC_H_

#pragma once

#include "platform/WindowPlatformInc.h"
#include "platform/UIManager.h"

namespace BUI {

struct PopManagerData
{
	BeString shortid;
	BeString fullid;
	UIManager* manager;
};

class UI_EXP PopWindowManager
{

  public:
	PopWindowManager();
	~PopWindowManager();

	void PopFrameShow(UIManager* manager, RECT* rcView, LPCTSTR title, UINT style = 0 /*| WIDGET_FRAME_POP*/ /*| WIDGET_TOPMOST*/);

	void PopDropShow(UIManager* manager, int x, int y, UINT align, LPCTSTR title, UINT style = 0 /*| WIDGET_FRAME_POP*/ /*| WIDGET_TOPMOST*/);
	UIManager* GetPopManager(BeString id);
	BOOL Add(PopManagerData& item);

  protected:
	WindowPlatform* GetWindowPlatform(void* ptr, LPCTSTR title, UINT style);

  public:
	std::vector<PopManagerData> m_pop_uis;
	std::map<void*, WindowPlatform*> m_mapwins;
};

/// 安装弹窗管理对象
extern "C" UI_EXP void InstallPopWindowManager(PopWindowManager* popwin);

/// 获得弹窗管理对象
extern "C" UI_EXP PopWindowManager* GetPopWindowManager();


}



#endif