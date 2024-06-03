#ifndef _XORG_LINK_TREE_TOOL_BLXDY_INC_H_
#define _XORG_LINK_TREE_TOOL_BLXDY_INC_H_

template<typename TreeType>
class MultTree
{
  public:
	TreeType* parent = NULL;
	TreeType* firstChild = NULL;
	TreeType* lastChild = NULL;
	TreeType* prevSibling = NULL;
	TreeType* nextSibling = NULL;

  public:
	TreeType* FirstChild() const
	{
		return firstChild;
	}

	TreeType* LastChild() const
	{
		return lastChild;
	}

	TreeType* PrevSibling() const
	{
		return prevSibling;
	}

	TreeType* NextSibling() const
	{
		return nextSibling;
	}

	TreeType* Parent() const
	{
		return parent;
	}
};

template<typename TreeType>
void InitTree(TreeType* tree)
{
	tree->firstChild = tree->lastChild = tree->nextSibling = tree->prevSibling = tree->parent = 0;
};

template<typename TreeType>
int TreeInsert(TreeType* entry, TreeType* parent, TreeType* prevSlib)
{
	if (prevSlib && prevSlib->parent != parent)
		return 1;
	if (entry == parent)
		return 1;
	if (entry == NULL)
		return 1;
	entry->parent = parent;

	TreeType* next = prevSlib != 0 ? prevSlib->nextSibling : parent->firstChild;
	entry->prevSibling = prevSlib;
	entry->nextSibling = next;

	if (prevSlib)
		prevSlib->nextSibling = entry;
	else
		parent->firstChild = entry;

	if (next)
		next->prevSibling = entry;
	else
		parent->lastChild = entry;

	return 0;
};

template<typename TreeType>
void TreeInsertFirstChind(TreeType* entry, TreeType* parent)
{
	TreeInsert<TreeType>(entry, parent, 0);
};

template<typename TreeType>
void TreeInsertLastChind(TreeType* entry, TreeType* parent)
{
	TreeInsert<TreeType>(entry, parent, parent->lastChild);
};

template<typename TreeType>
void TreeDelete(TreeType* entry)
{
	TreeType* prev = entry->prevSibling;
	TreeType* next = entry->nextSibling;

	if (prev)
		prev->nextSibling = next;
	if (next)
		next->prevSibling = prev;

	if (entry == entry->parent->firstChild)
		entry->parent->firstChild = next;

	if (entry == entry->parent->lastChild)
		entry->parent->lastChild = prev;
};

template<typename TreeType>
void TreeMove(TreeType* entry, TreeType* parent, TreeType* prevSlib)
{
	if (entry != parent && entry != prevSlib)
	{
		TreeDelete(entry);
		TreeInsert(entry, parent, prevSlib);
	}
};

template<typename TreeType>
int TreeIsEmpty(TreeType* head)
{
	return head->firstChild == NULL ? 0 : 1;
};

template<typename TreeType>
size_t TreeChildCount(TreeType* entry)
{
	size_t count = 0;
	TreeType* hChild = entry->firstChild;
	while (hChild)
	{
		++count;
		hChild = hChild->nextSibling;
	}
	return count;
};

template<typename TreeType>
TreeType* GetTreeChildNode(TreeType* entry, int index)
{
	TreeType* current_child = NULL;

	if (entry == NULL)
		return NULL;

	current_child = entry->firstChild;
	while ((current_child != NULL) && (index > 0))
	{
		index--;
		current_child = current_child->nextSibling;
	}

	return current_child;
};

template<typename TreeType>
TreeType* NextTreeEntry(TreeType* entry, BOOL bskip)
{
	TreeType* next = bskip ? entry->nextSibling : entry->firstChild;
	if (next)
		return next;
	TreeType* par = entry;
	while (par)
	{
		next = par->nextSibling;
		if (next)
			return next;
		par = par->parent;
	}
	return next;
};




#endif
