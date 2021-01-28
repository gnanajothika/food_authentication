/////////////// Smart Embedded System for Food Authentication using NIR ///////////////
// Initialize NIR sensor
#include "AS726X.h" 
AS726X sensor; 
// Connect to Blynk cloud
#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
// Display result on OLED
#include <SPI.h>    
#include <Wire.h>   
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

char auth[] = "YOUR_BLYNK_AUTH_TOKEN";  // You should get Auth Token in the Blynk App Go to the Project Settings (nut icon).
char ssid[] = "YOUR_WIFI_NAME";    // Your WiFi credentials.
char pass[] = "YOUR_WIFI_PASSWORD";  // Set password to "" for open networks.
// Initialize NIR sensor
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  sensor.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
}

void loop() {
  sensor.takeMeasurements();
  if (sensor.getVersion() == SENSORTYPE_AS7263)
  {
    //Near IR readings
    Serial.print(" Reading: R[");
    Serial.print(sensor.getR());
    Serial.print("] S[");
    Serial.print(sensor.getS());
    Serial.print("] T[");
    Serial.print(sensor.getT());
    Serial.print("] U[");
    Serial.print(sensor.getU());
    Serial.print("] V[");
    Serial.print(sensor.getV());
    Serial.print("] W[");
    Serial.print(sensor.getW());
    // Display result on OLED
    if(sensor.getR()<5)    
    {
       display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
     display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.print("Authenticated");
      display.setCursor(0,0);
  display.display();
    }
    else
    {
       display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
     display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.print("Good Quality");
      display.setCursor(0,0);
  display.display();
    }
    Blynk.run();
    Blynk.virtualWrite(V0,sensor.getR());
     Blynk.virtualWrite(V1,sensor.getS());
     Blynk.virtualWrite(V2,sensor.getT());
      Blynk.virtualWrite(V3,sensor.getU());
       Blynk.virtualWrite(V4,sensor.getV());
        Blynk.virtualWrite(V5,sensor.getW());
         Blynk.virtualWrite(V6,sensor.getTemperatureF());
  }

  Serial.print("] tempF[");
  Serial.print(sensor.getTemperatureF(), 1);
  Serial.print("]");

  Serial.println();
}
