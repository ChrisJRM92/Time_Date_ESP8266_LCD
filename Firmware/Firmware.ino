#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define D3 0 //GPIO0
#define D4 2 //GPIO2

LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "YourSSID";
const char* password = "YourPASS";


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -18000, 60000);

void setup() {
  Wire.begin(D3, D4);
  lcd.begin(20, 4); //20, 4
  lcd.backlight();
  lcd.clear();
  Serial.begin(115200);

  lcd.setCursor(3, 0);
  lcd.print("Hola Christian");
  lcd.setCursor(5, 1);
  lcd.print("Bienvenido");
  lcd.setCursor(0, 2); 
  lcd.print("====================");
  lcd.setCursor(0, 3);
  lcd.print("Conectando WIFI");
  delay(10000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Hola Christian");
    lcd.setCursor(5, 1);
    lcd.print("Bienvenido");
    lcd.setCursor(0, 2); 
    lcd.print("====================");
    lcd.setCursor(0, 3);
    lcd.print("Conectando");
    lcd.setCursor(10, 3);
    lcd.print(".");
    delay(500);
    lcd.setCursor(11, 3);
    lcd.print(".");
    delay(500);
    lcd.setCursor(12, 3);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Hola Christian");
  lcd.setCursor(5, 1);
  lcd.print("Bienvenido");
  lcd.setCursor(0, 2); 
  lcd.print("====================");
  lcd.setCursor(0, 3);
  lcd.print("Conexion establecida");
  delay(5000);
  lcd.clear();

  timeClient.begin();
}

void loop() {
  lcd.setCursor(3, 0);
  lcd.print("Hola Christian");
  lcd.setCursor(5, 1);
  lcd.print("Bienvenido");
  lcd.setCursor(0, 2); 
  lcd.print("====================");

  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();

  int day = getDay(epochTime);
  int month = getMonth(epochTime);
  int year = getYear(epochTime);

  lcd.setCursor(0, 3);
  lcd.print(formattedTime);

  lcd.setCursor(10, 3);
  lcd.print(day);
  lcd.print("/");
  lcd.print(month);
  lcd.print("/");
  lcd.print(year);

  delay(1000);
}

int getDay(unsigned long epoch) {
  time_t rawtime = epoch;
  struct tm * ti;
  ti = localtime (&rawtime);
  return ti->tm_mday;
}

int getMonth(unsigned long epoch) {
  time_t rawtime = epoch;
  struct tm * ti;
  ti = localtime (&rawtime);
  return ti->tm_mon + 1;
}

int getYear(unsigned long epoch) {
  time_t rawtime = epoch;
  struct tm * ti;
  ti = localtime (&rawtime);
  return ti->tm_year + 1900;
}
