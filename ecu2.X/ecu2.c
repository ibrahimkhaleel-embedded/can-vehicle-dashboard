#include <xc.h>
#include "adc.h"
#include "main.h"
#include "digital_keypad.h"
#include "ssd_display.h"
#include "can.h"
#include "msg_id.h"

//static unsigned char digit[] = { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned int count;
void get_rpm(void)
{
    uint8_t ssd[5];
    unsigned int rpm;
    rpm = read_adc(CHANNEL4) * 5.866;
    ssd[0] = ((rpm / 1000) % 10) + '0';
    ssd[1] = ((rpm / 100) % 10) + '0';
    ssd[2] = ((rpm / 10) % 10) + '0';
    ssd[3] = ((rpm / 1) % 10) + '0';
    ssd[4] = '\0';
    can_transmit(RPM_MSG_ID, ssd, 5);
}


void get_indicator(void)
{
    static unsigned int key, flag = 3;
    unsigned char event[4][4] = {"LEF", "RIG", "HAZ", "OFF"};
    key = read_digital_keypad(STATE_CHANGE);
    if(key == SWITCH1)
    {
        flag = 0;
    }
    else if(key == SWITCH2)
    {
        flag = 1;
    }
    else if(key == SWITCH3)
    {
        flag = 2;
    }
    else if(key == SWITCH4)
    {
        flag = 3;
        
    }
   can_transmit(INDICATOR_MSG_ID, event[flag], 4);
}