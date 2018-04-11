//
//  queue.h
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include "helper.h"

struct costumer {
    int password;
    struct costumer *next;
};

typedef struct costumer node;

bool is_empty(node *queue);
void _free(node *queue);
void start(node *queue);
node *alloc(int password);
void append(node *queue, int password);
void _remove(node *queue);
int count(node *queue);

#endif /* queue_h */
