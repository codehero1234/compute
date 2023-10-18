#include "error.h"


void error_push(enum error_code code, char* message) {
    struct error e = {code};
    strncpy(e.message, message, MAX_ERROR_MESSAGE_LENGTH);
    error_stack[error_stack_top++] = e;
}

void error_pop() {
    error_stack_top--;
}

void error_print() {
    for (int i = 0; i < error_stack_top; i++) {
        printf("Error %d: %s\n", error_stack[i].code, error_stack[i].message);
    }
}

void error_clear() {
    error_stack_top = 0;
}

void error_panic() {
    error_print();
    exit(1);
}