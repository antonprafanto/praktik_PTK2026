# 🌐 Praktikum IoT untuk Peternakan
### Fakultas Peternakan — Universitas Mulawarman, Samarinda 2026

<div align="center">

![Badge](https://img.shields.io/badge/Mata%20Kuliah-Pengenalan%20IoT-2E8B57?style=for-the-badge)
![Badge](https://img.shields.io/badge/Universitas-Mulawarman-F5A623?style=for-the-badge)
![Badge](https://img.shields.io/badge/Tahun-2026-1B562E?style=for-the-badge)

**Tidak diperlukan latar belakang IT, elektronika, atau pemrograman!**

</div>

---

## 📥 Download Materi Kuliah

| File | Keterangan | Download Langsung |
|------|-----------|:-----------------:|
| 📊 **Slide Presentasi PPT** | Materi lengkap **22 slide**, termasuk Telegram & Wokwi | [⬇️ **Download PPT**](https://github.com/antonprafanto/praktik_PTK2026/raw/main/IoT_untuk_Peternakan_UNMUL.pptx) |
| 🧪 **Kode Wokwi — Arduino Uno** | Simulasi suhu kandang (tanpa Telegram) | [⬇️ Download sketch.ino](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/sketch.ino) |
| 🔌 **Diagram Wokwi — Arduino Uno** | Rangkaian virtual: DHT22 + LCD + LED | [⬇️ Download diagram.json](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/diagram.json) |
| 📱 **Kode Wokwi — ESP32 + Telegram** | Simulasi notifikasi Telegram di Serial Monitor | [⬇️ Download sketch_telegram.ino](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/sketch_telegram.ino) |
| 🔌 **Diagram Wokwi — ESP32 + Telegram** | Rangkaian ESP32 dengan WiFi virtual | [⬇️ Download diagram_telegram.json](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/diagram_telegram.json) |
| 📖 **Panduan Praktikum** | Langkah-langkah Wokwi + soal diskusi + tantangan | [⬇️ Download Panduan](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/PANDUAN_PRAKTIKUM.md) |

---

## 📚 Isi Materi (22 Slide)

| # | Topik | Deskripsi |
|---|-------|-----------|
| 01 | 🛡️ Mitos vs Fakta | Kamu tidak harus bisa coding untuk pakai IoT! |
| 02 | 🤔 Apa itu IoT? | Penjelasan paling sederhana dengan analogi kandang |
| 03 | 🔗 Cara Kerja IoT | Sensor → Koneksi → Cloud → HP kamu |
| 04 | 🌟 IoT Sehari-hari | Contoh yang sudah kamu pakai tanpa sadar |
| 05 | ⚖️ Tradisional vs Smart Farm | Perbandingan efisiensi kandang |
| 06 | 🐄 6 Aplikasi di Kandang | Suhu, pakan, GPS ternak, produksi susu, dll |
| 07 | 🗺️ Studi Kasus Kaltim | Sapi Bali + GPS di kebun sawit (SISKA) |
| 08 | 📊 Data & Statistik | Efisiensi 40% lebih baik dengan IoT |
| 09 | ⚠️ Tantangan & Solusi | Koneksi internet, biaya, dan cara mengatasinya |
| 10 | 📖 Glosarium | Kamus 10 istilah IoT paling penting |
| 11 | 🎯 Kuis Interaktif | Tebak mana yang pakai IoT dan mana yang tidak |
| 12 | 🚀 Peluang Karir | Profesi baru untuk lulusan Fapet di era digital |
| 13 | **📱 Monitoring via Telegram Bot** | **HP kamu = dashboard kandang 24 jam!** |
| 14 | **🔧 Setup Telegram Bot** | **4 langkah mudah buat bot sendiri** |
| 15 | **🧪 Praktikum Wokwi** | **Simulasi IoT langsung di browser (GRATIS!)** |
| 16 | **🐄 Proyek Monitor Kandang** | **Rangkaian virtual + kode + penjelasan** |
| 17 | **📋 Panduan Wokwi** | **6 langkah step-by-step menggunakan simulator** |
| 18 | 💡 Kesimpulan | Rangkuman poin kunci materi |

---

## 🧪 Praktikum Simulasi IoT — Wokwi

> **Wokwi** adalah simulator Arduino/IoT yang **gratis dan berbasis browser**. Kamu bisa mencoba IoT **tanpa membeli hardware apapun!**

### Ada 2 Level Praktikum:

| Level | Platform | Fitur | File |
|-------|----------|-------|------|
| 🟢 **Level Dasar** | Arduino Uno | Sensor + LCD + LED alarm | `sketch.ino` + `diagram.json` |
| 🔵 **Level Lanjutan** | ESP32 (punya WiFi) | Sensor + LCD + LED + **Notifikasi Telegram ke HP** | `sketch_telegram.ino` + `diagram_telegram.json` |

---

## 📱 Fitur Baru: Monitoring via Telegram Bot

> **ESP32** (versi lebih canggih dari Arduino, punya WiFi bawaan) bisa mengirim notifikasi langsung ke HP lewat **Telegram** saat kandang terlalu panas!

### Alur Kerja Sistem:

```
🌡️ Sensor DHT22                    📺 LCD           📱 Telegram di HP
(Baca Suhu & Lembab)  →  ESP32  →  (Tampilkan)  +  (Kirim Notifikasi)
                           ↕
                         💡 LED
                      (Nyala jika panas)
```

### Contoh Notifikasi yang Akan Muncul di HP Kamu:

| Kondisi Suhu | Notifikasi Telegram |
|-------------|---------------------|
| Suhu > 35°C | 🚨 **BAHAYA KRITIS!** — Suhu 37.2°C, sapi butuh pendinginan SEGERA! |
| Suhu > 30°C | ⚠️ **PERINGATAN** — Suhu 31.5°C, melewati batas aman, nyalakan kipas! |
| Suhu Normal | ✅ **KANDANG NORMAL** — Suhu 26.8°C, kondisi aman |
| Setiap 10 menit | 📊 **Laporan Berkala** — Suhu, kelembaban, dan status kandang |

> **Di Simulator Wokwi:** notifikasi Telegram ditampilkan di **Serial Monitor** (kotak hitam di bawah simulasi)
> **Di Hardware Nyata:** notifikasi langsung terkirim ke HP kamu via aplikasi Telegram

### Setup Bot Telegram (Untuk Hardware Nyata — 4 Langkah):

**Langkah 1** — Buka Telegram → cari **@BotFather** → kirim `/newbot` → simpan TOKEN yang diberikan

**Langkah 2** — Cari **@userinfobot** → kirim `/start` → catat CHAT ID angka kamu

**Langkah 3** — Buka `sketch_telegram.ino` → isi bagian ini:
```cpp
const char* WIFI_SSID  = "NamaWiFiKandang";     // ← WiFi kamu
const char* WIFI_PASS  = "PasswordWiFi";         // ← Password WiFi
const String BOT_TOKEN = "123456:ABCDEF_TOKEN";  // ← Dari BotFather
const String CHAT_ID   = "987654321";            // ← ID kamu
```

**Langkah 4** — Upload ke ESP32 → kirim `/start` ke bot kamu → selesai! 🎉

---

### 🚀 Cara Mulai Praktikum (6 Langkah)

#### Langkah 1 — Buka Wokwi

Buka browser (Chrome/Firefox) dan kunjungi:

```
https://wokwi.com
```

> ✅ Gratis, tidak perlu daftar akun!

---

#### Langkah 2 — Buat Proyek Baru

- Untuk **Level Dasar**: Klik **`+ New Project`** → pilih **`Arduino Uno`**
- Untuk **Level Lanjutan** (Telegram): Klik **`+ New Project`** → pilih **`ESP32`**

---

#### Langkah 3 — Tempel Kode Program

1. Klik tab **`sketch.ino`** di editor Wokwi
2. Pilih semua teks → **`Ctrl + A`** → hapus → **`Delete`**
3. Download file kode: **[⬇️ sketch.ino](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/sketch.ino)**
4. Buka file yang terdownload → salin semua (**`Ctrl + A`** → **`Ctrl + C`**)
5. Tempel ke Wokwi (**`Ctrl + V`**)

---

#### Langkah 4 — Tempel Rangkaian Virtual

1. Klik tab **`diagram.json`** di Wokwi
2. Pilih semua → hapus → download **[⬇️ diagram.json](https://github.com/antonprafanto/praktik_PTK2026/raw/main/praktikum_wokwi/diagram.json)** → buka → salin → tempel

---

#### Langkah 5 — Jalankan Simulasi!

Klik tombol **`▶ Play`** (segitiga hijau di atas)

Kamu akan melihat:
- 📺 **Layar LCD** menampilkan → `Suhu: 33.0°C | Lembab: 75.0%`
- 🔴 **LED merah menyala** karena suhu 33°C sudah melebihi batas 30°C!

---

#### Langkah 6 — Eksperimen!

Klik komponen **DHT22** di simulator → ubah nilai **`temperature`** → lihat perubahan!

| Coba ubah suhu ke... | Yang terjadi |
|---------------------|--------------|
| **35°C** | LED tetap menyala merah (masih panas) |
| **28°C** | LED mati (kandang aman) |
| **25°C** | LED mati (suhu ideal sapi perah) |

---

### 🔍 Penjelasan Kode (Untuk Yang Penasaran)

Bagian terpenting dari kode adalah ini — **hanya 4 baris!**

```cpp
// Jika suhu LEBIH DARI 30 derajat Celsius:
if (suhu > 30.0) {
    digitalWrite(LED, HIGH);  // → Nyalakan LED merah (BAHAYA!)
} else {
    digitalWrite(LED, LOW);   // → Matikan LED (Aman)
}
```

Kamu tidak perlu memahami semua kodenya. Cukup tahu bahwa:
- **Angka `30.0`** = batas suhu aman kandang sapi
- **`HIGH`** = lampu nyala
- **`LOW`** = lampu mati

---

### 💡 Tantangan Bonus (Nilai Tambah)

- [ ] Ubah `30.0` menjadi `25.0` — apa yang terjadi?
- [ ] Tambahkan **LED Hijau** yang menyala saat suhu aman
- [ ] Tambahkan teks `"AMAN!"` atau `"PANAS!"` di layar LCD
- [ ] Buat LED merah **berkedip-kedip** saat bahaya (hint: gunakan `delay`)

---

## 🗂️ Struktur Repositori

```
praktik_PTK2026/
│
├── 📊 IoT_untuk_Peternakan_UNMUL.pptx      ← Slide kuliah (22 slide)
│
├── 📁 praktikum_wokwi/
│   ├── 🟢 sketch.ino                       ← [Level Dasar]   Kode Arduino Uno
│   ├── 🟢 diagram.json                     ← [Level Dasar]   Rangkaian Arduino Uno
│   ├── 🔵 sketch_telegram.ino              ← [Level Lanjutan] Kode ESP32 + Telegram
│   ├── 🔵 diagram_telegram.json            ← [Level Lanjutan] Rangkaian ESP32
│   └── 📖 PANDUAN_PRAKTIKUM.md            ← Panduan + soal diskusi + tantangan
│
└── 📄 README.md                            ← Halaman ini
```

> **Mulai dari Level Dasar** jika baru pertama kali. Setelah berhasil, lanjut ke Level Lanjutan (Telegram)!

---

## ❓ Pertanyaan Diskusi

Jawab bersama teman dan dosen kamu:

1. Jika kamu punya kandang sapi 50 ekor, **sensor apa saja** yang paling penting dipasang pertama kali?
2. Bayangkan kamu peternak sapi sawit (SISKA) di Kutai Kartanegara. **Apa manfaat GPS collar** bagi ternakmu?
3. Menurut kamu, **apa hambatan terbesar** penerapan IoT di peternakan lokal Kaltim?

---

## 📞 Informasi

| | |
|-|-|
| **Institusi** | Fakultas Peternakan, **UNIVERSITAS MULAWARMAN** |
| **Kota** | Samarinda, Kalimantan Timur |
| **Website** | [unmul.ac.id](https://unmul.ac.id) |
| **Simulator IoT** | [wokwi.com](https://wokwi.com) |
| **Telegram Bot** | [@BotFather](https://t.me/BotFather) (untuk buat bot sendiri) |
| **Tahun** | 2026 |

---

<div align="center">

*"Peternak masa depan bukan hanya yang ahli beternak,*
*tapi yang juga mampu memanfaatkan teknologi untuk kemajuan peternakan!"*

🐄 🌐 🚀

</div>
