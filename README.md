# IoT_UPB
Hugo Alejandro Hernandez Cardenas

1. Sensor Temperatura y Humedad

```C++
// Librerias para el Manejo del Sensor HDC1080
#include <ClosedCube_HDC1080.h>
#include <Wire.h>

// Se declaran las funciones y objetos
ClosedCube_HDC1080 sensor;
void prunning(double temperature,double humedad);

// Se declaran las variables a utilizar
double temperature;
double humedad;

// Se declara en el setup la frecuencia en la que se van a leer los datos del sensor 
void setup(){
  sensor.begin(0x40);
  Serial.begin(9600);
}

// En el ciclo se declaran las variables que van a obtener la temperatura y la humedad, luego son enviadas como parametros de la función de prunning
void loop(){
  temperature = sensor.readTemperature();
  humedad = sensor.readHumidity();
  prunning(temperature,humedad);
  delay(2000);
}

// Se realiza el proceso de prunning con un paquete de 15 datos 
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
```

2. Sensor Radiación Solar


3. Sensor GPS


4. Sensores de Temperatura, Humedad y Radiación Solar


5. Sensores de Temperatura, Humedad, Radiación Solar y GPS

