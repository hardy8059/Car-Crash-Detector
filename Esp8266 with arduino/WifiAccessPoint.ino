#include<SoftwareSerial.h>
SoftwareSerial esp(5,6);
#define LED 13

const int peizo = A0;
char ssid[] = "lenivo";
char pass[] = "123456789";
const char* eventname ="crash";
const char* host = "maker.ifttt.com";
const char* key = "mRQlS_Fx6TvxBNok7fLHJAH5XbXhUB_LP3f_HLtxN11";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  esp.begin(115200);
  Serial.println("Start Connecting");
  delay(3000);
  esp.println("AT\r\n");
  if(esp.find("OK"))
  {
    esp.println("AT+RST\r\n");
    delay(2000);
    Serial.println("ESP RESET SUCCESFULL");
    esp.println("AT+CWMODE=1\r\n");
    Serial.println("STATION MODE SELECTED");
    String command = "AT+CWJAP=";
    command+= "\"";
    command+= ssid;
    command+= "\"";
    command+= ",";
    command+= "\"";
    command+= pass;
    Serial.println("Connecting...");
    esp.println(command);
    
    delay(5000);
    if(esp.find("OK"))
    {
    String msg = "Connected"; 
    Serial.println(msg);
    digitalWrite(LED,HIGH);
    }
    }   
  else
  {
    Serial.println("AT MODE FAILED");
  }
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int readPiezo = analogRead(peizo);
  map(readPiezo,0,250,0,1023);
  Serial.println(readPiezo);
  if(readPiezo>700)
  {
    Serial.print("Connecting to:");
    Serial.println(host);
    String tcp = "AT+CIPSTART=\"TCP\",";
    tcp += "\"";
    tcp += String(host);
    tcp += "\"";
    tcp += ",80\r\n";
    Serial.println(tcp);
    esp.println(tcp);
    if(esp.find("CONNECT"))
    {
      String url = "/trigger/"+String(eventname)+"/with/key/"+String(key);
      Serial.println("Connection Established");
      String writeData = String("GET ")+url+" HTTP/1.1\r\n"+"HOST:"+host+"\r\n"+"Connection:close\r\n\r\n";
      esp.println("AT+CIPSEND="+String(writeData.length())+"\r\n");
      Serial.println(writeData.length());
      if(esp.find(">"))
      {
        esp.println(writeData);
        int timeout = millis() + 5000;
        if(timeout-millis() < 0)
        {
          Serial.println("Close Connection");
          esp.println("AT+CIPCLOSE");
        }
        else
        {
          delay(30000);
          esp.println("+++");
        }
      }
    }
    else
      {
        Serial.println("Connection Failed");
      }
  }
}
