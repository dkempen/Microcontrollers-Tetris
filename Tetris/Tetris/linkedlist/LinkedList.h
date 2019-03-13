#ifndef LLIST_DEF
#define LLIST_DEF

#include "../hardware/EasyBuzz.h"

typedef struct node
{
	note_struct data;
	struct node *next;
} node;

node *llist_create();
void  llist_add_last(node **, note_struct);
note_struct llist_get(node **);
void  llist_add(node **, note_struct);
void  llist_push(node **, note_struct);
note_struct llist_pop(node **);
note_struct llist_removeLast(node **);
note_struct llist_remove(node **, int);
void  llist_clear(node **);
int   llist_size(node *);
node *llist_copy(node *);

#endif
