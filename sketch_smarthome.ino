#include "DHT.h" // библиотека для датчика влажности (DHT sensor library)

#define DHTPIN 999999 // номер пина для датчика влажности(DHT11)(Заглушка)


DHT dht(DHITPIN, DHT11);


void setup() {
  Serial.begin(9600);
  // Run dht
  dht.begin();

}

void loop() {
  delay(2000); // Пауза 2 секунды (2000 мс)
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(temperature) || isnan(humidity)) {  // Если не удается считать показания, выводится "Ошибка считывания" и программа завершает работу
    Serial.println("Ошибка считывания с датчика DHT11");
    return;
  }

  // TODO: HEAT INDEX
  
  // Блок вывода данных в консоль
  Serial.print("Влажность: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(temperature);
}
