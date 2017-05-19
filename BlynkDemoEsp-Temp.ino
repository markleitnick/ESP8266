// App reads temperature and humidity using DHT11 sensor.
// Results are sent to Blynk app every 5 seconds.
// An improvement would be to only update Blynk when one of the
//   two values changes from the previous reading.

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
#include <Automaton.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

float temperature;
float humidity;

// You should get Auth Token from the Blynk Mobile App
char auth[] = "your-blynk-auth-token";

DHT dht(13, DHT11);
Atm_timer timer1;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ssid";
char pass[] = "pass";

void setup()
{
  Serial.begin(115200);
 
  Blynk.begin(auth, ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay (500);
    Serial.print(".");
  }
  Blynk.syncAll();
  dht.begin();
  timer1.begin(5000)  // set timer to get temp every 5 seconds (5000 ms)
    .repeat(-1)       // timer never stops if = -1
    .onTimer(sendTemp)
    .start();
}

void loop() {
  automaton.run();
  Blynk.run();
}

void sendTemp(int idx, int v, int up) {
  temperature = dht.readTemperature(true);
  humidity = dht.readHumidity();
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
}

