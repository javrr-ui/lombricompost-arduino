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
  Serial.print("Temperature: ");
  Serial.print(DS18B20sensor.getTempCByIndex(0));
  Serial.println(" C");

  delay(500);

}


void sensorReading(int sensor,String texto)
{
  float humedad = analogRead(sensor);
  float res = ((humedad / 1020) * 100)-100;
  if (res < 0)
  {
    res = res * -1;
  }
  String cadena = ""+String(res,2)+texto;

  Serial.println(cadena);
}
