#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial serial_info_from_nodemcu(3, 2); // Rx and Tx pins

const int stepPerRev = 200;
Stepper obj_stepper(stepPerRev, 13, 12, 11, 10);
Stepper scr_stepper(stepPerRev, 9, 8, 7, 6);

void setup() {
  Serial.begin(9600);
  serial_info_from_nodemcu.begin(4800);
  
  obj_stepper.setSpeed(5);
  scr_stepper.setSpeed(5);

}

void loop() {
  if(serial_info_from_nodemcu.available() > 0) {
    String str = serial_info_from_nodemcu.readStringUntil('\n');
//    Serial.println(str);

    steps = str.substring(1);
    
    if(str[0] == 'O') {
      obj_stepper.step(steps.toInt());
      Serial.println("moved -5");
    }
    else if (str[0] == 'I') {
      scr_stepper.step(steps.toInt());
      Serial.println("moved 5");
    }
  }
}
