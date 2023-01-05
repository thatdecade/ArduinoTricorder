/*
 * audio_player.cpp
 *
 *  Created on: Jan 04, 2022
 *      Author: Dustin Westaby
 */

//#define DEBUGSERIAL

#include "audio_player.h"

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

void printDetail(uint8_t type, int value);

SoftwareSerial mySoftwareSerial(PIN_SERIAL1_RX, PIN_SERIAL1_TX); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

bool player_online = true; //TBD, just force detection on for now

void init_audio_player(uint8_t led_scanner_pin_1)
{
  mySoftwareSerial.begin(9600);

#ifdef DEBUGSERIAL
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
#endif
  for(uint8_t i=0; i < 4; i++ )
  {  //Use softwareSerial to communicate with mp3.
    if(myDFPlayer.begin(mySoftwareSerial))
    {
      break;
    }
    
    if(led_scanner_pin_1 != 0)
    {
      analogWrite(led_scanner_pin_1 + i, 0);
    }
#ifdef DEBUGSERIAL
    Serial.print(F("Unable to begin DFPLayer, re-attempt :"));
    Serial.println(i);
#endif
    delay(1000);
  }
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
#ifdef DEBUGSERIAL
  if (myDFPlayer.available()) 
  {
    Serial.println(F("DFPlayer online."));
  }
  else
  {
    Serial.println("DFPlayer Offline");
  }
#endif
}

void start_audio_player(uint8_t track)
{
  if (player_online) 
  {
#ifdef DEBUGSERIAL
    Serial.print("Play Audio: ");
    Serial.println(track);
#endif
    myDFPlayer.play(track);
  }
}

void start_loop_audio_player(uint8_t track)
{
  if (player_online) 
  {
#ifdef DEBUGSERIAL
    Serial.print("Start looping track: ");
    Serial.println(track);
#endif
    myDFPlayer.play(track);
    myDFPlayer.loop(track);
  }
}

void stop_audio_player()
{
  if (player_online) 
  {
#ifdef DEBUGSERIAL
    Serial.println("Stop Sounds");
#endif
    myDFPlayer.stop();
  }
}
bool check_audio_status(int expected)
{
  bool status_matches_expected = false;

  if (player_online) 
  {
    int value = myDFPlayer.readState(); //readState: 1 = Playing, 0 = Stopped
    if (value == -1) 
    {  //Error while Reading.
#ifdef DEBUGSERIAL
      Serial.print("Player Error: ");
      printDetail(myDFPlayer.readType(), myDFPlayer.read());
#endif
      status_matches_expected = true;
    }
    else
    { //Successfully get the result.
#ifdef DEBUGSERIAL
      Serial.print("Player expected: ");
      Serial.print(expected);
      Serial.print(", Actual: ");
      Serial.print(value);
      Serial.print(", Play Status: ");
      Serial.println((value == expected));
#endif
      status_matches_expected = (value == expected);
    }

#ifdef DEBUGSERIAL
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
#endif
  }
  else
  {
#ifdef DEBUGSERIAL
    Serial.println("Player Offline");
#endif
  }

  return status_matches_expected;
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
