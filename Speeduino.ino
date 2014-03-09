/* Speeduino
   
   This sketch controls a digital speedometer.
   It takes an incoming byte via serial and reads as a decimal between
   the range of 0 and 200 (the range of a Speedhut speedometer).
   Instructions on how to connect the Speedhut speedometer are available
   at: http://www.speedhut.com/instructions.i
   
   Speed pulses are generated on pin 3. They currently sweep from 0Hz to 956Hz.
   Keep in mind the Arduino can't generate frequencies below 31Hz.
   
   Calibration occurs via a momentary button press on digital pin 2. This will
   set the frequency to "half" the sweep range. This would equate to 100 MPH on
   the speedometer gauge.
   
   On startup, the speedometer will sweep from minimum and maximum ranges.
   
   Look at the example Python scripts for sending data.
   
   https://github.com/mjuarez/Speeduino
   
   NOTICE: Author and contributors assume no liability for property damage or injury
   incurred as a result of this code or information.
   
   created March 8, 2014
   by Mike Juarez <https://github.com/mjuarez>
   
   This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 United States License.
   To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/us/ or send
   a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
   
*/

const int thisPin = 3;
const int buttonPin = 2;
const unsigned long freqMin = 0;    // adjust this for your speedometer after calibrating
const unsigned long freqMax = 956;  // adjust this for your speedometer after calibrating
const unsigned int rate = 30;       // rate of the initial start sweep

int buttonState = 0;

unsigned int freq;

void setup() {
  pinMode(thisPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  for (int i=0; i <= 200; i++) {
    freq = (int) map(i, 0, 200, freqMin, freqMax);    // remap speedometer range to frequency range
    tone(thisPin, freq);
    delay(rate);
  }
  freq = (int) freqMin;    // reset to frequency to zero
  tone(thisPin,freq);
}

void loop() {
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    // don't process values outside of the speedometer's range
    if ( incomingByte<=200 & incomingByte>=0 ) {
      freq = (int) map(incomingByte, 0, 200, freqMin, freqMax);    // remap speedometer range to frequency range
      Serial.print("I received: ");      // for debug purposes
      Serial.println(incomingByte);
      Serial.print("Tone set at: ");
      Serial.println(freq);
    }
  }
  tone(thisPin, freq);
  delay(2);
  
  // calibration mode
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    buttonState = LOW;
    freq = (int) (freqMax-freqMin)/2;
    tone(thisPin,freq);
  }
}
