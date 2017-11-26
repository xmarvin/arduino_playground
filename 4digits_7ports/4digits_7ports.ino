#include "dht11.h"
dht11 DHT;
#define DHT11_PIN 13
int ledState=0;
int data = 2;// set pin 14 of 74HC595as data input pin SI 
int clock = 5;// set pin 11 of 74hc595 as clock pin SCK
int latch = 4;// set pin 12 of 74hc595 as output latch RCK 
// select pin for cathode
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int dp = 8;
// select pin for anode
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;
// mapping port 1 - q0, port2 - q1, etc. port8 - q7
// set variable
long n = 1230;
int x = 100;
int del = 55;  // fine adjustment for clock
 int humidity=0;
  int temperature=0;
void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);  
}

void displayHumidity(){
  int fd = humidity / 10;
  int ld = humidity % 10;
  Display(1, fd);
  Display(2, ld);
  }
  
void displayTemperature(){
  int fd = temperature / 10;
  int ld = temperature % 10;
  Display(3, fd);
  Display(4, ld);
  }
 long last_update = 0;
void loop()

{
  long now = millis();
  if (last_update == 0 || (last_update + 10000 < now)){
    last_update = now;
  int chk;
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk) {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }
  // DISPLAT DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);  
    humidity = DHT.humidity;
    temperature = DHT.temperature;
  }
  displayTemperature();
  displayHumidity();  
}

int bits[] = {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};
int masks[] = {B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111};

void changeCell(int led, int state){
   ledState = ledState & masks[led];  //clears ledState of the bit we are addressing
   if(state == HIGH){ledState = ledState | bits[led];} //if the bit is on we will add it to ledState
   updateCells(ledState);              //send the new LED state to the shift register
 }
void updateCells(int value){ 
  digitalWrite(latch, LOW); 
  shiftOut(data, clock, MSBFIRST, value); 
  digitalWrite(latch, HIGH);  
}

