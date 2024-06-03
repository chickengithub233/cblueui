
#ifndef CBLUEUI_CMAINEVENTHANDLER_PRO_BLXDY_INC_H_
#define CBLUEUI_CMAINEVENTHANDLER_PRO_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCoreBasePro.h"
#include "CCoreEventHandler.h"
#include "CCoreObject.h"

namespace BUI {

/**
 * @brief 事件过滤器(可安装到控件上，截获需要处理的消息)
 *
 */
class UI_EXP CManagerHandler : public IEventHandler
{
  public:
	CManagerHandler(IManageHandler* pM);
	virtual ~CManagerHandler();

	void BindUI();

	void SetUIManager(IManageHandler* pM);

	IManageHandler* GetUIManager();

	virtual BOOL OnMessageHandler(UINT message, WPARAM wp, LPARAM lp);

  protected:
	IManageHandler* m_manager;
};

}

#endif