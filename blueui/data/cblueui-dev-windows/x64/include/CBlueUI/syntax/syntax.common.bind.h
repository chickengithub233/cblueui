
/**
 * @brief common语法树功能绑定
 *
 */

#ifndef AST_COMMION_BIND_MDBINC_H
#define AST_COMMION_BIND_MDBINC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#include "SyntaxTree.h"


/**
 * @brief 绑定事件和纠错处理
 *
 */
void UI_EXP bind_syntax_common(syntax_tree_node* node);

/**
 * @brief 执行语法树行为
 *
 */
void UI_EXP run_syntax_common(syntax_info* ast);

#endif
