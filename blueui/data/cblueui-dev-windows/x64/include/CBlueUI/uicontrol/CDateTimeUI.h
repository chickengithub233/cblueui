#ifndef CBLUEUI_CDATETIMEUI_BLXDY_INC_H_
#define CBLUEUI_CDATETIMEUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"
#include "CButtonUI.h"
#include "CEditTextUI.h"
#include "CNodeData.h"
#include "function/DateInfo.h"

namespace BUI {

enum DateTimeFlag
{
	NotSelectableWeekDay,   // 周末不可选择
	NotSelectableFutureDay, // 未来日不可选择
	ShowLunar,              // 显示农历
};

/**
 * @brief 日期控件
 *
 */
class UI_EXP CDateTimeUI : public CEditList, public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CDateTimeUI)
  private:
	DateInfo m_date; // 当前展示日期起点
	int m_nTitleHeight;
	int m_nItemHeight;
	DateInfo m_focusDate;
	UINT m_nHitFlag;

	DateInfo m_datebegin;
	DateInfo m_dateEnd;
	DateInfo m_SelectDate; // 当前选择日期

	UINT m_nDateModeFlags;
	BeString m_splitText;

	std::map<DateInfo, BeString> m_festivals;

  public:
	CDateTimeUI();
	~CDateTimeUI();

	DateInfo GetDate();
	void GoTodday();
	void ModifyDateTimeFlags(UINT style, UINT op = ADD_FLAGS); // 设置日期控件属性
	BOOL IsHasDateTimeFlags(UINT flags) const;

	void SetCurselDate(int y, int m, int d); ///< 设置选中日期
	void SetCurselDate(LPCTSTR strDate);
	void SetCalendarRange(DateInfo begin, DateInfo end);
	void SetItemHeight(int h);
	void SetTitleHeight(int h);
	void GetDateTimeText(BasicStringBuffer& str) const;

	void OnCreate() override;
	BeString GetControlText() override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseMove(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam) override;

	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | value <br/>设置日期  | value="20230715"	或者 value="now"    |
	 * | begin <br/>起始范围  | begin="19000101"	或者 begin="now"    |
	 * | end <br/>结束范围  | end="20230715"	或者 end="now"    |
	 * | lunar <br/>是否显示农历  | true / false    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

  protected:
	void CreateEditControl();
	void SetDateEditText(DateInfo& date);
	BOOL OnEditChange();
	BOOL IsEnableSelectDay(DateInfo& date);                      // 是否满足当前选择条件
	BOOL SetDate(int y, int m, int d, BOOL updateEditui = TRUE); // 设置选中日期
	BOOL SetDate(LPCTSTR strDate, BOOL updateEditui = TRUE);
	void CommitText();
};


}

#endif