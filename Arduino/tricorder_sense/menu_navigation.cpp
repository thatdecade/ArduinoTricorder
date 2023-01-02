/*
 * menu_navitation.c
 *
 *  Created on: Jul 15, 2020
 *      Author: Dustin Westaby
 */

#include "buttons.h"
#include "menu_navigation.h"

#define MENU_ACCESS_DELAY_IN_MILLIS 1000

byte software_state = INITILIZATION;
byte software_state_processed = true;

//prototypes
void button_clicked(byte button);
void button_held(byte button);
void process_left_click();
void process_right_click();
void process_center_click();
void process_camera_click();
void process_left_hold();
void process_center_hold();
void process_right_hold();
void process_camera_hold();

enum
{
   PROCESSED,
   NOT_PROCESSED
};

void process_menu_selection()
{
  static long last_menu_interaction_timestamp[NUMBER_OF_BUTTONS] = {0, 0, 0, 0};
  static byte last_mode_button_state[NUMBER_OF_BUTTONS] = {NOT_PROCESSED, NOT_PROCESSED, NOT_PROCESSED, NOT_PROCESSED};
  byte current_button_state;

  for( byte i = 0; i < NUMBER_OF_BUTTONS; i++)
  {
    current_button_state = get_button_state(i);
    
    if(current_button_state == WAS_RELEASED) // WAS_RELEASED = 2
    {
        //CLICKED ACTION

  Serial.print("Button ");
  Serial.print(i);
  Serial.print(" is ");
  Serial.println(current_button_state);
  
        //Note: action taken on WAS_RELEASED instead of IS_PRESSED to prevent extra clicks during button holds

        last_menu_interaction_timestamp[i] = millis();

        if(last_mode_button_state[i] == NOT_PROCESSED)
        {
            //one action per press / hold
            for( byte j = 0; j < NUMBER_OF_BUTTONS; j++)
            {
              last_mode_button_state[j] = PROCESSED;
            }
            
  Serial.print("Button Clicked ");
  Serial.println(i);
  
            button_clicked(i);
        }
    }
    else if ( ( current_button_state == IS_HELD ) &&
              ( last_menu_interaction_timestamp[i] + MENU_ACCESS_DELAY_IN_MILLIS < millis() ) )
    {
        //HELD ACTION

        last_menu_interaction_timestamp[i] = millis();

        if(last_mode_button_state[i] == NOT_PROCESSED)
        {
            //one action per press / hold
            for( byte j = 0; i < NUMBER_OF_BUTTONS; i++)
            {
              last_mode_button_state[i] = PROCESSED;
            }

            if( (get_button_state(MET_BUTTON) == IS_HELD) &&
                (get_button_state(BIO_BUTTON) == IS_HELD) )
            {
                set_software_state(HIDDEN_TOM_SERVO_SCREEN);
                break;
            }
            else
            {
              button_held(i);
            }
        }
    }
    else if (current_button_state == IS_NOT_PRESSED)
    {
        //reset timers
        last_menu_interaction_timestamp[i] = millis();
        last_mode_button_state[i] = NOT_PROCESSED;
    }

  }// end for loop
}


void button_clicked(byte button)
{      
      
  // call clicked action handler
  switch(button)
  {
    case GEO_BUTTON:
      process_left_click();
      break;
    case MET_BUTTON:
      process_center_click();
      break;
    case BIO_BUTTON:
      process_right_click();
      break;
    case CAM_BUTTON:
      process_camera_click();
      break;
    default:
      break; //do nothing
  }
}

void button_held(byte button)
{      
  // call clicked action handler
  switch(button)
  {
    case GEO_BUTTON:
      process_left_hold();
      break;
    case MET_BUTTON:
      process_center_hold();
      break;
    case BIO_BUTTON:
      process_right_hold();
      break;
    case CAM_BUTTON:
      process_camera_hold();
      break;
    default:
      break; //do nothing
  }
}

void process_left_click()
{
  switch (software_state)
  {
      case GO_TO_SLEEP:
      case SLEEPING:
      case INITILIZATION:
        //wake up
        set_software_state(INITILIZATION);
        break;
        
      case MAIN_SCREEN:
      case RGB_SCREEN:
      case CLIMATE_SCREEN:
      case MICROPHONE_SCREEN:
      case BATTERY_SCREEN:
        //menu_navigation_back
        set_software_state(software_state - 1);
        break;
        
      case HIDDEN_THERMAL_SCREEN:
      case HIDDEN_TOM_SERVO_SCREEN:
      case HIDDEN_LIGHTING_DETECTOR_SCREEN:
        set_software_state(MAIN_SCREEN);
        break;
        
      default:
        //do nothing
        break;
  }
}

void process_right_click()
{
  switch (software_state)
  {
      case GO_TO_SLEEP:
      case SLEEPING:
      case INITILIZATION:
        //wake up
        set_software_state(INITILIZATION);
        break;
        
      case MAIN_SCREEN:
      case RGB_SCREEN:
      case CLIMATE_SCREEN:
      case MICROPHONE_SCREEN:
      case BATTERY_SCREEN:
        //menu_navigation_forward
        set_software_state(software_state + 1);
        break;
        
      case HIDDEN_THERMAL_SCREEN:
      case HIDDEN_TOM_SERVO_SCREEN:
      case HIDDEN_LIGHTING_DETECTOR_SCREEN:
        set_software_state(MAIN_SCREEN);
        break;
        
      default:
        //do nothing
        break;
  }
}

void process_center_click()
{
  //go home
  set_software_state(MAIN_SCREEN);
}

void process_camera_click()
{
  static uint8_t save_state = MAIN_SCREEN;
  
  switch (software_state)
  {
      case GO_TO_SLEEP:
      case SLEEPING:
      case INITILIZATION:
        //wake up
        set_software_state(INITILIZATION);
        break;
        
      case MAIN_SCREEN:
      case RGB_SCREEN:
      case CLIMATE_SCREEN:
      case MICROPHONE_SCREEN:
      case BATTERY_SCREEN:
      case HIDDEN_TOM_SERVO_SCREEN:
      case HIDDEN_LIGHTING_DETECTOR_SCREEN:
        //launch camera
        save_state = software_state;
        set_software_state(HIDDEN_THERMAL_SCREEN);
        break;
        
      case HIDDEN_THERMAL_SCREEN:
        //return to previous screen
        set_software_state(save_state);
        
      default:
        //do nothing
        break;
  }
}

void process_left_hold()
{
  //TBD
}

void process_center_hold()
{
  //TBD
}

void process_right_hold()
{
  //TBD
}

void process_camera_hold()
{
  //TBD
}

/* ******************************* */

void set_software_state(uint8_t new_state)
{
  //validate state
  if(new_state < LAST_MENU_ITEM)
  {
    software_state = new_state;
  }
  
  //handle wrap around
  switch (software_state)
  {
    case MENU_SCREEN_WRAP_LOW:
      software_state = MENU_LOW_WRAP_AROUND;
      break;
    case MENU_SCREEN_WRAP_HIGH:
      software_state = MENU_HIGH_WRAP_AROUND;
      break;
    default:
      //do nothing
      break;
  }

  Serial.print("Set state to ");
  Serial.println(software_state);
}

uint8_t get_software_state()
{
  return software_state;
}
