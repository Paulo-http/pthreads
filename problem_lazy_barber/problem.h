//
//  problem.h
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#ifndef problem_h
#define problem_h

#include "queue.h"

struct arguments {
    node *cutting;
    node *waiting;
};

typedef struct arguments arguments;

struct countable {
    int cuts;
    int costumers;
    int costumers_left;
};

typedef struct countable countable;

void problem_lazy_barber(void);

#endif /* problem_h */
