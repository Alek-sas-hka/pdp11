#include "pdp11.h"
#include <stdio.h>

extern word reg[];
extern byte mem[];
extern Command cmd[];

void run() {
    pc = 01000;
    while (1) {
        word w = w_read(pc);
        printf("%06o %06o: ", pc, w);
        for (int i = 0;; ++i) {
            Command command = cmd[i];
            if ((w & command.mask) == command.opcode) {
                command.do_func();
                break;
            }
        }
        pc += 2;
    }
}