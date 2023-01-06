/*
 * pinmap.h
 *
 *  Created on: Jan 6, 2023
 *      Author: Dustin Westaby
 */

#ifndef INC_PINMAP_H_
#define INC_PINMAP_H_

/*
 Full arduino pinout for this board is here:
 https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/master/variants/feather_nrf52840_sense/variant.h

  List of Hardware
   - Adafruit Feather nRF52840 Sense
   - LCD
   - Audio FX
   - Neopixels
   - Buttons
   - Sequin LEDs

  I2C OnBoard
  Addr  IRQ  Chip      Type            
  0x61   D3  LSM6DS33  Gyro + Accel   
  0x1C       LIS3MDL   Magnetometer   
  0x44       SHT30     Humidity       
  0x77       BMP280    Temp + Pressure  
  0x39  D36  APDS9960  Light + Gesture + Proximity    
  
  I2C OffBoard
  0x33       MLX90640  Thermal Camera
  
  Pin Assignements
  Pin   Function Device
   A0   Input    Scroll Wheel (Library)
   A2   Output   Left LED Scanner (ALPHA)
   A3   Output   Left LED Scanner (BETA)
   A4   Output   Left LED Scanner (GAMMA)
   A5   Output   Left LED Scanner (DELTA)
   A6   Input    VOLTAGE_MONITOR 
   D4   Output   Board Blue LED
   D5   DC       TFT
   D6   CS       TFT
   D7   Input    Board Button (Camera)
   D8   Data     Board NeoPixels (Front Camera Flash)
   D9   Output   PWM Backlight Control (pull down to turn the backlight off)
   MO   MOSI     TFT
  SCK   SCK      TFT
   RX   Output   DFPlayer TX
   TX   Output   DFPlayer RX
  D10   Data     Cover NeoPixels (PWR, ID, EMRG)
  D11   Input    GEO Button (Left)
  D12   Input    MET Button (Center)
  D13   Input    BIO Button (Right)
  D13   Output   Board Red LED (Unsolder and remove this LED from the feather board or move BIO Button input)
  En    VREG     Enable Power Switch (Short to Ground for OFF)  
  SCL   I2C      Thermal Camera
  SDA   I2C      Thermal Camera
  
  -------------------------------------
  
  Adafruit defines physically labeled pin D2 as pin 2 in its header file, but it does not respond when set as an input by default.
  you will need to modify system_nrf52840.c file by adding
  #define CONFIG_NFCT_PINS_AS_GPIOS (1)
  YOU WILL SEE THIS CONSTANT REFERENCED IN THAT FILE, with compiler-conditional logic around it to actually free up the NFC pins, 
  but only if that constant exists in that file

  -------------------------------------
  
 */
 
/* ************************* */
/* Buttons */
/* ************************* */
#define GEO_BUTTON_1_PIN        (11) // GEO
#define MET_BUTTON_2_PIN        (12) // MET
#define BIO_BUTTON_3_PIN        (13) // BIO
#define CAM_BUTTON_BOARD        (PIN_BUTTON1)  // PIN_BUTTON1 - CAMERA / Board Button

/* ************************* */
/* Scroll Wheel */
/* ************************* */
//only need 1 pin for potentiometer / scroller input. both poles need to be wired to GND and 3v - order doesn't matter
#define PIN_SCROLL_INPUT      PIN_A0

/* ************************* */
/* Lights */
/* ************************* */
#define SCAN_LED_PIN_1        PIN_A2
#define SCAN_LED_PIN_2        PIN_A3
#define SCAN_LED_PIN_3        PIN_A4
#define SCAN_LED_PIN_4        PIN_A5

//neopixel power LED. must use an unreserved pin for this.  PWR, ID, EMRG all use this pin
#define NEOPIXEL_CHAIN_DATAPIN  (10)

// built-in pins: D4 = blue conn LED, 8 = neopixel on board, D13 = red LED next to micro usb port
// commented out lines are pre-defined by the adafruit board firmware
#define NEOPIXEL_BOARD_LED_PIN   (8)

/* ************************* */
/* LCD */
/* ************************* */
// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
//need to use pin 6 for TFT_CS, as pin 20 is analog 7. analog 7 is the only way to get current voltage, which is used for battery %

//MISO is not required for screen to work - this is used by mem card only?
#define TFT_CS                (6)
// SD card select pin
//#define SD_CS       11  //- can't use pin 4 as that is for blue connection led
#define TFT_RST               -1  //disabled
#define TFT_DC                (5)
#define USE_SD_CARD           (0)
#define TFT_BACKLIGHT         (9)

/* ************************* */
/* Misc */
/* ************************* */
//pin 9 is free, as pin_a6 is for vbat and is otherwise known as digital 20
 //INPUT_POWER_PIN. 
 //mnRF52840 is not 5V tolerance, max analog-in is VCC+0.3V or 3.9V, whichever is lower.  
 // The adafruit sense board has a hardwired 50% voltage divider.
#define VOLT_PIN              PIN_A6   

//buttons are defined in buttons.h

//#define PIN_NEOPIXEL         8
//#define BOARD_REDLED_PIN    13
//#define BOARD_BLUELED_PIN    4
//#define LED_RED             13
//#define LED_BLUE             4

#endif /* INC_PINMAP_H_ */
