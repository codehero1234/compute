#ifndef __MAT_H__
#define __MAT_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "error.h"

struct mat_f32 {
    int rows;
    int cols;
    float *data;
};

void mat_f32_alloc(struct mat_f32* m, int rows, int cols);
void mat_f32_free(struct mat_f32* m);
void mat_f32_add(struct mat_f32* lhs, struct mat_f32* rhs, struct mat_f32* dst);
void mat_f32_fill(struct mat_f32 *m, float val);
void mat_f32_mul_naive(struct mat_f32* lhs, struct mat_f32* rhs, struct mat_f32* dst);
void mat_f32_mul_mkn(struct mat_f32* lhs, struct mat_f32* rhs, struct mat_f32* dst);
void mat_f32_scale(struct mat_f32* src, float scale, struct mat_f32* dst);
void mat_f32_print(struct mat_f32* m);
void mat_f32_max_diff(struct mat_f32 *lhs, struct mat_f32 *rhs, float *max_diff);

#endif // __MAT_H__