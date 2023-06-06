#ifndef __LISTINTERNAL_H__
#define __LISTINTERNAL_H__

typedef struct Node Node;


struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
};

void InsertNode( Node *_befor, Node *_insert);
void RemoveNode( Node *_remove);

#endif /* __LISTINTERNAL_H__ */