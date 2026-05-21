// ================================================================
//  PROYEK WOKWI v3: Monitor Kandang + TELEGRAM BOT (ESP32 + OLED)
//  Fakultas Peternakan — Universitas Mulawarman 2026
//  Simulator: https://wokwi.com
// ================================================================
//
//  KOMPONEN VIRTUAL (ESP32 — punya WiFi bawaan!):
//  - 1x ESP32 DevKit V1  (otak + WiFi)
//  - 1x Sensor DHT22     (suhu & kelembaban)
//  - 1x OLED SSD1306 0.96" I2C  (layar penampil — lebih mudah!)
//  - 1x LED Merah        (lampu alarm fisik)
//
//  KEUNGGULAN OLED vs LCD:
//  ✅ Hanya 2 kabel data (SDA + SCL) — jauh lebih simpel!
//  ✅ Tidak ada masalah strapping pin
//  ✅ Tampilan lebih keren & modern
//
//  CARA KERJA:
//  ✅ Di SIMULATOR Wokwi: notifikasi Telegram ditampilkan
//     di Serial Monitor (kotak hitam di bawah simulator)
//  ✅ Di HARDWARE NYATA:  notifikasi terkirim ke HP kamu
//     lewat aplikasi Telegram
// ================================================================

#include <Wire.h>                   // Library I2C (untuk OLED)
#include <Adafruit_GFX.h>           // Library grafis dasar OLED
#include <Adafruit_SSD1306.h>       // Library OLED SSD1306
#include <DHT.h>                    // Library sensor suhu DHT

// ── Untuk Hardware Nyata: Hapus "//" dari baris-baris ini ──────
// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <UniversalTelegramBot.h>  // Install via Library Manager

// const char* WIFI_SSID  = "NamaWiFiKamu";      // ← Ganti!
// const char* WIFI_PASS  = "PasswordWiFiKamu";  // ← Ganti!
// const String BOT_TOKEN = "1234567890:ABCDEF_TOKEN_DARI_BOTFATHER"; // ← Ganti!
// const String CHAT_ID   = "-1001234567890";    // ← Ganti!
// WiFiClientSecure klien;
// UniversalTelegramBot bot(BOT_TOKEN, klien);
// ───────────────────────────────────────────────────────────────

// ── Konfigurasi OLED ──────────────────────────────────────────
#define OLED_WIDTH   128
#define OLED_HEIGHT   64
#define OLED_ADDRESS 0x3C   // Alamat I2C OLED (biasanya 0x3C)
// SDA → GPIO 21 (default I2C ESP32)
// SCL → GPIO 22 (default I2C ESP32)
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// ── Konfigurasi Sensor DHT22 ──────────────────────────────────
#define PIN_SENSOR    15    // DHT22 data → GPIO 15
#define JENIS_SENSOR  DHT22
DHT sensor(PIN_SENSOR, JENIS_SENSOR);

// ── Konfigurasi LED Alarm ─────────────────────────────────────
#define PIN_LED_ALARM  2    // LED Merah → GPIO 2

// ── Batas Suhu Kandang Sapi ────────────────────────────────────
#define BATAS_PANAS   30.0  // ⚠️ Peringatan (°C)
#define BATAS_KRITIS  35.0  // 🚨 Bahaya kritis (°C)

// ── Variabel Status ───────────────────────────────────────────
bool  sudah_alert     = false;
int   hitungan_bacaan = 0;

// ================================================================
//  FUNGSI: Tampilkan data di OLED
// ================================================================
void tampilOLED(float suhu, float lembab) {
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);

    // ── Baris 1: Judul ─────────────────────────────────────────
    oled.setTextSize(1);
    oled.setCursor(10, 0);
    oled.print("KANDANG SAPI UNMUL");

    // ── Garis pemisah ──────────────────────────────────────────
    oled.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    // ── Baris 2: Suhu (teks besar) ─────────────────────────────
    oled.setTextSize(2);
    oled.setCursor(0, 16);
    oled.print("T:");
    oled.print(suhu, 1);
    oled.print("C");

    // ── Baris 3: Kelembaban ────────────────────────────────────
    oled.setTextSize(1);
    oled.setCursor(0, 38);
    oled.print("Kelembaban: ");
    oled.print(lembab, 1);
    oled.print("%");

    // ── Baris 4: Status ────────────────────────────────────────
    oled.setCursor(0, 52);
    if (suhu >= BATAS_KRITIS) {
        oled.print("!! KRITIS - BAHAYA !!");
    } else if (suhu >= BATAS_PANAS) {
        oled.print(">> PANAS - Waspada! ");
    } else {
        oled.print("   STATUS: AMAN :)  ");
    }

    oled.display();
}

// ================================================================
//  FUNGSI: Kirim Notifikasi ke Telegram
//  Di simulator → tampil di Serial Monitor
//  Di hardware  → terkirim ke HP lewat Telegram
// ================================================================
void kirimTelegram(String ikon, String judul, String isi) {
    // ── [SIMULATOR] Tampilkan di Serial Monitor ─────────────────
    Serial.println();
    Serial.println(F("╔══════════════════════════════════════╗"));
    Serial.println(F("║  📱  NOTIFIKASI TELEGRAM BOT         ║"));
    Serial.println(F("╠══════════════════════════════════════╣"));
    Serial.print(F("║  Dari : @KandangSapiUNMUL_Bot        "));
    Serial.println(F("║"));
    Serial.print(F("║  "));
    Serial.print(ikon); Serial.print(F(" ")); Serial.println(judul);
    Serial.print(F("║  ")); Serial.println(isi);
    Serial.println(F("╚══════════════════════════════════════╝"));

    // ── [HARDWARE NYATA] Aktifkan baris ini ─────────────────────
    // String pesan = ikon + " *" + judul + "*\n" + isi;
    // bot.sendMessage(CHAT_ID, pesan, "Markdown");
}

