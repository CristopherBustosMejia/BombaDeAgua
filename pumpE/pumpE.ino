#include <WiFi.h>
#include <HTTPClient.h>

#define trigger 4

const char* ssid = "ESP32";
const char* pass = "Cristo3103";
const char* turnON = "http://192.168.4.1/deviceON";
const char* turnOFF = "http://192.168.4.1/deviceOFF";

bool flag = false;

String answer;

void setup() {
  Serial.begin(115200);
  delay(50);
  pinMode(trigger,INPUT_PULLDOWN);

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