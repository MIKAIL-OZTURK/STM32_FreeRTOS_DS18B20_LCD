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

## Kod Açıklaması
Bu proje, DS18B20 sıcaklık sensörü ile sıcaklığı ölçüp, I2C üzerinden bağlı bir LCD ekranda bu değeri her 10 saniyede bir göstermeyi amaçlıyor. FreeRTOS kullanılarak görev (task) ve zamanlayıcı (timer) 
yapılandırmaları yapıldı. 

### DisplayTask – Ekrana Yazı Gösteren Görev
- LCD başlatılır ve ilk satıra “Temp System” yazısı gönderilir.
- Görev sürekli çalışmaz, sadece bildirim (notify) geldiğinde çalışır.
- Bildirim geldiğinde sıcaklık bilgisi LCD'nin 2. satırına yazdırılır.

```c
static void DisplayTask(void *pvParameters)
{
    lcd_init(&hi2c1);
    lcd_set_cursor(0, 0);
    lcd_send_string("  Temp System");

    for (;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        lcd_set_cursor(1, 0);
        lcd_send_string("                "); // Clear line
        lcd_set_cursor(1, 0);
        lcd_send_string(temperatureStr);
    }
}
```
### TemperatureTimerCallback – 10 Saniyede Bir Çalışan Fonksiyon
```c
#define TEMP_MEASUREMENT_PERIOD_MS     10000        // 10.000 ms -> 10 sn 
static TimerHandle_t temperatureTimerHandle;

/* Create a Software Timer */
  temperatureTimerHandle = xTimerCreate(
      "TemperatureTimer",                          // Zamanlayıcı Adı 
      pdMS_TO_TICKS(TEMP_MEASUREMENT_PERIOD_MS),   // Zamanlayıcı Süresi= 10 sn.  pdMS_TO_TICKS(...) makrosu, bu değeri FreeRTOS tick süresine çeviriyor
      pdTRUE,                                      // pdTRUE olduğu için zamanlayıcı periyodik(Auto-Reload) çalışır, eğer pdFALSE olsaydı zamanlayıcı tek seferlik(one-shot) çalışacaktı.    
      NULL,                                        // Kullanıcı verisi yok
      TemperatureTimerCallback                     // 10 sn sonra çağırılacak Callback fonksiyonu
  );
```


- Callback fonksiyonu her çalıştığında DS18B20_GetTemp() fonksiyonu ile sıcaklık okunur.
- Okunan sıcaklık bir char[] dizisine yazılır (snprintf ile).
- DisplayTask'e bilgi verilir (notify).

```c
/* Timer Callback Function */ 
static void TemperatureTimerCallback(TimerHandle_t xTimer)
{
    currentTemperature = DS18B20_GetTemp();
    snprintf(temperatureStr, sizeof(temperatureStr), "Temp: %.2f C", currentTemperature);

    xTaskNotifyGive(displayTaskHandle);
}
```

### Kullanılan FreeRTOS Yapıları

| Yapı                 | Açıklama                                          |
| -------------------- | ------------------------------------------------- |
| `Task`               | LCD ekranı kontrol eden arka plan görevi          |
| `Timer`              | Her 10 saniyede bir çalışan yazılım zamanlayıcısı |
| `xTaskNotifyGive()`  | Göreve “şimdi çalış” sinyali verir                |
| `ulTaskNotifyTake()` | Görev sinyal gelene kadar bekler                  |


### Sonuç – Sistem Nasıl Çalışır?
1. Sistem açılır, sıcaklık sensörü ve LCD başlatılır.
2. DisplayTask bekleme moduna geçer.
3. Her 10 saniyede bir:
   - Sensörden sıcaklık alınır.
   - Ekranda gösterilecek metin hazırlanır.
   - DisplayTask tetiklenir.

4. DisplayTask, LCD'de sıcaklık bilgisini günceller.


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
