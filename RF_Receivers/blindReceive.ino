#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(7, 8);
const int led_pin = 4;
void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openReadingPipe(0, 0xF0F0F0F0E1LL);
  radio.setAutoAck(0, true);
  radio.enableDynamicPayloads();
  radio.enableAckPayload();
  radio.powerUp();
  radio.startListening();

}



void loop(void){

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
  
}
