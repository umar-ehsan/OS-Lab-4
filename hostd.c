/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define MAX_PROCESS 1000

// Put global environment variables here
node_t *dispatch_list, *job_queue, *realtime_queue, *first_priority, *second_priority, *third_priority;

// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    char filename[256]; //filename from input argument

    // initializing all the queues
    dispatch_list = (node_t*) malloc(sizeof(node_t));
    dispatch_list->next_node = NULL;
    job_queue = (node_t*) malloc(sizeof(node_t));
    job_queue->next_node = NULL;
    realtime_queue = (node_t*) malloc(sizeof(node_t));
    realtime_queue->next_node = NULL;
    first_priority = (node_t*) malloc(sizeof(node_t));
    first_priority->next_node = NULL;
    second_priority = (node_t*) malloc(sizeof(node_t));
    second_priority->next_node = NULL;
    third_priority = (node_t*) malloc(sizeof(node_t));
    third_priority->next_node = NULL;
    
    // Checking if input file was specified
    if (argc != 2){
        printf("\nUsage: ./hostd <process list filename>\n\n");
        return EXIT_FAILURE;
    }
    else {
        strcpy(filename, argv[1]);
    }

    // Load the dispatchlist. The dispatchlist simply contains
    // all the processes read from the input file. The processes
    // are pushed into a queue using the push function
    load_dispatch(filename, dispatch_list);

    /*node_t *curr = dispatch_list;
    while (curr->next_node != NULL){
        printf("%d ", pop(dispatch_list)->mbytes);
    }
    printf("\n");
    while (curr->next_node != NULL){
        printf("%d ", pop(dispatch_list)->mbytes);
    }
    printf("\n");*/

    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}
