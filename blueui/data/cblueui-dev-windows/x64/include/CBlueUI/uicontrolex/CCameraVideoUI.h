/**********************************************************************************
CBlueUI library.
Copyright (C) 2015  CBlueUI Studio<2842004379@qq.com>

Declaration
All rights reserved.
China

This software is released under the "CBlueUI License" (hereinafter referred to as the "License").
You may only use and distribute this software in accordance with the terms and conditions of the License.
Please make sure that you have read, understood, and accepted all the provisions of the License before using this software.
If you do not agree with any provisions of the License, you are not authorized to use this software.

This software is provided "as is" without any warranty, expressed or implied.
The author and copyright owner expressly disclaim any warranties, including but not limited to the implied warranties
of merchantability, fitness for a particular purpose, and non-infringement. In no event shall the author or copyright owner
be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to,
procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and
on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in
any way out of the use of this software, even if advised of the possibility of such damage.

For further details about the License, please refer to the license document.

声明：
保留所有权利
中国
本软件是根据CBlueUI许可证（下称“协议”）发布的，您只能在符合协议规定的条件下使用和分发本软件。
请确保在使用本软件之前，您已阅读、理解并接受协议的所有条款和条件。如果您不同意协议的任何规定，您将无权使用本软件。

本软件在不作任何明示或暗示的情况下，以“原样”提供。作者和版权所有者明确声明不提供任何形式的明示或暗示保证，包括但不限于
对该软件的适用性、适销性或特定用途的适用性的暗示保证。在任何情况下，作者和版权所有者对于使用本软件所导致的任何直接、间接、
附带的或特殊的损失或责任不承担任何责任。

如需详细了解协议的内容，请参考协议文档。

**********************************************************************************/

#ifdef CBLUEUI_USE_LIB_OPENCV

#ifndef CBLUEUI_CCAMERAVIDEOUI_BLXDY_INC_H_
#define CBLUEUI_CCAMERAVIDEOUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uicontrol/CControlUI.h"
#include "uicontrol/CScrollBarUI.h"

namespace BUI {


/**
 * @brief 视频画面控件
 *
 */
class UI_EXP CCameraVideoUI : public CScrollAreaUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CCameraVideoUI)
  public:
	CCameraVideoUI();
	~CCameraVideoUI();

	void SetVideoName(const BeString& name);
	void SetVideoIndex(int index);

	void ReConnect(); // 重连视频设备
	void GetCurFrameData(XImageInfo& img);

	int LayoutAdaptWidth(int expH) override;
	int LayoutAdaptHeight(int expW) override;
	void OnCreate() override;
	void OnControlSize() override;
	void OnCtrlKillFocus() override;

	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;
	void ChangeThemeColors(int theme) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  private:
	GImage m_target_img;
	CTimerTask m_vedio_timer;
	int m_video_index;
	BeString m_video_address;
	SIZE m_video_size;
	void* m_videoCapture;
	void* m_bufFrame;
};


}
#endif

#endif
