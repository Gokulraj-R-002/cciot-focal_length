#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial serial_info_from_nodemcu(3, 2); // Rx and Tx pins

const int stepPerRev = 200;
Stepper mystepper(stepPerRev, 13, 12, 11, 10); // pins 10, 11, 12 and 13 are used to control the motor

void setup() {
  Serial.begin(9600);
  serial_info_from_nodemcu.begin(4800);
  mystepper.setSpeed(5);
}

void loop() {
  if(serial_info_from_nodemcu.available() > 0) {
    String str = serial_info_from_nodemcu.readStringUntil('\n');
//    Serial.println(str);
    if(str[0] == '1') {
      mystepper.step(-5);
      Serial.println("moved -5");
    }
    else if (str[0] == '2') {
      mystepper.step(5);
      Serial.println("moved 5");
    }
  }
}
