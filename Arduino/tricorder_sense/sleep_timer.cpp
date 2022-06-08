/*
 * sleep_timer.cpp
 *
 *  Created on: May 31, 2022
 *      Author: Dustin Westaby
 */

#include "sleep_timer.h"

unsigned long sleep_timer = 0;


void reset_sleep_timer()
{
  sleep_timer = millis();
}

bool check_sleep_timer()
{
  return ((millis() - sleep_timer) > SLEEP_TIMEOUT);
}
