#include <OneWire.h>
#include <DallasTemperature.h>

#define BAUDRATE 9600
const int tempSensor = 11;
int sensorPin0 = A0;
int sensorPin1 = A1;
int boton = 13;
int led = 12;
int val;
int fan = 10;
int valve = 9;
int humiditySensor = 8;
String data;
bool valveIsOn = false;
bool fanIsOn = false;
OneWire oneWireInstance(tempSensor);
DallasTemperature DS18B20sensor(&oneWireInstance);

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(fan,OUTPUT);
  pinMode(valve,OUTPUT);
  pinMode(humiditySensor,OUTPUT);
  Serial.begin(BAUDRATE);
  // 1-wire bus begin
  DS18B20sensor.begin();
}

void loop()
{
  if(Serial.available()>0){
    data = Serial.readString();
    temperatureControl(data);
    valveControl(data);
    humiditySensorControl(data);
  }

  val = digitalRead(boton);
  if (val == HIGH)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  
  sensorReading(sensorPin0,356,1006,"sensor1");
  sensorReading(sensorPin1,354,1021,"sensor2");
  //retrieves temperatures from sensor
  DS18B20sensor.requestTemperatures();
  tempSensorC(0,"tempSensor1");
  
}

void temperatureControl(String data){
  //fan control from serial communication
  if(data == "fanOn"){
    fanIsOn = true;
    digitalWrite(fan,HIGH);
  }
  if(data == "fanOff"){
    fanIsOn = false;
    digitalWrite(fan,LOW);
  }
  
  //fan control based on temperature
  if(fanIsOn == false){
    int temperature = round(DS18B20sensor.getTempCByIndex(0));
    if(temperature > 30){
      digitalWrite(fan,HIGH);
    }else{
      digitalWrite(fan,LOW);
    }
  }
}

void tempSensorC(int sensorId,String text){
  float temperature = DS18B20sensor.getTempCByIndex(sensorId);
  String msg = ""+String(temperature,2)+text;
  Serial.println(msg);
}

void sensorReading(int sensor,int min, int max, String texto){
  int val = analogRead(sensor);
  if(val < min){
    val = min;
  }
  if(val > max){
    val = max;
  }
  val = map(val,min,max,100,0);
  String cadena = ""+String(val)+texto;
  Serial.println(cadena);
}

void valveControl(String data){
  // valve control from serial communication
    if(data=="valveOn"){
      valveIsOn = true;
      digitalWrite(valve,HIGH);
    }
    if(data=="valveOff"){
      valveIsOn = false;
      digitalWrite(valve,LOW);
    }
}

void humiditySensorControl(String data){
  // humidity sensor control from serial communication
  if(data=="humiditySensorOn"){
    digitalWrite(humiditySensor,HIGH);
  }
  if(data=="humiditySensorOff"){
    digitalWrite(humiditySensor,LOW);
  }
}
