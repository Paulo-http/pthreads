//
//  problem.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "problem.h"

#define TOTAL_COSTUMERS 1000
pthread_mutex_t mutex;
pthread_t thr1, thr2;

countable c;
arguments args;
bool error = false;

void *costumers(void *args) {
    arguments *_args = args;
    node *waiting = _args->waiting;
    
    while (++c.costumers <= TOTAL_COSTUMERS) {
        pthread_mutex_lock(&mutex);
        
        if  (count(waiting) == 3) {
            printf("- costumer %d left\n", c.costumers);
            ++c.costumers_left;
        } else {
            printf("- new costumer: %d\n", c.costumers);
            append(waiting, c.costumers);
        }
        
        printf("- costumers waiting: %d\n\n", count(waiting));
        
        pthread_mutex_unlock(&mutex);
    }
    
    --c.costumers;
    
    pthread_exit(NULL);
    return NULL;
}

void *barber(void *args) {
    arguments *_args = args;
    node *cutting = _args->cutting;
    node *waiting = _args->waiting;
    
    while (true) {
        pthread_mutex_lock(&mutex);
        
        if (!is_empty(cutting)) {
            printf("-- costumer [%d] finished\n\n", cutting->next->password);
            _remove(cutting);
            ++c.cuts;
        } else if (is_empty(waiting) && c.costumers >= TOTAL_COSTUMERS) {
            printf("---- day finished ----\n\n");
            printf("- costumers: %d\n", c.costumers);
            printf("- cuts: %d\n", c.cuts);
            printf("- costumers left: %d\n\n", c.costumers_left);
            break;
        } else if (!is_empty(waiting)) {
            printf("-- costumer [%d] cutting\n\n", waiting->next->password);
            append(cutting, waiting->next->password);
            _remove(waiting);
        }
        
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
    return NULL;
}

void problem_lazy_barber() {
    srand((unsigned)time(NULL));
    
    node *cutting = (node*) malloc(sizeof(node));
    if (!cutting) {
        exit(1);
    } else {
        start(cutting);
        args.cutting = cutting;
    }
    
    node *waiting = (node*) malloc(sizeof(node));
    if (!waiting) {
        exit(1);
    } else {
        start(waiting);
        args.waiting = waiting;
    }
    
    error = pthread_mutex_init(&mutex, NULL);
    if (error) {
        exit(1);
    }
    
    error = pthread_create(&thr1, NULL, &costumers, (void*) &args);
    if (error) {
        exit(1);
    }
    
    error = pthread_create(&thr2, NULL, &barber, (void*) &args);
    if (error) {
        exit(1);
    }
    
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_mutex_destroy(&mutex);
}
