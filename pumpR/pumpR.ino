#include <WiFi.h>
#include <WebServer.h>

#define pump 4

const char* ssid = "ESP32";
const char* pass = "Cristo3103";

bool flag = false;

String device = "";
String answer = "";

WebServer server(80);

void setup(){
  Serial.begin(115200);
  delay(50);
  pinMode(pump,OUTPUT);
  WiFi.softAP(ssid,pass);
  IPAddress ip = WiFi.softAPIP(); 

  Serial.print("Nombre de la red -> ");
  Serial.println(ssid);
  Serial.print("Direccion IP -> ");
  Serial.println(ip);

  server.on("/",handleConnectionRoot);
  server.on("/deviceON", handleDeviceON);
  server.on("/deviceOFF", handleDeviceOFF);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor inicializado");
  Serial.println("\nDispositivos Conectados:");
}

void loop(){
  server.handleClient();
}

void handleConnectionRoot(){
  server.send(200, "text/html", "Hola Bienvenido");
}

void handleDeviceON(){
  device = "ESP-R";
  Serial.println(device);
  if(!flag){
    digitalWrite(pump,HIGH);
    flag = true;
  }
  server.send(200, "text/html", answer);
}

void handleDeviceOFF(){
  device = "ESP-R";
  Serial.println(device);
  if(flag){
    digitalWrite(pump,LOW);
    flag = false;
  }
  server.send(200, "text/html", answer);
}

void handleNotFound(){
  server.send(404, "text/plain", "Not Found");
}
