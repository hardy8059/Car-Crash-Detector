#include<ESP8266WiFi.h>
//credentials
char ssid[]="Hotspot";
char pass[]="ranjanam";
int status = WL_IDLE_STATUS;
int vib=0;
char server[] = "www.dweet.io";
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10L * 1000L;
int sensorPin = A0;
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Attempting to connect to WPA SSID:");
  Serial.println(ssid);
  status=WiFi.begin(ssid,pass);
  
  while( WiFi.status() != WL_CONNECTED )
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("You Are connected to the network");
  printWifiStatus();
}

void loop() {
  // put your main code here, to run repeatedly:
   while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
 
 int sensorValue=analogRead(A0);
 Serial.println("Sensor Reading:");
 Serial.println(sensorValue);
 delay(1000);

if(millis()-lastConnectionTime>postingInterval)
{
  Serial.println("Uploading...");
  vib=analogRead(sensorPin);
  httpRequest(sensorValue);
}
}

void httpRequest(int sensorValue)
{
  client.stop();
  if(client.connect(server,80))
  {
    Serial.println("Connecting......");
    client.println("GET /dweet/for/myarduino?vib=" + String(290) + " HTTP/1.1");
    client.println("HOST:freeboard.io");
    client.println("User-Agent:ArduinoWiFi/1.1");
    client.println("Connection:close");
    client.println();
    
    lastConnectionTime= millis();
  }
  else
  {
    Serial.println("Connection Failed");
  }
}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

