# EPIstm8l Library (WIP)
E paper interfacing (EPI) Library for stm8l for interfacing with GDEW0102I4FC 1.02 inch Flexible E paper (or E ink) display from Good display.

I want too !
= 
Here's the link. 
The Display : 
```
https://www.aliexpress.com/item/32974516613.html?spm=a2g0o.productlist.0.0.4abf3889m5KCzP&algo_pvid=743fde42-e631-4a9a-b454-289185d4619b&algo_expid=743fde42-e631-4a9a-b454-289185d4619b-0&btsid=e5067c61-f2ee-48b7-8c97-dc2a50e34fe8&ws_ab_test=searchweb0_0,searchweb201602_10,searchweb201603_55
```
The adapter : 
```
https://www.aliexpress.com/item/32954921759.html?spm=a2g0o.detail.1000013.8.f59c11c677UcS2&gps-id=pcDetailBottomMoreThisSeller&scm=1007.13339.146401.0&scm_id=1007.13339.146401.0&scm-url=1007.13339.146401.0&pvid=9c9b8980-8d54-483b-b28f-6d0d2efd0d21
```

Requirement 
=
0. Brain and Linux pc pre-installed with the sdcc and stm8flash 
1. STM8L151F3. I use this one : https://www.ebay.com/itm/323104121862
2. 1.02 inch EP display from link above.
3. the display adaper from link above too.
4. Any cheap SWIM capable programmer ST-link like the chinese clone.
5. A bunch of jumpers wire.
6. Pin header for STM8l breakout board (1.) OPTIONAL.
7. breadboard OPTIONAL.

Installation Guide
=
1. git clone https://github.com/TiNredmc/stm8l_sdcc_template
2. git clone https://github.com/TiNredmc/EPIstm8l
3. cp EPIstm8l/* stm8l_sdcc_template/lib/
4. cd stm8l_sdcc_template/code/EPI/
5. connect the mcu to STlink then run make all && make flash
6. connect the jumper wire by following the bellow instruction

Connecting Up 
=
```
 * E paper connection:
 * from Display adapter -> MCU
 * DIN -> PB7
 * CLK -> PB6
 * CS  -> PB5
 * DC  -> PB4
 * RST -> PB3
 * BUSY-> PB2
 ```
 YOU MUST USE SAME POWER LINE BOTH DISPLAY AND MCU, FROM 2.6 to 3.3 volt (+- 0.4). 
