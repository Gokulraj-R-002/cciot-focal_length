#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial serial_info_from_nodemcu(3, 2); // Rx and Tx pins

const int stepPerRev = 200;
Stepper obj_stepper(stepPerRev, 13, 12, 11, 10); // pins 10, 11, 12 and 13 are used to control the motor
Stepper scr_stepper(stepPerRev, 4, 5, 6, 7);

const int motor_speed = 15;
String steps; char To_move;
int steps1;

//int enable_pin = ;
int direction_pin = 9, pulse_pin;


int obj_endpin1 = A4, obj_endpin2 = A1, scr_endpin1 = A2, scr_endpin2 = A3;
int obj_end1 = 0, obj_end2 = 0, scr_end1 = 0, scr_end2 = 0;

float obj_Recallibrate() {
  Serial.println("obj_recall");
  
  pulse_pin = 10;
  digitalWrite(direction_pin, HIGH);
  
  obj_end1 = analogRead(obj_endpin1);
  while (obj_end1 < 800) {
    serial_info_from_nodemcu.println("0");
    obj_end1 = analogRead(obj_endpin1);
    
    Serial.println("end=" + String(obj_end1));
    for (int i = 0; i < 10; i++) {
      digitalWrite(pulse_pin, HIGH);
      delayMicroseconds(500);
      digitalWrite(pulse_pin, LOW);
      delayMicroseconds(500);
    }
  }

  digitalWrite(direction_pin, LOW);
  for(int i = 0; i < 2; i++) {
    digitalWrite(pulse_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(pulse_pin, LOW);
    delayMicroseconds(500);
  }
}

float scr_Recallibrate() {
  Serial.println("scr_recall");

  pulse_pin = 8;
  digitalWrite(direction_pin, HIGH);
  
  scr_end1 = analogRead(scr_endpin1);
  while (scr_end1 < 800) {
    serial_info_from_nodemcu.println("0");
    scr_end1 = analogRead(scr_endpin1);
   // delay(50);
    Serial.println("end=" + String(scr_end1));
    for (int i = 0; i < 10; i++) {
      digitalWrite(pulse_pin, HIGH);
      delayMicroseconds(500);
      digitalWrite(pulse_pin, LOW);
      delayMicroseconds(500);
    }
  }
  
  digitalWrite(direction_pin, LOW);
  for(int i = 0; i < 2; i++) {
    digitalWrite(pulse_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(pulse_pin, LOW);
    delayMicroseconds(500);
  }
}

void setup() {
  Serial.begin(9600);
  serial_info_from_nodemcu.begin(4800);
  pinMode(direction_pin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(obj_endpin1, INPUT);
  pinMode(obj_endpin2, INPUT);
  pinMode(scr_endpin1, INPUT);
  pinMode(scr_endpin2, INPUT);
}

void loop() {
  if (serial_info_from_nodemcu.available() > 0) {
    String str = serial_info_from_nodemcu.readStringUntil('\n');
    Serial.println(str);

    if (str[0] == 'R') {
      Serial.println("Started");
      obj_Recallibrate();
      scr_Recallibrate();    
      Serial.println("end");
      serial_info_from_nodemcu.println("Done");

    }

    To_move = str[0];
    steps = str.substring(1);
    steps1 = steps.toInt();

    if (steps1 > 0) {
      digitalWrite(direction_pin, LOW);
      Serial.println(steps1);
    }
    
    else if(steps1<0) {
      digitalWrite(direction_pin, HIGH);
      Serial.println(steps1);

    }

    if (To_move == 'O') {
      pulse_pin = 10;

    }
    else if (To_move == 'S') {
      pulse_pin = 8;
    }

    for (int i = 0; i < abs(steps1); i++) {
      digitalWrite(pulse_pin, HIGH);
      delayMicroseconds(500);
      digitalWrite(pulse_pin, LOW);
      delayMicroseconds(1500);
    }
  }
}
