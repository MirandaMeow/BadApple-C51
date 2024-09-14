#include <STC89C5xRC.H>

#define uint unsigned int
#define uchar unsigned char

sbit OE = P2 ^ 3;
sbit DI = P2 ^ 2;
sbit STR = P2 ^ 1;
sbit CLK = P2 ^ 0;

uchar code row[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

void LED88_Init() {
    OE = 0;
}

void LED88_WriteByte(uchar LED_DATA) {
    uchar i;
    for (i = 0; i < 8; i++) {
        DI = LED_DATA & 0x80;
        LED_DATA <<= 1;
        CLK = 1;
        CLK = 0;
    }
}

void LED88_Show(uchar *Line_Green, uchar *Line_Red) {
    uchar i;
    for (i = 0; i < 8; i++) {
        LED88_WriteByte(~Line_Green[i]);
        LED88_WriteByte(~Line_Red[i]);
        LED88_WriteByte(row[i]);
        STR = 1;
        STR = 0;
        LED88_WriteByte(0xFF);
        LED88_WriteByte(0xFF);
        LED88_WriteByte(0xFF);
        STR = 1;
        STR = 0;
    }
}

void LED88_Show_Cascade(uchar Line_Green, uchar Line_Red, uchar _row) {
    LED88_WriteByte(Line_Green);
    LED88_WriteByte(Line_Red);
    LED88_WriteByte(row[_row]);
}

void LED88_Show_Cascade_Green(uchar Line_Green, uchar _row) {
    LED88_WriteByte(Line_Green);
    LED88_WriteByte(0xFF);
    LED88_WriteByte(row[_row]);
}

void LED88_Show_Cascade_Red(uchar Line_Red, uchar _row) {
    LED88_WriteByte(0xFF);
    LED88_WriteByte(Line_Red);
    LED88_WriteByte(row[_row]);
}

void LED88_Remove() {
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

void LED88_Latch() {
    STR = 1;
    STR = 0;
}

void LED88_Animation(uchar *Green, uchar *Red, frame) {
    uchar i, cascade4, cascade3, cascade2, cascade1;
    for (i = 0; i < 8; i++) {
        cascade4 = i * 2 + 17 + frame * 32;
        cascade3 = i * 2 + 16 + frame * 32;
        cascade2 = i * 2 + 1 + frame * 32;
        cascade1 = i * 2 + frame * 32;
        LED88_Show_Cascade(Green[cascade4], Red[cascade4], i);
        LED88_Show_Cascade(Green[cascade3], Red[cascade3], i);
        LED88_Show_Cascade(Green[cascade2], Red[cascade2], i);
        LED88_Show_Cascade(Green[cascade1], Red[cascade1], i);
        LED88_Latch();
    }
}

void LED88_Animation_Green(uchar *Green, frame) {
    uchar i, cascade4, cascade3, cascade2, cascade1;
    for (i = 0; i < 8; i++) {
        cascade4 = i * 2 + 17 + frame * 32;
        cascade3 = i * 2 + 16 + frame * 32;
        cascade2 = i * 2 + 1 + frame * 32;
        cascade1 = i * 2 + frame * 32;
        LED88_Show_Cascade_Green(Green[cascade4], i);
        LED88_Show_Cascade_Green(Green[cascade3], i);
        LED88_Show_Cascade_Green(Green[cascade2], i);
        LED88_Show_Cascade_Green(Green[cascade1], i);
        LED88_Latch();
    }
}

void LED88_Animation_Red(uchar *Red, frame) {
    uchar i, cascade4, cascade3, cascade2, cascade1;
    for (i = 0; i < 8; i++) {
        cascade4 = i * 2 + 17 + frame * 32;
        cascade3 = i * 2 + 16 + frame * 32;
        cascade2 = i * 2 + 1 + frame * 32;
        cascade1 = i * 2 + frame * 32;
        LED88_Show_Cascade_Red(Red[cascade4], i);
        LED88_Show_Cascade_Red(Red[cascade3], i);
        LED88_Show_Cascade_Red(Red[cascade2], i);
        LED88_Show_Cascade_Red(Red[cascade1], i);
        LED88_Latch();
    }
}