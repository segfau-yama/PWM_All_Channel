#include "debug.h"
#include "ch32v20x.h"
u16 control = 0, channel_control = 0, conpare_capture_enable = 0;

int main(void) {
  for (int i = 0; i < 3; i++) {
    motorInit(i, 255, 400);
  }
  Delay_Init();
  Delay_Ms(1000);
  while (1) {
    for (int j = 0; j <= 255; j++) {
      for (int i = 0; i < 3; i++) {

          motorWrite(i, j);
      }

      Delay_Ms(20);
    }
  }
}
