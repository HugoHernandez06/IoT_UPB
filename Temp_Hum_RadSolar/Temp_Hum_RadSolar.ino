#include <ClosedCube_HDC1080.h>
#include <Wire.h>
#include <AP3216_WE.h>

ClosedCube_HDC1080 sensor;
AP3216_WE myAP3216 = AP3216_WE();

void prunning(float als);
void prunningTemp(double temperature,double humedad);

double temperature;
double humedad;

float als;

void setup() {
  // put your setup code here, to run once:
  sensor.begin(0x40);
  Serial.begin(9600);
  Wire.begin();
  myAP3216.init();
  myAP3216.setMode(AP3216_ALS); 
  myAP3216.setLuxRange(RANGE_20661);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature = sensor.readTemperature();
  humedad = sensor.readHumidity();
  prunningTemp(temperature,humedad);
  delay(2000);
  als = myAP3216.getAmbientLight();
  prunning(als);
  delay(1000);
}

void prunningTemp(double temperature,double humedad){
  double avgTemp;
  double avgHum;
  int num = 15;
  for(int i=0;i<num;i++){
    avgTemp = temperature + avgTemp;
    avgHum = humedad + avgHum;
  }
  temperature = avgTemp/num;
  humedad = avgHum/num;
  Serial.print(" Prom Temperatura = ");
  Serial.print(temperature);
  Serial.print("°C Prom Humedad = ");
  Serial.print(humedad);
  Serial.print("\n");
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
