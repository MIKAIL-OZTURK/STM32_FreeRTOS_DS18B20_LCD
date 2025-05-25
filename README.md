# 🌡️ Temperature Monitoring System using DS18B20 & I2C LCD with FreeRTOS Software Timers
Bu proje, **STM32** tabanlı bir sistem üzerinde **FreeRTOS Software Timer** kullanılarak sıcaklık ölçümü yapılmasını ve bu sıcaklık bilgisinin **I2C tabanlı bir LCD ekranda** görüntülenmesini sağlamaktadır. 
**DS18B20 sıcaklık sensörü**, periyodik olarak ölçüm yapmak için yazılım zamanlayıcı (Software Timer) ile entegre edilmiştir. Bu sayede sıcaklık verisi düşük kaynak tüketimi ile zamanlanmış şekilde ekrana 
yansıtılmaktadır.

## 📌 Özellikler
- ⏱️ **FreeRTOS Software Timer** kullanımı
- 🌡️ **DS18B20** ile sıcaklık ölçümü
- 📟 **I2C LCD (16x2)** ile sıcaklık gösterimi
- 🔁 10 saniyede bir sıcaklık güncellemesi
- 🧵 Görev ve zamanlayıcı ayrımı ile **modüler RTOS mimarisi**

## 🛠️ Kullanılan Teknolojiler

| Bileşen           | Açıklama                          |
|-------------------|-----------------------------------|
| MCU               | STM32F407VG                       |
| Sensör            | DS18B20                           |
| Ekran             | I2C tabanlı 16x2 LCD              |
| RTOS              | FreeRTOS                          |
| Geliştirme IDE    | STM32CubeIDE 1.16.                |
| Dil               | C (HAL kütüphaneleriyle)          |

## Uygulama Videosu 
https://github.com/user-attachments/assets/2d3de26c-6a10-42e0-81bb-fd6a1733a870

## Donanım Gereksinimleri
- STM32 kartı (örnek: STM32F407VG)
- DS18B20 sıcaklık sensörü
- 4.7kΩ pull-up direnci
- I2C destekli 16x2 LCD ekran
- Jumper kablolar, breadboard

## 🧠 Öğrenim Çıktıları
- FreeRTOS yazılım zamanlayıcısının pratik kullanımı
- Görev-zamanlayıcı senkronizasyonu (xTaskNotifyGive)
- Donanım soyutlama katmanları (HAL) ile sürücü geliştirme
- Gerçek zamanlı sıcaklık izleme uygulaması

## 📌 İyileştirme Fikirleri
- Sıcaklık değişimini grafiksel olarak göstermek
- LCD yerine OLED ekranla geliştirmek
- Ölçümleri UART üzerinden bir PC’ye aktarmak
- Kullanıcıya görsel uyarı verecek alarm sistemi (örn. LED)
