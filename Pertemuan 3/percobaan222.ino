#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int adc = analogRead(pinPot);

  float volt = adc * (5.0 / 1023.0);
  float persen = (adc / 1023.0) * 100;

  int bar = map(adc, 0, 1023, 0, 16);

  // Serial Monitor
  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" | Volt: ");
  Serial.print(volt);
  Serial.print(" V | Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // LCD baris 1
  lcd.setCursor(0, 0);
  lcd.print("ADC:");
  lcd.print(persen, 0);
  lcd.print("%   ");

  // LCD baris 2 (bar)
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < bar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}