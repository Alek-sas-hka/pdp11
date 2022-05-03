#ifndef PDP_11_1__PDP11_H
#define PDP_11_1__PDP11_H

#define  pc reg[7] // 8?

#define HAS_SS 1
#define HAS_DD 2
#define HAS_SS_DD (HAS_SS | HAS_DD)
#define HAS_NN 4
#define HAS_R (4 << 1)
#define HAS_NN_R (HAS_NN | HAS_R)

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
void set_ri(word w);
void set_nn(word w);
extern word ri;


typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
    byte parametr;
} Command;

typedef struct {
    word val;
    word adr;
} Arg;

Arg get_ssdd(word w);
#endif //PDP_11_1__PDP11_H