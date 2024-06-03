#ifndef CBLUEUI_IANIMATION_BLXDY_INC_H_
#define CBLUEUI_IANIMATION_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "core/CCoreObject.h"
#include "easing.h"

#ifdef _WIN32
#include "platform/win/CGDIGraphics.h"
#include "platform/win/bufferDC.h"
#endif

namespace BUI {

class UI_EXP IAnimation
{
  public:
	IAnimation();
	virtual ~IAnimation();

	/*动画运动的时间间隔(毫秒)和次数， 动画持续时间 = msec * count.  */
	virtual void Run(int msec, int count) = 0;

  protected:
	int m_Duration; // 动画总时长
	int m_Frames;   // 动画帧数
};

class CControlUI;

class UI_EXP BlindAnimationAction : public IAnimation
{
  public:
	BlindAnimationAction(CControlUI* pCtrl, RECT rcTarget, Animation_Fun fn);
	~BlindAnimationAction();

	void Run(int msec, int count) override;

  protected:
	IManageHandler* m_manager; // 输出屏幕
	XImageInfo m_out_buf;
	XImageInfo m_back_buf;
	XImageInfo m_src_buf;

	RECT m_rcSrc;
	RECT m_rcTarget;
	Animation_Fun m_fn[4];
};

class UI_EXP AnimationControlMove : public IAnimation
{
  public:
	AnimationControlMove(CControlUI* pCtrl, RECT rcSrc, RECT rcTarget, Animation_Fun fn[]);
	~AnimationControlMove();

	void Run(int msec, int count) override;

  protected:
	RECT m_rcSrc;
	RECT m_rcTarget;
	Animation_Fun m_fn[4];
};

}
#endif
