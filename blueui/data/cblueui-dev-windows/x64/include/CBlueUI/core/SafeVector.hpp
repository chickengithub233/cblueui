#ifndef _SAFE_VECTOR_TOOL_BLXDY_INC_H_
#define _SAFE_VECTOR_TOOL_BLXDY_INC_H_

#include "StdAtomicLock.hpp"
#include <mutex>

template<typename T>
class vector_safe
{
  public:
	vector_safe()
	{
	}

	~vector_safe()
	{
		clear();
	}

	T& operator[](int _Pos)
	{
		// if (!(_Pos >= 0 && _Pos < size()))
		//{
		//	int a = 0;
		//	a = 100;
		// }
		assert(_Pos >= 0 && _Pos < size());
		LockGuard lock(&m_mutex);
		// std::unique_lock<std::mutex> lock(m_mutex);
		return m_datas.at(_Pos);
	}

	const T& operator[](int _Pos) const
	{
		assert(_Pos >= 0 && _Pos < size());
		LockGuard lock(&m_mutex);
		// std::unique_lock<std::mutex> lock(m_mutex);
		return m_datas.at(_Pos);
	}

	void insert(int pos, const T& _Val)
	{
		assert(pos >= 0 && pos <= size());
		LockGuard lock(&m_mutex);

		m_datas.insert(m_datas.begin() + pos, _Val);
	}

	void erase(int pos, int end)
	{
		assert(pos >= 0 && pos < size());
		assert(end > pos && end <= size());

		LockGuard lock(&m_mutex);
		m_datas.erase(m_datas.begin() + pos, m_datas.begin() + end);
	}

	void clear()
	{
		LockGuard lock(&m_mutex);
		m_datas.clear();
	}

	void push_back(const T& _Val)
	{
		LockGuard lock(&m_mutex);
		m_datas.push_back(_Val);
	}

	size_t size() const
	{
		return m_datas.size();
	}

	void resize(int _Newsize)
	{
		LockGuard lock(&m_mutex);
		m_datas.resize(_Newsize);
	}

  private:
	std::vector<T> m_datas;
	// mutable std::mutex m_mutex;
	mutable AtomicLock m_mutex;
};

#endif
