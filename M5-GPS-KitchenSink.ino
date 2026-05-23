#include <_m5Core2-only.h>
#include <_GPS.h>

void setup()
{
  _setup_M5();
  M5.Lcd.clear();
  _setup_GPS();
}

void loop()
{
  _test_GPS();  // run example.
  _GPS2LCD();
} 

