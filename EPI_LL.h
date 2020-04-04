/* E paper driver library coded by TinLethax */
/* This is the Low level part of the library, For interfacing with the display */
#ifndef  EPI_LL_H
#define EPI_LL_H

#include <stdint.h>
#include <stm8l.h>
#include <delay.h>

/*
 * E paper connection:
 * from Display -> MCU
 * 1 RST -> PB1 O
 * 2 CE  -> PB4 O
 * 3 DC  -> PD0 O
 * 4 DIN -> PB6 O
 * 5 CLK -> PB5 O 
 * 6 BUSY -> PB0 I
 */

#define epi_dc 0 // data/command mode pin
#define epi_ce 4 // chip enable 
#define epi_rst 1 // quick reset 
#define epi_clk 5 // clock
#define epi_dout 6 // data input (to the display)
#define epi_busy 0 // check for busy

void EPI_gpio_init() {
/* part for the Output only */    
	PB_DDR |= (1 << epi_ce) | (1 << epi_rst) | (1 << epi_clk) | (1 << epi_dout) ;// portB direct register
	PD_DDR |= (1 << epi_dc);// portD direct register
	PB_CR1 |= (1 << epi_ce) | (1 << epi_rst) | (1 << epi_clk) | (1 << epi_dout) ;// portB control register 1
	PD_CR1 |= (1 << epi_dc);// portD control register 1
/* part for the input only */
	PB_DDR |= (0 << epi_busy) ;// set PB0 as input using Direct register
	PB_CR1 |= (0 << epi_busy) ; // set control register of CR1 as 0 (as well with CR2) for normal input no-interrupt and no pull up.
	PB_CR2 |= (0 << epi_busy) ; // set control register 2
}

void EPI_wd(int wdc){ // Write data by set dc to 1 Write Command by set dc to 0.
if (wdc == 1){	
	PB_ODR |= (1 << epi_dc); // 1 
}else{
	PB_ODR &= ~(1 << epi_dc); // 0 
}
}

void EPI_write(unsigned char byte){// write byte to the display
	PB_ODR &= ~(1 << epi_ce); // 0 enable write	
	delay_ms(1);// wait a mSec
	for(int i =0;i < 8;i++){// shift out 8 bit into dout pin by 
	PB_ODR |= (1 << epi_clk); // rise the clock to 1
	if(byte & 0x80){// byte and with 0x80 if yes
		PB_ODR |= (1 << epi_dout); //put logic 1 to data line
	}else{// else
		PB_ODR &= ~(1 << epi_dout); // put logic 0 to data line 
	}
	byte = (byte << 1); // shift left by 1 bit so we can send the next bit 	
	delay_ms(2);// wait for 2 mSec
	PB_ODR &= ~(1 << epi_clk); // fall the clock to 0
} 
	PB_ODR |= (1 << epi_clk); // 1 disable write
	byte = 0;// clear byte  
}

void EPI_init(){// reset the display for initialize 
	PB_ODR |= (1 << epi_rst); // 1 reset to high
	delay_ms(200);// wait 200mSec
	PB_ODR &= ~(1 << epi_rst); // 0 0 reset to low
	PB_ODR |= (1 << epi_ce); // 1 disable write
}

void EPI_write_cmd(unsigned char cmd){// write byte as command
	EPI_wd(0);//write command
	EPI_write(cmd);// write byte
	cmd = 0 ;// clear 
}

void EPI_write_dat(unsigned char cmd){// write byte as display data
	EPI_wd(1);//write data
	EPI_write(cmd);// write byte
	cmd = 0 ;// clear
}

void EPI_wait(){// wait until the display ready 
while (!(PB_IDR & (0 << epi_busy)) );// wait the reversed busy status because the "while" need 1 to loop
}


#endif 
