#include <NewPing.h>

#define SONAR_NUM     3 // Number or sensors.
#define MAX_DISTANCE // Max distance in cm.
#define PING_INTERVAL 200 // Milliseconds between pings.
 
unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.
int a;
//put your height here
int height = 160
 
NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(2, 3, MAX_DISTANCE),
  NewPing(8, 9, MAX_DISTANCE),
  NewPing(10, 11, MAX_DISTANCE),
};
 
void setup() {
  Serial.begin(9600);
  
  DIST(height);
  
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}
 
void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1)
        oneSensorCycle(); // Do something with results.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
    }}}
 
void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}
 
void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    a =(i*100)+(cm[i]/2);
    if ((a == 100) || (a== 200)){
      a=0;
    }
    Serial.write(a);
  }
}
void DIST(int height){
if(height >= 140 && height <= 150){
  MAX_DISTANCE = 20;
  } else if( height >= 151 && height <= 160){
    MAX_DISTANCE = 30;
    }else if( height >= 161 && height <= 170){
    MAX_DISTANCE = 40;
    }else if( height >= 171 && height <= 180){
    MAX_DISTANCE = 50;
    }else if( height >= 181 && height <= 190){
    MAX_DISTANCE = 60;
    }else if( height >= 191 && height <= 200){
    MAX_DISTANCE = 70;
    }else if( height >= 201 && height <= 210){
    MAX_DISTANCE = 80;
    }

}
