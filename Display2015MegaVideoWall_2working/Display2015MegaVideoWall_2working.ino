#include <SPI.h>
#include <SD.h>

File myFile;

#define COLOR(r,g,b)     ((r)+((g)<<4)+((b)<<8))  //Color is 12-bit (4-bit each R, G, B)
#define black            COLOR(0,0,0)  
#define red              COLOR(0xf,0,0)  
#define green            COLOR(0,0xf,0)  
#define blue             COLOR(0,0,0xf)  
#define teal             COLOR(0,0xf,0xf)  
#define magenta          COLOR(0xf,0,0xf)
#define pink             COLOR(0xf,0x2,0xf)
#define yellow           COLOR(0xf,0xf,0)
#define purple           COLOR(0xa,0x0,0xf)
#define orange           COLOR(0xf,0x3,0x0)
#define warmWhite        COLOR(0xf,0x7,0x2)
#define white		 COLOR(0xd, 0xd, 0xd)
#define brown            COLOR(0x5, 0x3, 0x2)
#define lightCount      48             //50, only need 48 out of 50 for 24 x 48 pixel display
#define lightCount2     50             //Using 50 for enumerateAll() so last 2 won't turn on
#define defaultIntensity      0xcc
#define delayShort      10      //6 orig.
#define delayLong       20      //12 orig.
#define delayShort_2    10      //3 orig.
#define delayLong_2     20      //16 orig.
#define delayEnd        31      //30 orig.

int i, j = 0;
int  y = 0;

const int rgb[] = {COLOR(15, 0, 0), COLOR(15, 1, 0), COLOR(15, 2, 0), COLOR(15, 3, 0), COLOR(15, 4, 0), COLOR(15, 5, 0), COLOR(15, 6, 0), COLOR(15, 7, 0), COLOR(15, 8, 0), COLOR(15, 9, 0),
COLOR(15, 10, 0), COLOR(15, 11, 0), COLOR(15, 12, 0), COLOR(15, 13, 0), COLOR(15, 14, 0), COLOR(15, 15, 0), COLOR(14, 15, 0), COLOR(13, 15, 0), COLOR(12, 15, 0), COLOR(11, 15, 0),
COLOR(10, 15, 0), COLOR(9, 15, 0), COLOR(8, 15, 0), COLOR(7, 15, 0), COLOR(6, 15, 0), COLOR(5, 15, 0), COLOR(4, 15, 0), COLOR(3, 15, 0), COLOR(2, 15, 0), COLOR(1, 15, 0), COLOR(0, 15, 0),
COLOR(0, 15, 1), COLOR(0, 15, 2), COLOR(0, 15, 3), COLOR(0, 15, 4), COLOR(0, 15, 5), COLOR(0, 15, 6), COLOR(0, 15, 7), COLOR(0, 15, 8), COLOR(0, 15, 9), COLOR(0, 15, 10), COLOR(0, 15,11),
COLOR(0, 15, 12), COLOR(0, 15, 13), COLOR(0, 15, 14), COLOR(0, 15, 15), COLOR(0, 14, 15), COLOR(0, 13, 15), COLOR(0, 12, 15), COLOR(0, 11, 15), COLOR(0, 10, 15), COLOR(0, 9, 15),
COLOR(0, 8, 15), COLOR(0, 7, 15), COLOR(0, 6, 15), COLOR(0, 5, 15), COLOR(0, 4, 15), COLOR(0, 3, 15), COLOR(0, 2, 15), COLOR(0, 1, 15), COLOR(0, 0, 15), COLOR(1, 0, 15), COLOR(2, 0, 15),
COLOR(3, 0, 15), COLOR(4, 0, 15), COLOR(5, 0, 15), COLOR(6, 0, 15), COLOR(7, 0, 15), COLOR(8, 0, 15), COLOR(9, 0, 15), COLOR(10, 0, 15), COLOR(11, 0, 15), COLOR(12, 0, 15), COLOR(13, 0, 15),
COLOR(14, 0, 15), COLOR(15, 0, 15), COLOR(15, 0, 14), COLOR(15, 0, 13), COLOR(15, 0, 12), COLOR(15, 0, 11), COLOR(15, 0, 10), COLOR(15, 0, 9), COLOR(15, 0, 8), COLOR(15, 0, 7),
COLOR(15, 0, 6), COLOR(15, 0, 5), COLOR(15, 0, 4), COLOR(15, 0, 3), COLOR(15, 0, 2), COLOR(15, 0, 1)};


