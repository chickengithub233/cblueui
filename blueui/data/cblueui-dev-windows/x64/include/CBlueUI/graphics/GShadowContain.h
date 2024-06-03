#ifndef CBLUEUI_GSHADOWCONTAIN_INCLUDED_
#define CBLUEUI_GSHADOWCONTAIN_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "GSurface.h"
#include <vector>

namespace BUI {

	
class UI_EXP GShadowContain
{
	public:
	GShadowContain();
	~GShadowContain();

	// 添加阴影
	int AddShadow(int dx, int dy, int blur_size, int spread_size, GColor color, bool inset = false);

	// 更新阴影
	void UpdateShadow(int pos, int dx, int dy, int blur_size, int spread_size, GColor color, bool inset = false);

	// 删除阴影
	void RemoveShadow(int pos);

	// 清空阴影
	void ClearShadow();

	// 克隆
	void CloneFrom(GShadowContain* other);

	// 绘制阴影
	void DrawShadow(ISurface* surface, PathTransInfo& pathinfo, bool inset);

	//  是否包含inset模式的阴影
	BOOL GShadowContain::IsShadowCount(bool inset) const;

	private:
	std::vector<ShadowInfo*> m_shadowbox_list; // 外Shadow 特效
};

}










#endif