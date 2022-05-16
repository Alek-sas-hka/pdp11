#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "pdp11.h"

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

word reg[8];

Arg ss, dd;

byte nn;

byte bflag = 0;

void test_mem() {

    byte b0 = 0x0a;
    // пишем байт, читаем байт
    b_write(2, b0);
    byte bres = b_read(2);
    printf("%02hhx = %02hhx\n", b0, bres);
    assert(b0 == bres);

    // пишем 2 байта, читаем слово
    Adress a = 4;
    byte b1 = 0x0b;
    b0 = 0x0a;
    word w = 0x0b0a;
    b_write(a, b0);
    b_write(a + 1, b1);
    word wres = w_read(a);
    printf("bw/bw/wr \t %04hx=%02hhx%02hhx\n", wres, b1, b0);
    assert(w == wres);

    //пишем слово, читаем слово
    a = 6;
    w = 0x0c0d;
    w_write(a, w);
    wres = w_read(a);
    printf("ww/wr       \t %04hx=%04hx\n", w, wres);
    assert(w == wres);

    //пишем слово, читаем 2 байта
    a = 8;
    w = 0x0a0c;
    byte b9 = 0x0a;
    byte b8 = 0x0c;
    byte bres1;
    w_write(a, w);
    bres = b_read(a + 1);
    bres1 = b_read(a);
    printf("ww/br/br \t %04hx=%02hhx%02hhx\n", w, bres, bres1);
    assert(b9 == bres && b8 == bres1);
}


void load_file(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        perror(filename);
        exit(errno);
    }
    unsigned int block_adr, N, bt;
    while (fscanf(fin, "%x%x", &block_adr, &N) == 2 ) {
        printf("ard=%x N=%x\n", block_adr, N);
        for (unsigned int i = 0; i < N; i++) {

            fscanf(fin, "%x", &bt);
            b_write(block_adr + i, bt);
           // printf("%u %x : %x \n", i, block_adr + i, bt);
        }
    }
}

int main() {
    load_file("test");
    //dump();
    run();
    return 0;
}

void dump() {
    for (int i = 001000; i < 001012; i += 2) {
        word woord;
        woord = w_read(i);
        //printf("%06o : %06o\n", i, woord);
    }
}

word w_read(Adress a) {
    if (a < 8) {
        return reg[a];
    }
    else {
        word w = ((word) mem[a + 1]) << 8;
        // printf("w = %x\n", w);
        w = w | mem[a];
        return w;
    }
}
void w_write(Adress adr, word w) {
    if (adr < 8)   // if work with registr
        reg[adr] = (word) w;
    else {
        mem[adr] = (byte) w;
        mem[adr + 1] = (byte) (w >> 8);
    }
}
void b_write(Adress adr, byte b) {
    if (adr < 8) {
        if (b >> 7) {
            reg[adr] = b + 0xff00;
        } else {
            reg[adr] = b;
        }
        return;
    }
    mem[adr] = b;
}
byte b_read(Adress adr) {
    if (adr < 8) {
        return (byte) reg[adr];
    }
    return mem[adr];
}

void print_reg() {
    for (int i = 0; i < 8; ++i) {
        printf("reg[%d]: %o\n", i, reg[i]);
    }
}
