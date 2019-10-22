/* E paper driver library coded by TinLethax */
/* This is the High level part of the library, For advcanced function like bitmapping / rendering, Create data packet for bmp displaying .*/

#ifndef EPI_H
#define EPI_H 

#include <stdint.h>
#include <stm8l.h>

void Full_updata_setting(void);
void Part_updata_setting(void);
void Updata(void);
void Full_image(const unsigned char *data);
void Full_image_Clean(void);
void Part_image(const unsigned char *data_old,const unsigned char *data_new);
void Part_image_first(const unsigned char *data_new);
void Full_lut_bw(void);
void Part_lut_bw(void);

#endif 