//
//  problem.c
//  pthreads
//
//  Created by Paulo Henrique Leite on 10/04/2018.
//  Copyright © 2018 com.hfleite. All rights reserved.
//

#include "problem.h"

static long num_steps = 100000;
double step;

void calculate_pi_without_threads() {
  int i;
  double x, pi, sum = 0.0;
  step = 1.0 / (double) num_steps;

  for (i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
  }

  pi = step * sum;
  printf("%f\n", pi);
}

// ---------------------------

pthread_mutex_t mutex;
pthread_t thr1, thr2;
arguments args;

double step;
double x;
double pi;
double sum;

void *calculate_pi(void *args) {
  arguments *_args = args;
  double step = _args->step;
  double x = _args->x;
  double pi = _args->pi;
  double sum = _args->sum;
  int i;
  step = 1.0 / (double) num_steps;

  for (i = 0; i < num_steps; i++) {
    x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
  }

  pi = step * sum;
  printf("%f\n", pi);
}

void calculate_pi_with_threads() {
  error = pthread_mutex_init(&mutex, NULL);
  if (error) {
      exit(1);
  }

  error = pthread_create(&thr1, NULL, &calculate_pi, (void*) &args);
  if (error) {
      exit(1);
  }

  error = pthread_create(&thr2, NULL, &calculate_pi, (void*) &args);
  if (error) {
      exit(1);
  }

  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);
  pthread_mutex_destroy(&mutex);
}