// ================================================================
//  SETUP — Dijalankan SEKALI saat ESP32 menyala
// ================================================================
void setup() {
    Serial.begin(115200);
    delay(500);   // Tunggu ESP32 stabil

    // Inisialisasi OLED
    Wire.begin(21, 22);   // SDA=21, SCL=22 (default I2C ESP32)
    if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("[ERROR] OLED tidak terdeteksi!"));
        while (true);   // Berhenti jika OLED tidak ditemukan
    }

    // Inisialisasi sensor & LED
    sensor.begin();
    pinMode(PIN_LED_ALARM, OUTPUT);

    // Splash screen OLED
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(15, 10); oled.print("KANDANG PINTAR");
    oled.setCursor(10, 25); oled.print("IoT + Telegram Bot");
    oled.setCursor(5,  40); oled.print("Fapet UNMUL 2026");
    oled.display();
    delay(2500);

    Serial.println(F("\n============================================"));
    Serial.println(F("   SISTEM MONITOR KANDANG SAPI — AKTIF!   "));
    Serial.println(F("   ESP32 + DHT22 + OLED + Telegram Bot     "));
    Serial.println(F("============================================"));
    Serial.println(F("   Perhatikan kotak notifikasi Telegram    "));
    Serial.println(F("   yang muncul di Serial Monitor ini!       "));
    Serial.println(F("============================================\n"));

    // Kirim notifikasi sistem aktif
    kirimTelegram("✅", "Sistem Kandang AKTIF",
        "Monitor kandang sapi menyala.\nSiap memantau 24 jam nonstop!");
}

// ================================================================
//  LOOP — Diulang TERUS setiap 3 detik
// ================================================================
void loop() {
    float suhu   = sensor.readTemperature();
    float lembab = sensor.readHumidity();

    // Validasi data sensor
    if (isnan(suhu) || isnan(lembab)) {
        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setCursor(0, 20); oled.print("ERROR: Cek Sensor!");
        oled.display();
        Serial.println(F("[ERROR] Sensor tidak terbaca!"));
        delay(2000);
        return;
    }

    hitungan_bacaan++;

    // Tampilkan di OLED
    tampilOLED(suhu, lembab);

    // Log ke Serial Monitor
    Serial.print(F("[#")); Serial.print(hitungan_bacaan);
    Serial.print(F("] Suhu: ")); Serial.print(suhu);
    Serial.print(F("°C | Lembab: ")); Serial.print(lembab);
    Serial.println(F("%"));

    // ══════════════════════════════════════════════════════════
    //  LOGIKA ALERT TELEGRAM — 3 Kondisi
    // ══════════════════════════════════════════════════════════

    if (suhu >= BATAS_KRITIS && !sudah_alert) {
        // 🚨 KONDISI 1: Suhu SANGAT tinggi (> 35°C) → Darurat!
        digitalWrite(PIN_LED_ALARM, HIGH);
        kirimTelegram("🚨", "BAHAYA KRITIS!",
            "Suhu kandang: " + String(suhu, 1) + String((char)176) + "C\n"
            "Melebihi 35" + String((char)176) + "C — SANGAT BERBAHAYA!\n"
            "Sapi butuh pendinginan SEGERA!\n"
            "Segera hubungi drh. / teknisi!");
        sudah_alert = true;

    } else if (suhu >= BATAS_PANAS && !sudah_alert) {
        // ⚠️ KONDISI 2: Suhu tinggi (> 30°C) → Peringatan
        digitalWrite(PIN_LED_ALARM, HIGH);
        kirimTelegram("⚠️", "PERINGATAN SUHU PANAS",
            "Suhu kandang: " + String(suhu, 1) + String((char)176) + "C\n"
            "Melewati batas aman 30" + String((char)176) + "C.\n"
            "Nyalakan kipas / buka ventilasi!");
        sudah_alert = true;

    } else if (suhu < BATAS_PANAS) {
        // ✅ KONDISI 3: Suhu kembali normal
        digitalWrite(PIN_LED_ALARM, LOW);
        if (sudah_alert) {
            kirimTelegram("✅", "KANDANG SUDAH NORMAL",
                "Suhu turun ke: " + String(suhu, 1) + String((char)176) + "C\n"
                "Kelembaban: " + String(lembab, 1) + "%\n"
                "Kondisi kandang kembali aman!");
            sudah_alert = false;
        }
    }

    // ── Laporan rutin setiap 10 bacaan (30 detik) ──────────────
    if (hitungan_bacaan % 10 == 0) {
        String status_str = (suhu < BATAS_PANAS) ? "AMAN" : "BUTUH PERHATIAN";
        kirimTelegram("📊", "Laporan Berkala Kandang",
            "Suhu   : " + String(suhu, 1) + String((char)176) + "C\n"
            "Lembab : " + String(lembab, 1) + "%\n"
            "Status : " + status_str + "\n"
            "Bacaan ke-" + String(hitungan_bacaan));
    }

    delay(3000);
}

// ================================================================
//  TANTANGAN MAHASISWA:
//  1. Ubah BATAS_PANAS dari 30 → 25. Apa yang berubah?
//  2. Tambahkan pesan Telegram saat kelembaban > 85%
//     (tanda kandang terlalu lembab = risiko jamur)
//  3. Bisakah kamu tambahkan fitur menerima perintah dari Telegram?
//     Contoh: kirim "/status" → bot balas dengan suhu terkini
// ================================================================
