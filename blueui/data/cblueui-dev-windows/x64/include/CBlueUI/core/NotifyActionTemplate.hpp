
/*
This template requires c++11 standard
*/
#ifndef CBLUEUI_NOTIFYACTIONTEMPLATE_PRO_BLXDY_INC_H_
#define CBLUEUI_NOTIFYACTIONTEMPLATE_PRO_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "core/CCoreEventHandler.h"
#include "core/CCoreCharFunction.h"
// c standard
#include <stdlib.h>
// c++ standard
#include <vector>
#include <functional>

template<typename T = void()>
class FunctionActuator;

template<typename Ret, typename... Args>
class FunctionActuator<Ret(Args...)>
{
  public:
	typedef Ret value_type;
	typedef std::function<Ret(Args...)> CallValueFunc;

	FunctionActuator(CallValueFunc call)
	    : m_func(call)
	{
	}

	~FunctionActuator()
	{
	}

	value_type operator()(Args... args)
	{
		return m_func(args...);
	}

	value_type operator()(Args... args) const
	{
		return m_func(args...);
	}

  protected:
	CallValueFunc m_func;
};


template<typename T = BOOL()>
class FunctorAction;

template<typename Ret>
class FunctorAction<Ret()> : public FunctionActuator<Ret()>, public BUI::IActionNotify
{
	typedef std::function<Ret()> CallValueFunc;

  public:
	FunctorAction(CallValueFunc call)
	    : FunctionActuator<Ret()>(call)
	{
	}

	~FunctorAction()
	{
	}

	BOOL DoAction() override
	{
		return FunctionActuator<Ret()>::m_func();
	}
};











#endif
