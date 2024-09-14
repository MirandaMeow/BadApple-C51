#include <STC89C5xRC.H>
#include "LED88.h"

#define uint unsigned int
#define uchar unsigned char

// ֡����
uint count;

// ֡����
uchar Frame[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// ʵ��������ʾ��֡
uchar Out[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/** @brief  ���ڳ�ʼ����������Ϊ 9600
  * @param  ��
  * @retval ��
  */
void Uart_Init() {
    PCON &= 0x7F;
    SCON = 0x50;
    AUXR &= 0xBF;
    AUXR &= 0xFE;
    TMOD &= 0x0F;
    TMOD |= 0x20;
    TL1 = 0xFD;
    TH1 = 0xFD;
    ET1 = 0; 
    TR1 = 1;
    EA = 1;
    ES = 1;
}

/** @brief  ��������
  * @param  array1  Ŀ������
  * @param  array2  ԭ����
  * @retval ��
  */
void Copy_Array(uchar *array1, uchar *array2) {
    uint i;
    for (i = 0; i < 32; i++) {
        array1[i] = array2[i];
    }
}

/** @brief  �����жϺ�����ÿ�յ� 32 �ֽھ͸���һ��֡����
  * @param  ��
  * @retval ��
  */
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

/** @brief  ����������ʾ֡����
  * @param  ��
  * @retval ��
  */
void main() {
    Uart_Init();
    LED88_Init();

    while (1) {
        LED88_Animation(Out, Out, 0);
    };
}

