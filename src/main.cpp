#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>


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

 StanSystemu obecnyStan = CZEKAM_NA_PIN;

 String tajnyPin = "1234";
 String wpisanyPin = "";
 const byte PIN_BUZZER = A0;
 const byte PIN_LED_ZIELONA = A1;
 const byte PIN_LED_CZERWONA = A2;
 const byte PIN_PRZEKAZNIK = A3;
 
 Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {

  Serial.begin(115200);
  digitalWrite(PIN_PRZEKAZNIK, LOW);
  

  Serial.println("System kontroli dostepu gotowy.");
  Serial.println("Wprowadz PIN");

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_ZIELONA, OUTPUT);
  pinMode(PIN_LED_CZERWONA, OUTPUT);
  pinMode(PIN_PRZEKAZNIK, OUTPUT);

  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED_CZERWONA, HIGH);
  digitalWrite(PIN_LED_ZIELONA, LOW);

}

void loop() {
  char key = keypad.getKey();
  
  switch (obecnyStan){
    case CZEKAM_NA_PIN:
      if (key){
        wpisanyPin+= key;
        Serial.print("*");
        obecnyStan = WPISYWANIE_PINU;

      }
    break;

    case WPISYWANIE_PINU:
      if(key){
        wpisanyPin += key;
        Serial.print("*");

        if (wpisanyPin.length() == 4){
          Serial.println();

          if (wpisanyPin == tajnyPin){
            obecnyStan = ZAAKCEPTOWANY;
          }else{
            obecnyStan = ODRZUCONY;
          }
        
        }
      }
    break;

    case CZEKAM_NA_KARTE:
      
    break;

    case ZAAKCEPTOWANY:
      Serial.println("-->DOSTEP PRZYZNANY");
      Serial.println("-->ZAMEK OTWARTY NA 3 SEKUNDY");
      digitalWrite(PIN_LED_CZERWONA, LOW);
      digitalWrite(PIN_LED_ZIELONA, HIGH);
      digitalWrite(PIN_PRZEKAZNIK, HIGH);
      delay(3000);
      digitalWrite(PIN_PRZEKAZNIK, LOW);
      digitalWrite(PIN_LED_ZIELONA, LOW);
      digitalWrite(PIN_LED_CZERWONA, HIGH);
      Serial.println("-->ZAMEK ZAMKNIETY");
      Serial.println("\n-->WPROWADZ PIN:");

      wpisanyPin = "";
      obecnyStan = CZEKAM_NA_PIN;


    break;

    case ODRZUCONY:
    Serial.println("-->ODMOWA DOSTEPU");
    digitalWrite(PIN_BUZZER, HIGH);
    delay(2000);
    digitalWrite(PIN_BUZZER, LOW);


    Serial.println("\n-->SPROBOJ PONOWNIE, WPROWADZ PIN:");
    wpisanyPin = "";
    obecnyStan = CZEKAM_NA_PIN;

    
    break;
  }
}