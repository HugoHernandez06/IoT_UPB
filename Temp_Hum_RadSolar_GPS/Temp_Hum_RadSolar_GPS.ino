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
  // Preguntar *
  Serial.begin(115200);
  ss.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorTempHum();
  delay(2000);
  prunningTemp(temperature,humedad);
  delay(2000);
  sensorRadiacionSolar();
  delay(2000);
  prunning(als);
  delay(2000);
  sensorGPS();
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
