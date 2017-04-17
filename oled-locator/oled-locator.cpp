#include "Particle.h"
#include "google-maps-device-locator.h"
#include "Adafruit_SSD1306.h"

SerialLogHandler logHandler;
GoogleMapsDeviceLocator locator;
Adafruit_SSD1306 display;

// SYSTEM_THREAD(ENABLED);

void locationCallback(float lat, float lon, float accuracy);

void setup() {
	Serial.begin(9600);

	// Initialize the OLED display
	// VCC - 3V3
	// GND - GND
	// SCL - D1
	// SDA - D0
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();   // clears the screen and buffer

	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("NO LOCATION");
	display.display();

	locator.withSubscribe(locationCallback).withLocatePeriodic(120);
}


void loop() {
	locator.loop();
}

void locationCallback(float lat, float lon, float accuracy) {
	Serial.printlnf("lat=%f lon=%f accuracy=%f", lat, lon, accuracy);
	display.clearDisplay();   // clears the screen and buffer

	// 10 characters fit at text size 2
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);

	char buf[16];
	snprintf(buf, sizeof(buf), "%.6f", lat);
	display.println(buf);

	snprintf(buf, sizeof(buf), "%.6f", lon);
	display.println(buf);

	snprintf(buf, sizeof(buf), "%.1f", accuracy);
	display.println(buf);

	display.display();
}


