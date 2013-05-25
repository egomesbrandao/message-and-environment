#include <LiquidCrystal.h>
#include <dht11.h>
#include <AdvancedSerial.h>

#define BACKLIGHT_ON_MESSAGE 0
#define BACKLIGHT_OFF_MESSAGE 1
#define TEXT_MESSAGE 2

#define PIN_BACKLIGHT 7

dht11 DHT11;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  //AdvancedSerial
  //configure backlight pin
  pinMode(PIN_BACKLIGHT, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("Inicializando...");
  delay(2000);
  DHT11.attach(2);
  
  //AdvancedSerial
  //begin serial port with a desirable speed
  Serial.begin(115200);
  //configure receiver callback
  AdvancedSerial.setReceiver(onMessage);
}

void loop()
{
//  lcd.setCursor(0, 0);
//
//  int chk = DHT11.read();
//  
//  lcd.print("Humidade (%): ");
//  lcd.print((float) DHT11.humidity, DEC);
//
//  lcd.setCursor(0, 1);
//  
//  lcd.print("Temp. (C): ");
//  lcd.print((float) DHT11.temperature, DEC);
  
  //AdvancedSerial
  AdvancedSerial.loop();
}

void onMessage(AdvancedSerialMessage* message) {
  switch (message->id) {
    case BACKLIGHT_ON_MESSAGE:
      digitalWrite(PIN_BACKLIGHT, HIGH);
      break;
      
    case BACKLIGHT_OFF_MESSAGE:
      digitalWrite(PIN_BACKLIGHT, LOW);
      break;
      
    case TEXT_MESSAGE:
      lcd.clear();
      for (int i = 0; i<message->size; i++) {
        if (i == 16) lcd.setCursor(0, 1);
        lcd.write((char)message -> payload[i]);
      }
    break;
  }
}
