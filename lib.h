//#include <Arduino.h>

#define LOG 1

#define HOUR_WAITING        40
//#define TIME_WAITING        (915717 * HOUR_WAITING)  // 1hour = 915717 // 10m = 152620
//#define TIME_WAITING        (10836)  // 10m = 152620
#define TIME_WAITING        (3600000 * 7)  // 10m = 152620
#define TIME_NHA            1000
#define SPEED               255

#define CHARGE_STATE        0
#define DISCHARGE_STATE     1
#define WAITING_STATE       2

#define BUTTON_PIN        5
#define HIGH_PIN          4
#define LOW_PIN           2
#define OUT1_PIN          21
#define OUT2_PIN          20
#define OUT3_PIN          19
#define OUT4_PIN          18
#define LED_PIN           13   // LED_BUILTIN = 13
#define DIR_PIN           7
#define PUL_PIN           6
#define CTHT_PIN          17  // (A3)
#define ACTIVE_STATE      LOW
#define NON_ACTIVE_STATE  HIGH

//git config --global user.name "giang631125"
//git config --global user.email "honggiang8297@gmail.com"
