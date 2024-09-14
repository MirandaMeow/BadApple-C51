#include <STC89C5xRC.H>

#define uint unsigned int
#define uchar unsigned char

//引脚配置：
sbit OE = P2 ^ 3;
sbit DI = P2 ^ 2;
sbit STR = P2 ^ 1;
sbit CLK = P2 ^ 0;

uchar code Row_Hex[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

//函数定义：
/** @brief  初始化 LED 点阵屏，使能低电平为启用
  * @param  无
  * @retval 无
  */
void LED88_Init() {
    OE = 0;
}

/** @brief  向 74HC595 写入数据
  * @param  LED_DATA 写入的数据，1 比特
  * @retval 无
  */
void LED88_WriteByte(uchar LED_DATA) {
    uchar i;
    for (i = 0; i < 8; i++) {
        DI = LED_DATA & 0x80;
        LED_DATA <<= 1;
        CLK = 1;
        CLK = 0;
    }
}

/** @brief  显示一帧画面，传入的 Line_Green 和 Line_Red 必须为长度为 32 的数组，每个元素为 1 比特数据
  * @param  Line_Green 绿色灯数据
  * @param  Line_Red 红色灯数据
  * @retval 无
  */
void LED88_Show(uchar *Line_Green, uchar *Line_Red) {
    uchar i;
    for (i = 0; i < 8; i++) {
        LED88_WriteByte(~Line_Green[i]);
        LED88_WriteByte(~Line_Red[i]);
        LED88_WriteByte(Row_Hex[i]);
        STR = 1;
        STR = 0;
        LED88_WriteByte(0xFF);
        LED88_WriteByte(0xFF);
        LED88_WriteByte(0xFF);
        STR = 1;
        STR = 0;
    }
}

/** @brief  级联时写入单个 74HC595 的数据
  * @param  Line_Green 绿色灯数据
  * @param  Line_Green 绿色灯数据
  * @param  Row 行号
  * @retval 
  */
void LED88_Show_Cascade(uchar Line_Green, uchar Line_Red, uchar Row) {
    LED88_WriteByte(~Line_Green);
    LED88_WriteByte(~Line_Red);
    LED88_WriteByte(Row_Hex[Row]);
}

/** @brief  级联时写入单个 74HC595 的数据，只显示绿色
  * @param  Line_Green 绿色灯数据
  * @param  Row 行号
  * @retval 
  */
void LED88_Show_Cascade_Green(uchar Line_Green, uchar Row) {
    LED88_WriteByte(~Line_Green);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(Row_Hex[Row]);
}

/** @brief  级联时写入单个 74HC595 的数据，只显示红色
  * @param  Line_Red 红色灯数据
  * @param  Row 行号
  * @retval 
  */
void LED88_Show_Cascade_Red(uchar Line_Red, uchar Row) {
    LED88_WriteByte(0xFF);
    LED88_WriteByte(~Line_Red);
    LED88_WriteByte(Row_Hex[Row]);
}

/** @brief  在级联后消影，可能会造成闪烁
  * @param  无
  * @retval 无
  */
void LED88_Remove_Shadow() {
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(0xFF);
    STR = 1;
    STR = 0;
}

/** @brief  将移位寄存器的数据锁存
  * @param  无
  * @retval 无
  */
void LED88_Latch() {
    STR = 1;
    STR = 0;
}

/** @brief  播放动画
  * @param  Green 长度为 32 的倍数的数组，每个元素为 1 比特数据，为绿色灯数据
  * @param  Red 长度为 32 的倍数的数组，每个元素为 1 比特数据，为红色灯数据
  * @param  frame 当前帧
  * @retval 无
  */
void LED88_Animation(uchar *Green, uchar *Red, Frame) {
    uchar i, cascade4, cascade3, cascade2, cascade1;
    for (i = 0; i < 8; i++) {
        cascade4 = i * 2 + 17 + Frame * 32;
        cascade3 = i * 2 + 16 + Frame * 32;
        cascade2 = i * 2 + 1 + Frame * 32;
        cascade1 = i * 2 + Frame * 32;
        LED88_Show_Cascade(Green[cascade4], Red[cascade4], i);
        LED88_Show_Cascade(Green[cascade3], Red[cascade3], i);
        LED88_Show_Cascade(Green[cascade2], Red[cascade2], i);
        LED88_Show_Cascade(Green[cascade1], Red[cascade1], i);
        LED88_Latch();
    }
}

/** @brief  播放动画，只显示绿色
  * @param  Green 长度为 32 的倍数的数组，每个元素为 1 比特数据，为绿色灯数据
  * @param  frame 当前帧
  * @retval 无
  */
void LED88_Animation_Green(uchar *Green, Frame) {
    uchar i, cascade4, cascade3, cascade2, cascade1;
    for (i = 0; i < 8; i++) {
        cascade4 = i * 2 + 17 + Frame * 32;
        cascade3 = i * 2 + 16 + Frame * 32;
        cascade2 = i * 2 + 1 + Frame * 32;
        cascade1 = i * 2 + Frame * 32;
        LED88_Show_Cascade_Green(Green[cascade4], i);
        LED88_Show_Cascade_Green(Green[cascade3], i);
        LED88_Show_Cascade_Green(Green[cascade2], i);
        LED88_Show_Cascade_Green(Green[cascade1], i);
        LED88_Latch();
    }
}

/** @brief  播放动画，只显示红色
  * @param  Red 长度为 32 的倍数的数组，每个元素为 1 比特数据，为红色灯数据
  * @param  frame 当前帧
  * @retval 无
  */
void LED88_Animation_Red(uchar *Red, Frame) {
    uchar i, cascade4, cascade3, cascade2, cascade1;
    for (i = 0; i < 8; i++) {
        cascade4 = i * 2 + 17 + Frame * 32;
        cascade3 = i * 2 + 16 + Frame * 32;
        cascade2 = i * 2 + 1 + Frame * 32;
        cascade1 = i * 2 + Frame * 32;
        LED88_Show_Cascade_Red(Red[cascade4], i);
        LED88_Show_Cascade_Red(Red[cascade3], i);
        LED88_Show_Cascade_Red(Red[cascade2], i);
        LED88_Show_Cascade_Red(Red[cascade1], i);
        LED88_Latch();
    }
}