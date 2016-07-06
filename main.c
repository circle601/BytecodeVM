#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef	int int16;

#define HI_UINT16(a) ((((unsigned int)a) >> 8) & 0xFF)
#define LO_UINT16(a) (((unsigned int)a) & 0xFF)

#define a_UINT16(a) (((unsigned int)a) & 0xFF)
#define b_UINT16(a) ((((unsigned int)a) >> 8) & 0xFF)
#define c_UINT16(a) ((((unsigned int)a) >> 16) & 0xFF)
#define d_UINT16(a) ((((unsigned int)a) >> 24) & 0xFF)

#define ExDone 0xC3 // returns from the bytecode


#define BcNop 0x00
#define BcPush 0x01
#define BcPop 0x02
#define BcLoad 0x03
#define BcStore 0x04
#define BcAdd 0x05
#define BcSub 0x06
#define BcMul 0x07
#define BcDiv 0x08
#define BcCall 0x09
#define BcRet 0x0a
#define BcJmp 0x0b
#define BcCmp 0x0c
#define BcJeq 0x0d
#define BcJne 0x0e
#define BcJgt 0x0f
#define BcJlt 0x10
#define BcJle 0x11
#define BcJge 0x12
#define BcExit 0x13

#define BcInc 0x14
void PrintArray(char* ptr)
{
    int i =0;
    for(i=0;i<10;i++){

    printf("%02X ", (char)ptr[i]);
     printf("'%c'\n", (char)ptr[i]);
    }


}
int main()
{
 //int instructions[] = {  1,2, 1,10,  8,0, 1,1,  1,1,  0x4,0  ,0x13,0};
 int instructions[] = {
                          BcPush,1,
                         BcPush,0,
                          0x15,0,
                         BcPush,1,
                         BcPop,0,
                         BcPop,0,
                         BcExit,0};

    char Data[] = "Hello World!";
//

    char* CS = malloc(257 * 256);
    char* DS = malloc(257 * 256);

if (CS==NULL) exit (1);
if (DS==NULL) exit (1);
   // int instructions[] = { 1,0,  1,9,  0x0B,0,  1,2, 1,10,  8,0, 1,1,  1,1,  0x4,0  ,0x13,0};
     //int instructions[] = {1,2, 1,0,1,0,0x0B,1,10,8,0,1,1,1,1,0x4,0};
    int length = 20;
    int Datalength = 20;
    char* InstructionLookupTable[256];


    char* OutputBuffer =&DS[253 << 8];
    char* SystemCallSpace =&CS[254 << 8];
    char** SystemCallTable = (char**)&CS[255 << 8];
    char* OutputPointer = OutputBuffer;

    char* Text = OutputBuffer;
    char** TextPointer = (char**)&OutputBuffer[0];
    *TextPointer = &OutputBuffer[4];
    int codeIndex = 0;


SystemCallTable[0] = &SystemCallSpace[0];
SystemCallTable[1] = &SystemCallSpace[1];
SystemCallTable[2] = &SystemCallSpace[2];
const char bios[] = {ExDone,0x3C,0x05,0x66,0x6A,0x66,0x5A,ExDone};
//const char bios[] = {ExDone,0xFC,0x31,0xC0,0x66,0x59,0x66,0x58,0x66,0x5B,0x88,0xDC,0x66,0x8D,0xB0,a_UINT16(DS),b_UINT16(DS),c_UINT16(DS),d_UINT16(DS),0x66,0x8B,0x3D,a_UINT16(TextPointer),b_UINT16(TextPointer),c_UINT16(TextPointer),d_UINT16(TextPointer),0xF3,0xA4,0x66,0x89,0x3D,a_UINT16(TextPointer),b_UINT16(TextPointer),c_UINT16(TextPointer),d_UINT16(TextPointer),0xC3};
memcpy( SystemCallSpace,bios, 40 );


memcpy( DS,Data, Datalength );
int instruction = 0;
int data = 0;
int i =0;
int ins = 0;


while(i<length){
    InstructionLookupTable[i] = &CS[codeIndex];
    instruction = instructions[i++];
    InstructionLookupTable[i] = &CS[codeIndex];
    data = instructions[i++];
    switch(instruction)
    {
    case(0): //nop tested
        break;
    case(1): //push tested
       CS[codeIndex++]  = 0x66;
       CS[codeIndex++]  = 0x6A;
       CS[codeIndex++]  = (char)data;
        break;
    case(2): //pop tested
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5A;
         break;
    case(3): //Load
        CS[codeIndex++]  = 0x31;
        CS[codeIndex++]  = 0xC0;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xB0;
        CS[codeIndex++]  = a_UINT16(DS);
        CS[codeIndex++]  = b_UINT16(DS);
        CS[codeIndex++]  = c_UINT16(DS);
        CS[codeIndex++]  = d_UINT16(DS);
         break;
    case(4): //Store tested
        CS[codeIndex++]  = 0x31;
        CS[codeIndex++]  = 0xC0;

        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x8F;
        CS[codeIndex++]  = 0x80;
        CS[codeIndex++]  = a_UINT16(DS);
        CS[codeIndex++]  = b_UINT16(DS);
        CS[codeIndex++]  = c_UINT16(DS);
        CS[codeIndex++]  = d_UINT16(DS);
         break;
    case(5): //Add tested
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x01;
        CS[codeIndex++]  = 0xD8;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x50;
         break;
    case(6): //Sub tested
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x29;
        CS[codeIndex++]  = 0xD8;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x50;
         break;
    case(7): //Mul tested
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0xF7;
        CS[codeIndex++]  = 0xE3;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x50;
         break;
    case(8): //Div tested
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0xF6;
        CS[codeIndex++]  = 0xF3;
        CS[codeIndex++]  = 0x30;
        CS[codeIndex++]  = 0xE4;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x50;
         break;
    case(9): //Call need to recompile

        CS[codeIndex++]  = 0x31;
        CS[codeIndex++]  = 0xC0;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xD0;
         break;
    case(0x0A): //Ret tested
         CS[codeIndex++] = 0xC3;
         break;
    case(0x0B): //Jmp tested
        CS[codeIndex++]  = 0x31;
        CS[codeIndex++]  = 0xC0;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xE0;
         break;
    case(0x0C): //Cmp
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x39;
        CS[codeIndex++]  = 0xD8;
         break;
    case(0x0D): //Jeq
        ;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0x75;
        CS[codeIndex++]  = 0x02;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xE0;
        CS[codeIndex++]  = 0x90;
         break;
    case(0x0E): //Jne
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0x74;
        CS[codeIndex++]  = 0x02;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xE0;
         break;
    case(0x0F): //Jgt
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0x7E;
        CS[codeIndex++]  = 0x02;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xE0;
         break;
    case(0x10): //Jlt
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0x7D;
        CS[codeIndex++]  = 0x02;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xE0;
         break;
    case(0x11): //Jle
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0x7F;
        CS[codeIndex++]  = 0x02;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xE0;
         break;
    case(0x12): //Jge
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x5B;
        CS[codeIndex++]  = 0x88;
        CS[codeIndex++]  = 0xDC;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = b_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = c_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = d_UINT16(InstructionLookupTable);
        CS[codeIndex++]  = 0x7C;
        CS[codeIndex++]  = 0x02;
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xE0;
         break;
    case(0x13): //Exit tested
        CS[codeIndex++] = ExDone;
         break;
        case(0x14): // incremant item at top of stack
    ;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x83;
        CS[codeIndex++]  = 0xC0;
        CS[codeIndex++]  = 0x01;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x50;
         break;
         case(0x15): //syscall
        CS[codeIndex++]  = 0x31;
        CS[codeIndex++]  = 0xC0;
        CS[codeIndex++]  = 0x66;
        CS[codeIndex++]  = 0x58;
        CS[codeIndex++]  = 0x8B;
        CS[codeIndex++]  = 0x04;
        CS[codeIndex++]  = 0x85;
        CS[codeIndex++]  = a_UINT16(SystemCallTable);
        CS[codeIndex++]  = b_UINT16(SystemCallTable);
        CS[codeIndex++]  = c_UINT16(SystemCallTable);
        CS[codeIndex++]  = d_UINT16(SystemCallTable);
        CS[codeIndex++]  = 0xFF;
        CS[codeIndex++]  = 0xD0;
         break;
    }

}

 CS[codeIndex++] = ExDone;

 printf("running program\n");
     //Near return
    //run it

    ((void(*)())CS)();


    //print result
 printf("done program\n");
 printf("Length: %04x\n",codeIndex);
printf("result: %04x\n",DS[256 * 2 + 1]);

 PrintArray(SystemCallSpace);
 //PrintArray(Text);
    //free everything
    free(CS);
    free(DS);
     return 0;
}


