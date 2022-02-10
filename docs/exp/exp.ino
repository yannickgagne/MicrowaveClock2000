// Blinks an LED attached to a MCP23XXX pin.

// ok to include only the one needed
// both included here to make things simple for example
//#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

// uncomment appropriate line
//Adafruit_MCP23X08 mcp;
Adafruit_MCP23X17 mcp;

unsigned int timer = 0;
unsigned long lastTick = 0;
unsigned int i = 0;

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

void setSegments(int number) {
  Serial.println(number);
  switch(number) {
    case 0:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, LOW);
      mcp.digitalWrite(SGe, LOW);
      mcp.digitalWrite(SGf, LOW);
      mcp.digitalWrite(SGg, HIGH);
      break;
    case 1:
      mcp.digitalWrite(SGa, HIGH);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, HIGH);
      mcp.digitalWrite(SGe, HIGH);
      mcp.digitalWrite(SGf, HIGH);
      mcp.digitalWrite(SGg, HIGH);
      break;
    case 2:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, HIGH);
      mcp.digitalWrite(SGd, LOW);
      mcp.digitalWrite(SGe, LOW);
      mcp.digitalWrite(SGf, HIGH);
      mcp.digitalWrite(SGg, LOW);
      break;
    case 3:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, LOW);
      mcp.digitalWrite(SGe, HIGH);
      mcp.digitalWrite(SGf, HIGH);
      mcp.digitalWrite(SGg, LOW);
      break;
    case 4:
      mcp.digitalWrite(SGa, HIGH);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, HIGH);
      mcp.digitalWrite(SGe, HIGH);
      mcp.digitalWrite(SGf, LOW);
      mcp.digitalWrite(SGg, LOW);
      break;
    case 5:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, HIGH);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, LOW);
      mcp.digitalWrite(SGe, HIGH);
      mcp.digitalWrite(SGf, LOW);
      mcp.digitalWrite(SGg, LOW);
      break;
    case 6:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, HIGH);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, LOW);
      mcp.digitalWrite(SGe, LOW);
      mcp.digitalWrite(SGf, LOW);
      mcp.digitalWrite(SGg, LOW);
      break;
    case 7:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, HIGH);
      mcp.digitalWrite(SGe, HIGH);
      mcp.digitalWrite(SGf, HIGH);
      mcp.digitalWrite(SGg, HIGH);
      break;
    case 8:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, LOW);
      mcp.digitalWrite(SGe, LOW);
      mcp.digitalWrite(SGf, LOW);
      mcp.digitalWrite(SGg, LOW);
      break;
    case 9:
      mcp.digitalWrite(SGa, LOW);
      mcp.digitalWrite(SGb, LOW);
      mcp.digitalWrite(SGc, LOW);
      mcp.digitalWrite(SGd, LOW);
      mcp.digitalWrite(SGe, HIGH);
      mcp.digitalWrite(SGf, LOW);
      mcp.digitalWrite(SGg, LOW);
      break;
  }
}

void setDigit(int digit) {
  switch (digit) {
    case 0:
      mcp.digitalWrite(DG1, HIGH);
      mcp.digitalWrite(DG2, LOW);
      mcp.digitalWrite(DG3, LOW);
      mcp.digitalWrite(DG4, LOW);
      break;
    case 1:
      mcp.digitalWrite(DG1, LOW);
      mcp.digitalWrite(DG2, HIGH);
      mcp.digitalWrite(DG3, LOW);
      mcp.digitalWrite(DG4, LOW);
      break;
    case 2:
      mcp.digitalWrite(DG1, LOW);
      mcp.digitalWrite(DG2, LOW);
      mcp.digitalWrite(DG3, HIGH);
      mcp.digitalWrite(DG4, LOW);
      break;
    case 3:
      mcp.digitalWrite(DG1, LOW);
      mcp.digitalWrite(DG2, LOW);
      mcp.digitalWrite(DG3, LOW);
      mcp.digitalWrite(DG4, HIGH);
      break;
  }
}

void showNumber(int number) {
  //Serial.println(number);
  //break integer in buffer
  char buf[2];
  itoa(number, buf, 10);
  char rbuf[2];
  rbuf[1] = buf[0];
  rbuf[0] = buf[1];
  
  for (int i = 0; i < 2; i++) {
    if((rbuf[i] - '0') < 0) {
      rbuf[i] = '0';
    }
  }
  //get number len
  int len = intLen(number);
  //loop on len
  for(int x = 1; x-- > 0;) {
    setSegments((rbuf[x] - '0'));
    setDigit(x);
    delay(1);
  }
  /*
  //set segments
  setSegments(number);
  //set digits
  setDigit(digit);
  delay(1);
  */
}

int intLen(int x) {
  if(x >= 1000) return 4;
  if(x >= 100) return 3;
  if(x >= 10) return 2;
  if(x <= 9) return 1;
  return 0; //means error!
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
  delay(25);
  showNumber(i);
  
  if(millis() - lastTick > 1000) {
    lastTick = millis();
    i++;
    if(i>9) {i=0;}
  }
  /*
  timer++;

  showNumber(i);

  if(timer > 1000) {
    timer = 0;
    i++;

    if(i>20) {i=0;}
  }
  */
}
