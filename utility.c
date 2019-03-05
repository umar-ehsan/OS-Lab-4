/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utility.h"

#define BUFFER_LEN 100

// Define your utility functions here, you will likely need to add more...

// int alloc_mem(resources res, int size)
// {
//      ...
// }

// free_mem(resources res, int index, int size)
// {
//      ...
// }


// Loads the processes listed in the input file into the dispatch
// list queue
void load_dispatch(char *dispatch_file, node_t *queue)
{
    process input_process;
    char input_buffer[BUFFER_LEN], *split_input;
    FILE *file = fopen(dispatch_file, "r");
    
    // Checking if input file exits
    if (file == NULL){
        printf("Error, file does not exit.\n");
    }
    else {
        // start processing the file line by line. First the
        // split_input gets each line from the strtok function,
        // then the string is further split according to commas
        // and resulting strings converted to ints and copied to the
        // process values as defined in queue.h
        while(fgets(input_buffer, BUFFER_LEN, file) != NULL){
            split_input = strtok(input_buffer, "\n");
            split_input = strtok(split_input, ",");
            input_process.arrival_time = atoi(split_input);
            split_input = strtok(NULL, ",");
            input_process.priority = atoi(split_input);
            split_input = strtok(NULL, ",");
            input_process.processor_time = atoi(split_input);
            split_input = strtok(NULL, ",");
            input_process.mbytes = atoi(split_input);
            split_input = strtok(NULL, ",");
            input_process.printers = atoi(split_input);
            split_input = strtok(NULL, ",");
            input_process.scanners = atoi(split_input);
            split_input = strtok(NULL, ",");
            input_process.modems = atoi(split_input);
            split_input = strtok(NULL, ",");
            input_process.cds = atoi(split_input);
            input_process.memory_index = -1;
            // push process to dispatch queue
            push(queue, input_process);
        }
    }
    fclose(file);
    
}

// Add each process structure instance to the job dispatch list queue
// The job queue is filled according to the arrival time of each process
// The dispatch list is empty after the job queue is filled up.
void load_jobs(int time, node_t *job_queue, node_t *realtime_queue, node_t *first_priority, node_t *second_priority, node_t *third_priority, resources *available_res){
    
    node_t *current_node = job_queue;
    // get to the first item in the job queue
    while(current_node-> next_node != NULL){
        current_node = current_node->next_node;
    }

    // add processes to the priority queues as long as resources are available and arrival time is less than equal
    // to dispatcher time
    while (current_node->proc.arrival_time <= time && resource_available(&(current_node->proc), available_res)){
        process *proc = pop(job_queue);
        current_node 
    }
}

