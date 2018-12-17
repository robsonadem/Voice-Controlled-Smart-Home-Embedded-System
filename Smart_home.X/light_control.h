/* 
 * File:   light_control.h
 * Author: ademr
 *
 * Created on November 15, 2018, 9:00 AM
 */

#ifndef LIGHT_CONTROL_H
#define	LIGHT_CONTROL_H

void light_init();
void light_switch(int control_signal);
int get_light_status();
#endif