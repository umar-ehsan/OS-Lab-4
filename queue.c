/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

void *push(node_t *head, process proc){
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    node_t *current_node = head;
    while(current_node != NULL){
        node
    }
    
    //or add item to end of list
	node_t * current = head;
	while (current -> next != NULL){
     		current = current -> next;	
	}
	current -> next = malloc(sizeof(node_t));
	current -> next -> process = process;
	current -> next -> next = NULL;
}    

// Remove head from the list which is the first item added
node_t *pop(node_t **head){
	*get_node = NULL;
	node_t *next_node = NULL;
	if (*head == NULL){
		return -1;
	}
	next_node = (*head)->next;
	*get_node = head -> process;
	free(*head);
	*head = next_node;

	return get_node;
}
