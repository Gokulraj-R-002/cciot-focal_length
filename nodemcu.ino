#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

#define BLYNK_PRINT Serial


SoftwareSerial serial_info_to_arduino(D2, D3); // Rx and Tx pins

char auth[] = ""; // put your blynk authorization token here

char ssid[] = ""; // put your wifi ssid here
char pass[] = ""; // put your wifi password here


const float distPerstep = 0.02; //(in cm)

int Recall = 0;
bool obj_recal = false;
bool scr_recal = true;


float obj_dist;
float scr_dist;

float prev_obj = 9;
float prev_scr = 9.2;
int obj_StepsToTake = 0, scr_StepsToTake = 0 ;
int Timetorotate;


void setup() {

  Blynk.begin(auth, ssid, pass);

  // initialize the serial port:
  Serial.begin(9600);
  serial_info_to_arduino.begin(4800);

//  pinMode(16, INPUT);

  /*serial_info_to_arduino.println("R");

    String is_done;

    while(1) {
      if (serial_info_to_arduino.available() > 0) {
        is_done = serial_info_to_arduino.readStringUntil('\n');
        Serial.println(is_done);
        if (is_done[0]  == 'D') {
          Blynk.virtualWrite(4, 0);
          break;
        }
      }
    }*/

    obj_dist = 9;
    scr_dist = 9.2;
    prev_obj = 9;
    prev_scr = 9.2;

    Blynk.virtualWrite(2, 9);
    Blynk.virtualWrite(3, 9.2);
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


void loop()  {
  Blynk.run();

  if (Recall == 1) {  
    serial_info_to_arduino.println("R");

    String is_done;

    while(1) {
      if (serial_info_to_arduino.available() > 0) {
        is_done = serial_info_to_arduino.readStringUntil('\n');
        Serial.println(is_done);
        if (is_done[0]  == 'D') {
          Blynk.virtualWrite(4, 0);
          break;
        }
      }
    }

    Serial.println("Done");

    obj_dist = 9;
    scr_dist = 9.2;
    prev_obj = 9;
    prev_scr = 9.2;

    Blynk.virtualWrite(2, 9);
    Blynk.virtualWrite(3, 9.2);

    Recall = 0;
  }

  obj_StepsToTake = (obj_dist-prev_obj)/distPerstep;
  scr_StepsToTake = (scr_dist-prev_scr)/distPerstep;

  serial_info_to_arduino.println("O"+ String(obj_StepsToTake));
  serial_info_to_arduino.println("S"+ String(scr_StepsToTake));

  prev_obj = obj_dist;
  prev_scr = scr_dist;

  float focal_length = prev_obj * prev_scr / (prev_obj + prev_scr);

  Blynk.virtualWrite(5, focal_length);

  delay(2000);
}
