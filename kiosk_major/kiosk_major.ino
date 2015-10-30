#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>


byte mac[] = { 0x98, 0x5a, 0xeb, 0xdb, 0x5b, 0x8b }; // get from the Network Setting
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // or use any

IPAddress ip(192 ,168, 1, 251); // IP Address for the shield, Should do fix IP

byte server[] = { 192, 168, 1, 46 };

const int LED = 13;
const int ALARM = 8;
const int SENSOR = 53; // Declare sensor Pin position
int value = 0;

EthernetClient client;

void setup() {
  
  Ethernet.begin(mac,ip);
  Serial.begin(9600);
  delay(1000);
  Serial.println(Ethernet.localIP());
  Serial.println("Connecting to Ethernet....");
   if(client.connect(server,80)){   
    Serial.println("Connected");
    digitalWrite(LED,HIGH); 
  } else {
//  if you didn't get a connection to the server:
     Serial.println("Connection failed");
     digitalWrite(LED,LOW);
  } 
  pinMode(LED,OUTPUT);
  pinMode(ALARM,OUTPUT);
  pinMode(SENSOR,INPUT);
}

void loop() {
   // put your main code here, to run repeatedly:
     value = digitalRead(SENSOR); 
     Serial.print(value);
     if(value == HIGH){ 
            digitalWrite(ALARM,LOW);
           } else {
            digitalWrite(ALARM, HIGH);
            Serial.println("Found one Start Sending");
            delay(1000);
            if(client.connect(server,80)){  
            Serial.println("Connected Sending");
            client.println("GET /kiosk/count.php?count=1 HTTP/1.1");
            client.println("Host: 192.168.1.46");
            client.println("Connection: close");
            client.println();  
            client.stop();         
             } else {
              Serial.println("Connection failed");
             }
           }
//        if (client.available()) {
//     char c = client.read();
//     Serial.print(c);
//}
//}
}
