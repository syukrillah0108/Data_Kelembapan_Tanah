#include <SD.h>

#define PIN_SPI_CS 4

#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A6

File myFile;

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

void setup() {
    Serial.begin(9600);
    setupSensor();
    if(setupFileSD()){
        Serial.println("file berhasil");
    }else{
        Serial.println("File Gagal");
        delay(500);
        setup();
    }
    delay(500);
}

void loop() {
    delay(500);
    if(writeFile("test252.csv", "hallo")){
        Serial.println("Menulis");
    }else{
        Serial.println("Gagal Menulis");
        setup();
    }
}