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

| File | Keterangan | Link |
|------|-----------|------|
| 📊 **Slide Presentasi PPT** | Materi lengkap 20 slide, tema hijau premium | [⬇️ Download PPT](IoT_untuk_Peternakan_UNMUL.pptx) |
| 🧪 **Kode Arduino (sketch.ino)** | Kode simulasi monitor suhu kandang | [⬇️ Download sketch.ino](praktikum_wokwi/sketch.ino) |
| 🔌 **Diagram Rangkaian (diagram.json)** | Rangkaian virtual sensor + LCD + LED | [⬇️ Download diagram.json](praktikum_wokwi/diagram.json) |
| 📖 **Panduan Praktikum** | Langkah-langkah penggunaan Wokwi | [⬇️ Download Panduan](praktikum_wokwi/PANDUAN_PRAKTIKUM.md) |

---

## 📚 Isi Materi (20 Slide)

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
| 13 | **🧪 Praktikum Wokwi** | **Simulasi IoT langsung di browser (GRATIS!)** |
| 14 | 💡 Kesimpulan | Rangkuman poin kunci materi |

---

## 🧪 Praktikum Simulasi IoT — Wokwi

> **Wokwi** adalah simulator Arduino/IoT yang **gratis dan berbasis browser**. Kamu bisa mencoba IoT **tanpa membeli hardware apapun!**

### Yang Akan Kita Buat:

```
🌡️ Sensor DHT22  →  📺 Layar LCD  →  🔴 LED Alarm
   (Baca suhu)      (Tampilkan data)   (Nyala jika > 30°C)
```

Simulasi ini meniru cara kerja **sensor suhu kandang sapi** yang sesungguhnya!

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

Klik **`+ New Project`** → pilih **`Arduino Uno`**

---

#### Langkah 3 — Tempel Kode Program

1. Klik tab **`sketch.ino`** di editor Wokwi
2. Pilih semua teks → **`Ctrl + A`** → hapus → **`Delete`**
3. Buka file [`sketch.ino`](praktikum_wokwi/sketch.ino) dari repo ini
4. Salin semua (**`Ctrl + A`** → **`Ctrl + C`**)
5. Tempel ke Wokwi (**`Ctrl + V`**)

---

#### Langkah 4 — Tempel Rangkaian Virtual

1. Klik tab **`diagram.json`** di Wokwi
2. Pilih semua → hapus → tempel isi file [`diagram.json`](praktikum_wokwi/diagram.json)

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
├── 📊 IoT_untuk_Peternakan_UNMUL.pptx   ← Slide kuliah (20 slide)
│
├── 📁 praktikum_wokwi/
│   ├── 🔧 sketch.ino                    ← Kode Arduino (copy-paste ke Wokwi)
│   ├── 🔌 diagram.json                  ← Rangkaian virtual (copy-paste ke Wokwi)
│   └── 📖 PANDUAN_PRAKTIKUM.md         ← Panduan lengkap + soal diskusi
│
└── 📄 README.md                         ← Halaman ini
```

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
| **Institusi** | Fakultas Peternakan, Universitas Mulawarman |
| **Kota** | Samarinda, Kalimantan Timur |
| **Website** | [unmul.ac.id](https://unmul.ac.id) |
| **Simulator** | [wokwi.com](https://wokwi.com) |
| **Tahun** | 2026 |

---

<div align="center">

*"Peternak masa depan bukan hanya yang ahli beternak,*
*tapi yang juga mampu memanfaatkan teknologi untuk kemajuan peternakan!"*

🐄 🌐 🚀

</div>
