#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo myservo;

#define ir_enter 2
#define ir_exit 4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8

int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int slot = 4; // Initial available parking slots

void setup()
{
  Serial.begin(9600);
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_enter, INPUT);
  pinMode(ir_exit, INPUT);

  myservo.attach(9);
  myservo.write(90);

  lcd.begin(16, 2);
  lcd.init();        
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("    Smart Car   ");
  lcd.setCursor(0, 1);
  lcd.print(" Parking System ");
  delay(2000);
  lcd.clear();

  Read_Sensor();

  // Calculate the initial available parking slots
  int total = S1 + S2 + S3 + S4;
  slot = slot - total;
}

void loop()
{
  Read_Sensor();

  lcd.setCursor(0, 0);
  lcd.print("Available of 4:");
  lcd.print(slot);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print("S1:");
  lcd.print(S1 == 1 ? "F" : "E");

  lcd.setCursor(5, 1);
  lcd.print("S2:");
  lcd.print(S2 == 1 ? "F" : "E");

  lcd.setCursor(10, 1);
  lcd.print("S3:");
  lcd.print(S3 == 1 ? "F" : "E");

  lcd.setCursor(15, 1);
  lcd.print("");
  lcd.print(S4 == 1 ? "F" : "E");

  // Servo Motor Control
  if (digitalRead(ir_enter) == 0)
  {
    if (slot > 0)
    {
      myservo.write(180);
      delay(1500); // Simulating the time it takes for a car to enter
      slot = slot - 1;
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print(" Parking Full ");
      myservo.write(90);
      delay(1500);
    }
  }

  if (digitalRead(ir_exit) == 0)
  {
    if (slot < 4){
    delay(1500); // Simulating the time it takes for a car to exit
    slot = slot + 1;
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print(" You can enter !! ");
      delay(1500); 
    }
  }

  delay(1);
}

void Read_Sensor()
{
  S1=0, S2=0, S3=0, S4=0;
 if(digitalRead(ir_car1) == 0){S1=1;} // read degital data from IR sensor3
 if(digitalRead(ir_car2) == 0){S2=1;} // read degital data from IR sensor4
 if(digitalRead(ir_car3) == 0){S3=1;} // read degital data from IR sensor5
 if(digitalRead(ir_car4) == 0){S4=1;} // read degital data from IR sensor6
}