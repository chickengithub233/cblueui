#ifndef BUILIB_STACKSTRING_BLXDY_INC_H_
#define BUILIB_STACKSTRING_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "StringBufferBasic.h"

class UI_EXP BeStringShortA64 : public BasicStringBufferA
{
  public:
	BeStringShortA64();
	BeStringShortA64(const char* str, int count = -1);
	BeStringShortA64(const WCHAR* wstr, int count = -1, unsigned int CodePage = CP_UTF8);

	~BeStringShortA64();

  private:
	char buffer[64];
};

class UI_EXP BeStringShortA128 : public BasicStringBufferA
{
  public:
	BeStringShortA128();
	BeStringShortA128(const char* str, int count = -1);
	BeStringShortA128(const WCHAR* wstr, int count = -1, unsigned int CodePage = CP_UTF8);
	~BeStringShortA128();

  private:
	char buffer[128];
};

class UI_EXP BeStringShortA260 : public BasicStringBufferA
{
  public:
	BeStringShortA260();
	BeStringShortA260(const char* str, int count = -1);
	BeStringShortA260(const WCHAR* wstr, int count = -1, unsigned int CodePage = CP_UTF8);
	~BeStringShortA260();

  private:
	char buffer[260];
};

class UI_EXP BeStringShortW64 : public BasicStringBufferW
{
  public:
	BeStringShortW64();
	BeStringShortW64(const char* str, int count = -1, unsigned int CodePage = CP_ACP);
	BeStringShortW64(const WCHAR* wstr, int count = -1);
	~BeStringShortW64();

  private:
	WCHAR buffer[64];
};

class UI_EXP BeStringShortW128 : public BasicStringBufferW
{
  public:
	BeStringShortW128();
	BeStringShortW128(const char* str, int count = -1, unsigned int CodePage = CP_ACP);
	BeStringShortW128(const WCHAR* wstr, int count = -1);
	~BeStringShortW128();

  private:
	WCHAR buffer[128];
};

class UI_EXP BeStringShortW260 : public BasicStringBufferW
{
  public:
	BeStringShortW260();
	BeStringShortW260(const char* str, int count = -1, unsigned int CodePage = CP_ACP);
	BeStringShortW260(const WCHAR* wstr, int count = -1);
	~BeStringShortW260();

  private:
	WCHAR buffer[260];
};

// 通用字符预定义
#ifdef _UNICODE
typedef BeStringShortW64 BeStringShort64;
typedef BeStringShortW128 BeStringShort128;
typedef BeStringShortW260 BeStringShort260;
#else
typedef BeStringShortA64 BeStringShort64;
typedef BeStringShortA128 BeStringShort128;
typedef BeStringShortA260 BeStringShort260;
#endif



#endif
