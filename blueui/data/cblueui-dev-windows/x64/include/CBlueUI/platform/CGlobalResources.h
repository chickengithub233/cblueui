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
#ifndef CBLUEUI_CGLOBALRESOURCES_BLXDY_INC_H_
#define CBLUEUI_CGLOBALRESOURCES_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <atomic>
#include "core/CCoreBasePro.h"
#include "core/CCoreObject.h"
#include "core/CTimerWheel.h"
#include "function/CSkinInfo.h"
#include "function/SettingInfo.h"
#include "uicontrol/CControlUI.h"
#include "uimsgbox/CToastBox.h"
#include "graphics/CResourceGraphics.h"
#include "CControlGC.h"
#include "PopWindowBox.h"
#include "CResourceFont.h"
#include "WindowDockingManager.h"

namespace BUI {


/// 全局初始化对象，此对象的生命周期需要与执行程序相同
struct UI_EXP UISystemStartUp
{
	UISystemStartUp();
	~UISystemStartUp();

	POINT ptTrace;
	CLanguageTranslator langTranslator; ///< 语言翻译
	CSettingInfo setting_info;          ///< 智能记忆配置信息(json格式)。比如控件的历史输入记录，控件关闭时的状态
	CControlGC controlGC;               ///< UI控件回收机制，无需手动释放控件
	WindowDockingManager dockmgr;       ///< docking system
	PopWindowManager windowManager;     ///< 弹窗管理
	CTimerWheel timerMgr;               ///< 定时器
	CResourceFont resFont;              ///< 字体资源管理
	CResourceGraphics resGraphics;      ///< 图形色彩公共资源管理
	int m_cur_theme;                    ///< 当前主题索引，-1表示加载用户自定义主题
	BeString m_current_app_dir;         ///< app运行目录
	int m_gray_con_type;                ///< 全局灰度处理类型。小于0表示不做全局灰度处理
	CToastBox* m_toastBox;
};

/**
 * @brief 初始化UI系统，并启动服务
 *
 */
extern "C" UI_EXP int InitializeUISystem(UISystemStartUp* gc); // 初始化UI系统，并启动服务

/**
 * @brief 设置鼠标的跟踪的起点位置，该位置用来计算当前位置，与跟踪位置的距离
 *
 * @param pt 需要标记的位置
 */
extern "C" UI_EXP void SetMouseTracePoint(POINT pt);

/**
 * @brief 获得跟踪标记的位置
 *
 */
extern "C" UI_EXP POINT GetMouseTracePoint();


/**
 * @brief 获得当前应用的主题
 *
 */
extern "C" UI_EXP int ThemeNo();


/**
 * @brief 切换主题配色
 *
 * @param theme_index 主题编号（当主题序号和输入参数相同时，不会触发更新操作。可通过设置force参数为TRUE强制更新）
 * @param force 强制更新
 */
extern "C" UI_EXP void ChangeThemeNo(int theme_index, BOOL force = FALSE);


/**
 * @brief 获得当前应用的执行目录
 *
 */
extern "C" UI_EXP LPCTSTR AppCurrentDir();

/**
 * @brief 安装全局信息弹出控件
 *
 */
extern "C" UI_EXP void InstallToastBox(CToastBox* toastbox);

/**
 * @brief 获得消息提示框
 *
 */
extern "C" UI_EXP CToastBox* ToastBox();

/**
 * @brief 开启全局灰度模式
 *
 * @param gray_type 灰度算法
 *                   0: 针对人眼进行校正 Gray = (Red * 0.299 + Green * 0.587 + Blue * 0.114)
 *                   1: 平均加权方式，快速但效果不是最佳 Gray = (Red  + Green  + Blue )/3
 *                   2: 去饱和度 Gray = ( Max(Red, Green, Blue) + Min(Red, Green, Blue) ) / 2
 *                   3: 最大值分解 Gray = Max(Red, Green, Blue)
 *                   4: 最小值分解 Gray = Min(Red, Green, Blue)
 *                   5: 单色分解 Gray = Red
 *                   6: 单色分解 Gray = Green
 *                   7: 单色分解 Gray = Blue
 */
extern "C" UI_EXP void EnableGlobalGrayscaleMode(int gray_type);


extern "C" UI_EXP int GetGlobalGrayscaleMode();

}
#endif
