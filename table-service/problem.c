//
//  problem.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "problem.h"

#define TABLES 50
pthread_mutex_t mutex;
pthread_t thr1, thr2;

restaurant r;
bool error = false;

void thr1_block(int visitors) {
    pthread_mutex_lock(&mutex);
    
    int empty_tables = TABLES-r.eating;
    int waiting = visitors-empty_tables;
    
    if (visitors > empty_tables) {
        r.waiting += waiting;
        r.eating += empty_tables;
        r.meals -= empty_tables;
    } else {
        r.eating += visitors;
        r.meals -= visitors;
        if (r.waiting > 0) {
            r.waiting-=visitors;
        }
    }
    
    r.visitors += visitors;
    
    pthread_mutex_unlock(&mutex);
}

void *new_visitor(void *args) {
    while (r.meals > 0) {
        int visitors = 1 + rand() % 20;
        
        while (visitors > r.meals) {
            visitors = 1 + rand() % r.meals;
        }
        
        printf("- new visitors: %d\n\n", visitors);

        thr1_block(visitors);
        
        printf("- empty tables: %d\n\n", TABLES-r.eating);
        printf("- people eating: %d\n\n", r.eating);
        printf("- people waiting: %d\n\n", r.waiting);
        printf("- meals to serve: %d\n\n", r.meals);
    }
    
    pthread_exit(NULL);
    return NULL;
}

void thr2_block() {
    pthread_mutex_lock(&mutex);
    if (r.eating > 0) {
        r.eating--;
        printf("- meal finished\n\n");
    }
    pthread_mutex_unlock(&mutex);
}

void *meal_finished(void *args) {
    while (true) {
        if (r.meals == 0 && r.eating == 0) {
            printf("- visitors: %d\n\n", r.visitors);
            break;
        } else {
            bool finished = rand() & 1;
            if (finished) {
                thr2_block();
            }
        }
    }
    
    pthread_exit(NULL);
    return NULL;
}


void problem_restaurant_tables() {
    srand((unsigned)time(NULL));
    
    r.visitors = 0;
    r.waiting = 0;
    r.eating = 0;
    r.meals = 1000;
    
    error = pthread_mutex_init(&mutex, NULL);
    if (error) {
        exit(1);
    }

    error = pthread_create(&thr1, NULL, &new_visitor, NULL);
    if (error) {
        exit(1);
    }

    error = pthread_create(&thr2, NULL, &meal_finished, NULL);
    if (error) {
        exit(1);
    }

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_mutex_destroy(&mutex);
}
