# STM32F407VG + FreeRTOS + DS18B20 + I2C LCD

Bu proje, FreeRTOS kullanarak DS18B20 sıcaklık sensöründen sıcaklık verisini okuyup I2C üzerinden bağlı 16x2 LCD ekrana yazdırır.

## Donanım

- STM32F407VG Discovery
- DS18B20 Sıcaklık Sensörü
- I2C 16x2 LCD ekran (PCF8574 tabanlı)

## Özellikler

- FreeRTOS ile görev ayrımı
- Software Timer ile 10 saniyede bir ölçüm
- I2C haberleşme ile LCD kontrolü

## Görevler

- **DisplayTask**: Sıcaklık verisini LCD'ye yazdırır.
- **TemperatureTimerCallback**: 10 saniyede bir sıcaklık ölçer.

## Geliştirme Ortamı

- STM32CubeIDE 1.16.1
- HAL Driver
- FreeRTOS Classic API
