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

// Add an item to the end of the list with a previous node pointer as parameter
void llist_add_last(node **last_node, note_struct data)
{
	node *current = *last_node;
	if (current == NULL)
	{
		current = (node*)malloc(sizeof(node));
		current->data = data;
		current->next = NULL;
		*last_node = current;
		return;
	}

	current->next = malloc(sizeof(node));
	current->next->data = data;
	current->next->next = NULL;
}

#pragma region unused_functions
// Add an item to the end of the list
void llist_add(node **head, note_struct data)
{
	node *current = *head;
	if (current == NULL)
	{
		current = (node*)malloc(sizeof(node));
		current->data = data;
		current->next = NULL;
		*head = current;
		return;
	}

	while (current->next != NULL)
	current = current->next;

	current->next = malloc(sizeof(node));
	current->next->data = data;
	current->next->next = NULL;
}

// Add an item to the beginning of the list
void llist_push(node **head, note_struct data)
{
	node *new_node;
	new_node = malloc(sizeof(node));

	new_node->data = data;
	new_node->next = *head;
	*head = new_node;
}

// Remove the first item
note_struct llist_pop(node** head)
{
	node *nextNode = NULL;
	note_struct value;

	if (*head == NULL)
		return value;

	nextNode = (*head)->next;
	value = (*head)->data;
	free(*head);
	*head = nextNode;

	return value;
}

// Remove the last item
note_struct llist_removeLast(node **head)
{
	node *current = *head;
	note_struct value;
	/* if there is only one item in the list, remove it */
	if (current->next == NULL)
	{
		value = current->data;
		free(current);
		return value;
	}

	/* get to the second to last dnode in the list */
	while (current->next->next != NULL)
		current = current->next;

	/* now current points to the second to last item of the list, so let's remove current->next */
	value = current->next->data;
	free(current->next);
	current->next = NULL;
	return value;
}

// Remove an item at an index
note_struct llist_remove(node **head, int index)
{
	node *current = *head;
	note_struct value;

	if (index == 0)
		return llist_pop(head);

	for (int i = 0; i < index - 1; i++)
	{
		if (current->next == NULL)
			return value;
		current = current->next;
	}

	node *tempNode = NULL;
	tempNode = current->next;
	value = tempNode->data;
	current->next = tempNode->next;
	free(tempNode);

	return value;
}

// Clear the list (delete everything from memory)
void llist_clear(node **head)
{
	node *current = *head;
	node *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

// Get the size of the list
int llist_size(node *head)
{
	node *current = head;

	int size = 0;
	while (current != NULL)
	{
		current = current->next;
		size++;
	}

	return size;
}

// Make a deep copy of the list
node *llist_copy(struct node *head)
{
	node *headCopy = NULL;
	node *current = head;
	
	while(current != NULL)
	{
		llist_add(&headCopy, current->data);
		current = current->next;
	}

	return headCopy;
}
#pragma endregion unused_functions
