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
	PB_DDR |= (1 << epi_ce) | (1 << epi_rst) | (1 << epi_clk) | (1 << epi_dout) ;
	PD_DDR |= (1 << epi_dc);
	PB_CR1 |= (1 << epi_ce) | (1 << epi_rst) | (1 << epi_clk) | (1 << epi_dout) ;
	PD_CR1 |= (1 << epi_dc);
/* part for the input only */
	PB_DDR |= (0 << epi_busy) ;// set PB0 as input 
	PB_CR1 |= (0 << epi_busy) ; // set control register of CR1 as 0 (as well witah CR2) for normal input no-interrupt and no pull up.
	PB_CR2 |= (0 << epi_busy) ;
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
	delay_ms(1);
	for(int i =0;i < 8;i++){
	PB_ODR |= (1 << epi_clk); // 1 
	if(byte & 0x80){
		PB_ODR |= (1 << epi_dout); // 1 
	}else{
		PB_ODR &= ~(1 << epi_dout); // 0 
	}
	byte = (byte << 1); 	
	delay_ms(2);
	PB_ODR &= ~(1 << epi_clk); // 0
} 
	PB_ODR |= (1 << epi_clk); // 1 disable write
	byte = 0; 
}

void EPI_init(){// reset the display for initialize 
	PB_ODR |= (1 << epi_rst); // 1 
	delay_ms(200);
	PB_ODR &= ~(1 << epi_rst); // 0 
	PB_ODR |= (1 << epi_ce); // 1 disable write
}

void EPI_write_cmd(unsigned char cmd){// write byte as command
	EPI_wd(0);//write command
	EPI_write(cmd);
	cmd = 0 ;
}

void EPI_write_dat(unsigned char cmd){// write byte as display data
	EPI_wd(1);//write data
	EPI_write(cmd);
	cmd = 0 ;
}

void EPI_wait(){// wait until the display ready 
while ( ~(PB_IDR & (0 << epi_busy)) );// wait the reversed busy status because the "while" need 1 to loop
}


#endif 