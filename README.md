# Tiny-Clock-Trinket
A small clock with two buttons for displaying messages.

## Parts required:
1. ESP8266-MOD
2. 1.3" OLED Screen.
3. 3.6V Battery
4. Battery charging module
5. LM1117 Module
6. DS3231 Chip
7. PCB 

## Functionality:
- The trinket will display time and date in idle state.
- Two types of messages can be displayed:
  - One is dispayed when only B1 is pressed.
  - The other one is displayed when B1 is pressed while B2 is already pressed.
  - Personally, I made it so that these two events have randomly chosen messages.


## Choice of microcontroller:
This project does not have wifi yet. The ESP8266 chip was used because I had an extra one lying around. The current fucntionality can be achieved by pretty much any controller.
