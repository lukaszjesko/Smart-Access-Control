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
    ODRZUCONY
 };

 StanSystemu obecnyStan =  CZEKAM_NA_PIN;
 String tajnyPin = "1234";
 String wpisanyPin = "";
 
 Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Serial.println("System kontroli dostepu gotowy.");
  Serial.println("Wprowadz PIN");


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

    case ZAAKCEPTOWANY:
      Serial.println("-->DOSTEP PRZYZNANY");
      Serial.println("-->ZAMEK OTWARTY NA 3 SEKUNDY");
      delay(3000);
      Serial.println("-->ZAMEK ZAMKNIETY");
      Serial.println("\n-->WPROWADZ PIN:");

      wpisanyPin = "";
      obecnyStan = CZEKAM_NA_PIN;


    break;

    case ODRZUCONY:
    Serial.println("-->ODMOWA DOSTEPU");
    delay(3000);
    Serial.println("\n-->SPROBOJ PONOWNIE, WPROWADZ PIN:");
    wpisanyPin = "";
    obecnyStan = CZEKAM_NA_PIN;

    
    break;
  }
      
      

    
  
}