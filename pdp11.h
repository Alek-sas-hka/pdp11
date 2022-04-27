#ifndef PDP_11_1__PDP11_H
#define PDP_11_1__PDP11_H

#define  pc reg[7] // 8?


typedef unsigned char byte;  //8 bit
typedef unsigned short int word;   //16 bit
typedef word Adress;         //64 kb

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void run();
void dump();
void print_reg();


typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
} Command;

typedef struct {
    word val;
    word adr;
} Arg;

Arg get_ssdd(word w);
#endif //PDP_11_1__PDP11_H