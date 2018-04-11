//
//  queue.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "queue.h"

bool is_empty(node *atoms) {
    return (atoms->next == NULL) ? true : false;
}

void _free(node *atoms) {
    if (is_empty(atoms)) {
        return;
    }
    
    node *atom = atoms->next;
    node *next_atom;
    
    while (atom != NULL) {
        next_atom = atom->next;
        free(atom);
        atom = next_atom;
    }
}

void start(node *atoms) {
    atoms->next = NULL;
}

node *alloc(enum element type) {
    node *atom = (node *) malloc(sizeof(node));
    atom->type = type;
    return atom;
}

void append(node *atoms, enum element type) {
    node *atom = alloc(type);
    atom->next = NULL;
    
    if (is_empty(atoms)) {
        atoms->next = atom;
    } else {
        node *next_atom = atoms->next;
        while (next_atom->next != NULL) {
            next_atom = next_atom->next;
        }
        
        next_atom->next = atom;
    }
}

void _remove(node *atoms) {
    if (is_empty(atoms)) {
        return;
    } else {
        node *next_atom = atoms->next;
        atoms->next = next_atom->next;
        if(next_atom != NULL) {
            free(next_atom);
        }
    }
}

int count(node *atoms) {
    int count = 0;
    
    if (is_empty(atoms)) {
        return count;
    }
    
    node *next_atom = atoms->next;
    
    while (next_atom != NULL) {
        next_atom = next_atom->next;
        ++count;
    }
    
    return count;
}
