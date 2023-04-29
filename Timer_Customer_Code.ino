#include "lib.h"

static char flag = 0;
unsigned long cur_time = 0;
unsigned long log_time = 0;
unsigned long pre_log_time = -1;
unsigned long pre_time = 0;
uint8_t state = DISCHARGE_STATE;
extern volatile unsigned long timer0_millis;

void setup() {
#if LOG
  Serial.begin(9600);
#endif
  gpio_init();
  do
  {
    cur_time = millis();
    log_time = cur_time/5000;
    motorK();
    digitalWrite(LED_PIN, LOW);
  } while (digitalRead(CTHT_PIN) == NON_ACTIVE_STATE);
}

void loop() 
{
    static bool cthtState = 0;
    char buttonState = 0;
    char highState = 0;
    char lowState = 0;

    cthtState = digitalRead(CTHT_PIN);
    buttonState = digitalRead(BUTTON_PIN);
    highState = digitalRead(HIGH_PIN);
    lowState = digitalRead(LOW_PIN);
    cur_time = millis();
    log_time = cur_time/5000;
    
    switch (state)
    {
    case CHARGE_STATE:
        if((cthtState == NON_ACTIVE_STATE) and (flag == 1) )
        {
            motorK();
            digitalWrite(LED_PIN, LOW);
            cthtState = digitalRead(CTHT_PIN);
        }
        else
        {
            flag = 0;
        }
        motorS();
        
        if (buttonState == NON_ACTIVE_STATE)
        {
            setMillis(100);
            pre_time = millis();
            state = WAITING_STATE;
#if LOG
            Serial.print("Bom xong, pre_time=");
            Serial.println(pre_time/1000);
#endif
        }
        break;

    case WAITING_STATE:
        if ((cur_time - pre_time) > (TIME_WAITING)) // 10m = 152620  // 1hour = 915717 // 
        { // 15s = 15262
            state = DISCHARGE_STATE;
            flag = 0;
        }
#if LOG
        log_time = cur_time/60000;
        if(log_time != pre_log_time)
        {
          Serial.print("Waiting state, cur_time=");
          Serial.println(log_time);
        }
        pre_log_time = log_time;
#endif        
        break;

    case DISCHARGE_STATE:
        if(flag == 0)
        {
            flag = 1;
            motorN();
            digitalWrite(LED_PIN, HIGH);
            delay(TIME_NHA);
        }
        motorS();

        if (buttonState == ACTIVE_STATE)
        {
            state = CHARGE_STATE;
        }
        
#if LOG
        if(log_time != pre_log_time)
        {
            Serial.print("Dang xa - ");
        }
        pre_log_time = log_time;
#endif
        break;
    
    default:
        break;
    }
}

void setMillis(unsigned long new_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}
void gpio_init()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(HIGH_PIN, INPUT);
  pinMode(LOW_PIN, INPUT);
  pinMode(CTHT_PIN, INPUT);
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
void motorK()
{
  digitalWrite(DIR_PIN, LOW);
  analogWrite(PUL_PIN, SPEED);
#if LOG
  if(log_time != pre_log_time)
  {
    Serial.print("motor K \r\n");
  }
  pre_log_time = log_time;
#endif
}
void motorN()
{
  digitalWrite(DIR_PIN, HIGH);
  analogWrite(PUL_PIN, 300 - SPEED);
#if LOG
  if(log_time != pre_log_time)
  {
    Serial.print("motor N \r\n");
  }
  pre_log_time = log_time;
#endif
}
void motorS()
{
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(PUL_PIN, LOW);
#if LOG
  if(log_time != pre_log_time)
  {
    Serial.print("motor S \r\n");
  }
  pre_log_time = log_time;
#endif
}
