#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(0, 1, 9, 10, 11, 12);
 
Servo myservo;
 
#define ir_enter 2
#define ir_back 4
 
#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
 
 
int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4;
int total=0;
int pos=0;
 
void setup() {
  lcd.begin(16, 2); 
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
 
  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);
 
  myservo.attach(3);
  myservo.write(90);
  lcd.setCursor(0, 1);
  lcd.print(" Hi  ");
  lcd.setCursor(0, 2);
  lcd.print(" Welcome to");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("car parking system ");
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayLeft();
     delay(150);
  }
  delay(500);
  lcd.clear();
  Read_Sensor();
 slot-=total;
 
}
 
void loop() {
 
  Read_Sensor();
  lcd.setCursor(0, 0);
  
  if(slot>0)
     lcd.print(" Available Slot: ");
  else
    lcd.print("all slot is full");
    
  lcd.setCursor(0, 1);
  
  if (S1 == 1)
    lcd.print("   ");
  else
    lcd.print("S1 ");
 
  if (S2 == 1) 
    lcd.print("   ");
  else
    lcd.print("S2 ");
    
  if (S3 == 1)
    lcd.print("   ");
  else
    lcd.print("S3 ");

  if (S4 == 1)
    lcd.print("  ");
  else
    lcd.print("S4 ");
 
  if (digitalRead(ir_enter) == 0) 
  {
  
    if (slot > 0 && flag2==0)
    {
        for (; pos <= 180; pos += 1) 
        { 
            myservo.write(pos);
            delay(15);
        }
        flag1=1;
    }
     if(flag2==1)
     {
          while(digitalRead(ir_enter)==0);
          for (; pos >= 0; pos -= 1) 
          {
              myservo.write(pos);
              delay(15);
          }
          flag2=0;
          slot+=1;
      }
      if (slot <= 0 && flag2==0)
      {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("sorry slots full");
          while(digitalRead(ir_enter)==0);
      }    
    }
 
  if (digitalRead(ir_back) == 0) 
  {
    if (flag1 == 0) 
    {
      for (; pos <= 180; pos += 1) 
        { 
            myservo.write(pos);
            delay(15);
        }
        flag2=1;
    }
    else
    {
      while(digitalRead(ir_back) == 0);
      for (; pos >= 0; pos -= 1) 
      {
        myservo.write(pos);
        delay(15);
      }
      flag1=0;
      slot-=1;
    }
  }
 
}
 
void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;
 
  if (digitalRead(ir_car1) == 0) {
    S1 = 1;
  }
  if (digitalRead(ir_car2) == 0) {
    S2 = 1;
  }
  if (digitalRead(ir_car3) == 0) {
    S3 = 1;
  }
  if (digitalRead(ir_car4) == 0) {
    S4 = 1;
  }
 total=S1+S2+S3+S4;
}
