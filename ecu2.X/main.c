/*
 * File:   main.c
 * Author: USER
 *
 * Created on 28 October, 2025, 8:51 AM
 */


#include <xc.h>
#include "adc.h"
#include "main.h"
#include "digital_keypad.h"
#include "ssd_display.h"
#include "can.h"

void init_config()
{
    init_ssd_control();
    init_digital_keypad();
    init_adc();
    init_led();
    init_can();
}

void main(void) 
{
    init_config();
    while(1)
    {
        get_rpm(); 
        __delay_us(100);
        get_indicator();
        __delay_us(100);
    }
    return;
}
