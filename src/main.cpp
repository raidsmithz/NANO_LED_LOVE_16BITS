#include <Arduino.h>
#include "myLed.h"

bool lastButtonState = HIGH;
uint32_t lastButtonDebounce;

void handleButtonToggle()
{
  bool buttonState = digitalRead(buttonPin);

  if ((millis() - lastButtonDebounce) > 50)
  {
    if (lastButtonState == HIGH && buttonState == LOW)
    {
      currentModeLed = (ledMode_t)((currentModeLed + 1) % LED_MODE_COUNT_MAX);
      lastButtonDebounce = millis();
    }
  }

  lastButtonState = buttonState;
}

void setup()
{
  for (int i = 0; i < LED_COUNTS; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  handleButtonToggle();
  updateLedMode();
}
