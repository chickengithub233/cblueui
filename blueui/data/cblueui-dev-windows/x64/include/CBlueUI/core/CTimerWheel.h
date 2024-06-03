#ifndef CBLUEUI_TIMERWHEEL_BLXDY_INC_H_
#define CBLUEUI_TIMERWHEEL_BLXDY_INC_H_

#pragma once
/**
 * 定时器模块
 */


#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <functional>
#include <thread>
#include <atomic>
#include "CCoreBasePro.h"

// 第1个轮占的位数
#define TVR_BITS 8
// 第1个轮的长度
#define TVR_SIZE (1 << TVR_BITS)
// 第n个轮占的位数
#define TVN_BITS 6
// 第n个轮的长度
#define TVN_SIZE (1 << TVN_BITS)
// 掩码：取模或整除用
#define TVR_MASK (TVR_SIZE - 1)
#define TVN_MASK (TVN_SIZE - 1)


typedef std::function<void(uint32_t count, uint32_t times)> timer_cb_t; // 响应函数中的参数依次为:当前事件第n次数，期望执行总次数N


#define container_of(ptr, type, member) ((type*)((char*)(ptr) - (UINT_PTR)(&((type*)0)->member)))

// 定时器
typedef struct timer_handler
{
	timer_cb_t callback;
	uint32_t expire;
	uint32_t count;
	uint32_t times;
	uint32_t loop;
} timer_handler_t;

// 链表结点
typedef struct clinknode
{
	struct clinknode* next;
	struct clinknode* prev;
} clinknode_t;

// 定时器结点
typedef struct timernode
{
	clinknode_t* next;
	clinknode_t* prev;
	timer_handler timer_;
	std::atomic_bool is_kill;
} timernode_t;

// 第1个轮
typedef struct tvroot
{
	clinknode_t vec[TVR_SIZE];
} tvroot_t;

// 后面几个轮
typedef struct tvnum
{
	clinknode_t vec[TVN_SIZE];
} tvnum_t;

#define ALOOC_SIZE 256

// 内存分配
typedef struct blockitem
{
	clinknode_t* next;
	clinknode_t* prev;
	timernode_t node;
} blockitem_t;

typedef struct block
{
	blockitem_t items[ALOOC_SIZE];
	struct block* next;
} block_t;

// 时间轮定时器
typedef struct timerwheel
{
	tvroot_t tvroot_;        // 第1个轮
	tvnum_t tv[4];           // 后面4个轮
	long long start_up_time; // 启动时间毫秒
	long long lasttime;      // 上一次的时间毫秒
	long long currtick;      // 当前的tick
	long long interval;      // 每个时间点的毫秒间隔
	long long remainder;     // 剩余的毫秒
	bool isExit;
	int size_;
	block_t* block_;
	clinknode_t link_;

} timerwheel_t;

// 初始化时间轮，interval为每帧的间隔，currtime为当前时间
void timerwheel_init(timerwheel_t* tw, uint16_t interval, uint64_t currtime);
// 初始化时间结点：cb为回调，ud为用户数据
void timerwheel_node_init(timernode_t* node, timer_cb_t cb, void* ud);
// 增加时间结点，ticks为触发间隔(注意是以interval为单位)
void timerwheel_add(timerwheel_t* tw, timernode_t* node, uint32_t ticks, uint32_t delay_ticks);
// 删除结点
int timerwheel_del(timerwheel_t* tw, timernode_t* node);
// 更新时间轮
void timerwheel_update(timerwheel_t* tw, uint64_t currtime);

/**
 * @brief 定时器，以时间轮方式实现
 *
 */
class UI_EXP CTimerWheel
{
  public:
	CTimerWheel();
	~CTimerWheel();

	void InitWheel(uint16_t interval, uint64_t currtime);

	timer_handler* AddTimer(timer_cb_t cb, uint32_t loop, uint32_t delay, uint32_t times = 0);

	void KillTimer(timer_handler* timer);

	void Stop();

  private:
	void free_all();

	void startup();

	void thread_cb();

  protected:
	timerwheel* m_tw_;
	std::thread m_th_;
	bool is_start;
};

/**
 * @brief 定时任务对象,可以自动管理定时器的生命周期。对象析构时，自动释放
 *
 */
class UI_EXP CTimerTask
{
  public:
	CTimerTask();
	~CTimerTask();

	/// 设置任务
	BOOL SetTimer(timer_cb_t cb, uint32_t loop, uint32_t delay, uint32_t times = 0);
	/// 结束任务
	void KillTimer();
	/// 是否有效
	BOOL IsVaild() const;
	/// 是否中断
	BOOL IsAbort() const;

  private:
	timer_handler* m_task_handler;
};

extern "C" {

// 安装定时器
UI_EXP void InstallTimerManager(CTimerWheel* timerMgr);

// 获得定时器管理对象
UI_EXP CTimerWheel* TimerManager();
}

#endif
