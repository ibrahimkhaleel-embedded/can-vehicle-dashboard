/*
 * File:   main.c
 * Author: USER
 *
 * Created on 28 October, 2025, 8:51 AM
 */


#include <xc.h>
#include "clcd.h"
#include "can.h"
#include "msg_id.h"
#include "main.h"

void init_config() {
    init_clcd();
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
    RB0 = 0;
    RB1 = 0;
    RB6 = 0;
    RB7 = 0;
    init_can();
    clcd_print("CAN BASED AUTOMATIVE DASHBOARD", LINE1(0));
}

void main(void) {
    init_config();
    uint16_t msg_id;
    uint8_t data[6];
    uint8_t len, once = 1;
    unsigned int count = 0, wait = 0;
    clcd_print("SPD GER RPM  IND", LINE1(0));
    while (1) {
        can_receive(&msg_id, data, &len);
        if (msg_id == SPEED_MSG_ID) {
            clcd_print(data, LINE2(0));
        } else if (msg_id == GEAR_MSG_ID) {
            clcd_print(data, LINE2(4));
        } else if (msg_id == RPM_MSG_ID) {
            clcd_print(data, LINE2(8));
        } else if (msg_id == INDICATOR_MSG_ID) {
            //clcd_print(data, LINE2(13));
            if (data[0] == 'L') {
                clcd_print("<--", LINE2(13));
                RB6 = 0;
                RB7 = 0;
                once = 1;
                if (count++ > 200) {

                    RB0 = !RB0;
                    RB1 = !RB1;
                    count = 0;
                }
            } else if (data[0] == 'R') {
                clcd_print("-->", LINE2(13));
                RB0 = 0;
                RB1 = 0;
                once = 1;

                if (count++ > 200) {
                    RB6 = !RB6;
                    RB7 = !RB7;
                    count = 0;
                }
            } else if (data[0] == 'H') {
            clcd_print("<->", LINE2(13));
                if (once == 1) {
                    RB0 = RB1 = RB6 = RB7 = 0;
                    once = 0;
                }
                if (count++ > 200) {
                    RB0 = !RB0;
                    RB1 = !RB1;
                    RB6 = !RB6;
                    RB7 = !RB7;
                    count = 0;
                }
            } else if (data[0] == 'O') {
                clcd_print("OFF", LINE2(13));
                once = 1;
                PORTB = 0x00;

            }
        }
    }
    return;
}
