//Libraries
#include <WiFi.h>
#include <HTTPClient.h>

//IO Pins
#define trigger 4

//Wifi name and password
const char* ssid = "YOUR_SSID"; 
const char* pass = "YOUR_PASSWORD"; 
//Address to consume actions, if you don't change anything on the server begin the default IP: 192.168.4.1
const char* turnON = "http://192.168.4.1/deviceON";
const char* turnOFF = "http://192.168.4.1/deviceOFF";

//Variables
bool flag = false; //Boolean flag to control number of request
String answer; //Variable to give an answer to the client

void setup() {
  //Init Serial 
  Serial.begin(115200);
  delay(50);
  //Init IO Pins
  pinMode(trigger,INPUT_PULLDOWN);
  //Init Wifi
  WiFi.begin(ssid,pass);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a la red con la IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  if(digitalRead(trigger) == HIGH){
    if(!flag){
      answer = getRequest(turnON);
      flag = true; 
    }
  }else{
    if(flag){
      answer = getRequest(turnOFF);
      flag = false;
    }
  }
}

//Function to consume a GET request
String getRequest(const char* URL){
  HTTPClient http;
  http.begin(URL);

  int httpResponseCode = http.GET();

  String payload = "...";

  if(httpResponseCode > 0){
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return payload;
}