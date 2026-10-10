/*
 * File:   main.c
 * Author: USER
 *
 * Created on 28 October, 2025, 8:51 AM
 */


#include <xc.h>
#include "adc.h"
#include "ssd_display.h"
#include "digital_keypad.h"
#include "main.h"
#include "can.h"
#include "clcd.h"

void init_config()
{
    init_digital_keypad();
    init_adc();
//    init_clcd();
    init_can();
}
void main(void) 
{
    init_config();
    while(1)
    {
        get_speed(); 
        __delay_us(100);
        get_gear();
        __delay_us(100);

    }
    return;
}
