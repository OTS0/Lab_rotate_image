#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


_Noreturn void util_err(const char* msg) {
    fprintf(stderr, "%s", msg);
    exit(1);
}

void util_usage(int argc) {
    if (argc != 3) {
        if (argc < 3) err("Not enough arguments \n");
        if (argc > 3) err("Too many arguments \n");
    }
    fprintf("Invalid input \n");
}
