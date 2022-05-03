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
    int RGB[3];
    Serial.println("Start Reading Value");
    incomingByte = Serial.read();
    if(incomingByte == 78){
        led_number = Serial.read() - 48;
        Serial.println((String)"LED NUMBER: " + led_number);
    }

    bool dataAvailable = true
    while(dataAvailable){

        for(int _ = 0; _ < 3; _++){
            incomingByte = Serial.read();
            Serial.println(incomingByte);
            switch (incomingByte) {
                case 82: // R
                    RGB[0] = gatherValue();
                    break;
                case 71: // G
                    RGB[1] = gatherValue();
                    break;
                case 66: // B
                    RGB[2] = gatherValue();
                    break;
                case 69:
                    dataAvailable = !dataAvailable;
                    break;
            }
        }

        for(int i = 0; i<3; i++){
            Serial.print(RGB[i]);
            Serial.print(", ");
        }

        Serial.println(led_number);
        updateLed(RGB, led_number+1);
        led_number ++;
    }
}

int gatherValue(){
    int color_buffer = 0;
    Serial.println("Gathering Value");
    for (int i = 0; i < 3; ++i) {
        incomingByte = Serial.read() - 48;
        color_buffer = color_buffer + incomingByte * pow(10, 2-i);
    }
    return color_buffer;
}
void updateLed(int RGB[3], int led_number){
    Serial.println("Updating LED");
    leds[led_number].setRGB(RGB[0], RGB[1], RGB[2]);
    FastLED.show();
    delay(30);
}