#include <OneWire.h>
#include <DallasTemperature.h>

#define BAUDRATE 9600
const int tempSensor = 11;
int sensorPin0 = A0;
int sensorPin1 = A1;
int boton = 13;
int led = 12;
int val;

OneWire oneWireInstance(tempSensor);
DallasTemperature DS18B20sensor(&oneWireInstance);

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);

  Serial.begin(BAUDRATE);
  // 1-wire bus begin
  DS18B20sensor.begin();
}

void loop()
{
  val = digitalRead(boton);
  if (val == HIGH)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  
  sensorReading(sensorPin0,"sensor1");
  sensorReading(sensorPin1,"sensor2");
  //retrieves temperatures from sensor
  DS18B20sensor.requestTemperatures();
  tempSensorC(0,"tempSensor1");
  delay(500);

}

void tempSensorC(int sensorId,String text){
  String msg = ""+String(DS18B20sensor.getTempCByIndex(sensorId),2)+text;
  Serial.println(msg);
}
void sensorReading(int sensor,String texto){
  int val = analogRead(sensor);
  val = map(val,0,1023,100,0);
  String cadena = ""+String(val)+texto;
  Serial.println(cadena);
}