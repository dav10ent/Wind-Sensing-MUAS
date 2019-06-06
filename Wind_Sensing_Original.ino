// Code for multi-hole pressure probe wind measurement unit. Code reads from 3.3V analog pressure transducers to a Teensy 3.6.


#include <SD.h>
#include <SPI.h>

File myFile;
const int chipSelect = BUILTIN_SDCARD;

void setup() {
  Serial.begin(9600);
   while (!Serial) {
  }

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

\\ Make sure to change the analog ports to reflect which ports have been connected to the Teensy board. 

  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A4);
  int sensorValue4 = analogRead(A5);
  
  float sensor=sensorValue; 
  float sensor2=sensorValue2;
  float sensor3=sensorValue3;
  float sensor4=sensorValue4;
  
  float voltage=(sensorValue/1024.00)*3.3;
  float voltage2=(sensorValue2/1024.00)*3.3;
  float voltage3=(sensorValue3/1024.00)*3.3;
  float voltage4=(sensorValue4/1024.00)*3.3;
  float pressurediff=10.0;
  
  Serial.print(voltage);
  Serial.print(",");
  Serial.print(voltage2);
  Serial.print(",");
  Serial.print(voltage3);
  Serial.print(",");
  Serial.println(voltage4);  

 
  myFile=SD.open("data.csv", FILE_WRITE);
  if(myFile){
   myFile.print(sensorValue);
   myFile.print(",");
   myFile.print(sensorValue2);
   myFile.print(",");
   myFile.print(sensorValue3);  
   myFile.print(",");
   myFile.println(sensorValue4); 
   myFile.close();
  }
  delay(1);        // delay in between reads for stability
}



