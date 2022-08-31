/*Code for nano IC for all bench top function, starting with 2x5 neopixel strings lighting the bentch.
 * with PIR motion sensor with 10 minute timer, once setup could add a button to enter different lighting modes and potentiometer for controll brightness.
 * follow up idea button to play winning/mario level up sound effects
 */

#include <Adafruit_NeoPixel.h>
const byte lightPin = D1;
//int lightState = LOW;
unsigned long previousMillis = 0;
const long interval = 300*1500;  // how long the neopixels will stay on in miliseconds
const byte motionPin = D2;
const byte buttonPin = D3;// enter a pin number for a tactile button
bool buttonState;
int motionVal;
const byte numPixels = 18;
int pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel strip(numPixels, lightPin, NEO_GRB + NEO_KHZ800);
int purple;
int blue;
int white;
int red;
int off;
int colorGreen = 0; // RGB value variable
int colorRed = 0; // RGB value variable
int colorBlue = 0; // RGB value variable
int level = 0; //use this variable to fade the brightness
int color; //sets the color of the strip, using switchCase


//uint32_t softwhite = ((colorGreen = 255), (colorRed = 127), (colorBlue = 35))
// int purple = ((colorGreen = 0), (colorRed = level), (colorBlue = level));
// int blue = ((colorGreen = 0), (colorRed = 0), (colorBlue = level));
// int white = ((colorGreen = level), (colorRed = level), (colorBlue = level));
// int red = ((colorGreen = 0), (colorRed = level), (colorBlue = 0));
// int off = ((colorGreen = 0), (colorRed = 0), (colorBlue = 0));
//uint32_t softwhite = strip.Color(255, 127, 35);
//uint32_t purple = strip.Color(0, level, level)//;
//uint32_t blue = strip.Color(0, 0, level)////;
//uint32_t white = strip.Color level, level,////// level);
//uint32_t red = strip.Color(0, level, 0)////////;

////
int dt=200;

void setup() {
Serial.begin(9600);
pinMode(buttonPin, INPUT_PULLUP);
strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED) 
strip.clear(); // Set all pixel colors to 'off'
motionVal = LOW;
//activeColor = purple;
level = 0;
}

void loop() {
int activeColor;
motionVal=digitalRead(motionPin); 
unsigned long currentMillis = millis(); //check timer for on delay 
//when motion is detected do this shit
if (motionVal == HIGH){
  strip.Color(colorGreen, colorRed, colorBlue);
  Serial.println("motion detected");
    //strip.fill(softwhite, 0); //set neopixel color
    previousMillis = currentMillis; // save the last time motion was detected
} 

// turn LEDs off if timer has has run out
if (currentMillis - previousMillis >= interval) {
    strip.clear();
    level = 0;
    Serial.println("no motion strip cleared");
      }

// color presets
if (color == purple) { //purple
  colorGreen = 0;
  colorRed = level;
  colorBlue = level;
}

if (color == blue) {
  colorGreen = 0;
  colorRed = 0;
  colorBlue = level;
}

if (color == white) {
  colorGreen = level;
  colorRed = level;
  colorBlue = level;
}

if (color == red) {
  colorGreen = 0;
  colorRed = level;
  colorBlue = 0;
}
if (color == off) {
  strip.clear();
}

//Serial.println(currentMillis - previousMillis);
strip.show();
Serial.println("color displayed - strip.show command reached");
Serial.print("Active Color: ");
Serial.println(activeColor);
delay(dt);

// switching between base colors
switch(activeColor) {
  case 1:
    color = blue;
    Serial.println("color selected - OFF");
    break;
  case 2:
    color = purple;
    Serial.println("color selected - purple");
    break;
  case 3:
    color = red;
    Serial.println("color selected - blue");
    break;
  case 4:
    color = white;
    Serial.println("color selected - white");
    break;
  case 5:
    color = off;
    Serial.println("color selected - red");
    break;
}

// read button
buttonState = digitalRead (buttonPin);
if (buttonState == LOW) {
  activeColor = activeColor +1;
  Serial.println("button press");
  delay(500);
}

//ramp up level to fade in brightness
if ((level <= 179) && (currentMillis - previousMillis <= interval)) {
  level = level + 1;
  Serial.print("fade veriable: ");
  Serial.println(level);
}

//stop ramping brightness at 180
if (level >= 180) {
  level = 180;
}
Serial.print("Red value: ");
Serial.println(colorRed);
delay(50);
}
