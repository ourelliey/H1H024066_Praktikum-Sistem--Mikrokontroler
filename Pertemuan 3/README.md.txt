# README - Praktikum Modul 3: Protokol Komunikasi

**Nama:** Aurellia Nabila Rahma Putri
**NIM:** H1H024066

---

## 🔹 Deskripsi Praktikum

Praktikum ini bertujuan untuk mempelajari cara kerja protokol komunikasi serial pada Arduino, yaitu **UART** dan **I2C**.

* **UART** digunakan untuk komunikasi antara Arduino dan komputer
* **I2C** digunakan untuk komunikasi antara Arduino dan perangkat eksternal seperti LCD

Dengan praktikum ini, diharapkan mahasiswa memahami cara pengiriman dan penerimaan data antar perangkat.

---

# 🔹 Percobaan 3A - UART

## Dokumentasi Rangkaian

![alt text](<Percobaan 3A input 1.jpeg>)

---

## Serial Monitor

![alt text](<Percobaan 3A input 0.jpeg>)

---

## Jawaban Pertanyaan

### 1. Alur dari Input Keyboard hingga LED Menyala/Mati

Proses dimulai saat pengguna mengetik karakter pada Serial Monitor di Arduino IDE. Data tersebut dikirim ke Arduino melalui komunikasi serial (UART) dalam bentuk byte.

Arduino kemudian memeriksa apakah ada data masuk menggunakan fungsi `Serial.available()`. Jika ada, data akan dibaca dengan `Serial.read()`.

Selanjutnya dilakukan pengecekan:

* Jika menerima `'1'`, Arduino memberi sinyal HIGH ke LED sehingga menyala
* Jika menerima `'0'`, Arduino memberi sinyal LOW sehingga LED mati

Proses ini memungkinkan kontrol LED secara langsung dari komputer.

---

### 2. Fungsi Serial.available()

Fungsi `Serial.available()` digunakan untuk memastikan apakah terdapat data di buffer serial.

Jika tidak digunakan:

* Arduino bisa membaca data sebelum tersedia
* Data yang terbaca bisa tidak valid
* Program berpotensi menghasilkan error atau output yang salah

Karena itu, fungsi ini penting untuk menjaga keakuratan pembacaan data.

---

### 3. Modifikasi LED Berkedip saat Input '2'

Untuk menambahkan fitur LED berkedip saat menerima input `'2'`, perlu dibuat kondisi tambahan dalam program.

Saat `'2'` diterima:

* Arduino masuk ke mode blinking
* LED akan menyala dan mati secara berulang
* Kondisi ini berlangsung hingga ada input baru

Metode yang bisa digunakan:

* `delay()` → mudah namun menghentikan proses lain
* `millis()` → lebih efisien karena tidak blocking

---

### 4. Perbandingan delay() dan millis()

| Aspek          | delay()                        | millis()                |
| -------------- | ------------------------------ | ----------------------- |
| Cara kerja     | Menghentikan program sementara | Berjalan tanpa berhenti |
| Respons sistem | Kurang responsif               | Lebih cepat/responsif   |
| Multi-tasking  | Tidak mendukung                | Mendukung               |
| Kelebihan      | Sederhana                      | Lebih fleksibel         |

**Kesimpulan:**
Penggunaan `millis()` lebih disarankan karena program tetap bisa berjalan tanpa hambatan.

---

# 🔹 Percobaan 3B - I2C

## Dokumentasi Rangkaian

<img width="720" height="1280" alt="Percobaan 3B" src="https://github.com/ourelliey/H1H024066_Praktikum-Sistem--Mikrokontroler/blob/main/Pertemuan%203/Percobaan%203B.jpeg" />

---

## Jawaban Pertanyaan

### 1. Mekanisme Komunikasi I2C pada Arduino dan LCD

Dalam komunikasi I2C:

* Arduino bertindak sebagai **master**
* LCD sebagai **slave**

Komunikasi berlangsung melalui dua jalur:

* **SDA (Serial Data)** untuk pengiriman data
* **SCL (Serial Clock)** untuk sinkronisasi

Setiap perangkat memiliki alamat unik (misalnya 0x27). Arduino mengirim data ke alamat tersebut, lalu LCD menampilkannya.

Keunggulan utama I2C adalah efisiensi kabel karena hanya membutuhkan dua jalur komunikasi.

---

### 2. Susunan Pin Potensiometer

Susunan pin potensiometer harus sebagai berikut:

* Kiri → GND
* Tengah → A0
* Kanan → 5V

Jika posisi kiri dan kanan tertukar:

* Nilai tegangan tetap berubah
* Namun arah perubahan menjadi terbalik

Hal ini tidak merusak rangkaian, tetapi dapat membingungkan saat pembacaan data.

---

### 3. Integrasi UART dan I2C dalam Satu Sistem

Dalam sistem ini:

* UART berfungsi sebagai input (dari Serial Monitor)
* I2C digunakan sebagai output (ke LCD)

Alur kerja sistem:

1. Data dikirim dari komputer ke Arduino melalui UART
2. Arduino memproses data tersebut
3. Hasilnya ditampilkan pada LCD melalui I2C

Kedua protokol dapat berjalan bersamaan karena diproses secara berulang dalam fungsi `loop()`.

---

### 4. Tabel Hasil Pengamatan

| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 5%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |

---

# 🔹 Pertanyaan Analisis

### 1. Kelebihan dan Kekurangan UART dan I2C

**UART**

* ✔️ Mudah digunakan
* ✔️ Tidak membutuhkan sinyal clock
* ❌ Hanya untuk komunikasi dua perangkat
* ❌ Kecepatan terbatas

**I2C**

* ✔️ Hemat pin (hanya 2 kabel)
* ✔️ Bisa menghubungkan banyak perangkat
* ❌ Lebih lambat dibanding SPI
* ❌ Membutuhkan pengaturan alamat

---

### 2. Fungsi Alamat pada I2C

Alamat pada I2C digunakan sebagai identitas perangkat dalam satu jalur komunikasi.

Contoh:

* LCD dapat memiliki alamat seperti **0x27 atau 0x20**

Tanpa alamat ini, Arduino tidak dapat menentukan tujuan pengiriman data.

---

### 3. Alur Sistem UART dan I2C

Urutan kerja dalam sistem:

1. Data masuk melalui UART
2. Arduino memproses data
3. Data dikirim ke LCD melalui I2C

Arduino menjalankan proses ini secara bergantian sehingga tidak terjadi konflik antar komunikasi.

---

# Kesimpulan

UART dan I2C merupakan dua protokol komunikasi penting dalam sistem embedded. UART cocok digunakan untuk komunikasi sederhana dengan komputer, sedangkan I2C lebih efisien untuk komunikasi antar perangkat karena penggunaan kabel yang minimal.

Keduanya dapat digabungkan dalam satu sistem untuk menciptakan interaksi yang lebih dinamis dan efisien.

---