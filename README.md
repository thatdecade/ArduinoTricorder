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
* Close the lid to put to sleep, low power mode.

Thermal Camera: To access the video, press the button marked User SW on the Feather board.

# 3D Printing

The case assembly notes are on printables: https://www.printables.com/model/225964-printability-remix-of-arduino-tricorder

# Wiring Diagram

Battery, Charger Jack, and Power Switch not shown.  See Adafruit Feather nRF52840 Sense docs.

I used a 2500mAh battery, but smaller would work fine too.  1000mAh - 2500mAh is recommended.

![arduinotricorder_fritzing_diagram_bb](https://user-images.githubusercontent.com/6401110/210834237-d9f2d716-db72-4638-8847-c74d828b1951.png)
