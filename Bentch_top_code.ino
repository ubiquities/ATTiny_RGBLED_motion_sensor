/*Code for nano IC for all bench top function, starting with 2x5 neopixel strings lighting the bentch.
 * with PIR motion sensor with 10 minute timer, once setup could add a button to enter different lighting modes and potentiometer for controll brightness.
 * follow up idea button to play winning/mario level up sound effects
 */

#include <Adafruit_NeoPixel.h>
const byte lightPin = 3;
//int lightState = LOW;
unsigned long previousMillis = 0;
const long interval = 300*1000;  // how long the neopixels will stay on in miliseconds
const byte motionPin = 4;
int motionVal;
const byte numPixels = 18;
int pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel strip(numPixels, lightPin, NEO_GRB + NEO_KHZ800);
uint32_t softwhite = strip.Color(255, 127, 35);
int dt=100;

void setup() {
//Serial.begin(9600);
strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED) 
strip.clear(); // Set all pixel colors to 'off'
}

void loop() {
motionVal=digitalRead(motionPin); 
unsigned long currentMillis = millis(); //check timer for on delay 
//when motion is detected do this shit
if (motionVal == HIGH){
    strip.fill(softwhite, 0); //set neopixel color
    previousMillis = currentMillis; // save the last time motion was detected
} 

// turn LEDs off if timer has has run out
if (currentMillis - previousMillis >= interval) {
    strip.clear();
      }
//Serial.println(currentMillis - previousMillis);
strip.show();
delay(dt);
}
