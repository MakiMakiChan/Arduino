#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include "printf.h"

RF24 radio(9,10);
const uint64_t pipe = 0xB00B1E5000LL;
int inhalt = 0;

void setup() {
  Serial.begin(57600);
  printf_begin();
  printf("Empfänger\n");

  radio.begin();
  radio.setAutoAck(1);
  radio.setRetries(5,15);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  radio.printDetails();

  pinMode (3, OUTPUT);
}

void loop() {
  while (radio.available())
  {
    radio.read(&inhalt, 1);
  }
  Serial.println(inhalt);
  analogWrite(3,inhalt);
}
