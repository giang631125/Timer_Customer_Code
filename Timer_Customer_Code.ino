#include "lib.h"

//#define LOG

char flag = 0;
unsigned int cur_time = 0;
unsigned int pre_time = 0;


void setup() {
  gpio_init();
#ifdef LOG
  Serial.begin(115200);
#endif
}

void loop() {
  char buttonState = 0;
  char highState = 0;
  char lowState = 0;
  unsigned int VALUE_DELAY = 0;

  buttonState = digitalRead(BUTTON_PIN);
  highState = digitalRead(HIGH_PIN);
  lowState = digitalRead(LOW_PIN);

  // 1hour = 915717
  if (lowState == ACTIVE_STATE)    VALUE_DELAY = 915717 * 20;
  else VALUE_DELAY = VALUE_DELAY * 7;

  if (( buttonState == ACTIVE_STATE) )//or (Serial.available() > 0))
  {
    {
      cur_time = millis();
#ifdef LOG
      if (pre_time != cur_time / 1000)
      {
        Serial.print("\ncur_time: ");
        Serial.print(cur_time / 1000);
      }
#endif
      digitalWrite(LED_PIN, LOW);
      digitalWrite(OUT1_PIN, HIGH);
      digitalWrite(OUT2_PIN, HIGH);
      digitalWrite(OUT3_PIN, HIGH);
      digitalWrite(OUT4_PIN, HIGH);
    }
  }
  if ((millis() - cur_time) >= (915717 * 24)\
      and (highState == NON_ACTIVE_STATE))  //915717
  {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(OUT1_PIN, LOW);
    digitalWrite(OUT2_PIN, LOW);
    digitalWrite(OUT3_PIN, LOW);
    digitalWrite(OUT4_PIN, LOW);
#ifdef LOG
    if (pre_time != (millis() / 1000))
    {
      Serial.print("\nEnough 10s   ");
      Serial.print(millis() / 1000);
    }
#else
    asm volatile ( "jmp 0");
#endif
  }
  pre_time = millis() / 1000;
}
