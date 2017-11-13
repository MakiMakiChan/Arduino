#include <PinChangeInt.h>


#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>



#define OLED_RESET 24 // not used
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display2(OLED_RESET);

///////////// Varibales ////////////
int magSize = 6; 
boolean lastAutoBullet = false;
volatile int magCounter = 0;
volatile boolean flyWheel = false;
volatile boolean fire = false;
volatile int mode = 0;
volatile int bullets = 0;
volatile boolean pHinten = true;
volatile unsigned long last = 0;
volatile unsigned long speed = 0;
volatile boolean edge = false;

////////////  Setup  //////////////
void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  attachInterrupt(0, fired, RISING);
  attachInterrupt(1, newMag, RISING);
  attachPinChangeInterrupt(1,flyWheelOn,CHANGE);
  attachPinChangeInterrupt(9,modeChange,RISING);
  attachPinChangeInterrupt(8,pusherOn,CHANGE);
  attachPinChangeInterrupt(7,pSens,CHANGE);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display2.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3C (for the 128x32)
  
  display.clearDisplay(); // Clear the buffer.
  display.setTextColor(WHITE); // Set Text color
  display2.clearDisplay(); // Clear the buffer.
  display2.setTextColor(WHITE); // Set Text color
}


////////////////  ISR   ///////////////////////////
void newMag()
{
  magCounter = magSize;
}
void fired()
{
  if(magCounter >0) magCounter--;
}
void flyWheelOn()
{
  flyWheel = !(flyWheel);
} 
void pusherOn()
{
  fire = !fire;
  if(fire == true)
  {
    switch(mode)
    {
        case 0: bullets = 1; break;
        case 1: bullets = 3; break;
        default: bullets = 1; 
    }
    if (magCounter < bullets) bullets = magCounter;
  }
}
void modeChange()
{
  mode++;
  mode = mode %3;
}
void pSens()
{
  if (edge == false) 
  {
    last = millis();
    switch(mode)
    {
      case 2:
      {
        if (mode == 2 && !fire) 
        {
        digitalWrite(6,0);
        bullets = 0;
        }
        break;
      }
      default:
      {
        if (bullets > 0) bullets--;
        if (bullets == 0) digitalWrite(6,0);
        break;
      }
    }
    edge = true;
  }
  else 
  {
    speed = millis() - last;
    edge = false;
  }
}

//////////////////////////////////////////////////////
void loop() {
  display.clearDisplay();
  int fly = analogRead(A0);
  int flyWheel = map (fly,0,1023, 0,30);
  flyWheel += 15;
  int push = analogRead(A2);
  int pusher = map(push, 0,1023,0,30);
  pusher += 15;
    
  int battery = analogRead(A1);
  int bStatus = map(battery, 0,1023,0,8);
  activateFlyWheels(fly);
  activatePusher(push);

  
  drawBattery(bStatus);
  displayMotorSpeed(flyWheel, pusher);
  
  
  displayMag();
  displayFlyWheel();
  displayMode();
  display.display();

  displaySpeed();
}


///////////////  Function   //////////////////////
void displaySpeed()
{
  display2.clearDisplay();
  display2.setCursor(2,0);
  display2.setTextSize(2);
  double dartspeed = (7.2/ (double) speed) *100;
  display2.print(dartspeed);
  
  display2.setCursor(2,18);
  double dartE = (dartspeed*dartspeed)/2000;
  display2.print(dartE);
  display2.print("J");
  display2.display();
}

void activatePusher(int pusher)
{
  if(flyWheel && fire && bullets > 0) analogWrite(6, map(pusher,0,1023,50,255));
}
void drawBattery(int battery)
{
 display.drawRect(0,0,10,5,WHITE);
 display.drawRect(10,1,2,3,WHITE);
 for(int i =0; i <= battery; i++)
 {
  display.drawLine(i+1,1,i+1,3,WHITE);
 }
}
void displayMotorSpeed(int fly, int pusher)
{
  display.drawLine(15,1,fly,1,WHITE);
  display.drawLine(15,3,pusher,3,WHITE);
}
void activateFlyWheels(int fly)
{
  if(flyWheel) analogWrite(5, map(fly,0,1023,50,255));
  else if(bullets == 0) analogWrite(5,0);  
}
void displayMag()
{
  display.setCursor(0,18);
  display.setTextSize(2);
  if(magCounter < 10) display.print("0");
  display.print(magCounter);
  display.print("/");
  if(magSize < 10) display.print("0");
  display.println(magSize);
  display.setTextSize(1);
  delay(1);

  display.setCursor(70,18);
  display.print(bullets);
}
void displayFlyWheel()
{
  display.setCursor(50,0);
  display.print("F:");
  display.print(flyWheel);

}
void displayMode()
{
  display.setCursor(75,0);
  display.print("Mode:");
  if(mode == 0) display.print("S");
  else if(mode == 1) display.print("B");
  else if(mode == 2) display.print("A");
  else display.print("E");
}

