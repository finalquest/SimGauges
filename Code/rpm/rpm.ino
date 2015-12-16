#include <openGLCD.h>
#include <bitmaps/n1.h>
#include <bitmaps/n2.h>
#include <bitmaps/n3.h>
#include <bitmaps/n4.h>
#include <bitmaps/n5.h>
#include <bitmaps/n6.h>
#include <bitmaps/n7.h>
#include <bitmaps/n8.h>
#include <bitmaps/nr.h>
#include <bitmaps/nn.h>



int rpm;
int i;
int leds;
int Speed;
int fuel;
int ebrake;
int brake;
int fuelled;
int Turbo;
int gear;
int previous_potion = 0;
int rotate;

char kind_of_data;


void setup(){
  GLCD.Init();
  Serial.begin(115200); 

  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


}



void loop()
{
  //****************************** READ DATA FROM SERIAL ******************************
  while(Serial.available() > 0)
  {

    kind_of_data = Serial.read();
    if (kind_of_data == 'R' ) Read_Rpm();
    if (kind_of_data == 'T' ) Read_Temp();
    if (kind_of_data == 'C' ) Read_Shift();
    //if (kind_of_data == 'S' ) Read_Speed();
    //if (kind_of_data == 'F' ) Read_Fuel();
    //if (kind_of_data == 'E' ) Read_EBrake();
    //if (kind_of_data == 'B' ) Read_Brake();

  }


  //****************************** READ DATA FROM SERIAL END ******************************
}

void Read_Shift() {
  delay(1);
  int Rpm100 = Serial.read()- '0';
  delay(1);
  int Rpm10 = Serial.read()- '0';
  delay(1);
  int Rpm1 = Serial.read()- '0';

  int shift = 100*Rpm100 + 10*Rpm10 + Rpm1;
  Serial.println(shift);
  
  if(shift == 143) GLCD.DrawBitmap(n1, 0, 0);
  if(shift == 159) GLCD.DrawBitmap(n2, 0, 0);
  if(shift == 175) GLCD.DrawBitmap(n3, 0, 0);
  if(shift == 191) GLCD.DrawBitmap(n4, 0, 0);
  if(shift == 207) GLCD.DrawBitmap(n5, 0, 0);
  if(shift == 223) GLCD.DrawBitmap(n6, 0, 0);
  if(shift == 7) GLCD.DrawBitmap(n7, 0, 0);
  if(shift == 8) GLCD.DrawBitmap(n8, 0, 0);
  if(shift == -539) GLCD.DrawBitmap(nr, 0, 0);
  if(shift == 127) GLCD.DrawBitmap(nn, 0, 0);
}

void  Read_Rpm(){

  delay(1);
  int Rpm100 = Serial.read()- '0';
  delay(1);
  int Rpm10 = Serial.read()- '0';
  delay(1);
  int Rpm1 = Serial.read()- '0';

  int rpm = 100*Rpm100 + 10*Rpm10 + Rpm1;
  rpm = map(rpm, 135, 255, 0, 450);
  tone(9,rpm);


}

void  Read_Temp(){

  delay(1);
  int Rpm100 = Serial.read()- '0';
  delay(1);
  int Rpm10 = Serial.read()- '0';
  delay(1);
  int Rpm1 = Serial.read()- '0';

  int rpm = 100*Rpm100 + 10*Rpm10 + Rpm1;
  rpm = map(rpm, 127, 255, 115, 255); 
  
  analogWrite(8,rpm);
  
}

void Read_Speed(){

  delay(1);
  int Speed100 = Serial.read()- '0';
  delay(1);
  int Speed10 = Serial.read()- '0';
  delay(1);
  int Speed1 = Serial.read()- '0';

  Speed = 100*Speed100 + 10*Speed10 + Speed1;

  tone(12, map(Speed,127,255,0,950)); 

}

void Read_Fuel(){
  delay(1);
  int Fuel100 = Serial.read()- '0';
  delay(1);
  int Fuel10 = Serial.read()- '0';
  delay(1);
  int Fuel1 = Serial.read()- '0';

  fuel = 100*Fuel100 + 10*Fuel10 + Fuel1;

  analogWrite(2,map(fuel,127,255,53,183));
  if (fuel<135) digitalWrite(10,HIGH);
  if (fuel>135) digitalWrite(10,LOW); 

} 


void Read_EBrake(){
  delay(1);
  int EBrake100 = Serial.read()- '0';
  delay(1);
  int EBrake10 = Serial.read()- '0';
  delay(1);
  int EBrake1 = Serial.read()- '0';

  ebrake = 100*EBrake100 + 10*EBrake10 + EBrake1;

  if (ebrake>200) digitalWrite(3,HIGH);
  if (ebrake<200) digitalWrite(3,LOW); 

} 
void Read_Brake(){
  delay(1);
  int Brake100 = Serial.read()- '0';
  delay(1);
  int Brake10 = Serial.read()- '0';
  delay(1);
  int Brake1 = Serial.read()- '0';

  brake = 100*Brake100 + 10*Brake10 + Brake1;

  if (brake>200) digitalWrite(5,HIGH);
  if (brake<200) digitalWrite(5,LOW); 

} 
