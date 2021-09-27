/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "arbTMNFpk18iGtb0e2SmJosJLJ41uagS";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";


float curr_obj_pos = 0, curr_scr_pos = 0;
float new_obj_pos, new_scr_pos;

int recalibrate = 0;

void Recalibrate() {
  
}

SoftwareSerial serial_info_to_arduino(D2, D3); // Rx and Tx pins

BLYNK_WRITE(V0) {
  new_obj_pos = param.asFloat();
}

BLYNK_WRITE(V1) {
  new_scr_pos = param.asFloat();
}

BLYNK_WRITE(V2) {
  recalibrate = param.asInt();
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  serial_info_to_arduino.begin(4800);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
}

void loop() {
  Blynk.run();

  if (recalibrate == 1) {
    Recalibrate();
  }

  // update the object position
  if (new_obj_pos == curr_obj_pos) {
    serial_info_to_arduino.println("O+0");
  }
  else if (new_obj_pos < curr_obj_pos) {
    serial_info_to_arduino.println("O-1");
    curr_pos = new_pos;
  }
  else if (new_obj_pos > curr_scr_pos) {
    serial_info_to_arduino.println("O+1");
    curr_pos = new_pos;
  }

  // update the screen position
  if (new_scr_pos == curr_scr_pos) {
    serial_info_to_arduino.println("I+0");
  }
  else if (new_scr_pos < curr_scr_pos) {
    serial_info_to_arduino.println("I-1");
    curr_scr_pos = new_scr_pos;
  }
  else if (new_scr_pos > curr_scr_pos) {
    serial_info_to_arduino.println("I+1");
    curr_scr_pos = new_scr_pos;
  }
}
