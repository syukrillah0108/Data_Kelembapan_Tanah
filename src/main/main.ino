#include <SD.h>
#include <Wire.h>
#include <DS3231.h>
#include "DHT.h"
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2);

#define DHTPIN 2
#define DHTTYPE DHT11

#define PIN_SPI_CS 4

#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A6

RTClib myRTC;
File myFile;
bool CondSD;
DateTime now;

DHT dht(DHTPIN, DHTTYPE);
float lembap, suhu;

int freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void setupSensor(){
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
    pinMode(S5, INPUT);
}

bool setupFileSD(){
    if (!SD.begin(PIN_SPI_CS)) {
        return 0;
    }else{
        return 1;
    }
}

bool writeFile(String file_name, String txt){
    myFile = SD.open(file_name, FILE_WRITE);
    if(myFile){
        myFile.println(txt);
        myFile.close();
        return 1;
    }else{
        return 0;
    }    
}

String getDate(){
    now = myRTC.now();

    return (
        String(now.year(), DEC) + "/" +
        String(now.month(), DEC) + "/" +
        String(now.day(), DEC)
    );
}

String getTime(){
    now = myRTC.now();

    return (
        String(now.hour(), DEC) + ":" +
        String(now.minute(), DEC) + ":" +
        String(now.second(), DEC)
    );
}

void getDHT(){
    lembap = dht.readHumidity();
    suhu = dht.readTemperature();
}

void printLCD(){
    lcd.clear();
    // SD
    lcd.setCursor(0, 0);
    lcd.print("SD");
    lcd.setCursor(0, 1);
    if(CondSD){
        lcd.print("OK");
    }else{
        lcd.print("ER");
    }

    // RAM
    lcd.setCursor(3, 0);
    lcd.print("RAM");
    lcd.setCursor(3, 1);
    lcd.print(freeRam());

    // WAKTU
    lcd.setCursor(7, 0);
    lcd.print("WAKTU");
    lcd.setCursor(7, 1);
    lcd.print(getTime());
}

void setup() {
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
    
    Wire.begin();
    setupSensor();
    
    dht.begin();
    
    if(setupFileSD()){
        Serial.println("file berhasil");
        CondSD = true;
    }else{
        Serial.println("File Gagal");
        CondSD = false;
        delay(500);
        setup();
    }
    delay(500);
}

void loop() {
    printLCD();
    delay(500);
    delay(1000);
    getDHT();
    Serial.println(freeRam());
    Serial.println(getTime());
    if(writeFile("test252.csv", "hallo")){
        Serial.println("Menulis");
        CondSD = true;
    }else{
        Serial.println("Gagal Menulis");
        CondSD = false;
        setup();
    }
}