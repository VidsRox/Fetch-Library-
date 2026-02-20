#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"

void print_message(void *arg){
    printf("Task: %s\n", (char*)arg);
}

int main(){
    ThreadPool laborers;
    thread_pool_init(&laborers, 3, 10);

    Task* task1 = (Task*)malloc(sizeof(Task));
    task1->function = print_message;
    task1->arg = "Task 1";
    thread_pool_submit(&laborers, task1);

    Task* task2 = (Task*)malloc(sizeof(Task));
    task2->function = print_message;
    task2->arg = "Task 2";
    thread_pool_submit(&laborers, task2);

    Task* task3 = (Task*)malloc(sizeof(Task));
    task3->function = print_message;
    task3->arg = "Task 3";
    thread_pool_submit(&laborers, task3);

    Task* task4 = (Task*)malloc(sizeof(Task));
    task4->function = print_message;
    task4->arg = "Task 4";
    thread_pool_submit(&laborers, task4);

    Task* task5 = (Task*)malloc(sizeof(Task));
    task5->function = print_message;
    task5->arg = "Task 5";
    thread_pool_submit(&laborers, task5);

    thread_pool_destroy(&laborers);
}