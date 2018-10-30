#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Time.h>
#include <TimeAlarms.h>

char auth[] = "a68edab7acfe460e98189f673f539264";


char ssid[] = "GVT-EF9C";
char pass[] = "0038624284";
int steps = 0;
int seconds = 0;
float speedTotal = 0;
float distance = 0;

BLYNK_WRITE(V1){
 if(param.asInt()==1)
 {
  steps++;
  distance = steps*0.76;
  Blynk.virtualWrite(V2,String(steps)+" Passos");
  Blynk.virtualWrite(V4,String(distance)+" Metros");
 }

}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Alarm.timerRepeat(1, speedControler);  
}

void loop(){
  Blynk.run();
  Alarm.delay(1);
}

void speedControler(){
  seconds += 1;
  speedTotal = (distance/seconds)*3.6;
  Blynk.virtualWrite(V3,String(speedTotal)+" Km/H");
  
}

