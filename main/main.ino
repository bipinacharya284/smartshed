#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2        // DHT22 sensor pin
#define DHTTYPE DHT22   // DHT sensor type
DHT dht(DHTPIN, DHTTYPE);

// #define RELAY_BULB A1   // Bulb relay control pin
// #define RELAY_FAN A3    // Fan relay control pin


#define RELAY_BULB A3   // Bulb relay control pin
#define RELAY_FAN A1

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address, columns, rows

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  // lcd.begin(16, 2);
  lcd.backlight();

  pinMode(RELAY_BULB, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);

  // Initialize both relays in the off state
  digitalWrite(RELAY_BULB, HIGH);
  digitalWrite(RELAY_FAN, HIGH);
}

void displayOnLCD(float temperature, float humidity) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
}

void controlDevices(float temperature, float humidity) {
  // Control devices based on +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++temperature
  if (temperature > 18.0) {
    // Turn on the fan
    digitalWrite(RELAY_BULB, HIGH); // Bulb Banda
    digitalWrite(RELAY_FAN, LOW); // Fan Khulla
  } else {
    // Turn off the fan
    digitalWrite(RELAY_BULB, LOW); // Bulb Khulla
    digitalWrite(RELAY_FAN, HIGH);
  }

  
}

void loop() {
  // Read temperature and humidity from DHT22 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Display temperature and humidity on LCD
  displayOnLCD(temperature, humidity);

  // Control devices based on temperature and humidity
  controlDevices(temperature, humidity);

  // Optional: Output temperature and humidity to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  delay(2000); // Delay for 2 seconds


}
