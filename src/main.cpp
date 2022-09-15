#include <Arduino.h>
#include <Wire.h>
#include <String>
#include "TemperatureStub.h"
 
// Définition des LEDs
#define GPIO_PIN_LED_LOCK_ROUGE 12 // Led Rouge GPIO12
#define GPIO_PIN_LED_OK_VERT 14 // Led Verte GPIO14
#define GPIO_PIN_LED_HEAT_JAUNE 27 // Led Jaune 27
 
// Définition des boutons
#include "MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;
 
// Définition senseur température
#define DHTPIN  15   // Pin utilisée par le DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé
TemperatureStub *temperatureStub = NULL;
 
void setup() {
  Serial.begin(9600);
 
  // Initialisation des LEDs
  pinMode(GPIO_PIN_LED_LOCK_ROUGE, OUTPUT);
  pinMode(GPIO_PIN_LED_OK_VERT, OUTPUT);
  pinMode(GPIO_PIN_LED_HEAT_JAUNE, OUTPUT);
 
  //Initialisation des boutons
  myButtonAction = new MyButton();
  myButtonAction->init(T8);
  int sensibilisationButtonAction = myButtonAction->autoSensibilisation();
 
  myButtonReset = new MyButton();
  myButtonReset->init(T9);
  int sensibilisationButtonReset = myButtonReset->autoSensibilisation();
 
  //Initiation du senseur de température
  temperatureStub = new TemperatureStub;
  temperatureStub->init(DHTPIN, DHTTYPE);
}
 
void loop() {
  float t = temperatureStub->getTemperature();
  int i;

  Serial.print("Température : ");
  Serial.println(t);
 
  delay(2000);
 
  //Gestion du bouton Action
  int buttonAction = myButtonAction->checkMyButton();
  if(buttonAction > 2)  {
    if(t > 25)
    {
      Serial.println("Vous avez appuyé sur le bouton d'action ");
      for (i = 0; i < 5; i++)
      {
        digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, HIGH);
        delay(500);
        digitalWrite(GPIO_PIN_LED_LOCK_ROUGE, LOW);
        delay(500);
      }
    }
    else{
      digitalWrite(GPIO_PIN_LED_HEAT_JAUNE, HIGH);
      delay(3000);
      digitalWrite(GPIO_PIN_LED_HEAT_JAUNE, LOW);
    }
  }
}