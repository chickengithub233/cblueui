#ifndef CBLUEUI_IMAGEVIEW_BLXDY_INC_H_
#define CBLUEUI_IMAGEVIEW_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {

/**
 * @brief 图片视图控件
 *
 */
class UI_EXP CImageViewUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CImageViewUI)
  private:
	GImageIconInfo* m_pImage;
	double m_scale;
	double m_angle;
	ImageRatioStyle m_PreserveAspRatio; // 纵横比方式

	CTimerTask m_anim_timer;
	double m_anim_angle_step;

  public:
	CImageViewUI();
	~CImageViewUI();

	void SetImage(GImageIconInfo* pimg);
	void SetScale(double scale);
	void SetRoateAngle(double angle);

	void SetAnimAngleStep(int degree); ///< 设置旋转角度，范围[0-360]
	void SetAnimDelayTime(int ms);     ///< 设置动画时间， 小于0时代表停止
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | icon <br/>图表  | icon="图片资源符"	    |
	 * | ratio <br/>显示方式  | meet 	、slice 、none    |
	 * | anim-angle<br/> 动画每次旋转角度 | anim-angle="40" 角度值 |
	 * | delay-time<br/> 动画频率 | delay-time="200" 200毫秒 |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};

class UI_EXP CImageViewListUI : public CImageViewUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CImageViewListUI)
  private:
	std::vector<GImageIconInfo*> m_image_list;

  public:
	CImageViewListUI();
	~CImageViewListUI();

	int AddImage(GImageIconInfo* img); ///< 添加图标
	void Clear(BOOL bRedraw = TRUE);   ///< 清空

	void SetCurrentShow(int index, BOOL bRedraw = TRUE); ///< 设置当前显示索引


	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | icon <br/>图表  | icon="id1,id2,id3"	 图片资源符用逗号分开   |
	 * | cursel <br/>图表  | cursel="0"	 图片资源符索引号   |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};

// gif格式动画控件
class UI_EXP CGIFViewUI : public CControlUI, public IGIFHost
{
	DECLARE_DYNAMIC_OBJ_CLASS(CGIFViewUI)
  public:
	CGIFViewUI();
	~CGIFViewUI();

	void SetGifImage(GImageGIF* pGif);
	void Play();
	void Stop();

	/* CControlUI method:*/
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void CloneAttribute(CControlUI* clone) override;

	/**
	 * @brief 命令控制和属性设置接口
	 * |      szName属性       | szText语法格式
	 * |-------------------|-------------|
	 * | icon <br/>gif图标  | icon="gif资源符"	    |
	 */
	void ShellAttribute(const BeString& szName, const BeString& szText) override;

	/* IGIFHost method:*/
	void OnUpdataUI() override;
	void OnUpdataAll() override;
	void OnFreeObject() override;

  private:
	GImageGIF* m_pGIF;
	UINT m_nCurpos;
};

}

#endif
