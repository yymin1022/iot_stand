#include <SoftwareSerial.h>
#include <Servo.h>
#include <avr/wdt.h>

int btTX = 8;
int btRX = 9;
int LED = 2;
int VIB = 3;

byte buffer[1024];
int bufferPosition;

unsigned char onChar = 'ON';
unsigned char offChar = 'OF';
unsigned char exitChar = 'EXIT';

Servo servo;
SoftwareSerial  btSerial(btTX, btRX);

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  servo.attach(7, 544, 2400);
  servo.write(0);
  bufferPosition = 0;
}

void loop() {
  if (btSerial.available()) {
    byte data = btSerial.read();
    Serial.write(data);
    if (data == onChar) {
      servo.write(180);
      delay(500);
      servo.write(0);
      delay(500);
    }
    if (data == offChar) {
      servo.write(180);
      delay(500);
      servo.write(0);
      delay(500);
      servo.write(180);
      delay(500);
      servo.write(0);
      delay(500);
    }
    if (data == exitChar) {
      Serial.write("Hello, World!");
      btSerial.print("AT+RESET");
    }
    buffer[bufferPosition++] = data;
  }
}
