#include <Arduino.h>

#define BUTTON_PIN      5
#define HIGH_PIN        4
#define LOW_PIN         2
#define OUT1_PIN        21
#define OUT2_PIN        20
#define OUT3_PIN        19
#define OUT4_PIN        18
#define LED_PIN         13   // LED_BUILTIN = 13
#define DIR_PIN         7
#define PUL_PIN         6
#define SW_PIN          17

#define ACTIVE_STATE      LOW
#define NON_ACTIVE_STATE  HIGH

void gpio_init()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(HIGH_PIN, INPUT);
  pinMode(LOW_PIN, INPUT);
  pinMode(SW_PIN, INPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(OUT1_PIN, OUTPUT);
  pinMode(OUT2_PIN, OUTPUT);
  pinMode(OUT3_PIN, OUTPUT);
  pinMode(OUT4_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(OUT1_PIN, LOW);
  digitalWrite(OUT2_PIN, LOW);
  digitalWrite(OUT3_PIN, LOW);
  digitalWrite(OUT4_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(PUL_PIN, LOW);
}
