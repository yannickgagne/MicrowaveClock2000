// Blinks an LED attached to a MCP23XXX pin.

// ok to include only the one needed
// both included here to make things simple for example
//#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

// uncomment appropriate line
//Adafruit_MCP23X08 mcp;
Adafruit_MCP23X17 mcp;

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
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(11, OUTPUT);
  mcp.pinMode(12, OUTPUT);
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);

  mcp.digitalWrite(0, LOW);
  mcp.digitalWrite(1, LOW);
  mcp.digitalWrite(2, LOW);
  mcp.digitalWrite(3, LOW);
  mcp.digitalWrite(4, LOW);
  mcp.digitalWrite(5, LOW);
  mcp.digitalWrite(6, LOW);
  mcp.digitalWrite(7, LOW);
  mcp.digitalWrite(8, HIGH);
  mcp.digitalWrite(9, HIGH);
  mcp.digitalWrite(10, HIGH);
  mcp.digitalWrite(11, HIGH);
  mcp.digitalWrite(12, HIGH);
  mcp.digitalWrite(13, HIGH);
  mcp.digitalWrite(14, HIGH);
  mcp.digitalWrite(15, HIGH);
  
  Serial.println("Looping...");
}

void loop() {
  mcp.digitalWrite(0, HIGH);
  mcp.digitalWrite(8, LOW);
  delay(500);
  mcp.digitalWrite(0, LOW);
  mcp.digitalWrite(8, HIGH);
  delay(500);
}
