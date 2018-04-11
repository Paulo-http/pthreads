//
//  queue.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "queue.h"

bool is_empty(node *costumers) {
    return (costumers->next == NULL) ? true : false;
}

void _free(node *costumers) {
    if (is_empty(costumers)) {
        return;
    }
    
    node *costumer = costumers->next;
    node *next_costumer;
    
    while (costumer != NULL) {
        next_costumer = costumer->next;
        free(costumer);
        costumer = next_costumer;
    }
}

void start(node *costumers) {
    costumers->next = NULL;
}

node *alloc(int password) {
    node *costumer = (node *) malloc(sizeof(node));
    costumer->password = password;
    return costumer;
}

void append(node *costumers, int password) {
    node *costumer = alloc(password);
    costumer->next = NULL;
    
    if (is_empty(costumers)) {
        costumers->next = costumer;
    } else {
        node *next_costumer = costumers->next;
        while (next_costumer->next != NULL) {
            next_costumer = next_costumer->next;
        }
        
        next_costumer->next = costumer;
    }
}

void _remove(node *costumers) {
    if (is_empty(costumers)) {
        return;
    } else {
        node *next_costumer = costumers->next;
        costumers->next = next_costumer->next;
        if(next_costumer != NULL) {
            free(next_costumer);
        }
    }
}

int count(node *costumers) {
    int count = 0;
    
    if (is_empty(costumers)) {
        return count;
    }
    
    node *next_costumer = costumers->next;
    
    while (next_costumer != NULL) {
        next_costumer = next_costumer->next;
        ++count;
    }
    
    return count;
}
