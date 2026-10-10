#include<xc.h>
#include "adc.h"
#include "clcd.h"
#include "digital_keypad.h"
#include "main.h"
#include "msg_id.h"
#include "can.h"

void get_speed(void)
{
    unsigned int speed;
    uint8_t data[3];
    speed = read_adc(CHANNEL4) / 10.33;
    //clcd_print("SPEED", LINE1(0));
    data[0] = ((speed / 10) % 10) + '0';  
    data[1] = (speed % 10) + '0';
    data[2] = '\0';
   // clcd_putch((speed/10 % 10) + 48, LINE2(0));
   // clcd_putch((speed % 10) + 48, LINE2(1));
    can_transmit(SPEED_MSG_ID, data, 3);
}

void get_gear(void)
{
    unsigned char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C_"};
    static unsigned int index = 0, key, flag = 0;
    key = read_digital_keypad(STATE_CHANGE);
    
    if(flag == 0)
    {
        
        if(key == SWITCH1)
        {
            if(index < 7)
            {
                index++;
            }
        }
        else if(key == SWITCH2)
        {
            if(index > 1)
            {
                index--;
            }
        }
        else if(key == SWITCH3)
        {
            index = 8;
            flag = 1;
        }
    }
    else if(flag == 1)
    {
        if(key == SWITCH1 || key == SWITCH2)
        {
            index = 1;
            flag = 0;
        }
    }
    clcd_print("GEAR", LINE1(8));
    clcd_print(event[index], LINE2(8));
}
