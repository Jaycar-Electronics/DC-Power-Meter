
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// 5/1024, with the 1/8 volt div: 
#define MILLIVOLTS_PER_INT 40

// 5/1024, with the current sensor's 66mV per A 
// milliamps 0.075 per int*

#define MILLIAMPS_PER_INT 75 

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup(){

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
}
void loop(){

    int voltageReading = analogRead(A0);
    int currentReading = analogRead(A1) - 512; //Current reading can be negative, reverse it here.

    long power = MILLIAMPS_PER_INT * MILLIAMPS_PER_INT * voltageReading * currentReading;

    Serial.print("V:");
    Serial.print(voltageReading,DEC);
    Serial.print("|C:");
    Serial.println(currentReading,DEC);

    display.clearDisplay();
    display.setCursor(0,0);
    display.print(voltageReading * MILLIVOLTS_PER_INT);
    display.print(F("mV"));

    display.setCursor(0,18);
    display.print(currentReading * MILLIAMPS_PER_INT );
    display.print(F("mA"));

    display.setCursor(0,36);
    display.print(power/1000.0f); //dislpay as float
    display.print(F("mW"));

    display.display();    

    delay(100);
}
