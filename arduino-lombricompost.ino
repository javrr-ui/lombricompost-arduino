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
String fanState="";
bool fanIsOn = false;
OneWire oneWireInstance(tempSensor);
DallasTemperature DS18B20sensor(&oneWireInstance);

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(fan,OUTPUT);

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
  
  sensorReading(sensorPin0,356,1006,"sensor1");
  sensorReading(sensorPin1,354,1021,"sensor2");
  //retrieves temperatures from sensor
  DS18B20sensor.requestTemperatures();
  tempSensorC(0,"tempSensor1");
  //delay(500);
  temperatureControl();
}

void temperatureControl(){

  //fan control from serial communication
  if(Serial.available()>0){
    fanState = Serial.readString();
    if(fanState == "fanOn"){
      fanIsOn = true;
      digitalWrite(fan,HIGH);
    }
    if(fanState == "fanOff"){
      fanIsOn = false;
      digitalWrite(fan,LOW);
    }
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