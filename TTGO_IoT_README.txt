# TTGO IoT Sensor Project

This project reads temperature and humidity data using a DHT11 sensor connected to a TTGO T-Display ESP32 board. The data is sent to a Flask server running on an AWS EC2 instance and displayed in a browser.

---

## 🔌 Wiring
- **DHT11 VCC** → 3.3V on TTGO
- **DHT11 GND** → GND on TTGO
- **DHT11 DATA** → GPIO 15 on TTGO

---

## 💻 Requirements
### Hardware:
- TTGO T-Display
- DHT11 sensor

### Software:
- PlatformIO (for TTGO firmware)
- Python 3 with Flask (on EC2 server)

---

## ⚙️ ESP32 Code
- Reads sensor data
- Sends data to `/update?temp=...&hum=...` every 5 seconds

---

## 🌐 Flask Server
- Receives data at `/update`
- Shows history at `/` or `/history`
- Auto-refreshes every 5 seconds

### Run it:
```bash
python3 server.py
```

### View in browser:
```
http://:http://18.222.23.244/5000/
```

---

## 📹 Demo Video
[![Watch the demo](https://img.youtube.com/vi/VIDEO_ID_HERE/0.jpg)](https://youtu.be/tUtSn-eP9rw)

\

---

## ✅ Done!
