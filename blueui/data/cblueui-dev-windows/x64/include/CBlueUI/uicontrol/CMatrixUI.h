#ifndef CBLUEUI_CMATRIXUI_H_INCLUDED_
#define CBLUEUI_CMATRIXUI_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CControlUI.h"

namespace BUI {


/**
 * @brief 矩阵控件
 *
 */
class UI_EXP CMatrixUI : public CControlUI
{
	DECLARE_DYNAMIC_OBJ_CLASS(CMatrixUI)
  protected:
	std::vector<double> m_datas;
	int m_nrow;
	int m_ncol;
	int m_cell_size; // if m_cell_size <= 0 is adapt rect
	int m_precision;

  public:
	CMatrixUI();
	~CMatrixUI();


	void SetMtrixDatas(std::vector<double>& values, int r, int c, BOOL isRefresh = TRUE);
	void FillAllWithValue(double va, BOOL isRefresh = TRUE);

	void Multiply(const CMatrixUI* m1, const CMatrixUI* m2);
	void Addition(const CMatrixUI* m1, const CMatrixUI* m2);

	void PrintToFile(FILE* fp) const;

	void ChangeThemeColors(int theme) override;
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam) override;
	BOOL OnMessageHandler(UINT message, WPARAM wParam, LPARAM lParam) override;
	BOOL DoPaint(ISurface* pSurface, RECT* lpUpdate) override;
	void ShellAttribute(const BeString& szName, const BeString& szText) override;
};




}
#endif
