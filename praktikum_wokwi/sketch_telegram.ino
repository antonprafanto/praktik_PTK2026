// ================================================================
//  PROYEK WOKWI: Monitor Kandang Sapi + TELEGRAM BOT (ESP32)
//  Fakultas Peternakan — Universitas Mulawarman 2026
//  Referensi: https://wokwi.com/projects/370308747349207041
//  Simulator: https://wokwi.com
// ================================================================
//
//  KOMPONEN:
//  - ESP32 DevKit V1  (otak + WiFi)
//  - Sensor DHT22     (suhu & kelembaban)
//  - OLED SSD1306 I2C (layar penampil — hanya 2 kabel!)
//  - LED Merah        (lampu alarm)
//
//  FITUR:
//  ✅ Kirim notifikasi suhu ke Telegram otomatis tiap 30 detik
//  ✅ Kirim ALERT darurat jika suhu > 30°C atau > 35°C
//  ✅ Terima perintah dari Telegram (/status, /start, dll.)
//  ✅ Di Wokwi: pakai WiFi "Wokwi-GUEST" (gratis, tanpa password!)
// ================================================================

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>             // ← Wajib ada sebelum UniversalTelegramBot!
#include <UniversalTelegramBot.h>
#include "DHTesp.h"                  // Library DHT khusus ESP32
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ── WiFi (Wokwi-GUEST = WiFi virtual Wokwi, gratis!) ──────────
const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// ── Telegram Bot (Ganti dengan token & chat_id milikmu!) ──────
// Cara dapat BOTtoken: Chat @BotFather di Telegram → /newbot
// Cara dapat CHAT_ID:  Chat @myidbot di Telegram → kirim /start → ID langsung muncul!
#define BOTtoken  "MASUKKAN_TOKEN_BOT_KAMU_DISINI"
#define CHAT_ID   "MASUKKAN_CHAT_ID_KAMU_DISINI"

// ── Untuk Demo/Simulasi: gunakan token contoh dari referensi ───
// #define BOTtoken  "6323579581:AAHFEgqXhRQ5RyS2E47cIKfz6yfv6hf3kUs"
// #define CHAT_ID   "27892295"

// ── Konfigurasi Pin ────────────────────────────────────────────
#define DHT_PIN       15    // DHT22 → GPIO 15
#define PIN_LED_ALARM  2    // LED Merah → GPIO 2

// ── Batas Suhu Kandang Sapi ────────────────────────────────────
#define BATAS_PANAS   30.0  // ⚠️ Peringatan
#define BATAS_KRITIS  35.0  // 🚨 Darurat

// ── Interval Waktu ─────────────────────────────────────────────
#define WAKTU_KIRIM   30000   // Kirim laporan setiap 30 detik
#define WAKTU_BACA    1000    // Cek pesan Telegram setiap 1 detik

// ── OLED SSD1306 I2C (SDA=GPIO21, SCL=GPIO22) ─────────────────
#define OLED_WIDTH   128
#define OLED_HEIGHT   64
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// ── Objek Library ─────────────────────────────────────────────
WiFiClientSecure   klien;
UniversalTelegramBot bot(BOTtoken, klien);
DHTesp             dhtSensor;

// ── Variabel Status ───────────────────────────────────────────
bool  sudah_alert        = false;
bool  sensor_valid       = false;   // ← Cegah alert palsu saat boot (suhu=0)
float suhu_terakhir      = 0;
float lembab_terakhir    = 0;
unsigned long waktu_baca_dht = 0;  // ← Guard interval minimum DHTesp (2 detik)

// ================================================================
//  FUNGSI: Tampilkan data di OLED
// ================================================================
void tampilOLED(float suhu, float lembab, String status) {
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);

    // Judul
    oled.setTextSize(1);
    oled.setCursor(8, 0);
    oled.print("KANDANG SAPI UNMUL");
    oled.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    // Suhu (teks besar)
    oled.setTextSize(2);
    oled.setCursor(0, 14);
    oled.print("T:"); oled.print(suhu, 1); oled.print("C");

    // Kelembaban
    oled.setTextSize(1);
    oled.setCursor(0, 36);
    oled.print("Kelembaban: "); oled.print(lembab, 1); oled.print("%");

    // Status
    oled.setCursor(0, 50);
    oled.print(status);

    oled.display();
}

