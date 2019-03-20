#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

struct Node {
	struct Node *next;
	char name[256];
	char ip[256];
};

typedef struct Node *node_t;

node_t Node_New(const char*, const char*);
void Node_AppendNode(node_t to, node_t node);
void Node_Free(node_t);

struct LinkedList {
	node_t head;
};

typedef struct LinkedList *linkedlist_t;

void LinkedList_Append(linkedlist_t, const char*, const char*);
void LinkedList_Delete(linkedlist_t, const char*);
const char* LinkedList_FindByName(const linkedlist_t, const char*);

#endif