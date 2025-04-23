#include <stdio.h>


#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int


#define CRC_POLYNOMIAL

u16 crc16(u8 *sdata, u32 datalen)
{
    u16 crcval = 0x0000;
    u8 tmp = 0;

    for (u32 i = 0; i < datalen; ++i) {
        crcval ^= sdata[i];
        for (u8 j = 0; j < 8; ++j) {
            tmp = crcval & 0x0001;
            crcval = crcval >> 1;
            if (tmp) {
                crcval = (crcval ^ 0xA001);
            }
        }
    }

    return crcval;
}



            

