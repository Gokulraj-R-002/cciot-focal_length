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
char ssid[] = "RISMIT_770";
char pass[] = "RISHUmitu*8978@770";

const int stepsPerRevolution = 200; // change this to fit the number of steps per revolution
// for your motor
const float distPerstep = 1; //(in cm)
const int motor_spped = 20;

int Recall = 0;
int val = 0;
bool obj_recal = false;
bool scrn_recal = true;


int obj_endpin1 = 0, obj_endpin2 = 0, scrn_endpin1 = 0,scrn_endpin2 = 0;

float obj_dist;
float scrn_dist;

float prev_obj = 0;
float prev_scrn = 0;
int obj_StepsToTake = 0, scrn_StepsToTake = 0, count = 0 ;
int Timetorotate;


float obj_Recallibrate(float obj_dist) {
  obj_dist = 0;
  Blynk.virtualWrite(2, 0);

  count = 0;

  while(obj_endpin1!=1){
    serial_info_to_arduino.println("O"+String(-1)); // missing

    if(count == 10){
      obj_endpin1 = 1;
    }
    else{
      count += 1;
    }

  }
  return obj_dist;
}

float scrn_Recallibrate(float scrn_dist) {
  scrn_dist = 0;
  Blynk.virtualWrite(3, 0);

  count = 0;
  Serial.println(scrn_endpin1);
  Serial.println('a');
  scrn_endpin1 = digitalRead(D1);
  Serial.println(scrn_endpin1);
  Serial.println('b');
  while(scrn_endpin1 != 1){
    scrn_endpin1 = digitalRead(D1);
    Serial.println('c');
    Serial.println(scrn_endpin1);
    serial_info_to_arduino.println("S"+ String(-1)); // missing

  }
  return scrn_dist;
}

void setup(){

  Blynk.begin(auth, ssid, pass); // missing

  // initialize the serial port:
  Serial.begin(9600);
  serial_info_to_arduino.begin(4800);

  pinMode(D1, INPUT);

  //obj_dist = obj_Recallibrate(obj_dist);
  scrn_dist = scrn_Recallibrate(scrn_dist);

  //serial_info_to_arduino.println("O"+ String(+2));
  //serial_info_to_arduino.println("S"+ String(+2));
}

BLYNK_WRITE(V2){
  obj_dist = param.asFloat();
}
BLYNK_WRITE(V3){
  scrn_dist = param.asFloat();
}
BLYNK_WRITE(V4){
  Recall = param.asInt();
}


// Count pin is just for testing without the setup

void loop() {
  count = 0;
  Blynk.run();

  if(Recall == 1){
    Recall = 0;
    prev_obj =0;
    prev_scrn = 0;

    //obj_dist = obj_Recallibrate(obj_dist);
    scrn_dist = scrn_Recallibrate(scrn_dist);

    Blynk.virtualWrite(4, 0);

    //serial_info_to_arduino.println("O"+ String(+2));
    //serial_info_to_arduino.println("S"+ String(+2));
  }

  obj_StepsToTake = (obj_dist-prev_obj)/distPerstep;

  //for object
  scrn_StepsToTake = (scrn_dist-prev_scrn)/distPerstep;

  serial_info_to_arduino.println("O"+ String(obj_StepsToTake));
  serial_info_to_arduino.println("S"+String(scrn_StepsToTake));

  prev_obj = obj_dist;
  prev_scrn = scrn_dist;




  //delay(Timetorotate);
}
