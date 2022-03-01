#include <Wire.h>
#include <AP3216_WE.h>

AP3216_WE myAP3216 = AP3216_WE();
void prunning(float als);

float als;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  myAP3216.init();
  myAP3216.setMode(AP3216_ALS); 
  myAP3216.setLuxRange(RANGE_20661);
  delay(1000);
}
void loop() {
  als = myAP3216.getAmbientLight();
  prunning(als);
  delay(1000);
}
void prunning(float als){
  float avgLux;
  int num = 15;
  for(int i=0;i<num;i++){
    avgLux = als + avgLux;
  }
  als = avgLux/num;
  Serial.print("Lux: "); 
  Serial.println(als);
}
