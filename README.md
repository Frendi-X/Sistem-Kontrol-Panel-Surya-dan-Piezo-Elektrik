# Sistem-Kontrol-Panel-Surya-dan-Piezo-Elektrik

Proyek ini adalah sebuah sistem pemantauan yang mengintegrasikan berbagai sensor untuk mengukur kondisi lingkungan dan memberikan informasi visual melalui LCD dan LED. Mikrokontroler yang digunakan dalam proyek ini adalah Arduino yang bertugas untuk membaca data dari berbagai sensor dan mengontrol berbagai perangkat output. Proyek ini memantau beberapa parameter lingkungan seperti suhu, kelembaban, intensitas cahaya, getaran, curah hujan, daya panel surya, kondisi baterai, dan kondisi piezoelektrik. Data yang terkumpul kemudian ditampilkan pada LCD dan dikontrol dengan indikator LED serta relay. Sistem ini bisa digunakan untuk aplikasi yang memerlukan pengawasan kondisi lingkungan, seperti di rumah pintar atau sistem pertanian otomatis. [SKRIPSI - Teknik ELektro UMPO]

## ⚙️ Fitur Utama
- 🌡️ **Sensor suhu & kelembaban** dengan DHT11.  
- ☀️ **Sensor intensitas cahaya (lux)** menggunakan BH1750.  
- 🌧️ **Ombrometer (rain gauge)** untuk menghitung curah hujan berdasarkan jumlah tipping bucket.  
- 🔋 **Monitoring tegangan baterai & panel surya** melalui pembacaan analog.  
- ⚡ **Piezo sensor** sebagai indikator tegangan simulasi getaran.  
- 🚨 **Deteksi getaran (Vibrator)** untuk event kondisi tertentu.  
- 🖥️ **LCD 20x4** menampilkan data lengkap (suhu, kelembaban, lux, tegangan, curah hujan).  
- 💡 **Kontrol relay & LED indikator** berdasarkan kondisi cahaya.  

---

## 🛠️ Komponen Hardware
- Arduino (UNO/Nano/Pro Mini)  
- Sensor DHT11 (suhu & kelembaban)  
- Sensor cahaya BH1750 (lux meter)  
- Ombrometer (rain gauge / tipping bucket)  
- Sensor getaran (vibration switch)  
- Piezo sensor  
- LCD 20x4 I2C  
- LED indikator (biru, hijau, kuning)  
- Modul relay  
- Sumber daya (baterai + panel surya)  

---

## 📐 Wiring Pin
| Komponen          | Pin Arduino |
|-------------------|-------------|
| DHT11             | 11          |
| Ombrometer        | 7           |
| Relay             | 8           |
| LED Biru          | 9           |
| LED Hijau         | 10          |
| LED Kuning        | 13          |
| Vibrator          | 12          |
| VBatt (ADC)       | A0          |
| VPanel (ADC)      | A1          |
| VPiezo (ADC)      | A2          |
| LCD I2C           | SDA/SCL     |
| BH1750 (I2C)      | SDA/SCL     |

---

## 🚀 Cara Kerja Sistem
1. **Pembacaan sensor:**
   - DHT11 untuk suhu & kelembaban.  
   - BH1750 untuk intensitas cahaya.  
   - Ombrometer menghitung curah hujan (mm) berdasarkan pulsa tipping bucket.  
   - Vibrator & piezo sebagai deteksi getaran tambahan.  
   - Tegangan baterai & panel surya dipantau via ADC.  
   
2. **Tampilan data:**  
   Semua data ditampilkan pada LCD 20x4, meliputi:  
   - Tegangan baterai & panel.  
   - Suhu (°C) & kelembaban (%).  
   - Intensitas cahaya (lux).  
   - Curah hujan (mm).  

3. **Kontrol otomatis:**  
   - Jika intensitas cahaya ≥ 300 lux → Relay ON, LED biru ON.  
   - Jika < 300 lux → Relay OFF, LED hijau & kuning ON.  

4. **Event getaran:**  
   Saat getaran terdeteksi, sistem melakukan pembacaan tambahan & mengaktifkan simulasi tegangan piezo.  

---

## 📂 Struktur Kode
- `weather_station.ino` → Program utama pembacaan sensor, tampilan LCD, dan kontrol otomatis.  

### Library yang digunakan
- `Wire.h`  
- `BH1750.h`  
- `LiquidCrystal_I2C.h`  
- `DHT.h`  

---

## 📸 Tampilan LCD
LCD 20x4 menampilkan:  
- Baris 1 → Tegangan baterai + suhu  
- Baris 2 → Tegangan panel + kelembaban  
- Baris 3 → Tegangan piezo simulasi

---

## ✨ Lisensi
Proyek ini bersifat open-source. Silakan digunakan, dimodifikasi, dan dikembangkan lebih lanjut.  

---

## Contacs us : 
* [Frendi RoboTech](https://www.instagram.com/frendi.co/)
* [Whatsapp : +6287888227410](https://wa.me/+6287888227410)
* [Email    : frendirobotech@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendirobotech@gmail.com) atau [Email    : frendix45@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendix45@gmail.com)
- Baris 4 → Curah hujan (mm) + LUX  

---

## 👨‍💻 Author
Dikembangkan oleh: Imam Sa'id Nurfrendi [Reog Robotic & Robotech Electronics]  
