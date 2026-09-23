#include <Arduino.h>
#include <Bounce2.h>

#define TOGGLE_BUTTON_PIN 6
#define TOGGLE_LIGHT_PIN 5
#define TOGGLE_PREFIX "bouton0"

#define MOMENTARY_BUTTON_PIN 8
#define MOMENTARY_LIGHT_PIN 7
#define MOMENTARY_PREFIX "bouton1"

#define BAUD 115200

Bounce2::Button toggleButton = Bounce2::Button();
Bounce2::Button momentaryButton = Bounce2::Button();

bool toggleState = LOW;

void setup() {
  
  pinMode(TOGGLE_LIGHT_PIN, OUTPUT);
  digitalWrite(TOGGLE_LIGHT_PIN, toggleState);
  pinMode(MOMENTARY_LIGHT_PIN, OUTPUT);
  digitalWrite(MOMENTARY_LIGHT_PIN, LOW);

  
  toggleButton.attach(TOGGLE_BUTTON_PIN, INPUT_PULLUP);
  toggleButton.setPressedState(LOW);

  momentaryButton.attach(MOMENTARY_BUTTON_PIN, INPUT_PULLUP);
  momentaryButton.setPressedState(LOW);

  
  Serial.begin(BAUD);
}

void loop() {
  toggleButton.update();
  momentaryButton.update();

  if (toggleButton.pressed()) {
    toggleState = !toggleState;

    digitalWrite(TOGGLE_LIGHT_PIN, toggleState);

    Serial.print(TOGGLE_PREFIX);
    Serial.print(" ");
    Serial.print(toggleState ? "1" : "0");
    Serial.print("\n");
  }

   if (momentaryButton.pressed() || momentaryButton.released()) {
     bool pressed = momentaryButton.isPressed();

     digitalWrite(MOMENTARY_LIGHT_PIN, pressed);

     if(pressed) {
         Serial.print(MOMENTARY_PREFIX);
        Serial.print(" 1\n");
     }
   }

}