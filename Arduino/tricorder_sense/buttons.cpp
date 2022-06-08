/*
 * buttons.c
 *
 *  Created on: Jul 15, 2020
 *      Author: Dustin Westaby
 */

#include "buttons.h"


#define GEO_BUTTON_1_PIN        (11) // GEO
#define MET_BUTTON_2_PIN        (12) // MET
#define BIO_BUTTON_3_PIN        (13) // BIO
#define CAM_BUTTON_BOARD        (7)  // PIN_BUTTON1 - CAMERA / Board Button

byte pinMap_buttons[NUMBER_OF_BUTTONS] =
{
  GEO_BUTTON_1_PIN,  // GEO_BUTTON
  MET_BUTTON_2_PIN,  // MET_BUTTON
  BIO_BUTTON_3_PIN,  // BIO_BUTTON
  CAM_BUTTON_BOARD,  // CAM_BUTTON
};

byte button_state[NUMBER_OF_BUTTONS] = 
{
  IS_NOT_PRESSED,  // GEO_BUTTON
  IS_NOT_PRESSED,  // MET_BUTTON
  IS_NOT_PRESSED,  // BIO_BUTTON
  IS_NOT_PRESSED,  // CAM_BUTTON
};

byte get_button_state(byte button)
{
  return button_state[button];
}

void poll_input_switches()
{
  static bool last_button_read[]    = {false, false, false, false};
  static bool current_button_read[] = {false, false, false, false};

  for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++)
  {
    /* read digital active low button signal */
    current_button_read[i] = !digitalRead(pinMap_buttons[i]);

    if (!last_button_read[i] && current_button_read[i])
    {
      //button was just pressed
      button_state[i] = IS_PRESSED;
    }
    else if  (last_button_read[i] && current_button_read[i])
    {
      //button is being held
      button_state[i] = IS_HELD;
    }
    else if (last_button_read[i] && !current_button_read[i])
    {
      //button was just released
      button_state[i] = WAS_RELEASED;
    }
    else
    {
      button_state[i] = IS_NOT_PRESSED;
    }

    last_button_read[i] = current_button_read[i];
  }
}

void enable_input_switches()
{
  for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++)
  {
		pinMode(pinMap_buttons[i], INPUT);
	}
}

void disable_input_switches()
{
  for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++)
  {
		pinMode(pinMap_buttons[i], OUTPUT);
		digitalWrite(pinMap_buttons[i], HIGH);
	}
}
