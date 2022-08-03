#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
 int led1 =12;
 int led2 =11;
 int led3 =10;
 
void setup(void) 
{
  Serial.begin(9600); 
  pinMode(led1,OUTPUT); 
  pinMode(led2,OUTPUT);  
  pinMode(led3,OUTPUT); 
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("WLE COME");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print("MLRIT"); // print message at (2, 1)
  delay(1000);
  lcd.clear();   
}
 
void loop(void) 
{
  fsrReading = analogRead(fsrPin);  
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // print the raw analog reading
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("FRONT SENSOR= ");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print(fsrReading); // print message at (2, 1)
  delay(1000);
  if (fsrReading < 10)
  {
    Serial.println(" - No pressure");
    digitalWrite(12,1);
    digitalWrite(11,0);
    digitalWrite(10,0);
  } 
  else if (fsrReading < 100)
  {
    Serial.println(" - Light touch");
    digitalWrite(12,1);
    digitalWrite(11,0);
    digitalWrite(10,0);
  } 
  else if (fsrReading < 100) 
  {
    Serial.println(" - Light squeeze");
    digitalWrite(11,1);
    digitalWrite(12,0);
    digitalWrite(10,0);
  } 
  else if (fsrReading < 210) 
  {
    Serial.println(" - Medium squeeze");
    digitalWrite(12,0);
    digitalWrite(11,0);
    digitalWrite(10,1);
  }
  else 
  {
    Serial.println(" - Big squeeze");
    digitalWrite(12,0);
    digitalWrite(11,0);
    digitalWrite(10,0);
  }
  delay(1000);
}