int a[48][12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //0
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //1
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //2
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //3
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //4
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //5
                 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,  //6
                 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,  //7
                 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,  //8
                 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //9
                 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  //10
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //11
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //12
                 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,  //13
                 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  //14
                 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  //15
                 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0,  //16
                 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  //17
                 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,  //18
                 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2,  //19
                 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62,  //20
                 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,  //21
                 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  //22
                 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  //23
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //24
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //25
                 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,  //26
                 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,  //27
                 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c,  //28
                 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2,  //29
                 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62,  //30
                 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,  //31
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //32
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //33
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //34
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //35
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //36
                 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  //37
                 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //38
                 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e,  //39
                 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,  //40
                 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,  //41
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //42
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //43
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //44
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //45
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //46
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //47


int c[48][12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //0
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //1
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //2
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //3
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //4
                 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,  //5
                 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83,  //6
                 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,  //7
                 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,  //8
                 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,  //9
                 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  //10
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //11
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //12
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //13
                 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,  //14
                 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,  //15
                 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43, 0x43,  //16
                 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67,  //17
                 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,  //18
                 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,  //19
                 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,  //20
                 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b,  //21
                 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,  //22
                 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,  //23
                 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4,  //24
                 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,  //25
                 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b,  //26
                 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,  //27
                 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,  //28
                 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4, 0xc4,  //29
                 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,  //30
                 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,  //31
                 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,  //32
                 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,  //33
                 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  //34
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //35
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //36
                 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,  //37
                 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //38
                 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e,  //39
                 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,  //40
                 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,  //41
                 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,  //42
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //43
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //44
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //45
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //46
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //47


int l[48][12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //0
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //1
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //2
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //3
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //4
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //5
                 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //6
                 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,  //7
                 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70,  //8
                 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,  //9
                 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  //10
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //11
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //12
                 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,  //13
                 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,  //14
                 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,  //15
                 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,  //16
                 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,  //17
                 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  //18
                 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e,  //19
                 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,  //20
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //21
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //22
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //23
                 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //24
                 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e,  //25
                 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  //26
                 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,  //27
                 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23,  //28
                 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,  //29
                 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,  //30
                 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,  //31
                 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  //32
                 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,  //33
                 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //34
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //35
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //36
                 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  //37
                 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,  //38
                 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,  //39
                 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,  //40
                 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //41
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //42
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //43
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //44
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //45
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //46
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //47



void beginAll(){          //begins the data frame for all outputs on PORTA, PORTC and PORTL
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
}



void beginAllBitMask(int maskA, int maskC, int maskL){          //begins the data frame for all outputs on PORTA, PORTC and PORTL
  PORTA = B11111111 & byte(maskA);
  PORTC = B11111111 & byte(maskC);
  PORTL = B11111111 & byte(maskL);
  delayMicroseconds(delayShort);  //Output should be ~ 10uS long
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
}



void zeroAll(){
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(delayShort_2);  //Output should be ~ 10uS long
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  delayMicroseconds(delayLong_2); //Output should be ~ 20uS long
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
}



void zeroAllBitMask(int maskA, int maskC, int maskL){
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(delayShort_2);  //Output should be ~ 10uS long
  PORTA = B11111111 & byte(maskA);
  PORTC = B11111111 & byte(maskC);
  PORTL = B11111111 & byte(maskL);
  delayMicroseconds(delayLong_2); //Output should be ~ 20uS long
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
}



void oneAll(){
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000; 
  delayMicroseconds(delayLong);    //Output should be ~ 20uS long
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  delayMicroseconds(delayShort);    //Output should be ~ 10uS long
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
}



void oneAllBitMask(int maskA, int maskC, int maskL){
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000; 
  delayMicroseconds(delayLong);    //Output should be ~ 20uS long
  PORTA = B11111111 & byte(maskA);
  PORTC = B11111111 & byte(maskC);
  PORTL = B11111111 & byte(maskL);
  delayMicroseconds(delayShort);    //Output should be ~ 10uS long
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
}



void endAll(){            //sets the data line LOW between data frames
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000;
  delayMicroseconds(delayEnd);
}



void zeroOne(int byteA, int byteC, int byteL){            //
  
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000; 
  delayMicroseconds(9); //Output should be ~ 10uS long (orig. 6, changed to 3 to match zeroAll() timing)
  PORTA = ~byteA;
  PORTC = ~byteC;
  PORTL = ~byteL;
  delayMicroseconds(11);  //Output should be ~ 10uS long (orig. 6, changed to 9 to match zeroAll() timing)
  PORTA = B11111111;
  PORTC = B11111111;
  PORTL = B11111111;
  delayMicroseconds(9);  //Output should be ~ 10uS long (orig. 7)
}



void zeroOneBitMask(int byteA, int byteC, int byteL, int maskA, int maskC, int maskL){            //
  
  PORTA = B00000000;
  PORTC = B00000000;
  PORTL = B00000000; 
  delayMicroseconds(9); //Output should be ~ 10uS long (orig. 6, changed to 3 to match zeroAll() timing)
  PORTA = ~byteA & maskA;
  PORTC = ~byteC & maskC;
  PORTL = ~byteL & maskL;
  delayMicroseconds(11);  //Output should be ~ 10uS long (orig. 6, changed to 9 to match zeroAll() timing)
  PORTA = B11111111 & byte(maskA);
  PORTC = B11111111 & byte(maskC);
  PORTL = B11111111 & byte(maskL);
  delayMicroseconds(9);  //Output should be ~ 10uS long (orig. 7)
}



void enumerateAll(){       //addresses each bulb individually for all outputs
   fillColorAll(0, lightCount2, defaultIntensity, black);
}



void setColor(int led, int intensity){
  int _led = led;
  beginAll();
  
  for (int i = 6; i; i--, (led <<= 1))
    if (led & (1 << 5))
      oneAll();
    else
      zeroAll();
  
  for (int i = 8; i; i--, (intensity <<= 1))
    if (intensity & (1 << 7))
      oneAll();
    else
      zeroAll();
  
  for (int i = 0; i<12; i++){
    zeroOne(a[_led][i], c[_led][i], l[_led][i]);
  }
    
  endAll();
}



void setColorBitMask(int led, int intensity, int maskA, int maskC, int maskL){
  int _led = led;
  beginAllBitMask(maskA, maskC, maskL);
  
  for (int i = 6; i; i--, (led <<= 1))
    if (led & (1 << 5))
      oneAllBitMask(maskA, maskC, maskL);
    else
      zeroAllBitMask(maskA, maskC, maskL);
  
  for (int i = 8; i; i--, (intensity <<= 1))
    if (intensity & (1 << 7))
      oneAllBitMask(maskA, maskC, maskL);
    else
      zeroAllBitMask(maskA, maskC, maskL);
  
  for (int i = 0; i<12; i++){
    zeroOneBitMask(a[_led][i], c[_led][i], l[_led][i], maskA, maskC, maskL);
  }
    
  endAll();
}



void setColorOne(int led, int intensity, int address){
  int _led = led;
  beginAll();
  
  for (int i = 6; i; i--, (led <<= 1))
    if (led & (1 << 5))
      oneAll();
    else
      zeroAll();
  
  for (int i = 8; i; i--, (intensity <<= 1))
    if (intensity & (1 << 7))
      oneAll();
    else
      zeroAll();
  
  for (int i = 0; i<12; i++){
    zeroOne(a[address][i], c[address][i], l[address][i]);
  }
    
  endAll();
}



void setColorAll(uint8_t led, uint8_t intensity, uint16_t color){                   //sets the color and intensity for a specific bulb on all outputs of PORTA, PORTC and PORTL
  uint8_t i;  
  beginAll();  
  for(i=6;i;i--,(led<<=1))  
    if(led&(1<<5)) oneAll();  
    else zeroAll();
  for(i=8;i;i--,(intensity<<=1))  
    if(intensity&(1<<7)) oneAll();  
    else zeroAll();
  for(i=12;i;i--,(color<<=1))  
    if(color&(1<<11)) oneAll();  
    else zeroAll();
  endAll();  
}

void fillColorAll(uint8_t begin, uint8_t count, uint8_t intensity, uint16_t color){ //fills the string with a color and intensity starting from a specific bulb to the end of the string
  while(count--){                                                                   //for all outputs on PORTA, PORTC and PORTL
    setColorAll(begin++, intensity, color);  
  }
}



void USFlag(){
  myFile = SD.open("disp_15/USFlag.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  for (int i = 36; i < lightCount; i++)
    setColor(i, defaultIntensity);
  for (int i = 40; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}


void GELogo(){
  int x;
  myFile = SD.open("disp_15/GELogo.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (x = 0; x < lightCount; x++);
    setColorAll(x, 0, 0);
  for (x = 0; x < (defaultIntensity + 1); x++){
    for (int i = 0; i < lightCount; i++)
      setColor(i, x);
  }
  interrupts();
//  delay(3000);
}

void inThe(){
  i = 1;
  j = 12;
  y = j;
  myFile = SD.open("disp_15/inThe.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColor(i, defaultIntensity);
  for (int z = 0; z < 13; z++){
    for (int x = 0; x < i; x++){
      setColorOne(x, defaultIntensity, y);
      y += 1;
    }
    for (int k = i; k < lightCount; k++)
      setColorAll(k, defaultIntensity, 0);
    i++;
    j--;
    y = j;
  }
  i = 20;
  j = 47;
  for (int z = 0; z < 27; z++){
    for (int k = 0; k < 20; k++)
      setColor(k, defaultIntensity);
    for (int x = 20; x < j; x++)
      setColorAll(x, defaultIntensity, 0);
    for (int y = j; y < lightCount; y++){
      setColorOne(y, defaultIntensity, i);
      i++;
    }
    i = 20;
    j--;
  }
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  interrupts();
//  delay(1000);
}

void CLE(){
  myFile = SD.open("disp_15/CLE.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColor(i, defaultIntensity);
  int x;
  for (x = 0; x < 16; x++)
    setColor(x, defaultIntensity);
  for (x = 16; x < lightCount; x++)
    setColorAll(x, defaultIntensity, 0);
  interrupts();
  delay(250);
  noInterrupts();
  for (x = 0; x < 30; x++)
    setColor(x, defaultIntensity);
  for (x = 30; x < lightCount; x++);
    setColorAll(x, defaultIntensity, 0);
  interrupts();
  delay(250);
  noInterrupts();
  for (x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  interrupts();
//  delay(3000);
}

void R2D2leftDown(){
  myFile = SD.open("disp_15/R2D2.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColor(i, defaultIntensity);
  i = 4;
  j = 47;
  for (int z = 0; z < 43; z++){
    for (int x = 0; x < j; x++)
      setColorAll(x, defaultIntensity, 0);
    for (int y = j; y < lightCount; y++){
      setColorOne(y, defaultIntensity, i);
      i++;
    }
    i = 4;
    j--;
  }
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  interrupts();
  delay(1000);
  noInterrupts();
  for (int x = 0; x < lightCount-1; x++)
    setColorOne(x, defaultIntensity, x+1);
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  for (int x = 0; x < lightCount-1; x++)
    setColorOne(x, defaultIntensity, x+1);
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  for (int x = 0; x < lightCount-1; x++)
    setColorOne(x, defaultIntensity, x+1);
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  interrupts();
  delay(500);
  for (int z = 0; z < 24; z++){
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        int tempA = lowByte((a[i][j] << 1));
        int tempC = lowByte((c[i][j] << 1) + byte((a[i][j] >> 7)));
        int tempL = lowByte((l[i][j] << 1) + byte((c[i][j] >> 7)));
        a[i][j] = tempA;
        c[i][j] = tempC;
        l[i][j] = tempL;
      }
    }
    noInterrupts();
    for (int i = 0; i < lightCount; i++)
      setColor(i, defaultIntensity);
    interrupts();
  }
}

void R2D2left(){
  myFile = SD.open("disp_15/R2D2.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColor(i, defaultIntensity);
  i = 4;
  j = 47;
  for (int z = 0; z < 43; z++){
    for (int x = 0; x < j; x++)
      setColorAll(x, defaultIntensity, 0);
    for (int y = j; y < lightCount; y++){
      setColorOne(y, defaultIntensity, i);      //set the led "y" to contain the image data in array element "i"
      i++;
    }
    i = 4;        //reset the array counter so next led in the loop gets beginning of the image
    j--;          //decrement the next led so image scrolls left
  }
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  interrupts();
  delay(2000);
}

void R2D2right(){
  myFile = SD.open("disp_15/R2D2.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColor(i, defaultIntensity);
  for (int z = 0; z < 45; z++){
    for (int x = 0; x < i; x++){
      setColorOne(x, defaultIntensity, y);
      y += 1;
    }
    for (int k = i; k < lightCount; k++)
      setColorAll(k, defaultIntensity, 0);
    i++;
    j--;
    y = j;
  }
}

void R2D2upDown(){
  for (int z = 0; z < 8; z++){                                //R2 peeks up
    myFile = SD.open("disp_15/R2D2.txt", FILE_READ);
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        a[i][j] = myFile.read();
      }
    }
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        c[i][j] = myFile.read();
      }
    }
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        l[i][j] = myFile.read();
      }
    }
    myFile.close();
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        l[i][j] = lowByte(a[i][j] << (7-z));
        a[i][j] = 0;
        c[i][j] = 0;
      }
    }
    noInterrupts();
    for (int x = 0; x < lightCount; x++)
      setColor(x, defaultIntensity);
    interrupts();
  }
  for (int z = 0; z < 8; z++){
    myFile = SD.open("disp_15/R2D2.txt", FILE_READ);
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        a[i][j] = myFile.read();
      }
    }
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        c[i][j] = myFile.read();
      }
    }
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        l[i][j] = myFile.read();
      }
    }
    myFile.close();
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        int tempC = lowByte(a[i][j] << (7-z));
        int tempA = lowByte(a[i][j]);
        tempA >>= (z+1);
        int tempL = lowByte((c[i][j] << (7-z)) + tempA);
        a[i][j] = 0;
        c[i][j] = tempC;
        l[i][i] = tempL;
      }
    }
    noInterrupts();
    for (int x = 0; x < lightCount; x++)
      setColor(x, defaultIntensity);
    interrupts();
  }
  delay(500);
  noInterrupts();
  for (int x = 0; x < lightCount-1; x++)
    setColorOne(x, defaultIntensity, x+1);
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  for (int x = 0; x < lightCount-1; x++)
    setColorOne(x, defaultIntensity, x+1);
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  for (int x = 0; x < lightCount-1; x++)
    setColorOne(x, defaultIntensity, x+1);
  for (int x = 0; x < lightCount; x++)
    setColor(x, defaultIntensity);
  interrupts();
  delay(500);
  for (int z = 0; z < 16; z++){                              //R2 ducks back down
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        int tempA = lowByte((a[i][j] << 1));
        int tempC = lowByte((c[i][j] << 1) + byte((a[i][j] >> 7)));
        int tempL = lowByte((l[i][j] << 1) + byte((c[i][j] >> 7)));
        a[i][j] = tempA;
        c[i][j] = tempC;
        l[i][j] = tempL;
      }
    }
    noInterrupts();
    for (int i = 0; i < lightCount; i++)
      setColor(i, defaultIntensity);
    interrupts();
    delay(500);                //delay for testing, comment out for actual display
  }
}

