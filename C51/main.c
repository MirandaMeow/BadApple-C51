#include <STC89C5xRC.H>
#include "LED88.h"

#define uint unsigned int
#define uchar unsigned char

uint count;

uchar Frame[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

uchar Out[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// 初始化串口
void Uart_Init() {  //9600bps@11.0592MHz
    PCON &= 0x7F;       //波特率不倍速
    SCON = 0x50;        //8位数据,可变波特率
    AUXR &= 0xBF;       //定时器时钟12T模式
    AUXR &= 0xFE;       //串口1选择定时器1为波特率发生器
    TMOD &= 0x0F;       //设置定时器模式
    TMOD |= 0x20;       //设置定时器模式
    TL1 = 0xFD;         //设置定时初始值
    TH1 = 0xFD;         //设置定时重载值
    ET1 = 0;            //禁止定时器中断
    TR1 = 1;            //定时器1开始计时
    EA = 1;
    ES = 1;
}

void Copy_Array(uchar *array1, uchar *array2) {
    uint i;
    for (i = 0; i < 32; i++) {
        array1[i] = array2[i];
    }
}

void UART_Routine() interrupt 4 {
    if (RI == 1) {
        RI = 0;
        Frame[count] = SBUF;
        count++;
        if (count >= 32) {
            count = 0;
            Copy_Array(Out, Frame);
        }
    }
}


void main() {
    Uart_Init();
    LED88_Init();

    while (1) {
        LED88_Animation(Out, Out, 0);
    };
}

