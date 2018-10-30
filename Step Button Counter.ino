#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Time.h>
#include <TimeAlarms.h>

char auth[] = "a68edab7acfe460e98189f673f539264";


char ssid[] = "GVT-EF9C";
char pass[] = "0038624284";
int steps = 0;
int steps2Seconds = 0;
int stepHolder =0;
int seconds = 0;
float speedTotal = 0;
float distance = 0;
float Height = 1.73;
float Weight = 89.5;
float calories = 0;


BLYNK_WRITE(V1){
 if(param.asInt()==1)
 {
  steps++;
  Blynk.virtualWrite(V2,String(steps)+" Passos");
 }

}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Alarm.timerRepeat(2, speedControler);  
}

void loop(){
  Blynk.run();
  Alarm.delay(1);
}

void speedControler(){
  seconds += 2;
  steps2Seconds = steps-stepHolder;
  stepHolder = steps;
  float stride = strideComputer(steps2Seconds);
  float nowDistance = steps2Seconds*stride;
  distance += nowDistance;
  speedTotal = (nowDistance/2)*3.6;
  calories += 1.25*speedTotal*Weight/1800;
  Blynk.virtualWrite(V3,String(speedTotal)+" Km/H");
  Blynk.virtualWrite(V4,String(distance)+" Meters");
  Blynk.virtualWrite(V5,String(calories)+" Calories");
}

float strideComputer(int stepsCount){
  float stride =0;
  switch (stepsCount){
    case 0 ...1:
    stride = Height/5;
    break;
    case 2:
    stride = Height/4;
    break;
    case 3:
    stride = Height/3;
    break;
    case 4:
    stride = Height/2;
    break;
    case 5:
    stride = Height/1.2;
    break;
    case 6 ...7:
    stride = Height;
    break;
    default:
    stride = Height*1.2;
    break;
    
  }
  return stride;
}