// ================================================================
//  FUNGSI: Tangani pesan masuk dari Telegram
// ================================================================
void tanganiPesan(int jumlahPesan) {
    for (int i = 0; i < jumlahPesan; i++) {
        String chat_id = String(bot.messages[i].chat_id);
        String teks    = bot.messages[i].text;
        String nama    = bot.messages[i].from_name;

        Serial.print(F("[Telegram] Pesan dari ")); Serial.print(nama);
        Serial.print(F(": ")); Serial.println(teks);

        if (teks == "/start") {
            String sambutan = "Halo, " + nama + "! 🐄\n";
            sambutan += "Selamat datang di Monitor Kandang Sapi UNMUL!\n\n";
            sambutan += "Perintah yang tersedia:\n";
            sambutan += "/status — Cek suhu & kelembaban sekarang\n";
            sambutan += "/start  — Tampilkan menu ini\n";
            bot.sendMessage(chat_id, sambutan, "");
        }

        if (teks == "/status") {
            String laporan = "📊 *Status Kandang Terkini*\n";
            laporan += "🌡 Suhu     : " + String(suhu_terakhir, 1) + "°C\n";
            laporan += "💧 Lembab  : " + String(lembab_terakhir, 1) + "%\n";
            if (suhu_terakhir >= BATAS_KRITIS)
                laporan += "🚨 Status  : KRITIS - BAHAYA!";
            else if (suhu_terakhir >= BATAS_PANAS)
                laporan += "⚠️ Status  : PANAS - Waspada!";
            else
                laporan += "✅ Status  : AMAN";
            bot.sendMessage(chat_id, laporan, "Markdown");
        }
    }
}

// ================================================================
//  SETUP — Dijalankan SEKALI saat ESP32 menyala
// ================================================================
void setup() {
    Serial.begin(115200);
    delay(500);

    // Inisialisasi OLED
    Wire.begin(21, 22);
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("[ERROR] OLED tidak terdeteksi!"));
        while (true);
    }

    // Inisialisasi sensor & LED
    dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
    pinMode(PIN_LED_ALARM, OUTPUT);

    // Splash screen
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(15, 10); oled.print("KANDANG PINTAR");
    oled.setCursor(5,  25); oled.print("IoT + Telegram Bot");
    oled.setCursor(12, 40); oled.print("Fapet UNMUL 2026");
    oled.setCursor(18, 55); oled.print("Menghubungkan...");
    oled.display();

    // Hubungkan ke WiFi Wokwi (virtual WiFi, tidak perlu password!)
    Serial.print(F("\nMenghubungkan ke WiFi"));
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    klien.setCACert(TELEGRAM_CERTIFICATE_ROOT);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(F("\n✅ WiFi Terhubung!"));
    Serial.print(F("IP: ")); Serial.println(WiFi.localIP());

    Serial.println(F("\n============================================"));
    Serial.println(F("   SISTEM MONITOR KANDANG SAPI — AKTIF!   "));
    Serial.println(F("   Kirim /start ke bot Telegram kamu!      "));
    Serial.println(F("============================================\n"));

    // Kirim notifikasi sistem aktif
    bot.sendMessage(CHAT_ID,
        "✅ *Sistem Kandang Aktif!*\nMonitor kandang sapi UNMUL menyala.\nKirim /status untuk cek kondisi kandang.",
        "Markdown");

    // Update OLED: siap
    tampilOLED(0, 0, "WiFi OK - Siap!");
}

