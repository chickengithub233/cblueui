#ifndef CBLUEUI_WINDOWDOCKINGMANAGER_BLXDY_INC_H_
#define CBLUEUI_WINDOWDOCKINGMANAGER_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <string>

#include "core/CCoreBasePro.h"
#include "graphics/GImage.h"
#include "WindowPlatformInc.h"

namespace BUI {

class UI_EXP WindowDockingManager : public IDockHandler
{
  public:
	WindowDockingManager();
	~WindowDockingManager();

	void SetWindowScreenPoint(int x, int y); // 设置窗口左上角屏幕坐标
	void SetScreenRectMain(RECT& rc);        // 设置窗口区域屏幕坐标
	void SetScreenRectContain(RECT& rc);     // 设置容器区域屏幕坐标
	void SetScreenRectSourceView(RECT rc);
	void Show(BOOL show); // 展示dock

	GImage* GetBufferImage();
	/* IEventHandler override methods:*/
	BOOL OnMessageHandler(UINT message, WPARAM wp, LPARAM lp) override;

  private:
	void OnHitSideChanged(int type);

  private:
	RECT m_rcMain;    // 主窗口
	RECT m_rcContain; // 当前容器位置
	SIZE m_dock_size;
	RECT m_rcHit[9];
	int m_hit_side;
	POINT m_ptOrigin;

	CWidgetOverlayWnd m_preview;         // 位置预览
	CWidgetOverlayWnd m_dockview;        // 被拖拽出来的视图
	CWidgetOverlaySideWnd m_sideview[5]; // 占位导航

	GImage m_img;
};

// 安装Docking管理对象
extern "C" UI_EXP void InstallWindowDockingManager(WindowDockingManager* fontMgr);

// 获得Docking管理对象
extern "C" UI_EXP WindowDockingManager* GetWindowDockingManager();
};



#endif
