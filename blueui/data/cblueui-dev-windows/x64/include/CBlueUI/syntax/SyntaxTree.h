
/**
 * @brief 语法结构树
 *
 */

#ifndef AST_CPP_MDBINC_H
#define AST_CPP_MDBINC_H

#ifdef BUI_VERSION
#include "core/CCoreBasePro.h"
#define AST_EXP UI_EXP
#else
#define AST_EXP
#endif

#include <string>
#include <vector>
#include <functional>

#define INIT_ASTOP_4(op, a, b, c, d) \
	(op).ch[0] = (char)a; \
	(op).ch[1] = (char)b; \
	(op).ch[2] = (char)c; \
	(op).ch[3] = (char)d;

#define IS_ASTOP_4(op, a, b, c, d) (op).ch[0] == (char)a && (op).ch[1] == (char)b && (op).ch[2] == (char)c && (op).ch[3] == (char)d

struct TokensType
{
	int type;
	int pos;
};

union ASTOP
{
	char ch[4];
	int32_t code;
};

typedef struct syntax_tree_node
{
	/* op code*/
	ASTOP op;
	const char* value;

	/* ast node return data*/
	std::string out_str;
	double value_num;
	struct syntax_tree_node* value_ref_node;
	/* error code. 0 is no error*/
	int error_code;

	int is_bind;
	/* tree link data */
	struct syntax_tree_node* parent;
	struct syntax_tree_node* firstChild;
	struct syntax_tree_node* lastChild;
	struct syntax_tree_node* prevSibling;
	struct syntax_tree_node* nextSibling;
	/* action */
	std::function<void(syntax_tree_node* node)> action;

	syntax_tree_node();
	~syntax_tree_node();
} syntax_tree_node;

typedef struct syntax_info
{
	std::vector<TokensType> words_type;
	std::vector<char*> words;
	syntax_tree_node ast_root;

	syntax_info();
	~syntax_info();

} syntax_info;

/**
 * @brief 插入语法节点
 *
 * @param entry 待插入节点
 * @param parent  父节点
 * @param prevSlib 前一个兄弟节点
 * @return int 返回0 代表成功
 */
int syntax_tree_insert(syntax_tree_node* entry, syntax_tree_node* parent, syntax_tree_node* prevSlib);

/**
 * @brief 插入到最后一个子节点
 *
 * @param entry 待插入节点
 * @param parent 父节点
 * @return int 返回0 代表成功
 */
int syntax_tree_insert_last(syntax_tree_node* entry, syntax_tree_node* parent);

/**
 * @brief 删除节点
 *
 */
void syntax_tree_delete(syntax_tree_node* entry);

/**
 * @brief 打印层级结构
 *
 * @param ast 当前节点
 * @param indent 缩进等级
 */
void syntax_tree_print(syntax_tree_node* ast, int indent);

/// 语法参数链表
struct syntax_param_node
{
	syntax_tree_node* ast;
	int type;
	syntax_param_node* next;
	syntax_param_node* prev;

	syntax_param_node();
	~syntax_param_node();
};

/**
 * @brief 插入到参数列表
 *
 * @param entry 当前节点
 * @param prev 前向指针
 * @param next 后继指针
 */
void syntax_param_insert(syntax_param_node* entry, syntax_param_node* prev, syntax_param_node* next);

/**
 * @brief 插入到参数列表最后
 *
 * @param entry 当前节点
 * @param head 链表头
 */
void syntax_param_add(syntax_param_node* entry, syntax_param_node* head);

/**
 * @brief 释放链表
 *
 */
void syntax_param_list_free(syntax_param_node* head);

/**
 * @brief 将参数列表转换为树结构
 *
 */
void insert_param_to_ast(syntax_param_node* head, syntax_tree_node* parent);


/**
 * @brief 解析自研语法格式
 *
 */
void AST_EXP parse_syntax_common(syntax_info* out_syntax, const char* src_txt, bool is_only_lex = false);
#endif
