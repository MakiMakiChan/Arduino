#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include "printf.h"

RF24 radio(9,10);
const int inPutPin = A0;
const uint64_t pipe = 0xB00B1E5000LL;

long value = 0;

void setup() {
  Serial.begin(57600);
  printf_begin();
  printf("Sender\n");

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(5,15);
  radio.openWritingPipe(pipe);
  radio.stopListening();
  radio.printDetails();
  
  pinMode(inPutPin, INPUT);
  digitalWrite(inPutPin, HIGH);
}

void loop() {
  value = analogRead(inPutPin);
  value = value *255 /1024;
  Serial.println(value);
  if (!radio.write(&value,1))
  {
    Serial.println("Fail");
  }
  else
  {
    Serial.println("OK");
  }
  // put your main code here, to run repeatedly:

}
