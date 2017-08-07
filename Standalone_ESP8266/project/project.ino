

int ledPin = 13;

int knockSensor = A0;               

byte val = 0;

int statePin = LOW;

int THRESHOLD = 100;



void setup() {

 pinMode(ledPin, OUTPUT); 

 Serial.begin(9600);

}



void loop() {

  val = analogRead(knockSensor);  
  Serial.println(val);  
  delay(500);  // we have to make a delay to avoid overloading the serial port

}

