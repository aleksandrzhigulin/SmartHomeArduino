#include "DHT.h" // библиотека для датчика влажности (DHT sensor library)

#define DHTPIN 999999 // номер пина для датчика влажности(DHT11)(Заглушка)

DHT dht(DHITPIN, DHT11);
bool systemIsActive = false;

void setup() {
  Serial.begin(9600);
  // Инициализация шины SPI
  // SPI.begin();
  dht.begin();
}

void loop() {
  delay(2000); // Пауза 2 секунды (2000 мс)
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // Heat Index по Цельсию
  float hic = dht.computeHeatIndex(temperature, humidity, false);
  if (isnan(temperature) || isnan(humidity) || isnan(hic)) {  // Проверка ошибок считывания
    Serial.println("Ошибка считывания с датчика DHT11");
    return;
  }  
  // Блок вывода данных в консоль
  Serial.print("Влажность: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Температура: ");
  Serial.print(temperature);
  Serial.print("%\t");
  Serial.print("Тепловой индекс: ");
  Serial.print(hic);
}
