#include "pdp11.h"
#include <stdio.h>
#include <stdlib.h>

extern word reg[];
extern byte mem[];
extern Arg ss, dd;
extern byte nn;
extern byte bflag;
word ri, w;

void do_clr() {
    if (bflag) {
        printf("clrb \n");
        b_write(dd.adr, 0);
        return;
    }
    printf("clr \n");
    w_write(dd.adr, 0);
}

void do_mov() {
    if (bflag) {
        printf("movb \n");
        b_write(dd.adr, ss.val);
        return;
    }
    printf("mov \n");
    w_write(dd.adr, ss.val);
}

void do_halt() {
    printf("halt\n");
    print_reg();
    exit(0);
}

void do_add() {
    printf("add \n");
    reg[dd.adr] += ss.val;
}

void do_nothing() {
    printf("nothing \n");
}

void set_nn(word w) {
    nn = w & 077;
}

void set_ri(word w) {
    ri = (w >> 6) & 07;
}

void do_sob() {
    printf("sob \n");
    reg[ri] -= 1;
    if (reg[ri] != 0 ) {
        pc -= 2 * nn;
    }
}



Command cmd[] = {
        {0070000, 0010000, "mov",     do_mov, HAS_SS_DD | HAS_B},
        {0170000, 0060000, "add",     do_add, HAS_SS_DD},
        {0177777, 0000000, "halt",    do_halt, 0},
        {0177000, 0077000, "sob",    do_sob, HAS_NN_R},
        {0077700, 0005000, "clr", do_clr, HAS_DD | HAS_B},
        {0000000, 0000000, "unknown", do_nothing, 0}
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
        case 1:    // (Rn)
            res.adr = reg[n];
            res.val = w_read(res.adr);
            printf("(R%o) ", n);
            break;
        case 2:
            res.adr = reg[n];
            res.val = w_read(res.adr);
            if (bflag && n != 7) {
                reg[n] += 1;
            } else {
                reg[n] += 2;
            }
            if (n == 7) {      //  #nn
                printf("#%o ", res.val);
                break;
            } else {     //  (Rn)+
                printf("(R%o)+ ", n);
                break;
            }
        case 3:
            res.adr = reg[n];
            res.adr = mem[res.adr];
            res.val = mem[res.adr];
            reg[n] += 2;
            if (n == 7) {  // @#nn
                printf("@#%o ", res.adr);
                break;
            } else {   // @(Rn)+
                printf("@(R%o)+ ", n);
                break;
            }
        case 4:  // -(Rn)
            res.adr = reg[n] - 2;
            res.val = mem[res.adr];
            printf("-(R%o) ", n);
        default:
            printf("mode %o not implemented", n);
            exit(1);
    }
    return res;
}