//
//  problem.h
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#ifndef problem_h
#define problem_h

#include "helper.h"

typedef struct arguments arguments;

struct restaurant {
    int visitors;
    int waiting;
    int eating;
    int meals;
};

typedef struct restaurant restaurant;

void problem_restaurant_tables(void);

#endif /* problem_h */
