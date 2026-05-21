// ============================================================
//  PROYEK WOKWI: MONITOR SUHU & KELEMBABAN KANDANG SAPI
//  Mata Kuliah: Pengenalan IoT - Fapet Universitas Mulawarman
//  Kerjakan di: https://wokwi.com
// ============================================================
//
//  KOMPONEN YANG DIGUNAKAN (Semuanya VIRTUAL, tidak beli):
//  - 1x Arduino Uno (otak mini)
//  - 1x Sensor DHT22 (sensor suhu & kelembaban)
//  - 1x LCD 16x2 (layar penampil data)
//  - 1x LED Merah (lampu alarm)
//  - 1x Resistor 220 Ohm (pengaman LED)
//  - Kabel-kabel virtual
//
//  CARA KERJA:
//  Sensor DHT22 membaca suhu & kelembaban kandang setiap 2 detik.
//  Hasilnya ditampilkan di layar LCD.
//  Jika suhu LEBIH DARI 30 derajat Celsius → LED MERAH nyala (ALERT!)
//  Artinya: kandang terlalu panas, sapi perlu disegarkan!
// ============================================================

// --- Mengaktifkan pustaka (library) yang dibutuhkan ---
#include <LiquidCrystal.h>   // Library untuk layar LCD
#include <DHT.h>             // Library untuk sensor suhu DHT22

// --- Menentukan pin (kaki) Arduino ---
#define PIN_SENSOR  2        // Kaki data sensor DHT22 terhubung ke pin 2
#define JENIS_SENSOR DHT22   // Jenis sensor yang kita pakai adalah DHT22
#define PIN_LED_ALARM 13     // LED merah terhubung ke pin 13

// --- Batas Suhu Aman Kandang Sapi ---
// Suhu kandang sapi ideal adalah 18–27°C
// Jika melewati batas ini, LED alarm akan menyala
#define BATAS_SUHU_PANAS 30.0   // dalam derajat Celsius

// --- Menghubungkan LCD ke Arduino ---
// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// --- Membuat objek sensor ---
DHT sensor(PIN_SENSOR, JENIS_SENSOR);

// ============================================================
// SETUP: Dijalankan SEKALI saat Arduino pertama menyala
// ============================================================
void setup() {
  // Memulai layar LCD (16 kolom, 2 baris)
  lcd.begin(16, 2);

  // Memulai sensor suhu
  sensor.begin();

  // Mengatur pin LED sebagai OUTPUT (pengirim sinyal)
  pinMode(PIN_LED_ALARM, OUTPUT);
  
  // Tampilkan pesan pembuka di LCD
  lcd.setCursor(0, 0);
  lcd.print("  KANDANG SAPI  ");
  lcd.setCursor(0, 1);
  lcd.print("Monitor Aktif...");
  delay(2500);     // Tunggu 2.5 detik
  lcd.clear();     // Bersihkan layar
}

// ============================================================
// LOOP: Dijalankan TERUS-MENERUS selama Arduino hidup
// ============================================================
void loop() {
  
  // --- Langkah 1: Baca data dari sensor ---
  float suhu_C      = sensor.readTemperature();   // Baca suhu (Celsius)
  float kelembaban  = sensor.readHumidity();      // Baca kelembaban (%)

  // --- Langkah 2: Periksa apakah data valid ---
  if (isnan(suhu_C) || isnan(kelembaban)) {
    lcd.setCursor(0, 0);
    lcd.print("Error: Cek Sensor");
    delay(2000);
    return;   // Ulangi dari awal loop
  }

  // --- Langkah 3: Tampilkan data di LCD ---
  lcd.setCursor(0, 0);
  lcd.print("Suhu  : ");
  lcd.print(suhu_C, 1);       // 1 angka di belakang koma
  lcd.print((char)223);        // Simbol derajat °
  lcd.print("C  ");

  lcd.setCursor(0, 1);
  lcd.print("Lembab: ");
  lcd.print(kelembaban, 1);
  lcd.print(" %   ");

  // --- Langkah 4: Nyalakan LED alarm jika kandang terlalu panas ---
  if (suhu_C > BATAS_SUHU_PANAS) {
    digitalWrite(PIN_LED_ALARM, HIGH);  // LED MERAH MENYALA → BAHAYA!
    // [Tantangan mahasiswa] Coba tambahkan bunyi buzzer di sini!
  } else {
    digitalWrite(PIN_LED_ALARM, LOW);   // LED mati → Kandang Aman
  }

  // --- Langkah 5: Tunggu 2 detik sebelum baca ulang ---
  delay(2000);
}

// ============================================================
// TANTANGAN UNTUK MAHASISWA:
// 1. Ubah nilai BATAS_SUHU_PANAS dari 30 menjadi 25. Apa yang terjadi?
// 2. Coba tambahkan LED HIJAU yang menyala ketika suhu AMAN (< 30°C)
// 3. Bisakah kamu tambahkan tampilan "AMAN!" atau "PANAS!" di baris LCD?
// ============================================================
