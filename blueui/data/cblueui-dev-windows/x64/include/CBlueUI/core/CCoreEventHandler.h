#ifndef CBLUEUI_CEVENTHANDLER_PRO_BLXDY_INC_H_
#define CBLUEUI_CEVENTHANDLER_PRO_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include <vector>
#include <memory>
#pragma warning(disable : 4251)

namespace BUI {


union FourCode
{
	char ch[4];
	uint32_t code;
};

#define INIT_FOUR_CODE(op, a, b, c, d) \
	(op).ch[0] = (char)a; \
	(op).ch[1] = (char)b; \
	(op).ch[2] = (char)c; \
	(op).ch[3] = (char)d;

#define IS_FOUR_CODE(op, a, b, c, d) ((op).ch[0] == (char)a && (op).ch[1] == (char)b && (op).ch[2] == (char)c && (op).ch[3] == (char)d)

/**
 * @brief 对象之间传递数据的提交操作。比如表格单元格编辑后,更新到指定的单元格数据对象。按钮点击后关闭下拉窗口等
 */
class UI_EXP ICommitTarget
{
  public:
	ICommitTarget();
	virtual ~ICommitTarget();

	/**
	 * @brief 对象之间传递数据的提交操作
	 *
	 * @param four_code 由四个字符组合而成的类型符号
	 * @param data 额外字符串数据。可以是纯字符串，可以是json文本，可以是任意格式的数据流
	 */
	virtual void OnSummitTarget(FourCode four_code, LPCTSTR data);
};

class UI_EXP IEventHandler
{
  protected:
	IEventHandler();
	virtual ~IEventHandler();

  public:
	virtual BOOL OnMessageHandler(UINT message, WPARAM wp, LPARAM lp);
};

class UI_EXP IDockHandler
{
  protected:
	IDockHandler();
	virtual ~IDockHandler();

  public:
	virtual BOOL OnMessageHandler(UINT message, WPARAM wp, LPARAM lp);
};

class UI_EXP INotifyHandler
{
  protected:
	INotifyHandler();
	virtual ~INotifyHandler();

  public:
	virtual BOOL OnNotifyMessage(IEventHandler* notify, UINT message, WPARAM wp, LPARAM lp);
};

class UI_EXP IActionNotify
{
  public:
	IActionNotify();
	virtual ~IActionNotify();

	virtual BOOL DoAction() = 0;
};

class UI_EXP ActionList : public IActionNotify
{
  public:
	ActionList();
	~ActionList();

	void Clear();
	void AddAction(std::shared_ptr<IActionNotify> notify);
	const ActionList& operator=(const ActionList& other);


	BOOL DoAction() override;

  private:
	std::vector<std::shared_ptr<IActionNotify>> m_bind_list;
};

/* 基本交互事件组管理类*/
class UI_EXP EventTrigger
{
  public:
	EventTrigger();
	~EventTrigger();

	void BindActionNotify(ActionEvent ev, std::shared_ptr<IActionNotify> notify);

	void TriggerEvent(UINT message, WPARAM wp, LPARAM lp);

  private:
	std::shared_ptr<IActionNotify> m_events[6];
};

class UI_EXP IUserData
{
  public:
	IUserData(){};
	virtual ~IUserData(){};

	virtual void OnSelected() = 0;
};

class UI_EXP INodeData : public ICommitTarget
{
  public:
	INodeData() {}

	virtual ~INodeData() {}

	/* sup base NodeData*/
	virtual int LayoutAdaptWidth(int expH)  = 0;
	virtual int LayoutAdaptHeight(int expW) = 0;

	virtual int GetSplitControlOffsetW() = 0; ///< 获得拆分宽度偏移
	virtual int GetSplitControlOffsetH() = 0; ///< 获得拆分高度偏移

	virtual void Layout(int x, int y, int w, int h, UINT flags = 0) = 0;

	virtual RECT GetPosition() = 0; // 获得布局位置，用来测试鼠标命中

	virtual bool IsVisibleLayout() = 0;
};

/* 内存管理*/
class UI_EXP CMemoryAlloc
{
  public:
	CMemoryAlloc();
	~CMemoryAlloc();

	// 保证内存长度
	void EnsureSize(unsigned size);

	unsigned int Size() const;
	unsigned char* AddressPtr() const;

  private:
	unsigned char* m_ptr;
	unsigned int m_len;
};


}

#endif