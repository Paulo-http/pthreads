//
//  problem.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "problem.h"

#define TOTAL_ELEMENTS 1000
pthread_mutex_t mutex;
pthread_t thr1, thr2;

countable c;
arguments args;
bool error = false;

void *generate_oxygens(void *args) {
    arguments *_args = args;
    node *oxygens = _args->oxygens;
    node *hydrogens = _args->hydrogens;
    
    while (true) {
        pthread_mutex_lock(&mutex);
        
        if (!is_empty(oxygens) && count(hydrogens) > 1) {
            _remove(oxygens);
            _remove(hydrogens);
            _remove(hydrogens);
            printf("-- new water element\n");
            printf("-- water elements: %d\n\n", ++c.h2o);
        } else if (++c.elements < TOTAL_ELEMENTS) {
            append(oxygens, oxygen);
            printf("- new element: oxygen\n");
        } else {
            --c.elements;
            printf("---- elements created ----\n\n");
            printf("- elements: %d\n", c.elements);
            printf("-- water elements: %d\n", c.h2o);
            int total_oxygens = count(oxygens);
            printf("oxygens not utilized: %d\n", total_oxygens);
            int total_hydrogens = count(hydrogens);
            printf("hydrogens not utilized: %d\n\n", total_hydrogens);
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        printf("- elements: %d\n\n", c.elements);
        
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
    return NULL;
}

void *generate_hydrogens(void *args) {
    arguments *_args = args;
    node *hydrogens = _args->hydrogens;
    
    while (true) {
        pthread_mutex_lock(&mutex);
        
        if (++c.elements < TOTAL_ELEMENTS) {
            append(hydrogens, hydrogen);
            printf("- new element: hydrogen\n");
        } else {
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        printf("- elements: %d\n\n", c.elements);
        
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
    return NULL;
}


void problem_production_of_water() {
    srand((unsigned)time(NULL));
    
    node *oxygens = (node*) malloc(sizeof(node));
    if (!oxygens) {
        exit(1);
    } else {
        start(oxygens);
        args.oxygens = oxygens;
    }
    
    node *hydrogens = (node*) malloc(sizeof(node));
    if (!hydrogens) {
        exit(1);
    } else {
        start(hydrogens);
        args.hydrogens = hydrogens;
    }
    
    error = pthread_mutex_init(&mutex, NULL);
    if (error) {
        exit(1);
    }

    error = pthread_create(&thr1, NULL, &generate_oxygens, (void*) &args);
    if (error) {
        exit(1);
    }

    error = pthread_create(&thr2, NULL, &generate_hydrogens, (void*) &args);
    if (error) {
        exit(1);
    }

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_mutex_destroy(&mutex);
}
