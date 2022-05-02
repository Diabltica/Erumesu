/*
  Created by Thomas LE NINIVEN 23/04/2022
*/
#include <FastLED.h>

#include <EEPROM.h>

#define PUSH_BUTTON 2
#define RELAY_PIN 4
#define EEPROM_ADR 42
#define NUM_LEDS 48
#define PIN_LED 6

bool a = 0;
int incomingByte = 0; 

CRGBArray<NUM_LEDS> leds;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, PIN_LED>(leds, NUM_LEDS); 
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(PUSH_BUTTON,INPUT);
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON), controlRelay, RISING);
  a = EEPROM.read(EEPROM_ADR);
  
  if(a){
    digitalWrite(RELAY_PIN, HIGH);
  }
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if(incomingByte == 83){
      receiveData();
    }
  }
}

void controlRelay(){
  if(!a){
    a  = true;
    digitalWrite(RELAY_PIN, HIGH);
    EEPROM.write(EEPROM_ADR, a);
  }else if (a){
    a = false;
    digitalWrite(RELAY_PIN, LOW);
    EEPROM.write(EEPROM_ADR, a);
  }
  delay(20);
}

void receiveData(){
    int led_number = 0;
    int color_buffer = 0;
    int RGB[3];
    incomingByte = Serial.read();
    if(incomingByte == 78)
        led_number = Serial.read();

    while(Serial.available() > 0){
      for(int v = 0; v < 3; v++){
        for(int i = 0; i < 3; i++){
          incomingByte = Serial.read() - 48;
          color_buffer = color_buffer + incomingByte * pow(10, i);
        }
        RGB[v] = color_buffer;
        color_buffer = 0;
      }
      updateLed(RGB, led_number);
      led_number ++;
    }
}

void updateLed(int RGB[3], int led_number){
    leds[led_number].setRGB(RGB[0], RGB[1], RGB[2]);
    FastLED.show(); 
    delay(30);
}
