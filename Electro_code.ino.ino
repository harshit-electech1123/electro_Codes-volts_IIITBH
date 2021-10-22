#include <IRremote.h>
#include<Servo.h>
Servo servo1;
Servo servo2;
int MQ2pin = A0;
#define TEMPERATURE A2
int pirstate = 0;
#define pir 7
const int gas = 0;
int light = 3;
int light2 = 13;
int fan = 6;
int ls = 0;
int fs = 0;


int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;


int speed_decider(int temp){
  if(temp<20)
    return 0;
  else if(temp>40)
    return 255;
  else
    return map(temp, 20, 40, 0, 255);
}
void setup()
{
  
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(light2, OUTPUT);
  pinMode(8,INPUT);
  pinMode(9,OUTPUT);
  pinMode(A3,INPUT);
  servo1.attach(5);
  servo2.attach(2);
  Serial.begin(9600);
  irrecv.enableIRIn(); 
}

void loop() {
  digitalWrite(9,LOW);
  delayMicroseconds(10);
  digitalWrite(9,HIGH);
  delayMicroseconds(10);
  digitalWrite(9,LOW);
  int val=pulseIn(8,HIGH);
  Serial.println(val);
  float angle = -0.010*val + 103.13;
  servo1.write(angle);
  int phtr=analogRead(A3);
  Serial.println(phtr);
  float angle2=0.133*phtr - 0.802;
  servo2.write(angle2);
  if (irrecv.decode(&results)) { 
    unsigned int value = results.value;  
   // Serial.println(value);
      if(value == 2295)
      { 
        
        digitalWrite(light, HIGH);
        ls+= 1;
        if(ls% 2 == 0){
        digitalWrite(light,LOW);
        ls = 0;
        }
    delay(100);
      }
  
      if(value == 18615)
      {
        digitalWrite(6,HIGH);
        fs += 1;
        if(fs %2  == 0){
        digitalWrite(fan, LOW);
        fs = 0;
        }
    delay(100);
  }       
   
    irrecv.resume(); 
  }
  if(fs == 1){
        int temperature = analogRead(TEMPERATURE);
        temperature = map(temperature, 20, 358, -40, 125);
        analogWrite(fan, speed_decider(temperature));
  }
  
  pirstate = digitalRead(pir);
  Serial.println(pirstate);
  if (pirstate == 1) {
    digitalWrite(light2, HIGH);
  } else {
    digitalWrite(light2, LOW);
  }
  delay(10);
  
  float sensorValue,MQ2pin;
sensorValue = analogRead(MQ2pin); 

  if(sensorValue >= 850){
    digitalWrite(A1,HIGH);
   // Serial.print(sensorValue);
   // Serial.println(" SMOKE !!!");
  }
  else{
     digitalWrite(A1,LOW);
    //Serial.println("Sensor Value: ");
    //Serial.println(sensorValue);
  }
  delay(250);
  
}
float getsensorValue(int pin)
  {
  return (analogRead(pin));
  }  
