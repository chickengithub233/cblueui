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

#ifndef CBLUEUI_INC_H_
#define CBLUEUI_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// 核心基础类
#include "core/CCoreBasePro.h"
#include "core/CCoreCharFunction.h"
#include "core/CCoreObject.h"
#include "core/CCoreEventHandler.h"
#include "core/CManagerHandler.h"
#include "core/SignalSlotX.hpp"
#include "core/NotifyActionTemplate.hpp"
#include "core/LinkList.hpp"
#include "core/LinkTree.hpp"
#include "core/SafeQueue.hpp"
#include "core/CThreadPool.h"
#include "core/ShareMemPtr.hpp"
#include "core/MathMatrix.h"
#include "core/SafeVector.hpp"
// 字符处理类
#include "cstring/StringShort.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "cstring/StringConvertUtils.h"


#ifdef CBLUEUI_USE_MINIZIP
#include "function/FileReaderZip.h"
#endif
#include "function/FileReader.h"
#include "function/MarkupItem.h"
#include "function/XmlStorageA.h"
#include "function/XmlStorage.h"
#include "function/Loggerdebug.h"
#include "function/LoggerStorage.h"
#include "function/DateInfo.h"
#include "function/SettingInfo.h"
#include "function/CSkinInfo.h"
#include "function/LexicalParser.h"

// 包含窗口封装和UIManager消息管理者实现
#include "platform/WindowPlatformInc.h"
#include "platform/UIManager.h"
#include "platform/CPopupMenuEx.h"
#include "platform/CResourceFont.h"
#include "platform/CGlobalResources.h"
#include "platform/GFont.h"
#include "platform/FileSystem.h"
#include "platform/PopWindowBox.h"
#include "platform/WindowCursor.h"
#include "platform/WindowDockingManager.h"


// 图形接口类
#include "graphics/GSurface.h"
#include "graphics/GImage.h"
#include "graphics/GImageIconInfo.h"
#include "graphics/CResourceGraphics.h"
#include "graphics/GExtentText.h"
#include "graphics/GBrushGradient.h"
#include "graphics/GPathStorage.h"
#include "graphics/GStyleLine.h"
#include "graphics/GStyleMarkShape.h"
#include "graphics/easing.h"
#include "graphics/GAnimation.h"

// 布局类
#include "layout/CLayoutManager.h"

// 常用的基础ui类
#include "uicontrol/CControlUI.h"
#include "uicontrol/CButtonUI.h"
#include "uicontrol/CDateTimeUI.h"
#include "uicontrol/CDigitLcdUI.h"
#include "uicontrol/CCheckBoxUI.h"
#include "uicontrol/CColorPickerUI.h"
#include "uicontrol/CComboListUI.h"
#include "uicontrol/CEditKeyBoardUI.h"
#include "uicontrol/CEditLine.h"
#include "uicontrol/CEditTextUI.h"
#include "uicontrol/CEditTextRichUI.h"
#include "uicontrol/CEditSpinBoxUI.h"
#include "uicontrol/CImageViewUI.h"
#include "uicontrol/CLabelUI.h"
#include "uicontrol/CLabelMultiStyleUI.h"
#include "uicontrol/CListBoxUI.h"
#include "uicontrol/CPaginationUI.h"
#include "uicontrol/CProgressBarUI.h"
#include "uicontrol/CPopControlUI.h"
#include "uicontrol/CScrollBarUI.h"
#include "uicontrol/CTableViewUI.h"
#include "uicontrol/CMatrixUI.h"
#include "uicontrol/CNodeDataTable.h"
#include "uicontrol/CNodeDataChart.h"
#include "uicontrol/CCarouselUI.h"
#include "uicontrol/NetGraphUI.h"
#include "uicontrol/CTreeTableViewUI.h"
#include "uicontrol/CTreeListUI.h"
#include "uicontrol/CBaseSelectState.h"
#include "uicontrol/CContainTabUI.h"
#include "uicontrol/CContainerUI.h"
#include "uicontrol/CContainOptionUI.h"
#include "uicontrol/CContainScrollSyncUI.h"
#include "uicontrol/CContainLayoutUI.h"
#include "uicontrol/CContainTitleUI.h"
#include "uicontrol/CSplitBarUI.h"
#include "uicontrol/CContainOptionUI.h"

#ifdef CBLUEUI_USE_LIB_ZXING
#include "uicontrolex/CZBarCodeUI.h"
#endif

#ifdef CBLUEUI_USE_LIB_OPENCV
#include "uicontrolex/CCameraVideoUI.h"
#endif

#ifdef CBLUEUI_USE_LIB_QT
#include "uicontrolex/CCameraVideoQtUI.h"
#endif


#ifdef CBLUEUI_USE_LIB_GRAPHICS_GL
#include "uicontrolex/CView3dUI.h"
#endif

#include "uigraphviz/CNodeEditorUI.h"

// 新增图表UI，增强可视化效果
#ifndef DISABLE_UI_CHART
#include "uichart/CChartAxis.h"
#include "uichart/CChartCoordinate.h"
#include "uichart/CChartCoordinate3d.h"
#include "uichart/CChartCoordinateGeo.h"
#include "uichart/CChartElementImage.h"
#include "uichart/CChartElement.h"
#include "uichart/CChartElementText.h"
#include "uichart/CChartSeriesLine.h"
#include "uichart/CChartSeriesScatter.h"
#include "uichart/CChartSeriesBar.h"
#include "uichart/CChartSeriesTree.h"
#include "uichart/CChartSeriesPie.h"
#include "uichart/CChartSeriesGraph.h"
#include "uichart/CChartElementCandles.h"
#include "uichart/CChartElementBoxPlot.h"
#include "uichart/CChartElementPath.h"
#include "uichart/CChartElementMeter.h"
#include "uichart/CChartElementHeatmap.h"
#include "uichart/CChartElementLegendBox.h"
#include "uichart/CChartElementAttitudeIndicator.h"
#include "uichart/CChartViewUI.h"
#endif


#include "uimsgbox/CToastBox.h"

#ifdef CBLUEUI_USE_LIB_CEF
#include "uiweb/browser/cef_main_handler.h"
#include "uiweb/CWebUI.h"
#endif

// 设计器接口
#include "xmldesigner/XmlBuilder.h"

// 第三方脚本接口
#include "plugins/CScriptPlugin.h"

using namespace BUI;


#endif
