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
    
}
