// Blinks an LED attached to a MCP23XXX pin.

// ok to include only the one needed
// both included here to make things simple for example
//#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

// uncomment appropriate line
//Adafruit_MCP23X08 mcp;
Adafruit_MCP23X17 mcp;

int DG1 = 0;
int DG2 = 1;
int COL = 2;
int DG3 = 3;
int DG4 = 4;
int SGa = 8;
int SGb = 9;
int SGc = 10;
int SGd = 12;
int SGe = 13;
int SGf = 14;
int SGg = 15;

void blank() {
  mcp.digitalWrite(DG1, LOW);
  mcp.digitalWrite(DG2, LOW);
  mcp.digitalWrite(COL, LOW);
  mcp.digitalWrite(DG3, LOW);
  mcp.digitalWrite(DG4, LOW);
  mcp.digitalWrite(SGa, HIGH);
  mcp.digitalWrite(SGb, HIGH);
  mcp.digitalWrite(SGc, HIGH);
  mcp.digitalWrite(11, HIGH);
  mcp.digitalWrite(SGd, HIGH);
  mcp.digitalWrite(SGe, HIGH);
  mcp.digitalWrite(SGf, HIGH);
  mcp.digitalWrite(SGg, HIGH);
}

void one(int digit) {
  mcp.digitalWrite(digit, HIGH);
  mcp.digitalWrite(SGa, HIGH);
  mcp.digitalWrite(SGb, LOW);
  mcp.digitalWrite(SGc, LOW);
  mcp.digitalWrite(SGd, HIGH);
  mcp.digitalWrite(SGe, HIGH);
  mcp.digitalWrite(SGf, HIGH);
  mcp.digitalWrite(SGg, HIGH);
}

void two(int digit) {
  mcp.digitalWrite(digit, HIGH);
  mcp.digitalWrite(SGa, LOW);
  mcp.digitalWrite(SGb, LOW);
  mcp.digitalWrite(SGc, HIGH);
  mcp.digitalWrite(SGd, LOW);
  mcp.digitalWrite(SGe, LOW);
  mcp.digitalWrite(SGf, HIGH);
  mcp.digitalWrite(SGg, LOW);
}

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C()) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }

  // configure pin for output
  mcp.pinMode(DG1, OUTPUT); //1st digit
  mcp.pinMode(DG2, OUTPUT); //2nd digit
  mcp.pinMode(COL, OUTPUT); //Colon
  mcp.pinMode(DG3, OUTPUT); //3rd digit
  mcp.pinMode(DG4, OUTPUT); //4th digit
  mcp.pinMode(5, OUTPUT); //NOT USED
  mcp.pinMode(6, OUTPUT); //NOT USED
  mcp.pinMode(7, OUTPUT); //NOT USED
  mcp.pinMode(SGa, OUTPUT); //Segment a
  mcp.pinMode(SGb, OUTPUT); //Segment b
  mcp.pinMode(SGc, OUTPUT); //Segment c
  mcp.pinMode(11, OUTPUT); //NOT USED (Microwave functions items)
  mcp.pinMode(SGd, OUTPUT); //Segment d
  mcp.pinMode(SGe, OUTPUT); //Segment e
  mcp.pinMode(SGf, OUTPUT); //Segment f
  mcp.pinMode(SGg, OUTPUT); //Segment g

  //Turn OFF all
  blank();
  
  Serial.println("Starting Loop...");
}

void loop() {
  blank();
  one(0);
  delay(500);
  blank();
  two(0);
  delay(500);
}
