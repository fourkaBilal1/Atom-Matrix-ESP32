// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>
#include "M5Atom.h"

// Set your access point network credentials
const char* ssid = "depinfo";
const char* password = "123456789";
// Set web server port number to 80
unsigned int port_ = 80;
AsyncWebServer server(port_);


void setup(){
  M5.begin(true, false, true);
  Wire.begin();  
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request){
    // H-------------------------------------
    for(int i=0; i<5; i++){
        M5.dis.drawpix(0, i, 0x00ffff);
        M5.dis.drawpix(4, i, 0x00ffff);
        M5.dis.drawpix(i, 2, 0x00ffff);
      }
    // A-------------------------------------

    delay(1000);
    M5.dis.drawpix(0, 0, 0x000000);
    M5.dis.drawpix(4, 0, 0x000000);
    for(int i=1; i<4; i++){
      M5.dis.drawpix(i, 0, 0x00ffff);
    }
    // C-------------------------------------

    
    delay(1000);
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        M5.dis.drawpix(i, j, 0x000000);
      }
    }
    for(int i=1; i<4; i++){
      M5.dis.drawpix(i, 0, 0x00ffff);
      M5.dis.drawpix(i, 4, 0x00ffff);
      M5.dis.drawpix(0, i, 0x00ffff);
    }

    
    // K-------------------------------------
    delay(1000);
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        M5.dis.drawpix(i, j, 0x000000);
      }
    }
    for(int i=0; i<5; i++){
      M5.dis.drawpix(0, i, 0x00ffff);
    }
    M5.dis.drawpix(1, 2, 0x00ffff);
    M5.dis.drawpix(2, 1, 0x00ffff);
    M5.dis.drawpix(2, 3, 0x00ffff);
    M5.dis.drawpix(3, 4, 0x00ffff);
    M5.dis.drawpix(3, 0, 0x00ffff);

    delay(1000);
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        M5.dis.drawpix(i, j, 0x000000);
      }
    }
    request->send_P(200, "text/plain", "Hacked");
    
  });

  

  // default settings
  // (you can also pass in a Wire library object like &Wire2)

  M5.dis.clear();
  // Start server
  
  server.begin();
  
}


void loop(){
  
}
