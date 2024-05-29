#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

// Define pins
#define LM35_PIN A0         // Analog pin connected to the LM35 temperature sensor
#define ACS712_PIN A1       // Analog pin connected to the ACS712 current sensor
#define SCREEN_WIDTH 128    // OLED display width
#define SCREEN_HEIGHT 64    // OLED display height
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDRESS 0x3C   // I2C address for the OLED display
#define SD_CS 4             // Chip select pin for the SD card
#define AUDIO_PIN 9         // Pin for the audio output

// Initialize the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Initialize the audio library
TMRpcm audio;

// Variables for measurements
float temperatura = 0.0;
float corriente = 0.0;
float voltaje = 0.0;
float potencia = 0.0;
float porcentaje_bateria = 0.0;
float tiempo_restante = 0.0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Infinite loop to halt the program
  }
  display.display();
  delay(2000); // Pause to allow the display to initialize
  display.clearDisplay();

  // Initialize the SD card
  if (!SD.begin(SD_CS)) {
    Serial.println(F("SD card initialization failed"));
    for (;;); // Infinite loop to halt the program
  }

  // Initialize the audio library
  audio.speakerPin = AUDIO_PIN;
}

void loop() {
  // Read the value from the LM35 temperature sensor
  int lm35_value = analogRead(LM35_PIN);
  // Convert the analog value to temperature in degrees Celsius
  temperatura = (lm35_value * (5.0 / 1023.0)) * 100;

  // Read the value from the ACS712 current sensor
  int acs712_value = analogRead(ACS712_PIN);
  // Convert the analog value to voltage
  voltaje = acs712_value * (5.0 / 1023.0);
  // Calculate the current in amperes
  float voltage_offset = voltaje - 2.5;  // Offset for zero amperes
  corriente = voltage_offset / 0.185;    // Sensitivity for ACS712-05B

  // Calculate battery percentage based on voltage
  porcentaje_bateria = calcularPorcentajeBateria(voltaje);

  // Calculate power (P = V * I)
  potencia = voltaje * corriente;

  // Estimate remaining time (example values, adjust based on actual battery specs)
  tiempo_restante = (porcentaje_bateria / 100.0) * 5.0; // Example: 5 hours for full charge

  // Display measurements on the OLED screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperatura);
  display.print(" C");

  display.setCursor(0, 10);
  display.print("Current: ");
  display.print(corriente);
  display.print(" A");

  display.setCursor(0, 20);
  display.print("Voltage: ");
  display.print(voltaje);
  display.print(" V");

  display.setCursor(0, 30);
  display.print("Power: ");
  display.print(potencia);
  display.print(" W");

  display.setCursor(0, 40);
  display.print("Battery: ");
  display.print(porcentaje_bateria);
  display.print(" %");

  display.setCursor(0, 50);
  display.print("Time: ");
  display.print(tiempo_restante);
  display.print(" h");
  display.display();

  // Play alerts based on conditions
  if (porcentaje_bateria >= 100.0) {
    audio.play("complete.wav");
  } else if (porcentaje_bateria <= 20.0) {
    audio.play("low_batt.wav");
  } else if (corriente > 5.0) {
    audio.play("overload.wav");
  } else if (temperatura > 50.0) {
    audio.play("high_temp.wav");
  }

  // Wait for one second before the next measurement
  delay(1000);
}

// Function to calculate battery percentage based on voltage
float calcularPorcentajeBateria(float voltaje) {
  if (voltaje >= 4.2) {
    return 100.0;
  } else if (voltaje >= 4.0) {
    return 80.0 + (voltaje - 4.0) * 100.0 / 0.2;
  } else if (voltaje >= 3.7) {
    return 50.0 + (voltaje - 3.7) * 30.0 / 0.3;
  } else if (voltaje >= 3.5) {
    return 20.0 + (voltaje - 3.5) * 30.0 / 0.2;
  } else if (voltaje >= 3.0) {
    return (voltaje - 3.0) * 20.0 / 0.5;
  } else {
    return 0.0;
  }
}
