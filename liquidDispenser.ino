#include <NewPing.h>
const int ECHO_PIN = 13;
const int TRIG_PIN = 12;
const int VCC_PIN = 11;
boolean active = false;
const int RELAY_PIN = A0;
short pump_time = 2000;
const short pin_f = 2;
const short pin_a = 3;
const short pin_b = 4;
const short pin_e = 7;
const short pin_d = 6;
const short pin_c = 8;
const short pin_g = 9;
//jmp vermelho := F-5
//jmp verde := B
//branco A
//marrom G
//azul E
//verde BAIXO d
//branco BAIXO C
short digi0[] = {pin_a,pin_b,pin_c,pin_d,pin_e,pin_f};
short digi1[] = {pin_b,pin_c};
short digi2[] = {pin_a,pin_b,pin_g,pin_e,pin_d};
short digi3[] = {pin_a,pin_b,pin_c,pin_d,pin_g};
short digi4[] = {pin_f,pin_g,pin_c,pin_b};
short tot_digits[] = {digi1,digi2,digi3,digi4};
void activateDisplay(short pinArray[],short len);
void unactivateDisplay(short pinArray[],short len);
NewPing sonar(TRIG_PIN,ECHO_PIN,11);
void setup(){
  activateDisplay(digi2,5);
  Serial.begin(115200);
  for(int i=2;i<=9;i++){
    pinMode(i,OUTPUT);
  }  
  pinMode(VCC_PIN,OUTPUT);
  pinMode(RELAY_PIN,OUTPUT);
  digitalWrite(5,HIGH);
  digitalWrite(VCC_PIN,HIGH);
  digitalWrite(RELAY_PIN,LOW);
 
}

void loop(){
  short pot_read = analogRead(A4);
  Serial.println(analogRead(A4));
  delay(200);
  if (sonar.ping_cm()> 0 && active == false){
    digitalWrite(RELAY_PIN,HIGH);
    delay(pump_time);
    digitalWrite(RELAY_PIN,LOW);
    active = true;
  }
  if (sonar.ping_cm() == 0 && active == true){
  active = false;
  }
  if (pot_read < 256){
      unactivateDisplay(digi2,5);
      unactivateDisplay(digi3,5);
      unactivateDisplay(digi4,4);
      activateDisplay(digi1,2);
      pump_time = 1000;

  }
  else if (pot_read < 512){
    unactivateDisplay(digi1,2);
    unactivateDisplay(digi3,5);
    unactivateDisplay(digi4,4);
    activateDisplay(digi2,5);
    pump_time = 2000;


  }
  else if (analogRead(A4) < 768){
    unactivateDisplay(digi1,2);
    unactivateDisplay(digi2,5);
    unactivateDisplay(digi4,4);
    activateDisplay(digi3,5);
    pump_time = 3000;

  }
  else{
    unactivateDisplay(digi1,2);
    unactivateDisplay(digi2,5);
    unactivateDisplay(digi3,4);
    activateDisplay(digi4,4);
    pump_time = 4000;
  }
}
void activateDisplay(short pinArray[],short len){
  for (short i=0;i<len;i++){    
    digitalWrite(pinArray[i],HIGH);
  }
}

void unactivateDisplay(short pinArray[],short len){
  for (short i=0;i<len;i++){    
    digitalWrite(pinArray[i],LOW);
  }
}
