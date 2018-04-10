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
    node *women;
    node *men;
};

typedef struct arguments arguments;

struct party {
    int guests;
    int couples;
};

typedef struct party party;

void problem_pairing_of_couples(void);

#endif /* problem_h */
