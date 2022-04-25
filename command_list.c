#include "pdp11.h"
#include <stdio.h>
#include <stdlib.h>

extern word reg[];
extern byte mem[];

void do_mov() {
    pc += 2;
    printf("mov\n");
}

void do_halt() {
    printf("THE END!!!\n");
    exit(0);
}

void do_add() {}

void do_nothing() {}

Command cmd[] = {
        {0170000, 0010000, "mov", do_mov},
        {0170000, 0060000, "add", do_add},
        {, , "halt",do_halt},
        {, , "unknown", do_nothing}
};