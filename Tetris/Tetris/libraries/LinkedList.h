#ifndef LLIST_DEF
#define LLIST_DEF

typedef struct node
{
	note_struct data;
	struct node *next;
} node;

node *llist_create();
void  llist_print(node *);
void  llist_add(node **, note_struct);
void  llist_add_last(node **, note_struct);
void  llist_push(node **, note_struct);
note_struct llist_pop(node **);
note_struct llist_removeLast(node **);
note_struct llist_remove(node **, int);
note_struct llist_get(node **);
void  llist_clear(node **);
int   llist_size(node *);
int   llist_excist(node *, note_struct);
node *llist_copy(node *);

#endif
