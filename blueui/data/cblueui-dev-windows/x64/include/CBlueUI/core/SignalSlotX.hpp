#ifndef CBLUEUI_SIGNAL_SLOT_TEMPLATE_INC_H_
#define CBLUEUI_SIGNAL_SLOT_TEMPLATE_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "CCoreObject.h"

namespace BUI {


template<typename Ret, typename... Args>
class SlotImpl : public IXSlotBase
{
  public:
	SlotImpl(ST_Policy* policy = NULL)
	    : m_policy(policy)
	{
	}

	virtual ~SlotImpl()
	{
	}

	void SetPolicy(ST_Policy* policy)
	{
		m_policy = policy;
	}

	void UninstallSlot()
	{
		if (m_policy && m_bVaild)
			m_policy->RemoveSlot(this);
	}

	virtual void on_emit(Args... args) = 0;

	virtual bool compare(void* fun_ptr) = 0;
	virtual bool compare2(void* obj, void* fun_ptr) = 0;

  private:
	ST_Policy* m_policy;
};


template<typename funtype>
class Slot;

template<typename Ret, typename... Args>
class Slot<Ret(Args...)> : public SlotImpl<Ret, Args...>
{
	typedef Ret (*m_pfun)(Args...);

  public:
	Slot(m_pfun fuc)
	    : SlotImpl<Ret, Args...>(NULL)
	    , m_call(fuc)
	{
	}

	virtual ~Slot()
	{
	}

	virtual void on_emit(Args... args)
	{
		m_call(args...);
	}

	void operator()(Args... args)
	{
		m_call(args...);
	}

	virtual bool compare(void* fun_ptr)
	{
		return fun_ptr == m_call ? true : false;
	}

	virtual bool compare2(void* obj, void* fun_ptr)
	{
		return false;
	}

  private:
	m_pfun m_call;
};


template<typename dest_type, typename funtype>
class SlotMember;

template<typename dest_type, typename Ret, typename... Args>
class SlotMember<dest_type, Ret(Args...)> : public SlotImpl<Ret, Args...>
{
	typedef Ret (dest_type::*m_pmemfun)(Args...);
	typedef Ret (dest_type::*m_pmemfun_c)(Args...) const;

  public:
	SlotMember(dest_type* obj, m_pmemfun memfun, ST_Policy* policy = NULL)
	    : SlotImpl<Ret, Args...>(policy)
	    , m_obj(obj)
	    , m_call((m_pmemfun)memfun)
	{
	}

	SlotMember(dest_type* obj, m_pmemfun_c memfun, ST_Policy* policy = NULL)
	    : SlotImpl<Ret, Args...>(NULL)
	    , m_obj(obj)
	    , m_call((m_pmemfun)memfun)
	{
	}

	virtual ~SlotMember()
	{
	}

	virtual void on_emit(Args... args)
	{
		(m_obj->*m_call)(args...);
	}

	void operator()(Args... args)
	{
		(m_obj->*m_call)(args...);
	}

	virtual bool compare(void* fun_ptr)
	{
		return false;
	}

	virtual bool compare2(void* obj, void* fun_ptr)
	{
		union
		{
			void* uDst;
			m_pmemfun uSrc;
		} uMedia;

		uMedia.uSrc = m_call;

		if (obj == (void*)m_obj && fun_ptr == uMedia.uDst)
			return true;
		return false;
	}

  private:
	dest_type* m_obj;
	m_pmemfun m_call;
};


template<typename funtype>
class SignalX;

template<typename Ret, typename... Args>
class SignalX<Ret(Args...)>
{
	typedef SlotImpl<Ret, Args...> SlotBase;

  public:
	SignalX(){};

	~SignalX()
	{
		dis_connect_all();
	};

	template<Ret (*fun_ptr)(Args...)>
	void connect()
	{
		SlotBase* static_delegate = new Slot<Ret(Args...)>(fun_ptr);
		m_slots.push_back(static_delegate);
	}

	template<typename T, Ret (T::*mem_ptr)(Args...)>
	void connect(T* instance, ST_Policy* policy = NULL)
	{
		if (instance == NULL)
			return;
		SlotBase* member = new SlotMember<T, Ret(Args...)>(instance, mem_ptr, policy);
		m_slots.push_back(member);
	}

