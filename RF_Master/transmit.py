from lib_nrf24 import NRF24
import RPi.GPIO as GPIO
import time
import spidev
import argparse
import sys

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--manual", help="Enter manual mode", action="store_true")
arg = parser.parse_args()

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0,17)
time.sleep(1)

radio.setPayloadSize(32)
radio.setChannel(0x76)
radio.setDataRate(NRF24.BR_1MBPS)
radio.setPALevel(NRF24.PA_MIN)

radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openWritingPipe(pipes[1])
#radio.printDetails()
radio.stopListening()

transaction_good = False
retry_count = 0;

while True: 

    if arg.manual: #send keyboard input to receiver
        x = raw_input("Message: ")
        
        if x == "quit": 
            sys.exit()

        Message = list(x)
        radio.write(Message)  #transmit msg
        print("PL Sent: {}".format(Message))

        if radio.isAckPayloadAvailable(): #check for ack payload, this utilized the auto ack feature
            returnPL = []
            radio.read(returnedPayload, radio.getDynamicPayloadSize()) #read ack payload
            print("ACK PL RECEIVED: {}".format(returnedPayload))
        else:
            print("NO ACK PL RECEIVED")
        time.sleep(1)

    else: #defualt: send toggle "T" request
        
        print("\nToggle Request sending \nWaiting for ACK PL...")
        while not transaction_good and retry_count < 10: #if we havent head back from the receiver, try again
            radio.write("T") 

            radio.startListening()
            if radio.available():
                radio.read(returnedPayload, radio.getDynamicPayloadSize())
                if returnedPayload != "": 
                    print("ACK PL RECEIVED: {}".format(returnedPayload))
                    transaction_good = True

            time.sleep(.5)      
            retry_count = retry_count + 1

        if retry_count >= 10:
            print("\nTIME OUT ERROR: No response from receiver")
            sys.exit()
        else:
            print("\n\Request Sent")
            sys.exit()




