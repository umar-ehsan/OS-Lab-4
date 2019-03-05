/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef HOSTD_H_
#define HOSTD_H_
#include "utility.h"

// Include any relevant data structures here thay may be needed

// Include any relevant functions declarations here they must start with the 
// extern keyword such as in the following example:
extern void print_process(process proc);

// Add each process structure instance to the job dispatch list queue
// The job queue is filled according to the arrival time of each process
// The dispatch list is empty after the job queue is filled up.
extern void load_jobs(node_t *dispatch_list, node_t *job_queue);
#endif /* HOSTD_H_ */