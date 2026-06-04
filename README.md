# Percobaan 4A – Pengendalian Servo Menggunakan ADC

<img width="1200" height="1600" alt="Dokumentasi percobaan A" src="https://github.com/user-attachments/assets/0dcb89e8-28d1-40f1-bf41-7a05242e19c3" />

### 1. Apa kegunaan fungsi `analogRead()` pada percobaan ini?

Fungsi `analogRead()` dipakai untuk mengambil data tegangan analog dari potensiometer yang terhubung ke pin A0 Arduino. Nilai tegangan tersebut kemudian diubah oleh ADC menjadi data digital dengan rentang 0 sampai 1023 sehingga dapat diproses oleh program.

### 2. Mengapa menggunakan fungsi `map()`?

Nilai yang dihasilkan ADC dan sudut gerak servo memiliki rentang yang berbeda. ADC menghasilkan nilai 0–1023, sedangkan servo bekerja pada kisaran 0°–180°. Oleh karena itu, fungsi `map()` digunakan untuk mengonversi nilai ADC agar sesuai dengan rentang sudut servo.

Contoh kode:

```cpp
pos = map(val, 0, 1023, 0, 180);
```

### 3. Bagaimana cara membatasi pergerakan servo hanya antara 30° sampai 150°?

Batas gerakan servo dapat diatur dengan mengubah nilai keluaran pada fungsi `map()`. Dengan rentang keluaran 30 hingga 150, servo tidak akan bergerak di luar sudut tersebut.

Contoh:

```cpp
pos = map(val, 0, 1023, 30, 150);
```

---

# Percobaan 4B – Pengaturan Intensitas LED dengan PWM

<img width="1200" height="1600" alt="Dokumentasi Percobaan B" src="https://github.com/user-attachments/assets/9a5b4794-3893-476b-8df9-c6cc3ced737c" />

### 1. Mengapa kecerahan LED dapat diatur menggunakan `analogWrite()`?

Fungsi `analogWrite()` menghasilkan sinyal PWM (*Pulse Width Modulation*). Dengan mengubah duty cycle PWM, lama kondisi HIGH dan LOW pada LED dapat diatur sehingga tingkat kecerahan LED terlihat berbeda. Semakin besar nilai PWM, semakin terang cahaya LED yang dihasilkan.

Contoh:

```cpp
analogWrite(ledPin, pwmValue);
```

### 2. Apa keterkaitan antara ADC dan PWM?

Nilai ADC yang dibaca dari potensiometer berada pada rentang 0–1023, sedangkan PWM hanya menerima nilai 0–255. Karena itu diperlukan proses konversi menggunakan fungsi `map()` agar data ADC dapat digunakan sebagai nilai PWM.

Contoh:

```cpp
pwmValue = map(adcValue, 0, 1023, 0, 255);
```

### 3. Bagaimana agar LED hanya aktif pada nilai PWM 50–200?

Hal tersebut dapat dilakukan dengan menambahkan percabangan `if`. Jika nilai PWM berada dalam rentang 50–200, LED akan menyala sesuai nilai PWM. Jika tidak, LED akan dimatikan.

Contoh:

```cpp
if (pwmValue >= 50 && pwmValue <= 200) {
    analogWrite(ledPin, pwmValue);
} else {
    analogWrite(ledPin, 0);
}
```

Dengan cara ini, LED hanya akan menyala ketika nilai PWM berada pada kisaran 50 hingga 200.
