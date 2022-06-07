// library lcd
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// servo
#include <Servo.h>

// lcd init
LiquidCrystal_I2C lcd(0x27, 16, 2);

// irsensor bawah
int irsensor = 2;
int ValueIrsensor = 0;

int irsensor2 = 3; // atas
int ValueIrsensor2 = 0;

// pilot signal
int PilotRed = 4;
int PilotGreen = 5;

int totalwater = 8;
int counterwater = 0;

// button 
int button = 13;
int valuebutton = 0;

int statebutton = 0;


// var init 
int Var = 0;

// servo init
Servo myservo;
int pinServo = 6;

void setup() {
  Serial.begin(9600);
  lcd.begin(); // kalu error begin tukar jd init
  lcd.backlight();
  pinMode(button, INPUT_PULLUP);
  myservo.attach(pinServo);
  pinMode(irsensor, INPUT);
  pinMode(irsensor2, INPUT);
  pinMode(PilotRed, OUTPUT);
  pinMode(PilotGreen, OUTPUT);

  myservo.write(0);

  digitalWrite(PilotRed, HIGH);
  digitalWrite(PilotGreen, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Total Water = 8");
  lcd.setCursor(0, 1);
  lcd.print("Bal Water = ");

}

void loop() {
  ValueIrsensor = digitalRead(irsensor);
  ValueIrsensor2 = digitalRead(irsensor2);
  valuebutton = digitalRead(button);

  if (valuebutton == LOW && statebutton == 0){
    statebutton = 1;
    }

  if (ValueIrsensor2 == LOW){
    counterwater = totalwater;
    lcd.setCursor(12, 1);
    lcd.print("  ");
    lcd.setCursor(12, 1);
    lcd.print(counterwater);
    }

  if (ValueIrsensor == LOW){
    counterwater = counterwater - 1;
    }

  
  switch (Var) {
  case 0:
  
      if (statebutton == 1){ // masuk code card
        digitalWrite(PilotRed, LOW);
        digitalWrite(PilotGreen, HIGH);
        myservo.write(180);
        delay(2000); // 2 sec
        myservo.write(0);
        Var = 1;
        }

        // add card

//      else if (tag == "123456789"){
//        digitalWrite(PilotRed, LOW);
//        digitalWrite(PilotGreen, HIGH);
//        myservo.write(180);
//        delay(2000); // 2 sec
//        myservo.write(0);
//        Var = 1;
//        }
    
    break;
  case 1:
      lcd.setCursor(12, 1);
      lcd.print("  ");
      lcd.setCursor(12, 1);
      lcd.print(counterwater);
      digitalWrite(PilotRed, HIGH);
      digitalWrite(PilotGreen, LOW);
      Var = 0;
      statebutton = 0;
    break;
  }

}
