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
```C++
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
```

3. Sensor GPS
```C++
#include <SoftwareSerial.h>
#include <TinyGPS.h>


TinyGPS gps;
SoftwareSerial ss(2, 0);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  
  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
}
```

4. Sensores de Temperatura, Humedad y Radiación Solar
```C++
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
  Serial.print("Prom Temperatura = ");
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
```

5. Sensores de Temperatura, Humedad, Radiación Solar y GPS
```C++
#include <ClosedCube_HDC1080.h>
#include <Wire.h>
#include <AP3216_WE.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

ClosedCube_HDC1080 sensor;
AP3216_WE myAP3216 = AP3216_WE();
TinyGPS gps;
SoftwareSerial ss(2, 0);

void prunningTemp(double temperature,double humedad);
void prunning(float als);
void smart_delay(int t);

double temperature=0;
double humedad=0;
float als=0;
int estado=0;

void setup() {
  // put your setup code here, to run once:
  sensor.begin(0x40);
  Serial.begin(9600);
  Wire.begin();
  myAP3216.init();
  myAP3216.setMode(AP3216_ALS); 
  myAP3216.setLuxRange(RANGE_20661);
  // Preguntar *
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println("Iniciando Programa");
  estado = 1;
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(estado){
    case 1:
      Serial.println("1. Sensor Humedad y Temperatura");
      sensorTempHum();
      prunningTemp(temperature,humedad);
      estado = 2;
      delay(1000);
    break;
    case 2:
      Serial.println("2. Radiación Solar");
      sensorRadiacionSolar();
      prunning(als);
      estado = 3;
      delay(1000);
    break;
    case 3:
      Serial.println("3. Sensor GPS");
      sensorGPS();
      estado = 4;
      delay(1000);
    break;
    case 4:
      Serial.println("4. Haciendo Bunding");
      estado = 5;
      delay(1000);
    break;
    case 5:
      Serial.println("5. Durmiendo");
      estado = 1;
      delay(3000);
    break;
    default:
      Serial.println("No capturo estados");
      delay(1000);
  }
}

void sensorTempHum(){
  temperature = sensor.readTemperature();
  humedad = sensor.readHumidity();
  prunningTemp(temperature,humedad);
  delay(2000);
}
void sensorRadiacionSolar(){
  als = myAP3216.getAmbientLight();
  prunning(als);
  delay(1000);
}
void sensorGPS(){
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
}
void prunningTemp(double temperature, double humedad){
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
void smart_delay(int t){
  
}
```
