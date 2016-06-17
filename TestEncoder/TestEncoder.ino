int val;
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup() {
  pinMode (encoder0PinA, INPUT);      //setzt Pin 3 als Input
  pinMode (encoder0PinB, INPUT);      //setzt Pin 4 als Input
  digitalWrite(encoder0PinA, HIGH);   //aktiviert die Pullup Wiederstände
  digitalWrite(encoder0PinB, HIGH);   //aktiviert die Pullup Wiederstände
  Serial.begin(9600);                 //beginnt eine Serielle Kommunikation mit 9600 Boud/s
}

void loop() {
  n = digitalRead(encoder0PinA);      //liest den Zustand des Pin 3
  if((encoder0PinALast == LOW) && (n == HIGH))  //Prüft ob Pin 3 war zuletzt Low war und ob er jetzt High ist 
  {
    if (digitalRead(encoder0PinB) == LOW)       //Prüft ob auch Pin 4 Low ist
    {
      encoder0Pos--;                            //Reduziert Position um 1, wenn nun 3 High, zuvor Low, und 4 ebenfalls Low ist 
    }
    else
    {
      encoder0Pos++;                            //Erhöht Position um 1 andernfalls
    }
    Serial.print (encoder0Pos);                 //Überträgt Position an PC
    Serial.println (" / ");
  }
  encoder0PinALast = n;                         //Aktualisiert n mit dem Letzten Wert von Pin 3
}