// ================================================================
//  LOOP — Diulang TERUS
// ================================================================
void loop() {
    static unsigned long waktuKirimTerakhir = 0;
    static unsigned long waktuBacaTerakhir  = 0;
    unsigned long sekarang = millis();

    // ── Baca sensor (dengan guard interval minimum DHTesp: 2 detik) ─
    if (sekarang - waktu_baca_dht >= 2000) {
        waktu_baca_dht = sekarang;

        TempAndHumidity data = dhtSensor.getTempAndHumidity();
        float suhu   = data.temperature;
        float lembab = data.humidity;

        if (!isnan(suhu) && !isnan(lembab)) {
            suhu_terakhir   = suhu;
            lembab_terakhir = lembab;
            sensor_valid    = true;   // ← Tandai: data sensor sudah valid

            String status;
            if (suhu >= BATAS_KRITIS)     { status = "!! KRITIS !!"; digitalWrite(PIN_LED_ALARM, HIGH); }
            else if (suhu >= BATAS_PANAS) { status = ">> PANAS <<";  digitalWrite(PIN_LED_ALARM, HIGH); }
            else                          { status = "   AMAN :)  "; digitalWrite(PIN_LED_ALARM, LOW);  }

            tampilOLED(suhu, lembab, status);

            Serial.print(F("Suhu: ")); Serial.print(suhu, 1);
            Serial.print(F("C | Lembab: ")); Serial.print(lembab, 1);
            Serial.println(F("%"));
        } else {
            // Tampilkan error di OLED jika sensor gagal baca
            oled.clearDisplay();
            oled.setTextSize(1);
            oled.setTextColor(SSD1306_WHITE);
            oled.setCursor(0, 20); oled.print("ERROR: Cek Sensor!");
            oled.setCursor(0, 36); oled.print("DHT22 tidak merespons");
            oled.display();
            Serial.println(F("[ERROR] Sensor DHT22 tidak terbaca!"));
        }
    }

    // ── Kirim alert Telegram jika darurat ────────────────────────
    // sensor_valid mencegah alert palsu saat boot (suhu_terakhir masih 0)
    if (sensor_valid) {
        if (suhu_terakhir >= BATAS_KRITIS && !sudah_alert) {
            bot.sendMessage(CHAT_ID,
                "🚨 *BAHAYA KRITIS!*\nSuhu kandang: " + String(suhu_terakhir, 1) + "°C\n"
                "Melebihi 35°C — Sapi butuh pendinginan SEGERA!\nHubungi drh. / teknisi!", "Markdown");
            sudah_alert = true;

        } else if (suhu_terakhir >= BATAS_PANAS && !sudah_alert) {
            bot.sendMessage(CHAT_ID,
                "⚠️ *PERINGATAN SUHU PANAS!*\nSuhu kandang: " + String(suhu_terakhir, 1) + "°C\n"
                "Melewati batas aman 30°C.\nNyalakan kipas / buka ventilasi!", "Markdown");
            sudah_alert = true;

        } else if (suhu_terakhir < BATAS_PANAS && sudah_alert) {
            bot.sendMessage(CHAT_ID,
                "✅ *Kandang Kembali Normal*\nSuhu: " + String(suhu_terakhir, 1) + "°C\n"
                "Kelembaban: " + String(lembab_terakhir, 1) + "%", "Markdown");
            sudah_alert = false;
        }
    }

    // ── Kirim laporan berkala ke Telegram (tiap 30 detik) ────────
    if (sekarang - waktuKirimTerakhir >= WAKTU_KIRIM) {
        waktuKirimTerakhir = sekarang;
        if (sensor_valid) {
            String laporan = "📊 *Laporan Berkala Kandang*\n";
            laporan += "T: " + String(suhu_terakhir, 1) + "C | ";
            laporan += "H: " + String(lembab_terakhir, 1) + "%\n";
            laporan += (suhu_terakhir < BATAS_PANAS) ? "Status: AMAN" : "Status: BUTUH PERHATIAN";
            bot.sendMessage(CHAT_ID, laporan, "Markdown");
            Serial.println(F("[Telegram] Laporan berkala dikirim."));
        }
    }

    // ── Cek pesan masuk dari Telegram (tiap 1 detik) ─────────────
    // Tidak pakai delay(2000) di sini agar timer WAKTU_BACA tetap akurat!
    if (sekarang - waktuBacaTerakhir >= WAKTU_BACA) {
        waktuBacaTerakhir = sekarang;
        int pesan = bot.getUpdates(bot.last_message_received + 1);
        while (pesan) {
            tanganiPesan(pesan);
            pesan = bot.getUpdates(bot.last_message_received + 1);
        }
    }
    // Tidak ada delay() di sini — loop non-blocking!
}

// ================================================================
//  TANTANGAN MAHASISWA:
//  1. Ubah BATAS_PANAS dari 30 → 25. Apa yang berubah?
//  2. Tambahkan perintah /led_on dan /led_off dari Telegram
//     untuk kontrol LED dari jarak jauh!
//  3. Tambahkan alert jika kelembaban > 85% (risiko jamur)
// ================================================================
