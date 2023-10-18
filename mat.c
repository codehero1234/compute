#include "mat.h"

void mat_f32_alloc(struct mat_f32* m, int rows, int cols) {
    m->rows = rows;
    m->cols = cols;
    m->data = (float*)malloc(rows * cols * sizeof(float));
    if (m->data == NULL) {
        error_push(ERROR_CODE_OUT_OF_MEMORY, "Failed to allocate memory for matrix");
        error_panic();
    }
}

void mat_f32_free(struct mat_f32* m) {
    free(m->data);
}

void mat_f32_add(struct mat_f32* lhs, struct mat_f32* rhs, struct mat_f32* dst) {
    assert(lhs->rows == rhs->rows);
    assert(lhs->cols == rhs->cols);
    assert(lhs->rows == dst->rows);
    assert(lhs->cols == dst->cols);

    for (int i = 0; i < lhs->rows * lhs->cols; i++) {
        dst->data[i] = lhs->data[i] + rhs->data[i];
    }
}

void mat_f32_scale(struct mat_f32* src, float scale, struct mat_f32* dst) {
    assert(src->rows == dst->rows);
    assert(src->cols == dst->cols);

    for (int i = 0; i < src->rows * src->cols; i++) {
        dst->data[i] = src->data[i] * scale;
    }
}
void mat_f32_mul_naive(struct mat_f32* lhs, struct mat_f32* rhs, struct mat_f32* dst) {
    assert(lhs->cols == rhs->rows);
    assert(lhs->rows == dst->rows);
    assert(rhs->cols == dst->cols);

    for (int i = 0; i < lhs->rows; i++) {
        for (int j = 0; j < rhs->cols; j++) {
            float sum = 0.0f;
            for (int k = 0; k < lhs->cols; k++) {
                sum += lhs->data[i * lhs->cols + k] * rhs->data[k * rhs->cols + j];
            }
            dst->data[i * dst->cols + j] = sum;
        }
    }
}


void mat_f32_max_diff(struct mat_f32 *lhs, struct mat_f32 *rhs, float *max_diff) {
    assert(lhs->rows == rhs->rows);
    assert(lhs->cols == rhs->cols);

    *max_diff = 0.0f;
    for (int i = 0; i < lhs->rows * lhs->cols; i++) {
        float diff = fabs(lhs->data[i] - rhs->data[i]);
        if (diff > *max_diff) {
            *max_diff = diff;
        }
    }
}

void mat_f32_mul_mkn(struct mat_f32* lhs, struct mat_f32* rhs, struct mat_f32* dst) {
    assert(lhs->cols == rhs->rows);
    assert(lhs->rows == dst->rows);
    assert(rhs->cols == dst->cols);

    mat_f32_fill(dst, 0.0f);

    for (int i = 0; i < lhs->rows; i++) {
        for (int k = 0; k < lhs->cols; k++) {
            for (int j = 0; j < rhs->cols; j++) {
                dst->data[i * dst->cols + j] += lhs->data[i * lhs->cols + k] * rhs->data[k * rhs->cols + j];
            }
        }
    }
}

void mat_f32_fill(struct mat_f32 *m, float val) {
    for (int i = 0; i < m->rows * m->cols; i++) {
        m->data[i] = val;
    }
}

void mat_f32_rand_uniform(struct mat_f32 *m) {
    for (int i = 0; i < m->rows * m->cols; i++) {
        m->data[i] = (float)rand() / (float)RAND_MAX;
    }
}

void mat_f32_rand_normal(struct mat_f32 *m) {
    for (int i = 0; i < m->rows * m->cols; i++) {
        float x = (float)rand() / (float)RAND_MAX;
        m->data[i] = exp(x * x / -2.0f) / sqrt(2.0f * M_PI);
    }
}

void mat_f32_print(struct mat_f32 *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%f ", m->data[i * m->cols + j]);
        }
        printf("\n");
    }
}

