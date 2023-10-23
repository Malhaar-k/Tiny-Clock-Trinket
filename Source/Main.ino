/* Author: Malhaar Karandikar
* Made for Tiny_Clock_Trinket
*/
/*
* Note the LED in the circuit has not been used in this version
*/


#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <DS3231.h>
#include "animation.h" //This file has an animation of a heart beating 


#define RAND_POOL     4 


#define heart_width 128
#define heart_height 32


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Initialise 1.3 OLED Sreen
// U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
uint8_t i = 0;
uint8_t Light_mode = 0; 
char Time[] = "00:00";
char Date[] = "00/00";
RTClib myRTC;
uint8_t resetFlag = 0;

//Interrupt code begin
ICACHE_RAM_ATTR void LED_State_Change(){
  Serial.println("Interrupt Triggered");

  if(digitalRead(14)){
    Serial.println("Second page triggered");
    resetFlag = 2;
  }
  resetFlag = resetFlag == 0? 1: resetFlag;

}


//Interrupt code end

//Function definitions begin
void drawAnimation(uint8_t x, uint8_t y); // Draws animations from animation.h

void drawCircAnimation(void); // Intro animation for the page one

void drawCircAnimationRev(void); // Exit animation for the page one


void mainpage(void); // Page that shows date and time.

void page_one(void);

void page_two(void);
//Function definition end


void setup() {
  u8g2.begin();
  // Wire.begin();
  pinMode(14, INPUT); //GPIO 14
  pinMode(12, INPUT); //GPIO 12
  //Add another button
  attachInterrupt(digitalPinToInterrupt(12), LED_State_Change, RISING);


  Serial.begin(115200);
  
  Serial.println("Reached");
  
}

void loop() {
    switch(resetFlag){
      case 1:
      page_one();
      resetFlag = 0;
      break;
      case 2:
      Serial.print("Page two triggered");
      page_two();
      resetFlag = 0;
      break;
      default:
      break;
    }

    mainpage();
    // Serial.println("Keep alive");
    delay(200);

}

void mainpage(void){
    DateTime now = myRTC.now();


    sprintf(Time, "%02d:%02d", now.hour(), now.minute());
    sprintf(Date, "%02d/%02d", now.day(), now.month());

    const char * a = Time; //Prints time as a button
    const char * b = Date;
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_courB24_tf);
    u8g2.drawButtonUTF8(66, 30, U8G2_BTN_HCENTER|U8G2_BTN_BW2, 110,  2,  4, a );
    Serial.println(Time);
    // Serial.printf("\n %d:%d \n", hr, mnt);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.drawStr(48,60, Date);
    

    //Display mainpage end here
    u8g2.sendBuffer();

}

void page_one(void){

  
  drawCircAnimation();
  u8g2.clearDisplay();
 
  //Add page one animation/messages below
unsigned int randint = random(RAND_POOL); //Get a random value between 0 and RAND_POOL
  switch(randint){
    case 1: //Fill the cases
    break;

    default:
    break;
  }
  
  
  //Display the messages
  u8g2.sendBuffer();
  delay(2000);
  resetFlag = 0;
  drawCircAnimationRev();
  
}

void page_two(void){ //Page two does not have any specific animation. Feel free to add one on your own!
  
  u8g2.clearDisplay();
 
 
  //Add page two animation/messages below
unsigned int randint = random(6); //Get a random number between 0 and 6
  switch(randint){
    case 1: //Fill the cases
    break;

    default:
    break;
  }

}
void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void drawAnimation(uint8_t x, uint8_t y) { //Animation drawing

  for(int x = 2; x < 7 ; x ++){
    u8g2.clearBuffer();
    u8g2.drawXBMP( x, y, heart_width, heart_height, heart_bits[x]);
    u8g2.sendBuffer();
    delay(100);
  }
    for(int x = 6; x >= 2 ; x --){
    u8g2.clearBuffer();
    u8g2.drawXBMP( x, y, heart_width, heart_height, heart_bits[x]);
    u8g2.sendBuffer();
    delay(100);
  }  
}

void drawCircAnimationRev(void){
    u8g2.clearBuffer();
    for(int r = 40; r > 7; r -= 4){
    u8g2.drawCircle(63, 32, r);
    u8g2.sendBuffer();
    delay(100);
    }

}

void drawCircAnimation(void){
    u8g2.clearBuffer();
    for(int r = 8; r < 41; r += 4){
    u8g2.drawCircle(63, 32, r);
    u8g2.sendBuffer();
    delay(100);
    }
}

void drawRectAnimation(void){
    u8g2.clearBuffer();
    for(int r = 8; r < 40; r += 8){
    int less = r -4;
    u8g2.drawRBox(63-r, 31-r, less, less/2, 4);
    u8g2.sendBuffer();
    delay(200);
    u8g2.drawRFrame(63-r, 31-r, r, r/2, 4);
    u8g2.sendBuffer();
    delay(200);
    }
}
