
#include<WiFi.h>
#include<Arduino.h>
#include <ArduinoJson.h>
#include<WebServer.h>
#include"web_page.h"
#include <AccelStepper.h>
#include <EEPROM.h>



void btn_process();
void send_webpage();
void right();
void left();
void stop();
void home();

//void sendxml();
void sendJson();
AccelStepper stepper =AccelStepper(1,23,22);
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

#define ONBOARD_LED  2
#define step_pin 23
#define dir_pin 22
#define EEPROM_SIZE 1
int led=0;
int stepper_mode=0;
int position=50;
  int counter=0;
  char output[4];
void setup() {
  EEPROM.begin(EEPROM_SIZE);
position=EEPROM.read(0);
stepper.setMaxSpeed(1000);
 
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  pinMode(1,INPUT_PULLUP);
 
  Serial.begin(115200);
 char ssid[]="frommer";
 char pass[]="karby2212";

 WiFi.begin(ssid,pass);
 while(WiFi.status() !=WL_CONNECTED){
delay(500);
Serial.println(".");
 }
Serial.println("wifi connected");

 Serial.println(WiFi.SSID());
Serial.println(WiFi.localIP());
server.on("/",send_webpage);

server.on("/json",sendJson);
server.on("/left",left);
server.on("/right",right);
server.on("/stop",stop);
server.on("/home",home);
server.on("/btn", btn_process);
 server.begin();
 
  // put your setup code here, to run once:

}

void loop() {
  server.handleClient();
  stepper.setSpeed(400*stepper_mode);


if(stepper_mode==1&&position>0){
  
  stepper.runSpeed();
  counter++;
  if((counter%500)==0){
position=position-stepper_mode;

  }
}
if(stepper_mode==-1&&position<100){
  
  stepper.runSpeed();
  counter++;
  if((counter%500)==0){
position=position-stepper_mode;

  }
}
  // put your main code here, to run repeatedly:

}

void send_webpage(){
  server.send(200,"text/html",webpage);
  

}
void left(){
  stepper_mode=1;
     server.send(200, "text/plain","");
}
void right(){
  stepper_mode=-1;
     server.send(200, "text/plain","");
}
void stop(){
  stepper_mode=0;
  EEPROM.write(0,position);
  EEPROM.commit();
     server.send(200, "text/plain","");
}
void home(){
  int home=digitalRead(1);
  stepper.setSpeed(400);
while(home){
  stepper.runSpeed();
  home=digitalRead(1);
}
   
   position=0;
  
server.send(200,"text/plain","");

}
void btn_process(){
  led=!led;


 digitalWrite(2,led);

  Serial.println("led pressed");
  if(led){
   server.send(200, "text/plain","ON");
  }
   else
   {
    server.send(200, "text/plain","OFF");
   }
   
}

void sendJson(){
DynamicJsonDocument  doc(1024);
char output[1024];
doc["position"]=position;

serializeJsonPretty(doc,output);
Serial.println(output);
server.send(200,"text/plain",output);
}