void snow(){
  myFile = SD.open("disp_15/snow.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
  for (int z = 0; z < 48; z++){
    for (int i = 0; i < lightCount; i++){
      for (int j = 0; j < 12; j++){
        int tempA = lowByte((a[i][j] << 1) + byte((l[i][j] >> 7)));
        int tempC = lowByte((c[i][j] << 1) + byte((a[i][j] >> 7)));
        int tempL = lowByte((l[i][j] << 1) + byte((c[i][j] >> 7)));
        a[i][j] = tempA;
        c[i][j] = tempC;
        l[i][j] = tempL;
      }
    }
    noInterrupts();
    for (int i = 0; i < lightCount; i++)
      setColor(i, defaultIntensity);
    interrupts();
    delay(250);
  }
  
}

void TIE(){
  myFile = SD.open("disp_15/TIE.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void TIEleft(){
  myFile = SD.open("disp_15/TIE.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColor(i, defaultIntensity);
  i = 6;
  j = 44;
  for (int z = 0; z < 24; z++){
    for (int x = 0; x < j; x++)
      setColorAll(x, defaultIntensity, 0);
    for (int y = j; y < lightCount; y++){
      if (y >= 0) setColorOne(y, defaultIntensity, i);      //set the led "y" to contain the image data in array element "i"
      i++;
      if (i > 43) i = 43;
    }
    i = 6;        //reset the array counter so next led in the loop gets beginning of the image
    j -= 4;          //decrement the next led so image scrolls left
  }
  interrupts();
  delay(2000);
}

void trees(){
  myFile = SD.open("disp_15/trees.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void bellOne(){
  myFile = SD.open("disp_15/bellOne.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void bellTwo(){
  myFile = SD.open("disp_15/bell2.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void bellThree(){
  myFile = SD.open("disp_15/bell3.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void santaRight(){
  myFile = SD.open("disp_15/santa.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void santaLeft(){
  myFile = SD.open("disp_15/santa.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[47-i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[47-i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[47-i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int i = 0; i < lightCount; i++)
    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

/*void planeLeft(){
  myFile = SD.open("disp_15/plane.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}*/

void planeRight(){
  myFile = SD.open("disp_15/plane.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[47-i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[47-i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[47-i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
  for (int z = 0; z < 24; z++){
    for (int x = 0; x < i; x++){
      setColorOne(x, defaultIntensity, y);
      y += 1;
    }
    for (int k = i; k < lightCount; k++)
      setColorAll(k, defaultIntensity, 0);
    i += 4;
    j--;
    y = j;
  }
  interrupts();
}

void planeLeft(){
  myFile = SD.open("disp_15/plane.txt", FILE_READ);
//  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColor(i, defaultIntensity);
  i = 2;
  j = 45;
  for (int z = 0; z < 36; z++){
    for (int x = 0; x < j; x++)
      setColorAll(x, defaultIntensity, 0);
    for (int y = j; y < lightCount; y++){
      if (y >= 0) setColorOne(y, defaultIntensity, i);      //set the led "y" to contain the image data in array element "i"
      i++;
      if (i > 47) i = 47;
    }
    i = 2;        //reset the array counter so next led in the loop gets beginning of the image
    j -= 3;          //decrement the next led so image scrolls left
  }
  interrupts();
  delay(2000);
}

void hashtagTheme(){
  myFile = SD.open("disp_15/hashtag.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  for (int i = 0; i < lightCount; i++)                        //comment these 2 lines if partial update does not work
    setColorBitMask(i, defaultIntensity, 0, 0, 0xc0);         //comment these 2 lines if partial update does not work
  interrupts();
}

void fire(){
  myFile = SD.open("disp_15/fire1.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 0; i < lightCount; i++)
    setColor(i, defaultIntensity);
  for (int i = 32; i < lightCount; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void fire1(){
  myFile = SD.open("disp_15/fire1.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 18; i < 31; i++)
    setColorBitMask(i, defaultIntensity, 0, 0xe0, 0x3f);
  interrupts();
}

void fire2(){
  myFile = SD.open("disp_15/fire2.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 15; i < 33; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void fire3(){
  myFile = SD.open("disp_15/fire3.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 15; i < 33; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void fire4(){
  myFile = SD.open("disp_15/fire4.txt", FILE_READ);
  noInterrupts();
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      a[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      c[i][j] = myFile.read();
    }
  }
  for (int i = 0; i < lightCount; i++){
    for (int j = 0; j < 12; j++){
      l[i][j] = myFile.read();
    }
  }
  myFile.close();
  noInterrupts();
//  for (int i = 0; i < lightCount; i++)
//    setColorAll(i, defaultIntensity, 0);
  for (int i = 15; i < 33; i++)
    setColor(i, defaultIntensity);
  interrupts();
}

void fireplace(){
  byte lastSlide = 0;
  fire();
  for (int i = 0; i < 100; i++){
    byte slide = random(1, 5);
    if ((slide == lastSlide) && (slide != 4))
      slide += 1;
    else if ((slide == lastSlide) && (slide == 4))
      slide -= 1;
    switch (slide){
      case 1:
        fire1();
        break;
      case 2:
        fire2();
        break;
      case 3:
        fire3();
        break;
      case 4:
        fire4();
        break;
      }
      byte delayTime = random(75);
      delay(delayTime);
      lastSlide = slide;
    }
  }

void GEinTheCLE(){
  GELogo();
//  delay(1000);
  
  inThe();
  delay(1000);
  
  CLE();
  delay(2000);
  
  hashtagTheme();
  delay(5000);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------SETUP--------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup(){
  
  delay(1000);
  
  DDRA = B11111111;
  DDRC = B11111111;
  DDRL = B11111111;
  
  PORTA = 0x00;
  PORTC = 0x00;
  PORTL = 0x00;
  
  delay(5);
  
  noInterrupts();
  noInterrupts();
    enumerateAll();            //Enumerate lights on string to enable individual bulb addressing
  interrupts();
  
  noInterrupts();
  noInterrupts();
  fillColorAll(0, lightCount, defaultIntensity, white);        //test all LED's on board
  interrupts();
  delay(2000);
  
  pinMode(53, OUTPUT);
  
  
//  Serial.begin(9600);

  delay(500);
  
  SD.begin();          //use hardware cs pin 53 for Mega 2560
                       //CLK --> 52
                       //DO  --> 50
                       //DI  --> 51
                       //CS  --> 53

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {
  GEinTheCLE();
  
  USFlag();
  delay(5000);
  
  GEinTheCLE();
  
  snow();
  
  GEinTheCLE();
  
//  R2D2leftDown();
//  TIEleft();
//  delay(1000);
//  R2D2upDown();
//  delay(1000);
//  TIEleft();

  trees();
  delay(5000);
  
  GEinTheCLE();
  
  for (int z = 0; z < 3; z++){
    bellOne();
    delay(500);
    bellTwo();
    delay(500);
    bellThree();
    delay(500);
    bellTwo();
    delay(500);
  }
  delay(1000);
  
  GEinTheCLE();
  
  byte rand = random(1, 3);
  if (rand == 1) santaLeft();
  else santaRight();
  delay(5000);
  
  GEinTheCLE();
 
//  planeLeft();
//  delay(1000);
  
  fireplace();
  
//  planeRight();
//  delay(3000);
  

/*  noInterrupts();
  for (int i = 0; i < lightCount; i++) setColor(i, defaultIntensity);
  interrupts();
  delay(1000);
*/
}
