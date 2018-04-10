//
//  problem.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "problem.h"

#define CROWDED_PARTY 1000
pthread_mutex_t mutex;
pthread_t thr1, thr2;

party p;
arguments args;
bool error = false;

void *generate_person(void *args) {
    arguments *_args = args;
    node *women = _args->women;
    node *men = _args->men;
    
    while (++p.guests < CROWDED_PARTY) {
        pthread_mutex_lock(&mutex);
        bool is_woman = rand() & 1;
        if (is_woman) {
            append(women, woman);
            printf("- new guest: woman\n");
        } else {
            append(men, man);
            printf("- new guest: man\n");
        }
        printf("- guests: %d\n\n", p.guests);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
    return NULL;
}

void *generate_couples(void *args) {
    arguments *_args = args;
    node *women = _args->women;
    node *men = _args->men;
    
    while (true) {
        if (!is_empty(women) && !is_empty(men)) {
            pthread_mutex_lock(&mutex);
            _remove(women);
            _remove(men);
            printf("-- new couple dancing\n");
            printf("-- couples: %d\n\n", ++p.couples);
            pthread_mutex_unlock(&mutex);
        } else if (p.guests == CROWDED_PARTY) {
            printf("---- crowded party ----\n\n");
            printf("guests: %d\n", p.guests);
            printf("couples: %d\n", p.couples);
            int total_women = count(women);
            printf("women without pair: %d\n", total_women);
            int total_men = count(men);
            printf("men without pair: %d\n\n", total_men);
            break;
        }
    }
    
    pthread_exit(NULL);
    return NULL;
}


void problem_pairing_of_couples() {
    srand((unsigned)time(NULL));
    
    node *women = (node*) malloc(sizeof(node));
    if (!women) {
        exit(1);
    } else {
        start(women);
        args.women = women;
    }
    
    node *men = (node*) malloc(sizeof(node));
    if (!men) {
        exit(1);
    } else {
        start(men);
        args.men = men;
    }
    
    error = pthread_mutex_init(&mutex, NULL);
    if (error) {
        exit(1);
    }

    error = pthread_create(&thr1, NULL, &generate_person, (void*) &args);
    if (error) {
        exit(1);
    }

    error = pthread_create(&thr2, NULL, &generate_couples, (void*) &args);
    if (error) {
        exit(1);
    }

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_mutex_destroy(&mutex);
}
