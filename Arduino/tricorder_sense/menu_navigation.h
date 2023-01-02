/*
 * menu_navigation.h
 *
 *  Created on: May 30, 2022
 *      Author: Dustin Westaby
 */

#ifndef INC_MENU_NAVIGATION_H_
#define INC_MENU_NAVIGATION_H_

#include <Arduino.h>

/* --------------------- */
/*   SW Modes            */
/* --------------------- */
enum menu_page_order
{
   /*  0 */ GO_TO_SLEEP = 0,
   /*  1 */ SLEEPING,
   /*  2 */ INITILIZATION,
   
   /*  3 */ SYSTEM_NO_CHANGE_MODES, //entries above this line are special
   
   /*  4 */ MENU_SCREEN_WRAP_LOW,
   /*  5 */ MAIN_SCREEN,
   /*  6 */ RGB_SCREEN,
   /*  7 */ CLIMATE_SCREEN,
   /*  8 */ MICROPHONE_SCREEN,
   /* 10 */ MENU_SCREEN_WRAP_HIGH,
   
   /* 11 */ HIDDEN_EXIT_GO_HOME, //entries below this line, can only be exited to home
   
   /* 12 */ HIDDEN_THERMAL_SCREEN,
   /* 13 */ HIDDEN_TOM_SERVO_SCREEN,
   /* 14 */ HIDDEN_LIGHTING_DETECTOR_SCREEN,
   
   /*  9 */ BATTERY_SCREEN, //TBD, UNUSED
   
   /* 15 */ LAST_MENU_ITEM,
};

#define MENU_HIGH_WRAP_AROUND MAIN_SCREEN
#define MENU_LOW_WRAP_AROUND  MICROPHONE_SCREEN //Note: Update this if you add a menu page

void process_menu_selection();
void set_software_state(uint8_t new_state);
uint8_t get_software_state();

#endif
