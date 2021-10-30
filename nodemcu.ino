#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

#define BLYNK_PRINT Serial

SoftwareSerial serial_info_to_arduino(D2, D3); // Rx and Tx pins

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "arbTMNFpk18iGtb0e2SmJosJLJ41uagS";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Galaxy M31EA2F";
char pass[] = "12344321";

const int stepsPerRevolution = 200; // change this to fit the number of steps per revolution for your motor
const float distPerstep = 0.1; //(in cm)
const int motor_spped = 20;

int Recall = 0;
bool obj_recal = false;
bool scr_recal = true;


int obj_endpin1 = 16, obj_endpin2 = 5, scr_endpin1 = 2, scr_endpin2 = 13;
int obj_end1 = 0, obj_end2 = 0, scr_end1 = 0, scr_end2 = 0;

float obj_dist;
float scr_dist;

float prev_obj = 0;
float prev_scr = 0;
int obj_StepsToTake = 0, scr_StepsToTake = 0 ;
int Timetorotate;


float obj_Recallibrate(float obj_dist) {
  obj_dist = 0;
  Blynk.virtualWrite(2, 0);

  obj_end1 = digitalRead(obj_endpin1);
  
  while(obj_end1 != 1) {
    Serial.print(obj_endpin1);
    Serial.println(obj_end1);

    obj_end1 = digitalRead(obj_endpin1);
    serial_info_to_arduino.println("O" + String(-1));
    delay(50);
  }

  obj_end1 = 0;
  return obj_dist;
}

float scr_Recallibrate(float scr_dist) {
    scr_dist = 0;
    Blynk.virtualWrite(3, 0);

    Serial.println(scr_endpin1);
    Serial.println('a');
    scr_end1 = digitalRead(scr_endpin1);
    Serial.println(scr_end1);
    Serial.println('b');

    while(scr_end1 != 1) {
      scr_end1 = digitalRead(scr_endpin1);
      Serial.println('c');
      Serial.println(scr_end1);
      serial_info_to_arduino.println("S"+ String(-1));

    }
    scr_end1 = 0;
    return scr_dist;
}

void setup() {

  Blynk.begin(auth, ssid, pass);

  // initialize the serial port:
  Serial.begin(9600);
  serial_info_to_arduino.begin(4800);

  pinMode(16, INPUT);

  obj_dist = obj_Recallibrate(obj_dist);
  scr_dist = scr_Recallibrate(scr_dist);

  //serial_info_to_arduino.println("O"+ String(+2));
  //serial_info_to_arduino.println("S"+ String(+2));
}

BLYNK_WRITE(V2) {
  obj_dist = param.asFloat();
}

BLYNK_WRITE(V3) {
  scr_dist = param.asFloat();
}

BLYNK_WRITE(V4) {
  Recall = param.asInt();
}

//BLYNK_WRITE(V5) {
//  float focal_length = prev_obj * prev_scr / (prev_obj + prev_scr);
//  
//}


// Count pin is just for testing without the setup

void loop()  {
  Blynk.run();

  if(Recall == 1) {
    Recall = 0;
    prev_obj = 0;
    prev_scr = 0;

    obj_dist = obj_Recallibrate(obj_dist);
    scr_dist = scr_Recallibrate(scr_dist);

    Blynk.virtualWrite(4, 0);

    //serial_info_to_arduino.println("O"+ String(+2));
    //serial_info_to_arduino.println("S"+ String(+2));
  }

//  if (obj_dist > prev_obj && obj_end2 != 0) {
//      serial_info_to_arduino.println("O+1");
//  }
//
//  if (obj_dist < prev_obj && obj_end1 != 0) {
//      serial_info_to_arduino.println("O-1");
//  }
//
//  if (scr_dist > prev_scr && scr_end2 != 0) {
//      serial_info_to_arduino.println("S+1");
//  }
//
//  if (scr_dist < prev_scr && scr_end1 != 0) {
//      serial_info_to_arduino.println("S-1");
//  }

  obj_StepsToTake = (obj_dist-prev_obj)/distPerstep;
  scr_StepsToTake = (scr_dist-prev_scr)/distPerstep;

  serial_info_to_arduino.println("O"+ String(obj_StepsToTake));
  serial_info_to_arduino.println("S"+ String(scr_StepsToTake));

  prev_obj = obj_dist;
  prev_scr = scr_dist;

  float focal_length = prev_obj * prev_scr / (prev_obj + prev_scr);

  Blynk.virtualWrite(5, focal_length);`a

  //delay(Timetorotate);
}
