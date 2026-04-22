# README – Pertanyaan Praktikum (4.3)
## Identitas
- Nama: Aurellia Nabila Rahma Putri
- NIM: H1H024066

---

## 4.3 Pertanyaan Praktikum

### 1. Analisis Hasil Percobaan 2A dan 2B
Pada percobaan 2A, seven segment berhasil dioperasikan sebagai penampil counter heksadesimal secara otomatis, menampilkan karakter 0 hingga F secara sekuensial dengan memanfaatkan pola bit yang tersimpan dalam array dua dimensi.
Sementara itu, percobaan 2B membuktikan bahwa push button mampu berfungsi sebagai input digital yang stabil untuk mengatur nilai counter secara manual, didukung oleh penerapan mekanisme edge detection.

---

### 2. Prinsip Kerja Seven Segment
Seven segment beroperasi dengan cara mengaktifkan kombinasi segmen LED tertentu untuk membentuk suatu karakter yang dapat terbaca.
Setiap karakter memiliki pola aktivasi yang berbeda-beda, misalnya:
- Angka **0** → segmen a, b, c, d, e, f aktif (g tidak aktif)
- Huruf **A** → segmen a, b, c, e, f, g aktif (d tidak aktif)

Arduino mengendalikan status tiap segmen dengan mengirimkan sinyal **HIGH atau LOW** pada pin yang bersesuaian, sesuai pola yang telah didefinisikan dalam program.

---

### 3. Cara Kerja Sistem Counter
Sistem counter dijalankan menggunakan variabel `currentDigit` yang nilainya dapat berubah dengan dua cara:
- Bertambah secara otomatis sesuai alur program (percobaan 2A)
- Bertambah setiap kali tombol ditekan oleh pengguna (percobaan 2B)

Nilai variabel ini digunakan sebagai indeks untuk mengambil data pola dari array `digitPattern`, yang kemudian diteruskan ke seven segment melalui pemanggilan fungsi `displayDigit()`.
Ketika nilai counter melampaui angka 15, sistem secara otomatis mereset nilainya kembali ke 0.

---

## Kesimpulan Singkat
- Seven segment menampilkan karakter berdasarkan kombinasi pola bit yang telah ditentukan
- Nilai counter dikelola melalui variabel dan dapat dipengaruhi oleh input pengguna
- Push button memungkinkan pengendalian counter secara manual dan interaktif
- Sistem dapat berjalan baik secara otomatis maupun dalam mode interaktif

---