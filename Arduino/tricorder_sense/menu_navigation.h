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
   GO_TO_SLEEP = 0,
   SLEEPING,
   INITILIZATION,
   
   SYSTEM_NO_CHANGE_MODES, //entries above this line are special
   
   MENU_SCREEN_WRAP_LOW,
   MAIN_SCREEN,
   RGB_SCREEN,
   CLIMATE_SCREEN,
   MICROPHONE_SCREEN,
   BATTERY_SCREEN,
   MENU_SCREEN_WRAP_HIGH,
   
   HIDDEN_EXIT_GO_HOME, //entries below this line, can only be exited to home
   
   HIDDEN_THERMAL_SCREEN,
   HIDDEN_TOM_SERVO_SCREEN,
   HIDDEN_LIGHTING_DETECTOR_SCREEN,
};

#define MENU_FIRST_ENTRY   MAIN_SCREEN

#define MENU_HIGH_WRAP_AROUND MAIN_SCREEN
#define MENU_LOW_WRAP_AROUND  BATTERY_SCREEN

void process_menu_selection();
void set_software_state(uint8_t new_state);
uint8_t get_software_state();

#endif
