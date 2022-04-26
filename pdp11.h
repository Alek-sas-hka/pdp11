#ifndef PDP_11_1__PDP11_H
#define PDP_11_1__PDP11_H


#define  pc reg[7] // 8?


typedef unsigned char byte;  //8 bit
typedef unsigned int word;   //16 bit
typedef word Adress;         //16 bit

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
} Command;

#endif //PDP_11_1__PDP11_H