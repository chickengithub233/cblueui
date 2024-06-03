#ifndef _ATOMIC_LOCK_TOOL_BLXDY_INC_H_
#define _ATOMIC_LOCK_TOOL_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atomic>
#include <thread>

/*简单原子锁，仅包含两种状态*/
class AtomicLock
{
  public:
	AtomicLock()
	{
		m_flag.clear(std::memory_order_release);
	}

	~AtomicLock()
	{
	}

	void lock()
	{
		while (m_flag.test_and_set(std::memory_order_acquire))
			std::this_thread::yield();
	}

	void unlock()
	{
		m_flag.clear(std::memory_order_release);
	}

  public:
	std::atomic_flag m_flag; // = ATOMIC_FLAG_INIT;
};

/*加锁和释放管理者, 可避免开发者，退出时未释放锁，造成死锁*/
class LockGuard
{
  public:
	LockGuard(AtomicLock* lock)
	    : m_lock(lock)
	{
		m_lock->lock();
	}

	~LockGuard()
	{
		m_lock->unlock();
	}

  private:
	LockGuard(const LockGuard&);
	LockGuard& operator=(const LockGuard&);

  private:
	AtomicLock* m_lock;
};

#endif
