#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

node_t Node_New(const char *name, const char *ip) {
	node_t node = malloc(sizeof(struct LinkedList));
	if(node == NULL) return NULL;

	strcpy(node->name, name);
	strcpy(node->ip, ip);
	node->next = NULL;

	return node;
}

void Node_Free(node_t node) {
	if (node == NULL) {
		return;
	}

	node_t tmp = node->next;

	free(node->name);
	free(node->ip);
	free(node);	

	Node_Free(tmp);
}

void Node_AppendNode(node_t to, node_t node) {
	if (to == NULL || node == NULL) {
		return;
	}

	if (to->next == NULL) {
		to->next = node;
	} else {
		Node_AppendNode(to->next, node);
	}
}

void LinkedList_Append(linkedlist_t list, const char *name, const char *ip) {
	if (list == NULL) {
		return;
	}

	node_t node = Node_New(name, ip);

	if(list->head == NULL) {
		list->head = node;
	} else {
		Node_AppendNode(list->head, node);
	}
}

void LinkedList_Delete(linkedlist_t list, const char *name) {
	if (list == NULL || list->head == NULL) {
		return;
	}

	node_t from = list->head;

	if(strcmp(name, from->name) == 0) {
		list->head = from->next;
		from->next = NULL;
		Node_Free(from);
	} else {
		node_t prev = from;

		while((from = from->next) != NULL) {
			if(strcmp(name, from->name) == 0) {
				node_t tmp = from->next;
				from->next = NULL;
				Node_Free(from);
				
				prev->next = tmp;
			} else {
				prev = from;
			}
		}
	}
}

const char* LinkedList_FindByName(const linkedlist_t list, const char* name) {
	if(list == NULL) {
		return NULL;
	}

	node_t node = list->head;

	while(node != NULL) {
		if(strcmp(node->name, name) == 0) {
			return node->ip;
		}

		node = node->next;
	}

	return NULL;
}