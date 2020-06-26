/******************************************************************************
SHT15 Example
Joel Bartlett @ SparkFun Electronics
16 Sept 2015

This example shows how to get the temperature in F or C and humidity
Developed/Tested with:
SparkFun RedBoard 
Arduino IDE 1.6.5

Connections:
GND  -> A2
Vcc  -> A3
DATA -> A4
SCK  -> A5

Requires:
SparkFun_SHT1X Arduino Library
https://github.com/sparkfun/SHT15_Breakout/

This code is beerware.
Distributed as-is; no warranty is given. 
******************************************************************************/
#include "SHT1X.h"
#include <Wire.h>
#include "DFRobot_VEML7700.h"
#include <string.h>
#include <math.h>

//variables for storing values
char isWaterValid = 0;
float tempC = 0;
float tempF = 0;
float humidity = 0;
float lux = 0.0;
char buf[15] = {0}, empty[100];

//Create an instance of the SHT1X sensor
SHT1x sht15(A2, A3);//Data, SCK


//Create an instance of the VEML7700 sensor
DFRobot_VEML7700 als;

typedef union
{
    unsigned char a[4];
    float b;
} union_data;
void _ftoa(char buf[4], float number)
{
    int i;
    union_data data_s, data_r;
    data_s.b = number; // send할 float값을 세팅한다.
    // 캐릭터 배열의 메모리만을 복사한다!!!!
    memcpy(&data_r.a, &data_s.a, sizeof(data_s.a));
    for (i = 0; i < 4; i++)
        buf[i] = data_s.a[i];
}
float _atof(char buf[4])
{
    int i;
    union_data data_s = { 0,0,0,0 };
    float num = 0;
    for (i = 0; i < 4; i++)
        data_s.a[i] = buf[i];
    num = data_s.b;
    return num;
}
void setup()
{
  Serial.begin(9600); // Open serial connection to report values to host

  pinMode(2, INPUT); // Non-Contact Water Sensor
  
  als.begin();
  buf[0] = 's';
  buf[14] = 'a';
}
int elapseTime;
//-------------------------------------------------------------------------------------------
void loop()
{
  elapseTime = millis();
  
  // Read values from the sensor (SHT1x)
  tempC = sht15.readTemperatureC();
  tempF = sht15.readTemperatureF();
  humidity = sht15.readHumidity();  
  
  if(digitalRead(2) == 0)
  {
    //Serial.print("Non Water Level Sensor : available.");
    isWaterValid = 1;
    buf[1] = 1;
  }
  else
  {
    //Serial.print("Non Water Level Sensor : disavailable.");
    isWaterValid = 0;
    buf[1] = 0;
  }
  
  // Read values from the sensor (VEML7700)
  als.getALSLux(lux);
  
    _ftoa(&buf[2], tempC);
    _ftoa(&buf[6], humidity);
    _ftoa(&buf[10], lux);
  /*elapseTime = millis() - elapseTime;


  Serial.print("Water Level Sensor Value : ");
  Serial.print(analogRead(A0));
  

  Serial.print(" Temp = ");
  Serial.print(tempF);
  Serial.print("F, ");
  Serial.print(tempC);
  Serial.print("C");
  Serial.print(", Humidity = ");
  Serial.print(humidity); 
  Serial.print("%");
  Serial.print(", Lux:");
  Serial.print(lux);
  Serial.print(" lx");
  Serial.print("Elapsed Time : ");
  Serial.println(elapseTime);

  delay(20);*/
}
void serialEvent(){
  Serial.readBytes(empty, sizeof(buf));
  for(int i=0;i<15;i++)
    Serial.write(buf[i]);
}
