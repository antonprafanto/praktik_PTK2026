# PANDUAN PRAKTIKUM WOKWI
## Simulasi Monitor Suhu Kandang Sapi + Telegram Bot
### Mata Kuliah: Pengenalan IoT — Fakultas Peternakan UNMUL 2026

---

## 📋 Ada 2 Level Praktikum

| Level | Platform | Fitur | File yang Dipakai |
|-------|----------|-------|-----------------|
| 🟢 **Level Dasar** | Arduino Uno | Sensor + LCD + LED alarm | `sketch.ino` + `diagram.json` |
| 🔵 **Level Lanjutan** | ESP32 (punya WiFi) | Sensor + **OLED** + LED + **Notifikasi Telegram ke HP** | `sketch_telegram.ino` + `diagram_telegram.json` |

> 💡 **Mulai dari Level Dasar** terlebih dahulu. Setelah berhasil, lanjutkan ke Level Lanjutan!

---

## 🟢 LEVEL DASAR — Monitor Suhu Kandang (Arduino Uno)

### Apa yang Akan Kita Buat?

Simulasi **alat monitor kandang sapi virtual** yang menampilkan:
- 🌡️ Suhu kandang (dalam derajat Celsius)
- 💧 Kelembaban kandang (dalam persen)
- 🔴 Lampu alarm merah yang menyala otomatis jika kandang TERLALU PANAS (> 30°C)

### Langkah-Langkah Level Dasar

#### LANGKAH 1: Buka Wokwi
1. Buka browser (Chrome/Firefox/Edge)
2. Kunjungi: **https://wokwi.com**
3. Tidak perlu daftar/login untuk memulai!

#### LANGKAH 2: Buat Proyek Baru Arduino
1. Klik tombol **"New Project"** atau **"+ New"**
2. Pilih **"Arduino Uno"**
3. Akan muncul editor dengan dua tab: **sketch.ino** (kode) dan **diagram.json** (rangkaian)

#### LANGKAH 3: Masukkan Kode Program
1. Klik tab **sketch.ino**
2. Hapus semua kode yang ada (Ctrl+A → Delete)
3. Download **[⬇️ sketch.ino](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/sketch.ino)** → buka → salin semua (Ctrl+A → Ctrl+C)
4. Tempel (Ctrl+V) ke dalam editor Wokwi

#### LANGKAH 4: Pasang Rangkaian Virtual
1. Klik tab **diagram.json**
2. Hapus semua isi yang ada (Ctrl+A → Delete)
3. Download **[⬇️ diagram.json](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/diagram.json)** → buka → salin → tempel

#### LANGKAH 5: Jalankan Simulasi!
1. Klik tombol **▶ Play** (segitiga hijau) di pojok atas
2. Tunggu beberapa detik hingga kompilasi selesai
3. Lihat layar LCD menampilkan data suhu dan kelembaban!

#### LANGKAH 6: Ubah Suhu (Eksperimen)
1. Klik pada komponen **DHT22** (kotak kecil di kiri atas)
2. Di panel kanan, ubah nilai **temperature** menjadi **35**
3. Lihat apa yang terjadi pada LED merah! 🔴

---

## 🔵 LEVEL LANJUTAN — Monitor Kandang + Telegram Bot (ESP32)

### Apa Bedanya dengan Level Dasar?

Di level ini, kita pakai **ESP32** (chip yang lebih canggih dari Arduino Uno, punya WiFi bawaan). ESP32 dilengkapi layar **OLED SSD1306** (lebih modern dari LCD biasa!) dan bisa mengirim **notifikasi ke Telegram** saat kandang terlalu panas!

> 💡 **Kenapa OLED?** OLED hanya butuh **2 kabel data** (SDA + SCL via I2C), jauh lebih simpel dari LCD yang butuh 6 kabel data. Tampilan juga lebih keren!

### Langkah-Langkah Level Lanjutan

#### LANGKAH 1 & 2: Sama seperti Level Dasar
1. Buka **https://wokwi.com**
2. Klik **"New Project"** → pilih **"ESP32"** (bukan Arduino Uno!)

#### LANGKAH 3: Masukkan Kode ESP32 + Telegram
1. Klik tab **sketch.ino** di Wokwi
2. Hapus semua → Ctrl+A → Delete
3. Download **[⬇️ sketch_telegram.ino](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/sketch_telegram.ino)** → buka → salin semua → tempel ke Wokwi

#### LANGKAH 4: Pasang Rangkaian ESP32
1. Klik tab **diagram.json** di Wokwi
2. Hapus semua → download **[⬇️ diagram_telegram.json](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/diagram_telegram.json)** → buka → salin → tempel

