

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
File myFile;
const int chipSelect = BUILTIN_SDCARD;
unsigned long time;
int led = 13;

unsigned long delayTime;

void setup() {
    unsigned status;
    status = bme.begin(); 
    delayTime = 1000;
    Serial.println();
}
  
  
  pinMode(led, OUTPUT);    
  Serial.begin(57600);
  // while (!Serial) {
  //}

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
    if (SD.begin(chipSelect)){
    Serial.println("SD Card Ready");
    myFile=SD.open("data.csv", FILE_WRITE);
    if(myFile){
    myFile.println("Pressure 1, Pressure 2, Pressure 3, Pressure 4"); 
    myFile.close();
    }
    return;
  }
}

void loop() { 
  digitalWrite(led, HIGH); 
  Serial.print("Time: ");
  time = millis();
  
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  temperature=bme.readTemperature();
 
  myFile=SD.open("data.csv", FILE_WRITE);
  if(myFile){
   myFile.print(time);
   myFile.print(",");
   myFile.println(temperature);
   myFile.close();
  }
  delay(1);        // delay in between reads for stability
}



