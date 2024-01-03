#define TOUCH_GT911
#define TOUCH_SCL 20
#define TOUCH_SDA 19
#define TOUCH_INT -1
#define TOUCH_RST -1
#define TOUCH_ROTATION ROTATION_NORMAL
#define TOUCH_WIDTH 800
#define TOUCH_HEIGHT 480

int touch_last_x = 0, touch_last_y = 0;

#include <Wire.h>
#include <TAMC_GT911.h>
TAMC_GT911 ts = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

bool touch_has_signal() {
#if defined(TOUCH_FT6X36)
  ts.loop();
  return touch_touched_flag || touch_released_flag;

#elif defined(TOUCH_GT911)
  return true;

#elif defined(TOUCH_XPT2046)
  return ts.tirqTouched();

#else
  return false;
#endif
}

void touch_init() {
  Wire.begin(TOUCH_SDA, TOUCH_SCL);
  ts.begin();
  ts.setRotation(TOUCH_ROTATION);
  Serial.println("Touch Initialized!");
}

bool touch_touched() {
  ts.read();
  if (ts.isTouched) {
    Serial.println("Touch Detected");
#if defined(TOUCH_SWAP_XY)
    touch_last_x = map(ts.points[0].x, TOUCH_WIDTH, 0, 0, lcd.width() - 1);
    touch_last_y = map(ts.points[0].y, TOUCH_HEIGHT, 0, 0, lcd.height() - 1);
#else
    touch_last_x = ts.points[0].x;
    touch_last_y = ts.points[0].y;
#endif
    return true;
    Serial.println("touch_touched = true");
  } else {
    return false;
    Serial.println("touch_touched = false");
  }
}

bool touch_released() {
#if defined(TOUCH_FT6X36)
  if (touch_released_flag) {
    touch_released_flag = false;
    return true;
  } else {
    return false;
  }

#elif defined(TOUCH_GT911)
  return true;
  Serial.println("Touch Released line 69");

#elif defined(TOUCH_XPT2046)
  return true;

#else
  return false;
#endif
}