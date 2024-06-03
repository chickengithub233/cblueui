/*
This template requires c++11 standard
*/
#ifndef CBLUEUI_THREAD_POOL_PRO_BLXDY_INC_H_
#define CBLUEUI_THREAD_POOL_PRO_BLXDY_INC_H_

#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "CCoreBasePro.h"
#include "SafeQueue.hpp"

namespace BUI {

/**
 * @brief 跨平台线程池
 *
 */
class UI_EXP CThreadPool
{
  public:
	CThreadPool();
	~CThreadPool();

	void InitPoolSize(int n);

	void Shutdown();

	void SubmitTask(std::function<void()> fn);

	bool IsShutdown();

  protected:
	int m_thread_count;
	bool m_shutdown;
	SafeQueue<std::function<void()>> m_queue;
	std::vector<std::thread> m_threads;
	std::mutex m_conditional_mutex;
	std::condition_variable m_conditional_lock;
};

}
#endif