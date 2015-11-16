#include <AFMotor.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <Servo.h> 
#include <SPI.h>

#define REQ_BUF_SZ   90
byte mac[] = { 0x98, 0x5a, 0xeb, 0xdb, 0x5b, 0x8b }; // get from the Network Setting, or can set 
//anything you want

IPAddress ip(192 ,168, 10, 251); // IP Address for the shield, U can set anything you want
//char server[] = "www.google.com";  
//char server[] = "192.168.1.53";  
char server[] = "192.168.10.101";   
//byte serverIP[] = { 192, 168, 1, 58 }; //IP of your PC
unsigned long previousMillis = 0;  // last time update
const unsigned long interval = 10L * 500L;
//long interval  = 5000; // interval at which to do something (milliseconds) 

const int LED = 13;
const int servoPin = 10;
const int ALARM = 8;
const int SENSOR2 = 50;
const int SENSOR = 53; // Declare sensor Pin position
int value = 0;
int value2 = 0;
int angle = 0;
int doneFlag = 1;
boolean reading = false;
boolean scanning = false;
char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter

Servo servo;
EthernetClient client;
//EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
  delay(1000);
//  if (Ethernet.begin(mac) == 0) {
//    Serial.println("Failed to configure Ethernet using DHCP");
//////    // try to congifure using IP address instead of DHCP:
//    Ethernet.begin(mac, ip);
//  }
//    Serial.println(Ethernet.localIP());
//  //server.begin();
  delay(1000);
  pinMode(LED,OUTPUT);
 // pinMode(ALARM,OUTPUT);
  pinMode(SENSOR,INPUT);
  //digitalWrite(LED,HIGH);
  servo.attach(servoPin);
 // httpRequest();
 // sendRequest();
   Serial.println("Starting motor");
}

void loop() {
   value2 = digitalRead(SENSOR2); 
   Serial.println(value2);
    //if(
    for(angle = 0; angle < 45; angle++)  
      {    
      Serial.println(angle);                              
      servo.write(angle);               
      delay(10);                   
      } 
       delay(1000);
       for(angle = 45; angle > 0; angle--)  
      {    
      Serial.println(angle);                              
      servo.write(angle);               
      delay(10);                   
      } 
      delay(3000);

//    if (client.available()) {
//    boolean currentLineIsBlank = true;
//    char c = client.read();
//    //Serial.print(c);
//    if(reading && c == ' ') reading = false;
//    if(c == '<'){
//      reading = true; 
//    } else if (reading){
//      if(c != '>'){
//         inString[stringPos] = c;
//          stringPos ++;
//      } else {
//        reading = false;
//         if(strcmp(inString,"1") == 0){
//            Serial.println("Scanning completed");
//             Serial.println("Motor Open Lid");
//             scanning = true;
//            for(angle = 0; angle < 45; angle++)  
//            {                                  
//            servo.write(angle);               
//            delay(10);                   
//            } 
//         } else {
//            Serial.println("Scanning incompleted");
//         }
//      }
//    }
//    }   
//  //Loop problem just do only once
//    unsigned long currentMillis = millis();  
//     if((currentMillis - previousMillis) >= interval) {
//     Serial.println("Fetched Data");
//     previousMillis = millis();
//     httpRequest();
//  }
//      
//     value = digitalRead(SENSOR); 
//     if(value == HIGH){
//            digitalWrite(ALARM,LOW);
//           } else {
//            //Sending request to server
//            if(scanning){ // in case somebody trigger IR
//            digitalWrite(ALARM, HIGH);
//            delay(1000);
//            sendRequest();
//            //Close Lid
//            Serial.println("Closing Lid");
//            scanning = false;
//            delay(1000);
//            for(angle = 45; angle > 0; angle--)    
//             {    
//             Serial.println(angle);                            
//             servo.write(angle);           
//             delay(10);    
//             }            
//            }
//        }
}

void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
   client.stop();
   Serial.println("httpRequest");
  // if there's a successful connection:
  if (client.connect(server, 8080)) {
    Serial.println("Start Connecting");
    // send the HTTP GET request:
    client.println("GET /kioskmajor/readprocess.php HTTP/1.0");
    client.println("Host: 192.168.10.101");  
    client.println("Connection: close");
    client.println();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

void sendRequest() {
   
 // client.stop();
   Serial.println("Send Request");
  // if there's a successful connection:
  if (client.connect(server, 8080)) {
    Serial.println("Start Sending");
    client.println("GET /kioskmajor/count.php?count=1 HTTP/1.1");
    client.println("Host: 192.168.10.101");  
    client.println("Connection: close");
    client.println();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}