	template<typename T, Ret (T::*mem_ptr)(Args...) const>
	void connect(T* instance, ST_Policy* policy = NULL)
	{
		if (instance == NULL)
			return;
		SlotBase* member = new SlotMember<T, Ret(Args...)>(instance, mem_ptr, policy);
		m_slots.push_back(member);
	}

	template<Ret (*fun_ptr)(Args...)>
	void disconnect()
	{
		size_t len = m_slots.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (m_slots[i]->compare(fun_ptr))
			{
				free_slot(m_slots[i]);
				break;
			}
		}
	}

	template<typename T>
	void disconnect(T* instance, void* fun_ptr)
	{
		if (instance == NULL)
			return;
		size_t len = m_slots.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (m_slots[i]->compare2((void*)instance, fun_ptr))
			{
				free_slot(m_slots[i]);
				break;
			}
		}
	}

	template<typename T, Ret (T::*mem_ptr)(Args...)>
	void disconnect(T* instance)
	{
		if (instance == NULL)
			return;
		typedef Ret (T::*m_pmemfun)(Args...);

		union
		{
			void* uDst;
			m_pmemfun uSrc;
		} uMedia;

		uMedia.uSrc = mem_ptr;
		disconnect(instance, uMedia.uDst);
	}

	template<typename T, Ret (T::*mem_ptr)(Args...) const>
	void disconnect(T* instance)
	{
		typedef Ret (T::*m_pmemfun)(Args...) const;

		union
		{
			void* uDst;
			m_pmemfun uSrc;
		} uMedia;

		uMedia.uSrc = mem_ptr;
		disconnect(instance, uMedia.uDst);
	}

	void dis_connect_all()
	{
		size_t len = m_slots.size();
		for (size_t i = 0; i < len; ++i)
		{
			m_slots[i]->UninstallSlot();
			delete m_slots[i];
		}
		m_slots.clear();
	};

	void operator()(Args... args)
	{
		auto it1 = m_slots.begin();
		auto it_end = m_slots.end();
		while (it1 != it_end)
		{
			SlotBase* slot = *it1;
			if (slot->IsVaild())
			{
				slot->on_emit(args...);
				++it1;
			}
			else
			{
				slot->UninstallSlot();
				delete slot;
				it1 = m_slots.erase(it1);
			}
		}
	}

  private:
	void free_slot(SlotBase* slot)
	{
		if (slot)
			slot->SetVaildState(false);
	}

  private:
	std::vector<SlotBase*> m_slots;
};

template<typename T>
class DataSignalX
{
  public:
	DataSignalX()
	    : m_bFirstValue(false){};
	~DataSignalX(){};

	void operator=(T& value)
	{
		if (m_value != value || !m_bFirstValue)
		{
			m_bFirstValue = true;
			m_value = value;
			m_signal(m_value);
		}
	}

	void operator=(T value)
	{
		if (m_value != value || !m_bFirstValue)
		{
			m_bFirstValue = true;
			m_value = value;
			m_signal(m_value);
		}
	}

  private:
	bool m_bFirstValue;
	T m_value;

  public:
	SignalX<void(T)> m_signal;
};

class BoolDataSignalX
{
  public:
	BoolDataSignalX()
	    : m_value(2){};
	~BoolDataSignalX(){};

	void operator=(bool& value)
	{
		int va = value ? 1 : 0;
		if (m_value != va)
		{
			m_value = va;
			m_signal(m_value ? true : false);
		}
	}

	void operator=(bool value)
	{
		int va = value ? 1 : 0;
		if (m_value != va)
		{
			m_value = value;
			m_signal(m_value ? true : false);
		}
	}

  private:
	int m_value;

  public:
	SignalX<void(bool)> m_signal;
};

typedef DataSignalX<int> IntDataSignalX;
typedef DataSignalX<double> DoubleDataSignalX;
typedef DataSignalX<float> FloatDataSignalX;
typedef DataSignalX<char> CharDataSignalX;
typedef DataSignalX<unsigned int> UIntDataSignalX;
typedef DataSignalX<unsigned long> DwordDataSignalX;


}

#endif
