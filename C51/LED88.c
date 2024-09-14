#include <STC89C5xRC.H>

#define uint unsigned int
#define uchar unsigned char

//�������ã�
sbit OE = P2 ^ 3;
sbit DI = P2 ^ 2;
sbit STR = P2 ^ 1;
sbit CLK = P2 ^ 0;

uchar code Row_Hex[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

//�������壺
/** @brief  ��ʼ�� LED ��������ʹ�ܵ͵�ƽΪ����
  * @param  ��
  * @retval ��
  */
void LED88_Init() {
    OE = 0;
}

/** @brief  �� 74HC595 д������
  * @param  LED_DATA д������ݣ�1 ����
  * @retval ��
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

/** @brief  ��ʾһ֡���棬����� Line_Green �� Line_Red ����Ϊ����Ϊ 32 �����飬ÿ��Ԫ��Ϊ 1 ��������
  * @param  Line_Green ��ɫ������
  * @param  Line_Red ��ɫ������
  * @retval ��
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

/** @brief  ����ʱд�뵥�� 74HC595 ������
  * @param  Line_Green ��ɫ������
  * @param  Line_Green ��ɫ������
  * @param  Row �к�
  * @retval 
  */
void LED88_Show_Cascade(uchar Line_Green, uchar Line_Red, uchar Row) {
    LED88_WriteByte(~Line_Green);
    LED88_WriteByte(~Line_Red);
    LED88_WriteByte(Row_Hex[Row]);
}

/** @brief  ����ʱд�뵥�� 74HC595 �����ݣ�ֻ��ʾ��ɫ
  * @param  Line_Green ��ɫ������
  * @param  Row �к�
  * @retval 
  */
void LED88_Show_Cascade_Green(uchar Line_Green, uchar Row) {
    LED88_WriteByte(~Line_Green);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(Row_Hex[Row]);
}

/** @brief  ����ʱд�뵥�� 74HC595 �����ݣ�ֻ��ʾ��ɫ
  * @param  Line_Red ��ɫ������
  * @param  Row �к�
  * @retval 
  */
void LED88_Show_Cascade_Red(uchar Line_Red, uchar Row) {
    LED88_WriteByte(0xFF);
    LED88_WriteByte(~Line_Red);
    LED88_WriteByte(Row_Hex[Row]);
}

/** @brief  �ڼ�������Ӱ�����ܻ������˸
  * @param  ��
  * @retval ��
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

/** @brief  ����λ�Ĵ�������������
  * @param  ��
  * @retval ��
  */
void LED88_Latch() {
    STR = 1;
    STR = 0;
}

/** @brief  ���Ŷ���
  * @param  Green ����Ϊ 32 �ı��������飬ÿ��Ԫ��Ϊ 1 �������ݣ�Ϊ��ɫ������
  * @param  Red ����Ϊ 32 �ı��������飬ÿ��Ԫ��Ϊ 1 �������ݣ�Ϊ��ɫ������
  * @param  frame ��ǰ֡
  * @retval ��
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

/** @brief  ���Ŷ�����ֻ��ʾ��ɫ
  * @param  Green ����Ϊ 32 �ı��������飬ÿ��Ԫ��Ϊ 1 �������ݣ�Ϊ��ɫ������
  * @param  frame ��ǰ֡
  * @retval ��
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

/** @brief  ���Ŷ�����ֻ��ʾ��ɫ
  * @param  Red ����Ϊ 32 �ı��������飬ÿ��Ԫ��Ϊ 1 �������ݣ�Ϊ��ɫ������
  * @param  frame ��ǰ֡
  * @retval ��
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