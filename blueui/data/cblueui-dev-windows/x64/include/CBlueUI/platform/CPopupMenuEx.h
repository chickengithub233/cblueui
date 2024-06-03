/****************************************************************************
 *在SDK下的弹出式菜单, 接口和MFC下的函数名一致。各位MFC程序设计人员，可以快速上手使用
 *不依赖任何库,任意平台
 *Autor: MD
     MF_CHECKED：命令旁显示默认复选标志
     MF_UNCHECKED：清除命令旁的复选标志
     MF_DISABLED：禁止此菜单命令，但是不变灰显示
     MF_ENABLED：允许此菜单命令，恢复到正常状态
     MF_GRAYED：禁止此菜单命令，变灰显示
     MF_MENUBARBREAK：对于静态菜单，放到新行；对于弹出菜单，放到新栏 中，栏间有分隔线
     MF_MENUBREAK：对于静态菜单，放到新行；对于弹出菜单，放到新栏，栏间无分隔线
     MF_OWNERDRAW：指定该命令是自画式菜单命令
     MF_POPUP：指定该菜单命令有一个关联的弹出式菜单
     MF_SEPARATOR：画一条水平分隔线，只用于弹出式菜单
     MF_STRING：指定此菜单命令是一个字符串

     TPM_LEFTALIGN:若设置此标志, 函数使快捷菜单的左边界与由参数X指定的坐标对齐。
     TPM_RIGHTALIGN:若设置此标志, 函数使快捷菜单的右边界与由参数X指定的坐标对齐。
 ****************************************************************************/

#ifndef CBLUEUI_CPOPMENUEX_BLXDY_INC_H_
#define CBLUEUI_CPOPMENUEX_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <assert.h>
#include <string>
#include <vector>

#include "platform/WindowPlatformInc.h"
#include "platform/UIManager.h"
#include "uicontrol/CContainMenuUI.h"

namespace BUI {

class UI_EXP UIPopupMenuManager : public UIManager
{
  public:
	UIPopupMenuManager();
	~UIPopupMenuManager();

	virtual BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam);

  public:
	POINT m_point;
	UINT m_nAlignFlag;
	CContainMenuUI m_popContain;
	BOOL m_isFocusing;
	int m_nid = 0;
};

class UI_EXP CPopupMenuEx
{
  public:
	WindowPlatform m_windows;
	UIPopupMenuManager m_ManagerUI;
	BOOL m_bCreatSuccess;

  public:
	CPopupMenuEx(void);
	~CPopupMenuEx(void);

	BOOL CreatePopupMenu();

	/**
	 * @brief 返回UI管理对象
	 * @return UIManager*
	 */
	UIManager* ManagerUI();

	/**
	 * @brief 获得放置菜单的容器UI
	 * @return CContainLayoutUI*
	 */
	CContainMenuUI* GetPopMenuContainUI();

	UINT_PTR GetMenuID() const;

	/**
	 * @brief 加载xml ui文件
	 *
	 * @param file ui文件的路径
	 */
	void LoadMenuUI(const char* file);

	/**
	 * @brief 弹出菜单
	 *
	 * @param nFlags TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON | TPM_BOTTOMALIGN
	 * @param x    菜单显示的x位置
	 * @param y    菜单显示的y位置
	 * @return BOOL
	 */
	BOOL TrackDropPop(UINT nFlags, int x, int y);
};


}
#endif