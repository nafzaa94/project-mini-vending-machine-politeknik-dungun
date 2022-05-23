// library rfid
#include <SPI.h>
#include <MFRC522.h>

// library lcd
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// servo
#include <Servo.h>

// lcd init
LiquidCrystal_I2C lcd(0x27, 16, 2);

// irsensor
int irsensor = 2;
int ValueIrsensor = 0;

int irsensor2 = 3;
int ValueIrsensor2 = 0;

// pilot signal
int PilotRed = 4;
int PilotGreen = 5;

int totalwater = 8;
int counterwater = 0;

// rfid init
constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;

// var init 
int Var = 0;

// servo init
Servo myservo;
int pinServo = 6;

void setup() {
  Serial.begin(9600);
  lcd.begin(); // kalu error begin tukar jd init
  lcd.backlight();
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
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
      RunRfid();
  
      if (tag == "123456789"){
        digitalWrite(PilotRed, LOW);
        digitalWrite(PilotGreen, HIGH);
        myservo.write(180);
        delay(2000); // 2 sec
        myservo.write(0);
        Var = 1;
        }
    
    break;
  case 1:
      lcd.setCursor(12, 1);
      lcd.print("  ");
      lcd.setCursor(12, 1);
      lcd.print(counterwater);
      digitalWrite(PilotRed, HIGH);
      digitalWrite(PilotGreen, LOW);
      Var = 0;
      tag = "";
    break;
  }

}

void RunRfid(){
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
    if (rfid.PICC_ReadCardSerial()) {
      for (byte i = 0; i < 4; i++) {
        tag += rfid.uid.uidByte[i];
      }
      Serial.println(tag);
  }
  }
