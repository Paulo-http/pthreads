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

enum gender { woman, man };

struct person {
    enum gender type;
    struct person *next;
};

typedef struct person node;

bool is_empty(node *queue);
void _free(node *queue);
void start(node *queue);
node *alloc(enum gender type);
void append(node *queue, enum gender type);
void _remove(node *queue);
int count(node *queue);

#endif /* queue_h */
