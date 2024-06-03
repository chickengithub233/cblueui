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
#ifndef CBLUEUI_XML_PARSE_DESIGNER_H__
#define CBLUEUI_XML_PARSE_DESIGNER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <assert.h>
#include <string>
#include <vector>
#include <map>

#include "core/CCoreBasePro.h"
#include "core/CCoreObject.h"
#include "core/CCoreEventHandler.h"
#include "function/XmlStorageA.h"
#include "function/XmlStorage.h"

namespace BUI {

class CControlUI;

struct ParseSetting
{
	IManageHandler* pManger;
	CControlUI* pParent;
	ILayout* pLayoutBox;
	IEventHandler* handler;
};

struct LayoutSize
{
	int layWidth;
	int layHeight;
	SizeMode wType;
	SizeMode hType;
};

typedef CControlUI* (*CreateControl_cb)(const TCHAR* typeName, const TCHAR* desClassName, const TCHAR* className);

/**
 * @brief UI构建工具类
 *
 */
class UI_EXP XmlBuilder
{
	typedef void (XmlBuilder::*ParseNodeProc_cb)(XMLItem* pNode, ParseSetting* param);

  public:
	XmlBuilder();
	virtual ~XmlBuilder();

	// 加载全局资源文件，资源文件格式有xml格式和json格式
	static BOOL ApplyResourceWithFile(const char* filepath, DataTextFormat fmt = DataTextFormat::Format_Auto);
	static BOOL ApplyResourceWithFile(const WCHAR* uixml, DataTextFormat fmt = DataTextFormat::Format_Auto);
	static BOOL ApplyResourceWithData(const char* data, DataTextFormat fmt = DataTextFormat::Format_Auto);
	// 加载自定义主题色
	static BOOL ApplyThemeColors(XMLItem* pNode);

	// 加载自定义12等级字体
	static BOOL ApplyDefaultFonts(XMLItem* pNode);

	/* 加载ui到指定控件内*/
	static int LoadControlUIFile(const char* file, CControlUI* pCtrl, IEventHandler* handler = NULL);
	static int LoadControlUIFile(const WCHAR* file, CControlUI* pCtrl, IEventHandler* handler = NULL);
	static int LoadControlUIString(const char* xmlcontent, CControlUI* pCtrl, IEventHandler* handler = NULL, BOOL no_write = TRUE);

	void SetDesignParse(BOOL bDesignParse);

	/* interface api*/
	int LoadUIFileA(LPCSTR filepath, IManageHandler* pManger, CControlUI* pParent = NULL, ILayout* pLayBox = NULL, IEventHandler* handler = NULL);

	int LoadUIFileW(LPCWSTR filepath, IManageHandler* pManger, CControlUI* pParent = NULL, ILayout* pLayBox = NULL, IEventHandler* handler = NULL);

	void LoadBuffer(const char* xmlText, IManageHandler* pManger, CControlUI* pParent = NULL, ILayout* pLayBox = NULL, IEventHandler* handler = NULL, BOOL no_write = TRUE);
#ifdef _WIN32
	void LoadUIResource(UINT nID, LPCTSTR szType, HINSTANCE hMode, IManageHandler* pManger, CControlUI* pParent = NULL, ILayout* pLayBox = NULL, IEventHandler* handler = NULL);
#endif
	void LoadUITempCache(XmlStorage* templat, IManageHandler* pManger, CControlUI* pParent = NULL, ILayout* pLayBox = NULL, IEventHandler* handler = NULL);

	int ParseUiFileUNICODE(const WCHAR* wfilename, IManageHandler* pManger, CControlUI* pParent, ILayout* pParBox, IEventHandler* handler);

	int ParseUiFile(const char* filename, IManageHandler* pManger, CControlUI* pParent, ILayout* pParBox, IEventHandler* handler);

	void ParseNode(XMLItem* pNode, ParseSetting* param);

	void ParsePopManager(XMLItem* pXmlNode, ParseSetting* param);
	void ParsePopControl(XMLItem* pXmlNode, ParseSetting* param);
	void ParseDesignWindow(XMLItem* pNode, ParseSetting* param);

	CControlUI* ParseControl(XMLItem* pNode, ParseSetting* param, CreateControl_cb lpCreateControl = NULL);

	ILayout* ParseAdsorbLayout(XMLItem* pNode, ParseSetting* param);

	void ParseNodedata(XMLItem* pNode, ParseSetting* param, CreateControl_cb lpCreateControl = NULL);

	void ParseControlFont(XMLItem* pNode, ParseSetting* param);

	// 重复控件的自定义属性节点，格式为 <attribute class="title" text="xxxx"/>
	void ParseControlAttribute(XMLItem* pNode, CControlUI* parent);

	void ParseImage(XMLItem* pNode, ParseSetting* param);

	void ParseDesignLayout(XMLItem* pNode, ParseSetting* param);

	void ParseLayout(XMLItem* pNode, ParseSetting* param);

	void ParseZipResurce(XMLItem* pNode, ParseSetting* param);

	void ParseSharedNode(XMLItem* pNode);

	void PreLoadClassStyle(XMLItem* root);

	XMLItem* GetStyleNode(const TCHAR* name);


	void SetInitFlags(BOOL send_init_msg);

  public:
	virtual void OnParseWindow(const TCHAR* desClassName, const TCHAR* className);
	virtual void OnParseControl(CControlUI* pObjCtl, const TCHAR* desClassName, const TCHAR* className, const TCHAR* objName);
	virtual CControlUI* OnParseDesLayout(IManageHandler* pM, CControlUI* parent, const TCHAR* layoutname, LayoutSize* infodata, ILayout** outBoxLayout);

  private:
	BeString m_skinModule;
	BeString m_prefix_path; // 路径前缀
	ParseNodeProc_cb m_ParseWindows_cbfun;
	ParseNodeProc_cb m_ParseLayoyt_cbfun;
	CreateControl_cb m_CreateControl_cbfun;
	std::map<std::tstring, XMLItem*> m_StroageStyle; // 共享风格缓存
	int m_szie_cx;
	int m_szie_cy;
	SizeMode m_nWidMode;
	SizeMode m_nHeiMode;
	BOOL m_isNeedInit;
};




}

#endif