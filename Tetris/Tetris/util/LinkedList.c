// Ignore pragma warnings, because Atmel doesn't like code regions for some reason
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

// Init the list
node *llist_create()
{
	node *head = NULL;
	return head;
}

// Gets the data of the current node and shifts the current node to the next node
note_struct llist_get(node **current_node)
{
	note_struct note = (*current_node)->data;
	*current_node = (*current_node)->next;
	return note;
}

// Add an item to the end of the list with a previous node pointer as parameter and shifts the last node to the current node
void llist_add_last(node **head_node, note_struct data)
{
	node *current = *head_node;
	if (current == NULL)
	{
		current = (node*)malloc(sizeof(node));
		current->data = data;
		current->next = NULL;
		*head_node = current;
		return;
	}

	while (current->next != NULL)
	current = current->next;

	current->next = malloc(sizeof(node));
	current->next->data = data;
	current->next->next = NULL;
}
