#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "pdp11.h"


word reg[8];

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

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

    Adress block_adr;
    word N;
    while (fscanf(fin, "%hx", &block_adr) != EOF) {
        fscanf(fin, "%hx", &N);
        for (int i = 0; i < N; ++i) {
            byte bt;
            fscanf(fin, "%hhx", &bt);
            b_write(block_adr + i, bt);
        }
    }
}

int main()
{
    load_file("test");
}

word w_read(Adress a) {
    word w = ((word)mem[a + 1]) << 8;
    //printf("w = %x\n", w);
    w = w | mem[a];
    return w;
}
void w_write(Adress adr, word w) {
    mem[adr] = (byte) w;
    mem[adr + 1] = (byte) (w >> 8);
}
void b_write(Adress adr, byte b) {
    mem[adr] = b;
}
byte b_read(Adress adr) {
    return mem[adr];
}

