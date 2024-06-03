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
#ifndef CBLUEUI_LAYOUT_BLXDY_INC_H_
#define CBLUEUI_LAYOUT_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include <vector>

#include "core/CCoreBasePro.h"
#include "core/CCoreObject.h"
#include "cstring/StringA.h"
#include "cstring/String.h"

namespace BUI {

class CLayoutBase;

struct LayoutLinkNode
{
	BOOL isNeedFree;
	CLayoutBase* this_layout;
	struct LayoutLinkNode* prev;
	struct LayoutLinkNode* next;
};

/**
 * @brief 布局信息基类
 *
 */
class UI_EXP CLayoutBase : public ILayout
{
  public:
	CLayoutBase();
	virtual ~CLayoutBase();

	AlignmentStyle HorAlign();
	AlignmentStyle VerAlign();

	SizeMode WidthType();
	SizeMode HeightType();

	/**
	 * @brief 根据屏幕DPI，设置缩放因子。100表示不缩放
	 * @return int
	 */
	void SetScaleFactor(int scale);

	/**
	 * @brief 获得布局容器的宽度
	 * @return int
	 */
	virtual int Width();
	/**
	 * @brief: 获得布局容器的高度
	 */
	virtual int Height();

	virtual void GetPosition(RECT& rc);

	/// 查找布局
	ILayout* FindLayoutByName(LPCTSTR name) override;

	int GetAdaptWidth(int expH) override;
	int GetAdaptHeight(int expW) override;

	int GetSplitOffsetW() override; ///< 获得拆分宽度偏移
	int GetSplitOffsetH() override; ///< 获得拆分高度偏移

	/**
	 * @brief 设置布局信息
	 *
	 * @param w 布局占位宽度
	 * @param h 布局占位高度
	 * @param tw 布局占位方式 AdaptFill=自适应 ，FixedValue = 像素指定值w(或h)，Percentage = 百分比
	 * @param th
	 */
	void SetLayoutInfo(int w, int h, SizeMode tw, SizeMode th) override;

	void GetLayoutInfo(int& w, int& h, SizeMode& tw, SizeMode& th) override;
	/**
	 * @brief 设置布局容器内的对象水平和垂直的对齐风格
	 *
	 * @param hor  居中，左对齐，右对齐
	 * @param ver
	 */
	void SetAlignment(AlignmentStyle hor, AlignmentStyle ver) override;

	/**
	 * @brief 设置内边距
	 *
	 * @param l 左
	 * @param r 右
	 * @param t 上
	 * @param b 下
	 */
	void SetPadding(int l, int r, int t, int b) override;

	bool IsVaild() override;
	bool IsVisibleLayout() override;

	/**
	 * @brief 执行布局操作
	 */
	void Layout(int x, int y, int w, int h, UINT flags = 0) override;

	/**
	 * @brief 布局对象消息处理函数
	 */
	BOOL OnLayoutMessageProc(UINT message, WPARAM wParam, LPARAM lParam) override;

	ILayout* GetParentLayout() override;

	bool IsHasAdaptLayout() override;

	void RebuildLayout(bool isForceUpdate) override;

	LayoutType GetLayoutType() override;

  private:
	virtual BOOL ResetLayout();

  public:
	LayoutType m_LayoutType; // 布局类型
	BeString m_strName;      // 布局名称ID

	int m_nScaleFactor; // DPI缩放因子
	int m_nCacheOffsetSize;

	int m_nWidth;
	int m_nHeight;
	SizeMode m_nWidMode;
	SizeMode m_nHeiMode;

	AlignmentStyle m_horAlign;
	AlignmentStyle m_verAlign;

	CLayoutBase* m_pParentLayout;
	LayoutLinkNode m_link;

	PaddingInfo m_padding;

	SIZE m_szAdapt;
};

/**
 * @brief 弹性占位布局对象
 */
class UI_EXP CLayoutSpacer : public CLayoutBase
{
  public:
	CLayoutSpacer();
	~CLayoutSpacer();

