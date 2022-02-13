#include "Adafruit_MCP23X17.h"

Adafruit_MCP23X17 mcp;

unsigned int timer = 0;
unsigned long lastTick = 0;
unsigned int i = 100;
uint8_t prevSeg;

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

int intLen(int x) {
  if(x >= 1000) return 4;
  if(x >= 100) return 3;
  if(x >= 10) return 2;
  if(x <= 9) return 1;
  return 0; //means error!
}

static const uint8_t segMap[] = {
  // GFEDxCBA  Segments      7-segment map:
  0b010001000, // 0   "0"          AAA
  0b011111001, // 1   "1"         F   B
  0b001001100, // 2   "2"         F   B
  0b001101000, // 3   "3"          GGG
  0b000111001, // 4   "4"         E   C
  0b000101010, // 5   "5"         E   C
  0b000001010, // 6   "6"          DDD
  0b011111000, // 7   "7"
  0b000001000, // 8   "8"
  0b000101000, // 9   "9"
};

static const uint8_t segPins[] = {
  8,
  9,
  10,
  12,
  13,
  14,
  15,
};

void blank() {
  mcp.writeGPIOA(0b011111111);
  /*mcp.digitalWrite(DG1, LOW);
  mcp.digitalWrite(DG2, LOW);
  mcp.digitalWrite(COL, LOW);
  mcp.digitalWrite(DG3, LOW);
  mcp.digitalWrite(DG4, LOW);*/
  mcp.writeGPIOB(0b000000000);
  /*mcp.digitalWrite(SGa, HIGH);
  mcp.digitalWrite(SGb, HIGH);
  mcp.digitalWrite(SGc, HIGH);
  mcp.digitalWrite(11, HIGH); 
  mcp.digitalWrite(SGd, HIGH);
  mcp.digitalWrite(SGe, HIGH);
  mcp.digitalWrite(SGf, HIGH);
  mcp.digitalWrite(SGg, HIGH);*/
}

void setSegments(int number) {
  //Serial.println(number);
  mcp.writeGPIOB(segMap[number]);

  /*
  for (uint8_t z = 0;z < 7;z++) {
    if((prevSeg & (1 << z)) != (segMap[number] & (1 << z))) {
      if ((segMap[number] & (1 << z)) > 0) {
        mcp.digitalWrite(segPins[z], LOW);
      } else {
        mcp.digitalWrite(segPins[z], HIGH);
      }
    }
  }
  */
  prevSeg = segMap[number];
}

void setDigit(int digit) {
  switch (digit) {
    case 0:
      mcp.writeGPIOA(0b000000001);
      break;
    case 1:
      mcp.writeGPIOA(0b000000010);
      break;
    case 2:
      mcp.writeGPIOA(0b000001000);
      break;
    case 3:
      mcp.writeGPIOA(0b000010000);
      break;
  }
}

void showNumber(int number) {
  //get number len
  int len = intLen(number);
  //break integer in buffer and reverse order
  char buf[3];
  itoa(number, buf, 10);
  char rbuf[3];
  if(len > 1) {
    rbuf[2] = buf[0];
    rbuf[1] = buf[1];
    rbuf[0] = buf[2];
  } else {
    rbuf[0] = buf[0];
    rbuf[1] = buf[1];
    rbuf[2] = buf[2];
  }

  for (int i = 0; i < 3; i++) {
    //convert char buffer to integer
    rbuf[i] = rbuf[i] - '0';
    //if value smaller than zero, then equals zero
    if((rbuf[i]) < 0) {
      rbuf[i] = 0;
    }
  }

  //loop on len
  for(int x = len; x-- > 0;) {
    int v = rbuf[x];
    //Serial.println(v);
    setDigit(x);
    setSegments(v);
    delay(7);
  }
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
  delay(5);
  //Serial.println(i);
  showNumber(i);
  
  if(millis() - lastTick > 1000) {
    lastTick = millis();
    i++;
    if(i>110) {i=100;}
  }
}
