//
//  queue.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "queue.h"

bool is_empty(node *people) {
    return (people->next == NULL) ? true : false;
}

void _free(node *people) {
    if (is_empty(people)) {
        return;
    }
    
    node *person = people->next;
    node *next_person;
    
    while (person != NULL) {
        next_person = person->next;
        free(person);
        person = next_person;
    }
}

void start(node *people) {
    people->next = NULL;
}

node *alloc(enum gender type) {
    node *person = (node *) malloc(sizeof(node));
    person->type = type;
    return person;
}

void append(node *people, enum gender type) {
    node *person = alloc(type);
    person->next = NULL;
    
    if (is_empty(people)) {
        people->next = person;
    } else {
        node *next_person = people->next;
        while (next_person->next != NULL) {
            next_person = next_person->next;
        }
        
        next_person->next = person;
    }
}

void _remove(node *people) {
    if (is_empty(people)) {
        return;
    } else {
        node *next_person = people->next;
        people->next = next_person->next;
        if(next_person != NULL) {
            free(next_person);
        }
    }
}

int count(node *people) {
    int count = 0;
    
    if (is_empty(people)) {
        return count;
    }
    
    node *next_person = people->next;
    
    while (next_person != NULL) {
        next_person = next_person->next;
        ++count;
    }
    
    return count;
}
