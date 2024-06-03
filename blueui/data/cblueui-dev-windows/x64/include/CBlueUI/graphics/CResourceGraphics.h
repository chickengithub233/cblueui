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

#ifndef CBLUEUI_CRESOURCEGRAPHICS_BLXDY_INC_H_
#define CBLUEUI_CRESOURCEGRAPHICS_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "core/CCoreChartDefs.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "function/MarkupItem.h"


#include <map>
#include <memory>

namespace BUI {

class GImage;
class GImageGIF;
class GPathStorageSVG;
class GradientColors;
class GBrushGradient;
class GImageIconInfo;
#ifdef CBLUEUI_USE_MINIZIP
class FileReaderZip;
#endif


/**
 * @brief 图形相关资源存储类
 *
 */
class UI_EXP CResourceGraphics
{
  public:
	CResourceGraphics();
	~CResourceGraphics();

  private:
	std::map<BeString, std::map<BeString, COLORREF>> m_mapColors;
	std::map<BeString, GImage*> m_mapSGimg;
	std::map<BeString, GImageGIF*> m_mapSGimgGif;
	std::map<BeString, GPathStorageSVG*> m_mapSvg;

	std::map<BeString, GradientColors*> m_mapGradientColors;
	std::map<BeString, GBrushGradient*> m_mapGradientBrush;

	std::map<BeString, GImageIconInfo*> m_mapImageStatus; // 图标组合状态
#ifdef CBLUEUI_USE_MINIZIP
	std::map<BeString, FileReaderZip*> m_mapZip;
#endif

	std::map<BeString, std::shared_ptr<CandlesStyle>> m_mapCandlesStyle; // K线图样式
	std::map<BeString, std::shared_ptr<BoxPlotStyle>> m_mapBoxPlotStyle; // 盒子图样式

	BeString m_current_res_dir; ///< 当前资源文件所在


	std::map<BeString, std::vector<BeStringPair>> m_mapShareStyle; // 共享风格文件
  public:
	/**
	 * @brief 添加GImage资源
	 *
	 */
	GImage* LoadSGImageFromBuffer(const BeString& keyid, unsigned char* buffer, UINT dwSize);
	GImage* GetSGImage(const BeString& keyid);

	/**
	 * @brief 添加GImageGIF
	 *
	 */
	GImageGIF* LoadSGImageGIFFromBuffer(const BeString& keyid, unsigned char* buffer, UINT dwSize);
	GImageGIF* GetSGImageGIF(const BeString& keyid);

	/**
	 * @brief 添加GPathStorageSVG资源
	 *
	 */
	GPathStorageSVG* LoadSVGFromBuffer(const BeString& keyid, const char* buffer, UINT dwSize);
	GPathStorageSVG* GetSVGImage(const BeString& keyid);

	/**
	 * @brief 添加Colors资源
	 *
	 */
	void AddColors(const BeString& keyid, std::map<BeString, COLORREF>& colors);
	void GetColors(const BeString& keyid, COLORSTYLE& outColors);

	/**
	 * @brief 添加Gradient Colors资源
	 *
	 */
	void AddGradientColors(const BeString& keyid, GradientColors* gra_colors);
	GradientColors* GetGradientColors(const BeString& keyid);

	/**
	 * @brief 添加Gradient brush资源
	 *
	 */
	void AddGradientBrush(const BeString& keyid, GBrushGradient* linear);
	GBrushGradient* GetGradientBrush(const BeString& keyid);


	/**
	 * @brief 添加Gradient brush资源
	 *
	 */
	void AddSGImageIconInfo(const BeString& keyid, GImageIconInfo* icon);
	GImageIconInfo* GetSGImageIconInfo(const BeString& keyid);


	/**
	 * @brief zip resource
	 *
	 */
	DataBuffer GetZipArchiveFileData(const char* zipfile, const char* archiveName);

	/**
	 * @brief 添加蜡烛图风格资源
	 *
	 */
	void AddCandlesStyle(const BeString& keyid, std::shared_ptr<CandlesStyle> style);
	std::shared_ptr<CandlesStyle> GetCandlesStyle(const BeString& keyid);

	/**
	 * @brief 添加盒子图风格资源
	 *
	 */
	void AddBoxPlotStyle(const BeString& keyid, std::shared_ptr<BoxPlotStyle> style);
	std::shared_ptr<BoxPlotStyle> GetBoxPlotStyle(const BeString& keyid);

	/**
	 * @brief 获得当前资源解析的执行目录
	 *
	 */
	LPCTSTR ResourceCurrentDir();

	void SetResourceCurrentDir(LPCTSTR dir);

	/**
	 * @brief 添加风格样式文件资源
	 *
	 */
	void AddStyleSheet(const BeString& keyid, const std::vector<BeStringPair>& styleList);
	BOOL GetStyleSheet(const BeString& keyid, std::vector<BeStringPair>& outStyleList);
};

/**
 * @brief 安装资源管理对象
 *
 */
UI_EXP void InstallResourceGraphics(CResourceGraphics* res);


/**
 * @brief 获得资源管理对象
 *
 */
UI_EXP CResourceGraphics* ResourceGraphics();

}

#endif