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
node_t *job_queue, *realtime_queue, *first_priority, *second_priority, *third_priority;
resources *global_res;
// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    char filename[256]; //filename from input argument

    // initializing all the queues
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
    

    // initializing the resources struct which contains the max
    // available resources
    global_res = (resources*) malloc(sizeof(resources));
    global_res->cds = 2;
    global_res->scanners = 1;
    global_res->printers = 2;
    global_res->modems = 1;
    for (int i = 0; i < MEMORY; i++){
        global_res->memory[i] = 0;
    }

    // Checking if input file was specified
    if (argc != 2){
        printf("\nUsage: ./hostd <process list filename>\n\n");
        return EXIT_FAILURE;
    }
    else {
        strcpy(filename, argv[1]);
    }

    // Load the dispatchlist into the job queue. The job queue simply contains
    // all the processes read from the input file in order of arrival time.
    // The processes are pushed into a queue using the push function
    load_dispatch(filename, job_queue);

    // Add each process structure instance to the job dispatch list queue
    // The job queue is filled according to the arrival time of each process
    // The dispatch list is empty after the job queue is filled up.
    load_jobs(dispatch_list, job_queue);

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}

// Add each process structure instance to the job dispatch list queue
// The job queue is filled according to the arrival time of each process
// The dispatch list is empty after the job queue is filled up.
void load_jobs(node_t *dispatch_list, node_t *job_queue){
    int time = 0;
    node_t *current_node;
    // add processes till the dispatch list is empty
    while(dispatch_list-> next_node != NULL){
        // get the process from the dispatch list. If the process arrival time
        // is less than or equal to current time, then add it to the job queue
        
        current_node = dispatch_list->next_node;
        while (current_node != NULL){
            if (current_node->proc.arrival_time <= time){

            }
            process *get_process = pop(dispatch_list);
            if (get_process->arrival_time <= time){
                push(job_queue, *get_process);
            }
            else {
                push(dispatch_list, *get_process);
            }
            current_node = current_node->next_node;
        }
        
        time++;
    }
}

