#ifndef CBLUEUI_CCONTROLGC_BLXDY_INC_H_
#define CBLUEUI_CCONTROLGC_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <atomic>
#include "core/CCoreBasePro.h"
#include "core/CCoreObject.h"
#include "uicontrol/CControlUI.h"

namespace BUI {

class CControlUI;
class CManagerSkin;
class CSkinStyle;

/**
 * @brief 控件垃圾回收机制,生命周期检测。自行释放已经游离的对象
 *
 */
class UI_EXP CControlGC
{
  public:
	CControlGC();
	virtual ~CControlGC();

	void SystemQuit();

	/*control*/
	void RegisterGCObj(CControlUI*);
	void RemoveGCObj(CControlUI* pObj);

	/// 更新所有控件皮肤.常用于应用程序整体换肤
	void ApplyAllControlSkinFile(CManagerSkin& skin);

	/// 更新主题颜色
	void ApplyAllControlTheme(int theme);

	/// 触发翻译事件
	void LanguageTranslate();
	CControlUI* FindControl(const char* name);
	CControlUI* FindManageOfControl(IManageHandler* pMagr, LPCTSTR ctrlName);
	CControlUI* FindControlByID(IManageHandler* pMagr, UINT nID);

	int FindManageOfAllControl(IManageHandler* pMagr, LPCTSTR ctrlName, std::vector<CControlUI*>& vec);

  private:
	std::atomic<CControlUI*> m_pTailChain;
};

extern "C" {

/// 安装控件垃圾处理对象
UI_EXP void InstallGCManager(CControlGC* gc);
/// 获得控件垃圾处理对象
UI_EXP CControlGC* GCManager();

/// 将皮肤信息应用到控件中
UI_EXP void UpdateSkin(CManagerSkin& skinMgr, CControlUI* ui);

/**
 * @brief  更新指定控件皮肤。常用于数据展示类型的定制化
 *
 * @param  ui 控件对象
 * @param  recursive_child  TRUE:递归子控件
 */
UI_EXP void UpdateSkinByStyleName(CSkinStyle& skin, CControlUI* ui, BOOL recursive_child = FALSE);
}


}
#endif
