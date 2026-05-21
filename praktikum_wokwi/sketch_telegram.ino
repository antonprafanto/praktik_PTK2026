// ================================================================
//  PROYEK WOKWI v2: Monitor Kandang + TELEGRAM BOT (ESP32)
//  Fakultas Peternakan — Universitas Mulawarman 2026
//  Simulator: https://wokwi.com
// ================================================================
//
//  KOMPONEN VIRTUAL (ESP32 — punya WiFi bawaan!):
//  - 1x ESP32 DevKit V1  (otak + WiFi)
//  - 1x Sensor DHT22     (suhu & kelembaban)
//  - 1x LCD 16x2         (layar penampil)
//  - 1x LED Merah        (lampu alarm fisik)
//
//  CARA KERJA:
//  ✅ Di SIMULATOR Wokwi: notifikasi Telegram ditampilkan
//     di Serial Monitor (kotak hitam di bawah simulator)
//  ✅ Di HARDWARE NYATA:  notifikasi terkirim ke HP kamu
//     lewat aplikasi Telegram
//
//  Aktifkan bagian kode yang dikomentari (#) untuk hardware asli!
// ================================================================

#include <LiquidCrystal.h>   // Library LCD
#include <DHT.h>             // Library sensor suhu DHT

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

// ── Konfigurasi Pin ESP32 ──────────────────────────────────────
#define PIN_SENSOR      15     // DHT22 data → GPIO 15
#define JENIS_SENSOR    DHT22
#define PIN_LED_ALARM   2      // LED Merah → GPIO 2 (LED bawaan ESP32)

// ── Batas Suhu Kandang Sapi ────────────────────────────────────
#define BATAS_PANAS     30.0   // ⚠️ Peringatan (°C)
#define BATAS_KRITIS    35.0   // 🚨 Bahaya kritis (°C)

// ── LCD: LiquidCrystal(RS, E, D4, D5, D6, D7) ─────────────────
LiquidCrystal lcd(23, 22, 21, 19, 18, 5);

// ── Sensor DHT22 ──────────────────────────────────────────────
DHT sensor(PIN_SENSOR, JENIS_SENSOR);

// ── Variabel Status ───────────────────────────────────────────
bool  sudah_alert       = false;
int   hitungan_bacaan   = 0;

// ================================================================
//  FUNGSI: Kirim Notifikasi ke Telegram
//  Di simulator → tampil di Serial Monitor (kotak hitam)
//  Di hardware  → terkirim ke HP lewat Telegram
// ================================================================
void kirimTelegram(String ikon, String judul, String isi) {
    // ── [SIMULATOR] Tampilkan di Serial Monitor ─────────────────
    Serial.println();
    Serial.println(F("╔══════════════════════════════════════╗"));
    Serial.println(F("║  📱  NOTIFIKASI TELEGRAM BOT          ║"));
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
//  FUNGSI: Tampilkan Ikon Status di LCD Baris ke-2
// ================================================================
void tampilStatusLCD(float suhu) {
    lcd.setCursor(0, 1);
    if (suhu >= BATAS_KRITIS) {
        lcd.print("STATUS: KRITIS!!"); // Darurat
    } else if (suhu >= BATAS_PANAS) {
        lcd.print("STATUS: PANAS ! "); // Peringatan
    } else {
        lcd.print("STATUS: AMAN :) "); // Normal
    }
}

// ================================================================
//  SETUP — Dijalankan SEKALI saat ESP32 menyala
// ================================================================
void setup() {
    Serial.begin(115200);

    lcd.begin(16, 2);
    sensor.begin();
    pinMode(PIN_LED_ALARM, OUTPUT);

    // Splash screen
    lcd.setCursor(0, 0); lcd.print(" KANDANG PINTAR ");
    lcd.setCursor(0, 1); lcd.print("  IoT+Telegram  ");
    delay(2500);
    lcd.clear();

    // Untuk hardware nyata — koneksi WiFi:
    // Serial.print("Menghubungkan ke WiFi");
    // WiFi.begin(WIFI_SSID, WIFI_PASS);
    // while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    // Serial.println(" Terhubung!");
    // klien.setCACert(TELEGRAM_CERTIFICATE_ROOT);

    Serial.println(F("\n============================================"));
    Serial.println(F("   SISTEM MONITOR KANDANG SAPI — AKTIF!   "));
    Serial.println(F("   ESP32 + DHT22 + LCD + Telegram Bot      "));
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
        lcd.setCursor(0, 0); lcd.print("ERROR: Cek Sensor");
        Serial.println(F("[ERROR] Sensor tidak terbaca!"));
        delay(2000);
        return;
    }

    hitungan_bacaan++;

    // ── Tampilkan di LCD Baris 1 (Suhu) ────────────────────────
    lcd.setCursor(0, 0);
    lcd.print("Suhu: ");
    lcd.print(suhu, 1);
    lcd.print((char)223);  // Simbol °
    lcd.print("C  ");

    // ── Tampilkan status di LCD Baris 2 ────────────────────────
    tampilStatusLCD(suhu);

    // ── Log sederhana ke Serial Monitor ────────────────────────
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
        // ✅ KONDISI 3: Suhu kembali normal → Kirim laporan baik
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
