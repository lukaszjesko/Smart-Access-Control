Dokumentacja Techniczna: Smart Access Control System (Zamek RFID + PIN)
1. Opis Projektu
Profesjonalny system kontroli dostępu oparty na mikrokontrolerze Arduino Nano. System przeprowadza dwuetapową weryfikację użytkownika: za pomocą sprzętowego klucza (karta zbliżeniowa RFID RC522 po magistrali SPI), a następnie weryfikacji opartej na wiedzy (4-cyfrowy kod PIN wprowadzany na matrycowej klawiaturze membranowej). Interfejs użytkownika realizowany jest poprzez wyświetlacz LCD 16x2 (I2C) oraz sygnalizację akustyczną i optyczną. Elementem wykonawczym jest moduł przekaźnika sterujący ryglem elektromagnetycznym.

2. Status Projektu
Stan: UKOŃCZONY (Wersja 1.0)

Architektura oprogramowania: Wzorzec Maszyny Stanów (FSM) z pełną odpornością na blokowanie (brak wielokrotnego odczytu tej samej karty).

Walidacja sprzętowa (Hardware Debugging): Przeprowadzono pomyślnie. Skorygowano logikę sterowania przekaźnikiem (domyślny stan HIGH eliminujący spadki napięcia na szynie 5V) oraz wprowadzono formatowanie ramki UID karty (funkcja trim()).

KiCad (PCB): Projekt sprzętowy zweryfikowany (ERC), wygenerowano pliki produkcyjne Gerber.

3. Mapa połączeń sprzętowych (Pinout)
Magistrale Komunikacyjne
Wyświetlacz LCD 16x2 (I2C) - Zasilanie 5V:

SDA -> A4

SCL -> A5

Czytnik RFID MFRC522 (SPI) - Zasilanie 3.3V:

SDA (SS) -> D10

MOSI -> D11

MISO -> D12

SCK -> D13

Urządzenia Wejścia/Wyjścia
Klawiatura Matrycowa 4x4:

Rzędy (R1-R4) -> D6, D7, D8, D9

Kolumny (C1-C4) -> D5, D4, D3, D2

Sygnalizacja i Wykonawstwo:

Buzzer -> A0

Dioda Zielona (z rezystorem) -> A1

Dioda Czerwona (z rezystorem) -> A2

Przekaźnik (Active LOW) -> A3

4. Ostateczny kod źródłowy (main.cpp)
#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SDA_PIN 10
#define RST_PIN -1

MFRC522 rfid(SDA_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const byte ROWS = 4; 
const byte COLS = 4;

byte rowPins[ROWS] = {6,7,8,9};
byte colPins[COLS] = {5,4,3,2};

char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};

enum StanSystemu {
    CZEKAM_NA_PIN,
    WPISYWANIE_PINU,
    ZAAKCEPTOWANY,
    ODRZUCONY,
    CZEKAM_NA_KARTE
};

StanSystemu obecnyStan = CZEKAM_NA_KARTE;

String dozwolonaKarta = "C3 63 0D 2D";
String tajnyPin = "1234";
String wpisanyPin = "";

const byte PIN_BUZZER = A0;
const byte PIN_LED_ZIELONA = A1;
const byte PIN_LED_CZERWONA = A2;
const byte PIN_PRZEKAZNIK = A3;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  SPI.begin();
  rfid.PCD_Init();
  Serial.begin(115200);
  
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_ZIELONA, OUTPUT);
  pinMode(PIN_LED_CZERWONA, OUTPUT);
  pinMode(PIN_PRZEKAZNIK, OUTPUT);

  // Przekaźnik Active LOW - stan wysoki oznacza wyłączenie cewki
  digitalWrite(PIN_PRZEKAZNIK, HIGH);
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED_CZERWONA, HIGH);
  digitalWrite(PIN_LED_ZIELONA, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System gotowy");
  lcd.setCursor(0, 1);
  lcd.print("Zbliz karte: ");
}

void loop() {
  char key = keypad.getKey();
  
  switch(obecnyStan){
    
    case CZEKAM_NA_PIN:
      if (key){
        wpisanyPin += key;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wprowadz PIN:");
        lcd.setCursor(0, 1);
        lcd.print("*");
        obecnyStan = WPISYWANIE_PINU;
      }
    break;

    case WPISYWANIE_PINU:
      if(key){
        wpisanyPin += key;
        lcd.print("*");

        if (wpisanyPin.length() == 4){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Sprawdzanie PINu...");

          if (wpisanyPin == tajnyPin){
            obecnyStan = ZAAKCEPTOWANY;
          }else{
            obecnyStan = ODRZUCONY;
          }
        }
      }
    break;

    case CZEKAM_NA_KARTE:
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {      
        String odczytaneUID = "";
        for (byte i = 0; i < rfid.uid.size; i++) {         
          odczytaneUID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
          odczytaneUID.concat(String(rfid.uid.uidByte[i], HEX));
        }
        odczytaneUID.toUpperCase(); 
        odczytaneUID.trim(); // Usunięcie wiodącej spacji z formatowania HEX
        
        if (odczytaneUID == dozwolonaKarta) { 
          Serial.println("Rozpoznano karte: " + odczytaneUID);
          rfid.PICC_HaltA();
          digitalWrite(PIN_BUZZER, HIGH); delay(100); digitalWrite(PIN_BUZZER, LOW); 
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Karta OK");
          lcd.setCursor(0, 1);
          lcd.print("Wprowadz PIN:");
          obecnyStan = CZEKAM_NA_PIN; 
        }
        else {
          Serial.println("Nieznana karta: " + odczytaneUID);
          rfid.PICC_HaltA();
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Odmowa dostepu");
          lcd.setCursor(0, 1);
          lcd.print("Nieznana karta");

          digitalWrite(PIN_BUZZER, HIGH);
          delay(2000);
          digitalWrite(PIN_BUZZER, LOW);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("System gotowy");
          lcd.setCursor(0, 1);
          lcd.print("Zbliz karte: ");
        }
      }
    break;

    case ZAAKCEPTOWANY:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dostep przyznany"); 
      lcd.setCursor(0, 1);
      lcd.print("Zamek otwarty");
      
      digitalWrite(PIN_LED_CZERWONA, LOW);
      digitalWrite(PIN_LED_ZIELONA, HIGH);
      
      // Otwarcie zamka (Przekaźnik Active LOW)
      digitalWrite(PIN_PRZEKAZNIK, LOW);
      delay(3000);
      digitalWrite(PIN_PRZEKAZNIK, HIGH);
      
      digitalWrite(PIN_LED_ZIELONA, LOW);
      digitalWrite(PIN_LED_CZERWONA, HIGH);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("System gotowy");
      lcd.setCursor(0, 1);
      lcd.print("Zbliz karte: ");

      wpisanyPin = "";
      obecnyStan = CZEKAM_NA_KARTE;
    break;

    case ODRZUCONY:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Odmowa dostepu!");
      lcd.setCursor(0, 1);
      lcd.print("Bledny PIN!");
      
      digitalWrite(PIN_BUZZER, HIGH);
      delay(2000);
      digitalWrite(PIN_BUZZER, LOW);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("System gotowy");
      lcd.setCursor(0, 1);
      lcd.print("Zbliz karte: ");
      
      wpisanyPin = "";
      obecnyStan = CZEKAM_NA_KARTE;
    break;
  }
}
