/*
 * ShareMemPtr<T> 开辟一个T空间进行管理，当赋值时只改变引用计数，引用计数 <= 0 的时候销毁空间，
   用户在使用的过程中   ShareMemPtr<T>  p1(va);	   ShareMemPtr<T>  p2 = p1;
   此时p1 和p2指向同样的内存区域。 变量本身析构的时候，会将引用计数 -1
*/
#ifndef UI_WWW_SHAREMENPTR_BLXDY_INC_H_
#define UI_WWW_SHAREMENPTR_BLXDY_INC_H_

#include <deque>

template<typename T>
class PtrObjectPool
{
  public:
	std::deque<T> m_queItemsPool; /* 存放内存队列*/
	int m_nPoolSize;              /* 内存池的大小*/
  public:
	PtrObjectPool()
	    : m_nPoolSize(100){

	      };

	~PtrObjectPool()
	{
		int nlen = m_queItemsPool.size();
		for (int it = 0; it < nlen; it++)
		{
			if (m_queItemsPool[it])
			{
				delete m_queItemsPool[it];
				m_queItemsPool[it] = NULL;
			}
		}
		m_queItemsPool.clear();
	};

	// 设置池的大小
	void SetPoolSize(int size)
	{
		int nlen = m_queItemsPool.size();
		// 内存池中数据大小 超过给定大小。释放多余的内存
		if (size < nlen)
		{
			nlen = nlen - size;
			for (int it = 0; it < nlen; it++)
			{
				if (m_queItemsPool[it])
				{
					delete m_queItemsPool[it];
					m_queItemsPool[it] = NULL;
				}
			}
			m_queItemsPool.erase(m_queItemsPool.begin(), m_queItemsPool.begin() + nlen);
		}
		if (size > 0)
			m_nPoolSize = size;
	};

	// 从池中取出一块内存
	T& PopMemUint()
	{
		int nlen = m_queItemsPool.size();
		if (nlen <= 0)
			return (T)NULL;
		T& p = m_queItemsPool.front();
		m_queItemsPool.pop_front();
		return p;
	};

	bool PushMemUint(T pMem)
	{
		if (!pMem)
			return false;
		int nlen = m_queItemsPool.size();
		// 超过内存池的大小直接释放该内存 ，不进入内存池中
		if (nlen >= m_nPoolSize)
		{
			if (pMem)
			{
				delete pMem;
				pMem = NULL;
			}
			return false;
		}
		bool bFind = false;
		for (int i = 0; i < nlen; ++i)
		{
			if (pMem == m_queItemsPool[i])
			{
				bFind = true;
				break;
			}
		}

		if (!bFind)
			m_queItemsPool.push_back(pMem);
		return !bFind;
	};

	// 释放所有空间，清空内存池
	void ReleaseMemPool()
	{
		int n = m_queItemsPool.size();
		for (int i = 0; i < n; ++i)
		{
			if (m_queItemsPool[i])
			{
				// delete  m_queItemsPool[i];
				m_queItemsPool[i] = NULL;
			}
		}
		m_queItemsPool.clear();
	};

	int GetMemUintCount()
	{
		return m_queItemsPool.size();
	};

	// 获得内存池中的该位置数据内存 但不出栈
	T GetMemUint(int nIndex)
	{
		int n = m_queItemsPool.size();
		if (n <= 0 || nIndex < 0 || nIndex >= n)
			return (T)NULL;
		return m_queItemsPool[nIndex];
	};
};

#endif

#ifndef __SINGLETN_H__
#define __SINGLETN_H__

/********************************************************************************************
 *模板单例模式类
 ********************************************************************************************/
template<typename Ele>
class AutoDestory
{
  public:
	AutoDestory()
	    : pdata(0){};

	~AutoDestory()
	{
		if (pdata)
			delete pdata;
	};

  public:
	Ele* pdata;
};

template<typename Ele>
class SingletonPtr
{
  private:
	SingletonPtr() // 构造函数是私有的
	    {};

	~SingletonPtr() // 构造函数是私有的
	    {};

  private:
	static AutoDestory<Ele> _ptr;

  public:
	static Ele* GetSingletonPtr()
	{
		if (_ptr.pdata)
			return _ptr.pdata;
		_ptr.pdata = new Ele;
		return _ptr.pdata;
	}

	static void Release()
	{
		SAFEDEL(_ptr.pdata);
	}
};

template<typename Ele>
AutoDestory<Ele> SingletonPtr<Ele>::_ptr;


#endif // ___SINGLETN_H__