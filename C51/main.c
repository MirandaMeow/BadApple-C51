#include <STC89C5xRC.H>
#include "LED88.h"

#define uint unsigned int
#define uchar unsigned char

// 帧计数
uint count;

// 帧缓存
uchar Frame[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// 实际用来显示的帧
uchar Out[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/** @brief  串口初始化，波特率为 9600
  * @param  无
  * @retval 无
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

/** @brief  复制数组
  * @param  array1  目标数组
  * @param  array2  原数组
  * @retval 无
  */
void Copy_Array(uchar *array1, uchar *array2) {
    uint i;
    for (i = 0; i < 32; i++) {
        array1[i] = array2[i];
    }
}

/** @brief  串口中断函数，每收到 32 字节就更新一次帧数据
  * @param  无
  * @retval 无
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

/** @brief  主函数，显示帧数据
  * @param  无
  * @retval 无
  */
void main() {
    Uart_Init();
    LED88_Init();

    while (1) {
        LED88_Animation(Out, Out, 0);
    };
}

