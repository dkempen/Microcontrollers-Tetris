#ifndef LLIST_DEF
#define LLIST_DEF

#include "../hardware/EasyBuzz.h"

typedef struct node
{
	note_struct data;
	struct node *next;
} node;

node *llist_create();
void  llist_add(node **, note_struct);

#endif
