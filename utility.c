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

int alloc_mem(resources *res, int size, int priority){
    int max_memory = 0;
    int memory_count = size;
    int memory_index = 0;
    if (priority == 0){
        max_memory = 1024;
        memory_index = 960;
    }
    else {
        max_memory = 960;
    }
    for (; memory_index < max_memory && memory_count > 0; memory_index++){
        if (res->memory[memory_index] == 0){
            res->memory[memory_index] == 1;
            memory_count--;
        }
    }
    return memory_index - size;
}

void free_mem(resources *res, int index, int size){
    int memory_index = index;
    while (memory_index < index + size){
        res->memory[memory_index] = 0;
        memory_index++;
    }
    res->memoryleft += size;
}


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

    // add processes to the priority queues as long as resources are available
    while (current_node->proc.arrival_time == time){
        if (resource_available(&(current_node->proc), available_res)){
            process *proc = pop(job_queue);
            available_res->cds = available_res->cds - proc->cds;
            available_res->printers = available_res->printers - proc->printers;
            available_res->scanners = available_res->scanners - proc->scanners;
            available_res->modems = available_res->modems - proc->modems;
            proc->memory_index = alloc_mem(available_res, proc->mbytes, proc->priority);
            switch (proc->priority){
                case 0:
                    push(realtime_queue, *proc);
                    break;
                case 1:
                    push(first_priority, *proc);
                    break;
                case 2:
                    push(second_priority, *proc);
                    break;
                case 3:
                    push(third_priority, *proc);
                    break;
            }
        }
        else {
            current_node->proc.arrival_time++;
        }
        current_node = current_node->previous_node;
        
    }
}

// Returns true if process resources are less than equal to available resources
// false otherwise
bool resource_available(process *proc, resources *available_res){
    int cds = available_res->cds - proc->cds;
    int modems = available_res->modems - proc->modems;
    int printers = available_res->printers - proc->printers;
    int scanners = available_res->scanners - proc->scanners;
    int memory = 0;
    if (proc->priority == 0){
        memory = available_res->realtime_memory - proc->mbytes;
    } 
    else {
        memory = available_res->user_memory - proc->mbytes;
    }
    if (cds >=0 && modems >=0 && printers >=0 && scanners >=0 && memory >= 0){
        return true;
    }
    else {
        return false;
    }
}


// Returns true if all queues are empty, false otherwise
bool terminate_dispatcher(node_t *job_queue, node_t *realtime_queue, node_t *first_priority, node_t *second_priority, node_t *third_priority){
    if (job_queue->next_node == NULL && realtime_queue->next_node == NULL && first_priority->next_node == NULL && second_priority->next_node == NULL && third_priority->next_node == NULL){
        return true;
    }
    else {
        return false;
    }
}

// Run dispatcher
extern void run_jobs(node_t *realtime_queue, node_t *first_priority, node_t *second_priority, node_t *third_priority){

}