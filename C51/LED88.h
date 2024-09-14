#ifndef __LED88_H__
#define __LED88_H__

#define uint unsigned int
#define uchar unsigned char

void LED88_Init();
void LED88_Remove_Shadow();
void LED88_Show(uchar *Line_Green, uchar *Line_Red);
void LED88_Animation(uchar *Green, uchar *Red, frame);
void LED88_Animation_Green(uchar *Green, frame);
void LED88_Animation_Red(uchar *Red, frame);

#endif