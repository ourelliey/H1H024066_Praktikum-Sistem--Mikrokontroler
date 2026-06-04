# Modul IV – Interrupt dan Timer pada Arduino

**Nama:** Aurellia Nabila Rahma Putri 
**NIM:** H1H024066
**Asisten:** Arga Aryanta Indrafata

## Deskripsi

Pada praktikum ini dilakukan pengujian penggunaan **interrupt eksternal** dan **timer berbasis fungsi millis()** pada Arduino Uno.

Praktikum terdiri dari dua percobaan utama:

* **Percobaan 1** – Pengendalian LED menggunakan interrupt eksternal melalui push button.
* **Percobaan 2** – Pengendalian LED menggunakan timer non-blocking dengan fungsi `millis()`.

---

## Alat dan Bahan

| Komponen               | Jumlah     |
| ---------------------- | ---------- |
| Arduino Uno            | 1          |
| LED Merah              | 1          |
| LED Kuning             | 1          |
| Push Button            | 1          |
| Resistor 220Ω          | 2          |
| Breadboard             | 1          |
| Kabel Jumper           | Secukupnya |
| Komputer + Arduino IDE | 1          |

---

# Percobaan 1 – Interrupt Eksternal

## Skema Rangkaian

* LED Merah → Pin D13 → Resistor 220Ω → GND
* LED Kuning → Pin D12 → Resistor 220Ω → GND
* Push Button → Pin D2 → GND
* Pin D2 menggunakan internal pull-up resistor Arduino

## Kode Program

```cpp
#include <Arduino.h>

volatile bool ledState = false;

void tombolInterrupt() {
  ledState = !ledState;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(2, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    FALLING
  );
}

void loop() {
  digitalWrite(13, ledState);
  digitalWrite(12, ledState);
}
```

## Penjelasan Tiap Baris Penting

| Fungsi / Perintah          | Penjelasan                                                               |
| -------------------------- | ------------------------------------------------------------------------ |
| `volatile bool ledState`   | Menyimpan status LED yang dapat diubah oleh interrupt.                   |
| `tombolInterrupt()`        | ISR (*Interrupt Service Routine*) yang dieksekusi ketika tombol ditekan. |
| `ledState = !ledState`     | Membalik kondisi LED dari ON ke OFF atau sebaliknya.                     |
| `pinMode(2, INPUT_PULLUP)` | Mengaktifkan resistor pull-up internal pada pin input.                   |
| `attachInterrupt()`        | Menghubungkan pin interrupt dengan ISR.                                  |
| `FALLING`                  | Interrupt aktif saat sinyal berubah dari HIGH menjadi LOW.               |
| `digitalWrite()`           | Mengatur kondisi LED sesuai nilai variabel `ledState`.                   |

## Cara Kerja

Ketika tombol ditekan, sinyal pada pin D2 berubah dari HIGH ke LOW sehingga interrupt dipicu. ISR kemudian dijalankan dan mengubah nilai `ledState`. Nilai tersebut digunakan untuk mengatur LED pada pin D12 dan D13 sehingga kedua LED akan berganti kondisi setiap kali tombol ditekan.

---

# Percobaan 2 – Timer Non-Blocking Menggunakan millis()

## Skema Rangkaian

* LED Merah → Pin D13 → Resistor 220Ω → GND
* LED Kuning → Pin D12 → Resistor 220Ω → GND

## Kode Program

```cpp
#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = false;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    ledState = !ledState;

    digitalWrite(13, ledState);
    digitalWrite(12, ledState);
  }
}
```

## Penjelasan Tiap Baris Penting

| Fungsi / Perintah                                | Penjelasan                                                               |
| ------------------------------------------------ | ------------------------------------------------------------------------ |
| `millis()`                                       | Mengembalikan waktu sejak Arduino mulai berjalan dalam satuan milidetik. |
| `previousMillis`                                 | Menyimpan waktu terakhir saat LED berubah kondisi.                       |
| `interval`                                       | Menentukan periode perubahan LED, yaitu 1000 ms.                         |
| `currentMillis`                                  | Menyimpan waktu saat ini dari fungsi `millis()`.                         |
| `if(currentMillis - previousMillis >= interval)` | Mengecek apakah interval yang ditentukan sudah terlampaui.               |
| `ledState = !ledState`                           | Mengubah status LED menjadi kebalikannya.                                |
| `digitalWrite()`                                 | Mengirim nilai HIGH atau LOW ke pin LED.                                 |

## Cara Kerja

Program memanfaatkan fungsi `millis()` untuk menghitung waktu tanpa menggunakan `delay()`. Setiap kali selisih waktu mencapai 1000 ms, status LED dibalik. Dengan metode ini mikrokontroler tetap dapat menjalankan proses lain karena tidak terblokir oleh fungsi delay.

---

# Modifikasi Program

Pada percobaan ini dilakukan modifikasi dengan menambahkan LED kedua pada pin D12. Kedua LED dikendalikan secara bersamaan sehingga ketika kondisi berubah menjadi HIGH, kedua LED akan menyala, dan ketika berubah menjadi LOW, kedua LED akan mati.

```cpp
digitalWrite(13, ledState);
digitalWrite(12, ledState);
```

Hasil modifikasi menunjukkan bahwa kedua LED berkedip secara sinkron mengikuti interval yang telah ditentukan.

---

# Hasil Percobaan

| Percobaan  | Parameter            | Hasil                                       |
| ---------- | -------------------- | ------------------------------------------- |
| 1          | Interrupt eksternal  | Berfungsi dengan baik saat tombol ditekan   |
| 1          | Perubahan status LED | LED berubah ON/OFF setiap interrupt terjadi |
| 2          | Timer millis()       | LED berkedip setiap 1000 ms                 |
| 2          | Non-blocking timer   | Program berjalan tanpa menggunakan delay()  |
| Modifikasi | Dua LED bersamaan    | Kedua LED menyala dan mati secara sinkron   |

## Kesimpulan

Berdasarkan hasil praktikum, interrupt eksternal memungkinkan Arduino merespons kejadian dari luar secara cepat tanpa perlu melakukan polling secara terus-menerus. Selain itu, fungsi `millis()` dapat digunakan sebagai timer non-blocking yang lebih efisien dibandingkan `delay()`, karena tidak menghentikan jalannya program selama proses penundaan berlangsung.
