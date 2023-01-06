/*
 * audio_player.h
 *
 *  Created on: Jan 04, 2023
 *      Author: Dustin Westaby
 */

#ifndef INC_AUDIO_PLAYER_H_
#define INC_AUDIO_PLAYER_H_

#include <Arduino.h>

void init_audio_player(uint8_t led_scanner_pin_1); //set to 0 to disable animation
void start_audio_player(uint8_t track);
void start_loop_audio_player(uint8_t track);
void stop_audio_player();
bool check_audio_status(int expected);

#endif /* INC_AUDIO_PLAYER_H_ */
