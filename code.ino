#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleSerialBLE.h>

SimpleTimer timer;
unsigned long prevMillis = 0;
#define BLYNK_USE_DIRECT_CONNECT

#define DHTPIN  7     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11

#define RED_LED 8 // red led pin
#define GREEN_LED 9 // green led pin
DHT dht(DHTPIN, DHTTYPE);

// we should get Auth Token in the Blynk App.
char auth[] = "mrFJYFzAgRzm1E4wEHObs_WUXOgREpvx";

void setup() {
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
  // set a timer to read data from sensor every 30 sec
  timer.setInterval(30000L, readSensor);
  Blynk.begin(Serial, auth);
}
void loop() {
  Blynk.run(); // update blynk
  timer.run(); // update timer
}

void readSensor() {
  float hum = dht.readHumidity();
  float tem = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(hum) || isnan(tem)) {
    return;
  }

  if(tem > 25) digitalWrite(RED_LED, HIGH);
  else digitalWrite(RED_LED, LOW);
  
  if(hum > 40)digitalWrite(GREEN_LED, HIGH);
  else  digitalWrite(GREEN_LED, LOW);

  Blynk.virtualWrite(V0, tem); // sending temperature to Blynk
  Blynk.virtualWrite(V1, hum); // sending humidity to Blynk
}
