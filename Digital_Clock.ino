#include <Wire.h>
#include <LiquidCrystal.h>
#include <RTClib.h>

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

RTC_DS3231 rtc;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Start serial communication for debugging
  Serial.begin(9600);  

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

   rtc.adjust(DateTime(2024, 8, 4, 17, 22, 00));

  Serial.println("RTC setup complete");
}

void loop() {
  // Get the current time from RTC
  DateTime now = rtc.now();
  float temperature = rtc.getTemperature(); // Get temperature from RTC

  // Print time to LCD
  lcd.clear(); // Clear the LCD screen
  
  // Print time in HH:MM:SS format
  lcd.setCursor(0, 0); // Set cursor to the first column and first row
  if (now.hour() < 10) {
    lcd.print("0"); // Print leading zero for single digit hour
  }
  lcd.print(now.hour()); // Print hours
  lcd.print(":"); // Print colon
  if (now.minute() < 10) {
    lcd.print("0"); // Print leading zero for single digit minute
  }
  lcd.print(now.minute()); // Print minutes
  lcd.print(":"); // Print colon
  if (now.second() < 10) {
    lcd.print("0"); // Print leading zero for single digit second
  }
  lcd.print(now.second()); // Print seconds

  // Print date in DD/MM/YYYY format
  lcd.setCursor(0, 1); // Set cursor to the first column and second row
  if (now.day() < 10) {
    lcd.print("0"); // Print leading zero for single digit day
  }
  lcd.print(now.day()); // Print day
  lcd.print("/"); // Print slash
  if (now.month() < 10) {
    lcd.print("0"); // Print leading zero for single digit month
  }
  lcd.print(now.month()); // Print month
  lcd.print("/"); // Print slash
  lcd.print(now.year()); // Print year

  // Print temperature on the second row
  lcd.setCursor(11, 1); // Set cursor to the eleventh column and second row
  lcd.print(temperature);
  lcd.print((char)223); // Print degree symbol
  lcd.print("C"); // Print 'C' for Celsius
  
  delay(1000);  // Delay 1 second between updates
}
