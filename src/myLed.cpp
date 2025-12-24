#include "myLed.h"

int ledIndex = 0;
int ledDirection = 1;
bool blinkState = false;
uint32_t lastLedUpdate;
ledMode_t currentModeLed = LED_ALL_OFF;

void allLedsOff()
{
    for (int i = 0; i < LED_COUNTS; i++)
    {
        digitalWrite(ledPins[i], LOW);
    }
}

void allLedsOn()
{
    for (int i = 0; i < LED_COUNTS; i++)
    {
        digitalWrite(ledPins[i], HIGH);
    }
}

void blinkAllLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    blinkState = !blinkState;
    for (int i = 0; i < 16; i++)
        digitalWrite(ledPins[i], blinkState);
}

void runningLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    allLedsOff();
    digitalWrite(ledPins[ledIndex], HIGH);
    digitalWrite(ledPins[ledIndex + 1], HIGH);
    digitalWrite(ledPins[ledIndex + 2], HIGH);
    digitalWrite(ledPins[ledIndex + 3], HIGH);

    ledIndex++;
    if (ledIndex >= LED_COUNTS)
        ledIndex = 0;
}

void pingPongLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    allLedsOff();
    digitalWrite(ledPins[ledIndex], HIGH);

    ledIndex += ledDirection;
    if (ledIndex == 15 || ledIndex == 0)
        ledDirection = -ledDirection;
}

void fillUpLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    for (int i = 0; i <= ledIndex; i++)
        digitalWrite(ledPins[i], HIGH);

    ledIndex++;
    if (ledIndex >= 16)
        ledIndex = 0;
}

void fillDownLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    for (int i = 15; i >= ledIndex; i--)
        digitalWrite(ledPins[i], HIGH);

    ledIndex++;
    if (ledIndex >= 16)
        ledIndex = 0;
}

void centerOutLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    allLedsOff();

    int left = 7 - ledIndex;
    int right = 8 + ledIndex;

    if (left >= 0)
        digitalWrite(ledPins[left], HIGH);
    if (right < 16)
        digitalWrite(ledPins[right], HIGH);

    ledIndex++;
    if (left < 0 && right >= 16)
        ledIndex = 0;
}

void edgeInLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    allLedsOff();

    int left = ledIndex;
    int right = 15 - ledIndex;

    if (left <= right)
    {
        digitalWrite(ledPins[left], HIGH);
        digitalWrite(ledPins[right], HIGH);
    }

    ledIndex++;
    if (left > right)
        ledIndex = 0;
}

void scannerWideLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    allLedsOff();

    for (int i = -1; i <= 1; i++)
    {
        int idx = ledIndex + i;
        if (idx >= 0 && idx < 16)
            digitalWrite(ledPins[idx], HIGH);
    }

    ledIndex += ledDirection;
    if (ledIndex >= 15 || ledIndex <= 0)
        ledDirection = -ledDirection;
}

void randomSingleLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    allLedsOff();
    digitalWrite(ledPins[random(0, 16)], HIGH);
}

void testSequenceLeds(uint16_t interval)
{
    if (millis() - lastLedUpdate < interval)
        return;
    lastLedUpdate = millis();

    allLedsOff();
    digitalWrite(ledPins[ledIndex], HIGH);

    ledIndex++;
    if (ledIndex >= 16)
        ledIndex = 0;
}

void resetLedState()
{
    ledIndex = 0;
    ledDirection = 1;
    blinkState = false;
    lastLedUpdate = 0;
}

void updateLedMode()
{
    switch (currentModeLed)
    {
    case LED_ALL_OFF:
        allLedsOff();
        break;

    case LED_ALL_ON:
        allLedsOn();
        break;

    case LED_BLINK_SLOW:
        blinkAllLeds(600);
        break;

    case LED_BLINK_MED:
        blinkAllLeds(300);
        break;

    case LED_BLINK_FAST:
        blinkAllLeds(120);
        break;

    case LED_RUNNING_SLOW:
        runningLeds(400);
        break;

    case LED_RUNNING_MED:
        runningLeds(200);
        break;

    case LED_RUNNING_FAST:
        runningLeds(80);
        break;

    case LED_PING_PONG_SLOW:
        pingPongLeds(400);
        break;

    case LED_PING_PONG_MED:
        pingPongLeds(200);
        break;

    case LED_PING_PONG_FAST:
        pingPongLeds(80);
        break;

    case LED_FILL_UP_SLOW:
        fillUpLeds(200);
        break;

    case LED_FILL_UP_MED:
        fillUpLeds(130);
        break;

    case LED_FILL_UP_FAST:
        fillUpLeds(80);
        break;

    case LED_FILL_DOWN_SLOW:
        fillDownLeds(200);
        break;

    case LED_FILL_DOWN_MED:
        fillDownLeds(130);
        break;

    case LED_FILL_DOWN_FAST:
        fillDownLeds(80);
        break;

    case LED_CENTER_OUT:
        centerOutLeds(200);
        break;

    case LED_EDGE_IN:
        edgeInLeds(200);
        break;

    case LED_SCANNER_WIDE:
        scannerWideLeds(120);
        break;

    case LED_RANDOM_SINGLE:
        randomSingleLeds(150);
        break;

    case LED_TEST_SEQUENCE:
        testSequenceLeds(150);
        break;

    default:
        allLedsOff();
        break;
    }
}
