#include "pdp11.h"
#include <stdio.h>
#include <stdlib.h>

extern word reg[];
extern byte mem[];

void do_mov() {
    printf("mov \n");
}

void do_halt() {
    printf("THE END!!! \n");
    exit(0);
}

void do_add() {
    printf("add \n");
}

void do_nothing() {
    printf("nothing \n");
}

Command cmd[] = {
        {0170000, 0010000, "mov",     do_mov},
        {0170000, 0060000, "add",     do_add},
        {0177777, 0000000, "halt",    do_halt},
        {0000000, 0000000, "unknown", do_nothing}
};

Arg get_ssdd(word w) {
    Arg res;
    int n = w & 7; // dd
    int mode = (w >> 3) & 7; // ss
    switch (mode) {
        case 0:    // Rn
            res.adr = n;
            res.val = reg[n];
            printf("R%o ", n);
            break;
    }
    return res;
}