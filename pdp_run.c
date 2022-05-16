#include "pdp11.h"
#include <stdio.h>

extern word reg[];
extern byte mem[];
extern Command cmd[];
extern Arg ss, dd;
extern byte nn;


void run() {
    pc = 01000;
    while (1) {
        word w = w_read(pc);
        printf("%06o %06o: ", pc, w);
        pc += 2;
        for (int i = 0;; ++i) {
            Command command = cmd[i];
            if ((w & command.mask) == command.opcode) {
                if (command.parametr == HAS_SS_DD) {
                    ss = get_ssdd(w >> 6);
                    dd = get_ssdd(w);
                }
                if (command.parametr == HAS_NN_R) {
                    set_ri(w);
                    printf("r%o ", ri);
                    set_nn(w);
                    printf("%o ", pc - 2 * nn);
                }
                command.do_func();
                break;
            }
        }
    }
}