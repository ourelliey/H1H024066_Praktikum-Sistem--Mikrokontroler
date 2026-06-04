# Modul V – Penerapan Real-Time Operating System (RTOS)

**Nama:** Aurellia Nabila Rahma Putri
**NIM:** H1H024066
**Asisten:** Arga Aryanta Indrafata

## Pendahuluan

Pada praktikum ini dilakukan implementasi **FreeRTOS** pada papan mikrokontroler Arduino Uno. Tujuan utama praktikum adalah memahami konsep multitasking dan komunikasi antar-task dalam sistem operasi waktu nyata.

Praktikum dibagi menjadi dua bagian utama:

* **Percobaan 5A** – Implementasi beberapa task yang berjalan secara bersamaan menggunakan fungsi `xTaskCreate()` dan `vTaskDelay()`.
* **Percobaan 5B** – Pertukaran data antar-task dengan memanfaatkan mekanisme **message queue** melalui `xQueueCreate()`, `xQueueSend()`, dan `xQueueReceive()`.

---

## Peralatan dan Komponen

| Komponen                     | Jumlah     |
| ---------------------------- | ---------- |
| Arduino Uno                  | 1 buah     |
| LED Merah                    | 1 buah     |
| LED Kuning                   | 1 buah     |
| Resistor 220Ω                | 2 buah     |
| Breadboard                   | 1 buah     |
| Kabel Jumper                 | Secukupnya |
| Sensor DHT (untuk 5B)        | 1 buah     |
| PC/Laptop dengan Arduino IDE | 1 unit     |

Library yang digunakan dalam praktikum ini adalah **Arduino_FreeRTOS**.

---

# Percobaan 5A – Multitasking pada FreeRTOS

## Rangkaian

Konfigurasi rangkaian yang digunakan adalah sebagai berikut:

* LED Merah terhubung ke pin **D8** melalui resistor 220Ω menuju GND.
* LED Kuning terhubung ke pin **D10** melalui resistor 220Ω menuju GND.

## Program

```cpp
#include <Arduino_FreeRTOS.h>

// Deklarasi task
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void Taskprint(void *pvParameters);

void setup() {
  Serial.begin(9600);

  xTaskCreate(TaskBlink1, "Blink1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "Blink2", 128, NULL, 1, NULL);
  xTaskCreate(Taskprint, "Print", 128, NULL, 1, NULL);
}

void loop() {
}

void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);
  for (;;) {
    digitalWrite(8, HIGH);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    digitalWrite(8, LOW);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {
  pinMode(10, OUTPUT);
  for (;;) {
    digitalWrite(10, HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(10, LOW);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void Taskprint(void *pvParameters) {
  int counter = 0;
  for (;;) {
    Serial.print("Counter: ");
    Serial.println(counter++);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```

## Penjelasan Program

Pada percobaan ini dibuat tiga task yang dijalankan secara bersamaan oleh scheduler FreeRTOS.

| Fungsi/Perintah                 | Keterangan                                                                                             |
| ------------------------------- | ------------------------------------------------------------------------------------------------------ |
| `#include <Arduino_FreeRTOS.h>` | Mengaktifkan fitur FreeRTOS pada Arduino.                                                              |
| `xTaskCreate()`                 | Digunakan untuk membuat task baru yang akan dikelola scheduler.                                        |
| `vTaskDelay()`                  | Menunda eksekusi task selama waktu tertentu tanpa menghentikan task lain.                              |
| `for(;;)`                       | Loop tak terbatas yang digunakan dalam task FreeRTOS.                                                  |
| `loop()` kosong                 | Setelah scheduler berjalan, seluruh proses ditangani oleh task sehingga `loop()` tidak digunakan lagi. |

## Pengembangan Menggunakan Potensiometer

Sebagai modifikasi, ditambahkan task baru yang membaca nilai potensiometer pada pin `A0`. Data ADC kemudian dikonversi menjadi waktu delay sehingga kecepatan kedipan LED dapat diatur secara langsung.

```cpp
void TaskPot(void *pvParameters) {
  for (;;) {
    int adcVal = analogRead(A0);
    int delayMs = map(adcVal, 0, 1023, 50, 1000);

    digitalWrite(8, HIGH);
    vTaskDelay(delayMs / portTICK_PERIOD_MS);

    digitalWrite(8, LOW);
    vTaskDelay(delayMs / portTICK_PERIOD_MS);
  }
}
```

