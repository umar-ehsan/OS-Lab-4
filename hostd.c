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
#define NUM_RESOURCE 9
#define MAX_PROCESS 1000

// Put global environment variables here
node_t *job_queue, *realtime_queue, *first_priority, *second_priority, *third_priority;
resources *available_res;
int time;
bool terminate = false;
int dispatch_list[MAX_PROCESS][NUM_RESOURCE] = {0};
// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    char filename[256]; //filename from input argument
    int num_processes = 0;
    time = 0;

    // initializing all the queues
    job_queue = (node_t*) malloc(sizeof(node_t));
    job_queue->next_node = NULL;
    //job_queue->previous_node = NULL;
    realtime_queue = (node_t*) malloc(sizeof(node_t));
    realtime_queue->next_node = NULL;
    //realtime_queue->previous_node = NULL;
    first_priority = (node_t*) malloc(sizeof(node_t));
    first_priority->next_node = NULL;
    //first_priority->previous_node = NULL;
    second_priority = (node_t*) malloc(sizeof(node_t));
    second_priority->next_node = NULL;
    //second_priority->previous_node = NULL;
    third_priority = (node_t*) malloc(sizeof(node_t));
    third_priority->next_node = NULL;
    //third_priority->previous_node = NULL;
    

    // initializing the resources struct which contains the max
    // available resources
    available_res = (resources*) malloc(sizeof(resources));
    available_res->cds = 2;
    available_res->scanners = 1;
    available_res->printers = 2;
    available_res->modems = 1;
    available_res->memoryleft = MEMORY - 64;
    available_res->realtime_mem = 64;
    for (int i = 0; i < MEMORY; i++){
        available_res->memory[i] = 0;
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
    // The processes are read into a array
    num_processes = load_dispatch(filename, dispatch_list);

    // if no processes then terminate, else set terminate to false and load all processes
    if (num_processes > 0){
        terminate = false;
    }
    else {
        terminate = true;
    }
    // Start dispatcher
    while(!terminate){
    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues
        load_jobs(time, num_processes, dispatch_list, job_queue, realtime_queue, first_priority, second_priority, third_priority, available_res);
    // Allocate the resources for each process before it's executed
        process *proc;
        if (realtime_queue->next_node != NULL){
            proc = pop(realtime_queue);
            alloc_mem(available_res, proc->mbytes, proc->priority);
        }
        else if (first_priority->next_node != NULL) {
            proc = pop(first_priority);
            alloc_mem(available_res, proc->mbytes, proc->priority);
        }
        else if (second_priority->next_node != NULL) {
            proc = pop(second_priority);
            alloc_mem(available_res, proc->mbytes, proc->priority);
        }
        else if (third_priority->next_node != NULL) {
            proc = pop(third_priority);
            alloc_mem(available_res, proc->mbytes, proc->priority);
        }
    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
        time++;
        terminate = terminate_dispatcher(job_queue, realtime_queue, first_priority, second_priority, third_priority);
    }
    return EXIT_SUCCESS;
}