#define SENSORPIN0 A0
#define SENSORPIN1 A1

int boton = 13;
int led = 12;
int val;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);

  Serial.begin(9600);
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
  
  sensorReading(SENSORPIN0,"sensor1");
  sensorReading(SENSORPIN1,"sensor2");

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
