# ArduinoTricorder
Interactive Tricorder Prop with real environmental sensors

Based on the original work by lambtor: https://github.com/lambtor/ArduinoTricorder

# Features

* Animated Lights and Sounds, Interactive Menus
* Thermal Camera (MLX90640)
* Climate Sensors: Humidity (SHT31), Temperature and barometric pressure (BMP280)
* Color Sensor and Distance Measurement (APDS9960)
* Microphone (PDM) FFT spectrum
* Auto Sleep when Door is Closed, uses Magnetometer (LIS3MDL)

# Usage

On Power up, the main screen is displayed and the sound effects start.  

* To navigate the info pages, press left or right.  Pressing center goes home.
* To toggle sound effects, hold the left button.
* Close the lid or wait 10 mins to put to sleep, low power mode.  Open the lid or press a button to wake up.

Thermal Camera: To access the video, press the button marked User SW on the Feather board.  If you did not install the thermal camera, the tricorder will display an error message.
Press the center button to return home.

# Part List

TBD

# 3D Printing

The case assembly notes are on printables: https://www.printables.com/model/225964-printability-remix-of-arduino-tricorder

# Wiring Diagram

Battery, Charger Jack, and Power Switch not shown.  See Adafruit Feather nRF52840 Sense docs.

I used a 2500mAh battery, but smaller would work fine too.  1000mAh - 2500mAh is recommended.

![arduinotricorder_fritzing_diagram_bb](https://user-images.githubusercontent.com/6401110/210834237-d9f2d716-db72-4638-8847-c74d828b1951.png)

If you want to change any wires, use the pinmap.h file.  

# Software Setup

Follow the adafruit guide for setting up the Feather nRF52840 board package in Arduino. Then begin installing the libraries.
https://learn.adafruit.com/adafruit-feather-sense/arduino-support-setup

1. Copy the MLX90640_API folder from this repo's libraries folder to your arduino's libraries folder.  If you are unsure where this is, open Preferences from the Arduino File menu and look for the sktechbook location. Mine is My Documents\Arduino\libraries.
1. Install the following lilbraries.  Start with the latest versions.
> * Adafruit NeoPixel version 1.10.6
> * Adafruit TinyUSB Library version 1.7.0
> * Adafruit GFX Library version 1.11.3
> * Adafruit BusIO version 1.14.1
> * Adafruit ST7735 and ST7789 Library 
> * Adafruit APDS9960 Library version 1.2.2
> * Adafruit BMP280 Library version 2.6.6
> * Adafruit Unified Sensor version 1.1.6
> * Adafruit SHT31 Library version 2.2.0
> * nRF52840 PDM - Adafruit Fork version 1.0
> * Adafruit Zero FFT Library version 1.0.4
> * Adafruit LIS3MDL version 1.2.1
> * DFRobotDFPlayerMini version 1.0.5
3. Hit the Compile to test everything is as it should be.  If you get any errors, try switching to the version listed above.
4. Plug in the arduino to USB, and select Adafruit Feather nRF52840 Sense as the board, then select the port.
5. Hit Upload.

If all went well, you should see the display come alive.

# Bugs

* I used D13 for the BIO button input and needed to remove the Arduino's D13 onboard LED.  

On the Adafruit Feather nRF52840 Sense board, D13 is wired to an onboard LED (similar to other arduino boards).  D13 worked at first using INPUT_PULLUP, but eventually stopped working.  I measured the voltage on this pin at 1.9V when the button was unpressed, and 0.2V for pressed.  The nRF52840 requires at least 0.7xVcc to detect a digital high.  1.9V < 2.3V, so the chip thought the button was stuck pressed.  The LED + Resistor and INPUT_PULLUP were creating a voltage clamp at the diode's Forward Voltage.

My fix was unsoldering the D13 LED.  A better fix would be moving the BIO button input wire and reserving D13 as output only.

* Communication with the DFPlayer is inconsistant.

Likely due to me using a clone of the DFPlayer.  Work around is for the arduino to query the status from the DFPlayer every 500ms, then if the player is not playing when it should (or vice versa) we send the play/stop command again.  So if there is a glitch in the audio start / loop / stop, it is fixed quickly.

* Speaker Volume and Screen Flicker, reduce volume and use a larger battery

When the DFPlayer is set to max volume and the tricorder is powered by USB, I noticed the screen flickering from the speaker amp.  Switching to battery, the screen appears ok.
