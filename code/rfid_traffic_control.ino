I have to push it to my github
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

// LCD (change 0x27 to 0x3F if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Traffic
#define RED 3
#define YELLOW 4
#define GREEN 5
#define BUZZER 6

// UIDs
byte emergencyUID[4] = {0x8F, 0x3D, 0xD8, 0x1F};
byte theftUID[4]     = {0x8A, 0x91, 0x7E, 0x00};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED, HIGH);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("RFID Traffic");
  lcd.setCursor(0, 1);
  lcd.print("Scan Card...");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  if (compareUID(rfid.uid.uidByte, emergencyUID)) {
    emergencyMode();
  }
  else if (compareUID(rfid.uid.uidByte, theftUID)) {
    theftMode();
  }
  else {
    unauthorizedMode();
  }

  rfid.PICC_HaltA();
}

// 🚑 Emergency
void emergencyMode() {
  Serial.println("Emergency");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Emergency Veh");
  lcd.setCursor(0, 1);
  lcd.print("Green Signal");

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);

  delay(5000);

  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);

  resetLCD();
}

// 🚨 Theft
void theftMode() {
  Serial.println("Theft");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Theft Vehicle!");
  lcd.setCursor(0, 1);
  lcd.print("Alert!");

  for (int i = 0; i < 5; i++) {
    digitalWrite(RED, LOW);
    digitalWrite(BUZZER, HIGH);
    delay(300);

    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, LOW);
    delay(300);
  }

  resetLCD();
}

// ❌ Unauthorized
void unauthorizedMode() {
  Serial.println("Unauthorized");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Unauthorized");
  lcd.setCursor(0, 1);
  lcd.print("Try Again");

  delay(2000);

  resetLCD();
}

// Reset LCD
void resetLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan Card...");
}

// UID compare
boolean compareUID(byte a[], byte b[]) {
  for (byte i = 0; i < 4; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}