	void SetManageHandler(IManageHandler* handler);

	bool IsVisibleLayout() override;

  protected:
	IManageHandler* m_manger; // 是否自动根据窗口最大化最小化显示
};

/**
 * @brief UI控件布局对象
 */
class UI_EXP CLayoutControl : public CLayoutBase
{
  public:
	IControlUI* m_pIControl;
	SIZE m_adaptSize;

  public:
	CLayoutControl(IControlUI* pObj);
	virtual ~CLayoutControl();

	ILayout* FindLayoutByName(LPCTSTR name) override;
	int Width() override;
	int Height() override;
	int GetAdaptWidth(int expH) override;
	int GetAdaptHeight(int expW) override;

	int GetSplitOffsetW() override; ///< 获得拆分宽度偏移
	int GetSplitOffsetH() override; ///< 获得拆分高度偏移

	void GetPosition(RECT& rc) override;
	bool IsVisibleLayout() override;
	bool IsVaild() override;
	void Layout(int x, int y, int w, int h, UINT flags = 0) override;
	BOOL OnLayoutMessageProc(UINT message, WPARAM wParam, LPARAM lParam) override;
};

/**
 * @brief UI控件布局对象
 */
class UI_EXP CLayoutNodeData : public CLayoutBase
{
  public:
	INodeData* m_pNodedata;
	SIZE m_adaptSize;
	RECT m_rcNode;

  public:
	CLayoutNodeData(INodeData* pObj);
	virtual ~CLayoutNodeData();

	ILayout* FindLayoutByName(LPCTSTR name) override;
	int Width() override;
	int Height() override;
	int GetAdaptWidth(int expH) override;
	int GetAdaptHeight(int expW) override;

	int GetSplitOffsetW() override; ///< 获得拆分宽度偏移
	int GetSplitOffsetH() override; ///< 获得拆分高度偏移

	void GetPosition(RECT& rc) override;
	bool IsVisibleLayout() override;
	bool IsVaild() override;
	void Layout(int x, int y, int w, int h, UINT flags = 0) override;
	BOOL OnLayoutMessageProc(UINT message, WPARAM wParam, LPARAM lParam) override;
};

/**
 * @brief UI控件吸附布局对象
 */
class UI_EXP CLayoutControlAdsorb : public CLayoutControl
{
  public:
	int m_base_x;
	int m_base_y;
	int m_base_dx;
	int m_base_dy;
	SizeMode m_mode_base_x;
	SizeMode m_mode_base_y;

  public:
	CLayoutControlAdsorb(IControlUI* pObj);
	virtual ~CLayoutControlAdsorb();
	void SetBaseMode(int x, int y, SizeMode tw, SizeMode th);
	void SetBaseOffset(int dx, int dy);

	void Layout(int x, int y, int w, int h, UINT flags = 0) override;
};

/**
 * @brief 盒子布局容器类.
 *        水平盒子: 水平计算布局对象
 *        垂直盒子: 垂直计算布局对象
 *        层叠盒子: Z方向计算方式，所有对象共享区域
 */
class UI_EXP CLayoutBox : public CLayoutBase
{
  public:
	LayoutLinkNode m_head;
	BOOL m_bReverse;          // 反序排列
	int m_nInterval;          // 控件之间的间隔
	int m_nOverlapOffset;     // 重叠区域位置偏移量(第二控件开始生效)
	BOOL m_bEnableAutoScroll; // 自动滚动
	int m_nAutoScrollOffset;  // 自动滚动的偏移量
	RECT m_rcBox;
	BOOL m_bKeepInView; // 保持最后一个布局对象在视窗下可见

  public:
	CLayoutBox(LayoutBoxType boxType = VERTICAL);
	virtual ~CLayoutBox();

	int GetZCurSel() const;          // 获得层叠当前显示索引
	void SetLayoutCurSel(int index); // 设置层叠当前显示索引

