#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial serial_info_from_nodemcu(3, 2); // Rx and Tx pins

const int stepPerRev = 200;
Stepper obj_stepper(stepPerRev, 13, 12, 11, 10); // pins 10, 11, 12 and 13 are used to control the motor
Stepper scr_stepper(stepPerRev, 4, 5, 6, 7);

const int motor_speed = 22;
String steps;
char To_move;
int steps1;

void setup() {
  Serial.begin(9600);
  serial_info_from_nodemcu.begin(4800);
  obj_stepper.setSpeed(motor_speed);
  scr_stepper.setSpeed(motor_speed);
}

void loop() {
  if(serial_info_from_nodemcu.available() > 0) {
    String str = serial_info_from_nodemcu.readStringUntil('\n');
    
    Serial.println(str);
    
    To_move = str[0];
    steps = str.substring(1);
    steps1 = steps.toInt();
    
    if(To_move == 'O') {
      obj_stepper.step(steps1);
    }
    else if (To_move == 'S') {
      scr_stepper.step(steps1);
    }    
  }
}
