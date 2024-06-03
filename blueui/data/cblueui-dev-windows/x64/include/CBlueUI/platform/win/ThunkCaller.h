#ifndef THUNK_CALLBACKER_INCLUDED_
#define THUNK_CALLBACKER_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// 没有使用MFC框架
#ifndef _MFC_VER

#define _WINSOCKAPI_
#include <Windows.h>

#else

#include <afxwin.h>
#include <afxcmn.h>

#endif


namespace BUI {

// 堆上可分配执行代码
class HeapExecute
{
  private:
	HeapExecute();
	~HeapExecute();

  public:
	static void LockSharePtr(LPARAM lp);

	static void UnlockSharePtr();

	static LPARAM GetSharePtr();

	static HANDLE GetHeap();

	static UINT GetCPUType(); /* 0:x86 1:amd64 2:arm*/

	static void* InstallThunkCode(DWORD_PTR proc, void* pThis);
};


}

/************************************************************************/
/*      代码注入技术     函数名就是指令，参数存于栈上
/************************************************************************/
// #if defined(_M_IX86)
//  按一字节对齐
#pragma pack(push, 1)

struct ThunkCodeX86
{
	DWORD m_mov; // 4个字节
	DWORD m_this;
	BYTE m_jmp;
	DWORD m_relproc;

	void Init(DWORD_PTR proc, void* pThis)
	{
		// 关键代码   //////////////////////////////////////
		m_mov     = 0x042444C7;                                                      /* mov指令机器码*/
		m_this    = (DWORD)(ULONG_PTR)pThis;                                         /* mov [esp + 4], pThis;而esp + 4本来是放hWnd, 现在被偷着放对象指针了.*/
		m_jmp     = 0xe9;                                                            /* 跳转指令机器码*/
		m_relproc = (DWORD)((INT_PTR)proc - ((INT_PTR)this + sizeof(ThunkCodeX86))); /* 跳转到proc指定的入口函数 */
		FlushInstructionCache(GetCurrentProcess(), this, sizeof(ThunkCodeX86));      /* 告诉CPU把以上四条语句不当数据，当指令, 接下来用GetCodeAddress获得的指针就会运行此指令*/
	}

	void* GetCodeAddress() { return this; /* 指向this, 那么由GetCodeAddress获得的函数pProc是从DWORD m_mov;开始执行的*/ }
};

#pragma pack(pop)

// #elif defined(_M_AMD64)
#pragma pack(push, 2)

struct ThunkCodeAMD64
{
	USHORT RcxMov; /* mov rcx, pThis*/
	ULONG64 RcxImm;
	USHORT RaxMov; /* mov rax, target*/
	ULONG64 RaxImm;
	USHORT RaxJmp; /* jmp target*/

	void Init(DWORD_PTR proc, void* pThis)
	{
		RcxMov = 0xb948; /* mov rcx, pThis*/
		RcxImm = (ULONG64)pThis;
		RaxMov = 0xb848; /* mov rax, target*/
		RaxImm = (ULONG64)proc;
		RaxJmp = 0xe0ff; /* jmp rax*/
		FlushInstructionCache(GetCurrentProcess(), this, sizeof(ThunkCodeAMD64));
	}

	void* GetCodeAddress() /* some thunks will dynamically allocate the memoryforthe code*/ { return this; }
};

#pragma pack(pop)
// #elif defined(_ARM_)
#pragma pack(push, 4)

struct ThunkCodeArm /* this should come out to 16 bytes*/
{
	DWORD m_mov_r0; /* mov    r0, pThis*/
	DWORD m_mov_pc; /* mov    pc, pFunc*/
	DWORD m_pThis;
	DWORD m_pFunc;

	void Init(DWORD_PTR proc, void* pThis)
	{
		m_mov_r0 = 0xE59F0000;
		m_mov_pc = 0xE59FF000;
		m_pThis  = (DWORD)pThis;
		m_pFunc  = (DWORD)proc;
		FlushInstructionCache(GetCurrentProcess(), this, sizeof(ThunkCodeArm));
	}

