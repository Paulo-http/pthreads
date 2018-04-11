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
    node *oxygens;
    node *hydrogens;
};

typedef struct arguments arguments;

struct countable {
    int h2o;
    int elements;
    int oxygens;
    int hydrogens;
};

typedef struct countable countable;

void problem_production_of_water(void);

#endif /* problem_h */
