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

// Add an item to the end of the list with the head node pointer as parameter
void llist_add(node **head_node, note_struct data)
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
