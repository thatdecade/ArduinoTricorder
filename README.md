# ArduinoTricorder
Interactive Tricorder Prop with real environmental sensors

Based on the original work by lambtor: https://github.com/lambtor/ArduinoTricorder

# Features

* Animated Lights and Sounds, Interactive Menus
* Thermal Camera (MLX90640)
* Climate Sensors: Humidity (SHT), Temperature and barometric pressure (BMP280)
* Color Sensor and Distance Measurement (APDS9960)
* Microphone (PDM) FFT bargraph
* Auto Sleep when Door is Closed, uses Magnetometer (LIS3MDL)

# Usage

On Power up, the main screen is displayed and the sound effects start.  

* To navigate the info pages, press left or right.  Pressing center goes home.
* To toggle sound effects, hold the left button.
* Close the lid or wait 10 mins to put to sleep, low power mode.  Open the lid or press a button to wake up.

Thermal Camera: To access the video, press the button marked User SW on the Feather board.

# Part List

TBD

# 3D Printing

The case assembly notes are on printables: https://www.printables.com/model/225964-printability-remix-of-arduino-tricorder

# Wiring Diagram

Battery, Charger Jack, and Power Switch not shown.  See Adafruit Feather nRF52840 Sense docs.

I used a 2500mAh battery, but smaller would work fine too.  1000mAh - 2500mAh is recommended.

![arduinotricorder_fritzing_diagram_bb](https://user-images.githubusercontent.com/6401110/210834237-d9f2d716-db72-4638-8847-c74d828b1951.png)

# Bugs

* I used D13 for the BIO button input and needed to remove the Arduino's D13 onboard LED.  

On the Adafruit Feather nRF52840 Sense board, D13 is wired to an onboard LED (similar to other arduino boards).  D13 worked at first using INPUT_PULLUP, but eventually stopped working.  I measured the voltage on this pin at 1.9V when the button was unpressed, and 0.2V for pressed.  The nRF52840 requires at least 0.7xVcc to detect a digital high.  1.9V < 2.3V, so the chip thought the button was stuck pressed.  The LED + Resistor and INPUT_PULLUP were creating a voltage clamp at the diode's Forward Voltage.

My fix was unsoldering the D13 LED.  A better fix would be moving the BIO button input wire and reserving D13 as output only.

* Communication with the DFPlayer is inconsistant.

Likely due to me using a clone of the DFPlayer.  Work around is for the arduino to query the status from the DFPlayer every 500ms, then if the player is not playing when it should (or vice versa) we send the play/stop command again.  So if there is a glitch in the audio start / loop / stop, it is fixed quickly.

* Speaker Volume and Screen Flicker, reduce volume and use a larger battery

When the DFPlayer is set to max volume and the tricorder is powered by USB, I noticed the screen flickering from the speaker amp.  Switching to battery, the screen appears ok.