#### LANGKAH 5: Jalankan & Amati Serial Monitor
1. Klik **▶ Play** untuk mulai simulasi
2. Lihat **Serial Monitor** (klik ikon terminal/kotak hitam di bawah)
3. Kamu akan melihat kotak notifikasi Telegram muncul seperti ini:

```
╔══════════════════════════════════════╗
║  📱  NOTIFIKASI TELEGRAM BOT         ║
╠══════════════════════════════════════╣
║  Dari : @KandangSapiUNMUL_Bot        ║
║  ⚠️ PERINGATAN SUHU PANAS             ║
║  Suhu kandang: 33.0°C                ║
╚══════════════════════════════════════╝
```

#### LANGKAH 6: Eksperimen Alert Telegram

| Ubah suhu DHT22 ke... | Notifikasi yang muncul |
|----------------------|------------------------|
| **33°C** | ⚠️ PERINGATAN — Suhu melewati 30°C |
| **37°C** | 🚨 BAHAYA KRITIS — Suhu melewati 35°C! |
| **26°C** | ✅ KANDANG NORMAL — Suhu kembali aman |

---

## 🔧 Penjelasan Komponen Virtual

| Komponen | Level Dasar | Level Lanjutan | Analogi Nyata |
|----------|:-----------:|:--------------:|---------------|
| **Arduino Uno** | ✅ | — | Seperti CPU di HP biasa |
| **ESP32** | — | ✅ | Seperti HP Android (ada WiFi!) |
| **DHT22** | ✅ | ✅ | Termometer digital kandang |
| **LCD 16x2** | ✅ | — | Layar display lama |
| **OLED SSD1306** | — | ✅ | Layar modern (2 kabel saja!) |
| **LED Merah** | ✅ | ✅ | Lampu darurat kandang |
| **Telegram Bot** | — | ✅ (simulasi) | Notifikasi WhatsApp/HP peternak |

---

## Pertanyaan Diskusi

1. **Apa yang terjadi** jika kamu mengubah `BATAS_SUHU_PANAS` dari `30.0` menjadi `25.0`?
2. **Bagaimana caranya** agar LED merah berkedip-kedip (bukan terus menyala) saat bahaya?
3. **Dalam peternakan nyata**, apa yang sebaiknya dilakukan secara otomatis jika suhu mencapai 35°C?
4. **Menurut kamu**, kenapa ESP32 lebih cocok untuk IoT kandang dibandingkan Arduino Uno biasa?
5. **Jika WiFi kandang mati**, bagaimana agar peternak tetap bisa memonitor suhu kandang?

---

## Tantangan Tambahan (Nilai Bonus)

**Level Dasar:**
- [ ] Tambahkan **LED Hijau** yang menyala saat suhu AMAN (< 30°C)
- [ ] Tambahkan teks **"AMAN!"** atau **"PANAS!"** di baris ke-2 LCD
- [ ] Ubah batas suhu aman menjadi **28°C** (batas lebih ketat untuk sapi perah)

**Level Lanjutan (Telegram):**
- [ ] Tambahkan pesan Telegram saat **kelembaban > 85%** (risiko jamur di kandang)
- [ ] Ubah `BATAS_PANAS` → apa yang berubah di notifikasi?
- [ ] Tambahkan **laporan harian** setiap jam 06:00 pagi (hint: gunakan millis())

---

## Link Berguna
- 🌐 Wokwi Simulator: https://wokwi.com
- 📱 Buat Bot Telegram: https://t.me/BotFather
- 🎥 Tutorial Wokwi Bahasa Indonesia: cari "Wokwi Arduino Tutorial Indonesia" di YouTube
- 📦 Library Telegram untuk ESP32: cari "UniversalTelegramBot" di Arduino Library Manager

---

## 🔧 Troubleshooting (Kalau Ada Masalah)

| Gejala | Penyebab | Solusi |
|--------|----------|--------|
| **OLED tidak muncul** | Library belum terdeteksi | Klik ▶ Play lagi — Wokwi auto-install `Adafruit SSD1306` |
| **Notifikasi Telegram tidak muncul** | Serial Monitor belum dibuka | Klik ikon **terminal hitam** di bawah area simulasi |
| **Error: "library not found"** | Library belum terdeteksi Wokwi | Klik tombol ▶ Play sekali lagi, Wokwi akan auto-install |
| **Suhu tidak berubah** | Belum klik sensor DHT22 | Klik komponen DHT22 → geser slider temperature di panel kanan |
| **OLED gelap total** | Tegangan salah | Pastikan VCC → 3V3 dan SDA/SCL sudah terhubung |

> ⚠️ **Penting untuk mahasiswa**: Jika LCD tetap blank setelah dicoba, cek kembali apakah **diagram_telegram.json** sudah di-paste dengan benar dan lengkap (dari baris `{` sampai `}` terakhir).

---

*Dokumen ini dibuat untuk keperluan pembelajaran — Fapet UNMUL 2026*
