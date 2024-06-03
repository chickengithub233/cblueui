#ifndef CBLUEUI_FILEREADER_BLXDY_INC_H_
#define CBLUEUI_FILEREADER_BLXDY_INC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <string>

#include "core/CCoreBasePro.h"

namespace BUI {

class UI_EXP FileReader
{
  public:
	enum CommentFlags
	{
		cpp_comment_style  = 1 << 0,                                                     // 类似C++风格注释
		xml_comment_style  = 1 << 1,                                                     // 类似xml风格注释 <!-- -->
		bash_comment_style = 1 << 2,                                                     // #; 注释风格
		all_comment_style  = cpp_comment_style | xml_comment_style | bash_comment_style, // #; 注释风格
	};

  protected:
	DataBuffer m_buf;

  public:
	FileReader();
	~FileReader();

	int LoadFileA(const char* filename_utf8);
	int LoadFileW(const WCHAR* filename);
	int LoadFile(const TCHAR* filename);
#ifdef _WIN32
	int LoadImageFromResource(HMODULE hMod, const TCHAR* resid, const TCHAR* restype); ///< window平台下, 从资源文件中读取数据
#endif
	DataBuffer GetDataBuffer(BOOL skipBom = FALSE) const;                    ///< 获得文件内容数据和长度信息
	void ClearComments(UINT commentflags = CommentFlags::cpp_comment_style); ///< 清除注释

	static void SaveAsFile(const char* filepath, const char* data, int len);
};

//
//// 通过资源定位url，读取出数据
// class UI_EXP FileResourceByUrl : public FileReader
//{
// protected:
//     DataBuffer  m_buf_no_free;  //析构时不需要自动释放
//     DataBuffer* m_bur_cur_ptr;
// public:
//     FileResourceByUrl();
//     ~FileResourceByUrl();
//
//     DataBuffer GetDataBuffer() const;
//
//     void LoadUrl(const char* filename);
// };


}
#endif
