unsigned long z=0;
#include <Servo.h>
#define in1 2  
#define in2 3  
#define in3 7 
#define in4 8  
#define ena 5  
#define enb 6  
Servo myservo;  
int pos = 0;    
const int trigPin = 11;
const int echoPin = 12;
long duration;
int distance,Cdistance,Rdistance,Ldistance;
#include <EEPROM.h>
int ThermistorPin = A0;
int Vo;
int res;
float R1 = 10000; // قيمة R1 على متن الطائرة
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; // معاملات Steinhart-hart للثرمستور
//-----------------------------------------
float vout;
float temp;
float value;
void setup() {
   pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  myservo.attach(9);  
  myservo.write(85); 
Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  while(z < 10){
    z++;
   Cdistance=ultrasonic();
  if(Cdistance>30)
  {
    forward();
  }else 
  {
    if(Cdistance<=10&&Cdistance>2)reverse();
    off();                   
    myservo.write(35);       
    delay(300);
    Rdistance=ultrasonic();  
    myservo.write(135);      
    delay(300);
    Ldistance=ultrasonic();  
    myservo.write(85);       
    delay(300);
    comparison(Rdistance, Ldistance); 
    off();                    
    delay(150);
  }
  
  Rdistance=0;
  Ldistance=0;
  Cdistance=0;
   /*
 Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); // حساب المقاومة على الثرمستور
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // درجة الحرارة في كلفن
  T = T - 273.15; // تحويل كلفن إلى مئوية
 // T = (T * 9.0)/ 5.0 + 32.0; // تحويل Celcius إلى Farenheit

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" C"); 

  delay(500);
*/
  vout = analogRead(A0);
  temp = (vout*500)/1023;
  
  EEPROM.write(0,temp);
  // put your main code here, to run repeatedly:

}
res= EEPROM.read(0);
  Serial.print("Temperature: in Celsius "); 
  Serial.print(res);
  Serial.println();
  delay(3000); 
  off();
}
int ultrasonic(void)
{
  distance=0;
 
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;
return distance;
}

void comparison(int r, int l) 
{
  if(r>25||l>25)
  {
   if(r>l||r==l)
   {
     Tright90();
   }else if(l>r)
   {
     Tleft90();
   }
  }else if(r<25&&l<25)
  {
    Tleft180();
  }
}
void forward()
{
  analogWrite(ena,130);
  analogWrite(enb,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void off()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void Tleft90()
{
  analogWrite(ena,160);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(650);
}
void Tright90()
{
  analogWrite(ena,150);
  analogWrite(enb,160);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(750);  
}

void Tleft180()
{
  analogWrite(ena,150);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1500);
}
void reverse()
{
  analogWrite(ena,140);
  analogWrite(enb,140);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(450);
}