void digitalWriteWithHC(byte pin, byte value){
  if (pin<=8){
    changeCell(pin-1, value);
  }
  else{
    digitalWrite(pin, value);
  }
}
///////////////////////////////////////////////////////////////
void WeiXuan(unsigned char n)//
{
  switch (n)
  {
    case 1:
      digitalWriteWithHC(d1, LOW);
      digitalWriteWithHC(d2, HIGH);
      digitalWriteWithHC(d3, HIGH);
      digitalWriteWithHC(d4, HIGH);
      break;
    case 2:
      digitalWriteWithHC(d1, HIGH);
      digitalWriteWithHC(d2, LOW);
      digitalWriteWithHC(d3, HIGH);
      digitalWriteWithHC(d4, HIGH);
      break;
    case 3:
      digitalWriteWithHC(d1, HIGH);
      digitalWriteWithHC(d2, HIGH);
      digitalWriteWithHC(d3, LOW);
      digitalWriteWithHC(d4, HIGH);
      break;
    case 4:
      digitalWriteWithHC(d1, HIGH);
      digitalWriteWithHC(d2, HIGH);
      digitalWriteWithHC(d3, HIGH);
      digitalWriteWithHC(d4, LOW);
      break;
    default :
      digitalWriteWithHC(d1, HIGH);
      digitalWriteWithHC(d2, HIGH);
      digitalWriteWithHC(d3, HIGH);

      digitalWriteWithHC(d4, HIGH);
      break;
  }
}
void Num_0()
{
  digitalWriteWithHC(a, HIGH);
  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, HIGH);
  digitalWriteWithHC(e, HIGH);
  digitalWriteWithHC(f, HIGH);
  digitalWriteWithHC(g, LOW);
  digitalWriteWithHC(dp, LOW);
}
void Num_1()
{
  digitalWriteWithHC(a, LOW);
  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, LOW);
  digitalWriteWithHC(e, LOW);
  digitalWriteWithHC(f, LOW);
  digitalWriteWithHC(g, LOW);
  digitalWriteWithHC(dp, LOW);
}
void Num_2()
{
  digitalWriteWithHC(a, HIGH);
  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, LOW);
  digitalWriteWithHC(d, HIGH);
  digitalWriteWithHC(e, HIGH);
  digitalWriteWithHC(f, LOW);
  digitalWriteWithHC(g, HIGH);
  digitalWriteWithHC(dp, LOW);
}
void Num_3()
{
  digitalWriteWithHC(a, HIGH);

  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, HIGH);
  digitalWriteWithHC(e, LOW);
  digitalWriteWithHC(f, LOW);
  digitalWriteWithHC(g, HIGH);
  digitalWriteWithHC(dp, LOW);
}
void Num_4()
{
  digitalWriteWithHC(a, LOW);
  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, LOW);
  digitalWriteWithHC(e, LOW);
  digitalWriteWithHC(f, HIGH);
  digitalWriteWithHC(g, HIGH);
  digitalWriteWithHC(dp, LOW);
}
void Num_5()
{
  digitalWriteWithHC(a, HIGH);
  digitalWriteWithHC(b, LOW);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, HIGH);
  digitalWriteWithHC(e, LOW);
  digitalWriteWithHC(f, HIGH);
  digitalWriteWithHC(g, HIGH);
  digitalWriteWithHC(dp, LOW);
}
void Num_6()
{
  digitalWriteWithHC(a, HIGH);
  digitalWriteWithHC(b, LOW);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, HIGH);
  digitalWriteWithHC(e, HIGH);
  digitalWriteWithHC(f, HIGH);
  digitalWriteWithHC(g, HIGH);
  digitalWriteWithHC(dp, LOW);

}
void Num_7()
{
  digitalWriteWithHC(a, HIGH);
  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, LOW);
  digitalWriteWithHC(e, LOW);
  digitalWriteWithHC(f, LOW);
  digitalWriteWithHC(g, LOW);
  digitalWriteWithHC(dp, LOW);
}
void Num_8()
{
  digitalWriteWithHC(a, HIGH);
  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, HIGH);
  digitalWriteWithHC(e, HIGH);
  digitalWriteWithHC(f, HIGH);
  digitalWriteWithHC(g, HIGH);
  digitalWriteWithHC(dp, LOW);
}
void Num_9()
{
  digitalWriteWithHC(a, HIGH);
  digitalWriteWithHC(b, HIGH);
  digitalWriteWithHC(c, HIGH);
  digitalWriteWithHC(d, HIGH);
  digitalWriteWithHC(e, LOW);
  digitalWriteWithHC(f, HIGH);
  digitalWriteWithHC(g, HIGH);
  digitalWriteWithHC(dp, LOW);
}
void Clear()  // clear the screen
{
  digitalWriteWithHC(a, LOW);
  digitalWriteWithHC(b, LOW);
  digitalWriteWithHC(c, LOW);
  digitalWriteWithHC(d, LOW);

  digitalWriteWithHC(e, LOW);
  digitalWriteWithHC(f, LOW);
  digitalWriteWithHC(g, LOW);
  digitalWriteWithHC(dp, LOW);
}
void pickNumber(unsigned char n)// select number
{
  switch (n)
  {
    case 0: Num_0();
      break;
    case 1: Num_1();
      break;
    case 2: Num_2();
      break;
    case 3: Num_3();
      break;
    case 4: Num_4();
      break;
    case 5: Num_5();
      break;
    case 6: Num_6();
      break;
    case 7: Num_7();
      break;
    case 8: Num_8();
      break;
    case 9: Num_9();
      break;
    default: Clear();
      break;
  }
}
void Display(unsigned char x, unsigned char Number)//  take x as coordinate and display number
{
  WeiXuan(x);
  pickNumber(Number);
  if (x == 2){
    digitalWriteWithHC(dp, HIGH);
  }
  delay(1);
  Clear() ; // clear the screen
}
