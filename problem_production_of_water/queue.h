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

enum element { oxygen, hydrogen };

struct atom {
    enum element type;
    struct atom *next;
};

typedef struct atom node;

bool is_empty(node *queue);
void _free(node *queue);
void start(node *queue);
node *alloc(enum element type);
void append(node *queue, enum element type);
void _remove(node *queue);
int count(node *queue);

#endif /* queue_h */
