/*
 * sleep_timer.h
 *
 *  Created on: May 31, 2022
 *      Author: Dustin Westaby
 */

#ifndef INC_SLEEP_TIMER_H_
#define INC_SLEEP_TIMER_H_

#include <Arduino.h>

#define SLEEP_TIMEOUT 600000 // 10 mins

void reset_sleep_timer(); //call for user interaction

bool check_sleep_timer();

#endif /* INC_BUTTONS_H_ */
