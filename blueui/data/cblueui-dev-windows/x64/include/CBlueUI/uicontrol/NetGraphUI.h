#ifndef CBLUEUI_NETGRAPHUI_BLXDY_INC_H_
#define CBLUEUI_NETGRAPHUI_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {


class NetNode
{
  public:
	double x;
	double y;
	double vx;
	double vy;

	NetNode()
	    : x(0)
	    , y(0)
	    , vx(0)
	    , vy(0)
	{}
};

class EdgeLink
{
  public:
	int source;
	int target;
};

void forceSpring(NetNode* nodes, EdgeLink links[], int count, float alpha);

void forceCenter(NetNode* nodes, int len, int x, int y);

void forceRadial(NetNode* nodes, int len, int radius, int x, int y, int strength, float alpha);

void forceManyBody(NetNode* nodes, int len, int strength, float alpha);

class UI_EXP NetGraphUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(NetGraphUI)
  private:
	NetNode* m_nodes;
	EdgeLink* m_edges;

  public:
	NetGraphUI();
	virtual ~NetGraphUI();
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
};

}
#endif