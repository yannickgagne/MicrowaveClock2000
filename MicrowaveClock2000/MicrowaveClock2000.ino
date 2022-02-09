#include "SevSeg.h"
SevSeg sevseg;

int deciSeconds = 0;
unsigned long timer = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    while (!Serial);
  
  delay(2000);
  byte numDigits = 2;
  byte digitPins[] = {0, 1};
  byte segmentPins[] = {8, 9, 10, 12, 13, 14, 15};
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = true; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);

  sevseg.blank();
}

void loop() {
  // put your main code here, to run repeatedly:  
  if (millis() - timer >= 1000) {
    Serial.println("in loop if");
    timer += 1000;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    
    if (deciSeconds == 99) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(deciSeconds, 0);
  }
  
  sevseg.refreshDisplay(); // Must run repeatedly
}
