/*Back lights for drone pegboard, if motion is detected the selected color will ramp up
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// set and define pins
#define PIN        D1  // Data pin for Neopixles 
#define motionPin  D2  // IR motion sensor pin
#define buttonPin  D3  // Pin number for a tactile button

// Neopixle setup and number of LEDS
#define NUMPIXELS 72
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// timer variables
unsigned long previousMillis = 0;
const long interval = 60000*10;  // how long the neopixels will stay on, second digit is minutes

// data buckets
bool buttonState;
bool motionVal;
byte colorGreen = 0; // RGB value variable
byte colorRed = 0; // RGB value variable
byte colorBlue = 0; // RGB value variable
byte level = 0; //use this variable to adjust the brightness
byte activeColor = 0;

// Fade controls
byte fadeIncrament = 1;
byte maxBrightness = 210;
byte fadeInitiator = maxBrightness - 1; //don't change

//slow the loop a bit, affects brightness ramp time
byte dt=14; 

void setup() {
pinMode(buttonPin, INPUT_PULLUP); // initialize button
pixels.begin(); // INITIALIZE NeoPixel pixels object (REQUIRED) 
//pixels.show();  // Initialize all pixels to 'off'
} // end setup

void loop() {

// color presets
if (activeColor == 1) { //purple
  colorGreen = 0;
  colorRed = level - 40;
  colorBlue = level;
}

if (activeColor == 0) { //blue
  colorGreen = 0;
  colorRed = 0;
  colorBlue = level;
}

if (activeColor == 3) { //white
  colorGreen = level;
  colorRed = level;
  colorBlue = level;
}

if (activeColor == 2) { //red
  colorGreen = 0;
  colorRed = level;
  colorBlue = 0;
}

if (activeColor == 4) { //green
  colorGreen = level;
  colorRed = 0;
  colorBlue = 0;
}

if (activeColor == 5) { // OFF
  colorGreen = 0;
  colorRed = 0;
  colorBlue = 0;  
}

motionVal=digitalRead(motionPin); // check for motion
unsigned long currentMillis = millis(); // check the timer

//when motion is detected do this shit
if (motionVal == HIGH){
  previousMillis = currentMillis; // save a time stamp for last motion
} 

// turn LEDs off if timer has has run out
if (currentMillis - previousMillis >= interval) {
  pixels.clear();
  level = 0; // reset the birghtness so we can have a nice fade in the next go around.
  }

pixels.fill(pixels.Color(colorRed, colorGreen, colorBlue, 0)); // this shit almost killed me, you can set the colors until you are blue in the face, if you don't use a action command like "fill" with the Adafruit libraray the damn LEDs are never going to turn on.
pixels.show(); // display those fancy LEDs

delay(dt);

// check if the button is pressed and cycle through the color presets
buttonState = digitalRead (buttonPin);
if (buttonState == LOW) {
  activeColor++;    // incriment counter to change color
  delay(500);
  if (activeColor >= 6) { // Loop color counter back to zero
    activeColor = 0;
  } // close the color slecetion counter reset function
} // close the button function

//ramp up level to fade in brightness, settings are in the global variables
if ((level <= fadeInitiator) && (currentMillis - previousMillis <= interval)) {
  level = level + fadeIncrament;
  if (level >= maxBrightness) { //stop ramping brightness at max brightness
    level = maxBrightness;
  }
} // close brightness ramp function
} // end of loop, see you next time