Semakin besar nilai ADC yang terbaca, maka interval kedipan LED menjadi semakin cepat. Sebaliknya, jika nilai ADC kecil maka LED akan berkedip lebih lambat.

---

# Percobaan 5B – Komunikasi Antar Task Menggunakan Queue

## Rangkaian

Percobaan ini hanya memanfaatkan Arduino Uno yang terhubung ke komputer melalui kabel USB untuk menampilkan data pada Serial Monitor.

## Program

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>

struct readings {
  int temp;
  int h;
};

QueueHandle_t dataQueue;

void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {
  Serial.begin(9600);

  dataQueue = xQueueCreate(1, sizeof(struct readings));

  xTaskCreate(read_data, "ReadData", 128, NULL, 1, NULL);
  xTaskCreate(display, "Display", 128, NULL, 1, NULL);
}

void loop() {
}

void read_data(void *pvParameters) {
  struct readings sensorData;

  for (;;) {
    sensorData.temp = 54;
    sensorData.h = 30;

    xQueueSend(dataQueue, &sensorData, portMAX_DELAY);

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void display(void *pvParameters) {
  struct readings received;

  for (;;) {
    if (xQueueReceive(dataQueue, &received, portMAX_DELAY) == pdPASS) {
      Serial.print("temp = ");
      Serial.println(received.temp);

      Serial.print("humidity = ");
      Serial.println(received.h);
    }
  }
}
```

## Penjelasan Program

Queue digunakan sebagai media pertukaran data antara task pengirim dan task penerima.

| Fungsi/Perintah   | Keterangan                                                       |
| ----------------- | ---------------------------------------------------------------- |
| `struct readings` | Menyimpan data suhu dan kelembapan dalam satu struktur data.     |
| `xQueueCreate()`  | Membentuk queue dengan kapasitas tertentu.                       |
| `xQueueSend()`    | Mengirim data ke dalam queue.                                    |
| `xQueueReceive()` | Mengambil data dari queue untuk diproses.                        |
| `portMAX_DELAY`   | Membuat task menunggu tanpa batas waktu sampai operasi berhasil. |
| `pdPASS`          | Menunjukkan bahwa operasi queue berhasil dilakukan.              |

## Modifikasi Menggunakan Sensor DHT11

Pada tahap pengembangan, data simulasi diganti dengan pembacaan langsung dari sensor DHT11 sehingga nilai suhu dan kelembapan yang diperoleh sesuai kondisi lingkungan sebenarnya.

```cpp
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void read_data(void *pvParameters) {
  struct readings sensorData;

  dht.begin();

  for (;;) {
    sensorData.temp = (int)dht.readTemperature();
    sensorData.h = (int)dht.readHumidity();

    xQueueSend(dataQueue, &sensorData, portMAX_DELAY);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
```

Dengan penggunaan sensor DHT11, data yang dikirim melalui queue menjadi dinamis dan mencerminkan kondisi lingkungan saat pengukuran berlangsung.

---

# Hasil dan Analisis

| Percobaan | Parameter Pengujian           | Hasil                                                                       |
| --------- | ----------------------------- | --------------------------------------------------------------------------- |
| 5A        | Eksekusi multitasking         | Seluruh task dapat berjalan bersamaan tanpa gangguan.                       |
| 5A        | Tampilan Serial Monitor       | Counter meningkat secara berkala setiap 500 ms.                             |
| 5A        | Kinerja Scheduler             | Scheduler mampu mengatur eksekusi task sesuai periode masing-masing.        |
| 5B        | Pengiriman data melalui queue | Data berhasil ditransmisikan dan diterima dengan baik.                      |
| 5B        | Tampilan data                 | Nilai temperatur dan kelembapan muncul secara berulang pada Serial Monitor. |

## Kesimpulan

Berdasarkan hasil praktikum, FreeRTOS mampu menjalankan beberapa task secara paralel pada Arduino Uno dengan pengelolaan waktu yang efisien. Selain itu, penggunaan queue mempermudah proses komunikasi antar-task sehingga data dapat ditransmisikan secara aman dan terstruktur. Implementasi ini menunjukkan bahwa FreeRTOS sangat bermanfaat dalam pengembangan sistem embedded yang membutuhkan multitasking dan sinkronisasi data.
