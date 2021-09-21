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


float curr_pos = 0, new_pos;

SoftwareSerial serial_info_to_arduino(D2, D3); // Rx and Tx pins

BLYNK_WRITE(V0) {
  new_pos = param.asFloat();
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

  if (new_pos == curr_pos) {
    serial_info_to_arduino.println("0");
  }

  else if (new_pos < curr_pos) {
    serial_info_to_arduino.println("1");
    curr_pos = new_pos;
  }

  else if (new_pos > curr_pos) {
    serial_info_to_arduino.println("2");
    curr_pos = new_pos;
  }
}
