#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
/**
COMMON PARAMS:
  T = location parameter of the blinds; 
      0 = closed  --->  60 = open 
  dT = Delta T; how much time to reach desired position
  switchState = state of single pole double throw switch 
      0 = no nothing
      1 = open
      2 = close
**/
RF24 radio(7, 8);

//pins
const int MOTOR_OPEN_PIN = 1;
const int MOTOR_CLOSED_PIN = 2;
const int SWITCH_OPEN_PIN = 3;
const int SWITCH_CLOSE_PIN = 4;

//comparitor const
const int BLIND_OPEN_STATE = 60; //t=60 when fully open
const int BLIND_CLOSED_STATE = 0; //t=0 when fully closed

void setup() {
  pinMode(MOTOR_OPEN_PIN, OUTPUT);
  pinMode(MOTOR_CLOSE_PIN, OUTPUT);
  pinMode(SWITCH_OPEN_PIN, INPUT);
  pinMode(SWITCH_CLOSE_PIN, INPUT);
  
  //RF OPTIONS
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openReadingPipe(0, 0xF0F0F0F0E1LL);
  radio.setAutoAck(0, true);
  radio.enableDynamicPayloads();
  radio.enableAckPayload();
  radio.powerUp();
  radio.startListening();
  
  int T = 0; //blinds must manually be set closed when restarting software
}

//alter blind position based on 
int changeBlindPosition(int dT, int T){
    
}

//check and parse any incoming RF data
int checkRF(int T){
  char message[] = "";
  
  if(radio.available()){

    while(radio.available()){
      radio.read(&message, radio.getDynamicPayloadSize());  
    }
    
    if(message[1] != ""){
        Serial.println(message);
        if(message[1] = "T"){
          if(digitalRead(led_pin) == LOW){
            digitalWrite(led_pin, HIGH);  
          }else{
            digitalWrite(led_pin, LOW);  
          }
        }
    }
}

int

void loop(void){
  RF_dT = checkRF(T);

  if(RF_dT != 0){
    dT = RF_dt;  
  }else if(digitalRead(BUTTON_CLOSE_PIN) == HIGH){
    dT = 1;
  }else if(digitalRead(BUTTON_OPEN_PIN) == HIGH){
    dT = -1;  
  }else{
    dT = 0;
  }

  if(lastdT != dT){
    T = changeBlindPosition(dT, T);
  }

  lastdT = dT;
 
}
