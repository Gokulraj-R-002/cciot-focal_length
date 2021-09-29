#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial serial_info_from_nodemcu(3, 2); // Rx and Tx pins

const int stepPerRev = 200;
Stepper mystepper(stepPerRev, 13, 12, 11, 10); // pins 10, 11, 12 and 13 are used to control the motor
String steps;
char To_move;
int steps1;
void setup() {
  Serial.begin(9600);
  serial_info_from_nodemcu.begin(4800);
  mystepper.setSpeed(20);
}

void loop() {
  if(serial_info_from_nodemcu.available() > 0) {
    String str = serial_info_from_nodemcu.readStringUntil('\n');
   Serial.println(str);
   To_move = str[0];
  steps = str.substring(1);
  steps1 = steps.toInt();
    if(To_move == 'O') {
      mystepper.step(steps1);
    }
    else if (To_move == 'S') {
      mystepper.step(steps1);
    }
  }
}
