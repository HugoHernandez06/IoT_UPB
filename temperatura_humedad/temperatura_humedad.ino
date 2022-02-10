#include <ClosedCube_HDC1080.h>
#include <Wire.h>

ClosedCube_HDC1080 sensor;
float n;
double temperature;
double humedad;

void setup(){
sensor.begin(0x40);
Serial.begin(9600);
}

void loop(){
  float avgTemp = 0;
  float avgHum = 0;
  n = random(10,20);
  for(int i=0;i<n;i++){
    temperature = sensor.readTemperature();
    humedad = sensor.readHumidity();
    avgTemp = temperature + avgTemp;
    avgHum = humedad + avgHum;
  }
  temperature = avgTemp/n;
  humedad = avgHum/n;
  Serial.print("Numero de pruebas = ");
  Serial.print(n);
  Serial.print(" Prom Temperatura = ");
  Serial.print(temperature);
  Serial.print("°C Prom Humedad = ");
  Serial.print(humedad);
  Serial.print("%\n");
  delay(2000);
}
