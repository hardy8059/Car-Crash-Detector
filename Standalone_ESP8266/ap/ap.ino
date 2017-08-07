#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int sensorPin = A0;
ESP8266WebServer server(80);
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESPsoft", "123123123");
  server.begin();
  if(result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }
}

void loop()
{
  delay(3000);
  while (server.available()) {
    char c = client.read();
    Serial.write(c);
  }
 
 int sensorValue=analogRead(sensorPin);
 Serial.println("Sensor Reading:");
 Serial.println(sensorValue);
 delay(1000);

if(millis()-lastConnectionTime>postingInterval)
{
  Serial.println("Uploading...");
   int sensorValue=analogRead(sensorPin);
  httpRequest(sensorValue);
}
}
}
void httpRequest(int sensorValue)
{
  client.stop();
  if(Server.connect())
  {
    server.println("Connecting......");
    server.println("GET /dweet/for/myarduino?light=" + String(sensorValue) + "HTTP/1.1");
    server.println("HOST:freeboard.io");
    server.println("User-Agent:ArduinoWiFi/1.1");
    server.println("Connection:close");
    server.println();

    lastConnectionTime= millis();
  }
  else
  {
    Serial.println("Connection Failed");
  }
}