	void* GetCodeAddress() { return this; }
};

#pragma pack(pop)
// #else
// #error Only AMD64, ARM and X86 supported
// #endif


#define THUNK_ALLOC(nsize) ::VirtualAlloc(NULL, nsize, MEM_COMMIT, PAGE_EXECUTE_READWRITE)

#define THUNK_FREE(ptr) ::VirtualFree(ptr, 0, MEM_RELEASE)


#define FLUSHINSTRUCTIONCACHE(type) ::FlushInstructionCache(::GetCurrentProcess(), this, sizeof(type));



#pragma pack(push, 1)

// 这种方式值适合调用约定为 thiscall 的
struct MemFunThisCallThunk
{
	BYTE m_mov;
	DWORD m_this; /* mov ecx pThis*/
	BYTE m_jmp;
	DWORD m_relproc; /* jmp  偏移地址*/

	BOOL Init(DWORD_PTR proc, void* pThis)
	{
		m_mov     = 0xB9; /*  mov ecx*/
		m_this    = PtrToUlong(pThis);
		m_jmp     = 0xe9;
		m_relproc = DWORD((INT_PTR)proc - ((INT_PTR)this + sizeof(MemFunThisCallThunk))); /* jmp跳转的地址为相对地址, 相对地址 = 目标地址 - 当前指令下一条指令的地址 */
		FLUSHINSTRUCTIONCACHE(MemFunThisCallThunk);
		return TRUE;
	}

	void* GetCodeAddress() { return this; }
};

typedef unsigned char byte1;
typedef unsigned short byte2;
typedef unsigned int byte4;

struct MemFunCdeclThunk
{
	BYTE pop_ret[7];
	BYTE push_this[5];
	BYTE push_my_ret[5];
	BYTE jmp_mfn[5];
	BYTE add_esp[3];
	BYTE jmp_ret[7];
	DWORD ret_addr;

	BOOL Init(DWORD_PTR proc, void* pThis)
	{
		pop_ret[0]           = 0x3E;
		pop_ret[1]           = 0x8F;
		pop_ret[2]           = 0x05;
		*(DWORD*)&pop_ret[3] = (DWORD)&ret_addr;

		push_this[0]           = 0x68;
		*(DWORD*)&push_this[1] = (DWORD)pThis;

		push_my_ret[0]           = 0x68;
		*(DWORD*)&push_my_ret[1] = (DWORD)&add_esp[0];

		jmp_mfn[0]           = 0xE9;
		*(DWORD*)&jmp_mfn[1] = (DWORD)proc - ((DWORD)&jmp_mfn + 5);

		add_esp[0] = 0x83;
		add_esp[1] = 0xC4;
		add_esp[2] = 0x04;

		jmp_ret[0]           = 0x3E;
		jmp_ret[1]           = 0xFF;
		jmp_ret[2]           = 0x25;
		*(byte4*)&jmp_ret[3] = (byte4)&ret_addr;
		FLUSHINSTRUCTIONCACHE(MemFunCdeclThunk);
		return TRUE;
	}

	void* GetCodeAddress() { return this; }
};

struct MemFunStdcallThunk
{
	BYTE push[3];
	DWORD mov;
	DWORD pthis;
	BYTE jmp;
	DWORD addr;

	BOOL Init(DWORD_PTR proc, void* pThis)
	{
		push[0] = 0xFF;
		push[1] = 0x34;
		push[2] = 0x24;

		mov   = 0x042444C7;
		pthis = (DWORD)pThis;

		jmp  = 0xE9;
		addr = (DWORD)proc - ((DWORD)&jmp + 5);
		FLUSHINSTRUCTIONCACHE(MemFunStdcallThunk);
		return TRUE;
	}

	void* GetCodeAddress() { return this; }
};

#pragma pack(pop)


#endif