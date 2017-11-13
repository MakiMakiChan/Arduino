/*
    Arduino Game Death Logger

    by Timm Meiwes
*/
#include <SD.h>
#include <SPI.h>
#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PinChangeInt.h>


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
File myFile;
DS3231  rtc(SDA, SCL);
int pinCS = 9; // ChipSelect für die SD Karte

//Variables
volatile boolean store = false;
volatile boolean changeGame = true;
volatile int counter = 0;

//Files 
String logFile = "all.txt";
String myFiles [] = {"fo4.txt", "test.txt", "deusEx.txt", "DarkS3.txt", "Sky.txt", "ShOM.txt", "DisH2.txt"};
String myGames [] = {"FallOut 4", "Test", "DeusEx", "Dark Souls 3", "Skyrim", "Shadow of Mordor", "Dishonored 2"};

//DeathNumbers
int totalDeath = 0;
int totalGameDeath = 0;
int todaysDeath = 0;

//ScreenPositions
int all = 0;
int other = 9; 


int myFilesLength = sizeof(myFiles) / sizeof(String);
int acctGame = counter;

void setup() {

  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  

  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();

  // SD Card Initialization
  if (SD.begin())
  {
    lcd.println("SD card is ready to use.");
  } else
  {
    lcd.println("Card init failed");
    delay(1000);
    return;
  }
  rtc.begin();

  attachInterrupt(0, gameDown, RISING);
  attachPinChangeInterrupt(6, gameUp, RISING);
  attachPinChangeInterrupt(4, save, RISING);


  //Prüfe ob alle nötigen Files da sind, sonst lege sie an
  //Serial.println("Init");
  int files = 0;
 
  for ( int i = 0 ; i < myFilesLength ; i++) {
    File openTest = SD.open(myFiles[i], FILE_WRITE);
    if (openTest) {
    
      openTest.close(); // close the file
    //  Serial.println(myFiles[i]);
      files ++;
    }
    // if the file didn't open, print an error:
    else {
      lcd.clear();
      lcd.print("error opening " + myFiles[i]);
    }
  }
  if (!files == myFilesLength) {
    //Serial.println("ERROR");
    lcd.println("ERROR");
  } else {
    //Serial.println("init okay");
    lcd.setCursor(0, 1);
    lcd.print("Ready");
  }

  delay(10000);
}






