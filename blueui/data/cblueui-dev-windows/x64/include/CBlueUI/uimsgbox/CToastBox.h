#ifndef HANDLER_CTOASTBOX_INC_H_
#define HANDLER_CTOASTBOX_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreObject.h"
#include "uicontrol/CContainLayoutUI.h"
#include "uicontrol/CLabelUI.h"
#include "uicontrol/CImageViewUI.h"

namespace BUI {

class UI_EXP CToastBox
{
  public:
	CToastBox();
	~CToastBox();

	/**
	 * @brief 获得顶层UI控件对象。可用于开发者的定制控件风格。如颜色，字体大小。
	 *        如需更高程序的定制化。可自行封装UI模板
	 */
	CContainLayoutUI* GetContainLayoutUI();
	CImageViewUI* GetImageUI();
	CLabelUI* GetLabelUI();

	/**
	 * @brief 弹出自动延时隐藏消息框
	 *
	 * @param IManageHandler  消息弹出的目标位置。为NULL时，表示在上次的位置弹出
	 * @param text_type 图标id
	 * @param msg  消息内容
	 * @param hide_delay 超过指定时长(毫秒)后自动隐藏
	 * @param anim_time 图标动画频率
	 * @param anim_angle 图标动画 旋转角度
	 */
	void PopupText(IManageHandler* pM, LPCTSTR text_type, LPCTSTR msg, int hide_delay = 1000, BOOL update = FALSE, int anim_time = 0, int anim_angle = 45);
	void PopupTextA(IManageHandler* pM, LPCSTR text_type, LPCSTR msg, int hide_delay = 1000, BOOL update = FALSE, int anim_time = 0, int anim_angle = 45);
	void PopupTextW(IManageHandler* pM, LPCWSTR text_type, LPCWSTR msg, int hide_delay = 1000, BOOL update = FALSE, int anim_time = 0, int anim_angle = 45);

  private:
	void InitUI(IManageHandler* pM);

  private:
	CContainLayoutUI* m_ui_notice_msg_box;
	CImageViewUI* m_ui_notice_msg_image;
	CLabelUI* m_ui_msgtext; // xxxxxx
};




}




#endif
