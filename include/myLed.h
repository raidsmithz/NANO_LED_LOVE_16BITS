#include <Arduino.h>

#define LED_COUNTS 16

typedef enum
{
    LED_ALL_OFF = 0,
    LED_ALL_ON,

    LED_BLINK_SLOW,
    LED_BLINK_MED,
    LED_BLINK_FAST,

    LED_RUNNING_SLOW,
    LED_RUNNING_MED,
    LED_RUNNING_FAST,

    LED_PING_PONG_SLOW,
    LED_PING_PONG_MED,
    LED_PING_PONG_FAST,

    LED_FILL_UP_SLOW,
    LED_FILL_UP_MED,
    LED_FILL_UP_FAST,

    LED_FILL_DOWN_SLOW,
    LED_FILL_DOWN_MED,
    LED_FILL_DOWN_FAST,

    LED_CENTER_OUT,
    LED_EDGE_IN,

    LED_SCANNER_WIDE,
    LED_RANDOM_SINGLE,
    LED_TEST_SEQUENCE,
    LED_MODE_COUNT_MAX
} ledMode_t;

const uint8_t ledPins[LED_COUNTS] = {
    3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13,
    A0, A1, A2, A3, A4};
const uint8_t buttonPin = 2;

extern ledMode_t currentModeLed;

void allLedsOff(void);
void allLedsOn(void);
void blinkAllLeds(uint16_t interval);
void runningLeds(uint16_t interval);
void pingPongLeds(uint16_t interval);
void fillUpLeds(uint16_t interval);
void fillDownLeds(uint16_t interval);
void centerOutLeds(uint16_t interval);
void edgeInLeds(uint16_t interval);
void scannerWideLeds(uint16_t interval);
void randomSingleLeds(uint16_t interval);
void testSequenceLeds(uint16_t interval);
void resetLedState(void);
void updateLedMode(void);
