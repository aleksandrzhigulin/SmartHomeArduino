#include "DHT.h" // библиотека для dht11(DHT sensor library)
#include "MFRC522.h"
#include "SPI.h"

// #define DHTPIN 2 

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 10;

MFRC522 mfrc522(SS_PIN, RST_PIN);
//DHT dht(DHTPIN, DHT11);

bool systemIsActive = false;
String cardUUID = "19 61 77 C2";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  //dht.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
}
 
void loop() {
  /*delay(2000); // Пауза 2 секунды (2000 мс)
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // Heat Index по Цельсию
  float hic = dht.computeHeatIndex(temperature, humidity, false);
  if (isnan(temperature) || isnan(humidity) || isnan(hic)) {  // Check errors
    Serial.println("Ошибка считывания с датчика DHT11");
    return;
  }  */
 
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
 
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  if (content.substring(1) == cardUUID) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
 
  
  /*
  // Блок вывода данных в консоль
  Serial.print("Влажность: ");
  Serial.print(humidity);
  Serial.println("%\t");
  Serial.print("Температура: ");
  Serial.println(temperature);
  Serial.print("Тепловой индекс: ");
  Serial.println(hic);
  Serial.print("\n");
  Serial.print("\n");
  */
} 
