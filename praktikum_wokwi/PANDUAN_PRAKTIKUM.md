# PANDUAN PRAKTIKUM WOKWI
## Simulasi Monitor Suhu Kandang Sapi
### Mata Kuliah: Pengenalan IoT — Fakultas Peternakan UNMUL 2026

---

## Apa yang Akan Kita Buat?

Kita akan membuat simulasi **alat monitor kandang sapi virtual** yang menampilkan:
- 🌡️ Suhu kandang (dalam derajat Celsius)
- 💧 Kelembaban kandang (dalam persen)
- 🔴 Lampu alarm merah yang menyala otomatis jika kandang TERLALU PANAS (> 30°C)

---

## Langkah-Langkah Praktikum

### LANGKAH 1: Buka Wokwi
1. Buka browser (Chrome/Firefox/Edge)
2. Kunjungi: **https://wokwi.com**
3. Tidak perlu daftar/login untuk memulai!

### LANGKAH 2: Buat Proyek Baru Arduino
1. Klik tombol **"New Project"** atau **"+ New"**
2. Pilih **"Arduino Uno"**
3. Akan muncul editor dengan dua tab: **sketch.ino** (kode) dan **diagram.json** (rangkaian)

### LANGKAH 3: Masukkan Kode Program
1. Klik tab **sketch.ino**
2. Hapus semua kode yang ada (Ctrl+A → Delete)
3. Salin seluruh isi file `sketch.ino` yang diberikan dosen
4. Tempel (Ctrl+V) ke dalam editor Wokwi

### LANGKAH 4: Pasang Rangkaian Virtual
1. Klik tab **diagram.json**
2. Hapus semua isi yang ada (Ctrl+A → Delete)
3. Salin seluruh isi file `diagram.json` yang diberikan dosen
4. Tempel (Ctrl+V) ke dalam editor Wokwi

### LANGKAH 5: Jalankan Simulasi!
1. Klik tombol **▶ Play** (segitiga hijau) di pojok atas
2. Tunggu beberapa detik hingga kompilasi selesai
3. Lihat layar LCD menampilkan data suhu dan kelembaban!

### LANGKAH 6: Ubah Suhu (Eksperimen)
1. Klik pada komponen **DHT22** (kotak kecil di kiri atas)
2. Di panel kanan, ubah nilai **temperature** menjadi **35**
3. Lihat apa yang terjadi pada LED merah! 🔴

---

## Penjelasan Komponen Virtual

| Komponen | Fungsi | Analogi Nyata |
|----------|--------|---------------|
| Arduino Uno | Otak/pengontrol | Seperti CPU di HP kamu |
| DHT22 | Sensor suhu & kelembaban | Termometer digital kandang |
| LCD 16x2 | Layar penampil data | Layar display kandang |
| LED Merah | Indikator alarm | Lampu darurat kandang |
| Resistor | Pengaman LED | Sekering listrik mini |

---

## Pertanyaan Diskusi

1. **Apa yang terjadi** jika kamu mengubah `BATAS_SUHU_PANAS` dari `30.0` menjadi `25.0`?
2. **Bagaimana caranya** agar LED merah berkedip-kedip (bukan terus menyala) saat bahaya?
3. **Dalam peternakan nyata**, apa yang sebaiknya dilakukan secara otomatis jika suhu mencapai 35°C?

---

## Tantangan Tambahan (Nilai Bonus)

- [ ] Tambahkan **LED Hijau** yang menyala saat suhu AMAN (< 30°C)
- [ ] Tambahkan teks **"AMAN!"** atau **"PANAS!"** di baris ke-2 LCD
- [ ] Ubah batas suhu aman menjadi **28°C** (batas lebih ketat untuk sapi perah)
- [ ] Coba tambahkan **Buzzer** sebagai alarm bunyi saat kandang terlalu panas

---

## Link Berguna
- 🌐 Wokwi Simulator: https://wokwi.com
- 📚 Dokumentasi DHT22: https://wokwi.com/projects/322410931467034210
- 🎥 Tutorial Wokwi Bahasa Indonesia: cari "Wokwi Arduino Tutorial Indonesia" di YouTube

---

*Dokumen ini dibuat untuk keperluan pembelajaran — Fapet UNMUL 2026*
