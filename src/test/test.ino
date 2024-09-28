#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A6

DHT dht(DHTPIN, DHTTYPE);
float lembap, suhu;

void setup(){
    Serial.begin(9600);
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
    pinMode(S5, INPUT);
}

void loop(){
    lembap = dht.readHumidity();
    suhu = dht.readTemperature();

    Serial.print(analogRead(S1));
    Serial.print(",");
    Serial.print(analogRead(S2));
    Serial.print(",");
    Serial.print(analogRead(S3));
    Serial.print(",");
    Serial.print(analogRead(S4));
    Serial.print(",");
    Serial.print(analogRead(S5));
    Serial.print(",");
    Serial.print(suhu);
    Serial.print(",");
    Serial.println(lembap);
    delay(1000);
}