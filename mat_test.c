#include "mat.h"



void test_matmul_small() {
    const int N = 1000;
    struct mat_f32 a, b, c, d, e;
    mat_f32_alloc(&a, 3, 2);
    mat_f32_alloc(&b, 2, 3);
    mat_f32_alloc(&c, 3, 3);
    mat_f32_alloc(&d, 3, 3);
    mat_f32_alloc(&e, 3, 3);


    float a_buf[] = {
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f,
    };
    memcpy(a.data, a_buf, sizeof(a_buf));
    float b_buf[] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
    };
    memcpy(b.data, b_buf, sizeof(b_buf));

    struct timeval start, end;
    float t_naive_ms = 0.0f, t_mkn_ms = 0.0f;


    for (int i = 0; i < N; ++i) {
        gettimeofday(&start, NULL);
        mat_f32_mul_naive(&a, &b, &c);
        gettimeofday(&end, NULL);
        t_naive_ms += (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;
    }
    t_naive_ms /= N;

    for (int i = 0; i < N; ++i) {
        gettimeofday(&start, NULL);
        mat_f32_mul_mkn(&a, &b, &d);
        gettimeofday(&end, NULL);
        t_mkn_ms += (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;
    }
    t_mkn_ms /= N;

    float e_buf[] = {
        9.0f, 12.0f, 15.0f,
        19.0f, 26.0f, 33.0f,
        29.0f, 40.0f, 51.0f,
    };
    memcpy(e.data, e_buf, sizeof(e_buf));

    float eps;

    mat_f32_max_diff(&c, &e, &eps);
    fprintf(stderr, "mat_f32_mul: max diff = %f\n", eps);
    fprintf(stderr, "mat_f32_mul: naive time = %f ms\n", t_naive_ms);

    mat_f32_max_diff(&d, &e, &eps);
    fprintf(stderr, "mat_f32_mul_mkn: max diff = %f\n", eps);
    fprintf(stderr, "mat_f32_mul_mkn: mkn time = %f ms\n", t_mkn_ms);

    mat_f32_print(&d);

}

void test_matmul_large() {
    struct mat_f32 a, b, c, d;
    const int m = 2048;
    const int k = 1024;
    const int n = 2048;
    fprintf(stderr, "Start test_matmul_large with setting: ");
    fprintf(stderr, "m=%d, k=%d, n=%d\n", m, k, n);

    a.data = NULL;
    b.data = NULL;
    c.data = NULL;
    d.data = NULL;

    mat_f32_alloc(&a, m, k);
    mat_f32_alloc(&b, k, n);
    mat_f32_alloc(&c, m, n);
    mat_f32_alloc(&d, m, n);

    struct timeval start, end;
    float t_naive_ms = 0.0f, t_mnk_ms = 0.0f;
 
    fprintf(stderr, "Testing mat_f32_mul_naive...");
    gettimeofday(&start, NULL);
    mat_f32_mul_naive(&a, &b, &c);
    gettimeofday(&end, NULL);
    t_naive_ms = (float)(end.tv_sec - start.tv_sec) * 1000 + (float)(end.tv_usec - start.tv_usec) / 1000;
    fprintf(stderr, "Done!\n");
    
    fprintf(stderr, "Testing mat_f32_mul_mkn...");
    gettimeofday(&start, NULL);
    mat_f32_mul_mkn(&a, &b, &d);
    gettimeofday(&end, NULL);
    t_mnk_ms = (float)(end.tv_sec - start.tv_sec) * 1000 + (float)(end.tv_usec - start.tv_usec) / 1000;
    fprintf(stderr, "Done!\n");

    fprintf(stderr, "mat_f32_mul_naive: %fms\n", t_naive_ms);
    fprintf(stderr, "mat_f32_mul_mkn: %fms\n", t_mnk_ms);
}


int main() {
    test_matmul_large();
    return 0;
}



