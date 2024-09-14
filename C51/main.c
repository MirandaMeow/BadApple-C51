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

// ��ʼ������
void Uart_Init() {  //9600bps@11.0592MHz
    PCON &= 0x7F;       //�����ʲ�����
    SCON = 0x50;        //8λ����,�ɱ䲨����
    AUXR &= 0xBF;       //��ʱ��ʱ��12Tģʽ
    AUXR &= 0xFE;       //����1ѡ��ʱ��1Ϊ�����ʷ�����
    TMOD &= 0x0F;       //���ö�ʱ��ģʽ
    TMOD |= 0x20;       //���ö�ʱ��ģʽ
    TL1 = 0xFD;         //���ö�ʱ��ʼֵ
    TH1 = 0xFD;         //���ö�ʱ����ֵ
    ET1 = 0;            //��ֹ��ʱ���ж�
    TR1 = 1;            //��ʱ��1��ʼ��ʱ
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