	int GetCounts(BOOL only_visable = TRUE) const;
	SIZE GetAdaptSize();                                      // 获得布局对象适应大小
	void EnableAutoScroll(BOOL isEnable);                     // 自动滚动
	void AddAutoScrollOffset(int step);                       // 增加偏移量
	void GetAllLayout(std::vector<CLayoutBase*> lists) const; // 获得子布局列表，调试用
	void EnableKeepLastInView(BOOL keep);                     ///< 保持最后一个布局对象在视窗下可见,当且仅当有2个布局时生效
	int Width() override;
	int Height() override;
	bool IsVisibleLayout() override;

	void SetScaleFactor(int scale);

	void RemoveAllLayout();
	int GetDistance(); // 获得行程距离

	void Layout(int x, int y, int w, int h, UINT flags = 0) override;

	void SetLayoutType(LayoutBoxType boxType = HORIZONTAL);

	void SetLayoutReverse(BOOL bReverse); // 反方向排列
	void SetCrossOffset(int d);           // 设置交叉偏移量
	BOOL LayoutReverse() const;

	int GetAdaptWidth(int expH) override;
	int GetAdaptHeight(int expW) override;
	bool IsHasAdaptLayout() override;
	void GetPosition(RECT& rc) override;
	BOOL OnLayoutMessageProc(UINT message, WPARAM wParam, LPARAM lParam) override;

	/* CLayoutBase methods:*/
	BOOL ResetLayout() override;
	/// 查找布局
	ILayout* FindLayoutByName(LPCTSTR name) override;

	/// 添加的布局对象需要由用户自己释放。传入指针，不负责指针的销毁
	BOOL AddLayout(CLayoutBase* pObj, BOOL bManualFree = FALSE);

	CLayoutBox* AddVerLayout(int w, int h, SizeMode stw, SizeMode sth);
	CLayoutBox* AddHorLayout(int w, int h, SizeMode stw, SizeMode sth);
	CLayoutBox* AddLayeredLayout(int w, int h, SizeMode stw, SizeMode sth);
	CLayoutSpacer* AddSpacer(int w, int h, SizeMode stw, SizeMode sth);
	CLayoutControl* AddLayoutCtrl(IControlUI* pObj, int w, int h, SizeMode stw, SizeMode sth);

	/// 测试点命中布局间隔的信息
	CLayoutBase* HitTestSplit(POINT pt) const;

	void ShellLayoutBoxAttribute(LPCTSTR szName, LPCTSTR szText);

  private:
	void LayoutHorizontal(int size, int x, int y, int w, int h, UINT flags);
	void LayoutVertical(int size, int x, int y, int w, int h, UINT flags);
	void LayoutStackBox(int x, int y, int w, int h, UINT flags);

	BOOL LayoutHorizontalKeepView(int size, int x, int y, int w, int h, UINT flags);
	BOOL LayoutVerticalKeepView(int size, int x, int y, int w, int h, UINT flags);

	int GetCacheSplitOffset(LayoutLinkNode* node, BOOL isPrev);
};

/**
 * @brief 圆形布局对象
 */
class UI_EXP CLayoutCircle : public CLayoutBox
{
  public:
	int m_nRadius;

  public:
	CLayoutCircle();
	virtual ~CLayoutCircle();

	void Layout(int x, int y, int w, int h, UINT flags = 0) override;
};

/**
 * @brief  网格布局
 */
class UI_EXP CLayoutGrid : public CLayoutBox
{
  public:
	int m_columnCount;
	int m_nCellWidth;
	int m_nCellHeight;
	SizeMode m_nCellWidMode;
	SizeMode m_nCellHeiMode;
	SIZE m_invetalSize; // 网格间距尺寸
  public:
	CLayoutGrid();
	virtual ~CLayoutGrid();
	void SetIntervalSize(int cx, int cy);
	void SetColumCount(int count);
	void SetCellLayoutInfo(int w, int h, SizeMode stw, SizeMode sth);

	void Layout(int x, int y, int w, int h, UINT flags = 0) override;
};


}

#endif
