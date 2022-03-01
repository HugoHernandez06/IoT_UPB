#include <ClosedCube_HDC1080.h>
#include <Wire.h>

ClosedCube_HDC1080 sensor;
void prunning(double temperature,double humedad);

double temperature;
double humedad;

void setup(){
  sensor.begin(0x40);
  Serial.begin(9600);
}

void loop(){
  temperature = sensor.readTemperature();
  humedad = sensor.readHumidity();
  prunning(temperature,humedad);
  delay(2000);
}

void prunning(double temperature,double humedad){
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
