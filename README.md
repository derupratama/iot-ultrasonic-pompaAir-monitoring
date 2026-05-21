# README.md

# Ultrasonic Sensor + Water Pump IoT with Blynk (ESP8266)

![IoT](https://img.shields.io/badge/IoT-ESP8266-blue)
![Blynk](https://img.shields.io/badge/Blynk-Connected-green)
![License](https://img.shields.io/badge/License-Educational-orange)

Project IoT sederhana menggunakan ESP8266, sensor ultrasonic HC-SR04, relay pompa air, dan Blynk untuk mendeteksi jarak air atau objek secara real-time.

---

# Features

* Monitoring jarak menggunakan sensor ultrasonic
* Pompa air menyala otomatis ketika jarak kurang dari batas tertentu
* Monitoring data melalui aplikasi Blynk
* Real-time serial monitor
* Cocok untuk pembelajaran IoT dasar

---

# Deskripsi Project

Project ini merupakan implementasi sederhana Internet of Things (IoT) menggunakan ESP8266, sensor ultrasonic HC-SR04, relay pompa air, dan aplikasi Blynk. Sistem bekerja dengan cara membaca jarak menggunakan sensor ultrasonic. Ketika jarak kurang dari nilai tertentu, maka pompa air akan menyala secara otomatis.

Project ini cocok digunakan untuk:

* Monitoring tinggi air
* Sistem pengisian air otomatis
* Praktikum IoT dasar
* Pembelajaran sensor dan aktuator

---

# Komponen yang Digunakan

## Hardware

1. ESP8266 NodeMCU
2. Ultrasonic HC-SR04
3. Relay Module
4. Pompa Air Mini
5. Kabel Jumper
6. Breadboard

---

# Wiring

## Ultrasonic HC-SR04

| Ultrasonic | ESP8266 |
| ---------- | ------- |
| VCC        | VIN     |
| GND        | GND     |
| TRIG       | D5      |
| ECHO       | D6      |

## Relay Pompa Air

| Relay | ESP8266 |
| ----- | ------- |
| IN    | D1      |
| VCC   | VIN     |
| GND   | GND     |

---

# Library yang Digunakan

Install library berikut melalui Arduino IDE:

## 1. Blynk

Nama Library:

```txt
Blynk
```

Author:

```txt
Volodymyr Shymanskyy
```

## 2. ESP8266WiFi

Library ini tersedia setelah install board ESP8266.

---

# Cara Install ESP8266 di Arduino IDE

1. Buka Arduino IDE
2. Masuk ke:

```txt
File -> Preferences
```

3. Tambahkan URL berikut pada Additional Board Manager URLs:

```txt
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

4. Masuk ke:

```txt
Tools -> Board -> Boards Manager
```

5. Cari:

```txt
ESP8266
```

6. Install board ESP8266.

---

# Cara Membuat Template Blynk

1. Buka aplikasi atau website Blynk.
2. Buat Template baru.
3. Pilih device:

```txt
NodeMCU 1.0 (ESP-12E Module)
```

4. Connection type:

```txt
WiFi
```

5. Copy:

* BLYNK_TEMPLATE_ID
* BLYNK_TEMPLATE_NAME
* BLYNK_AUTH_TOKEN

---

# Widget Blynk yang Digunakan

## Gauge / Value Display

Gunakan:

```txt
Virtual Pin V0
```

Untuk menampilkan jarak.

## LED Indicator

Gunakan:

```txt
Virtual Pin V1
```

Untuk status pompa.

---

# Source Code

```cpp
#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Ultrasonic Pump"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NamaWiFi";
char pass[] = "PasswordWiFi";

#define TRIG_PIN D5
#define ECHO_PIN D6
#define PUMP_PIN D1

long duration;
int distance;

void setup()
{
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);

    digitalWrite(PUMP_PIN, LOW);

    Blynk.begin(auth, ssid, pass);
}

void loop()
{
    Blynk.run();

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    Blynk.virtualWrite(V0, distance);

    if(distance < 10)
    {
        digitalWrite(PUMP_PIN, HIGH);

        Blynk.virtualWrite(V1, 1);

        Serial.println("Pompa Menyala");
    }
    else
    {
        digitalWrite(PUMP_PIN, LOW);

        Blynk.virtualWrite(V1, 0);

        Serial.println("Pompa Mati");
    }

    delay(1000);
}
```

---

# Cara Upload Program

1. Sambungkan ESP8266 ke laptop.
2. Pilih board:

```txt
NodeMCU 1.0 (ESP-12E Module)
```

3. Pilih COM port yang sesuai.
4. Paste source code.
5. Ganti:

* Nama WiFi
* Password WiFi
* Token Blynk

6. Klik Upload.

---

# Cara Kerja Sistem

1. Sensor ultrasonic membaca jarak objek atau permukaan air.
2. Jika jarak kurang dari 10 cm:

   * Pompa air menyala
   * Status dikirim ke Blynk
3. Jika jarak lebih dari 10 cm:

   * Pompa air mati
   * Status normal dikirim ke Blynk

---

# Rumus Ultrasonic

Jarak dihitung menggunakan rumus:

distance = duration × 0.034 / 2

Keterangan:

* duration = waktu pantulan gelombang
* 0.034 = kecepatan suara
* dibagi 2 karena gelombang bolak-balik

---

# Output Serial Monitor

## Saat Pompa Mati

```txt
Distance: 15 cm
Pompa Mati
```

## Saat Pompa Menyala

```txt
Distance: 5 cm
Pompa Menyala
```

---

# Penjelasan Logika Program

Program dimulai dengan menghubungkan ESP8266 ke jaringan WiFi dan server Blynk menggunakan token autentikasi. Setelah koneksi berhasil, sensor ultrasonic HC-SR04 akan membaca jarak objek menggunakan pin trigger dan echo.

Pin trigger digunakan untuk mengirim gelombang ultrasonik, sedangkan pin echo digunakan untuk menerima pantulan gelombang. Nilai jarak kemudian dihitung menggunakan rumus ultrasonic.

Ketika jarak kurang dari 10 cm, relay pompa air akan aktif menggunakan digitalWrite(PUMP_PIN, HIGH). Selain itu status pompa dan nilai jarak juga dikirim ke aplikasi Blynk menggunakan Blynk.virtualWrite(). Jika jarak lebih dari 10 cm maka pompa akan mati.

---

# Repository Structure

```txt
ultrasonic-waterpump-blynk/
│
├── ultrasonic_waterpump_blynk.ino
├── README.md
│
└── assets/
    └── wiring-diagram.png
```

---

# Kesimpulan

Project ini menunjukkan implementasi dasar IoT menggunakan ESP8266 dan Blynk dengan kombinasi sensor ultrasonic dan aktuator pompa air. Sistem dapat melakukan monitoring jarak secara real-time dan mengontrol pompa air secara otomatis berdasarkan kondisi yang ditentukan.
