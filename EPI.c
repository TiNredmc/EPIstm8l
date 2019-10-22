/* E paper driver library coded by TinLethax */
/* This is the High level part of the library, For advcanced function like bitmapping / rendering, Create data packet for bmp displaying .*/
#include "EPI_LL.h"
#include "EPI.h"
#include "lut.h"

void Part_updata_setting(void){
	EPI_init();
	EPI_write_cmd(0xD2);			
	EPI_write_dat(0x3F); 
	EPI_write_cmd(0x00);  			
	EPI_write_dat (0x6F);  //from outside
	EPI_write_cmd(0x01);  			//power setting
	EPI_write_dat (0x03);	    
	EPI_write_dat (0x00);
	EPI_write_dat (0x2b);		
	EPI_write_dat (0x2b); 	
	EPI_write_cmd(0x06);				
	EPI_write_dat(0x3f);	
	EPI_write_cmd(0x2A);			
	EPI_write_dat(0x00); 
	EPI_write_dat(0x00); 	
	EPI_write_cmd(0x30);
	EPI_write_dat(0x05);			
	EPI_write_cmd(0x50);			
	EPI_write_dat(0xF2);
	EPI_write_cmd(0x60);			
	EPI_write_dat(0x22);
	EPI_write_cmd(0x82);			
	EPI_write_dat(0x00);//-0.1v
	EPI_write_cmd(0xe3);			
	EPI_write_dat(0x33);
	Part_lut_bw();		
}

void Full_updata_setting(void){
    	EPI_init(); 
	EPI_write_cmd(0xD2);			
	EPI_write_dat(0x3F);
	EPI_write_cmd(0x00);  			
	EPI_write_dat(0x6F);  //from outside
	EPI_write_cmd(0x01);  			//power setting
	EPI_write_dat(0x03);	    
	EPI_write_dat(0x00);
	EPI_write_dat(0x2b);		
	EPI_write_dat(0x2b); 
	EPI_write_cmd(0x06);				
	EPI_write_dat(0x3f);
	EPI_write_cmd(0x2A);			
	EPI_write_dat(0x00); 
	EPI_write_dat(0x00); 
	EPI_write_cmd(0x30);	
	EPI_write_dat(0x13); 
	EPI_write_cmd(0x50);
	EPI_write_dat(0x57);			
	EPI_write_cmd(0x60);			
	EPI_write_dat(0x22);
	EPI_write_cmd(0x61);			//resolution setting
  	EPI_write_dat(0x50);       //source 128 	 
  	EPI_write_dat(0x80);       
	EPI_write_cmd(0x82);			
	EPI_write_dat(0x12);  //-1v
	EPI_write_cmd(0xe3);			
	EPI_write_dat(0x33);
	Full_lut_bw();			    		
}

void Updata(void){
    EPI_write_cmd(0x04);     		//power on
		EPI_wait();
		EPI_write_cmd(0x12);	
		EPI_wait();
		EPI_write_cmd(0x02);
		EPI_wait();
}
void Full_image(const unsigned char *data){
	  unsigned int i;
		EPI_write_cmd(0x10);
		for(i=0;i<1280;i++)
		{
			EPI_write_dat(0xff);
		}
		EPI_write_cmd(0x13);	      //Transfer new data
		for(i=0;i<1280;i++)
		{
			EPI_write_dat(*data);
			data++;
		}
	Updata();
			 		
}	
void Full_image_Clean(void){ 
	  unsigned int i;
		EPI_write_cmd(0x10);
		for(i=0;i<1280;i++)
		{
			EPI_write_dat(0xff);
		}
		EPI_write_cmd(0x13);	       //Transfer new data
		for(i=0;i<1280;i++)
		{
			EPI_write_dat(0xff);
		}
	Updata();
			 		
}
void Part_image(const unsigned char *data_old,const unsigned char *data_new){
	unsigned int i;
	EPI_write_cmd(0x91);			//resolution setting
	EPI_write_cmd(0x90);			//resolution setting
	EPI_write_dat (0);       	 
	EPI_write_dat (79);		
	EPI_write_dat (0);
	EPI_write_dat (127);
	EPI_write_dat (0x00);

	EPI_write_cmd(0x10);
	for(i=0;i<1280;i++)
	{
		EPI_write_dat(*data_old);
		data_old++;
	}
	EPI_write_cmd(0x13);	       //Transfer new data
	for(i=0;i<1280;i++)
	{
		EPI_write_dat(*data_new);
		data_new++;
	}
 Updata();
	
}
void Part_image_first(const unsigned char *data_new){
	unsigned int i;
	EPI_write_cmd(0x91);			//resolution setting
	EPI_write_cmd(0x90);			//resolution setting
	EPI_write_dat (0);       	 
	EPI_write_dat (79);		
	EPI_write_dat (0);
	EPI_write_dat (127);
	EPI_write_dat (0x00);

 
	EPI_write_cmd(0x10);
	for(i=0;i<1280;i++)
	{
		EPI_write_dat(0xff);
	}
	EPI_write_cmd(0x13);	         //Transfer new data
	for(i=0;i<1280;i++)
	{
		EPI_write_dat(*data_new);
		data_new++;
	}
 Updata();
	
}
void Full_lut_bw(void){
	unsigned int count;
	EPI_write_cmd(0x23);
	for(count=0;count<42;count++)	     
	{
	EPI_write_dat(lut_w1[count]);
	}    
	
	EPI_write_cmd(0x24);
	for(count=0;count<42;count++)	     
	{
	EPI_write_dat(lut_b1[count]);
	}          
}

void Part_lut_bw(void){
	unsigned int count;
	EPI_write_cmd(0x23);
	for(count=0;count<42;count++)	     
	{
	EPI_write_dat(lut_w[count]);
	}    
	
	EPI_write_cmd(0x24);
	for(count=0;count<42;count++)	     
	{
	EPI_write_dat(lut_b[count]);
	}          
}
