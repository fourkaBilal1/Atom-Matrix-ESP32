#include <WiFi.h>
#include <Wire.h>
#include "M5Atom.h"
#include <HTTPClient.h>

uint8_t DisBuff[2 + 5 * 5 * 3];
void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    for (int i = 0; i < 25; i++)
    {
        DisBuff[2 + i * 3 + 0] = Rdata;
        DisBuff[2 + i * 3 + 1] = Gdata;
        DisBuff[2 + i * 3 + 2] = Bdata;
    }
}

// Replace with your network credentials
const char* ssid     = "depinfo";
const char* password = "123456789";

// Set web server port number to 80
 WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  M5.begin(true, false, true);
  delay(50);
  setBuff(0xff, 0x00, 0x00);
  M5.dis.displaybuff(DisBuff);
  
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();

}

void loop(){
  if (M5.Btn.wasPressed())
  {
    Serial.println("button pressed");
    HTTPClient http;
    String serverName = "http://192.168.4.2/light";
    http.begin(serverName.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
     
  }
  delay(50);
  M5.update();
}
 
   
