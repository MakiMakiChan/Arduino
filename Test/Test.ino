int zaehler = 0;
void setup() {
  Serial.begin(57600);
  pinMode (3, OUTPUT);
}

void loop() {
  Serial.println (zaehler);
  digitalWrite (3, HIGH);
  delay(1000);
  digitalWrite (3, LOW);
  delay(1000);
  zaehler++;
}
