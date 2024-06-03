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

	void SetWindowScreenPoint(int x, int y); // ���ô������Ͻ���Ļ����
	void SetScreenRectMain(RECT& rc);        // ���ô���������Ļ����
	void SetScreenRectContain(RECT& rc);     // ��������������Ļ����
	void SetScreenRectSourceView(RECT rc);
	void Show(BOOL show); // չʾdock

	GImage* GetBufferImage();
	/* IEventHandler override methods:*/
	BOOL OnMessageHandler(UINT message, WPARAM wp, LPARAM lp) override;

  private:
	void OnHitSideChanged(int type);

  private:
	RECT m_rcMain;    // ������
	RECT m_rcContain; // ��ǰ����λ��
	SIZE m_dock_size;
	RECT m_rcHit[9];
	int m_hit_side;
	POINT m_ptOrigin;

	CWidgetOverlayWnd m_preview;         // λ��Ԥ��
	CWidgetOverlayWnd m_dockview;        // ����ק��������ͼ
	CWidgetOverlaySideWnd m_sideview[5]; // ռλ����

	GImage m_img;
};

// ��װDocking�������
extern "C" UI_EXP void InstallWindowDockingManager(WindowDockingManager* fontMgr);

// ���Docking�������
extern "C" UI_EXP WindowDockingManager* GetWindowDockingManager();
};



#endif
