#include <Servo.h>

Servo myservo;

// ===================== PIN SETUP =====================
const int potensioPin = A0;   // pin analog potensiometer
const int servoPin = 9;       // pin digital PWM servo

// ===================== VARIABEL =====================
int pos = 0;   // sudut servo
int val = 0;   // nilai ADC potensiometer

void setup() {
  // Hubungkan servo ke pin yang sudah ditentukan
  myservo.attach(servoPin);

  // Aktifkan komunikasi serial untuk monitoring
  Serial.begin(9600);
}

void loop() {
  // ===================== PEMBACAAN ADC =====================
  val = analogRead(potensioPin);

  // ===================== KONVERSI DATA =====================
  pos = map(val, 0, 1023, 0, 180);

  // ===================== OUTPUT SERVO =====================
  myservo.write(pos);

  // ===================== MONITORING DATA =====================
  Serial.print("ADC Potensio: ");
  Serial.print(val);

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  // ===================== STABILISASI =====================
  delay(15);
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
