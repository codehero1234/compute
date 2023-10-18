#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ERROR_MESSAGE_LENGTH 1024
#define MAX_ERROR_STACK_DEPTH 32

enum error_code {
    ERROR_CODE_OUT_OF_MEMORY = 1,
    ERROR_CODE_ASSERTION_FAILED = 2,
};

struct error {
    enum error_code code;
    char message[MAX_ERROR_MESSAGE_LENGTH];
};

static struct error error_stack[MAX_ERROR_STACK_DEPTH];
static int error_stack_top = 0;

void error_push(enum error_code code, char* message);
void error_pop();
void error_print();
void error_clear();
void error_panic();
