#ifndef PDP_11_1__PDP11_H
#define PDP_11_1__PDP11_H


#define  pc reg[7] // 8?

typedef unsigned char byte; // 8 bit
typedef unsigned short int word;  // 16 bit
typedef word Adress;        // 64 Kb

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (do_func)(void);
} Command;

#endif //PDP_11_1__PDP11_H